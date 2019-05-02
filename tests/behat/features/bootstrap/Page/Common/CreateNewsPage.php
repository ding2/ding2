<?php
/**
 * @file
 * Implements the admin page for news page creation.
 */

namespace Page\Common;

use Behat\Mink\Element\NodeElement;
use SensioLabs\Behat\PageObjectExtension\PageObject\Exception\ElementNotFoundException;
use SensioLabs\Behat\PageObjectExtension\PageObject\Page;

/**
 * Class CreateNewsPage
 */
class CreateNewsPage extends Page {
  protected $path = '/node/add/ding-news';

  protected $elements = array(
    'Create form' => 'form#ding-news-node-form',
    'Category select' => 'select#edit-field-ding-news-category-und',
    'Submit' => 'input#edit-workflow-2',
  );

  /**
   * Open news page
   */
  public function openNewsPage() {
    $this->open();
  }

  /**
   * Fill news content
   *
   * @param string $title
   *   The news title.
   * @param string $lead
   *   The news lead.
   * @param string $body
   *   The new body.
   * @param string $category
   *   The news category.
   *
   * @throws \Behat\Mink\Exception\ElementNotFoundException
   *   If any of the form elements are not found.
   */
  public function fillNewsContent($title, $lead, $body, $category) {
    $form = $this->getElement('Create form');

    $form->fillField('edit-title', $title);
    $form->fillField('edit-field-ding-news-lead-und-0-value', $lead);

    // For Wysiwyg fields we need to use CkeEditor to fill the fill
    $bodyId = 'edit-field-ding-news-body-und-0-value';
    $script = sprintf('CKEDITOR.instances["%s"].setData("%s");', $bodyId, $body);
    $this->getSession()->executeScript($script);

    $typeSelect = $this->getElement('Category select');
    $typeSelect->selectOption($category);
  }

  /**
   * Set campaign keywords
   *
   * @param string $keywords
   *   The campaign keywords in a comma separated list.
   *
   * @throws \Behat\Mink\Exception\ElementNotFoundException
   *   If the form element is not found.
   */
  public function setCampaignKeywords($keywords) {
    $form = $this->getElement('Create form');

    $form->checkField('edit-ding-campaign-plus-auto-generate-enable');
    $form->fillField('edit-ding-campaign-plus-auto-generate-keywords', $keywords);
  }

  /**
   * Save news page
   *
   * @return NodeElement
   */
  public function submitNewsPage() {
    $submit = $this->getElement('Submit');
    $submit->click();

    return $this->getPage('Content Page')->waitFor(3, function ($page) {
      return $page->find('css', 'html');
    });
  }
}
