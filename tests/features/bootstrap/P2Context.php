<?php

use Behat\Behat\Context\Context;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Behat\Tester\Exception\PendingException;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;
use Behat\Mink\Exception\UnsupportedDriverActionException;
use Page\CreateListPage;
use Page\ListPage;
use Page\SearchPage;
use Page\MyListsPage;

/**
 * Provides step definitions for interacting with P2.
 */
class P2Context implements Context, SnippetAcceptingContext
{
    /** @var Ding2Context */
    private $ding2Context;

    /**
     * @var array
     *   Save data within scenarios.
     */
    private $dataRegistry = array();

    function __construct(ListPage $listPage, CreateListPage $createListPage, SearchPage $searchPage, MyListsPage $myListsPage)
    {
        $this->listPage = $listPage;
        $this->createListPage = $createListPage;
        $this->searchPage = $searchPage;
        $this->myListsPage = $myListsPage;
    }

    /** @BeforeScenario */
    public function gatherContexts(BeforeScenarioScope $scope)
    {
        $environment = $scope->getEnvironment();

        $this->ding2Context = $environment->getContext('Ding2Context');
    }

    /**
     * Navigate to a page.
     *
     * @todo should only navigate if the path is different from the current.
     *
     * @param string $path
     *   The path to navigate to.
     */
    public function gotoPage($path)
    {
        $this->ding2Context->minkContext->visit($path);
    }

    /**
     * Go to the page that lists a users lists.
     *
     * Currently /user
     */
    public function gotoListListingPage()
    {
        $this->gotoPage($this->ding2Context->userPath());
    }

    /**
     * Go to a list page.
     *
     * @Given I am on the :title list page
     * @When I go to the :title list page
     *
     * @param string $name
     *   Name of list to goto.
     */
    public function gotoListPage($name)
    {
        $listId = $this->getListId($name);
        $this->listPage->open(['listId' => $listId]);
    }

    /**
     * Go to the search page.
     *
     * @Given I have searched for :arg1
     *
     * @todo should be moved to Ding2Context.
     *
     * @param string $string
     *   String to search for.
     */
    public function gotoSearchPage($string)
    {
        $this->gotoPage('/search/ting/' . urlencode($string));
    }

    /**
     * Select an item in a "More.." dropdown.
     *
     * @param string $text
     *   The link title to search for.
     * @param string $errorMessage
     *   Exception message if the link could not be found.
     * @throws \Exception
     */
    public function moreDropdownSelect($text, $errorMessage)
    {
        $page = $this->ding2Context->minkContext->getSession()->getPage();
        $button = $page->find('css', '.ding-list-add-button a');
        if (!$button) {
            throw new \Exception("Couldn't find more button");
        }

        try {
            // Scroll to and mouseover the button to trigger the dropdown.
            // Can't click an invisible link in a real browser.
            $this->ding2Context->scrollTo($button);

            $button->mouseOver();
        } catch (UnsupportedDriverActionException $e) {
            // Carry on if the driver doesn't support it.
        }

        // Sadly the links isn't related to the button in any way.
        $link = $page->find('css', 'a:contains("' . $text . '")');

        if (!$link) {
            throw new \Exception($errorMessage);
        }
        $this->ding2Context->scrollTo($link);
        $link->click();
    }

    /**
     * Get the ID of the named list.
     *
     * @param string $list
     *   List name.
     *
     * @return string
     *   The list id.
     * @throws \Exception
     */
    public function getListId($list)
    {
        // Predefined lists.
        $specialLists = [
            'Bøger jeg har læst',
            'Forfattere jeg følger',
            'Huskeliste',
            'Lister jeg følger',
            'Materialer jeg har bedømt',
            'Mine interesser',
            'Søgninger jeg følger',
            'Tidligere lån',
        ];

        $listName = 'list:' . $list;
        if (!isset($this->dataRegistry[$listName]) &&
            in_array($list, $specialLists)) {
            // Try to find list id by scanning user page.
            $listId = $this->myListsPage->open()->getListIdOf($list);
            $this->dataRegistry[$listName] = $listId;
        }

        if (!isset($this->dataRegistry[$listName])) {
            throw new \Exception("List id for list $list doesn't exist");
        }
        $listId = $this->dataRegistry[$listName];
        if (!$listId) {
            throw new \Exception("List id for list $list seems to be public");
        }

        return $listId;
    }

    /**
     * Add current material to the list containing the given string.
     *
     * @param string $title
     *   List title.
     */
    public function addCurrentMaterialToList($title)
    {
        $this->moreDropdownSelect($title, "Couldn't find button to add material to list");
    }

    /**
     * Make list shared.
     *
     * @param string $title
     *   Title of list
     * @throws \Behat\Mink\Exception\ElementNotFoundException
     * @throws \Exception
     */
    public function makeListShared($title) {
        $page = $this->ding2Context->minkContext->getSession()->getPage();
        $this->gotoListPage($title);

        // Click share list.
        $this->iGoToTheShareLink();

        $found = $page->find('css',
          '#ding-list-list-permissions-form #edit-status');
        if (!$found) {
            throw new \Exception("Couldn't find dropdown menu for sharing list");
        }
        $found->selectOption('shared');
        // Wait for list to be shared.
        $page->waitFor(5, function ($page) {
            return $page->find('css',
              '#status-description:contains("Your list is now shared")');
        });
    }

    /**
     * @Then I should see a link to the create list page
     */
    public function iShouldSeeALinkToTheCreateListPage()
    {
        $this->ding2Context->iSeeALinkTo('/list/create');
    }

    /**
     * @Then the list for followed searches exists
     */
    public function theFollowedSearchesListExists()
    {
        $this->theListExists('Søgninger jeg følger');
    }

    /**
     * @When I add the search to followed searches
     */
    public function iAddTheSearchToFollowedSearches()
    {
        $this->moreDropdownSelect('Tilføj til Søgninger jeg følger', "Couldn't find button to add search to list");
    }

    /**
     * @param string $href
     *   The actual link to search for.
     * @param $errorMessage
     *   Exception message if the link could not be found.
     * @throws \Exception
     */
    public function moreDropdownSelectByLink($href, $errorMessage)
    {
        $page = $this->ding2Context->minkContext->getSession()->getPage();
        $page->waitFor(5, function ($page) {
            return $page->find('css', '.ding-list-add-button a');
        });
        $button = $page->find('css', '.ding-list-add-button a');
        if (!$button) {
            throw new \Exception("Couldn't find more button");
        }

        try {
            // Mouseover the button to trigger the dropdown. Can't click an
            // invisible link in a real browser.
            $this->ding2Context->scrollTo($button);
            $button->mouseOver();
        } catch (UnsupportedDriverActionException $e) {
            // Carry on if the driver doesn't support it.
        }

        // Sadly the links isn't related to the button in any way.
        $link = $page->find('css', 'a[href^="' . $href . '"]');
        if (!$link) {
            throw new \Exception($errorMessage);
        }
        $this->ding2Context->scrollTo($link);
        $link->click();
    }

    /**
     * @Then I should see :arg1 on followed searches
     */
    public function iShouldSeeOnFollowedSearches($arg1)
    {
        $this->gotoListPage('Søgninger jeg følger');
        $this->ding2Context->minkContext->assertElementContainsText('.ding-type-ding-list-element .content a', $arg1);
    }

    /**
     * @Given I have followed the search :arg1
     */
    public function iHaveFollowedTheSearch($arg1)
    {
        // Perform search.
        $this->gotoSearchPage($arg1);
        $this->iAddTheSearchToFollowedSearches();
        $this->iShouldSeeOnFollowedSearches($arg1);
    }

    /**
     * @When I remove the search :arg1 from followed searches
     */
    public function iRemoveTheSearchFromFollowedSearches($arg1)
    {
        $this->gotoListPage('Søgninger jeg følger');
        $listId = $this->getListId('Søgninger jeg følger');
        $found = $this->ding2Context->minkContext->getSession()->getPage()
            ->find('css', 'form[action="/list/' . $listId . '"] #edit-submit');
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
        $this->gotoListPage('Søgninger jeg følger');
        $found = $this->ding2Context->minkContext->getSession()->getPage()
            ->find('css', 'a[href^="/search/ting"]:contains("' . $arg1 . '")');
        if ($found && $found->getValue() == $arg1) {
            throw new \Exception("Link to author '$arg1' still exists.");
        }
    }

    /**
     * @Given I am on a material of :author
     */
    public function iAmOnAMaterialOf($author)
    {
        $page = $this->ding2Context->minkContext->getSession()->getPage();
        $this->gotoSearchPage($author);

        $found = $page->find('css', '#edit-creator input[value="' . strtolower($author) . '"]');
        if (!$found) {
            throw new Exception("Couldn't filter for author $author");
        }
        $this->ding2Context->scrollTo($found);
        $found->check();
    }

    /**
     * @When I add the author :author to authors I follow
     */
    public function iAddTheAuthorToAuthorsIFollow($author)
    {
        // Choose book facet.
        $found = $this->ding2Context->minkContext->getSession()->getPage()
            ->find('css', '#ding-facetbrowser-form .form-item-type-bog input');
        if (!$found) {
            throw new \Exception('Book facet not found');
        }
        $this->ding2Context->scrollTo($found);
        $found->check();

        $authorLowerCase = strtolower(preg_replace(array('/\s/', '/\./'), array('-', ''), $author));
        $found = $this->ding2Context->minkContext->getSession()->getPage()
            ->find('css', '#edit-creator-' . $authorLowerCase);
        if (!$found) {
            throw new \Exception('Creator facet not found');
        }
        $this->ding2Context->scrollTo($found);
        $found->check();

        // Follow link to book.
        $this->ding2Context->minkContext->assertElementContains('.search-result--heading-type', 'Bog');
        $this->iChooseTheFirstSearchResult();

        // Follow link to follow author.
        $this->moreDropdownSelectByLink('/dinglist/attach/follow_author/', "Couldn't find follow author link");
    }

    /**
     * @Then I should see :author on the list of followed authors
     */
    public function iShouldSeeOnTheListOfFollowedAuthors($author)
    {
        $page = $this->ding2Context->minkContext->getSession()->getPage();
        $this->gotoListPage('Forfattere jeg følger');
        $link = '/search/ting/phrase.creator';
        $page->waitFor(10000, function ($page) use ($link) {
            return $page->find('css', 'a[href^="' . $link . '"]');
        });
        $this->ding2Context->minkContext->assertElementContains('a[href^="' . $link . '"]', $author);
    }

    /**
     * @Given I have followed the author :author
     */
    public function iHaveFollowedTheAuthor($author)
    {
        // First add the author to the list.
        $this->gotoSearchPage($author);
        $this->iAddTheAuthorToAuthorsIFollow($author);

        $this->iShouldSeeOnTheListOfFollowedAuthors($author);
    }

    /**
     * @When I remove the author :arg1 from followed authors
     */
    public function iRemoveTheAuthorFromFollowedAuthors($arg1)
    {
        $this->gotoListPage('Forfattere jeg følger');
        $listId = $this->getListId('Forfattere jeg følger');
        $found = $this->ding2Context->minkContext->getSession()->getPage()
            ->find('css', 'form[action="/list/' . $listId . '"] #edit-submit');
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
        $this->gotoListPage('Forfattere jeg følger');
        $found = $this->ding2Context->minkContext->getSession()->getPage()
            ->find('css', 'a[href^="/search/ting/phrase.creator"]');
        if ($found && $found->getValue() == $arg1) {
            throw new \Exception("Link to author '$arg1' still exists.");
        }
    }

    /**
     * @Given I am on my user consent page
     */
    public function iAmOnMyUserConsentPage()
    {
        if (empty($this->ding2Context->user) || empty($this->ding2Context->user->uid)) {
            throw new \Exception("User doesn't exist");
        }
        $this->gotoPage($this->ding2Context->userPath() . "/consent");
        $this->ding2Context->waitForPage();
    }

    /**
     * @When I check the consent box
     */
    public function iCheckTheConsentBox()
    {
        $checked = $this->ding2Context->minkContext->getSession()->getPage()->find('css', '#edit-loan-history-store');
        if (!$checked) {
            throw new \Exception("Couldn't find consent check box");
        }
        if ($checked->isChecked()) {
            throw new \Exception("Consent checkbox is already checked.");
        }

        $checked->check();
        $this->ding2Context->minkContext->pressButton('edit-submit');
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
        if (!$checked) {
            throw new \Exception("Couldn't find consent check box");
        }
        $this->ding2Context->waitForPage();
        if (!$checked->isChecked()) {
            throw new \Exception("Consent checkbox is not checked.");
        }

        $checked->uncheck();
        $this->ding2Context->minkContext->pressButton('edit-submit');
    }

    /**
     * @Given I have given consent to save my loan history
     */
    public function iHaveGivenConsentToSaveMyLoanHistory()
    {
        $this->iAmOnMyUserConsentPage();
        $this->iCheckTheConsentBox();
    }

    /**
     * @Then I should see the list of previous loans
     */
    public function iShouldSeeTheListOfPreviousLoans()
    {
        $this->gotoListListingPage();
        $listName = 'Tidligere lån';
        $this->ding2Context->minkContext->assertElementOnPage('.signature-label:contains("' . $listName . '")');
        $this->gotoListPage($listName);
    }

    /**
     * @Given I have withdrawn consent to save loan history
     */
    public function iHaveWithdrawnConsentToSaveLoanHistory()
    {
        // Uncheck the 'consent to save loan history' checkbox.
        $this->iAmOnMyUserConsentPage();
        $this->iUncheckTheConsentBox();
    }

    /**
     * @Then I should not see the list of previous loans
     */
    public function iShouldNotSeeTheListOfPreviousLoans()
    {
        $this->gotoListListingPage();
        $listName = 'Tidligere lån';
        $this->ding2Context->minkContext->assertElementNotOnPage('.signature-label:contains("' . $listName . '")');

        // Check that the list doesn't exist.
        try {
            $this->gotoListPage($listName);
            // If no exception is raised, the list still exists.
            throw new Exception("The list '$listName' still exists!");
        } catch (Exception $e) {
            // Do nothing, swallow exception.
        }
    }

    /**
     * @Given I am on my create list page
     */
    public function iAmOnMyCreateListPage()
    {
        $this->createListPage->open();
    }

    /**
     * @When I create a new list :title with description :description
     * @When fill in :title as list title
     */
    public function iCreateANewListWithDescription($title, $description = '')
    {
        $this->createListPage->verifyCurrentPage();
        $createForm = $this->createListPage->getElement('Create list form');
        $listPage = $createForm->createList($title, $description);
        expect($listPage->isListPageFor($title))->shouldBe(true);
        $this->dataRegistry['list:' . $title] = $listPage->getListId();
    }

    /**
     * @Then I should be on the :arg1 list page
     */
    public function iShouldBeOnTheListPage($arg1)
    {
        $this->listPage->verifyCurrentPage();
    }

    /**
     * @Given I have created a list :title
     */
    public function iHaveCreatedAList($title)
    {
        $this->createListPage->open(['uid' => $this->ding2Context->userUid()]);
        $this->iCreateANewListWithDescription($title);
    }

    /**
     * @When I go to the share link
     */
    public function iGoToTheShareLink()
    {
        $page = $this->ding2Context->minkContext->getSession()->getPage();
        $found = $page->find('css', '.share .menu-item');
        if (!$found) {
            throw new \Exception("Couldn't find link to share list");
        }
        $found->click();

        $page->waitFor(5, function ($page) {
            return $page->find('css', '#edit-status option');
        });
    }

    /**
     * @When I make the list :title public
     * @Given I have made the list :title public
     */
    public function iMakeTheListPublic($title)
    {
        $page = $this->ding2Context->minkContext->getSession()->getPage();
        // Click on list link.
        $this->gotoListPage($title);

        // Click share list.
        $this->iGoToTheShareLink();
        $this->ding2Context->waitForPage();

        $found = $page->find('css', '#ding-list-list-permissions-form #edit-status');
        if (!$found) {
            throw new \Exception("Couldn't find dropdown menu for sharing list");
        }

        $found->selectOption('public');
        $page->waitFor(10000, function ($page) {
            return $page->find('css', '#status-description:contains("Your list is now public")');
        });

        $form = $this->ding2Context->minkContext->getSession()->getPage()
            ->find('css', '#ding-list-list-permissions-form');
        $form->submit();
    }

    /**
     * @Then I should see that the list :title is marked as public
     */
    public function iShouldSeeThatTheListIsMarkedAsPublic($title)
    {
        $this->gotoListPage($title);
        $this->iGoToTheShareLink();
        $this->ding2Context->waitForPage();

        $found_select = $this->ding2Context->minkContext->getSession()->getPage()
            ->find('css', '#ding-list-list-permissions-form #edit-status');
        if (!$found_select) {
            throw new \Exception("Couldn't find drop down menu for sharing list");
        }
        $checked = $found_select->getValue();
        if (!$checked || $checked != 'public') {
            throw new \Exception("List is not set to public shared");
        }
    }

    /**
     * @When I go to the public lists page
     */
    public function iGoToThePublicListsPage()
    {
        $this->gotoPage('/public-lists');
    }

    /**
     * @Then I should see the public list :title
     */
    public function iShouldSeeThePublicList($title)
    {
        $listId = $this->getListId($title);

        try {
            $this->ding2Context->minkContext->assertElementContainsText('a[href^="/list/' . $listId . '"]', $title);
            return;
        } catch (Exception $e) {
            $nrPages = 1;
            // Get number of pages from pager in the bottom.
            $lastPage = $this->ding2Context->minkContext->getSession()->getPage()
                ->find('css', '.pager-last a');
            if (!$lastPage) {
                throw new Exception("Couldn't find pager");
            }
            $lastPageHref = $lastPage->getAttribute('href');
            if ($lastPageHref) {
                $match = array();
                if (preg_match('{/public-lists\?page=(\d+)}', $lastPageHref, $match)) {
                    $nrPages = $match[1];
                }
            }

            // Search for list on all pages.
            for ($i = 0; $i <= $nrPages; $i++) {
                if ($i) {
                    $this->gotoPage('/public-lists?page=' . $i);
                }

                $found = $this->ding2Context->minkContext->getSession()->getPage()
                    ->find('css', 'a[href^="/list/' . $listId . '"]');
                if ($found) {
                    $this->ding2Context->minkContext->assertElementContainsText('a[href^="/list/' . $listId . '"]', $title);

                    // We return now, cause we have found the element.
                    return;
                }
            }
        }
        // If we get here, the element hasn't been found.
        throw new Exception("List '$title' couldn't be found on public lists");
    }

    /**
     * @Given I have a link to a public list with the title :title
     */
    public function iHaveALinkToAPublicListWithTheTitle($title)
    {
        $this->iHaveCreatedAList($title);
        $this->iMakeTheListPublic($title);

        // Log in as different user.
        $this->ding2Context->iAmLoggedInAsALibraryUser();
    }

    /**
     * @When I follow the list :title
     */
    public function iFollowTheList($title)
    {
        $page = $this->ding2Context->minkContext->getSession()->getPage();
        $this->gotoListPage($title);

        $listId = $this->getListId($title);
        $foundButton = $this->ding2Context->minkContext->getSession()->getPage()
            ->find('css', 'form[action="/list/' . $listId . '"] #edit-submit'); //input[type="submit"]');
        if (!$foundButton) {
            throw new \Exception("Couldn't find follow list button");
        }

        $foundButton->click();
    }

    /**
     * @Then I should see the list :title on lists I follow
     */
    public function iShouldSeeTheListOnListsIFollow($title)
    {
        $this->gotoListPage('Lister jeg følger');

        $listId = $this->getListId($title);
        $this->ding2Context->minkContext->assertElementContainsText('a[href="/list/' . $listId . '"]', $title);
    }

    /**
     * @Given I am following a public list with the title :title
     */
    public function iAmFollowingAPublicListWithTheTitle($title)
    {
        // Make sure to follow a public list.
        $this->iHaveALinkToAPublicListWithTheTitle($title);
        $this->iFollowTheList($title);
        $this->iShouldSeeTheListOnListsIFollow($title);
    }

    /**
     * @When I unfollow the list with the title :title
     */
    public function iUnfollowTheListWithTheTitle($title)
    {
        $this->gotoListPage('Lister jeg følger');
        $listId = $this->getListId($title);
        // Find link to followed list.
        $found = $this->ding2Context->minkContext->getSession()->getPage()
            ->find('css', '.ding-type-ding-list a[href="/list/' . $listId . '"]');
        if (!$found) {
            throw new \Exception("Couldn't find list '$title' on followed lists");
        }
        $this->ding2Context->minkContext
            ->assertElementContainsText('.ding-type-ding-list a[href="/list/' . $listId . '"]', $title);

        $deleteLink = $this->ding2Context->minkContext->getSession()->getPage()
            ->find('css', '#ding-list-remove-element-ding-list-' . $listId . '-form #edit-submit');
        if (!$deleteLink) {
            throw new \Exception("Couldn't find remove from list button");
        }
        $this->ding2Context->scrollTo($deleteLink);
        $deleteLink->click();
    }

    /**
     * @Then I should not see the list :title on lists I follow
     */
    public function iShouldNotSeeTheListOnListsIFollow($title)
    {
        $listId = $this->getListId($title);
        $this->gotoListListingPage();
        $found_list = $this->ding2Context->minkContext->getSession()->getPage()
            ->find('css', '.ding-user-lists .lists-list a');
        if (!$found_list) {
            throw new \Exception("Couldn't find link to list of followed lists");
        }
        $this->ding2Context->scrollTo($found_list);
        $found_list->click();

        $this->ding2Context->minkContext
            ->assertElementNotOnPage('.ding-type-ding-list a[href="/list/' . $listId . '"]');
    }

    /**
     * @Given I have created a public list :title
     */
    public function iHaveCreatedAPublicList($title)
    {
        $this->iHaveCreatedAList($title);
        $this->iMakeTheListPublic($title);
        $this->iShouldSeeThatTheListIsMarkedAsPublic($title);
    }

    /**
     * @When I make the list :title read shared
     * @When I make the list :title write shared
     */
    public function iMakeTheListReadShared($title)
    {
        $page = $this->ding2Context->minkContext->getSession()->getPage();
        // Make list shared.
        $this->makeListShared($title);

        // Select view mode.
        $found = $page->find('css', '#edit-sharer #edit-permission');
        if (!$found) {
            throw new \Exception("Couldn't find dropdown menu for sharing permissions");
        }
        $found->selectOption('view');
        $editView = $page->find('css', '#edit-view');
        $editView->focus();

        $foundLink = $page->find('css', '#edit-sharer #edit-view');
        if (!$foundLink) {
            throw new Exception("Couldn't find sharing link with token");
        }
        $link = $foundLink->getValue();
        $this->dataRegistry['read link:' . $title] = $link;

        $found->selectOption('edit');
        $editView = $page->find('css', '#edit-view');
        $editView->focus();

        $foundLink = $page->find('css', '#edit-sharer #edit-view');
        if (!$foundLink) {
            throw new Exception("Couldn't find sharing link with token");
        }
        $link = $foundLink->getValue();
        $this->dataRegistry['write link:' . $title] = $link;
    }

    /**
     * @Then I should be able to see the list :title with the :access link
     */
    public function iShouldBeAbleToSeeTheListWithTheLink($title, $access)
    {
        $page = $this->ding2Context->minkContext->getSession()->getPage();
        // Get link to list.
        $link = $this->dataRegistry[strtolower($access) . ' link:' . $title];

        // Go to list.
        $this->gotoPage($link);

        $found = $page->find('css', '.pane-list-followers .pane-title');
        if (!$found) {
            throw new Exception("Couldn't find shared list");
        }
        $listTitle = $found->getText();
        if ($listTitle != $title) {
            throw new Exception("Found list '$listTitle' is not the same as '$title'");
        }

        $this->iFollowTheList($title);
    }

    /**
     * @Given I am on the material :material
     */
    public function iAmOnTheMaterial($material)
    {
        $this->searchPage->search($material);
        $this->searchPage->gotoFirstResultNamed($material);
    }

    /**
     * @When I add material :material to the list :title
     */
    public function iAddMaterialToTheList($material, $title)
    {
        $this->iAmOnTheMaterial($material);
        $this->moreDropdownSelect($title, "Couldn't find button to add material to list");
    }

    /**
     * @When I add it to a new list
     */
    public function iAddItToANewList()
    {
        $this->moreDropdownSelect('Tilføj til ny liste', "Couldn't find button to add material to a new list");
    }

    /**
     * @Given I have added the material :material to the list :list
     */
    public function iHaveAddedTheMaterialToTheList($material, $list)
    {
        $this->iAddMaterialToTheList($material, $list);
        $this->iShouldSeeTheMaterialOnTheList($material, $list);
    }

    /**
     * @Then I should get a confirmation that I added the material to :list list
     */
    public function iShouldGetAConfirmationThatIAddedTheMaterialToList($list)
    {
        // @todo Should use a more general page.
        $this->listPage->waitForPopup();
        $popup = $this->listPage->getElement('Popup');
        expect($popup->getContentText())->shouldBe('Tilføjet til ' . $list);
    }

    /**
     * @Then I should see the material :material on the list :title
     */
    public function iShouldSeeTheMaterialOnTheList($material, $title)
    {
        $listId = $this->myListsPage->open()->getListIdOf($title);
        $this->listPage->open(['listId' => $listId]);
        expect($this->listPage->hasMaterial($material))->shouldBe(true);
    }

    /**
     * @Then I should not see the material :material on the list :title
     */
    public function iShouldNotSeeTheMaterialOnTheList($material, $title)
    {
        try {
            $this->iShouldSeeTheMaterialOnTheList($material, $title);
            throw new Exception('Material "' . $material . '" not removed from "' . $title . '" list');
        } catch (Exception $e) {
            // Not found, swallow exception.
        }
    }

    /**
     * @When I remove the material :material from the list
     */
    public function iRemoveTheMaterialFromTheList($material)
    {
        $this->listPage->removeMaterial($material);
    }

    /**
     * @Then I should see the material :material on the public list :title
     */
    public function iShouldSeeTheMaterialOnThePublicList($material, $title)
    {
        $this->iShouldSeeTheMaterialOnTheList($material, $title);

        // Log in as different user and check the list again.
        $listId = $this->getListId($title);
        $this->ding2Context->iAmLoggedInAsALibraryUser();
        $this->gotoPage("/list/$listId");
        $this->ding2Context->minkContext->assertElementContainsText('.ting-object', $material);
    }

    /**
     * @Then I should not see the material :material on the public list :title
     */
    public function iShouldNotSeeTheMaterialOnThePublicList($material, $title)
    {
        $this->gotoListPage($title);
        $this->ding2Context->minkContext->assertElementNotContainsText('.ting-object', $material);
    }

    /**
     * @Given I am on a material page that has the subject science fiction
     */
    public function iAmOnAMaterialPageThatHasTheSubject()
    {
        $material = '870970-basis%3A08983127';
        $this->gotoPage('/ting/object/' . $material);
    }

    /**
     * @Then I should see the tag :tag on the material
     * @Then I should see the subject :tag on the material
     */
    public function iShouldSeeTheTagOnTheMaterial($tag)
    {
        $button = $this->ding2Context->minkContext->getSession()->getPage()
          ->find('css', '.subjects .subject:contains("' . $tag . '")');
    }

    /**
     * @Given I have chosen a book material :material with the tag :tag
     * @Given I have chosen a book material :material with the subject :tag
     */
    public function iHaveChosenABookMaterialWithTheTag($material, $tag)
    {
        $this->gotoPage('/ting/object/' . $material);
        $this->ding2Context->minkContext->assertElementOnPage('.subject:contains("' . $tag . '")');
    }

    /**
     * @When I choose the first search result
     */
    public function iChooseTheFirstSearchResult()
    {
        $found = $this->ding2Context->minkContext->getSession()->getPage()
            ->find('css', '.search-results .search-result:nth-child(1) .ting-object .heading a');
        if (!$found) {
            throw new Exception("Couldn't find search result.");
        }
        $this->ding2Context->scrollTo($found);
        $found->click();
    }

    /**
     * @When I follow the tag :tag
     * @When I follow the subject :tag
     */
    public function iFollowTheTag($tag)
    {
        $this->moreDropdownSelect('Følg emnet ' . $tag, "Couldn't find tag '$tag' on material");
    }

    /**
     * @Then I should see the tag :tag on my list :list
     * @Then I should see the subject :tag on my list :list
     */
    public function iShouldSeeTheTagOnMyList($tag, $list)
    {
        $this->gotoListPage($list);
        $this->ding2Context->minkContext->assertElementContainsText('.vocabulary-ding-content-tags a', $tag);
    }

    /**
     * @Then I should see the subject :tag on the list of my interests
     */
    public function iShouldSeeTheSubjectOnTheListOfMyInterests($tag)
    {
        $this->iShouldSeeTheTagOnMyList($tag, 'Mine interesser');
    }

    /**
     * @Given I am following the tag :tag
     * @Given I am following the subject :tag
     */
    public function iAmFollowingTheTag($tag)
    {
        // Some material with the subject "orkideer".
        $material = "870970-basis%3A45614654";
        $this->gotoPage('/ting/collection/' . $material);
        $this->iFollowTheTag($tag);
        $this->iShouldSeeTheTagOnMyList($tag, 'Mine interesser');
    }

    /**
     * @When I unfollow the tag :tag
     * @When I unfollow the subject :tag
     */
    public function iUnfollowTheTag($tag)
    {
        $this->gotoListPage('Mine interesser');

        $found = $this->ding2Context->minkContext->getSession()->getPage()
            ->find('css', 'a[href^="/tags/"]:contains("' . $tag . '")');
        if (!$found) {
            throw new Exception("Can't unfollow tag '$tag' when it's not being followed");
        }
        $deleteButton = $found->getParent()->getParent()->getParent()
            ->find('css', '.close-btn');
        if (!$deleteButton) {
            throw new Exception("Couldn't find remove from list button");
        }
        $deleteButton->click();
    }

    /**
     * @Then I should not see the tag :tag on the list of my interests
     * @Then I should not see the subject :tag on the list of my interests
     */
    public function iShouldNotSeeTheTagOnMyList($tag)
    {
        $list = 'Mine interesser';
        $this->gotoListPage($list);
        $found = $this->ding2Context->minkContext->getSession()->getPage()
            ->find('css', '.vocabulary-ding-content-tags a:contains("' . $tag . '")');
        if ($found) {
            throw new Exception("Shouldn't find tag '$tag', but it is being followed");
        }
    }

    /**
     * @Given the list :name exists
     */
    public function theListExists($name)
    {
        // Rely on getListId throwing an error for unknown lists.
        $this->getListId($name);
    }

    /**
     * @Given the list of my interests exists
     */
    public function theListOfMyInterestsExists()
    {
        $this->theListExists('Mine interesser');
    }

    /**
     * @Given the list of rated materials exists
     */
    public function theListOfRatedMaterialsExists()
    {
        $this->theListExists('Materialer jeg har bedømt');
    }

    /**
     * @Given the list of followed authors exists
     */
    public function theListOfFollowedAuthorsExists()
    {
        $this->theListExists('Forfattere jeg følger');
    }

    /**
     * @Given I have searched for :search and the tag :tag
     */
    public function iHaveSearchedForAndTheTag($search, $tag)
    {
        $this->gotoSearchPage("$search $tag");

        $found = $this->ding2Context->minkContext->getSession()->getPage()
            ->find('css', '#edit-subject input[value="' . $tag . '"]');
        if (!$found) {
            throw new Exception("Couldn't filter for tag $tag");
        }
        $this->ding2Context->scrollTo($found);

        $found->check();
    }

    /**
     * @When I log in as a different user
     */
    public function iLogInAsADifferentUser()
    {
        $this->ding2Context->iAmLoggedInAsALibraryUser();
    }

    /**
     * @Then I should not be able to add material :materialTitle to the list :title
     */
    public function iShouldNotBeAbleToAddMaterialToTheList($materialTitle, $title)
    {
        $material = $this->titleToMaterial($materialTitle);
        $this->gotoPage('/ting/object/' . $material);

        // Check that the link for add element to shared list does not exist.
        $listId = $this->getListId($title);
        $this->ding2Context->minkContext->assertElementNotOnPage(
            '.buttons li a[href^="/dinglist/attach/ting_object/' . $listId . '/"]'
        );
    }

    /**
     * @Then I should be able to add material :materialTitle to the list :title as a different user
     */
    public function iShouldBeAbleToAddMaterialToTheListAsADifferentUser($materialTitle, $title)
    {
        $material = $this->titleToMaterial($materialTitle);
        $this->gotoPage('/ting/object/' . $material);

        // Check that the link for add element to shared list exists.
        $listId = $this->getListId($title);
        $this->ding2Context->minkContext->assertElementOnPage(
          '.buttons li a[href="/dinglist/attach/ting_object/' . $listId . '/' . $material . '"]'
        );

        // If the add link is there, test that the user can add material.
        $this->moreDropdownSelectByLink(
          '/dinglist/attach/ting_object/' . $listId,
          "Couldn't find link to add material to the list '$title'"
        );

        // Check that the material is on the list.
        $this->gotoListPage($title);
        $this->ding2Context->minkContext->assertElementOnPage('.a[href^="/ting/collection/' . $material . '"]');
    }

    /**
     * @Given I have searched for :search with the material name :material
     */
    public function iHaveSearchedForWithTheMaterialName($search, $material)
    {
        $this->gotoSearchPage($search);
        $this->ding2Context->waitForPage();
        $this->ding2Context->minkContext->assertElementOnPage('a[href="/ting/collection/' . $material . '"]');
    }

    /**
     * @When I rate the material :title with :stars stars
     * @When I change the rating of material :title to :stars stars
     */
    public function iRateTheMaterialWithStars($title, $stars)
    {
        $material = $this->titleToMaterial($title);
        $page = $this->ding2Context->minkContext->getSession()->getPage();

        $found = $page->find('css', '.ding-rating[data-ding-entity-rating-path^="' . urldecode($material) . '/"]');
        if (!$found) {
            throw new Exception("Couldn't find material '$material'");
        }
        $star = $page->find(
            'css',
            '.ding-rating[data-ding-entity-rating-path^="' . urldecode($material) . '/"]' .
            ' .star:nth-child(' . $stars . ')'
        );
        if (!$star) {
            throw new Exception("Couldn't find star");
        }
        $this->ding2Context->scrollTo($star);
        $star->click();

        // Wait for Ajax to finish.
        $page->waitFor(5, function ($page) {
            return $page->find('css', '.ding-entity-rating-respons');
        });
        $this->ding2Context->minkContext
            ->assertElementContainsText('.ding-entity-rating-respons', 'Tak for din bedømmelse');
    }

    /**
     * Translate some defined titles to materials.
     *
     * @param $title
     * @return null|string
     */
    public function titleToMaterial($title) {
        $material = NULL;
        switch($title) {
            case 'The riddle of Nostradamus':
                $material = '870970-basis%3A42065897';
                break;

            case 'Asimov on physics':
                $material = '870970-basis%3A01860410';
                break;

            case "Debrett's etiquette and modern manners":
                $material = '870970-basis%3A25893271';
                break;

            case 'Essential guide to back garden self-sufficiency':
                $material = '870970-basis%3A06130992';
                break;

            case 'The raven':
                $material = "870970-basis%3A07838573";
                break;

            case 'The price':
                $material = '870970-basis%3A41249463';
                break;

            default:
                $material = '';
        }
        return $material;
    }

    /**
     * @Given I have rated the material :title with :stars stars
     */
    public function iHaveRatedTheMaterialWithStars($title, $stars)
    {
        $material = $this->titleToMaterial($title);
        $this->gotoPage('/ting/object/' . $material);
        $this->iRateTheMaterialWithStars($title, $stars);
    }

    /**
     * @When I go to the list of rated materials
     */
    public function iGoToTheListOfRatedMaterials()
    {
        $this->gotoListPage('Materialer jeg har bedømt');
    }

    /**
     * @Then I should see that the material :title is marked with :stars stars
     */
    public function iShouldSeeThatTheMaterialIsMarkedWithStars($title, $stars)
    {
        $material = $this->titleToMaterial($title);
        $this->ding2Context->minkContext
            ->assertElementOnPage('.ding-entity-rating[data-ding-entity-rating-path^="' . urldecode($material) . '/"]');
        $this->ding2Context->minkContext->assertNumElements(
            $stars,
            '.ding-entity-rating[data-ding-entity-rating-path^="' . urldecode($material) . '/"]' .
            ' .star.submitted'
        );
    }

    /**
     * @When there are :num new materials for the author :author
     */
    public function thereAreNewMaterialsForTheAuthor($num, $author)
    {
        // We want the element after the first $num elements.
        $nth = $num + 1;

        // Update notifications for user and find message id.
        $uid = $this->ding2Context->drupalContext->user->uid;
        ding_message_update_users(array($uid), false);
        $query = db_select('message', 'm');
        $query->addField('m', 'mid');
        $query->condition('m.uid', $uid);
        $record = $query->execute()->fetchAssoc();
        $mid = $record['mid'];

        // Go to the author search to reset notifications.
        $this->gotoListPage('Forfattere jeg følger');
        $this->ding2Context->minkContext->clickLink($author);
        $this->ding2Context->waitForPage();

        // Perform search and choose {$nth}th element's material id.
        $page = $this->ding2Context->minkContext->getSession()->getPage();
        $this->ding2Context->minkContext
            ->assertElementOnPage(".search-results .list .search-result:nth-child($nth) .ting-object");
        $found = $page->find('css', ".search-results .list .search-result:nth-child($nth) .ting-object");
        $materialId = $found->getAttribute('data-ting-object-id');

        // Update message's last element to be previously found material id.
        $message = message_load($mid);
        $wrapper = entity_metadata_wrapper('message', $message);
        $wrapper->field_last_element->set($materialId);
        $wrapper->save();
        // And update notifications.
        ding_message_update_users(array($uid), false);
    }

    /**
     * @Then I should see that there are :num new materials on the notifications list on the notifications top menu
     */
    public function iShouldSeeThatThereAreNewMaterialsOnTheNotificationsListOnTheNotificationsTopMenu($num)
    {
        $page = $this->ding2Context->minkContext->getSession()->getPage();
        $this->ding2Context->minkContext->visitPath('/user');

        $page->waitFor(10000, function ($page) use ($num) {
            return $page->find('css', '.notifications-count:not(:contains("0"))');
        });

        $found = $page->find('css', '.notifications-count');
        $notifications = $found->getText();
        if ($notifications != $num) {
            throw new Exception("There should be $num notifications in the top menu, but I only see $notifications");
        }
    }

    /**
     * @Then I should see that there are :num new materials on the list of authors I follow
     */
    public function iShouldSeeThatThereAreNewMaterialsOnTheListOfAuthorsIFollow($num)
    {
        $page = $this->ding2Context->minkContext->getSession()->getPage();
        $this->ding2Context->minkContext->assertNumElements(2, '.follow-author a');
        $found = $page->find('css', '.follow-author .label');
        if (!$found) {
            throw new Exception("Couldn't find number of notifications on the followed authors list");
        }
        $foundNotifications = $found->getText();
        if ($foundNotifications != $num) {
            throw new Exception("There should be $num notifications on the author list, but I only see $foundNotifications");
        }
    }
}
