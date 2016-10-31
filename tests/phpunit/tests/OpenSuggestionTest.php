<?php

require_once 'Ding2TestBase.php';

class OpenSuggestionTest extends Ding2TestBase {
  protected function setUp() {
    parent::setUp();
    resetState($this->config->getLms());
  }

  /**
   * Test the autosuggestion functionality in search form for
   * anonymous user.
   *
   * Check some pre-tested values to be autosuggested.
   */
  public function testSearchAutosuggestionAnonymous() {
    $this->open('/' . $this->config->getLocale());
    // Type something in search field and force autocomplete
    // to be shown. Check simple query.
    $this->type('css=#edit-search-block-form--2', 'nors');
    $this->fireEvent('css=#edit-search-block-form--2', 'keyup');
    $this->abstractedPage->waitForElement('css=#autocomplete');
    // Check the first result from autocomplete.
    $this->abstractedPage->waitForElement('css=#autocomplete ul li:first');
    $this->assertElementContainsText('css=#autocomplete ul li:first', 'Norsk litteratur');
    // Check utf8 characters.
    $this->type('css=#edit-search-block-form--2', 'gæk');
    $this->fireEvent('css=#edit-search-block-form--2', 'keyup');
    $this->abstractedPage->waitForElement('css=#autocomplete');
    // Check the first result from autocomplete.
    $this->abstractedPage->waitForElement('css=#autocomplete ul li:first');
    $this->assertElementContainsText('css=#autocomplete ul li:first', 'gækkebreve og vers');
    // Check that active suggestion is highlighted.
    // Force 'down' key press.
    $this->keyDown('css=#edit-search-block-form--2', '\\40');
    $this->assertEquals('selected', $this->getAttribute('css=#autocomplete ul li:first@class'));
    // Click the first result and check the search form to be
    // populated with this text.
    $this->mouseDown('css=#autocomplete ul li:first');
    $this->assertEquals('gækkebreve og vers', $this->getValue('css=#edit-search-block-form--2'));
  }

  /**
   * Test the autosuggestion functionality in search form for
   * logged in user.
   *
   * @see testSearchAutosuggestionAnonymous()
   */
  public function testSearchAutosuggestionLoggedIn() {
    $this->open('/' . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    $this->testSearchAutosuggestionAnonymous();
  }
}
