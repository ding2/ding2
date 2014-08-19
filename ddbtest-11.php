<?php
class SearchResult extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testSoringAnonymous()
  {
    $this->open("/");
    $this->type("id=edit-search-block-form--2", "45154211 OR 43615513 OR 000305954");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=Inferno"));
    $this->assertEquals("", $this->getSelectedValue("id=edit-sort"));
    $this->assertEquals("Sort by: RankingSort by: Title (Ascending)Sort by: Title (Descending)Sort by: Creator (Ascending)Sort by: Creator (Descending)Sort by: Date (Ascending)Sort by: Date (Descending)", $this->getText("id=edit-sort"));
    $this->select("id=edit-sort", "label=Sort by: Title (Ascending)");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Inferno", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Sprache als Herrschaft : semiotische Kritik des \"Guten Menschen von Sezuan\", der Theorie Brechts und der literarischen Wertung", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[2]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Trchnicolour", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[3]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Zos kia cultus", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[4]/div/div/div[2]/div/h2/a"));
    $this->select("id=edit-sort", "label=Sort by: Title (Descending)");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Zos kia cultus", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Trchnicolour", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[2]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Sprache als Herrschaft : semiotische Kritik des \"Guten Menschen von Sezuan\", der Theorie Brechts und der literarischen Wertung", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[3]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Inferno", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[4]/div/div/div[2]/div/h2/a"));
    $this->select("id=edit-sort", "label=Sort by: Creator (Ascending)");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Zos kia cultus", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Trchnicolour", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[2]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Sprache als Herrschaft : semiotische Kritik des \"Guten Menschen von Sezuan\", der Theorie Brechts und der literarischen Wertung", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[3]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Inferno", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[4]/div/div/div[2]/div/h2/a"));
    $this->select("id=edit-sort", "label=Sort by: Creator (Descending)");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Sprache als Herrschaft : semiotische Kritik des \"Guten Menschen von Sezuan\", der Theorie Brechts und der literarischen Wertung", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Trchnicolour", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[2]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Zos kia cultus", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[3]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Inferno", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[4]/div/div/div[2]/div/h2/a"));
    $this->select("id=edit-sort", "label=Sort by: Date (Ascending)");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Sprache als Herrschaft : semiotische Kritik des \"Guten Menschen von Sezuan\", der Theorie Brechts und der literarischen Wertung", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Zos kia cultus", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[2]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Inferno", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[3]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Trchnicolour", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[4]/div/div/div[2]/div/h2/a"));
    $this->select("id=edit-sort", "label=Sort by: Date (Descending)");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Trchnicolour", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Inferno", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[2]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Zos kia cultus", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[3]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Sprache als Herrschaft : semiotische Kritik des \"Guten Menschen von Sezuan\", der Theorie Brechts und der literarischen Wertung", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[4]/div/div/div[2]/div/h2/a"));
  }

  public function testSoringLoggedIn()
  {
    $this->open("/");
    $this->click("link=Login");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
    $this->open("/");
    $this->type("id=edit-search-block-form--2", "45154211 OR 43615513 OR 000305954");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=Inferno"));
    $this->assertEquals("", $this->getSelectedValue("id=edit-sort"));
    $this->assertEquals("Sort by: RankingSort by: Title (Ascending)Sort by: Title (Descending)Sort by: Creator (Ascending)Sort by: Creator (Descending)Sort by: Date (Ascending)Sort by: Date (Descending)", $this->getText("id=edit-sort"));
    $this->select("id=edit-sort", "label=Sort by: Title (Ascending)");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Inferno", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Sprache als Herrschaft : semiotische Kritik des \"Guten Menschen von Sezuan\", der Theorie Brechts und der literarischen Wertung", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[2]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Trchnicolour", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[3]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Zos kia cultus", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[4]/div/div/div[2]/div/h2/a"));
    $this->select("id=edit-sort", "label=Sort by: Title (Descending)");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Zos kia cultus", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Trchnicolour", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[2]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Sprache als Herrschaft : semiotische Kritik des \"Guten Menschen von Sezuan\", der Theorie Brechts und der literarischen Wertung", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[3]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Inferno", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[4]/div/div/div[2]/div/h2/a"));
    $this->select("id=edit-sort", "label=Sort by: Creator (Ascending)");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Zos kia cultus", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Trchnicolour", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[2]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Sprache als Herrschaft : semiotische Kritik des \"Guten Menschen von Sezuan\", der Theorie Brechts und der literarischen Wertung", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[3]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Inferno", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[4]/div/div/div[2]/div/h2/a"));
    $this->select("id=edit-sort", "label=Sort by: Creator (Descending)");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Sprache als Herrschaft : semiotische Kritik des \"Guten Menschen von Sezuan\", der Theorie Brechts und der literarischen Wertung", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Trchnicolour", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[2]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Zos kia cultus", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[3]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Inferno", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[4]/div/div/div[2]/div/h2/a"));
    $this->select("id=edit-sort", "label=Sort by: Date (Ascending)");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Sprache als Herrschaft : semiotische Kritik des \"Guten Menschen von Sezuan\", der Theorie Brechts und der literarischen Wertung", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Zos kia cultus", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[2]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Inferno", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[3]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Trchnicolour", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[4]/div/div/div[2]/div/h2/a"));
    $this->select("id=edit-sort", "label=Sort by: Date (Descending)");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Trchnicolour", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Inferno", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[2]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Zos kia cultus", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[3]/div/div/div[2]/div/h2/a"));
    $this->assertEquals("Sprache als Herrschaft : semiotische Kritik des \"Guten Menschen von Sezuan\", der Theorie Brechts und der literarischen Wertung", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[4]/div/div/div[2]/div/h2/a"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
?>
