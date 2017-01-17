<?php
class FilterSpt extends PHPUnit_Extensions_SeleniumTestCase {
  const WAIT_FOR_ELEMENT = 15;

  public function waitForElement($selector, $time = self::WAIT_FOR_ELEMENT, $force = TRUE) {
    for ($second = 0; ; $second++) {
      if ($second >= $time) {
        if ($force) {
          $this->fail('Element ' . $selector . ' not found.');
        }
        return FALSE;
      }
      try {
        if ($this->isElementPresent($selector)) {
          return TRUE;
        }
      }
      catch (Exception $e) {}
      sleep(1);
    }
  }

  protected function setUp() {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://spt-v2.ddbcms.dev.inlead.dk/");
  }

  public function testFilterSpt() {
    $this->open("/");
    $this->type("id=edit-search-block-form--2", "harry potter");
    $this->click("id=edit-submit");
    sleep(7);
    $this->click("link=Search Digital Resources");
    // Add sleep metod for wait all element mkdru to load!!
    sleep(10);
    $this->waitForElement('id=bibliotek.dk');
    $this->click('id=bibliotek.dk');
    sleep(10);
      //Verify if facets are.
    $this->assertTrue($this->isElementPresent('css=div.mkdru-facet-subject'));
    $this->assertTrue($this->isElementPresent('css=div.mkdru-facet-author'));
    $this->click('id=bibliotek.dk');
  }
}
