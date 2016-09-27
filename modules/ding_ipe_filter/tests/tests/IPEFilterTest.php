<?php
Class IPETest extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstractedPage;
  protected $config;

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();

    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
  }


  public function testIPE() {
    $this->open("/");
    // Login with admin user
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    // Go to modules for enabled module easyddb editorial dashboard
    $this->open("/admin/modules");
    $this->type("id=edit-module-filter-name", "easyDDB IPE Filter");
    sleep(5);
    $element=$this->isElementPresent("css=input[checked='checked'][name='modules[easyDDB][easyddb_ipe_filter][enable]']");
    if ($element== FALSE) {
      $this->click("id=edit-modules-easyddb-easyddb-ipe-filter-enable");
      sleep(5);
      $this->click("id=edit-submit");
      $this->click("id=edit-submit");
    }
    else {
      $this->assertTrue($this->isElementPresent("css=input[checked='checked'][name='modules[easyDDB][easyddb_ipe_filter][enable]']"));
    }
    $this->open("/admin/config");
    sleep(5);
    $this->click("link=IPE pane filter settings");
    $this->abstractedPage->waitForPage();

    $element=$this->isElementPresent("css=input[checked='checked'][name='easyddb_ipe_filter_roles[3]']");
    if ($element== FALSE) {
      $this->click("id=edit-easyddb-ipe-filter-roles-3");
      sleep(5);
      $this->click("id=edit-submit");
    }
    else {
      $this->assertTrue($this->isElementPresent("css=input[checked='checked'][name='easyddb_ipe_filter_roles[3]']"));
    }

    $this->click("link=IPE pane filter");
    sleep(5);
    $element=$this->isElementPresent("css=input[checked='checked'][name='easyddb_ipe_filter_table[ding_event-ding_event_list_frontpage][value]']");
    if ($element== FALSE) {
      $this->click("id=edit-easyddb-ipe-filter-table-ding-event-ding-event-list-frontpage-value");
      $this->click("id=edit-easyddb-ipe-filter-table-ding-event-ding-event-simple-list-value");
      $this->click("id=edit-easyddb-ipe-filter-table-ding-event-ding-event-list-same-tag-value");
      $this->click("id=edit-easyddb-ipe-filter-table-ting-ting-collection-types-value");
      $this->click("id=edit-easyddb-ipe-filter-table-ting-ting-object-types-value");
      $this->click("id=edit-easyddb-ipe-filter-table-ting-ting-relation-anchors-value");
      $this->click("id=edit-easyddb-ipe-filter-table-ting-search-carousel-ting-search-carousel-value");
      $this->click("id=edit-easyddb-ipe-filter-table-ding-news-ding-news-frontpage-list-value");
      $this->click("id=edit-easyddb-ipe-filter-table-ding-news-ding-news-list-value");
      $this->click("id=edit-easyddb-ipe-filter-table-ding-news-panel-pane-2-value");
      $this->click("id=edit-easyddb-ipe-filter-table-carousel-value");
    
      sleep(5);
      $this->click("id=edit-actions-submit");
    }  
    else {
      $this->assertTrue($this->isElementPresent("css=input[checked='checked'][name='easyddb_ipe_filter_table[ding_event-ding_event_list_frontpage][value]']"));
    }
    $this->open("/admin/modules");
    $this->type("id=edit-module-filter-name", "Panels In-Place Editor");
    $this->click("id=edit-modules-panels-panels-ipe-links-configure");
    $this->abstractedPage->waitForPage();
    $this->click("link=Settings");
    $this->abstractedPage->waitForPage();
    $this->select("id=edit-panels-renderer-default", "label=In-Place Editor");
    $this->click("id=edit-submit");
    $this->open("/admin/structure/pages/nojs/operation/page-ding_frontpage/");
    $this->click("id=page-manager-operation-settings");
   
    sleep(2);
    $this->click("//label[text()='In-Place Editor']");
    sleep(2);
    $this->click("css=input[value='Update and save']");
      
    $this->abstractedPage->waitForPage();
    $this->open("/");
    sleep(5);
    $this->click("id=panels-ipe-customize-page");
    sleep(5);
    $this->click("xpath=(//a[contains(text(),'Add')])[2]");
    sleep(5);
  }
}
