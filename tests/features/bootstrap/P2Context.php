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
     * @Then The list :arg1 exists
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
     * @Given I have searched for :arg1
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
        $found = $this->ding2Context->minkContext->getSession()->getPage()->find('css', 'a[href^="/dinglist/attach/search_query/' . $followed_searches_id . '"]');
        if (!$found) {
            throw new \Exception("Couldn't find button to add search to list.");
        }

        $found->click();
    }

    /**
     * @Then I should see :arg1 on followed searches
     */
    public function iShouldSeeOnFollowedSearches($arg1)
    {
        $followed_searches_id = $this->dataRegistry['user-searches'];
        $this->ding2Context->drupalContext->visitPath("/list/$followed_searches_id");
        $this->ding2Context->minkContext->assertElementContainsText('.ding-type-ding-list-element .content a', $arg1);
    }

    /**
     * @Given I have followed the search :arg1
     */
    public function iHaveFollowedTheSearch($arg1)
    {
        // Perform search.
        $this->iHaveSearchedFor($arg1);
        $this->iAddTheSearchToFollowedSearches();
        $this->iShouldSeeOnFollowedSearches($arg1);
    }

    /**
     * @When I remove the search :arg1 from followed searches
     */
    public function iRemoveTheSearchFromFollowedSearches($arg1)
    {
        $followed_searches_id = $this->dataRegistry['user-searches'];
        $this->ding2Context->drupalContext->visitPath('/list/' . $followed_searches_id);
        $found = $this->ding2Context->minkContext->getSession()->getPage()->find('css', 'a:contains("' . $arg1 . '") + form[id^="ding-list-remove-element"] #edit-submit');
        if (!$found) {
            throw new \Exception("Remove link doesn't exist");
        }
        $found->click();
    }

    /**
     * @Then I should not see :arg1 on followed searches
     */
    public function iShouldNotSeeOnFollowedSearches($arg1)
    {
        $followed_searches_id = $this->dataRegistry['user-searches'];
        $this->ding2Context->drupalContext->visitPath('/list/' . $followed_searches_id);
        $found = $this->ding2Context->minkContext->getSession()->getPage()->find('css', 'a[href^="/search/ting"]:contains("' . $arg1 . '")');
        if ($found && $found->getValue() == $arg1) {
            throw new \Exception("Link to author '$arg1' still exists.");
        }
    }

    /**
     * @When I add the author to authors I follow
     */
    public function iAddTheAuthorToAuthorsIFollow()
    {
        // Choose book facet.
        $this->ding2Context->minkContext->getSession()->getPage()->find('css', '.form-item-type-bog a')->click();
        $this->ding2Context->minkContext->getSession()->getPage()->find('css', '.form-item-creator-george-orwell a')->click();

        // Follow link to book.
        $res = $this->ding2Context->minkContext->assertElementContains('.search-result--heading-type', 'Bog');
        $found = $this->ding2Context->minkContext->getSession()->getPage()->find('css', '.search-result--heading-type:contains("Bog") + h2 > a');
        if (!$found) {
            throw new \Exception("Link to book doesn't exist");
        }
        $found->click();

        $follow_author_id = $this->dataRegistry['follow-author'];
        // Follow link to follow author.
        $found = $this->ding2Context->minkContext->getSession()->getPage()->find('css', 'a[href^="/dinglist/attach/follow_author/"]');
        if (!$found) {
            throw new \Exception("Link to follow author doesn't exist");
        }
        $found->click();
    }

    /**
     * @Then I should see :arg1 on the list of followed authors
     */
    public function iShouldSeeOnTheListOfFollowedAuthors($arg1)
    {
        $follow_author_id = $this->dataRegistry['follow-author'];
        $this->ding2Context->drupalContext->visitPath('/list/' . $follow_author_id);
        $link = '/search/ting/phrase.creator';
        $this->ding2Context->minkContext->assertElementContains('a[href^="' . $link . '"]', $arg1);
    }

    /**
     * @Given I have followed the author :arg1
     */
    public function iHaveFollowedTheAuthor($arg1)
    {
        // First add the author to the list.
        $this->iHaveSearchedFor($arg1);
        $this->iAddTheAuthorToAuthorsIFollow();

        $this->iShouldSeeOnTheListOfFollowedAuthors($arg1);
    }

    /**
     * @When I remove the author :arg1 from followed authors
     */
    public function iRemoveTheAuthorFromFollowedAuthors($arg1)
    {
        $follow_author_id = $this->dataRegistry['follow-author'];
        $this->ding2Context->drupalContext->visitPath('/list/' . $follow_author_id);
        $found = $this->ding2Context->minkContext->getSession()->getPage()->find('css', 'a:contains("' . $arg1 . '") + form[id^="ding-list-remove-element"] #edit-submit');
        if (!$found) {
            throw new \Exception("Remove link doesn't exist");
        }
        $found->click();
    }

    /**
     * @Then I should not see :arg1 on followed authors
     */
    public function iShouldNotSeeOnFollowedAuthors($arg1)
    {
        $follow_author_id = $this->dataRegistry['follow-author'];
        $this->ding2Context->drupalContext->visitPath('/list/' . $follow_author_id);
        $found = $this->ding2Context->minkContext->getSession()->getPage()->find('css', 'a[href^="/search/ting/phrase.creator"]');
        if ($found && $found->getValue() == $arg1) {
            throw new \Exception("Link to author '$arg1' still exists.");
        }
    }

    /**
     * @Given I am on my user consent page
     */
    public function iAmOnMyUserConsentPage()
    {
        $uid = $this->ding2Context->user->uid;
        $this->ding2Context->drupalContext->visitPath("/user/$uid/consent");
    }

    /**
     * @When I check the consent box
     */
    public function iCheckTheConsentBox()
    {
        $checked = $this->ding2Context->minkContext->getSession()->getPage()->find('css', '#edit-loan-history-store');
        $checked_value = $checked->getValue();
        if ($checked_value) {
            throw new \Exception("Consent checkbox is already checked.");
        }

        $checked->check();
        $this->ding2Context->minkContext->pressButton('edit-submit');
    }

    /**
     * @Then I should see that the consent box is checked
     */
    public function iShouldSeeThatTheConsentBoxIsChecked()
    {
        $this->iAmOnMyUserConsentPage();
        $checked = $this->ding2Context->minkContext->getSession()->getPage()->find('css', '#edit-loan-history-store');
        $checked_value = $checked->getValue();
        if (!$checked_value) {
            throw new \Exception("Consent checkbox is not checked.");
        }
    }

    /**
     * @When I uncheck the consent box
     */
    public function iUncheckTheConsentBox()
    {
        // First go to consent page, check consent box, and go to consent page.
        $this->iCheckTheConsentBox();
        $this->iAmOnMyUserConsentPage();

        $checked = $this->ding2Context->minkContext->getSession()->getPage()->find('css', '#edit-loan-history-store');
        $checked_value = $checked->getValue();
        if (!$checked_value) {
            throw new \Exception("Consent checkbox is not checked.");
        }

        $checked->uncheck();
        $this->ding2Context->minkContext->pressButton('edit-submit');
    }

    /**
     * @Then I should see that the consent box is not checked
     */
    public function iShouldSeeThatTheConsentBoxIsNotChecked()
    {
        $this->iAmOnMyUserConsentPage();
        $checked = $this->ding2Context->minkContext->getSession()->getPage()->find('css', '#edit-loan-history-store');
        $checked_value = $checked->getValue();
        if ($checked_value) {
            throw new \Exception("Consent checkbox is checked.");
        }
    }
}
