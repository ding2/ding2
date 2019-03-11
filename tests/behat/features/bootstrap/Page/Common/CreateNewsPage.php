<?php
/**
 * @file
 * Implements the admin page for news page creation.
 */

namespace Page\Common;

use SensioLabs\Behat\PageObjectExtension\PageObject\Exception\ElementNotFoundException;
use SensioLabs\Behat\PageObjectExtension\PageObject\Page;

class CreateNewsPage extends Page
{
  protected $path = '/node/add/ding-news';

  protected $elements = array(
    'Create form' => 'form#ding-news-node-form',
    'Category select' => 'select#edit-field-ding-news-category-und',
    'Submit' => 'input#edit-workflow-2',
  );

  /**
   * Open news page
   */
  public function openNewsPage()
  {
    $this->open();
  }

  /**
   * Fill news content
   *
   * @param string $title
   * @param string $lead
   * @param string $body
   * @param string $category
   *
   * @throws \Behat\Mink\Exception\ElementNotFoundException
   */
  public function fillNewsContent(string $title, string $lead, string $body, string $category)
  {
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
   *
   * @throws \Behat\Mink\Exception\ElementNotFoundException
   */
  public function setCampaignKeywords(string $keywords)
  {
    $form = $this->getElement('Create form');

    $form->checkField('edit-ding-campaign-plus-auto-generate-enable');
    $form->fillField('edit-ding-campaign-plus-auto-generate-keywords', $keywords);
  }

  /**
   * Save news page
   *
   * @return mixed
   */
  public function submitNewsPage()
  {
    $submit = $this->getElement('Submit');
    $submit->click();

    return $this->getPage('Content Page')->waitFor(3, function ($page) {
      return $page->find('css', 'html');
    });
  }
}
