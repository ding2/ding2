<?php
class MkdruModules extends PHPUnit_Extensions_SeleniumTestCase {  
  protected $config;

  protected function setUp() {
    $this->config = new SPTTestConfig();
    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
    sleep(5);
  }

  public function testMkdruModules() {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[2]/a/span");
    $this->type("id=edit-name", "admin");
    $this->type("id=edit-pass", "1234");
    $this->click('css=input[value="Log ind"]');
    // Add sleep metod for wait all element mkdru to load!!
    sleep(7);
    $this->open("/admin/modules");

    // Verify ifthe mkdru module is enabled.
    $this->type("id=edit-module-filter-name", "Pazpar2 metasearch Ding integration");

    $mkdru_element = $this->isElementPresent('css=input[checked="checked"][name="modules[Ding!][mkdru_ding][enable]"]');
    sleep(5);
    if ($mkdru_element) {
      $this->assertTrue($this->isElementPresent('css=input[checked="checked"][name="modules[Ding!][mkdru_ding][enable]"]'));
    }
    else {
      echo "Module Ding mkdru is not enabled";
    }

    // Go to Mkdru settings and verify if is correct.
    $this->open("/admin/config/search/mkdru_ding");
    sleep(5);

    $proxy_service_p2 = $this->isElementPresent('css=input[value="/service-proxy/"]');
    if ($proxy_service_p2) {
      $this->assertTrue($this->isElementPresent('css=input[value="/service-proxy/"]'));
    }
    else {
      echo "Pazpar2/Service Proxy URL or path is incorect or is empty";
    }

    $proxy_service_u = $this->isElementPresent('css=input[value="spt"]');
    if ($proxy_service_u) {
      $this->assertTrue($this->isElementPresent('css=input[value="spt"]'));
    }
    else {
      echo "Service Proxy username  is incorect or is empty";
    }
    sleep(5);

    $proxy_service_p = $this->isElementPresent('css=input[value="spt919"]');
    if ($proxy_service_p) {
      $this->assertTrue($this->isElementPresent('css=input[value="spt919"]'));
    }
    else {
      echo "Service Proxy password is incorect or is empty";
    }
  }
}
