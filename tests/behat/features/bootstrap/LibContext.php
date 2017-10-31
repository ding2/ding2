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

  /** @var $cssStr
   * is holding css-locator strings
   */
  public $cssStr;

  /** @var $verbose
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
   * @Given I am logged in as a library user
   * @When I log in as a library user
   */
  public function iAmLoggedInAsALibraryUser()
  {

    // temporary solution, setting up hardcoded username list. Password is last 4 for Connie Provider
    $userlist = array ();
    $userlist[] = 'Lillekvak';
    $userlist[] = 'Supermand';
    $userlist[] = 'Fernando';
    $userlist[] = 'Georgina';
    $userlist[] = 'Henrietta';
    $userlist[] = 'Ibenholt';
    $userlist[] = 'Jepardy';
    $userlist[] = 'Karolina';
    $userlist[] = 'Louisette';
    $userlist[] = 'Marionette';
    $userlist[] = 'Nielsette';
    $userlist[] = 'Ottomand';
    $userlist[] = 'Pegonia';

    // now pick a random one.
    $name = $userlist[random_int(0, count($userlist)-1)];

    // set up the user:
    $user = (object) array(
          'name' => $name,
          'pass' => substr($name, -4),
    );
    $this->drupalContext->user = $user;
    $this->login();

    // We need the user uid for various reasons, however it's not easily
    // available. Apparently the only place it makes an appearance
    // nowadays is in a class on the body element of the user page. So try
    // to dig it out from there.
    $this->drupalContext->getSession()->visit($this->drupalContext->locatePath('/user'));

    $body = $this->getPage()->find('css', 'body');
    if (!$body) {
      throw new Exception('Kunne ikke hente brugerens side.');
    }
    $classes = explode(' ', $body->getAttribute('class'));
    foreach ($classes as $class) {
      if (preg_match('{^page-user-(\d+)$}', $class, $matches)) {
        $user->uid = $matches[1];
        break;
      }
    }
    if (!$user->uid) {
      throw new Exception('Kunne ikke hente brugerens UID fra brugerens side.');
    }

    // In addition, make a note of the "id" that is used in paths (which
    // is most often "me"), so we can construct paths as would be
    // expected. We're sniffing this rather than hardcoding it because
    // some users are except from the "me" replacement.
    $link = $this->drupalContext->getSession()->getPage()->findLink('Brugerprofil');
    if (!$link) {
      throw new Exception('Kunne ikke finde link til brugerprofil på brugerens side.');
    }
    $this->user = $user;
  }

  /**
   * Log in a user.
   *
   */
  public function login()
  {

    if (!$this->drupalContext->user) {
      throw new \Exception('Tried to login without a user.');
    }

    // it's nice to know in the log who we log in with:
    $this->log_msg(($this->verbose->loginInfo=="on"), "Forsøger at logge ind med brugeren: " . $this->drupalContext->user->name . "\n");

    $this->log_timestamp(($this->verbose->loginInfo=="on"), " - ");

    $el = $this->minkContext->getSession()->getPage();
    if (!$el) {
      throw new Exception ("Kunne ikke finde en side at logge ind på.");
    }

    // find out if we are not logged in on page - body has a certain class
    $pageclass = $el->find('xpath', '//body[contains(@class, "not-logged-in")]');

    if ($pageclass) {
      // now we know we are not logged-in.
      // Find the link represented by the login-button in the top.
      $xpath = "//body[contains(@class, 'overlay-is-active')]";
      $libutton=$this->getPage()->find('xpath', $xpath);

      if (!$libutton) {

        // the overlay is not shown. This is expected.
        // So we interject a bit of javascript to open it.

        // This is actually a copy of the js that actually runs on the page itself
        // but I couldn't get to activate that. This seems to do the same thing,
        // except it cannot remove the mobile-tags, so I commented that out.
        $js = "";
        $js .= "document.querySelector('body').classList.toggle('pane-login-is-open');";
        //$js .= "document.querySelector('body').classList.remove('mobile-menu-is-open mobile-search-is-open mobile-usermenu-is-open');";
        $js .= "if (document.querySelector('body').classList.contains('pane-login-is-open')) {";
        $js .= "document.querySelector('body').classList.add('overlay-is-active');";
        $js .= "} else {";
        $js .= "document.querySelector('body').classList.remove('overlay-is-active');";
        $js .= "}";

        $this->minkContext->getSession()->executeScript($js);

      } else {
        throw new Exception ("Fandt ikke login-knappen");
      }

    } else {
      // we are already logged in?! This should not be possible. Yet, here we are..
      print_r("Lader til at vi allerede er logget ind?");
    }

    // now wait until the username field is visible - it's the last one that scrolls into view
    $this->wait_until_field_is_found('css', 'input#edit-name', 'Login brugernavn-felt er ikke på siden.');

    // check if we can see the password and login-button as well
    $passwordfield = $this->getPage()->find('css', 'input#edit-pass');
    if (!$passwordfield) {
      throw new Exception("Login password felt er ikke på siden");
    }
    $loginknap = $this->getPage()->find('css', 'input#edit-submit');
    if (!$loginknap) {
      throw new Exception("Login knap er ikke på siden");
    }
    if (!$loginknap->isVisible() || !$passwordfield->isVisible()) {
      throw new Exception ("login-knap eller password-felt er ikke vist og tilgængelig på siden.");
    }
    // now fill in credentials
    $el->fillField($this->drupalContext->getDrupalText('username_field'), $this->drupalContext->user->name);
    $el->fillField($this->drupalContext->getDrupalText('password_field'), $this->drupalContext->user->pass);
    $submit = $el->findButton($this->drupalContext->getDrupalText('log_in'));

    if (empty($submit)) {
      throw new \Exception(sprintf("Ingen login-knap på siden %s", $this->drupalContext->getSession()->getCurrentUrl()));
    }

    // Log in.
    $submit->click();

    // wait until we can see the username displayed
    $this->wait_until_field_is_found('xpath',
          '//div[contains(@class,"pane-current-user-name")]//div[contains(@class,"pane-content")]/text()[contains(.,"' . $this->drupalContext->user->name . '")]/..',
          'Fandt ikke brugernavn på siden');

    // check if we are logged in drupal-wise
    if (!$this->drupalContext->loggedIn()) {
      throw new \Exception(sprintf("Kunne ikke logge på som brugeren: '%s'", $this->drupalContext->user->name));
    }

    $this->log_timestamp(($this->verbose->loginInfo=="on"), " - OK\n");

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
   * @When I scroll to the bottom (of the page)
   * Scroll to bottom of page
   *
   */
  public function scroll_to_bottom()
  {
    $found = $this->getPage()->find('css', 'footer.footer');
    if (!$found) {
      $this->scrollTo($found);
    }
  }

  /**
   * @When I scroll :pixels pixels
   * Scroll a bit up
   *
   */
  public function scroll_a_bit($pixels)
  {
    $this->minkContext->getSession()->executeScript('window.scrollBy(0, ' . $pixels . ');');
  }

  /**
   * Scroll to an element.
   *
   * @param ElementInterface $element
   *   Element to scroll to.
   * @throws \Exception
   */
  public function scroll_to(ElementInterface $element)
  {
    // translate the xpath of the element by adding \\ in front of " to allow it
    // to be passed in the javascript
    $xpath = strtr($element->getXpath(), ['"' => '\\"']);
    try {
      $js = '';
      $js = $js . 'var el = document.evaluate("' . $xpath .
            '", document, null, XPathResult.FIRST_ORDERED_NODE_TYPE, null ).singleNodeValue;';
      $js = $js . 'document.body.scrollTop = document.documentElement.scrollTop = 0;';
      $js = $js . 'el.scrollIntoViewIfNeeded(true);';
      $this->minkContext->getSession()->executeScript($js);
    } catch (UnsupportedDriverActionException $e) {
      // Ignore.
    } catch (Exception $e) {
      throw new Exception('Kunne ikke scrolle til element: ' . $e->getMessage());
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

  /**
   * Print out information about the browser being used for the testing
   *
   * @Given you tell me the current browser name
   * @Given you tell me the current browser
   * @Given you show me the current browser name
   * @Given you reveal the browser
   *
   * @param string $path
   *   The path to navigate to.
   */
  public function show_the_browser()
  {
    $session = $this->minkContext->getSession();
    $driver = $session->getDriver();
    $userAgent = $driver->evaluateScript('return navigator.userAgent');
    $provider = $driver->evaluateScript('return navigator.vendor');
    $browser = null;
    if (preg_match('/google/i', $provider)) {
      //using chrome
      $browser = 'chrome';
    } elseif (preg_match('/firefox/i',$userAgent)) {
      $browser = 'firefox';
    }

    if (!$provider) {
      $provider = "<unknown>";
    }
    print_r("The current browser is: " . $browser . "\n");
    print_r("The provider on record is: " . $provider . "\n");
    print_r("The user agent is: " . $userAgent . "\n");

  }

  /**
   * Wait for page to load.
   */
  public function wait_for_page()
  {
    try {
      // Strictly, this waits for jQuery to be loaded, but it seems
      // sufficient.
      $this->drupalContext->getSession()->wait(5000, 'typeof window.jQuery == "function"');
    } catch (UnsupportedDriverActionException $e) {
      // Ignore.
    } catch (Exception $e) {
      throw new Exception('Ukendt fejl imens side load blev afventet: ' . $e);
    }
  }

  /**
   * Wait for element to be visible
   */
  public function wait_until_field_is_found($locatortype, $locator, $errmsgIfFails)
  {
    $field = $this->getPage()->find($locatortype, $locator);

    // timeout is 30 seconds
    $maxwait = 30;
    while (--$maxwait>0 && !$field ) {
      sleep(1);

      # try to find it again, if necessary
      if (!$field) {
        $field = $this->getPage()->find($locatortype, $locator);
      }

    }
    if (!$field) {
      throw new Exception("Ventede 30 sekunder, men: " . $errmsgIfFails);
    }
  }

  /**
   * @When waiting up to :waitmax until :txt goes away
   * @param $waitmax - number of waits of 300 ms
   * @param $txt - text that we wait for will disappear
   */
  public function wait_until_text_is_gone($waitmax, $txt)
  {
    $wait=$this->getPage()->find('xpath', "//text()[contains(.,'" . $txt . "')]/..");
    $continueWaiting = true;
    if (!$wait) {
      return;
    }
    try {
      $continueWaiting = ($wait->isVisible()) ? true : false;

    } catch (Exception $e) {
      // ignore
    }
    while ($continueWaiting and --$waitmax>0) {
      usleep(300);
      $wait=$this->getPage()->find('xpath', "//text()[contains(.,'" . $txt . "')]/..");
      if ($wait) {
        try {
          $continueWaiting = ($wait->isVisible()) ? true : false;

        } catch (Exception $e) {
          ## ignore
        }
      } else {
        $continueWaiting = false;
      }
    }
  }

}
