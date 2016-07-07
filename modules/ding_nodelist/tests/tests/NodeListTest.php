<?php

class NodeListTest extends PHPUnit_Extensions_Selenium2TestCase {
  protected $abstractedPage;
  protected $config;

  protected function setUp() {
  $this->abstractedPage = new DINGTestPageAbstraction($this);
  $this->config = new DINGTestConfig();

  $this->setBrowser($this->config->getBrowser());
  $this->setBrowserUrl($this->config->getUrl());
  }
  /**
   * Test Ding NodeList as admin.
   */
  public function testNodeList() {
    $test = $this; // Workaround for anonymous function scopes in PHP < v5.4.
    $session = $this->prepareSession(); // Make the session available.
    // get
    $this->url("/");
    // clickElement
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    // get
    $this->url("/" . "/admin/modules");
    // setElementText
    $element = $this->byId("edit-module-filter-name");
    $element->click();
    $element->value("ding nodelist");
    // setElementSelected
    $element = $this->byId("edit-modules-artesis-ding-nodelist-enable");
    if (!$element->selected()) {
      $element->click();
      $this->byId("edit-submit")->click();
    }
    // clickElement
    sleep(5);
    $element = $this->byId("edit-module-filter-name");
    $element->click();
    $element->clear();
    $element->value("Ding Ipe ");
    // setElementSelected
    $element = $this->byId("edit-modules-ding-ding-ipe-filter-enable");
    if (!$element->selected()) {
      $element->click();
      $this->byId("edit-submit")->click();
    }
    // clickElement
    $this->url("/" . "/admin/config");
    // clickElement
    sleep(5);
    $this->byLinkText("IPE pane filter settings")->click();
    // clickElement
    sleep(5);
    $this->byLinkText("IPE PANE FILTER")->click();
    // setElementSelected
    $element = $this->byId("edit-ding-ipe-filter-table-ding-item-list-value");
    if (!$element->selected()) {
      $element->click();
    }
    // setElementSelected
    $element = $this->byId("edit-ding-ipe-filter-table-ding-nodelist-value");
    if (!$element->selected()) {
      $element->click();
    }
    // clickElement
    $this->byId("edit-actions-submit")->click();
    // clickElement
    sleep(5);
    $this->url("/");
    $this->byId("panels-ipe-customize-page")->click();
    sleep(5);
    // clickElement
    //add nodelist with IPE module
    $this->byLinkText("Add")->click();
    sleep(5);
    // clickElement
    $this->byLinkText("Nodelist")->click();
    // setElementSelected
    sleep(5);
    $element = $this->byXPath("//select[@id='edit-widget-type']//option[6]");
    if (!$element->selected()) {
      $element->click();
    }
    sleep(5);
    // setElementSelected
    $element = $this->byXPath("//select[@id='edit-limit']//option[7]");
    if (!$element->selected()) {
      $element->click();
    }
    // clickElement
    $this->byId("edit-return")->click();
    // clickElement
    $this->byId("panels-ipe-save")->click();
    // get
    // add nodelist with panel
    /*  $this->url("/"."/admin/structure/pages/nojs/operation/page-ding_frontpage/handlers/page_ding_frontpage_panel_context/content");
    // clickElement
    sleep(5);
    // clickElement
    $this->byCssSelector("a.ctools-dropdown-link.ctools-dropdown-image-link")->click();
    // clickElement
    $this->byXPath("//div[4]/div[2]/div[2]/div/div[2]/div[2]/div/div[2]/form/div/div[4]/div/div[1]/div/div[1]/div[2]/div/ul/li[1]/a")->click();
    // clickElement
    sleep(5);
    $this->byLinkText("Ding!")->click();
    // clickElement
    sleep(5);
    $this->byLinkText("Nodelist")->click();
    sleep(5);
    $element = $this->byXPath("//select[@id='edit-content-type']//option[2]");
    if (!$element->selected()) {
      $element->click();
    }
    sleep(5);
    // setElementSelected
    $element = $this->byXPath("//select[@id='edit-widget-type--2']//option[6]");
    if (!$element->selected()) {
      $element->click();
    }
    sleep(5);
    // setElementText
    $element = $this->byId("edit-override-title-text--2");
    $element->click();
    $element->value("NodeList");
    // setElementSelected
    sleep(5);
    $element = $this->byXPath("//select[@id='edit-limit']//option[9]");
    if (!$element->selected()) {
      $element->click();
    }
    sleep(5);
    // clickElement
    $this->byId("edit-return--2")->click();
    sleep(5);
    // clickElement
    $this->byId("edit-save")->click();
    sleep(5);
    // clickElement
    $this->url("/");*/
    // assertElementPresent
    //Verifying if nodelist exist in frontpage
    try {
      $boolean = ($test->byCssSelector("div.panel-pane.pane-ding-nodelist") instanceof \PHPUnit_Extensions_Selenium2TestCase_Element);
    }
    catch (\Exception $e) {
      $boolean = false;
    }
    $test->assertTrue($boolean);
    sleep(5);
  }
}
