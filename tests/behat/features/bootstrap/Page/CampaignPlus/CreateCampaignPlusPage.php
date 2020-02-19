<?php
/**
 * @file
 * Implements the admin page for campaign plus creation.
 */

namespace Page\CampaignPlus;

use Behat\Mink\Element\NodeElement;
use Behat\Mink\Exception\ExpectationException;
use Behat\Mink\Exception\ElementNotFoundException;
use SensioLabs\Behat\PageObjectExtension\PageObject\Page;

/**
 * Class CreateCampaignPlusPage
 */
class CreateCampaignPlusPage extends Page {

  private $basicCampaignTriggerRulesAdded = 0;
  private $facetCampaignTriggerRulesAdded = 0;

  protected $path = '/node/add/ding-campaign-plus';

  protected $elements = array(
    'Create form' => 'form#ding-campaign-plus-node-form',
    'Campaign Title' => 'input#edit-title',
    'Campaign Text' => 'textarea#edit-field-ding-campaign-plus-text-und-0-value',
    'Campaign Link' => 'input#edit-field-ding-campaign-plus-link-und-0-url',
    'Type select' => 'select#edit-field-ding-campaign-plus-type-und',
  );

  /**
   * Fill Campaign content
   *
   * @param string $title
   *   The campaign title.
   * @param string $type
   *   The campaign type.
   * @param string $text
   *   The campaign text.
   * @param string $link
   *   The campaign link.
   * @param string $style
   *   The campaign style.
   *
   * @throws ElementNotFoundException
   *   If any of the forms elements are not found.
   */
  public function fillCampaignContent($title, $type, $text, $link, $style) {
    $form = $this->getElement('Create form');
    $typeSelect = $this->getElement('Type select');
    $typeSelect->selectOption($type);

    $this->getElement('Campaign Title')->setValue($title);
    $this->getElement('Campaign Text')->setValue($text);
    $this->getElement('Campaign Link')->setValue($link);

    $radioButton = $form->find('named', ['radio', $style]);
    $select = $radioButton->getAttribute('name');
    $option = $radioButton->getAttribute('value');
    $this->selectFieldOption($select, $option);
  }

  /**
   * Select campaign type
   *
   * @param string $type
   *   The type of campaign.
   */
  public function selectCampaignType($type) {
    switch ($type) {
      case 'facet':
        $tabButtonNumber = 0;
        break;

      case 'basic':
        $tabButtonNumber = 1;
        break;

      case 'object_view':
        $tabButtonNumber = 2;
        break;

      case 'search':
        $tabButtonNumber = 3;
        break;

      default:
        throw new UnexpectedValueException('Unknown Campaign Type: ' . $type);
    }

    $tab = $this->find('css', '.horizontal-tab-button-' . $tabButtonNumber);
    $tab->click();
  }

  /**
   * Add basic campaign trigger
   *
   * @param string $type
   *   The rule type of the basic campaign.
   * @param string $ruleValue
   *   The value of the rule.
   *
   * @throws ExpectationException
   * @throws ElementNotFoundException
   */
  public function addBasicCampaignTriggerRule($type, $ruleValue) {
    $this->selectCampaignType('basic');

    if ($this->basicCampaignTriggerRulesAdded > 0) {
      $addAnother = $this->find('xpath', '//input[contains(@id,\'edit-tabs-basic-rules-add-rule\')]');
      $addAnother->click();

      // Wait for ajax call to complete for new element to be available.
      $ruleElement = $this->waitFor(1, function ($page) {
        return $page->find('css', '.edit-tabs-basic-rules-rule-' . $this->basicCampaignTriggerRulesAdded);
      });

      if (!$ruleElement) {
        throw new ExpectationException(sprintf('Failed to add basic campaign trigger rule %d to the campaign', $this->basicCampaignTriggerRulesAdded));
      }
    }

    $form = $this->getElement('Create form');

    $selectLocator = sprintf('edit-tabs-basic-rules-rule-%d-type', $this->basicCampaignTriggerRulesAdded);
    $fieldLocator = sprintf('edit-tabs-basic-rules-rule-%d-value', $this->basicCampaignTriggerRulesAdded);

    $form->selectFieldOption($selectLocator, $type);
    $form->fillField($fieldLocator, $ruleValue);

    $autocomplete = $this->waitFor(1, function ($page) {
      return $page->find('css', '#autocomplete li');
    });
    $autocomplete->click();

    $this->basicCampaignTriggerRulesAdded++;
  }

  /**
   * Add facet campaign trigger
   *
   * @param string $type
   *   The type of facet.
   * @param string $ruleValue
   *   The facet value.
   * @param string $commmonValue
   *   The common value wherein facet value is contained to trigger campaign.
   *
   * @throws ElementNotFoundException
   *   If either of the from elements are not found.
   */
  public function addFacetCampaignTriggerRule($type, $ruleValue, $commmonValue) {
    $this->selectCampaignType('facet');

    if ($this->facetCampaignTriggerRulesAdded > 0) {
      $addAnother = $this->find('xpath', '//input[contains(@id,\'edit-tabs-facet-rules-add-rule\')]');
      $addAnother->click();

      // Wait for ajax call to complete for new element to be available.
      $ruleElement = $this->waitFor(2, function ($page) {
        return $page->find('css', '.edit-tabs-facet-rules-rule-' . $this->facetCampaignTriggerRulesAdded);
      });

      if (!$ruleElement) {
        throw new ElementNotFoundException(sprintf('Failed to add facet campaign trigger rule %d to the campaign', $this->facetCampaignTriggerRulesAdded));
      }
    }

    $form = $this->getElement('Create form');

    $selectLocator = sprintf('edit-tabs-facet-rules-rule-%d-facet', $this->facetCampaignTriggerRulesAdded);
    $commonLocator = sprintf('edit-tabs-facet-rules-rule-%d-common', $this->facetCampaignTriggerRulesAdded);
    $fieldLocator = sprintf('edit-tabs-facet-rules-rule-%d-facet-value', $this->facetCampaignTriggerRulesAdded);
    $valueSelectLocator = sprintf('edit-tabs-facet-rules-rule-%d-facet-value-select-type', $this->facetCampaignTriggerRulesAdded);

    $form->selectFieldOption($selectLocator, $type);
    $form->selectFieldOption($commonLocator, $commmonValue);

    // Form is dynamic. For 'Materialetype' a multiselect field is shown, otherwise a text field.
    if ($type === 'Materialetype') {
      $form->selectFieldOption($valueSelectLocator, $ruleValue);
    } else {
      $form->fillField($fieldLocator, $ruleValue);
    }

    $this->facetCampaignTriggerRulesAdded++;
  }

  /**
   * Set operand for facet campaign triggers
   *
   * @param string $operand
   *   The operand whereby facet triggers are combined.
   *
   * @throws ElementNotFoundException
   *   If either form element is not found.
   */
  public function setFacetCampaignTriggerOperand($operand) {
    if (!in_array($operand, ['og', 'eller'])) {
      throw new UnexpectedValueException('Unknown operand: ' . $operand);
    }
    $form = $this->getElement('Create form');
    $form->selectFieldOption('edit-tabs-facet-rules-operator', $operand);
  }

  /**
   * Set object view trigger
   *
   * @param string $query
   *   The query that should trigger campaign on object view.
   *
   * @throws ElementNotFoundException
   *   If the form element is not found.
   */
  public function setObjectViewCampaignTrigger($query) {
    $this->selectCampaignType('object_view');

    $form = $this->getElement('Create form');
    $form->fillField('edit-tabs-object-rules-query', $query);
  }

  /**
   * Set search campaign trigger
   *
   * @param string $query
   *   The query that should trigger the campaign.
   *
   * @throws ElementNotFoundException
   *   If the form element is not found.
   */
  public function setSearchCampaignTrigger($query) {
    $this->selectCampaignType('search');

    $form = $this->getElement('Create form');
    $form->fillField('edit-tabs-search-rules-query', $query);
  }

  /**
   * Save campaign
   *
   * @return NodeElement
   */
  public function submitCampaign() {
    $form = $this->getElement('Create form');
    $form->submit();

    return  $this->getPage('Content Page')->waitFor(3, function ($page) {
      return $page->find('css', 'html');
    });
  }
}
