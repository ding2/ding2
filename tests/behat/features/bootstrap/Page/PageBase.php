<?php


namespace Page;

use Behat\Mink\Session;

use SensioLabs\Behat\PageObjectExtension\PageObject\Exception\UnexpectedPageException;
use Behat\Mink\Element\ElementInterface;
use Behat\Mink\Exception\UnsupportedDriverActionException;


class PageBase extends LogMessages
{

  protected $verboseCookies = 'off';

  protected $elements = array(
        'button-agree' => array('css' => '.agree-button'),
        'button-askLibrarian' => array('css' => '.ask-vopros-minimize span'),
        'autocomplete' => 'div#autocomplete',
        'autocomplete-list' => 'li',
        'search-item-list' => '.search-results li.list-item',
        'pager-current' => '.pager-current',
        'pager-links' => "//li[contains(@class, 'pager')]//a",
        'pager-elements' => 'ul.pager li',
  );


  /**
   * Accept cookies and seeks to minimize Ask The Librarian, unless it already is.
   *
   * Checks if cookie acceptance is shown, and accepts it if it is.
   */
  public function acceptCookiesMinimizeAskLibrarianOverlay()
  {
    // check if there's a cookie thing showing:
    // nb. we cannot use getElement here although it would be simpler, because
    // if the cookie is not shown it's not a fault we should stop on
    $cookieAgree = $this->find('css', $this->elements['button-agree']['css']);
    if ($cookieAgree) {
      $this->logMsg(($this->verboseCookies=='on'), "Cookie accept-besked vises.\n");
      $this->logTimestamp(($this->verboseCookies=='on'), "Start: ");

      // now timing wise this is tricky, because the overlay moves. There seems to be no way to
      // catch it while moving, so we try to click it until that actually works. Selenium always
      // clicks in the middle of the element.
      // We try at most 50 times. That will work for even very slow systems. Typically only one wait cycle is necessary.
      $max=50;
      $success=false;
      while(--$max>0 && !$success) {
        try {
          $cookieAgree = $this->find('css', $this->elements['button-agree']['css']);

          $cookieAgree->click();
          // we will only ever execute this if the cookie button is clickable
          $success = true;

        } catch (Exception $e) {
          // give it a bit more time to come into place.
          usleep(100);
        }
      }
      if(!$success) {
        return "Cookie Agree-knap didn't go away after clicking on it.";
      }

      $this->logMsg(($this->verboseCookies=='on'), "End: ");

      // now we have clicked it, we expect it to go away within at the most 10 secs.
      $maxwait=330;
      $cookieAgree = $this->find('css', $this->elements['button-agree']['css']);
      while ($cookieAgree and --$maxwait > 0) {
        usleep(300);
        // refresh the search on the page
        $cookieAgree = $this->find('css', $this->elements['button-agree']['css']);
      }
      $this->logMsg(($this->verboseCookies == 'on'), "Awaited cookie to go away: " . ((330 - $maxwait)*300) . " millisecs\n");

    }

    // now minimize the "Spørg biblioteksvagten"
    // @todo: this should probably be a separate function
    $askLibrary = $this->find('css', $this->elements['button-askLibrarian']['css']);
    if ($askLibrary) {
      $this->logMsg(($this->verboseCookies == "on"), "Ask A Librarian was centered. Clicks it to minimize it.\n");
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
        $askLibrary = $this->find('css', $this->elements['button-askLibrarian']['css']);

      }
      if ($askLibrary) {
        return "Ask The Librarian did not minimize.";
      }
    }
  }



  /**
   * @When I scroll to the bottom (of the page)
   * Scroll to bottom of page
   *
   */
  public function scrollToBottom()
  {
    $found = $this->find('css', 'footer.footer');
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
    $this->getSession()->executeScript('window.scrollBy(0, ' . $pixels . ');');
  }

  /**
   * Scroll to an element.
   *
   * @param ElementInterface $element
   *   Element to scroll to.
   * @throws Exception
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
      $this->getSession()->executeScript($js);
    } catch (UnsupportedDriverActionException $e) {
      // Ignore.
    } catch (Exception $e) {

      throw new Exception('Could not scroll to element: ' . $e->getMessage());
    }
  }

  public function setVerboseCookieMode($onoff) {
    $this->verboseCookies = $onoff;
  }


  /**
   * Checks if the current Mink page matches this object.
   */
  public function verifyCurrentPage()
  {
    $currentUrl = $this->getDriver()->getCurrentUrl();
    // Replace placeholders with regexps. We have to match on quoted
    // placeholdes as preg_quote quotes them (naturally).
    $quotedPath = preg_replace('/\\\{.*?\\\}/', '[^/]+', preg_quote($this->path, '@'));
    $urlRegex = preg_quote(rtrim($this->getParameter('base_url'), '/'), '@') . $quotedPath;

    if (!preg_match('@' . $urlRegex . '@', $currentUrl)) {
      throw new UnexpectedPageException(sprintf('URL "%s" does not match path "%s"', $currentUrl, $this->path));
    }

    return $this;
  }

  public function waitForPopup()
  {
    $this->waitFor(10, function ($page) {
      return $page->find('css', '.ui-dialog');
    });
  }

  /**
   * Wait for page to load.
   */
  public function waitForPage()
  {
    try {
      // Strictly, this waits for jQuery to be loaded, but it seems
      // sufficient.
      $this->getSession()->wait(5000, 'typeof window.jQuery == "function"');
    } catch (UnsupportedDriverActionException $e) {
      // Ignore.
    } catch (Exception $e) {
      throw new UnexpectedPageException('Unknown error waiting for page');
    }
  }

  /**
   * @When waiting up to :waitmax until :txt goes away
   * @param $waitmax - number of waits of 300 ms
   * @param $txt - text that we wait for will disappear
   */
  public function waitUntilTextIsGone($waitmax, $txt)
  {
    $wait=$this->find('xpath', "//text()[contains(.,'" . $txt . "')]/..");
    $continueWaiting = true;
    if (!$wait) {
      return;
    }
    try {
      $continueWaiting = ($wait->isVisible()) ? true : false;

    } catch (UnexpectedPageException $e) {
      // ignore
    }
    while ($continueWaiting and --$waitmax>0) {
      usleep(300);
      $wait=$this->find('xpath', "//text()[contains(.,'" . $txt . "')]/..");
      if ($wait) {
        try {
          $continueWaiting = ($wait->isVisible());

        } catch (Exception $e) {
          // ignore
        }
      } else {
        $continueWaiting = false;
      }
    }
  }

}