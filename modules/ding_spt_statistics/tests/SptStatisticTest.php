<?php
class SptStatistics extends PHPUnit_Extensions_SeleniumTestCase {
  protected $config;

  protected function setUp() {
    $this->config = new SPTTestConfig();

    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
    sleep(5);
  }

  public function testSptStatistics() {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[2]/a/span");
    $this->type("id=edit-name", "admin");
    $this->type("id=edit-pass", "1234");
    $this->click('css=input[value="Log ind"]');
    sleep(5);
    // Go to statistics page spt!!
    $this->open("/admin/reports/spt-statistics");
    sleep(7);
    $is_present_elem = $this->isElementPresent('id=ding-spt-statistics-date-picker-form');
    // Verify if are the table statistics.
    sleep(2);
    if ($is_present_elem) {
      $this->assertTrue($this->isElementPresent('css=div.form-item-date-from'));
      $this->assertTrue($this->isElementPresent('css=div.form-item-date-to'));   
      $this->assertTrue($this->isElementPresent('css=input#edit-reset'));   
      sleep(5);
    }
    else echo 'The tabell statistic is not!!!';
  }
}
