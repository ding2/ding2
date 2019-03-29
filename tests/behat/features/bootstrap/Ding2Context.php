<?php

use Behat\Behat\Context\Context;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;
use Behat\Mink\Element\ElementInterface;
use Behat\Mink\Exception\UnsupportedDriverActionException;

/**
 * Provides step definitions for interacting with Ding2.
 */
// phpcs:disable PSR1.Classes.ClassDeclaration.MissingNamespace
class Ding2Context implements Context, SnippetAcceptingContext
{
    /**
     * Current authenticated user.
     *
     * A value of FALSE denotes an anonymous user.
     *
     * @var stdClass|bool
     */
    public $user = false;

    /** @var \Drupal\DrupalExtension\Context\DrupalContext */
    public $drupalContext;

    /** @var \Drupal\DrupalExtension\Context\MinkContext */
    public $minkContext;

    /** @var \Ding2MessagesContext */
    private $ding2MessagesContext;

    /** @BeforeScenario */
    public function beforeScenario(BeforeScenarioScope $scope)
    {
        // Gather contexts.
        $environment = $scope->getEnvironment();

        $this->drupalContext = $environment->getContext('Drupal\DrupalExtension\Context\DrupalContext');
        $this->minkContext = $environment->getContext('Drupal\DrupalExtension\Context\MinkContext');
        try {
            $this->ding2MessagesContext = $environment->getContext('Ding2MessagesContext');
        } catch (Exception $e) {
            // Ingore.
        }

        $this->libContext = $environment->getContext('LibContext');

        // Try to set a default window size. PhantomJS will default to mobile
        // sizes which will make some elements invisible.
        try {
            $this->minkContext->getSession()
                ->getDriver()
                ->resizeWindow(1024, 768, 'current');
        } catch (UnsupportedDriverActionException $e) {
            // Ignore.
        }
    }

    /**
     * @Given I am logged in as a library user
     * @When I log in as a library user
     */
    public function iAmLoggedInAsALibraryUser()
    {
        $name = $this->drupalContext->getRandom()->name(8);
        $user = (object) array(
            'name' => $name,
            'pass' => substr($name, -4),
        );
        $this->login($user);

        // We need the user uid for various reasons, however it's not easily
        // available. Apparently the only place it makes an appearance
        // nowadays is in a class on the body element of the user page. So try
        // to dig it out there.
        $this->drupalContext->getSession()->visit($this->drupalContext->locatePath('/user'));
        $this->waitForPage();
        $body = $this->drupalContext->getSession()->getPage()->find('css', 'body');
        $classes = explode(' ', $body->getAttribute('class'));

        foreach ($classes as $class) {
            if (preg_match('{^page-user-(\d+)$}', $class, $matches)) {
                $user->uid = $matches[1];
                break;
            }
        }

        if (!isset($user->uid)) {
            throw new Exception('Could not sniff out user UID from profile page.');
        }

        // In addition, make a note of the "id" that is used in paths (which
        // is most often "me"), so we can construct paths as would be
        // expected. We're sniffing this rather than hardcoding it because
        // some users are except from the "me" replacement.
        $user->pathId = $user->uid;
        $links = $this->drupalContext->getSession()->getPage()->findAll('css', 'a[href="/user/"]');
        foreach ($links as $link) {
            if (preg_match('{user/(.*)/view}', $link->getAttribute('href'), $matches)) {
                $user->pathId = $matches[1];
                break;
            }
        }
        $this->user = $user;
    }

    /**
     * Log in a user.
     *
     * Copy of Drupal\DrupalExtension\Context\RawDrupalContext::login() that
     * checks the messages just after login.
     *
     * Without this Ding2MessagesContext would be unaware of any Drupal
     * messages just after login, as RawDrupalContext::login() navigates to
     * the user page in order to check that the browser is logged in.
     */
    public function login($user)
    {
        $manager = $this->drupalContext->getUserManager();

        // The current page might be from the previous scenario, and
        // ChromeDriver apparently flushes sessions between scenarios, so
        // start with a fresh front page.
        $this->drupalContext->getSession()->visit($this->drupalContext->locatePath('/'));
        $this->waitForPage();

        // Check if we're logged in.
        $page = $this->drupalContext->getSession()->getPage();
        if ($page->has('css', $this->drupalContext->getDrupalSelector('logged_in_selector'))) {
            $this->drupalContext->logout();
            $this->waitForPage();
        }

        if (!$user) {
            throw new Exception('Tried to login without a user.');
        }

        $manager->setCurrentUser($user);

        // Ensure that we're on a page.
        if (!$page->has('css', 'body.html')) {
            // Wait for the click handler on the login button. There's no
            // other way to check whether the button is ready for clicking, it
            // doesn't use jQuery.once(). Method from
            // https://stackoverflow.com/questions/2518421/jquery-find-events-handlers-registered-with-an-object
            $script = 'typeof window.jQuery == "function" &&
jQuery("a.topbar-link-user").get(0) &&
jQuery._data(jQuery("a.topbar-link-user").get(0), "events") !== undefined &&
jQuery._data(jQuery("a.topbar-link-user").get(0), "events").hasOwnProperty("click");';
            $this->drupalContext->getSession()->wait(5000, $script);
        }

        // Wait for the login button (it's loaded via Ajax) and click it.
        $loginLink = $page->waitFor(5, function ($page) {
            return $page->find('css', 'a[href="/user"]');
        });

        if (!$loginLink) {
            throw new Exception('Could not find loging button after toggling login folddown.');
        }

        $loginLink->click();

        // Wait for the login popdown to show itself.
        $this->drupalContext->getSession()->getPage()->waitFor(5, function ($page) {
            return $page->find('css', 'input#edit-name');
        });

        $element = $this->drupalContext->getSession()->getPage();
        $element->fillField($this->drupalContext->getDrupalText('username_field'), $user->name);
        $element->fillField($this->drupalContext->getDrupalText('password_field'), $user->pass);
        $submit = $element->findButton($this->drupalContext->getDrupalText('log_in'));
        if (empty($submit)) {
            throw new Exception(sprintf("No submit button at %s", $this->getSession()->getCurrentUrl()));
        }

        // Log in.
        $submit->click();

        $logoutLink = $page->waitFor(30, function ($page) {
            // As the login is posted via ajax, and the page is reloaded by
            // JS, there's a chance it haven't done that yet when we get here.
            // Mink/ChromeDriver might throw an exception when an element
            // disappears from under it, so catch any exceptions and try again.
            try {
                return $page->find('css', 'body.logged-in');
            } catch (Throwable $e) {
                return false;
            }
        });

        if (!$logoutLink) {
            throw new Exception("No logout link after logging in");
        }

        //print $logoutLink->getParent()->getHtml();
        if ($this->ding2MessagesContext) {
            $this->ding2MessagesContext->collectMessages();
        }

        if (!$this->drupalContext->loggedIn()) {
            throw new Exception(sprintf("Failed to log in as user '%s'", $user->name));
        }
    }

    /**
     * Returns the path prefix of the currently logged in user.
     *
     * For instance: /user/1
     */
    public function userPath()
    {
        $user = $this->drupalContext->getUserManager()->getCurrentUser();
        if (!isset($user->uid)) {
            throw new Exception('No currently logged in user.');
        }
        return '/user/' . $user->pathId;
    }

    /**
     * Get the uid of the current logged in user.
     */
    public function userUid()
    {
        $user = $this->drupalContext->getUserManager()->getCurrentUser();
        if (!isset($user->uid)) {
            throw new Exception('No currently logged in user.');
        }
        return $user->uid;
    }

    /**
     * @Given I am on my user page
     */
    public function iAmOnMyUserPage()
    {
        $this->minkContext->visit('/user');
    }

    /**
     * Check if there's a link to a given path in the current page.
     *
     * @Given I see a link to :path
     */
    public function iSeeALinkTo($path)
    {
        $xpath = "//a[contains(@href,'" . $path . "')]";
        $links = $this->minkContext->getSession()->getPage()->findAll('xpath', $xpath);
        if (count($links) < 1) {
            throw new Exception(sprintf('Could not see link to %s', $path));
        }
    }

    /**
     * Scroll to an element.
     *
     * @param ElementInterface $element
     *   Element to scroll to.
     * @throws Exception
     */
    public function scrollTo(ElementInterface $element)
    {
        $xpath = strtr($element->getXpath(), ['"' => '\\"']);
        try {
            $this->minkContext->getSession()
                ->evaluateScript(
                    '(document.evaluate("' . $xpath .
                    '", document, null, XPathResult.FIRST_ORDERED_NODE_TYPE, null ).singleNodeValue).scrollIntoView();'
                );
        } catch (UnsupportedDriverActionException $e) {
            // Ignore.
        } catch (Exception $e) {
            throw new Exception('Could not scroll to element');
        }
    }

    /**
     * Wait for page to load.
     */
    public function waitForPage()
    {
        try {
            // Strictly, this waits for jQuery to be loaded, but it seems
            // sufficient.
            $this->drupalContext->getSession()->wait(5000, 'typeof window.jQuery == "function"');
        } catch (UnsupportedDriverActionException $e) {
            // Ignore.
        } catch (Exception $e) {
            throw new Exception('Unknown error waiting for page');
        }
    }

    /**
     * Wait for page to be fully loaded.
     */
    public function waitForPageLoad()
    {
        $this->waitForPage();
        try {
            // Add an document.ready() handler that adds a window.load()
            // handler which sets our variable. This ensures that it's only
            // set when everything is loaded. See
            // https://stackoverflow.com/questions/5006922/window-load-inside-a-document-ready
            $script = 'window.Ding2ContextLoaded = false;
jQuery(function ($) {
  $(window).load(function () {
    window.Ding2ContextLoaded = true;
  });
});';
            $this->drupalContext->getSession()->evaluateScript($script);
            $this->drupalContext->getSession()->wait(5000, 'window.Ding2ContextLoaded == true');
        } catch (UnsupportedDriverActionException $e) {
            // Ignore.
        } catch (Exception $e) {
            throw new Exception('Unknown error waiting for page');
        }
    }
}
