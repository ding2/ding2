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
use Page\SearchPage;

/**
 * Defines application features from the specific context.
 */
class LibContext implements Context, SnippetAcceptingContext {

  /** @var array
   * is holding css-locator strings
   */
  public $cssStr;


  /** @var \Drupal\DrupalExtension\Context\DrupalContext */
  public $drupalContext;

  /**
   * @var string
   * Contains the last search string we used
   */
  public $lastSearchString;

  /** @var \Drupal\DrupalExtension\Context\MinkContext */
  public $minkContext;


  /**
   * Current authenticated user.
   * A value of FALSE denotes an anonymous user.
   *
   * @var stdClass|bool
   */
  public $user = FALSE;

  /** @var object
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
  public function __construct(SearchPage $searchPage) {
    $this->searchPage = $searchPage;

    // initialise the verbose structure. These are default settings.
    $this->verbose = (object) array (
          'searchResults' => false,
          'loginInfo' => true,
          'cookies' => false,
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
            ->resizeWindow(1024, 2000, 'current');
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
  public function AcceptCookiesMinimizeAskLibrarianOverlay()
  {
    // we use the searchPage-instance to deal with cookies
    $result = $this->searchPage->acceptCookiesMinimizeAskLibrarianOverlay();
    if ($result = "") {
      $this->logMsg(true, $this->searchPage->getMessages());
      throw new Exception ($result);
    }
  }

  /**
   * @When I enter :text in field :field
   *
   * Type text character by character, with support for newline, tab as \n and \t
   */
  public function EnterTextIntoField($text, $field) {
    $found = $this->getPage()->find('css', $field);
    if (!$found) {
      throw new Exception ("Couldn't find the field " . $field);
    }
    $this->scrollTo($found);
    // click so we place the cursor in the field
    $found->click();

    // now it becomes technical, because we will type each character in
    // the $text variable one at a time, but also we want to use the escape
    // option of \n for instance. So we will remember if we get the \ char
    // and check the next character.
    $escaped = false;
    for ($i=0; $i<strlen($text); $i++) {
      $key = substr($text, $i, 1);
      if ($escaped) {
        switch ($key) {
          case 'n':
            $key = "\r\n";
            break;
          case "t":
            $key = "\t";
            break;
          default:
            // we will just let $key be what it is
        }
      }
      // unless we start an escaped character, play it through the browser
      if ($key == "\\") {
        $escaped = true;
      } else {
        $this->minkContext->getSession()
              ->getDriver()
              ->getWebDriverSession()
              ->element('xpath', $found->getXpath())
              ->postValue(['value' => [$key]]);
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
   * Navigate to a page.
   *
   * @todo should only navigate if the path is different from the current.
   *
   * @param string $path
   *   The path to navigate to.
   */
  public function gotoPage($path)
  {
    $this->minkContext->visit($path);
  }


  /**
   * Go to the search page.
   *
   * @Given I have searched for :arg1
   *
   * @param string $string
   *   String to search for.
   * @throws Exception
   */
  public function gotoSearchPage($string)
  {
    // First we try to translate the argument, to see if there's anything we should pick out first
    $searchString = $this->translateArgument($string);

    $this->logMsg(($this->verbose->searchResults=="on"), "Searches for " . urlencode($searchString) . "\n");

    $this->lastSearchString = $searchString;

    $this->gotoPage('/search/ting/' . urlencode($searchString));

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
      throw new Exception("Couldn't find the users own page.");
    }
    $classes = explode(' ', $body->getAttribute('class'));
    foreach ($classes as $class) {
      if (preg_match('{^page-user-(\d+)$}', $class, $matches)) {
        $user->uid = $matches[1];
        break;
      }
    }
    if (!$user->uid) {
      throw new Exception("Couldn't find the users UID from the users page");
    }

    // In addition, make a note of the "id" that is used in paths (which
    // is most often "me"), so we can construct paths as would be
    // expected. We're sniffing this rather than hardcoding it because
    // some users are except from the "me" replacement.
    $link = $this->drupalContext->getSession()->getPage()->findLink('Brugerprofil');
    if (!$link) {
      throw new Exception("Couldn't find link to user profile on the users page");
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
    $this->logMsg(($this->verbose->loginInfo=="on"), "Attempts logging in with user: " . $this->drupalContext->user->name . "\n");

    $this->logTimestamp(($this->verbose->loginInfo=="on"), " - ");

    $el = $this->minkContext->getSession()->getPage();
    if (!$el) {
      throw new Exception ("Couldn't find a page to login from");
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
        throw new Exception ("Did not find the login-button");
      }

    } else {
      // we are already logged in?! This should not be possible. Yet, here we are..
      print_r("Apparently we are already logged in?");
    }

    // now wait until the username field is visible - it's the last one that scrolls into view
    $this->waitUntilFieldIsFound('css', 'input#edit-name', "Login user-name field is not shown");

    // check if we can see the password and login-button as well
    $passwordfield = $this->getPage()->find('css', 'input#edit-pass');
    if (!$passwordfield) {
      throw new Exception("Login password field is not shown");
    }
    $loginknap = $this->getPage()->find('css', 'input#edit-submit');
    if (!$loginknap) {
      throw new Exception("Login button is not on page");
    }
    if (!$loginknap->isVisible() || !$passwordfield->isVisible()) {
      throw new Exception ("Login button or password field is not shown/accessible on page.");
    }
    // now fill in credentials
    $el->fillField($this->drupalContext->getDrupalText('username_field'), $this->drupalContext->user->name);
    $el->fillField($this->drupalContext->getDrupalText('password_field'), $this->drupalContext->user->pass);
    $submit = $el->findButton($this->drupalContext->getDrupalText('log_in'));

    if (empty($submit)) {
      throw new \Exception(sprintf("No login button on page %s", $this->drupalContext->getSession()->getCurrentUrl()));
    }

    // Log in.
    $submit->click();

    // wait until we can see the username displayed
    $this->waitUntilFieldIsFound('xpath',
          '//div[contains(@class,"pane-current-user-name")]//div[contains(@class,"pane-content")]/text()[contains(.,"' . $this->drupalContext->user->name . '")]/..',
          "Did not find the users name displayed on page");

    // check if we are logged in drupal-wise
    if (!$this->drupalContext->loggedIn()) {
      throw new \Exception(sprintf("Could not log on as user: '%s'", $this->drupalContext->user->name));
    }

    $this->logTimestamp(($this->verbose->loginInfo=="on"), " - OK\n");

  }



  /**
   * log_msg - prints message on log if condition is true.
   *
   * @param $ifTrue
   * @param $msg
   */
  public function logMsg($ifTrue, $msg) {
    if ($ifTrue) {
      print_r($msg);
    }
  }

  /**
   * log_timestamp - puts a timestamp in the log. Good for debugging timing issues.
   * @param $ifTrue
   * @param $msg
   */
  public function logTimestamp($ifTrue, $msg) {
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
   * @Then pageing allows to get all the results
   *
   * This retrieves the search result and stores it in the local array searchResults.
   * There can be several search results, so some garbage collection needs to be done.
   * The searchResult array will be reset before each scenario.
   */
  public function pageingAllowsToGetAllResults()
  {
    // log messages in any case. Might be useful info in there.
    $this->logMsg(($this->verbose->searchResults == "on"), $this->searchPage->getMessages());

    $result = $this->searchPage->getEntireSearchResult();
    if ($result != "") {
      throw new Exception ($result);
    };

  }

  /**
   * @When I scroll to the bottom (of the page)
   * Scroll to bottom of page
   *
   */
  public function scrollToBottom()
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
  public function scrollABit($pixels)
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
  public function scrollTo(ElementInterface $element)
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
      throw new Exception('Could not scroll to element: ' . $e->getMessage());
    }
  }


  /**
   * @Given I want verbose mode for :area to be :onoff
   * @Given I set verbose mode for :area to be :onoff
   * @Given I set control mode for :area to be :onoff
   *
   * Sets the control or verbose mode of the run, controlling how much info is put into the output log.
   */
  public function setVerboseControlMode($area, $onoff)  {
    $area = mb_strtolower($area);
    $onoff = mb_strtolower($onoff);
    switch($area) {
      // this tells if we want to know the username we logged in with
      case 'login':
      case 'logininfo':
        $this->verbose->loginInfo = $onoff;
        if ($onoff == 'on') {
          print_r("Verbose mode of loginInfo set to on");
        }
        break;
        // this indicates if we want to see in the log what was found in the searches
      case 'search-results':
      case 'search-result':
      case 'searchresults':
        $this->verbose->searchResults = $onoff;
        if ($onoff == 'on') {
          print_r("Verbose mode of searchResults set to on");
        }
        break;
        // this indicates if we want to know about handling cookie-popups
      case 'cookie':
      case 'cookies':
        $this->verbose->cookies = $onoff;
        $this->searchPage->setVerboseCookieMode($onoff);

        if ($onoff == 'on') {
          print_r("Verbose mode of cookie-handling set to on");
        }
        break;
        // this setting controls how many search result pages we will traverse during testing
      case 'searchmaxpages':

        $this->searchPage->setMaxPageTraversals($onoff);

        // always notify the user of this setting
        print_r("Verbose mode for max number of search result pages set to " . $onoff);
        print_r("\n");
        break;
        // this is the catch-all setting
      case 'everything':
      case 'all':
        $this->verbose->loginInfo = $onoff;
        $this->verbose->searchResults = $onoff;
        $this->verbose->cookies = $onoff;
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
  public function showTheBrowser()
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
   * Attempts to translate argument given in gherkin script.
   * This allows for generic arguments to be given, to be replaced during runtime here either
   * by looking up values on the current page, or substitute from a catalogue/known variable value
   * The convention is to initiate a variable with a dollar-sign followed by <choice> : <source>
   * choice is the way to select between several values that originates from the source.
   * It could be 'random', 'first', 'last' or simply 'get', if there's only one value possible.
   * Source is pointing to where the value should come from.
   * 'nyhed' looks up news placed on the front page. If not on the front page - this will fail.
   *
   * @param $string
   * @return mixed
   * @throws Exception
   */
  public function translateArgument($string)
  {
    // if we can't translate it, we just pass it right back
    $returnString = $string;
    if (substr($string, 0, 1)=="$") {
      // try to translate it
      // form is $ <choice> : <source>
      $lstr = substr($string, 1);
      $cmdArr = explode(":", $lstr);
      if (count($cmdArr)!=2) {
        throw new Exception ("Argument given does not follow \$modifier:source, ex. \$random:news. Got: " . $lstr);
      }

      // here we try to figure out what to translate to
      switch (strtolower($cmdArr[1]))
      {
        // find news (presuming to be on the front page, otherwise fail)
        // choose between them and return the value
        case "news":
        case 'nyhed':
          $foundArr = $this->getPage()->findAll('css', '.news-text h3.title');
          if (!$foundArr) {
            throw new Exception ("Argument for a news item. Could not find any news on the page.");
          }
          // only first, last and random works with nyheder as choice
          switch( strtolower($cmdArr[0]))
          {
            case 'first':
              $returnString = $foundArr[0]->getText();
              break;
            case 'last':
              $returnString = $foundArr[count($foundArr)-1]->getText();
              break;
            case 'random':
              $i = random_int(0, count($foundArr)-1);
              $returnString = $foundArr[$i]->getText();
              break;
            default:
              throw new Exception ("Only 'first', 'last' og 'random' can be modifiers for 'news'");
          }
          break;
        // Replace the value with the last known search string
        case 'lastsearchstring':
          // regardless of the choice
          $returnString = $this->lastSearchString;
          break;
        default:
          throw new Exception ("Unknown \$modifier:source combination: " . $string );
          break;
      }
    }
    if ($returnString != $string) {
      // we always want to tell this, otherwise the tester cannot figure out what was done.
      print_r("Replaced " . $string . " with " . $returnString);
      print_r("\n");
    }
    return $returnString;
  }


  /**
   * Wait for page to load.
   */
  public function waitForPage()
  {
    try {
      // Strictly, this waits for jQuery to be loaded, but it seems
      // sufficient.
      $this->drupalContext->getSession()->wait(5000, 'typeof window.jQuery == "function"');
    } catch (UnsupportedDriverActionException $e) {
      // Ignore.
    } catch (Exception $e) {
      throw new Exception("Unknown error while awaiting page to load:" . $e);
    }
  }

  /**
   * Wait for element to be visible
   */
  public function waitUntilFieldIsFound($locatortype, $locator, $errmsgIfFails)
  {
    $field = $this->getPage()->find($locatortype, $locator);

    // timeout is 30 seconds
    $maxwait = 30;
    while (--$maxwait>0 && !$field ) {
      sleep(1);

      // try to find it again, if necessary
      if (!$field) {
        $field = $this->getPage()->find($locatortype, $locator);
      }

    }
    if (!$field) {
      throw new Exception("Waited 30 secs but: " . $errmsgIfFails);
    }
  }

  /**
   * @When waiting up to :waitmax until :txt goes away
   * @param $waitmax - number of waits of 300 ms
   * @param $txt - text that we wait for will disappear
   */
  public function waitUntilTextIsGone($waitmax, $txt)
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
          // ignore
        }
      } else {
        $continueWaiting = false;
      }
    }
  }

}
