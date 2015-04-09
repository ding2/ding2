<?php

require_once(__DIR__ . '/autoload.php');

class ItemPageRelations extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstraction;
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
    $this->open("/" . $this->config->getLocale() . '/ting/collection/870970-basis:27267912');
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userMakeSearch('Rom : i Vilhelm Bergsøes');

    // Check the item title.
    $this->assertElementContainsText('css=li.list-item.search-result:first .group_ting_right_col_search .heading a', 'Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo');
    // Click on title.
    $this->click("css=li.list-item.search-result:first .group_ting_right_col_search .heading a");
    $this->abstractedPage->waitForPage();
    // Check the item title on the landing page.
    $this->assertElementContainsText('css=div.ting-object.view-mode-full .field-name-ting-title a', 'Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo');

    // The item should contain three reviews.
    // CSS selector would return nothing since the ID is malformed (contains ':').
    $this->assertTrue($this->isElementPresent("//div[@id='dbcaddi:hasReview']/div"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[1]"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[1]/a"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[2]"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[2]/a"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[3]"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[3]/a"));

    // Check relation anchors block.
    $this->assertTrue($this->isElementPresent('css=.pane-ting-ting-relation-anchors'));
    // Check that there are actully 3 reviews.
    $this->assertElementContainsText('css=.pane-ting-ting-relation-anchors .pane-content ul li.first a', 'Review (3)');

    // Check we are located on that single type of that item.
    $this->assertElementContainsText('css=.pane-ting-ting-object-types .pane-content ul li.first a', 'Bog (1)');

    // Check local review link.
    $this->click('css=.ting-object-related-item:last a');
    $this->abstractedPage->waitForPage();
    $this->assertElementContainsText('css=h1.page-title', 'Lektørudtalelse');

    // Go back and check anchor link.
    $this->open("/ting/object/870970-basis%3A50676927");
    $this->abstractedPage->waitForPage();
    $this->click('css=.pane-ting-ting-relation-anchors .pane-content ul li.first a');
    $this->assertTrue((bool) preg_match('/^[\s\S]*ting\/object\/870970-basis%3A50676927#dbcaddi:hasReview$/', $this->getLocation()));
  }

  /**
   * Test related materials as logged in user.
   *
   * @see testOtherMaterialsAnonymous()
   */
  public function testOtherMaterialsLoggedIn() {
    $this->open("/" . $this->config->getLocale());
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    $this->testOtherMaterialsAnonymous();
  }
}
