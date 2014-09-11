<?php

require_once(dirname(__FILE__) . '/config.inc');

class UserMenu extends PHPUnit_Extensions_SeleniumTestCase {

  protected function setUp() {
    $this->setBrowser(TARGET_BROWSER);
    $this->setBrowserUrl(TARGET_URL);
  }

  /**
   * Check loan link and loan page in user profile.
   */
  public function testClickOnLoans()
  {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/h2/a"));
    $this->assertEquals("Loans", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div/div/a[3]/span[2]"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/div/div/div/a[3]/span[2]");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Loan list", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div/h2"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }

  /**
   * Check reservation link and reservation page.
   */
  public function testClickOnReservation()
  {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("link=Login");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My account", $this->getText("link=My account"));
    $this->assertTrue($this->isElementPresent("css=a.user-status.user-status-reservation > span.user-status-label"));
    $this->click("css=a.user-status.user-status-reservation > span.user-status-label");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My reservations", $this->getText("css=h2.pane-title"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }

  /**
   * Check bookmark link and bookmark page.
   */
  public function testClickOnBookmark()
  {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=My account"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[5]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=label.option"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-bookmark-import-form']/div/div/label"));
    $this->assertTrue($this->isElementPresent("//div[@id='user-bookmarks']/div/aside/div/ul/li[5]/a/span"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }

  /**
   * Check debts link and page.
   */
  public function testLinkToMyDebts()
  {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=h2.pane-title"));
    $this->assertTrue($this->isElementPresent("link=My account"));
    $this->assertTrue($this->isElementPresent("css=span.user-status-label"));
    $this->click("css=span.user-status-label");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=h2.pane-title"));
    $this->assertTrue($this->isElementPresent("id=edit-pay-selected"));
    $this->assertTrue($this->isElementPresent("id=edit-pay-all"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}