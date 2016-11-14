<?php

require_once 'Ding2TestBase.php';

class SearchResultTest extends Ding2TestBase {
  protected function setUp() {
    parent::setUp();
    resetState($this->config->getLms());
    $this->config->resetLms();
  }

  /**
   * Test search functionality as anonymous.
   *
   * Check when filled and empty search is made.
   */
  public function testSearchPageAnonymous() {
    $this->open($this->config->getUrl() . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    // Check for no results page.
    $this->abstractedPage->userMakeSearch('');
    $this->assertElementContainsText('css=div.messages.error', 'Please enter some keywords.');

    // Check for search results page.
    $this->abstractedPage->userMakeSearch('hest');
    $this->assertElementPresent("css=li.list-item.search-result");

    // Check for search with cql.
    $this->abstractedPage->userMakeSearch('28954263 or 27994431');
    $this->assertElementPresent("css=li.list-item.search-result");

    // Check facets.
    // Check the pre-defined result.
    $results = array(
      'Ebog:',
      'Film (net):',
    );

    for ($i = 0; $i < count($results); $i++) {
      $this->assertElementPresent('css=.pane-search-result .search-results li.search-result:eq(' . $i . ')');
      $this->assertElementContainsText('css=.search-result--heading-type:eq(' . $i . ')', $results[$i]);
    }


    // Two type facets should be available.
    $this->assertElementPresent('link=ebog (1)');
    $this->assertElementPresent('link=film (net) (1)');

    // Now filter, using a type facet.
    $this->click('link=film (net) (1)');
    $this->abstractedPage->waitForPage();

    // Check that there is no ebog type facet.
    $this->assertElementNotPresent('link=ebog (1)');
    // Check that there is no more a second item.
    $this->assertElementNotPresent('css=.pane-search-result .search-results li.search-result:eq(1)');

    // And the first one is of type film.
    $this->assertElementContainsText('css=.search-result--heading-type:eq(0)', 'Film (net):');

    // Click the bog facet again, to uncheck.
    $this->click('link=film (net) (1)');
    $this->abstractedPage->waitForPage();

    // Try the year facet.
    $this->assertElementPresent('link=2009 (1)');
    $this->click('link=2009 (1)');
    $this->abstractedPage->waitForPage();

    // One single item has to have year 2001.
    $this->assertElementContainsText('css=.pane-search-result .search-results li.search-result:eq(0) .content:first', 'By Peder Bundgaard (2009)');
    // Restore the facet.
    $this->click('link=2009 (1)');
    $this->abstractedPage->waitForPage();

    // Check ascending title sorting.
    $this->select('css=#edit-sort', 'value=title_ascending');
    $this->abstractedPage->waitForPage();
    $results = array('Cowboy, Indianer og Hest', 'Sorte Hest : roman');
    for ($i = 0; $i < count($results); $i++) {
      $this->assertElementContainsText('css=.pane-search-result .search-result:eq(' . $i . ') .heading a', $results[$i]);
    }

    // Check descending title sorting.
    $this->select('css=#edit-sort', 'value=title_descending');
    $this->abstractedPage->waitForPage();
    $results = array('Sorte Hest : roman', 'Cowboy, Indianer og Hest');
    for ($i = 0; $i < count($results); $i++) {
      $this->assertElementContainsText('css=.pane-search-result .search-result:eq(' . $i . ') .heading a', $results[$i]);
    }

    // Check the search results limits.
    // 10 by default.
    $this->abstractedPage->userMakeSearch('alle');
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
    $this->open($this->config->getUrl() . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    $this->testSearchPageAnonymous();
  }
}
