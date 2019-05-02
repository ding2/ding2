<?php

/**
 * @file
 * Campaign Plus Context defining relevant steps for campaign creation.
 */

use Behat\Gherkin\Node\TableNode;
use Behat\Mink\Exception\ExpectationException;
use Behat\MinkExtension\Context\RawMinkContext;
use Page\CampaignPlus\CreateCampaignPlusPage;
use SensioLabs\Behat\PageObjectExtension\PageObject\Page;

/**
 * Class CampaignPlusContext
 */
class CampaignPlusContext extends RawMinkContext {
  private $createCampaignPage;

  /**
   * CampaignPlusContext constructor.
   *
   * @param CreateCampaignPlusPage $createCampaignPage
   *   A 'Create Campaign' page object.
   */
  public function __construct(CreateCampaignPlusPage $createCampaignPage) {
    $this->createCampaignPage = $createCampaignPage;
  }

  /**
   * Open the "Create Campaign Plus" page
   *
   * @When /^(?:|I )go to the create campaign plus page$/
   */
  public function iGoToCreateCampaignPage() {
    $this->createCampaignPage->open();
  }

  /**
   * Fill the campaign with values from the provided table
   *
   * Example: When I fill a campaign with the following"
   *  | Title | Batman          |
   *  | Type  | Text with image |
   *  | Text  | Go Batman!      |
   *  | Link  | <front>         |
   *  | Style | Bånd            |
   *  | Tags  | Superheroes     |
   *
   * @When /^(?:|I )fill a campaign with the following:$/
   */
  public function iFillACampaignWithTheFollowing(TableNode $table) {
    foreach ($table->getRowsHash() as $field => $value) {
      switch ($field) {
        case 'Title':
          $title = $value;
          break;

        case 'Type':
          $type = $value;
          break;

        case 'Text':
          $text = $value;
          break;

        case 'Link':
          $link = $value;
          break;

        case 'Style':
          $style = $value;
          break;

        case 'Tags':
          $tags = explode(',', $value);
          break;

        default:
          throw new UnexpectedValueException('Unknown Campaign Field: ' . $field);
      }
    }

    $this->createCampaignPage->fillCampaignContent($title, $type, $text, $link, $style, $tags);
  }

  /**
   * Add basic trigger with values from the provided table
   *
   * Example: When I create a campaign with the following"
   *  | Rule type   | Side     |
   *  | Rule value  | Campaign |
   *
   * @When /^(?:|I )add a basic trigger with the following:$/
   */
  public function iAddABasicTrigger(TableNode $table) {
    foreach ($table->getRowsHash() as $field => $value) {
      switch ($field) {
        case 'Rule type':
          $ruleType = $value;
          break;

        case 'Rule value':
          $ruleValue = $value;
          break;

        default:
          throw new UnexpectedValueException('Unknown basic trigger field: ' . $field);
      }
    }

    $this->createCampaignPage->addBasicCampaignTrigger($ruleType, $ruleValue);
  }

  /**
   * Add facet trigger with values from the provided table
   *
   * Example: When I create a campaign with the following"
   *  | Facet type  | Emne |
   *  | Facet value | Børn |
   *
   * @When /^(?:|I )add a facet trigger with the following:$/
   */
  public function iAddAFacetTrigger(TableNode $table) {
    foreach ($table->getRowsHash() as $field => $value) {
      switch ($field) {
        case 'Facet type':
          $facetType = $value;
          break;

        case 'Facet value':
          $facetValue = $value;
          break;

        case 'Common value':
          $commonValue = $value;
          break;

        default:
          throw new UnexpectedValueException('Unknown facet trigger field: ' . $field);
      }
    }

    $this->createCampaignPage->addFacetCampaignTrigger($facetType, $facetValue, $commonValue);
  }

  /**
   * Set facet trigger operand
   *
   * @When /^(?:|I )set the facet trigger operand to :operand
   */
  public function iChooseFacetTriggerOperand(string $operand) {
    $this->createCampaignPage->setFacetCampaignTriggerOperand($operand);
  }

  /**
   * Add object view trigger with values from the provided table
   *
   * @When /^(?:|I )set the object view trigger with the search query :query
   */
  public function iSetTheObjectViewTrigger(string $query) {
    $this->createCampaignPage->setObjectViewCampaignTrigger($query);
  }

  /**
   * Add object view trigger with values from the provided table
   *
   * @When /^(?:|I )set the search trigger with the search query :query
   */
  public function iSetTheSearchTrigger(string $query) {
    $this->createCampaignPage->setSearchCampaignTrigger($query);
  }

  /**
   * Save the Campaign
   *
   * @When /^(?:|I )save the campaign$/
   */
  public function iSaveTheCampaign() {
    $this->createCampaignPage->submitCampaign();
  }

  /**
   * Implements step to check if a campaign is shown.
   *
   * Uses the 'jQuery.active' property to test if there are outstanding
   * ajax requests. Once all requests complete look for campaign.
   *
   * @param string $title
   *    The title of the campaign to wait for.
   *
   * @throws ExpectationException
   *    If the campaign does not appear.
   *
   * @Then the campaign :title should appear on the page
   */
  public function assertCampaignAppears(string $title) {
    $this->getSession()->getPage()->waitFor(3, function () {
      // jQuery.active holds the number of outstanding ajax requests
      return $this->getSession()->getDriver()->evaluateScript('jQuery.active === 0');
    });

    $campaignHeadings = $this->getSession()->getPage()->findAll('css', '.ding-campaign-headline');
    foreach ($campaignHeadings as $campaignHeading) {
      $textElement = $campaignHeading->find('xpath', "//text()[contains(.,'" . $title . "')]/..");
      if ($textElement && $textElement->isVisible()) {
        return;
      }
    }

    throw new ExpectationException(sprintf('The campaign "%s" did not appear on the page', $title), $this->getSession()->getDriver());
  }

  /**
   * Implements step to check if a campaign is not shown.
   *
   * Uses the 'jQuery.active' property to test if there are outstanding
   * ajax requests. Once all requests complete look for campaign.
   *
   * @param string $title
   *    The title of the campaign to wait for.

   *
   * @throws ExpectationException
   *    If the campaign does not appear.
   *
   * @Then the campaign :title should not appear on the page
   */
  public function assertCampaignDoesNotAppears(string $title) {
    $this->getSession()->getPage()->waitFor(3, function () {
      // jQuery.active holds the number of outstanding ajax requests
      return $this->getSession()->getDriver()->evaluateScript('jQuery.active === 0');
    });

    $campaignHeadings = $this->getSession()->getPage()->findAll('css', '.ding-campaign-headline');
    foreach ($campaignHeadings as $campaignHeading) {
      $textElement = $campaignHeading->find('xpath', "//text()[contains(.,'" . $title . "')]/..");
      if ($textElement && $textElement->isVisible()) {
        throw new ExpectationException(sprintf('The campaign "%s" was found , but should NOT appear', $title), $this->getSession()->getDriver());
      }
    }
  }
}
