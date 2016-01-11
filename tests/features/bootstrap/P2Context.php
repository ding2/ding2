<?php

use Behat\Behat\Context\Context;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Behat\Tester\Exception\PendingException;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;

/**
 * Provides step definitions for interacting with P2.
 */
class P2Context implements Context, SnippetAcceptingContext
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

    /** @var Ding2Context */
    private $ding2Context;

    /** @BeforeScenario */
    public function gatherContexts(BeforeScenarioScope $scope)
    {
        $environment = $scope->getEnvironment();

        $this->ding2Context = $environment->getContext('Ding2Context');
    }

    /**
     * @Then I should see a link to the create list page
     */
    public function iShouldSeeALinkToTheCreateListPage()
    {
        $this->ding2Context->iSeeALinkTo($this->ding2Context->userPath() .
                                         '/createlist');
    }

    /**
     * @Given The list :arg1 exists
     */
    public function theListExists($arg1)
    {
        $list_name = strtolower(preg_replace('/\s/', '-', $arg1));
        $this->ding2Context->drupalContext->visitPath('/user');
        $link = $this->ding2Context->minkContext->getSession()->getPage()->find('css', '.' . $list_name . ' a');
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
        $this->ding2Context->drupalContext->visitPath('/search/ting/' . urlencode($arg1));
    }

    /**
     * @When I add the search to followed searches
     */
    public function iAddTheSearchToFollowedSearches()
    {
        $followed_searches_id = $this->dataRegistry['user-searches'];
        $this->ding2Context->minkContext->getSession()->getPage()->find('css', 'a[href^="/dinglist/attach/search_query/' . $followed_searches_id . '"]')->click();
    }

    /**
     * @Then I should get a confirmation for followed searches
     */
    public function iShouldGetAConfirmationForFollowedSearches()
    {
        $this->ding2Context->minkContext->assertElementContainsText('.ding-list-message', 'Tilføjet til');
        $this->ding2Context->minkContext->assertElementContainsText('.ding-list-message', 'Søgninger jeg følger');
    }

    /**
     * @Then I should see :arg1 on followed searches
     */
    public function iShouldSeeOnFollowedSearches($arg1)
    {
        $this->ding2Context->drupalContext->visitPath('/user');
        $this->ding2Context->minkContext->assertElementContainsText('.ding-type-ding-list-element .content a', 'harry potter');
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
