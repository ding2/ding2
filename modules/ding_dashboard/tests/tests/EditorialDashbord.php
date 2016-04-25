<?php
Class EDashTest extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstractedPage;
  protected $config;

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();

    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
  }

  /**
   * Test Ding item Cache as admin.
   */
  public function testEDash() {
    // Open the ding2 site
    $this->open("/");
    // Login with admin user
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    // Go to modules for enabled module easyddb editorial dashboard
    $this->open("/admin/modules");
    $this->type("id=edit-module-filter-name", "easyddb editorial dashboard");

    $element = $this->isElementPresent('css=input[checked="checked"][name="modules[easyDDB][easyddb_editorial_dashboard][enable]"]');
    if ($element== FALSE) {
      $this->click("id=edit-modules-easyddb-easyddb-editorial-dashboard-enable");
      $this->click("id=edit-submit");
      sleep(5);
      $this->click("id=edit-submit");
    }
    else {
      $this->assertTrue($this->isElementPresent('css=input[checked="checked"][name="modules[easyDDB][easyddb_editorial_dashboard][enable]"]'));
    }
    $this->abstractedPage->refresh();
    $this->open("/admin/config");
    sleep(5);
    $this->click("link=Content types");
    $this->abstractedPage->waitForPage();

    $element=$this->isElementPresent("css=input[checked='checked'][name='editorial_content_types[ding_event]']");
    if ($element== FALSE) {
      $this->click("id=edit-editorial-content-types-ding-event");
      $this->click("id=edit-editorial-content-types-ding-library");
      $this->click("id=edit-editorial-content-types-ding-news");
      sleep(5);
      $this->click("id=edit-submit");
    }
    else {
      $this->assertTrue($this->isElementPresent("css=input[checked='checked'][name='editorial_content_types[ding_event]"));
    }
    sleep(5);
    $this->open("/");
    $this->click("link=Da farfar var dreng - billeder og postkort fra en svunden tid");
    $this->abstractedPage->waitForPage();
    $this->click("link=Edit");
    $this->isElementPresent("id=edit-save-push");
  }
}
?>