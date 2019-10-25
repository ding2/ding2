<?php

/**
 * @file
 * Login Context defining relevant steps for login by role.
 */

use Behat\Mink\Exception\DriverException;
use Behat\Mink\Exception\ElementNotFoundException;
use Behat\Mink\Exception\UnsupportedDriverActionException;
use Drupal\DrupalExtension\Context\RawDrupalContext;
use Page\Common\LoginPage;

/**
 * Class LoginContext
 */
class LoginContext extends RawDrupalContext {

  private $loginPage;

  /**
   * LoginContext constructor.
   *
   * @param LoginPage $loginPage
   *   A 'Login Page' page object.
   */
  public function __construct(LoginPage $loginPage) {
    $this->loginPage = $loginPage;
  }

  /**
   * Creates and authenticates a cms user with the given role(s).
   *
   * @param string $roleList
   *   A comma separated string of the roles the user needs, e.g. 'administrators, editor'
   *
   * @throws DriverException
   * @throws ElementNotFoundException
   * @throws UnsupportedDriverActionException
   *
   * @Given I am logged in as a cms user with the :roleList role(s)
   */
  public function assertAuthenticatedByRole(string $roleList) {
    $user = (object) array(
      'name' => $this->getRandom()->name(8),
      'pass' => $this->getRandom()->name(16),
      'role' => $roleList,
    );
    $user->mail = "{$user->name}@ding2.example";

    $this->userCreate($user);

    $roles = explode(',', $roleList);
    $roles = array_map('trim', $roles);
    foreach ($roles as $role) {
      if (!in_array(strtolower($role), array('authenticated', 'authenticated user'))) {
        // Only add roles other than 'authenticated user'.
        $this->getDriver()->userAddRole($user, $role);
      }
    }

    $this->loginPage->login($user->name, $user->pass);
  }
}
