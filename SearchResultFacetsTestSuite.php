<?php

require_once(__DIR__ . '/autoload.php');
require_once(__DIR__ . '/bootstrap.php');

class SearchResultFacets extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstractedPage;
  protected $config;

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();
    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
  }

  /**
   * Test the search result facet filtering as anonymous.
   *
   * Assume pre-defined search result output with several item types.
   * Check each item type after a type facet is used.
   */
  public function testFacetBrowserAnonymous() {
    $this->open('/' . $this->config->getLocale());

    // Search for two specific items.
    $this->abstractedPage->userMakeSearch('"23685531" or "29275475"');

    // Check the pre-defined result.
    $results = array(
      'Bog:',
      'Ebog:',
    );

    for ($i = 0; $i < count($results); $i++) {
      $this->assertElementPresent('css=.pane-search-result .search-results li.search-result:eq(' . $i . ')');
      $this->assertElementContainsText('css=.search-result--heading-type:eq(' . $i . ')', $results[$i]);
    }

    // Two type facets should be available.
    $this->assertElementPresent('link=bog (1)');
    $this->assertElementPresent('link=ebog (1)');

    // Now filter, using a type facet.
    $this->click('link=bog (1)');
    $this->abstractedPage->waitForPage();

    // Check that there is no ebog type facet.
    $this->assertElementNotPresent('link=ebog (1)');
    // Check that there is no more a second item.
    $this->assertElementNotPresent('css=.pane-search-result .search-results li.search-result:eq(1)');

    // And the first one is of type Bog.
    $this->assertElementContainsText('css=.search-result--heading-type:eq(0)', 'Bog:');

    // Click the bog facet again, to uncheck.
    $this->click('link=bog (1)');
    $this->abstractedPage->waitForPage();

    // Try the year facet.
    $this->assertElementPresent('link=2001 (1)');
    $this->click('link=2001 (1)');
    $this->abstractedPage->waitForPage();

    // One single items has to have year 2001.
    $this->assertElementContainsText('css=.pane-search-result .search-results li.search-result:eq(0) .content:first', 'By Dorthe Nors (2001)');
  }

  /**
   * Test the search result facet filtering as logged in user.
   */
  public function testFacetBrowserLoggedIn() {
    $this->open('/' . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    $this->testFacetBrowserAnonymous();
  }
}
