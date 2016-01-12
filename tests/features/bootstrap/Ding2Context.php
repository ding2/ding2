<?php

use Behat\Behat\Context\Context;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;

/**
 * Provides step definitions for interacting with Ding2.
 */
class Ding2Context implements Context, SnippetAcceptingContext
{
    /**
     * Current authenticated user.
     *
     * A value of FALSE denotes an anonymous user.
     *
     * @var stdClass|bool
     */
    public $user = FALSE;

    /** @var \Drupal\DrupalExtension\Context\DrupalContext */
    public $drupalContext;

    /** @var \Drupal\DrupalExtension\Context\MinkContext */
    public $minkContext;

    /** @var \Ding2MessagesContext */
    private $ding2MessagesContext;

    /**
     * @var array
     *   Save data across scenarios.
     */
    private $dataRegistry = array();

    /** @BeforeScenario */
    public function gatherContexts(BeforeScenarioScope $scope)
    {
        $environment = $scope->getEnvironment();

        $this->drupalContext = $environment->getContext('Drupal\DrupalExtension\Context\DrupalContext');
        $this->minkContext = $environment->getContext('Drupal\DrupalExtension\Context\MinkContext');
        try {
            $this->ding2MessagesContext = $environment->getContext('Ding2MessagesContext');
        } catch (Exception $e) {
            // Throw a bit more useful error message.
            throw new Exception('Ding2MessagesContext not found, please add it to behat.yml');
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
        $this->drupalContext->user = $user;
        $this->login();

        // We need the user uid in order to construct some links to user
        // pages, however it's not easily available. We rely on
        // DrupalContext::login() using the /user page, and then look for the
        // link to the user view page there and parse the UID out of the link.
        $link = $this->drupalContext->getSession()->getPage()->findLink('Brugerprofil');
        if (!$link) {
            throw new Exception('Could not find profile link on page.');
        }
        if (preg_match('{user/(\d+)/view}', $link->getAttribute('href'), $matches)) {
            $user->uid = $matches[1];
        } else {
            throw new Exception('Could not parse user UID from profile link.');
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
    public function login()
    {
        // Check if logged in.
        if ($this->drupalContext->loggedIn()) {
            $this->drupalContext->logout();
        }

        if (!$this->drupalContext->user) {
            throw new \Exception('Tried to login without a user.');
        }

        $this->drupalContext->getSession()->visit($this->drupalContext->locatePath('/user'));
        $element = $this->drupalContext->getSession()->getPage();
        $element->fillField($this->drupalContext->getDrupalText('username_field'), $this->drupalContext->user->name);
        $element->fillField($this->drupalContext->getDrupalText('password_field'), $this->drupalContext->user->pass);
        $submit = $element->findButton($this->drupalContext->getDrupalText('log_in'));
        if (empty($submit)) {
            throw new \Exception(sprintf("No submit button at %s", $this->getSession()->getCurrentUrl()));
        }

        // Log in.
        $submit->click();

        $this->ding2MessagesContext->collectMessages();

        if (!$this->drupalContext->loggedIn()) {
            throw new \Exception(sprintf("Failed to log in as user '%s' with role '%s'", $this->user->name, $this->user->role));
        }
    }

    /**
     * Returns the path prefix of the currently logged in user.
     *
     * For instance: /user/1
     */
    public function userPath()
    {
        if (!isset($this->drupalContext->user->uid)) {
            throw new Exception('No currently logged in user.');
        }
        return '/user/' . $this->drupalContext->user->uid;
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
}
