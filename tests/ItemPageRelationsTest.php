<?php

class ItemPageRelationsTest extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstractedPage;
  protected $config;

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();

    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
  }

  /**
   * Test related materials of a certain item as anonymous.
   *
   * Assume item has related materials (reviews, etc.), pointing
   * to remote resources.
   */
  public function testOtherMaterialsAnonymous() {
    $this->open('/' . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userMakeSearch('dorthe nors');

    // Check the item title on search result page.
    $this->assertTrue($this->isElementPresent('link=Stormesteren'));
    // Click on title. Goes to collection page.
    $this->click('link=Stormesteren');
    $this->abstractedPage->waitForPage();
    sleep(5);
    // Check the item title on the collection page.
    $this->assertTrue($this->isElementPresent('link=Stormesteren : roman'));
    sleep(5);
    // Click on title. Goes to item page.
    $this->click('link=Stormesteren : roman');
    $this->abstractedPage->waitForPage();

    // The item should contain 1 (one) author portrait.
    // CSS selector would return nothing since the ID is malformed (contains ':').
    $this->assertTrue($this->isElementPresent('//div[@id="dbcaddi:hasCreatorDescription"]/div'));
    $this->assertTrue($this->isElementPresent('//div[@id="dbcaddi:hasCreatorDescription"]/div/div[1]'));
    $this->assertTrue($this->isElementPresent('//div[@id="dbcaddi:hasCreatorDescription"]/div/div[1]/a'));

    // The item should contain 7 (seven) reviews.
    // CSS selector would return nothing since the ID is malformed (contains ':').
    $this->assertTrue($this->isElementPresent('//div[@id="dbcaddi:hasReview"]/div'));
    for ($i = 1; $i <= 7; $i++) {
      $this->assertTrue($this->isElementPresent('//div[@id="dbcaddi:hasReview"]/div/div[' . $i . ']'));
    }

    // Check relation anchors block.
    $this->assertTrue($this->isElementPresent('css=.pane-ting-ting-relation-anchors'));
    // Check that there is one author portrail link.
    $this->assertTrue($this->isElementPresent('link=Author portrait (2)'));
    // Check that there are actully 7 (seven) review links.
    $this->assertTrue($this->isElementPresent('link=Review (7)'));

    // Check local review link.
    $this->click('css=.ting-object-related-item:last a');
    // $this->abstractedPage->waitForPage();
    sleep(5);
    // $this->assertElementContainsText('css=h1.page-title', 'Dorthe Nors');

    // Go back and check anchor links.
    $this->open('/'.$this->config->getLocale().'/ting/object/870970-basis%3A24908941');
    // $this->abstractedPage->waitForPage();
    sleep(5);
    $this->click('link=Author portrait (2)');
    $this->assertTrue((bool) preg_match('/^[\s\S]*ting\/object\/870970-basis%3A24908941#dbcaddi:hasCreatorDescription$/', $this->getLocation()));
    $this->click('link=Review (7)');
    $this->assertTrue((bool) preg_match('/^[\s\S]*ting\/object\/870970-basis%3A24908941#dbcaddi:hasReview$/', $this->getLocation()));
  }

  /**
   * Test related materials as logged in user.
   *
   * @see testOtherMaterialsAnonymous()
   */
  public function testOtherMaterialsLoggedIn() {
    $this->open('/' . $this->config->getLocale());
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    $this->testOtherMaterialsAnonymous();
  }
}
