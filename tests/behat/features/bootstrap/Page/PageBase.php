<?php

/**
 * @file
 * Implements the basics of a page.
 */

namespace Page;

use Behat\Mink\Exception\DriverException;
use Behat\Mink\Session;

use SensioLabs\Behat\PageObjectExtension\PageObject\Exception\UnexpectedPageException;
use Behat\Mink\Element\ElementInterface;
use Behat\Mink\Exception\UnsupportedDriverActionException;
use Exception;

/**
 * Class PageBase
 *
 * @package Page
 */
class PageBase extends LogMessages
{

    /**
     * Flag holding if verbose mode for cookies is set or not.
     *
     * @var string $verboseCookies
     */
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
        // Check if there's a cookie thing showing:
        // NB: we cannot use getElement here although it would be simpler.
        // This is because if the cookie is not shown it's not a fault we should stop on.
        $cookieAgree = $this->find('css', $this->elements['button-agree']['css']);
        if ($cookieAgree) {
            $this->logMsg(($this->verboseCookies == 'on'), "Cookie accept-besked vises.\n");
            $this->logTimestamp(($this->verboseCookies == 'on'), "Start: ");

            /*
             * Now timing wise this is tricky, because the overlay moves.
             * There seems to be no way to catch it while moving, so we try to
             * click it until that actually works. Selenium always clicks in
             * the middle of the element.
             *
             * We try at most 50 times. That will work for even very slow
             * systems. Typically only one wait cycle is necessary.
             */
            $max = 50;
            $success = false;
            while (--$max > 0 && !$success) {
                try {
                    $cookieAgree = $this->find('css', $this->elements['button-agree']['css']);

                    $cookieAgree->click();
                    // We will only ever execute this if the cookie button is clickable.
                    $success = true;
                } catch (\Exception $e) {
                    // Give it a bit more time to come into place.
                    usleep(100);
                }
            }
            if (!$success) {
                return "Cookie Agree-button didn't go away after clicking on it.";
            }

            $this->logMsg(($this->verboseCookies == 'on'), "End: ");

            // Now we have clicked it, we expect it to go away within at the most 10 secs.
            $maxwait = 330;
            $cookieAgree = $this->find('css', $this->elements['button-agree']['css']);
            while ($cookieAgree and --$maxwait > 0) {
                usleep(300);
                // Refresh the search on the page.
                $cookieAgree = $this->find('css', $this->elements['button-agree']['css']);
            }
            $this->logMsg(
                ($this->verboseCookies == 'on'),
                "Awaited cookie to go away: " . ((330 - $maxwait) * 300) . " millisecs\n"
            );
        }

        // Now minimize the "Spørg biblioteksvagten".
        // @Todo: this should probably be a separate function.
        $askLibrary = $this->find('css', $this->elements['button-askLibrarian']['css']);
        if ($askLibrary) {
            $this->logMsg(($this->verboseCookies == "on"), "Ask A Librarian was centered. Clicks it to minimize it.\n");
            // Simply click, and ignore if it can't click.
            try {
                $askLibrary = $this->find('css', $this->elements['button-askLibrarian']['css']);
                $askLibrary->click();
            } catch (\Exception $e) {
                // Wait a bit and try again.
                sleep(1);
                $askLibrary = $this->find('css', $this->elements['button-askLibrarian']['css']);
                $askLibrary->click();
            }
            // We will wait a bit until it goes away.
            $max = 10;
            while ($askLibrary && --$max > 0) {
                // Renew our view on the page.
                $askLibrary = $this->find('css', $this->elements['button-askLibrarian']['css']);
            }
            if ($askLibrary) {
                return "Ask The Librarian did not minimize.";
            }
        }
        return "";
    }


    /**
     * Get Prompt To login.
     *
     * @return string
     *    Nonempty if we didn't get a prompt to log in.
     */
    public function getPromptToLogin()
    {
        // Start by waiting for the popupbar-is-open class to be added to the body-tag.
        // It is a bit cheaky but that's all we need to check for.
        $found = $this->find('css', 'body');
        $max = 300;
        while (--$max > 0 && strstr($found->getAttribute('class'), 'popupbar-is-open') === false) {
            usleep(100);
            $found = $this->find('css', 'body');
        }

        // Let's check in another way to make sure.
        $classArr = explode(' ', $found->getAttribute('class'));
        $gotIt = false;
        foreach ($classArr as $class) {
            if ($class == "popupbar-is-open") {
                $gotIt = true;
            }
        }
        if (!$gotIt) {
            return "Was not prompted for login as expected.";
        }
        return "";
    }

    /**
     * Scroll to bottom of page
     *
     * @When I scroll to the bottom (of the page)
     *
     * @throws Exception
     *   In case of error.
     */
    public function scrollToBottom()
    {
        $found = $this->find('css', 'footer.footer');
        if (!$found) {
            $this->scrollTo($found);
        }
    }

    /**
     * Scroll a bit up
     *
     * @param string $pixels
     *   The number of pixels to scroll.
     *
     * @When I scroll :pixels pixels
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
     *
     * @throws \Exception
     *   In case of error.
     */
    public function scrollTo(ElementInterface $element)
    {
        // Translate the xpath of the element by adding \\ in front of " to allow it to be passed in the javascript.
        $xpath = strtr($element->getXpath(), ['"' => '\\"']);
        try {
            $js = '';
            $js = $js . 'var el = document.evaluate("' . $xpath .
                '", document, null, XPathResult.FIRST_ORDERED_NODE_TYPE, null).singleNodeValue;';
            $js = $js . 'document.body.scrollTop = document.documentElement.scrollTop = 0;';
            $js = $js . 'el.scrollIntoViewIfNeeded(true);';
            $this->getSession()->executeScript($js);
        } catch (DriverException $e) {
            throw new \Exception('Could not scroll to element: ' . $e->getMessage());
        }
    }

    /**
     * Set Verbose Mode for Cookie handling.
     *
     * @param string $onoff
     *    On or Off to set verbose mode for cookie handling.
     */
    public function setVerboseCookieMode($onoff)
    {
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

    /**
     * Wait For Popup.
     */
    public function waitForPopup()
    {
        $this->waitFor(10, function ($page) {
            return $page->find('css', '.ui-dialog');
        });
    }

    /**
     * Wait for popupbar.
     */
    public function waitForPopupbar()
    {
        $popupbar = $this->waitFor(10, function ($page) {
            return $page->find('css', '#popupbar');
        });

        if (!$popupbar) {
            throw new Exception('Popupbar not shown.');
        }

        return $this->getElement('Popupbar');
    }

    /**
     * Wait for page to load.
     */
    public function waitForPage()
    {
        try {
            // Strictly, this waits for jQuery to be loaded, but it seems sufficient.
            $this->getSession()->wait(5000, 'typeof window.jQuery == "function"');
        } catch (Exception $e) {
            throw new Exception('Unknown error waiting for page');
        }
    }

  /**
   * Wait Until Text is gone.
   *
   * @param int $waitmax
   *    Number of waits of 300 ms.
   * @param string $txt
   *    Text that we wait for will disappear.
   *
   * @When waiting up to :waitmax until :txt goes away
   *
   * @return string
   *    Return status of operation.
   */
  public function waitUntilTextIsGone($waitmax, $txt) {
      // First see if we can find the element.
      $wait = $this->find('xpath', "//text()[contains(.,'" . $txt . "')]/..");
      $continueWaiting = true;
      if (!$wait) {
          return "";
      }
      // Now wait for the assigned time until we no longer can find txt on the page.
      while ($continueWaiting and --$waitmax > 0) {
          usleep(300);
          $wait = $this->find('xpath', "//text()[contains(.,'" . $txt . "')]/..");
          $continueWaiting = ($wait === null);
      }
      if ($waitmax > 0) {
          return '';
      }
      return 'Failed - ' . $txt . ' is still on page.';
  }
}
