<?php

use Behat\Behat\Context\Context;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;
use Behat\Mink\Element\ElementInterface;
use Behat\MinkExtension\Context\MinkContext;
use Behat\Mink\Driver\Selenium2Driver;
use Behat\Mink\Exception\UnsupportedDriverActionException;

/**
 * Defines application features from the specific context.
 */
class Ding2Context implements Context, SnippetAcceptingContext {

  /**
   * Current authenticated user.
   *
   * A value of FALSE denotes an anonymous user.
   *
   * @var stdClass|bool
   */
  public $user = FALSE;

  /** @var \Drupal\DrupalExtension\Context\DrupalContext */
  public $drupalContext;

  /** @var \Drupal\DrupalExtension\Context\MinkContext */
  public $minkContext;

  /** @BeforeScenario */
  public function beforeScenario(BeforeScenarioScope $scope)
  {
    // Gather contexts.
    $environment = $scope->getEnvironment();
    $this->currentFeature = $scope->getFeature()->getTitle();
    $this->currentScenario = $scope->getScenario()->getTitle();

    $this->drupalContext = $environment->getContext('Drupal\DrupalExtension\Context\DrupalContext');
    $this->minkContext = $environment->getContext('Drupal\DrupalExtension\Context\MinkContext');
    # caf $this->minkContext = $environment->getContext('Behat\MinkExtension\Context');
    #$this->markupContext = $environment->getContext('Behat\MinkExtension\Context\MinkContext');
    try {
      $this->ding2MessagesContext = $environment->getContext('Ding2MessagesContext');
    } catch (Exception $e) {
      // Ingore.
    }

    // Try to set a default window size. 
    try {
      $this->minkContext->getSession()
            ->getDriver()
            ->resizeWindow(1024, 768, 'current');
    } catch (UnsupportedDriverActionException $e) {
      // Ignore, but make a note of it for the tester
      print_r("Before Scenario: resizeWindow fejlede. \n");
    }
  }


}
