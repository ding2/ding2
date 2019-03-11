<?php

use Behat\Behat\Context\Context;
use Behat\Gherkin\Node\TableNode;
use Page\Common\CreateNewsPage;

class CreateNewsContext implements Context
{
  private $createNewsPage;

  public function __construct(CreateNewsPage $createNewsPage)
  {
    $this->createNewsPage = $createNewsPage;
  }

  /**
   * Open the "Create News" page
   *
   * @When /^(?:|I )go to the create news page$/
   */
  public function iGoToCreateNewsPage()
  {
    $this->createNewsPage->open();
  }

  /**
   * Fill a news page with values from the provided table
   * Example: When I fill a news page with the following"
   *  | Title     | Batman            |
   *  | Lead      | Superhero returns |
   *  | Body      | Go Batman!        |
   *  | Keywords  | superheroes       |
   *
   * @When /^(?:|I )fill a news page with the following:$/
   */
  public function iFillANewsPageWithTheFollowing(TableNode $table)
  {
    foreach ($table->getRowsHash() as $field => $value) {
      switch ($field) {
        case 'Title':
          $title = $value;
          break;
        case 'Lead':
          $lead = $value;
          break;
        case 'Body':
          $body = $value;
          break;
        case 'Category':
          $category = $value;
          break;
        default:
          throw new UnexpectedValueException('Unknown News Page Field: ' . $field);
      }
    }

    $this->createNewsPage->fillNewsContent($title, $lead, $body, $category);
  }

  /**
   * Set the campaign keywords to auto generate campaign
   *
   * @When I set the campaign keywords to :keywords
   */
  public function iSetCampaignKeywords(string $keywords)
  {
    $this->createNewsPage->setCampaignKeywords($keywords);
  }

  /**
   * Save the Campaign
   *
   * @When /^(?:|I )save the news page$/
   */
  public function iSaveTheNewsPage()
  {
    $this->createNewsPage->submitNewsPage();
  }

}
