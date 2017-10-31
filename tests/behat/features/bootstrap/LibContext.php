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

  /** @var holding css-locator strings */
  public $cssStr;

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
    $this->verbose = (object) array (
          'searchResults' => false,
          'loginInfo' => true,
          'cookies' => false,
          'searchMaxPages' => 0,
    );

    $this->cssStr['button_agree'] = '.agree-button';
    $this->cssStr['button_asklibrarian'] = '.ask-vopros-minimize span';


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
   * @Given I accept cookies
   *
   * @throws Exception
   * Checks if cookie acceptance is shown, and accepts it if it is.
   */
  public function handle_cookie_ask_librarian_overlay()
  {
    // check if there's a cookie thing showing:
    $cookieAgree = $this->getPage()->find('css', $this->cssStr['button_agree']);
    if ($cookieAgree) {
      $this->log_msg(($this->verbose->cookies=='on'), "Cookie accept-besked vises.\n");
      $this->log_timestamp(($this->verbose->cookies=='on'), "Start: ");

      // now timing wise this is tricky, because the overlay moves. There seems to be no way to
      // catch it while moving, so we try to click it until that actually works. Selenium always
      // clicks in the middle of the element.
      // We try at most 50 times. That will work for even very slow systems. Typically only one wait cycle is necessary.
      $max=50;
      $success=false;
      while(--$max>0 && !$success) {
        try {
          $cookieAgree = $this->getPage()->find('css', $this->cssStr['button_agree']);

          $cookieAgree->click();
          // we will only ever execute this if the cookie button is clickable
          $success = true;

        } catch (Exception $e) {
          // give it a bit more time to come into place.
          usleep(100);
        }
      }
      if(!$success) {
        throw new Exception ("Cookie Agree-knap kunne ikke klikkes væk.");
      }

      $this->log_msg(($this->verbose->cookies=='on'), "Slut: ");

      // now we have clicked it, we expect it to go away within at the most 10 secs.
      $maxwait=330;
      $cookieAgree = $this->getPage()->find('css', $this->cssStr['button_agree']);
      while ($cookieAgree and --$maxwait > 0) {
        usleep(300);
        // refresh the search on the page
        $cookieAgree = $this->getPage()->find('css', $this->cssStr['button_agree']);
      }
    }
    $this->log_msg(($this->verbose->cookies == 'on'), "Ventede på at cookie forsvandt: " . ((330 - $maxwait)*300) . " millisecs\n");

    // now minimize the "Spørg biblioteksvagten"
    // @todo: this should probably be a separate function
    $askLibrary = $this->getPage()->find('css', $this->cssStr['button_asklibrarian']);
    if ($askLibrary) {
      $this->log_msg(($this->verbose->cookies == "on"), "Spørg biblioteksvagten var centreret. Klikker den til minimeret tilstand.\n");
      // simply click, and ignore if it can't click.
      try {
        $askLibrary->click();
        usleep(100);
      }  catch (UnsupportedDriverActionException $e) {
        // Ignore.
      } catch (Exception $e) {
        // Ignore too
      }
      // We will wait a bit until it goes away
      $max = 10;
      while ($askLibrary && --$max>0) {

        // renew our view on the page
        $askLibrary = $this->getPage()->find('css', $this->cssStr['button_asklibrarian']);

      }
      if ($askLibrary) {
        throw new Exception ("Spørg Bibliotekaren gik ikke væk.");
      }
    }
  }

  /**
   * getPage - quick reference to the getPage element. Makes code more readable.
   *
   * @return \Behat\Mink\Element\DocumentElement
   */
  public function getPage() {
    return $this->minkContext->getSession()->getPage();
  }

  /**
   * log_msg - prints message on log if condition is true.
   *
   * @param $ifTrue
   * @param $msg
   */
  public function log_msg($ifTrue, $msg) {
    if ($ifTrue) {
      print_r($msg);
    }
  }

  /**
   * log_timestamp - puts a timestamp in the log. Good for debugging timing issues.
   * @param $ifTrue
   * @param $msg
   */
  public function log_timestamp($ifTrue, $msg) {
    // this is so we can use this function with verbose-checking
    if ($ifTrue) {
      // get the microtime, format it and print it.
      $t = microtime(true);
      $micro = sprintf("%06d",($t - floor($t)) * 1000000);
      $d = new DateTime( date('Y-m-d H:i:s.'.$micro, $t) );
      print_r($msg . " " . $d->format("Y-m-d H:i:s.u") . "\n");
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
