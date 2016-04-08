<?php

class SearchResultTest extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstractedPage;
  protected $config;

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();
    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
  }

  /**
   * Test search functionality as anonymous.
   *
   * Check when filled and empty search is made.
   */
  public function testSearchPageAnonymous() {
    $this->open('/' . $this->config->getLocale());
    $this->abstractedPage->waitForPage();

    // Check for no results page.
    $this->abstractedPage->userMakeSearch('');
    $this->assertElementContainsText('css=div.messages.error', 'Please enter some keywords.');

    // Check for search results page.
    $this->abstractedPage->userMakeSearch('dorthe nors');
    $this->assertElementPresent("css=li.list-item.search-result");

    // Check for search with cql.
    $this->abstractedPage->userMakeSearch('"23685531" or "51109635"');
    $this->assertElementPresent("css=li.list-item.search-result");

    // Check facets.
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

    // One single item has to have year 2001.
    $this->assertElementContainsText('css=.pane-search-result .search-results li.search-result:eq(0) .content:first', 'By Dorthe Nors (2001)');
    // Restore the facet.
    $this->click('link=2001 (1)');
    $this->abstractedPage->waitForPage();

    // Check ascending title sorting.
    $this->select('css=#edit-sort', 'value=title_ascending');
    $this->abstractedPage->waitForPage();
    $results = array('Gravgæst', 'Soul : roman');
    for ($i = 0; $i < count($results); $i++) {
      $this->assertElementContainsText('css=.pane-search-result .search-result:eq(' . $i . ') .heading a', $results[$i]);
    }

    // Check descending title sorting.
    $this->select('css=#edit-sort', 'value=title_descending');
    $this->abstractedPage->waitForPage();
    $results = array('Soul : roman', 'Gravgæst');
    for ($i = 0; $i < count($results); $i++) {
      $this->assertElementContainsText('css=.pane-search-result .search-result:eq(' . $i . ') .heading a', $results[$i]);
    }

    // Check descending title sorting.
    $this->select('css=#edit-sort', 'value=date_ascending');
    $this->abstractedPage->waitForPage();
    $results = array('By Dorthe Nors (2001)', 'By Johan Theorin (2014)');
    for ($i = 0; $i < count($results); $i++) {
      $this->assertElementContainsText('css=.pane-search-result .search-result:eq(' . $i . ') .content:first', $results[$i]);
    }

    // Check ascending title sorting.
    $this->select('css=#edit-sort', 'value=date_descending');
    $this->abstractedPage->waitForPage();
    $results = array('By Johan Theorin (2014)', 'By Dorthe Nors (2001)');
    for ($i = 0; $i < count($results); $i++) {
      $this->assertElementContainsText('css=.pane-search-result .search-result:eq(' . $i . ') .content:first', $results[$i]);
    }

    // Check the search results limits.
    // 10 by default.
    $this->abstractedPage->userMakeSearch('bog');
    $this->assertEquals(9, $this->getElementIndex('css=.search-result:last'));

    // 25
    $this->select('css=#edit-size', 'value=25');
    $this->abstractedPage->waitForPage();
    $this->assertEquals(24, $this->getElementIndex('css=.search-result:last'));

    // 50
    $this->select('css=#edit-size', 'value=50');
    $this->abstractedPage->waitForPage();
    $this->assertEquals(49, $this->getElementIndex('css=.search-result:last'));

    // Check that each item has availability block.
    for ($i = 0; $i < 49; $i++) {
      $this->assertElementPresent('css=.search-result--availability:eq(' . $i . ')');
    }

    // Speed up things a little bit.
    $this->select('css=#edit-size', 'value=10');
    $this->abstractedPage->waitForPage();

    // Check pager.
    $this->assertElementContainsText('css=.pager .pager-current', '1');
    $this->click('link=next ›');
    $this->abstractedPage->waitForPage();

    $this->assertElementContainsText('css=.pager .pager-current', '2');
    $this->assertElementPresent('link=‹ previous');
    $this->click('link=next ›');
    $this->abstractedPage->waitForPage();

    $this->assertElementContainsText('css=.pager .pager-current', '3');
    $this->assertElementPresent('link=« first');
    $this->click('link=« first');
    $this->abstractedPage->waitForPage();

    $this->assertElementContainsText('css=.pager .pager-current', '1');
    $this->assertElementNotPresent('link=« first');
    $this->assertElementNotPresent('link=‹ previous');
  }

  /**
   * Test search functionality as logged in user.
   *
   * @see testSubmitAnonymous()
   */
  public function testSearchPageLoggedIn() {
    $this->open('/' . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    $this->testSearchPageAnonymous();
  }
}
