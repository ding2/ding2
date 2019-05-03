<?php
/**
 * @file
 * Implements the admin page for campaign creation.
 */

namespace Page\Common;

use Behat\Mink\Element\NodeElement;
use Behat\Mink\Exception\DriverException;
use Behat\Mink\Exception\ElementNotFoundException;
use Behat\Mink\Exception\UnsupportedDriverActionException;
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
   * @throws DriverException
   * @throws ElementNotFoundException
   * @throws UnsupportedDriverActionException
   */
  public function login(string $username, string $password) {
    $this->open();

    // All forms are protected by the antibot module. The module uses
    // javascript to set all form actions to '/antibot', then reset
    // them to the original value when 'human' interaction is detected.
    // Given that behat/mink interaction doesn't qualify as 'human' we
    // need to wait for the antibot javascript module to load, then call
    // its 'unlockForms()' before we submit the login form.
    $this->waitFor(3, function (Page $page) {
      return $page->getDriver()->evaluateScript('typeof(Drupal) !== "undefined" && typeof(Drupal.antibot) !== "undefined"');
    });
    $this->getDriver()->evaluateScript('Drupal.antibot.unlockForms()');

    $form = $this->getElement('Login Form');
    $form->fillField('edit-name', $username);
    $form->fillField('edit-pass', $password);
    $form->submit();

    return $this->getPage('Login Page')->waitFor(3, function ($page) {
      return $page->find('css', '.pane-current-user-name');
    });
  }
}
