<?php

/**
 * @file
 * Here are the steps being implemented.
 */

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
// phpcs:disable PSR1.Classes.ClassDeclaration.MissingNamespace
class StepsContext implements Context, SnippetAcceptingContext
{

    /**
     * This is the context variable
     *
     * @var libContext
     *   This is the context var
     */
    private $libContext;

    /**
     * Sets up things before each scenario
     *
     * @param BeforeScenarioScope $scope
     *    Built-in value of the scope. Part of the behat framework.
     *
     * @BeforeScenario
     */
    public function gatherContexts(BeforeScenarioScope $scope)
    {
        $environment = $scope->getEnvironment();

        $this->libContext = $environment->getContext('LibContext');
    }

    /**
     * Implements step to check for a pattern in the search result.
     *
     * The pattern is given in a popular name, and then
     * translated to a regular expression format.
     *
     * @param string $pattern
     *    The popular pattern to search for.
     *
     * @Then I can see :pattern somewhere in the search result
     *
     * @throws Exception
     *    In case of errors.
     */
    public function iCanSeeRegexpSomewhereInSearchResult($pattern)
    {

        $result = $this->libContext->searchPage->getEntireSearchResult();
        if ($result != "") {
            print_r($this->libContext->searchPage->getMessages());
            throw new Exception($result);
        }

        $pattern = $this->libContext->translateArgument($pattern);
        if (!$this->libContext->searchPage->findRegEx($pattern)) {
            throw new Exception("Did not find " . $pattern . " in the search result. Looked through " .
                                $this->libContext->searchPage->getMaxPageTraversals() . " pages.");
        }
    }

    /**
     * Implements step to check that openscan suggestions are given.
     *
     * Note this requires that openscan is enabled in the configuration.
     *
     * @Then I get suggestions from openscan
     *
     * @throws Exception
     *   In case of errors.
     */
    public function iGetSuggestionsFromOpenscan()
    {
        $result = $this->libContext->searchPage->getOpenScanSuggestions();
        $this->libContext->logMsg(true, $this->libContext->searchPage->getAndClearMessages());
        if ($result != "") {
            throw new Exception($result);
        }

        // We need to enable a wait because we cannot control the timing.
        $max = 300;
        $found = $this->libContext->getPage()->find('css', 'div#autocomplete');

        while (--$max > 0 && !$found) {
            usleep(100);
            $found = $this->libContext->getPage()->find('css', 'div#autocomplete');
        }

        // Report error if we ran out of time.
        if (!$found) {
            throw new Exception("Openscan did not show any suggestions. ");
        }

        // It also takes a bit for the page to get the dynamics of the suggestions done. So we wait again.
        $max = 300;
        $cnt = 0;
        while (--$max > 0 && !$found->findAll("css", "li")) {
            usleep(100);
            // Refresh the search.
            $found = $this->libContext->getPage()->find('css', 'div#autocomplete');
        }

        // Now we list the suggestions given.
        foreach ($found->findAll("css", "li") as $suggestion) {
            print_r($suggestion->getText() . "\n");
            $cnt++;
        }
        if ($cnt == 0) {
            throw new Exception("No suggestions were found.");
        }
        // All we can do is list the number for convenience. It's in the configuration how many there should be.
        print_r("In total " . $cnt . " suggestions were shown. Check configurationen.");
    }
}
