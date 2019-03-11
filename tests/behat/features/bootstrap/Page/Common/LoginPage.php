<?php
/**
 * @file
 * Implements the admin page for campaign creation.
 */

namespace Page\Common;

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
   * @param \stdClass $user
   *   A std objecy containing 'name' and 'pass' properties.
   *
   * @return mixed
   *   A 'Login Page' object.
   *
   * @throws \Behat\Mink\Exception\ElementNotFoundException
   *   If login form elements not found.
   */
  public function login(\stdClass $user) {
    $this->open();

    $this->waitFor(3, function ($page) {
      $jsButton = $page->find('css', 'a.js-topbar-link.topbar-link-user');
      if (!empty($jsButton) && $jsButton->isVisible()) {
        // We need to wait further for javascript to attach and intercept the click
        // event on the link.
        // @TODO find a condition we van test for?
        usleep(500000);
        $jsButton->mouseOver();
        $jsButton->click();
      }

      $form = $page->find('css', 'form#user-login-form');

      return $form->isVisible();
    });

    $form = $this->getElement('Login Form');
    $form->fillField('edit-name', $user->name);
    $form->fillField('edit-pass', $user->pass);
    $form->submit();

    return $this->getPage('Login Page')->waitFor(3, function ($page) {
      return $page->find('css', '.pane-current-user-name');
    });
  }
}
