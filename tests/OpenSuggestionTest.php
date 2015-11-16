<?php

class OpenSuggestionTest extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstractedPage;
  protected $config;

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();

    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());

    }

  public function testLoansMaterialInformation() {
    $this->windowMaximize();
    $this->open('/' . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->type("id=edit-search-block-form--2", "abba");
    $this->fireEvent("id=edit-search-block-form--2", 'keyup');
    $this->abstractedPage->waitForElement('css=#autocomplete');
  }
}
