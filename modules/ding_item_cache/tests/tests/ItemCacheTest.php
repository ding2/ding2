<?php

class ItemCacheTest extends PHPUnit_Extensions_Selenium2TestCase {
  protected $abstractedPage;
  protected $config;

  protected function setUp() {
    $this->abstractedPage = new DINGTestPageAbstraction($this);
    $this->config = new DINGTestConfig();

    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
    }

  /**
   * Test Ding item Cache as admin.
   */
  public function testItemCache() {
    $test = $this; // Workaround for anonymous function scopes in PHP < v5.4.
    $session = $this->prepareSession(); // Make the session available.
    // get
    $this->url("/");
    // clickElement
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    // clickElement
    $this->url("/" . "/admin/modules");
    // setElementText
    $element = $this->byId("edit-module-filter-name");
    $element->click();
    $element->value("ding item cache");
    // setElementText
    sleep(5);
    // setElementSelected
    $element = $this->byId("edit-modules-ding-ding-item-cache-enable");
    if (!$element->selected()) {
      $element->click();
      $this->byId("edit-submit")->click();
    }
    sleep(5);
    // clickElement
    // setElementText
    $element = $this->byId("edit-module-filter-name");
    $element->click();
    $element->clear();
    $element->value("ding item list");
    // setElementSelected
    sleep(5);
    $element = $this->byId("edit-modules-ding-ding-item-list-enable");
    if (!$element->selected()) {
      $element->click();
      $this->byId("edit-submit")->click();
    }
    sleep(5);
    // clickElement
    // get
    $this->url("/" . "/admin/config");
    // clickElement
    sleep(5);
    $this->byLinkText("Ding item cache")->click();
    // setElementSelected
    $element = $this->byId("edit-ding-item-cache-modules-ding-item-list");
    if (!$element->selected()) {
      $element->click();
    }
    $this->byId("edit-ding-item-cache-clear")->click();
    // clickElement
  }
}