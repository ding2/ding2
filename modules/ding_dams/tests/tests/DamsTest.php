<?php

Class DamsTest extends PHPUnit_Extensions_SeleniumTestCase {
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
  public function testDams()
  {
  // Open the ding2 site
   $this->open("/");
    // Login with admin user
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    // Go to modules for enabled module easyddb editorial dashboard
   $this->open("/admin/modules");
   $this->type("id=edit-module-filter-name", "ding dams");

   $element = $this->isElementPresent('css=input[checked="checked"][name="modules[Ding][ding_dams][enable]"]');
    if ($element== FALSE) {
      $this->click("id=edit-modules-easyddb-easyddb-dams-enable");
      $this->click("id=edit-submit");
      sleep(5);
      $this->click("id=edit-submit");
    }
    else {
      $this->assertTrue($this->isElementPresent('css=input[checked="checked"][name="modules[Ding][ding_dams][enable]"]'));
    }
   $this->abstractedPage->refresh();
   $this->open("/admin/config");
   sleep(5);
   $this->click("link=Wysiwyg profiles");
   $this->abstractedPage->waitForPage();
    $this->click("link=Edit");
    $this->abstractedPage->waitForPage();

$element = $this->isElementPresent('css=input[checked="checked"][name="buttons[drupal][dams_document]"]');
    if ($element== FALSE) {
      $this->click("id=edit-buttons-drupal-dams-document");
      $this->click("id=edit-buttons-drupal-dams-image");
      $this->click("id=edit-buttons-drupal-dams-audio");
      $this->click("id=edit-buttons-drupal-dams-video");
      $this->click("id=edit-submit");
    }
    else {
      $this->assertTrue($this->isElementPresent('css=input[checked="checked"][name="buttons[drupal][dams_document]"]'));
    }
    $this->open("/node/add/ding-event");
    $this->click("css=span.cke_button_icon.cke_button__media_icon");
    sleep(5);
    $this->click("xpath=(//a[contains(text(),'Cancel')])[2]");
 }
}
