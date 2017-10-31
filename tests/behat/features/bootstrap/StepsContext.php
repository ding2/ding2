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
  public function i_can_see_regexp_somewhere_in_search_result($regexp)
  {

    $regexp = $this->libContext->translate_argument($regexp);

    $this->libContext->get_entire_search_result();

    // now run through the entire search result to see if the title is there
    $lb_found = false;
    $xte = 0;
    for ($i=0;$i<count($this->libContext->searchResults);$i++)
    {
      if (preg_match('/' . $regexp . '/', $this->libContext->searchResults[$i]->title) ) {
        $lb_found = true;
        $this->libContext->log_msg(($this->libContext->verbose->searchResults == 'on'), "Fandt " . $regexp . " på side " . $this->libContext->searchResults[$i]->page . " listet som nummer " . $this->libContext->searchResults[$i]->item . "\n");
      }

      $xte = $xte + 1;
    }

    if (!$lb_found ) {
      throw new Exception("Fandt ikke " . $regexp . " i søgeresultatet på nogen side");
    }
  }

}
