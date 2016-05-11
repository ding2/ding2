<?php
Class ItemWTest extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstractedPage;
  protected $config;

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();

    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
    // resetState($this->config->getLms());
  }

  /**
   * Test Ding item Cache as admin.
   */
  public function testItemW() {
    // Open the ding2 site
    $this->open("/");
    // Login with admin user
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    // Go to modules for enabled module easyddb editorial dashboard
    $this->open("/admin/modules");
    $this->type("id=edit-module-filter-name", "ding item viewer");

    $element = $this->isElementPresent('css=input[checked="checked"][name="modules[easyDDB][ding_item_viewer][enable]"]');
    if ($element== FALSE) {
      $this->click("id=edit-modules-easyddb-ding-item-viewer-enable");
      $this->click("id=edit-submit");
    }
    else {
      $this->assertTrue($this->isElementPresent('css=input[checked="checked"][name="modules[easyDDB][ding_item_viewer][enable]"]'));
    }
    $this->abstractedPage->refresh();
    $this->open("/admin/structure/pages/nojs/operation/page-ding_frontpage/handlers/page_ding_frontpage_panel_context/content");
    sleep(5);
    $this->click("css=a.ctools-dropdown-link.ctools-dropdown-image-link");
    sleep(5);
    $this->click("css=#panel-region-primary .ctools-dropdown .ctools-dropdown-container > ul > li:eq(0) a");
    sleep(5);
    $this->click("link=Ding!");
    sleep(5);
    $this->click("link=Ding item viewer");
    sleep(5);
    $this->type("id=edit-ding-item-viewer-ting-searches-0-title", "Inferno");
    $this->type("id=edit-ding-item-viewer-ting-searches-0-subtitle", "Inferno");
    $this->type("id=edit-ding-item-viewer-ting-searches-0-query", "Inferno");
    $this->click("id=edit-buttons-return");
    sleep(25);
    $this->click("id=edit-save");
    $this->click("id=edit-save");
    $this->waitForPageToLoad("30000");
    $this->click("id=edit-save");
  }
}
?>