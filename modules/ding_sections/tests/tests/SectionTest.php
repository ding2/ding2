<?php

/**
 * @file
 * Ding Sections Selenium test.
 */

// @codingStandardsIgnoreStart
/**
 *
 */
class SectionsTest extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstractedPage;
  protected $config;

  /**
   *
   */
  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();

    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
  }

  /**
   * Test Ding item Cache as admin.
   */
  public function testSection() {
    // Open the ding2 site.
    $this->open("/");
    // Login with admin user.
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    // Go to modules for enabled module ding sections.
    $this->open("/admin/modules");
    $this->type("id=edit-module-filter-name", "ding sections");

    $element = $this->isElementPresent('css=input[checked="checked"][name="modules[Ding!][ding_sections][enable]"]');
    if ($element == FALSE) {
      $this->click('id=edit-modules-ding-ding-sections-enable');
      $this->click('id=edit-modules-ding-ding-sections-custom-css-enable');
      $this->click('id=edit-modules-ding-ding-sections-header-image-enable');
      $this->click('id=edit-modules-ding-ding-sections-og-integration-enable');
      $this->click('id=edit-modules-ding-ding-sections-term-menu-enable');
      $this->click('id=edit-modules-ding-ding-sections-term-panel-enable');
      sleep(5);
      $this->type("id=edit-module-filter-name", "nodelist");
      $this->click('id=edit-modules-easyddb-ding-nodelist-enable');
      sleep(5);
      $this->click("id=edit-submit");
    }
    else {
      $this->assertTrue($this->isElementPresent('css=input[checked="checked"][name="modules[Ding!][ding_sections][enable]"]'));
    }
    // Add new section link and edit and save.
    $this->open("/admin/structure/taxonomy/section/add");
    $this->type("id=edit-name", "Section-term");
    $this->click("id=edit-submit");
    $this->abstractedPage->waitForPage();
    sleep(5);
  }

}
// @codingStandardsIgnoreEnd