<?php

class ItemListTest extends PHPUnit_Extensions_Selenium2TestCase {
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
  public function testItemList() {
    $test = $this; // Workaround for anonymous function scopes in PHP < v5.4.
    $session = $this->prepareSession(); // Make the session available.
    // get
    $this->url("/");
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    // get
     $this->url("/" . "/admin/modules");
    // setElementText
    $element = $this->byId("edit-module-filter-name");
    // $element->click();
    // $element->clear();
    $element->value("Ding item List");
    // clickElement
    $this->byId("module-filter-squeeze")->click();
    // clickElement
    // $this->byXPath("//label[@for='edit-modules-ding-ding-item-list-enable']")->click();
    // setElementNotSelected
    sleep(5);
    $element = $this->byId("edit-modules-ding-ding-item-list-enable");
    if (!$element->selected()) {
      $element->click();

      // clickElement
      $this->byId("module-filter-squeeze")->click();
      sleep(5);
      $this->byId("edit-submit")->click();
      // sleep for 5 sec
      sleep(5);
      $this->byId("edit-submit")->click();
      sleep(5);
    }
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
    $this->byLinkText("Ding item list")->click();
    // clickElement
    sleep(5);
    // setElementText
    $element = $this->byId("edit-item-query");
    $element->click();
    $element->clear();
    $element->value("Harry Potter");
    // clickElement
    sleep(5);
    $this->byId("edit-return")->click();
    // clickElement
    sleep(50);
    $this->byId("panels-ipe-save")->click();

     /* // add ding item list with panel
     $this->url("/"."/admin/structure/pages/nojs/operation/page-ding_frontpage/handlers/page_ding_frontpage_panel_context/content");
    // clickElement
    sleep(5);
    // clickElement
    $this->byCssSelector("a.ctools-dropdown-link.ctools-dropdown-image-link")->click();
    // clickElement
    $this->byXPath("//div[4]/div[2]/div[2]/div/div[2]/div[2]/div/div[2]/form/div/div[4]/div/div[1]/div/div[1]/div[2]/div/ul/li[1]/a")->click();
    // clickElement
    sleep(5);
    $this->byLinkText("Ding!")->click();
    sleep(5);
    // clickElement
    $this->byLinkText("Ding item list")->click();
    // setElementText
    sleep(5);
    $element = $this->byId("edit-item-query");
    $element->click();
    $element->clear();
    $element->value("Inferno");
    // clickElement
    $this->byId("edit-return--2")->click();
    sleep(5);
    // clickElement
    $this->byId("edit-save")->click();
    // clickElement
    sleep(5);
    $this->url("/");
     */

    //Verifying if ding item list exist in frontpage
    sleep(5);
    try {
      $boolean = ($test->byCssSelector("div.panel-pane.pane-ding-item-list") instanceof \PHPUnit_Extensions_Selenium2TestCase_Element);
    } catch (\Exception $e) {
      $boolean = false;
    }
    $test->assertTrue($boolean);
    sleep(5);
  }
}
