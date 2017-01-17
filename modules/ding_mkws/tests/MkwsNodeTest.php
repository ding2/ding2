<?php
class MkwsNode extends PHPUnit_Extensions_SeleniumTestCase {
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

  public function testMkwsNode() {
    $this->open("/nyheder/boger/eventyrere-og-globetrottere");
    /* Verify if content mkws are present in page search and verify if elements target
       title, autor, date are prezent in content mkws. If is not will be appear report message. 
    */
    $is_present_elem = $this->isElementPresent('css=div.ding-mkws-content');
    if ($is_present_elem) {
      $this->waitForElement('css=.ding-mkws-author');
      $this->assertTrue($this->isElementPresent('css=p.ding-mkws-target'));
      $title_mkws = $this->isElementPresent('class=ding-mkws-title');
      //Verify if title is link.
      if ($title_mkws) {
        $this->assertTrue($this->isElementPresent('css=a.ding-mkws-title'));
      }
      $this->assertTrue($this->isElementPresent('css=.ding-mkws-author'));
      $this->assertTrue($this->isElementPresent('css=.ding-mkws-date'));
      sleep(5);
      $this->assertTrue($this->isElementPresent('link=See all results'));
      $this->click("link=See all results");
      sleep(5);
    }
    else echo 'Missing results mkws!!!';
  }
}
