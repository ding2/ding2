<?php

use Behat\Behat\Context\Context;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Behat\Tester\Exception\PendingException;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;
use Behat\Mink\Exception\UnsupportedDriverActionException;

/**
 * Defines application features from the specific context.
 */
class StepsContext implements Context, SnippetAcceptingContext {

  /** @var libContext */
  private $libContext;


  /**
   * Initializes context.
   *
   * Every scenario gets its own context instance.
   * You can also pass arbitrary arguments to the
   * context constructor through behat.yml.
   */
  public function __construct() {

  }

  /** @BeforeScenario */
  public function gatherContexts(BeforeScenarioScope $scope)
  {
    $environment = $scope->getEnvironment();

    $this->libContext = $environment->getContext('LibContext');
  }

  /**
   * @Then I can see :regexp somewhere in the search result
   */
  public function iCanSeeRegexpSomewhereInSearchResult($regexp) {
    $regexp = $this->libContext->translateArgument($regexp);

    $this->libContext->getEntireSearchResult();

    // now run through the entire search result to see if the title is there
    $lb_found = false;
    $xte = 0;
    for ($i=0; $i<count($this->libContext->searchResults); $i++) {
      if (preg_match('/' . $regexp . '/', $this->libContext->searchResults[$i]->title) ) {
        $lb_found = true;
        $this->libContext->logMsg(($this->libContext->verbose->searchResults == 'on'), "Fandt " . $regexp . " på side " . $this->libContext->searchResults[$i]->page . " listet som nummer " . $this->libContext->searchResults[$i]->item . "\n");
      }
      $xte = $xte + 1;
    }

    if (!$lb_found ) {
      throw new Exception("Did not find " . $regexp . " in the search result. Looked through " . $this->libContext->verbose->searchMaxPages . " pages.");
    }
  }

  /**
   * @Then I get suggestions from openscan
   */
  public function iGetSuggestionsFromOpenscan() {
    // we need to enable a wait because we cannot control the timing
    $max = 300;
    $found = $this->libContext->getPage()->find('css', 'div#autocomplete');

    while (--$max>0 && !$found) {
      usleep(100);
      $found = $this->libContext->getPage()->find('css', 'div#autocomplete');
    }

    // report error if we ran out of time
    if (!$found) {
      throw new Exception ("Openscan did not show any suggestions. ");
    }

    // it also takes a bit for the page to get the dynamics of the suggestions done. So we wait again
    $max = 300;
    $cnt=0;
    while (--$max>0 && !$found->findAll("css", "li")) {
      usleep(100);
      // refresh the search
      $found = $this->libContext->getPage()->find('css', 'div#autocomplete');
    }

    // now we list the suggestions given.
    foreach ($found->findAll("css", "li") as $suggestion) {
      print_r($suggestion->getText() . "\n");
      $cnt++;
    }
    if ($cnt==0) {
      throw new Exception ("No suggestions were found.");
    }
    // all we can do is list the number for convenience. It's in the configuration how many there should be.
    print_r("In total " . $cnt . " suggestions were shown. Check configurationen.");

  }

}
