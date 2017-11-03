<?php


namespace Page;

use Behat\Mink\Session;
use SensioLabs\Behat\PageObjectExtension\PageObject\Factory;
use Stack;


class SearchPage extends PageBase
{

  /**
   * @var Stack $expectedResultsCount
   * Stack holding the number of result per search. Primarily used for testing facets.
   */
  private $expectedResultsCount ;

  /**
   * @var integer $maxPageTraversals
   * If 0 it will be interpreted as 'all'
   */
  protected $maxPageTraversals = 0;

  /**
   * @var string $messageCollection
   * contains all log messages from verbose mode
   */
  protected $messageCollection = '';

  /**
   * @var string $path
   */
  protected $path = '/';

  /**
   * @var array $searchResults
   *
   * Holds the latest search result we scraped from the pages.
   *
   */
  protected $searchResults = array();


  /**
   * @var string $verboseSearchResults
   *
   */
  protected $verboseSearchResults = 'off';



  /**
   * @return string - empty if we found the number of results as we expected.
   */
  public function compareResultSizeWithExpected() {
    if ($this->getExpectedSearchResultSize() != 0)
    {
      // see if we can find the number of results from the page.
      $expectCount = $this->returnShownSizeOfSearchResult();
      if ($this->getExpectedSearchResultSize() != $expectCount) {
        return "Did not find the expected amount of posts. (Found: " . $expectCount . ". Expected:" . $this->getExpectedSearchResultSize();
      }
    } else {
      // do nothing, but put it in the log
      $this->logMsg(true,"An expected number of items were not set.");
    }
    return "";
  }


  /**
   * This searches for a pattern anywhere in the search results
   */
  public function findRegEx($regexp) {

    // run through the entire search result to see if the title is there
    $found = false;
    $xte = 0;
    for ($i=0; $i<count($this->searchResults); $i++) {
      if (preg_match('/' . $regexp . '/', $this->searchResults[$i]->title) ) {
        $found = true;
        $this->logMsg(($this->verboseSearchResults == 'on'),
              "Found " . $regexp . " on page " . $this->searchResults[$i]->page .
              " as item# " . $this->searchResults[$i]->item . "\n");
      }
      $xte++;
    }

    return $found;

  }



  /**
   * @return int - is the number of search results we actually found by scraping them off the pages
   * Contrast this to getShownSizeOfSearchResult.
   * Notice this is possibly limited by the verbose/control setting of maxSearchPages.
   */

  public function getActualSearchResultSize() {
    return count($this->searchResults);
  }

  /**
   *   Building the entire search result into an array
   *
   * @return string - empty means everything was fine. Not empty means failed. Text will be the reason it failed
   *
   */
  public function getEntireSearchResult()
  {
    // initialise
    $this->searchResults = array();
    $founds = $this->findAll('css', '.search-results li.list-item');

    if (!$founds) {
      return "Didn't find a search result.";
    }

    // now we need to await that all the availability data are collected. We will wait here until we cannot find
    // "Henter beholdningsoplysninger" anymore
    $this->waitUntilTextIsGone(100, 'Henter beholdningsoplysninger');

    // count of page number
    $cnt = 1;
    $lb_continue = true;
    // loop through the pages until we're on the last page
    while ($lb_continue ) {
      // count of placement on page from top
      $xte = 1;
      foreach ($founds as $srItem) {

        $this->scrollTo($srItem);
        $isSamling = false;

        // Get hold of the title
        $titlelink = $srItem->find('css', '.ting-object h2 a');  // v4
        if (!$titlelink) {
          $titlelink = $srItem->find('css', '.ting-object .heading a'); // v3
        }
        $txt_title = ($titlelink) ? $titlelink->getText() : "";

        // Find the author and published date
        $creator = $srItem->find('css', '.ting-object .field-name-ting-author');
        $txt_creator = "";
        $txt_published = "";
        if ($creator) {
          $txt_creator_full = $creator->getText();
          if (strlen($txt_creator_full)>0) {
            $arrCreator=explode("(", $txt_creator_full);
            // so authors may be listed with their birth year in ( ), so we need the last item for date and first for author
            if (count($arrCreator)>=2) {
              $txt_creator = $arrCreator[0];
              $txt_published = substr($arrCreator[count($arrCreator)-1], 0, 4);
            } else {
              $this->logMsg(true, "Creator was not followed with a '(' : " . $txt_title . " af " . $txt_creator_full);
            }
          }

        }

        // find the series - there can be multiple
        $series = $srItem->findAll('css', '.field-name-ting-series .field-item');
        $txt_serie = "";

        foreach ($series as $serie) {
          $txt_serie = $txt_serie . $serie->getText() . "\n";
        }

        // find "tilgængelig som"
        $accessibilities = $srItem->findAll('css', '.availability p a');
        $txt_access = "";

        foreach ($accessibilities as $access) {
          $txt_access = $txt_access . $access->getText() . "\n";
        }

        // Now we'll check if we've got a collection.
        // The way to be sure on the search-page is to check
        // if there are different material types (bog, lydbog, dvd, ...) listed
        // We'll check if there are more found, and if the first one found
        // is different from any of the subsequent ones. If so, we'll have a collection.
        // If a collection consists only of one type, say 'bog', then we'll not
        // be able to spot it from the search-page, only by opening the material-show
        // and check if the url contains "Collection" (note: on the search screen all
        // urls contain 'collection', so don't fall into that trap).
        if ($txt_access != "") {
          $arr_samling = preg_split("/\n/", $txt_access);

          if (count($arr_samling)>1) {

            $txt_mtype1 = $arr_samling[0];
            for ($i=1; $i<count($arr_samling); $i++) {

              $isSamling = ($txt_mtype1!=$arr_samling[$i] and $arr_samling[$i]!='') ? true : $isSamling;
            }
          }
        }

        // get the link that is shown as 'tilgængelig'. This needs to be present
        $link = $srItem->find('css', '.availability a');
        $txt_link = "";
        if ($link) {
          $txt_link = $link->getText();
        }

        // and finally grab out the cover image, if present.
        $coverimg = $srItem->find('xpath', '//div[contains(@class,"ting-cover")]/img');
        $txt_cover = "";
        if ($coverimg) {
          $txt_cover = $coverimg->getAttribute('src');

        }

        $this->searchResults[] = (object) array (
              'page' => $cnt,
              'item' => $xte,
              'title' => $txt_title,
              'link' => $txt_link,
              'cover' => $txt_cover,
              'serie' => $txt_serie,
              'access' => $txt_access,
              'collection' => ($isSamling) ? 'yes' : 'no',
              'creator' => $txt_creator,
              'published' => $txt_published,
        );

        $ll = count($this->searchResults)-1;
        $this->logMsg(($this->verboseSearchResults== 'on'), "Title: " . $this->searchResults[$ll]->title .
              ", by " . $this->searchResults[$ll]->creator . " (" . $this->searchResults[$ll]->published . ") "
                . " (page " . $this->searchResults[$ll]->page
                . " # " . $this->searchResults[$ll]->item . ")\n");

        // next item on page
        $xte = $xte + 1;
      }
      $this->logMsg(($this->verboseSearchResults == 'on'), "Total items listed on page: " . ($xte - 1) . "\n");


      // ready for next page:
      $cnt = $cnt + 1;
      $pageing = $this->find('css', '.pager .pager-next a');

      if (!$pageing) {
        // we trust this means we are at the end of the search result and we have scooped everything up
        $lb_continue = false;
      } else {
        // this is a bit precarious, as we need to check if the cookie and 'ask librarians' overlays are
        // popping up. If so, we'll whack them down again, because they can disturb our clicking.
        // $this->AcceptCookiesMinimizeAskLibrarianOverlay();
        // scroll down and click 'næste'
        $this->scrollTo($pageing);

        try {
          $pageing->click();
        } catch (UnsupportedDriverActionException $e) {
          // Ignore
        } catch (\Exception $e) {
          // just try again... might save us
          $this->scrollABit(500);
          //$this->AcceptCookiesMinimizeAskLibrarianOverlay();
          $pageing->click();
        }

        $this->waitForPage();
        // rescan the search results on this page
        $founds = $this->findAll('css', '.search-results li.list-item');
      }
      if ($this->maxPageTraversals==($cnt-1)) {
        // stop early because of setting in verbose/control
        $lb_continue = false;
        $this->logMsg(($this->verboseSearchResults=="on"), "Stops after " . $cnt . " pages due to verbose setting.\n");
      }
    }
    $this->logMsg(($this->verboseSearchResults == "on"), "Total pages: " . ($cnt-1) . "\nTotal items:" . count($this->searchResults) . "\n");
    return ""; // signal it went well
  }





  /**
   * getExpectedSearchResultSize - returns the last expected result
   * @pop - optional default false. If true, the last result will be popped from the stack too
   * @return int
   *
   */
  public function getExpectedSearchResultSize($pop = false)
   {
    // It's a bit crude, but I'm not sure where else to initialize this Stack variable
    if (!$this->expectedResultsCount) {
      $this->expectedResultsCount = new Stack;
    }
    return $this->expectedResultsCount->get($pop);
  }


  /**
   * @param $facets   - List of elements containing facets
   * @param bool $select - default true - if true sets expected result. If false, pops the last value
   * @return string
   * @throws Exception
   */
  private function getLargestFacetAndClickIt($facets, $select = true) {
    // Now we traverse them to find out how many results they 'promise' if selected
    $largestName = "";
    $largestCount = 0;
    $largestCheckbox =$facets[0];
    foreach($facets as $chkbox) {
      // this can be a getElement
      $lcntElement = $chkbox->find('css', 'span.count');
      if ($lcntElement) {
        $lcnt = $lcntElement->getText();
      } else {
        return "Did not find correct structure of facet. Should contain a 'span class=count' element.";
      }
      // remove the paranthesises to retrieve the number and check if this is the largest number
      // found this far. If so, we will save it for later use.
      $lcnt = substr($lcnt, 1, strlen($lcnt)-2);
      if ($lcnt > $largestCount) {
        $largestCount = $lcnt;
        $largestName = $chkbox->find('css', 'a')->getText();
        $largestCheckbox = $chkbox;
      }
    }
    if (!$largestCheckbox) {
      return "Did not find a largest facet to choose.";
    }

    // Save the 'promise' to enable later checks and tell the tester what we attempt, so
    // if this fails there is a chance to interpretate the screenshot
    if ($select) {
      $this->setExpectedSearchResultSize($largestCount);
    } else {
      if ($this->expectedResultsCount->pop() < 0) {
        return "Something went wrong with expected results - are you trying to deselect with selecting facets first?";
      };

    }
    $this->logMsg(true, "Clicks facet: " . $largestName . " to get " . $this->expectedResultsCount->get() . " results.");

    // Now we will select the largest one we ended up with.
    $link = $largestCheckbox->find('css', 'a');
    if ($link) {
      $this->scrollTo($link);
      $link->click();
      $this->waitForPage();
    } else {
      return "Expected to find a link in the html structure under a facet.";
    }
    return "";
  }

  /**
   * @return int
   * Set the maximum number of pages we want to traverse to scrape off the search result.
   */
  public function getMaxPageTraversals() {
    return $this->maxPageTraversals;
  }




  /**
   * @return string
   * Returns and resets the log messages. They can only be read once.
   */
  public function getMessages() {
    $msg = $this->messageCollection;
    $this->messageCollection = "";
    return $msg;
  }

  /**
   * @return string : empty if ok, otherwise the error message.
   */
  public function getOpenScanSuggestions() {
    // we need to enable a wait because we cannot control the timing

    // you'd think we want to use the waitFor method, but it doesn't actually do this trick
    // we need to enable a wait because we cannot control the timing
    // It is possibly some dynamic javascript on the page that tricks it.
    $max = 300;
    $found = $this->find('css', $this->elements['autocomplete']);
    while (--$max>0 && !$found) {
      usleep(100);
      $found = $this->find('css', $this->elements['autocomplete']);
    }

    // report error if we ran out of time
    if (!$found) {
      return "Openscan did not show any suggestions. ";
    }

    $found = $this->getElement('autocomplete');

    // it also takes a bit for the page to get the dynamics of the suggestions done. So we wait again
    $max = 300;
    $cnt=0;
    while (--$max>0 && !$found->findAll("css", $this->elements['autocompleteList'])) {
      usleep(100);
      // refresh the search
      $found = $this->getElement('autocomplete');
    }

    // now we list the suggestions given.
    foreach ($found->findAll("css", $this->elements['autocompleteList']) as $suggestion) {
      $this->logMsg(true, $suggestion->getText() . "\n");
      $cnt++;
    }
    if ($cnt==0) {
      return "No suggestions were found.";
    }
    // all we can do is list the number for convenience. It's in the configuration how many there should be.
    $this->logMsg(true, "In total " . $cnt . " suggestions were shown. Check configurationen.");
    return "";
  }


  /**
   * Tries to find the number of search results shown as total found posts on the search page
   * @return int
   */
  public function getShownSizeOfSearchResult() {
    // todo: use getElement here
    $found =$this->find('css', '.pane-content .count');
    if (!$found) {
      $this->logMsg(true, "Couldn't find count of results on page.");
      return -1;
    }

    // getText() will here be of the form "(nnn resultater)", where nnn is what we want.
    // so we will split the string on the space, then substr the '(' away
    $resArr = explode(' ', $found->getText());
    if (count($resArr)==0) {
      return "Couldn't interpret result as '(x resultater)'. All I found was this: " . $found->getText();
    }
    $expectCount = substr($resArr[0], 1);

    return $expectCount;
  }


  /**
   * @return string
   * Returns the verbose setting for search result
   */
  public function getVerboseSearchResult() {
    return $this->verboseSearchResults;
  }

  /**
   * log_msg - prints message on log if condition is true.
   *
   * @param $ifTrue
   * @param $msg
   */
  public function log2Msg($ifTrue, $msg) {
    if ($ifTrue) {
      $this->messageCollection = $this->messageCollection . $msg;
    }
  }

  /**
   * popExpectedSearchResultSize - pops and returns the last expected result
   * @return int
   *
   */
  public function popExpectedSearchResultSize() {
    // it's a bit crude, but I don't know where else to initialise this Stack
    if (!$this->expectedResultsCount) {
      $this->expectedResultsCount = new Stack;
    }
    return $this->expectedResultsCount->pop();
  }

  /**
   * setExpectedSearchResultSize - pops and returns the last expected result
   * @return int
   *
   */
  public function setExpectedSearchResultSize($size) {
    // It's a bit crude, but I don't know where else to initialise this Stack
    if (!$this->expectedResultsCount) {
      $this->expectedResultsCount = new Stack;
    }
    // we fail diligently by just setting a -1 as expected result. That will never compare
    // to anything so we will get the actual failing condition at a later step.
    // Meanwhile we loaded the reason into the logmessages which should be revealed at that
    // time.
    if (!is_numeric($size)) {
      $this->logMsg(true, "Tried to set expected result to a non-number: " . $size);
      $size = -1;
    }
    $this->expectedResultsCount->set($size);
  }



  /**
   * searches for $string
   */
  public function search($string) {
    // You'd think we should URL encode this, but that makes it fail on
    // "The hitchhiker's guide to the galaxy".
    $this->open(['string' => $string]);
  }

  public function setMaxPageTraversals($maxPages) {
    $this->maxPageTraversals = $maxPages;
  }

  /**
   * Sets number of search items per page via dropdown.
   * Returns non-empty string if failing.
   * @param $size
   * @return string
   * @throws \Behat\Mink\Exception\ElementNotFoundException
   */
  public function setTheNumberOfResultsPerPageToSize($size)
  {
    $found =$this->find('css', 'select#edit-size.form-select[name="size"]');
    if (!$found){
      return "Did not find a dropdown for setting results per page.";
    }
    $found->selectOption($size, false);
    $this->waitForPage();
    return "";
  }

  public function setVerboseSearchResult($onoff) {
    $this->verboseSearchResults = $onoff;
  }

  private function unpackFacetLists() {
    // unpack all lists
    // notice we can't use getElement because it is not a problem if we don't have to unpack lists.
    $found = $this->find('css', 'a.expand-more');
    // we set 200 as the upper limit for unpacking. It's way above what we will experience, but
    // we want to unpack them all, and still get out of this in a civilised way if there unpacking
    // doesn't work
    $cnt = 200;
    while($found && --$cnt > 0)
    {
      $this->scrollTo($found);

      try {
        $found->click();
      } catch (\Exception $e) {
        // If we end here, it's likely something is blocking for the control
        // we can try to scroll a bit more, try to recapture and click again
        $this->scrollABit(200);
        $found = $this->find('css', 'a.expand-more');
        // from a testing perspective we would like to know that we needed more scrolling.
        // This is an indication that the page is not shown as expected.
        $this->logMsg(true, "scrolling a bit extra..");
        $found->click();
      }
      // we allow the javascript to run.
      sleep(1);
      // search again for the next
      $found = $this->find('css', 'a.expand-more');
    }
  }

  /**
   * finds all used facets, figure which will give the largest subset and click it
   * @return string - empty if all ok
   */
  public function useFacetsToIncreaseSearchResults()
  {
    // report an error if we've not set a facet correctly previously
    if ($this->getExpectedSearchResultSize()==0) {
      return "We can only attempt to deselect a facet if we selected one first.";
    }

    // then find all the checked facets on the page
    $found =$this->findAll('css', '.selected-checkbox');
    if (!$found) {
      return "Did not find any selected facets. We expect facets to contain class=selected-checkbox.";
    }

    return $this->getLargestFacetAndClickIt($found, false);
  }


  /**
   * Unpacks and selects the facet with the largest subset if selected
   * @return string
   * @throws Exception
   */
  public function useFacetsToReduceSearchResultsToTheHighestPossible()
  {
    // first we need to unpack the list, so we can see all facets
    $this->unpackFacetLists();

    // Now find all the checkboxes on the page
    $found =$this->findAll('css', '.unselected-checkbox');
    if (!$found) {
      return "Didn't find any facets on the page.";
    }

    return $this->getLargestFacetAndClickIt($found, true);
  }

}