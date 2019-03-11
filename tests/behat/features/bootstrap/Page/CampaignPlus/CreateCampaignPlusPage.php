<?php
/**
 * @file
 * Implements the admin page for campaign plus creation.
 */

namespace Page\CampaignPlus;

use SensioLabs\Behat\PageObjectExtension\PageObject\Exception\ElementNotFoundException;
use SensioLabs\Behat\PageObjectExtension\PageObject\Page;

class CreateCampaignPlusPage extends Page
{
  private $basicCampaignTriggersAdded = 0;
  private $facetCampaignTriggersAdded = 0;

  protected $path = '/node/add/ding-campaign-plus';

  protected $elements = array(
    'Create form' => 'form#ding-campaign-plus-node-form',
    'Type select' => 'select#edit-field-ding-campaign-plus-type-und',
  );

  /**
   * Open Create Campaign page
   */
  public function openCampaign()
  {
    $this->open();
  }

  /**
   * Fill Campaign content
   *
   * @param string $title
   * @param string $type
   * @param string $text
   * @param string $link
   * @param string $style
   * @param array $tags
   *
   * @throws \Behat\Mink\Exception\ElementNotFoundException
   */
  public function fillCampaignContent(string $title, string $type, string $text, string $link, string $style, array $tags = ['campaign'])
  {
    $form = $this->getElement('Create form');
    $typeSelect = $this->getElement('Type select');
    $typeSelect->selectOption($type);

    $form->fillField('edit-title', $title);
    $form->fillField('edit-field-ding-campaign-plus-text-und-0-value', $text);
    $form->fillField('edit-field-ding-campaign-plus-link-und-0-url', $link);

    $radioButton = $this->find('named', ['radio', $style]);
    $select = $radioButton->getAttribute('name');
    $option = $radioButton->getAttribute('value');
    $this->selectFieldOption($select, $option);

    $form->fillField('edit-field-ding-campaign-plus-track-und-0-value', implode(',', $tags));
  }

  /**
   * Select campaign type
   *
   * @param string $type
   */
  public function selectCampaignType(string $type)
  {
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

    $tab = $this->find('css', '.horizontal-tab-button-' . $tabButtonNumber );
    $tab->click();
  }

  /**
   * Add basic campaign trigger
   *
   * @param string $type
   * @param string $ruleValue
   *
   * @throws \Behat\Mink\Exception\ElementNotFoundException
   */
  public function addBasicCampaignTrigger(string $type, string $ruleValue)
  {
    $this->selectCampaignType('basic');

    if ($this->basicCampaignTriggersAdded > 0) {
      $addAnother = $this->find('xpath', '//input[contains(@id,\'edit-tabs-basic-rules-add-rule\')]');
      $addAnother->click();

      // Wait for ajax call to complete for new element to be availiable
      $ruleElement = $this->waitFor(1, function ($page) {
        return $page->find('css', '.edit-tabs-basic-rules-rule-' . $this->basicCampaignTriggersAdded);
      });

      if(!$ruleElement) {
        throw new ElementNotFoundException(sprintf('Failed to add rule %d to the campaign', $this->facetCampaignTriggersAdded));
      }
    }

    $form = $this->getElement('Create form');

    $selectLocator = sprintf('edit-tabs-basic-rules-rule-%d-type', $this->basicCampaignTriggersAdded);
    $fieldLocator = sprintf('edit-tabs-basic-rules-rule-%d-value', $this->basicCampaignTriggersAdded);

    $form->selectFieldOption($selectLocator, $type);
    $form->fillField($fieldLocator, $ruleValue);

    $autocomplete = $this->waitFor(1, function ($page) {
      return $page->find('css', '#autocomplete li');
    });
    $autocomplete->click();

    $this->basicCampaignTriggersAdded++;
  }

  /**
   * Add facet campaign trigger
   *
   * @param string $type
   * @param string $ruleValue
   * @param string $commmonValue
   *
   * @throws \Behat\Mink\Exception\ElementNotFoundException
   */
  public function addFacetCampaignTrigger(string $type, string $ruleValue, string $commmonValue)
  {
    $this->selectCampaignType('facet');

    if ($this->facetCampaignTriggersAdded > 0) {
      $addAnother = $this->find('xpath', '//input[contains(@id,\'edit-tabs-basic-rules-add-rule\')]');
      $addAnother->click();

      // Wait for ajax call to complete for new element to be availiable
      $ruleElement = $this->waitFor(2, function ($page) {
        return $page->find('css', '.edit-tabs-facet-rules-rule-' . $this->facetCampaignTriggersAdded);
      });

      if(!$ruleElement) {
        throw new ElementNotFoundException(sprintf('Failed to add rule %d to the campaign', $this->facetCampaignTriggersAdded));
      }
    }

    $form = $this->getElement('Create form');

    $selectLocator = sprintf('edit-tabs-facet-rules-rule-%d-facet', $this->facetCampaignTriggersAdded);
    $commonLocator = sprintf('edit-tabs-facet-rules-rule-%d-common', $this->facetCampaignTriggersAdded);
    $fieldLocator = sprintf('edit-tabs-facet-rules-rule-%d-facet-value', $this->facetCampaignTriggersAdded);
    $valueSelectLocator = sprintf('edit-tabs-facet-rules-rule-%d-facet-value-select-type', $this->facetCampaignTriggersAdded);

    $form->selectFieldOption($selectLocator, $type);
    $form->selectFieldOption($commonLocator, $commmonValue);

    // Form is dynamic. For 'Materialetype' a multiselect field is shown, otherwise a text field
    if($type === 'Materialetype') {
      $form->selectFieldOption($valueSelectLocator, $ruleValue);
    } else {
      $form->fillField($fieldLocator, $ruleValue);
    }

    $this->facetCampaignTriggersAdded++;
  }

  /**
   * Set operand for facet campaign triggers
   *
   * @param string $operand
   *
   * @throws \Behat\Mink\Exception\ElementNotFoundException
   */
  public function setFacetCampaignTriggerOperand(string $operand)
  {
    if(!in_array($operand, ['og', 'eller'])) {
      throw new UnexpectedValueException('Unknown operand: ' . $operand);
    }
    $form = $this->getElement('Create form');
    $form->selectFieldOption('edit-tabs-facet-rules-operator', $operand);
  }

  /**
   * Set object view trigger
   *
   * @param string $query
   *
   * @throws \Behat\Mink\Exception\ElementNotFoundException
   */
  public function setObjectViewCampaignTrigger(string $query)
  {
    $this->selectCampaignType('object_view');

    $form = $this->getElement('Create form');
    $form->fillField('edit-tabs-object-rules-query', $query);
  }

  /**
   * Set search campaign trigger
   *
   * @param string $query
   *
   * @throws \Behat\Mink\Exception\ElementNotFoundException
   */
  public function setSearchCampaignTrigger(string $query)
  {
    $this->selectCampaignType('search');

    $form = $this->getElement('Create form');
    $form->fillField('edit-tabs-search-rules-query', $query);
  }

  /**
   * Save campaign
   *
   * @return mixed
   */
  public function submitCampaign()
  {
    $form = $this->getElement('Create form');
    $form->submit();

    return $this->getPage('Content Page')->waitFor(3, function ($page) {
      return $page->find('css', 'html');
    });
  }
}