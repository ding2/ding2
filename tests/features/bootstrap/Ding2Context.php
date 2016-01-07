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
     * Initializes context.
     *
     * Every scenario gets its own context instance.
     * You can also pass arbitrary arguments to the
     * context constructor through behat.yml.
     */
    public function __construct()
    {
    }

    /** @var \Drupal\DrupalExtension\Context\DrupalContext */
    private $drupalContext;

    /**
     * @var \Drupal\DrupalExtension\Context\MinkContext
     */
    private $minkContext;

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
}
