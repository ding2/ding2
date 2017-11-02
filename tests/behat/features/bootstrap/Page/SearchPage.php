<?php


namespace Page;




class SearchPage extends PageBase
{

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
   * @var string $verboseSearchResults
   *
   */
  protected $verboseSearchResults = 'off';

  /**
   *   Building the entire search result into an array
   */

  /**
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
   * @return int
   * Set the maximum number of pages we want to traverse to scrape off the search result.
   */
  public function getMaxPageTraversals() {
    return $this->maxPageTraversals;
  }

  public function getSearchResultSize() {
    return count($this->searchResults);
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
   * @return string
   * Returns and resets the log messages. They can only be read once.
   */
  public function getMessages() {
    return $this->messageCollection;
    $this->messageCollection = "";
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

  public function setVerboseSearchResult($onoff) {
    $this->verboseSearchResults = $onoff;
  }

}