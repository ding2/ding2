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
class LibContext implements Context, SnippetAcceptingContext {

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

  /** @var verbose
   * Holds the flags telling whether we want a very verbose run or a more silent one
   */
  public $verbose;

  /**
   * Initializes context.
   *
   * Every scenario gets its own context instance.
   * You can also pass arbitrary arguments to the
   * context constructor through behat.yml.
   */
  public function __construct() {

    // initialise the verbose structure. These are default settings.
    $this->verbose[] = (object) array (
          'searchResults' => false,
          'loginInfo' => true,
          'cookies' => false,
          'searchMaxPages' => 0,
    );

  }

  /**
   * @BeforeScenario
   *
   * @param BeforeScenarioScope $scope
   * @throws \Behat\Mink\Exception\DriverException
   */
  public function beforeScenario(BeforeScenarioScope $scope)
  {
    // Gather contexts.
    $environment = $scope->getEnvironment();
    $this->currentFeature = $scope->getFeature()->getTitle();
    $this->currentScenario = $scope->getScenario()->getTitle();

    $this->drupalContext = $environment->getContext('Drupal\DrupalExtension\Context\DrupalContext');
    $this->minkContext = $environment->getContext('Drupal\DrupalExtension\Context\MinkContext');

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


  /**
   * @Given I want verbose mode for :area to be :onoff
   * @Given I set verbose mode for :area to be :onoff
   * @Given I set control mode for :area to be :onoff
   *
   * Sets the control or verbose mode of the run, controlling how much info is put into the output log.
   */
  public function set_verbose_control_mode($area, $onoff)  {
    $area = mb_strtolower($area);
    $onoff = mb_strtolower($onoff);
    switch($area) {
      // this tells if we want to know the username we logged in with
      case 'login':
      case 'logininfo':
        $this->verbose[0]->loginInfo = $onoff;
        if ($onoff == 'on') {
          print_r("Verbose mode of loginInfo set to on");
        }
        break;
        // this indicates if we want to see in the log what was found in the searches
      case 'search-results':
      case 'search-result':
      case 'searchresults':
        $this->verbose[0]->searchResults = $onoff;
        if ($onoff == 'on') {
          print_r("Verbose mode of searchResults set to on");
        }
        break;
        // this indicates if we want to know about handling cookie-popups
      case 'cookie':
      case 'cookies':
        $this->verbose[0]->cookies = $onoff;
        if ($onoff == 'on') {
          print_r("Verbose mode of cookie-handling set to on");
        }
        break;
        // this setting controls how many search result pages we will traverse during testing
      case 'searchmaxpages':
        $this->verbose[0]->searchMaxPages = $onoff;
        # always notify the user of this setting
        print_r("Verbose mode for max number of search result pages set to " . $onoff);
        print_r("\n");
        break;
        // this is the catch-all setting
      case 'everything':
      case 'all':
        $this->verbose[0]->loginInfo = $onoff;
        $this->verbose[0]->searchResults = $onoff;
        $this->verbose[0]->cookies = $onoff;
        break;
        // if we don't recognise this, let the user know, but don't fail on it
      default:
        print_r("Unknown verbose mode:" . $area);
        print_r("\n");
        break;
    }
  }
}
