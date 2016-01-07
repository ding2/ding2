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
    private $drupalContext;

    /** @var \Drupal\DrupalExtension\Context\MinkContext */
    private $MinkContext;

    /** @BeforeScenario */
    public function gatherContexts(BeforeScenarioScope $scope)
    {
        $environment = $scope->getEnvironment();

        $this->drupalContext = $environment->getContext('Drupal\DrupalExtension\Context\DrupalContext');
        $this->minkContext = $environment->getContext('Drupal\DrupalExtension\Context\MinkContext');
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
        $this->drupalContext->login();

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
