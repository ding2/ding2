<?php
/**
 * @file
 * Implements the admin page for campaign creation.
 */

namespace Page\Common;

use Behat\Mink\Element\NodeElement;
use Behat\Mink\Exception\ElementNotFoundException;
use SensioLabs\Behat\PageObjectExtension\PageObject\Page;

/**
 * Class LoginPage
 */
class LoginPage extends Page {
  protected $path = '/';

  protected $elements = array(
    'Login Form' => 'form#user-login-form',
  );

  /**
   * Perform login with given user
   *
   * @param string $username
   *   The username of the account
   * @param string $password
   *   The password for the account
   *
   * @return NodeElement
   *
   * @throws ElementNotFoundException
   */
  public function login(string $username, string $password): NodeElement
  {
    $this->open();

    $form = $this->getElement('Login Form');
    $form->fillField('edit-name', $username);
    $form->fillField('edit-pass', $password);
    $form->submit();

    return $this->getPage('Login Page')->waitFor(3, static function ($page) {
      return $page->find('css', '.pane-current-user-name');
    });
  }
}
