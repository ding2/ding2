<?php
class MkwsWidgetPane extends PHPUnit_Extensions_SeleniumTestCase {
  const WAIT_FOR_ELEMENT = 15;
  protected $config;

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
    $this->config = new SPTTestConfig();
    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
    sleep(5);
  }

  public function testMkwsWidgetPane() {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[2]/a/span");
    $this->type("id=edit-name", "admin");
    $this->type("id=edit-pass", "1234");
    $this->click('css=input[value="Log ind"]');
    sleep(5);
    $this->open("/admin/structure/pages/nojs/operation/node_view/handlers/node_view_panel_context/content?destination=node/20");
    sleep(5);
    $this->click("css= .panels-region-links-left_sidebar a.ctools-dropdown-link");
    sleep(4);
    $this->click("xpath=(//a[contains(text(),'Add content')])[2]"); 
    sleep(4);
    $this->click("link=Ding!"); 
    sleep(2);
    $this->click("link=MKWS widget pane"); 
    sleep(3);
    $this->type("id=edit-term", "abba");
    $this->type("id=edit-amount", "3");
    $this->addSelection("id=edit-resources", "label=Bibliotek.dk");
    $this->addSelection("id=edit-resources", "label=Britannica Library (RSS) [uk]");
    $this->addSelection("id=edit-resources", "label=DR Bonanza");
    $this->type("id=edit-maxrecs", "1");
    $this->click("css=.form-submit[value='Finish']"); 
    sleep(4);
    $this->click("css=.form-submit[value='Update and save']"); 
    sleep(6);
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
    else echo 'The mkws not work well!!!';
  }
}
