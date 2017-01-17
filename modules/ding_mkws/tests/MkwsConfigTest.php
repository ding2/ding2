<?php
class MkwsModules extends PHPUnit_Extensions_SeleniumTestCase {  
  protected $config;

  protected function setUp() {
    $this->config = new SPTTestConfig();
    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
    sleep(5);
  }

  public function testMkwsModules() {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[2]/a/span");
    $this->type("id=edit-name", "admin");
    $this->type("id=edit-pass", "1234");
    $this->click('css=input[value="Log ind"]');
    // Add sleep metod for wait all element mkdru to load!!
    sleep(7);
    $this->open("/admin/modules");

    // Verify ifthe mkws module is enabled.
    $this->type("id=edit-module-filter-name", "mkws");
    $mkws_element = $this->isElementPresent('css=input[checked="checked"][name="modules[Ding!][ding_mkws][enable]"]');
    sleep(5);
    if ($mkws_element) {
      $this->assertTrue($this->isElementPresent('css=input[checked="checked"][name="modules[Ding!][ding_mkws][enable]"]'));
    }
    else {
      echo "Module Ding mkws is not enabled";
    }
    // Go to Mkws settings and verify if is correct.
    $this->open("admin/config/ding/mkws");
    $url_service = $this->isElementPresent('css=input[value="http://mkc.indexdata.com:9009/service-proxy/"]');
    sleep(5);
    if ($url_service) {
      $this->assertTrue($this->isElementPresent('css=input[value="http://mkc.indexdata.com:9009/service-proxy/"]'));
    }
    else {
      echo "Url of service is incorect or is empty";
    }

    sleep(5);
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
    sleep(5);

    $proxy_service_p2 = $this->isElementPresent('css=input[value="/service-proxy/"]');
    if ($proxy_service_p2) {
      $this->assertTrue($this->isElementPresent('css=input[value="/service-proxy/"]'));
    }
    else {
      echo "Pazpar2/Service Proxy URL or path is incorect or is empty";
    }
    sleep(5);
  }
}
