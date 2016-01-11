<?php

use Behat\Behat\Context\Context;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Behat\Tester\Exception\PendingException;
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
    private $drupalContext;

    /** @var \Drupal\DrupalExtension\Context\MinkContext */
    private $minkContext;

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
        $this->iAmOn('/user');
    }

    /**
     * Go to a path.
     *
     * @Given I am on :path
     */
    public function iAmOn($path)
    {
        $this->minkContext->assertAtPath($path);
    }

    /**
     * @Given The list :arg1 exists
     */
    public function theListExists($arg1)
    {
        $list_name = strtolower(preg_replace('/\s/', '-', $arg1));
        $this->drupalContext->visitPath('/user');
        $link = $this->minkContext->getSession()->getPage()->find('css', '.' . $list_name . ' a');
        if (!$link) {
            throw new \Exception("Couldn't find the list");
        }
        $list_a = $link->getAttribute('href');
        $match = array();
        if (!preg_match('/\/list\/(\d+)/', $list_a, $match)) {
            throw new \Exception("List is not formatted correctly");
        }

        // Save id of list.
        $this->dataRegistry[$list_name] = $match[1];
    }

    /**
     * @When I have searched for :arg1
     */
    public function iHaveSearchedFor($arg1)
    {
        $this->drupalContext->visitPath('/search/ting/' . urlencode($arg1));
    }

    /**
     * @When I add the search to followed searches
     */
    public function iAddTheSearchToFollowedSearches()
    {
        $followed_searches_id = $this->dataRegistry['user-searches'];
        $this->minkContext->getSession()->getPage()->find('css', 'a[href^="/dinglist/attach/search_query/' . $followed_searches_id . '"]')->click();
    }

    /**
     * @Then I should get a confirmation for followed searches
     */
    public function iShouldGetAConfirmationForFollowedSearches()
    {
        $this->minkContext->assertElementContainsText('.ding-list-message', 'Tilføjet til');
        $this->minkContext->assertElementContainsText('.ding-list-message', 'Søgninger jeg følger');
    }

    /**
     * @Then I should see :arg1 on followed searches
     */
    public function iShouldSeeOnFollowedSearches($arg1)
    {
        $this->drupalContext->visitPath('/user');
        $this->minkContext->assertElementContainsText('.ding-type-ding-list-element .content a', 'harry potter');
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
     * @When I add the author to authors I follow
     */
    public function iAddTheAuthorToAuthorsIFollow()
    {
        throw new PendingException();
    }

    /**
     * @Then I should see :arg1 on the list of followed authors
     */
    public function iShouldSeeOnTheListOfFollowedAuthors($arg1)
    {
        throw new PendingException();
    }
}
