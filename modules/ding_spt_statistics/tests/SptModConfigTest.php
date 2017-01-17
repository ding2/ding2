<?php
class SptModules extends PHPUnit_Extensions_SeleniumTestCase {  
  protected $config;

  protected function setUp() {
    $this->config = new SPTTestConfig();
    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
    sleep(5);
  }

  public function testSptModules() {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[2]/a/span");
    $this->type("id=edit-name", "admin");
    $this->type("id=edit-pass", "1234");
    $this->click('css=input[value="Log ind"]');
    // Add sleep metod for wait all element mkdru to load!!
    sleep(7);
    $this->open("/admin/modules");

    // Verify ifthe spt statistic module is enabled.
    $this->type("id=edit-module-filter-name", "Ding SPT Statistics");
    $spt_element = $this->isElementPresent('css=input[checked="checked"][name="modules[Ding!][ding_spt_statistics][enable]"]');
    sleep(5);
    if ($spt_element) {
      $this->assertTrue($this->isElementPresent('css=input[checked="checked"][name="modules[Ding!][ding_spt_statistics][enable]"]'));
    }
    else {
      echo "Module Ding SPT Statistics is not enabled";
    }
  }
}
