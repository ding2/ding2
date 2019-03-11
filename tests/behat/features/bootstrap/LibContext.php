<?php

/**
 * @file
 * Implements step definitions for general-purpose steps
 */

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
use Page\ObjectPage;

/**
 * Defines application features from the specific context.
 */
class LibContext implements Context, SnippetAcceptingContext {

  /**
   * Holder of css-locator strings
   *
   * @var array $cssStr
   */
  public $cssStr;

  /**
   * Holds the name of the current feature being run
   *
   * @var string $currentFeature
   */
  private $currentFeature;

  /**
   * Holds the name of the current scenario being run
   *
   * @var string $currentScenario
   */
  private $currentScenario;

  /**
   * Holds the drupal Context
   *
   * @var \Drupal\DrupalExtension\Context\DrupalContext $drupalContext
   */
  public $drupalContext;

  /**
   * Holds the current user
   *
   * @var array $drupalUser
   */
  public $drupalUser;

  /**
   * Contains the last search string we used
   *
   * @var string $lastSearchString
   */
  public $lastSearchString;

  /**
   * Holds the MinkContext to drive the browser
   *
   * @var \Drupal\DrupalExtension\Context\MinkContext $minkContext
   */
  public $minkContext;

  /**
   * Hold the flag for whether screendumps are created or not. Default they are, but for circleCI they should not be.
   *
   * @var bool $takeScreenDumps
   */
  public $takeScreenDumps;


  /**
   * Current authenticated user. A value of FALSE denotes an anonymous user.
   *
   * @var stdClass|bool $user
   */
  public $user = FALSE;

  /**
   * Holds the flags telling whether we want a very verbose run or a more silent one
   *
   * @var object $verbose
   */
  public $verbose;

  /**
   * LibContext constructor.
   *
   * Initializes context.
   * Every scenario gets its own context instance.
   * You can also pass arbitrary arguments to the
   * context constructor through behat.yml.
   *
   * @param SearchPage $searchPage
   *    Injects the searchPage class.
   * @param DataManager $dataManager
   *    Injects the dataManager class.
   * @param ObjectPage $objectPage
   *    Injects the objectPage class.
   * @param string $NoScreenDump
   *    Retrieved from behat.yml to indicate if screendumps are to be made or not.
   */
  public function __construct(SearchPage $searchPage, DataManager $dataManager, ObjectPage $objectPage, $NoScreenDump) {
    $this->searchPage = $searchPage;
    $this->dataMgr = $dataManager;
    $this->objectPage = $objectPage;
    $this->takeScreenDumps = true;
    if ($NoScreenDump == "true") {
      $this->takeScreenDumps = false;
    }

    // Initialise the verbose structure. These are default settings.
    $this->verbose = (object) array(
      'loginInfo' => true,
      'loginTimingInfo' => false,
      'ScrShotDir' => "",
      'ScrShotUseFeatureFolder' => false,
    );

    // Read in parameters from config-file. Notice its name is hard coded and must be
    // placed in the behat root directory.
    $filename = "behat.config";
    if (is_readable($filename)) {
      // Now open, and read in all lines until no more data is returned.
      $mfilehandle = fopen($filename, "r");
      while (($fline = fgets($mfilehandle)) !== false) {
        if ($fline != "") {
          // Format should be key <tab> value.
          $columns = explode("\t", $fline);
          if (count($columns) != 2) {
            print_r("Error: File '" . $filename . "' is expected to have two columns.");
          }
          if (ord(substr($columns[1], strlen($columns[1]), 1)) < 32) {
            $columns[1] = substr($columns[1], 0, strlen($columns[1]) - 1);
          }
          switch (strtolower($columns[0])) {
            case "scrshotdir":
              $this->verbose->ScrShotDir = $columns[1];
              break;

            case "screenshotusefeaturefolder":
              $this->verbose->ScrShotUseFeatureFolder = $columns[1];
              break;

            case "logintiminginfo":
              $this->verbose->loginTimingInfo = $columns[1];
              break;

          }
        }
      }
      fclose($mfilehandle);
    }
  }

  /**
   * Runs before each scenario.
   *
   * @param BeforeScenarioScope $scope
   *   Contains scope information.
   *
   * @BeforeScenario
   *
   * @throws \Behat\Mink\Exception\DriverException
   *   In case of error.
   */
  public function beforeScenario(BeforeScenarioScope $scope) {
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
            ->resizeWindow(1280, 2000, 'current');
    }
    catch (UnsupportedDriverActionException $e) {
      // Ignore, but make a note of it for the tester.
      print_r("Before Scenario: resizeWindow failed. \n");
    }
  }

  /**
   * Runs after each scenario.
   *
   * If scenario failed: place screenshots in the assigned folder, after resizing window appropriately.
   *
   * @param \Behat\Behat\Hook\Scope\AfterScenarioScope $scope
   *    Built-in parameter.
   *
   * @AfterScenario
   *
   * @throws Exception
   *   When errors happens during screenshot.
   */
  public function afterScenario(\Behat\Behat\Hook\Scope\AfterScenarioScope $scope) {
    if ($scope->getTestResult()->getResultCode() > 0) {
      $this->saveScreenshot();
    }
  }

  /**
   * Step to save a screenshot on demand
   *
   * @Then I save (a) screenshot
   */
  public function saveScreenshot() {
    // Initially check if we are taking screenshots at all. The setting is in the behat.yml file.
    if (!$this->takeScreenDumps) {
      print_r("Due to screendump setting in behat.yml, screendumps are currently not being saved.\n");
      return;
    }

    // Setup folders and make sure the folders exists.
    $screenShotDir = $this->verbose->ScrShotDir;
    $featureFolder = "";
    if ($this->verbose->ScrShotUseFeatureFolder) {
      $featureFolder = preg_replace('/\W/', '', ucwords(strtolower($this->currentFeature)));
      if (!file_exists($screenShotDir . $featureFolder)) {
        mkdir($screenShotDir . $featureFolder);
      }
      // Add the slash to make the following code work in all circumstances.
      $featureFolder = $featureFolder . "/";
    }

    // Setup filename and make sure it is unique, by adding a postfix (simple number).
    $fileName = $screenShotDir . $featureFolder
      . preg_replace('/\W/', '', ucwords(strtolower($this->currentScenario)));
    $fileNamePostfix = "";
    while (file_exists($fileName . $fileNamePostfix . '.png')) {
      $fileNamePostfix++;
    }
    $fileName = $fileName . $fileNamePostfix . '.png';

    // Log the filename of the screenshot to notify the user.
    print_r("Screenshot in: " . $fileName . "\n");

    // Now find the actual height of the shown page.
    $height = $this->minkContext->getSession()->evaluateScript("return document.body.scrollHeight;");
    // Save the screenshot.
    $this->minkContext->getSession()
          ->getDriver()
          ->resizeWindow(1280, $height, 'current');
    file_put_contents($fileName, $this->minkContext->getSession()->getDriver()->getScreenshot());
  }

  /**
   * Implements step to accept the use of cookies agreement.
   *
   * @Given I accept cookies
   *
   * @throws Exception
   *   Checks if cookie acceptance is shown, and accepts it if it is.
   */
  public function acceptCookiesMinimizeAskLibrarianOverlay() {
    // We use the searchPage-instance to deal with cookies.
    $this->check($this->searchPage->acceptCookiesMinimizeAskLibrarianOverlay(), $this->searchPage->getAndClearMessages());
  }

  /**
   * General function to check the outcome of a function and handle the result
   *
   * @param string $result
   *   If non-empty an exception is thrown.
   * @param string $msg
   *   The message to show together with the exception.
   *
   * @throws Exception
   *   In case of error.
   */
  public function check($result, $msg = '') {
    // Log messages if we have any.
    if ($msg !== '') {
      print_r($msg);
    }
    // Fail if we have a non-empty string.
    if ($result !== "") {
      throw new Exception($result);
    }
  }


  /**
   * Implements step to check that the expected number of search results are found after using facets.
   *
   * The methods "I use facets to reduce..." sets $this->>expectedResultsCount and must
   * be used before this is called, otherwise it will fail with that message.
   *
   * @Then I check if the right number of search results are shown
   *
   * @throws Exception
   *    In case of errors.
   */
  public function checkIfTheRightNumberOfSearchResultsAreShown() {
    // Scrape off the search result size from the page. This is displayed on every search result page.
    $resultSize = $this->searchPage->getShownSizeOfSearchResult();
    if ($resultSize < 0) {
      print_r($this->searchPage->getAndClearMessages());
      throw new Exception("Couldn't find a search result size on page.");
    }

    // Now compare to the expected number.
    if ($this->searchPage->getExpectedSearchResultSize() != 0) {
      if ($this->searchPage->getExpectedSearchResultSize() != $resultSize) {
        throw new Exception("Did not find the expected number of posts. (Found: " . $resultSize . ". Expected:" . $this->searchPage->getExpectedSearchResultSize() . ")");
      }
    }
    else {
      throw new Exception("An expected number was never set. Use facets to set it.");
    }
  }

  /**
   * Implement step to check the pagination is correct on all pages.
   *
   * This is meant only to be used after a multipage search when paging is in place.
   * It goes through the latest stored search result and finds a random page which is accessible on the
   * currently displayed page, and go to that one.
   * Notice that the way to move to a particular page is to go to the link /search/thing/<searchcrit>?page=n
   * where n = 1 yields page 2 in the search result (without ?page it defaults to first page).
   * Also notice that not all pages are given as options for the user.
   * On a 10-page result, only 1 + 2 is displayed from the beginning.
   * From page 3 you get "første" + "forrige". On page 1 and 2 you don't.
   *
   * @Then I check pagination on all pages
   *
   * @throws Exception
   *   If errors happens.
   */
  public function checkPaginationOnAllPages() {
    try {
      $this->check($this->searchPage->checkPaginationOnAllPages(), $this->searchPage->getAndClearMessages());
    }
    catch (Exception $e) {
      throw new Exception("Failed: " . $e->getMessage());
    }
    catch (\Page\Exception $e) {
      throw new Exception("Failed getting pages: " . $e->getMessage());
    }
  }

  /**
   * Type text character by character
   *
   * @param string $text
   *    The text to enter into the field.
   * @param string $field
   *    The popular name for the field to enter data into.
   *
   * @When I enter :text in field :field
   *
   * @throws Exception
   *    In case of errors.
   */
  public function enterTextIntoField($text, $field) {
    $found = $this->getPage()->find('css', $this->translateFieldName($field));
    if (!$found) {
      throw new Exception("Couldn't find the field " . $field);
    }
    $found->setValue($text);
  }

  /**
   * Implements step to open the object page of an object from the equivalence class chosen.
   *
   * The equivalence class is chosen by setting the file in another step.
   *
   * @When I display random object from file
   *
   * @throws Exception
   *    In case of errors.
   */
  public function displayRandomObjectFromFile() {
    // Obtain a random PID, but throw an error if we get an error message back instead of a PID.
    $mpid = $this->dataMgr->getRandomPID();
    if (substr($mpid, 0, 5) == "Error") {
      throw new Exception($mpid);
    }

    // Help the tester by showing what was searched for and also which test system we're on.
    print_r("Displaying: " . $this->minkContext->getMinkParameter('base_url')  . "ting/object/" . $mpid . "\n");

    // Now open the page - replace the {id} with the mpid in the path.
    $this->objectPage->open(['id' => urlencode($mpid)]);
    $this->waitForPage();
  }

  /**
   * Implements step to open the object page of all objects in turn from the equivalence class chosen.
   *
   * This is mainly used for testing if the objects are valid, and should not run regulary on every push.
   * The equivalence class is chosen by setting the file in another step.
   *
   * @When I display all objects from file
   *
   * @throws Exception
   *    In case of errors.
   */
  public function displayAllObjectsFromFile() {
    $this->dataMgr->setToFirstInFile();
    while (!$this->dataMgr->EOF()) {
      $mpid = $this->dataMgr->readNextPidFromFile();
      if ($mpid != "") {
        // Help the tester by showing what was searched for and also which test system we're on.
        print_r("Displaying: " . $this->minkContext->getMinkParameter('base_url') . "ting/object/" . $mpid . " ");

        // Now open the page - replace the {id} with the mpid in the path.
        $this->objectPage->open(['id' => urlencode($mpid)]);
        $this->waitForPage();
        if (!$this->getPage()->find("xpath", "//div[contains(@class,'field-name-ting-title')]/h2")) {
          print_r("Failed\n");
        }
        else {
          print_r("OK\n");
          $this->saveScreenshot();
        }
      }

    }
  }

  /**
   * Check for whether the Husk / Tilføj til liste button is shown and visible
   *
   * @Then it is possible to add to a list
   * @Then it should be possible to add to a list
   *
   * @throws Exception
   *    In case of errors.
   */
  public function findAddToAList() {
    $this->check($this->objectPage->hasAddToList());
  }

  /**
   * The function can be used to return the href to the image as well.
   *
   * @Then I (should) see availability options
   *
   * @throws Exception
   *    In case of errors.
   */
  public function findAvailabilityOptions() {
    $this->check($this->objectPage->hasAvailabiltyOptions());
  }

  /**
   * Implements step to check if a cover page is shown.
   *
   * @Then I should see a cover page
   *
   * @throws Exception
   *    In case of errors.
   */
  public function findCoverPage() {
    $this->check($this->objectPage->hasCoverPage());
  }

  /**
   * Check for whether the "Husk / Tilføj til liste" button is shown and visible
   *
   * @Then it is possible to get online access
   * @Then online access button is shown
   *
   * @throws Exception
   *   In case of errors.
   */
  public function findOnlineAccessButton() {
    $this->check($this->objectPage->hasOnlineAccessButton());
  }

  /**
   * Implements step to check that at least one search result post has a particular attribute.
   *
   * @param string $attribute
   *    The attribute to look for.
   *
   * @Then there are posts with :attribute in the search results
   *
   * @throws Exception
   *    In case of error.
   */
  public function findPostsWithXXInTheSearchResult($attribute) {
    $this->check($this->searchPage->checkPostsWithXXInTheSearchResult($attribute, "some"));
  }

  /**
   * Implements step to check that all shown posts in search result has a particular attribute.
   *
   * @param string $attribute
   *    The attribute to look for.
   *
   * @Then all posts have :attribute in the search results
   */
  public function findPostsAllHaveXXInTheSearchResult($attribute) {
    $this->searchPage->checkPostsWithXXInTheSearchResult($attribute, "all");
  }

  /**
   * Implements step to open one of the search results that has a cover page shown.
   *
   * Any of the shown results which have a cover page shown should also have a cover page shown
   * on the detail object view. So it picks one in random.
   * It expects to start on a search result. It scans the page for results, chooses one randomly
   * and opens it up by extracting the pid from the link, and force its way to the ting/object/ prefix
   * This means it does not show a work / collection, if that's where the search would go.
   *
   * @When I open a random search result with (a) cover page to show the post
   *
   * @throws Exception
   *    In case of errors.
   */
  public function findRandomSearchResultWithCoverPageToShowThePost() {
    $this->searchPage->getRandomSearchResultToShowPost("coverpage");
  }

  /**
   * Implements a step to check if a particular relation type is shown.
   *
   * @param string $relType
   *    The relation type to look for.
   *
   * @Then a :relationType entry is shown
   *
   * @throws Exception
   *    In case of error.
   */
  public function findRelationTypeEntryIsShown($relType) {
    $this->check($this->objectPage->entryIsShown($relType));
  }

  /**
   * Implements step to check if a particular relation type is not shown.
   *
   * @param string $relType
   *    The relation type to look for.
   *
   * @Then a :relationType entry is not shown
   *
   * @throws Exception
   *    In case of error.
   */
  public function findRelationTypeEntryNotShown($relType) {
    $this->check($this->objectPage->entryIsNotShown($relType));
  }

  /**
   * Checks for the reserve-button being shown and visible
   *
   * @Then it is possible to click to reserve the material
   *
   * @throws Exception
   *   In case of error.
   */
  public function findReserveMaterialButton() {
    $this->check($this->objectPage->hasReservationButton());
  }

  /**
   * Implements step to check for a title to be present on the first page of a search result.
   *
   * @param string $title
   *   The title to search for.
   *
   * @Then I can see :title in the search results first page
   *
   * @throws Exception
   *   In case of errors.
   */
  public function findTitleInTheSearchResultsFirstPage($title) {
    $title = $this->translateArgument($title);

    $this->check($this->searchPage->findTitleOnPage($title));
  }

  /**
   * GetPage - quick reference to the getPage element. Makes code more readable.
   *
   * @return \Behat\Mink\Element\DocumentElement
   *   returns a page element
   */
  public function getPage() {
    return $this->minkContext->getSession()->getPage();
  }

  /**
   * Implements step to check for a login prompt.
   *
   * @Then I am prompted to login
   *
   * @throws Exception
   *   In case of error.
   */
  public function getPromptToLogin() {
     $this->check($this->objectPage->getPromptToLogin());
  }

  /**
   * Navigate to a page.
   *
   * @todo should only navigate if the path is different from the current.
   *
   * @param string $path
   *   The path to navigate to.
   */
  public function gotoPage($path) {
    $this->minkContext->visit($path);
  }

  /**
   * Go to the search page.
   *
   * @param string $string
   *   String to search for.
   *
   * @Given I have searched for :string
   *
   * @throws Exception
   *   In case of error.
   */
  public function gotoSearchPage($string) {
    // First we try to translate the argument, to see if there's anything we should pick out first.
    $searchString = $this->translateArgument($string);
    $this->logMsg(($this->searchPage->getVerboseSearchResult() == "on"), "Searches for " . urlencode($searchString) . "\n");
    $this->lastSearchString = $searchString;
    $this->gotoPage('/search/ting/' . urlencode($searchString));
  }


  /**
   * Implements step to search for data and put it into a file as known data.
   *
   * @param string $mfile
   *    Filename basis for the two files being created, appended with _pos.mat and _neg.mat.
   * @param string $relation
   *    The relation we are looking for, in opensearch terminology, f.ex. dbcaddi:hasCreatorDescription.
   *
   * @Given I create files :mfile from opensearch on relation :relation
   *
   * @throws ErrorException
   *   In case of error in calling the opensearch service.
   */
  public function ICreateFilesForRelation($mfile, $relation) {
    for ($i = 1; $i < 12000; $i = $i + 50) {
      $this->ICreateFilesForRelationChunk($mfile, $relation, $i);
    }
  }

  /**
   * Helper function for ICreateFilesForRelation.
   *
   * @param string $mfile
   *    Filename base for the two files being created.
   * @param string $relation
   *    The relation we are looking for.
   * @param int $start
   *    The starting point for the service retrieval.
   *
   * @throws ErrorException
   *    In case of fetching from the search fails.
   */
  private function ICreateFilesForRelationChunk($mfile, $relation, $start) {
    // Set up the search as URL.
    $url = "https://oss-services.dbc.dk/opensearch/4.5/";
    $url_search = "?action=search&query=%22term.type=Bog%22";
    $url_params = "&relationData=full";
    $url_auth = "&agency=100200&profile=test&start=" . $start . "&stepValue=50&sort=date_descending";

    // Now do the search.
    $curl = new Curl\Curl();
    $curl->get($url . $url_search . $url_params . $url_auth);

    // Now look at the result.
    // NB: $got_header=$curl->response_headers;
    // $got_body=$curl->response;
    $xml2 = new DOMDocument();
    try {
      $xml2->loadXML($curl->response);
    }
    catch (Exception $e) {
      // Return gracefully.
      return;
    }
    // Find all the titles, this is returned as an array.
    $result = $xml2->getElementsByTagName("object");

    // Reset the counters.
    $cntPos = 0;
    $cntNeg = 0;

    // We always append to files. We create a positive and negative. Positive contains
    // PIDs that have the relation. Negatives don't.
    $outputfilePositive = fopen($mfile . "_Positive.mat", "a");
    $outputfileNegative = fopen($mfile . "_Negative.mat", "a");

    // Now we loop through the results. It's an array of Nodes.
    foreach ($result as $rout) {
      // Ignore anything which is not a collection record.
      if ($rout->parentNode->nodeName == "collection") {
        $mpid = "";
        $mtype = "";
        $mrelations = array();

        // This is where record | relations is which we're looking for.
        // @todo: this would be better as a xpath, I guess, but can't make xpath work on this. It never returns anything.
        foreach ($rout->childNodes as $rc) {
          // Find the record block and retrieve the data we want from there: the type.
          if ($rc->nodeName == 'dkabm:record') {
            foreach ($rc->childNodes as $rc1) {
              if ($rc1->nodeName == "dc:type") {
                $mtype = $rc1->nodeValue;
              }
            }
          }

          // Pick out the PID.
          if ($rc->nodeName == 'primaryObjectIdentifier') {
            $mpid = $rc->nodeValue;
          }

          // Get the relations.
          if ($rc->nodeName == 'relations') {
            $rcrelations = $rc->childNodes;

            // Go through each relation in turn.
            foreach ($rcrelations as $rcrel) {
              // The relationType and relationURI are even a level down from here.
              $rcNodes = $rcrel->childNodes;
              $mRelType = "";
              $mRelURI = "";
              // This is a bit complicated. We try to gather the relationType and relationUri
              // we find, but there might only be a relationObject. Since we need both type
              // and the Uri to make a relation, we scan all childnodes to pick out the values.
              foreach ($rcNodes as $rc1) {
                $mRelType = ($rc1->nodeName == 'relationType') ? $rc1->nodeValue : $mRelType;
                $mRelURI = ($rc1->nodeName == 'relationUri') ? $rc1->nodeValue : $mRelURI;
                // Now we try to see if we can pick out an infomedia relation
                // which is hidden as a full object under the relationObject-node.
                // If only xpath would work, this code could be much simpler and better.
                if ($rc1->nodeName == 'relationObject' && $mRelType == 'ddcaddi:hasOnlineAccess') {
                  foreach ($rc1->childNodes as $rc4) {
                    foreach ($rc4->childNodes as $rc3) {
                      foreach ($rc3->childNodes as $rc2) {
                        if ($rc2->nodeName == "dc:identifier") {
                          if ($rc2->getAttribute("xsi:type") == "dcterms:URI") {
                            $mrelations[] = ['type' => 'accessInfoMedia', 'uri' => $rc2->nodeValue];
                          }
                        }
                      }
                    }
                  }
                }
              }
              // Check if we found a relationType, in which case we add it to the array.
              // Note, that the Uri may be empty. That's okay for this purpose.
              if ($mRelType != "") {
                $mrelations[] = ['type' => $mRelType, 'uri' => $mRelURI];
              }
            }
          }
        }
        // Now let's see if we found the relation we are looking for.
        $positiveFound = false;
        $haveSavedIt = false;
        foreach ($mrelations as $mr1) {
          if ($mr1['type'] == $relation && $mpid != "" && !$haveSavedIt) {
            fwrite($outputfilePositive, $mpid . "\t" . ((strlen($mr1['uri']) > 0) ? $mr1['uri'] : "") . "\t" . $mtype . "\n");
            $positiveFound = true;
            $cntPos++;
            $haveSavedIt = true;
          }
        }
        // Save to the negative file if relation was not found.
        if ($positiveFound == false && $mpid != "") {
          fwrite($outputfileNegative, $mpid . "\t\t" . $mtype . "\n");
          $cntNeg++;
        }
      }
    }
    fclose($outputfilePositive);
    fclose($outputfileNegative);

    // Report to the log what happened.
    print_r("Appended " . $cntPos . " records to the '" . $mfile . "_Positive'-file\n");
    print_r("Appended " . $cntNeg . " records to the '" . $mfile . "_Negative'-file\n");
  }

  /**
   * Step for logging in a user assuming Connie is the provider
   *
   * @Given I am logged in as a library user
   *
   * @When I log in as a library user
   *
   * @throws Exception
   *   In case of error.
   */
  public function iAmLoggedInAsALibraryUser() {
    // If for some reason Mink has not started us up on the site, then navigate there.
    if (strstr($this->minkContext->getSession()->getDriver()->getContent(), "Drupal") == 0) {
      $this->minkContext->getSession()->visit($this->minkContext->getMinkParameter('base_url'));
    };
    // Temporary solution, setting up hardcoded username list. Password is last 4 for Connie Provider.
    $userlist = array();
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

    // Now pick a random one.
    $name = $userlist[random_int(0, count($userlist) - 1)];

    // Set up the user.
    $user = (object) array(
      'name' => $name,
      'pass' => substr($name, -4),
    );
    $this->drupalUser = $user;
    $this->login();

    /*
     * We need the user uid for various reasons, however it's not easily
     * available. Apparently the only place it makes an appearance
     * nowadays is in a class on the body element of the user page. So try
     * to dig it out from there.
     */
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

    /*
     * In addition, make a note of the "id" that is used in paths (which
     * is most often "me"), so we can construct paths as would be
     * expected. We're sniffing this rather than hardcoding it because
     * some users are except from the "me" replacement.
     */
    $link = $this->drupalContext->getSession()->getPage()->findLink('Brugerprofil');
    if (!$link) {
      throw new Exception("Couldn't find link to user profile on the users page");
    }
    $this->user = $user;
  }


  /**
   * Log a user in.
   *
   * @throws Exception
   *   When errors happens.
   */
  public function login() {

    if (!$this->drupalUser) {
      throw new Exception('Tried to login without a user.');
    }

    // It's nice to know in the log who we log in with.
    $this->logMsg(($this->verbose->loginInfo == "on"), "Attempts logging in with user: " . $this->drupalUser->name . "\n");

    $this->logTimestamp(($this->verbose->loginTimingInfo == "on"), " - ");

    $el = $this->minkContext->getSession()->getPage();
    if (!$el) {
      throw new Exception("Couldn't find a page to login from");
    }

    // Find out if we are not logged in on page - body has a certain class.
    $pageclass = $el->find('xpath', '//body[contains(@class, "not-logged-in")]');

    if ($pageclass) {
      // Now we know we are not logged-in. Find the link represented by the login-button in the top.
      $xpath = "//body[contains(@class, 'overlay-is-active')]";
      $libutton = $this->getPage()->find('xpath', $xpath);

      if (!$libutton) {

        /*
         * the overlay is not shown. This is expected.
         * So we interject a bit of javascript to open it.
         * This is actually a copy of the js that actually runs on the page itself
         * but I couldn't get to activate that. This seems to do the same thing,
         * except it cannot remove the mobile-tags, so I commented that out.
         */
        $js = "";
        $js .= "document.querySelector('body').classList.toggle('pane-login-is-open');";
        $js .= "if (document.querySelector('body').classList.contains('pane-login-is-open')) {";
        $js .= "document.querySelector('body').classList.add('overlay-is-active');";
        $js .= "} else {";
        $js .= "document.querySelector('body').classList.remove('overlay-is-active');";
        $js .= "}";

        $this->minkContext->getSession()->executeScript($js);
      }
      else {
        throw new Exception("Did not find the login-button");
      }
    }
    else {
      // We are already logged in?! This should not be possible. Yet, here we are.
      print_r("Apparently we are already logged in?");
    }

    // Now wait until the username field is visible - it's the last one that scrolls into view.
    $this->waitUntilFieldIsFound('css', 'input#edit-name', "Login user-name field is not shown");

    // Check if we can see the password and login-button as well.
    $passwordfield = $this->getPage()->find('css', 'input#edit-pass');
    if (!$passwordfield) {
      throw new Exception("Login password field is not shown");
    }
    $loginknap = $this->getPage()->find('css', 'input#edit-submit');
    if (!$loginknap) {
      throw new Exception("Login button is not on page");
    }
    if (!$loginknap->isVisible() || !$passwordfield->isVisible()) {
      throw new Exception("Login button or password field is not shown/accessible on page.");
    }
    // Now fill in credentials.
    $el->fillField($this->drupalContext->getDrupalText('username_field'), $this->drupalUser->name);
    $el->fillField($this->drupalContext->getDrupalText('password_field'), $this->drupalUser->pass);
    $submit = $el->findButton($this->drupalContext->getDrupalText('log_in'));

    if (empty($submit)) {
      throw new Exception(sprintf("No login button on page %s", $this->drupalContext->getSession()->getCurrentUrl()));
    }

    // Log in.
    $submit->click();

    // Wait until we can see the username displayed.
    $this->waitUntilFieldIsFound('xpath',
          '//div[contains(@class,"pane-current-user-name")]//div[contains(@class,"pane-content")]/text()[contains(.,"' . $this->drupalUser->name . '")]/..',
          "Did not find the users name displayed on page");

    // Check if we are logged in drupal-wise.
    if (!$this->drupalContext->loggedIn()) {
      throw new Exception(sprintf("Could not log on as user: '%s'", $this->drupalUser->name));
    }

    $this->logTimestamp(($this->verbose->loginTimingInfo == "on"), " - OK\n");
  }

  /**
   * Log_msg - prints message on log if condition is true.
   *
   * @param bool $ifTrue
   *   Indicates if the message is to be printed or not.
   * @param string $msg
   *   The actual message to show if condition is true.
   */
  public function logMsg($ifTrue, $msg) {
    if ($ifTrue) {
      print_r($msg);
    }
  }

  /**
   * Log_timestamp - puts a timestamp in the log. Good for debugging timing issues.
   *
   * @param bool $ifTrue
   *   Indicates if the message is to be shown or not.
   * @param string $msg
   *   The actual message to show.
   */
  public function logTimestamp($ifTrue, $msg) {
    // This is so we can use this function with verbose-checking.
    if ($ifTrue) {
      // Get the microtime, format it and print it.
      $t = microtime(true);
      $micro = sprintf("%06d", ($t - floor($t)) * 1000000);
      $d = new DateTime(date('Y-m-d H:i:s.' . $micro, $t));
      print_r($msg . " " . $d->format("Y-m-d H:i:s.u") . "\n");
    }
  }

  /**
   * Scrape off all the search results for further analysis and reference.
   *
   * This retrieves the search result and stores it in the local array searchResults.
   * There can be several search results, so some garbage collection needs to be done.
   * The searchResult array will be reset before each scenario.
   *
   * @Then paging allows to get all the results
   *
   * @throws Exception
   *   In case of errors.
   */
  public function pagingAllowsToGetAllResults() {
    try {
      $this->check($this->searchPage->getEntireSearchResult(), ($this->searchPage->getVerboseSearchResult() == "on") ? $this->searchPage->getAndClearMessages() : '');
    }
    catch (Exception $e) {
      throw new Exception("Failed: " . $e->getMessage());
    }
    catch (\Page\Exception $e) {
      throw new Exception("Failed: " . $e->getMessage());
    }
  }

  /**
   * Make a reservation.
   *
   * @When I try to reserve the material
   *
   * @throws Exception
   *    In case of error.
   */
  public function reserveTheMaterial() {

    try {
      $this->findReserveMaterialButton();
      $this->check($this->objectPage->makeReservation());
    }
    catch (Exception $e) {
      throw new Exception("Failed: " . $e->getMessage());
    }
    catch (\Page\Exception $e) {
      throw new Exception("Failed: " . $e->getMessage());
    }

  }

  /**
   * Scroll to bottom of page
   *
   * @When I scroll to the bottom (of the page)
   *
   * @throws Exception
   *    In case of error.
   */
  public function scrollToBottom() {
    $found = $this->getPage()->find('css', 'footer.footer');
    if (!$found) {
      $this->scrollTo($found);
    }
  }

  /**
   * Scroll a bit up.
   *
   * @param string $pixels
   *    The number of pixels to scroll up.
   *
   * @When I scroll :pixels pixels
   */
  public function scrollABit($pixels) {
    $this->minkContext->getSession()->executeScript('window.scrollBy(0, ' . $pixels . ');');
  }

  /**
   * Scroll to an element.
   *
   * @param ElementInterface $element
   *   Element to scroll to.
   *
   * @throws Exception
   *   The exception we throw in case of error.
   */
  public function scrollTo(ElementInterface $element) {
    // Translate the xpath of the element by adding \\ in front of " to allow it to be passed in the javascript.
    $xpath = strtr($element->getXpath(), ['"' => '\\"']);
    try {
      $js = '';
      $js = $js . 'var el = document.evaluate("' . $xpath .
            '", document, null, XPathResult.FIRST_ORDERED_NODE_TYPE, null).singleNodeValue;';
      $js = $js . 'document.body.scrollTop = document.documentElement.scrollTop = 0;';
      $js = $js . 'el.scrollIntoViewIfNeeded(true);';
      // $js = $js . 'el.scrollIntoView(true);';
      $this->minkContext->getSession()->executeScript($js);
    }
    catch (UnsupportedDriverActionException $e) {
      // Ignore.
    }
    catch (Exception $e) {
      throw new Exception('Could not scroll to element: ' . $e->getMessage());
    }
  }

  /**
   * Makes a series of searches until the search result is satisfactory.
   *
   * The method will use all the listOfTerms, but alter the dates published until a satisfactory
   * amount of results are found. It will try first only the earliest year (ex. 1995) and if too
   * few, then it will add another year - and keep adding years until it reaches 2017. If still too
   * few with the full interval, it will fail.
   * If too many, it will move up one year, until it has tried all years.
   * With verbose of searchResults = on it will log it's attempts.
   * If unable to reach a searchresult of the wanted size it will fail.
   *
   * @param string $interval
   *    Acceptable interval of search result. Given in form "50-75".
   * @param string $listOfTerms
   *    Restrictive search term, f.ex. "term.type=ebog;term.publisher=Gyldendal".
   * @param string $publishedBetween
   *    Year interval of publishing, f.ex. "1995-2017".
   *
   * @Given I want a search result between :interval using :listOfTerms published between :publishedInterval
   *
   * @throws Exception
   *    In case of search error or a suitable result cannot be found.
   */
  public function searchForResultOfCertainSizeUsingInterval($interval, $listOfTerms, $publishedBetween) {
     $this->check($this->searchPage->searchForCertainSize($interval, $listOfTerms, $publishedBetween), $this->searchPage->getAndClearMessages());
  }

  /**
   * Implements step to perform the current search on the library's home page.
   *
   * @When I search internally on the home page
   *
   * @throws Exception
   *   Happens in case of errors.
   */
  public function searchOnHomePage() {
    try {
      $this->check($this->searchPage->searchOnHomePage());
    }
    catch (Exception $e) {
      throw new Exception("Failed: " . $e->getMessage());
    }
    catch (\Page\Exception $e) {
      throw new Exception("Failed: " . $e->getMessage());
    }
  }

  /**
   * Implements step to set the current file.
   *
   * @param string $file
   *    Filename to use. The file should be in the behat root dir.
   *
   * @Given filename :file is used
   */
  public function setFilename($file) {
    $this->dataMgr->setFilename($file);
  }

  /**
   * Sets the control or verbose mode of the run, controlling how much info is put into the output log.
   *
   * @param string $area
   *    The key to the setting.
   * @param string $onoff
   *    The value to set - on or off.
   *
   * @Given I want verbose mode for :area to be :onoff
   * @Given I set verbose mode for :area to be :onoff
   * @Given I set control mode for :area to be :onoff
   */
  public function setVerboseControlMode($area, $onoff) {
    $area = mb_strtolower($area);
    $onoff = mb_strtolower($onoff);
    switch ($area) {
      // This tells if we want to know the username we logged in with.
      case 'login':
      case 'logininfo':
        $this->verbose->loginInfo = $onoff;
        if ($onoff == 'on') {
          print_r("Verbose mode of loginInfo set to on");
        }
        break;

        // This indicates if we want to see in the log what was found in the searches.
      case 'search-results':
      case 'search-result':
      case 'searchresults':
        $this->searchPage->setVerboseSearchResult($onoff);
        if ($onoff == 'on') {
          print_r("Verbose mode of searchResults set to on");
        }
        break;

        // This indicates if we want to know about handling cookie-popups.
      case 'cookie':
      case 'cookies':
        $this->searchPage->setVerboseCookieMode($onoff);

        if ($onoff == 'on') {
          print_r("Verbose mode of cookie-handling set to on");
        }
        break;

        // This setting controls how many search result pages we will traverse during testing.
      case 'searchmaxpages':

        $this->searchPage->setMaxPageTraversals($onoff);

        // Always notify the user of this setting.
        print_r("Verbose mode for max number of search result pages set to " . $onoff);
        print_r("\n");
        break;

        // This is the catch-all setting.
      case 'everything':
      case 'all':
        $this->verbose->loginInfo = $onoff;
        $this->searchPage->setVerboseSearchResult($onoff);
        $this->searchPage->setVerboseCookieMode($onoff);
        break;

        // If we don't recognise this, let the user know, but don't fail on it.
      default:
        print_r("Unknown verbose mode:" . $area);
        print_r("\n");
        break;

    }
  }


  /**
   * Implements step to indicate that only reservable material is to be found.
   *
   * @Given (I) only (want) reservables
   */
  public function setReservables() {
    $this->dataMgr->setReservable(true);
  }

  /**
   * Print out information about the browser being used for the testing
   *
   * @Given you tell me the current browser name
   * @Given you tell me the current browser
   * @Given you show me the current browser name
   * @Given you reveal the browser
   */
  public function showTheBrowser() {
    $session = $this->minkContext->getSession();
    $driver = $session->getDriver();
    $userAgent = $driver->evaluateScript('return navigator.userAgent');
    $provider = $driver->evaluateScript('return navigator.vendor');
    $browser = null;
    if (preg_match('/google/i', $provider)) {
      // Using chrome.
      $browser = 'chrome';
    }
    elseif (preg_match('/firefox/i', $userAgent)) {
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
   * Implements step to sort the search result by choosing in the dropdown.
   *
   * @param string $sortOption
   *    The option sort by.
   *
   * @When I sort the search result on :sortOption
   *
   * @throws Exception
   *   When errors are met.
   */
  public function sortTheSearchResultOnOption($sortOption) {
    // Check that the user asked for a valid sort-option.
    try {
      $this->check($this->searchPage->sortOptionValid($sortOption));
      $this->check($this->searchPage->sort($sortOption));
    }
    catch (\Behat\Mink\Exception\ElementNotFoundException $e) {
      throw new Exception("Failed in sorting: " . $e->getMessage());
    }
    catch (Exception $e) {
      throw new Exception("Failed in sorting: " . $e->getMessage());
    }
    catch (\Page\Exception $e) {
      throw new Exception("Failed in sorting: " . $e->getMessage());
    }
  }

  /**
   * Attempts to translate argument given in gherkin script.
   *
   * This allows for generic arguments to be given, to be replaced during runtime here either
   * by looking up values on the current page, or substitute from a catalogue/known variable value
   * The convention is to initiate a variable with a dollar-sign followed by <choice> : <source>
   * choice is the way to select between several values that originates from the source.
   * It could be 'random', 'first', 'last' or simply 'get', if there's only one value possible.
   * Source is pointing to where the value should come from.
   * 'nyhed' looks up news placed on the front page. If not on the front page - this will fail.
   *
   * @param string $string
   *    The argument given.
   *
   * @return mixed
   *    The translated argument, or the original if no translation was made.
   *
   * @throws Exception
   *   Throws exception in case of error.
   */
  public function translateArgument($string) {
    // If we can't translate it, we just pass it right back.
    $returnString = $string;
    if (substr($string, 0, 1) == "$") {
      // Try to translate it. Form is $ <choice> : <source>!
      $lstr = substr($string, 1);
      $cmdArr = explode(":", $lstr);
      if (count($cmdArr) != 2) {
        throw new Exception("Argument given does not follow \$modifier:source, ex. \$random:news. Got: " . $lstr);
      }

      // Here we try to figure out what to translate to.
      switch (strtolower($cmdArr[1])) {
        // Find news (presuming to be on the front page, otherwise fail), choose between them and return the value.
        case "news":
          $foundArr = $this->getPage()->findAll('css', '.news-text h3.title');
          if (!$foundArr) {
            throw new Exception("Argument for a news item. Could not find any news on the page. Make sure the browser is on the front page when running this command.");
          }
          // Only first, last and random works with nyheder as choice.
          switch (strtolower($cmdArr[0])) {
            case 'first':
              $returnString = $foundArr[0]->getText();
              break;

            case 'last':
              $returnString = $foundArr[count($foundArr) - 1]->getText();
              break;

            case 'random':
              $i = random_int(0, count($foundArr) - 1);
              $returnString = $foundArr[$i]->getText();
              break;

            default:
              throw new Exception("Only 'first', 'last' og 'random' can be modifiers for 'news'");
          }
          break;

        // Replace the value with the last known search string.
        case 'lastsearchstring':
          // Regardless of the choice.
          $returnString = $this->lastSearchString;
          break;

        default:
          throw new Exception("Unknown \$modifier:source combination: " . $string);
          break;

      }
    }
    if ($returnString != $string) {
      // We always want to tell this, otherwise the tester cannot figure out what was done.
      print_r("Replaced " . $string . " with " . $returnString);
      print_r("\n");
    }
    return $returnString;
  }


  /**
   * Translate popular name to css field name
   *
   * @param string $field
   *   Popular name.
   *
   * @return string
   *   Translated to css field name from popular name. If unknown, input is returned.
   */
  private function translateFieldName($field) {
    $result = $field;
    switch (strtolower($field)) {
      case "search":
      case "searchfield":
        $result = "input#edit-search-block-form--2";
        break;

    }
    return $result;
  }

  /**
   * Runs through the facets and deselects one. Note, this will fail if facets have not been selected already
   *
   * @When I deselect a facet to increase the search results
   *
   * @throws Exception
   *   In case of error.
   */
  public function useFacetsToIncreaseSearchResults() {
    // Start by logging what we start out with and also reduce the stack to the new expected result.
    print_r("Current number of results: " . $this->searchPage->getShownSizeOfSearchResult() . "\n");
    print_r("Expecting now: " . $this->searchPage->getExpectedSearchResultSize(true) . "\n");

    try {
      $this->check($this->searchPage->useFacetsToIncreaseSearchResults(), $this->searchPage->getAndClearMessages());
    }
    catch (Exception $e) {
      throw new Exception("Failed: " . $e->getMessage());
    }
    catch (\Page\Exception $e) {
      throw new Exception("Failed: " . $e->getMessage());
    }
  }

  /**
   * Implements step to navigate to a specific page using the paging mechanism
   *
   * @param int $toPage
   *   is expected to be numeric. First page is 1.
   *
   * @When I use pagination to go to page :toPage
   *
   * @throws Exception
   *   When errors occurs.
   */
  public function usePaginationToGoToPageN($toPage) {
    // Start by scrolling to the footer so if we fail the screendump will tell us something.
    try {
      $this->searchPage->scrollToBottom();
    }
    catch (\Page\Exception $e) {
      throw new Exception("Failed: " . $e->getMessage());
    }

    // This will return the page number.
    $curpg = $this->searchPage->getCurrentPage();

    // Only change page if we are not already on it.
    if ($curpg != $toPage) {
      try {
        $this->check($this->searchPage->goToPage($toPage));
      }
      catch (Exception $e) {
        throw new Exception("Failed in go to Page " . $e->getMessage());
      }
      catch (\Page\Exception $e) {
        throw new Exception("Failed in going to Page: " . $e->getMessage());
      }
    }
  }

  /**
   * Runs through the facets and selects the highest number of results possible
   *
   * @When I use facets to reduce the search results to the highest possible
   *
   * @throws Exception
   *   In case of error.
   */
  public function useFacetsToReduceSearchResultsToTheHighestPossible() {
    // Start by initialising the stack if necessary and reveal which number we are starting with.
    if ($this->searchPage->getExpectedSearchResultSize() < 0) {
      $this->searchPage->setExpectedSearchResultSize($this->searchPage->getShownSizeOfSearchResult());
    }
    print_r("Current number of results: " . $this->searchPage->getShownSizeOfSearchResult() . "\n");

    try {
      $this->check($this->searchPage->useFacetsToReduceSearchResultsToTheHighestPossible(), $this->searchPage->getAndClearMessages());
    }
    catch (Exception $e) {
      throw new Exception("Failed: " . $e->getMessage());
    }
    catch (\Page\Exception $e) {
      throw new Exception("Failed: " . $e->getMessage());
    }
  }

  /**
   * Wait for page to load.
   *
   * @throws Exception
   *    In case of error.
   */
  public function waitForPage() {
    try {
      // Strictly, this waits for jQuery to be loaded, but it seems sufficient.
      $this->drupalContext->getSession()->wait(5000, 'typeof window.jQuery == "function"');
    }
    catch (UnsupportedDriverActionException $e) {
      // Ignore.
    }
    catch (Exception $e) {
      throw new Exception("Unknown error while awaiting page to load:" . $e);
    }
  }


  /**
   * Implements step to sort the search result with a particular sort order.
   *
   * @param string $sortOption
   *    What the sorting should be made on.
   *
   * @Then the search result is sorted on :sortOption
   *
   * @throws Exception
   *   In case of errors.
   */
  public function checkSearchResultIsSortedOnSortOption($sortOption) {
    // Check that the user asked for a valid sort-option.
    try {
      $this->check($this->searchPage->sortOptionValid($sortOption));
      $this->check($this->searchPage->checkSorting($sortOption), $this->searchPage->getAndClearMessages());
    }
    catch (Exception $e) {
      throw new Exception("Failed " . $e->getMessage());
    }
    catch (\Page\Exception $e) {
      throw new Exception("Failed with " . $e->getMessage());
    }
  }

  /**
   * Wait for element to be visible
   *
   * @param string $locatortype
   *   Whether we are looking for an xpath or css locator.
   * @param string $locator
   *   The locator address to search for.
   * @param string $errmsgIfFails
   *   The error message to display in case of error.
   *
   * @throws Exception
   *   In case of error.
   */
  public function waitUntilFieldIsFound($locatortype, $locator, $errmsgIfFails) {
    $field = $this->getPage()->find($locatortype, $locator);

    // Timeout is 30 seconds.
    $maxwait = 30;
    while (--$maxwait > 0 && !$field) {
      sleep(1);

      // Try to find it again, if necessary.
      if (!$field) {
        $field = $this->getPage()->find($locatortype, $locator);
      }
    }
    if (!$field) {
      throw new Exception("Waited 30 secs but: " . $errmsgIfFails);
    }
  }

  /**
   * Implements step to wait until a text disappears.
   *
   * @param int $waitmax
   *    Number of waits of 300 ms.
   * @param string $txt
   *    Text that we wait for will disappear.
   *
   * @When waiting up to :waitmax until :txt goes away
   */
  public function waitUntilTextIsGone($waitmax, $txt) {
    $wait = $this->getPage()->find('xpath', "//text()[contains(.,'" . $txt . "')]/..");
    $continueWaiting = true;
    if (!$wait) {
      return;
    }
    try {
      $continueWaiting = ($wait->isVisible()) ? true : false;

    }
    catch (Exception $e) {
      // Ignore.
    }
    while ($continueWaiting and --$waitmax > 0) {
      usleep(300);
      $wait = $this->getPage()->find('xpath', "//text()[contains(.,'" . $txt . "')]/..");
      if ($wait) {
        try {
          $continueWaiting = $wait->isVisible();
        }
        catch (Exception $e) {
          // Ignore.
        }
      }
      else {
        $continueWaiting = false;
      }
    }
  }

  /**
   * Implements step to wait until text appears.
   *
   * @param string $txt
   *    Text that we wait for will appear.
   * @param int $seconds
   *    Number of seconds to wait.
   *
   * @Then :txt should appear within :seconds seconds
   *
   * @throws \WebDriver\Exception\NoSuchElement
   *    If text does not appear
   */
  public function waitUntilTextAppears(string $txt, int $seconds) {
    $end = microtime(true) + $seconds;
    do {
      $textElement = $this->getPage()->find('xpath', "//text()[contains(.,'" . $txt . "')]/..");
      if ($textElement && $textElement->isVisible()) {
        return;
      }
      usleep(300);
    } while (microtime(true) < $end);

    throw new \WebDriver\Exception\NoSuchElement(sprintf('Text "%s" not found after %d seconds', $txt, $seconds));
  }

  /**
   * Implements step to wait a given number of seconds, then test that text is not visible.
   *
   * Using this step will always cause the execution to be paused for the given number of
   * seconds so use sparingly. The reason is that we have no way to detect when ajax loads
   * are finished and therefore no way to know when it is "safe" to look for the text.
   *
   * @Then :txt should not appear within :seconds seconds
   *
   * @param string $txt
   *    Text that must not appear.
   * @param int $seconds
   *    Number of seconds to wait.
   *
   * @throws \Behat\Mink\Exception\ElementTextException
   */
  public function waitAndLookForText(string $txt, int $seconds) {
    sleep($seconds);
    $textElement = $this->getPage()->find('xpath', "//text()[contains(.,'" . $txt . "')]/..");
    if(!$textElement) {
      return;
    }

    throw new \Behat\Mink\Exception\ElementTextException(sprintf('Text "%s" was found after %d seconds, but should NOT appear', $txt, $seconds));
  }
}
