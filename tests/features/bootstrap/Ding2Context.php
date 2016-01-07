<?php

use Behat\Behat\Context\Context;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Behat\Tester\Exception\PendingException;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;

/**
 * Provides step definitions for interacting with Ding2.
 */
class Ding2Context implements Context, SnippetAcceptingContext
{
    /**
     * Initializes context.
     *
     * Every scenario gets its own context instance.
     * You can also pass arbitrary arguments to the
     * context constructor through behat.yml.
     */
    public function __construct()
    {
    }

    /** @var \Drupal\DrupalExtension\Context\DrupalContext */
    private $drupalContext;

    /**
     * @var \Drupal\DrupalExtension\Context\MinkContext
     */
    private $minkContext;

    /** @BeforeScenario */
    public function gatherContexts(BeforeScenarioScope $scope)
    {
        $environment = $scope->getEnvironment();

        $this->drupalContext = $environment->getContext('Drupal\DrupalExtension\Context\DrupalContext');
        $this->minkContext = $environment->getContext('Drupal\DrupalExtension\Context\MinkContext');
    }

    /**
     * @Given I am logged in as a library user
     * @When I log in as a library user
     */
    public function iAmLoggedInAsALibraryUser()
    {
        $name = $this->drupalContext->getRandom()->name(8);
        $user = (object) array(
            'name' => $name,
            'pass' => substr($name, -4),
        );
        $this->drupalContext->user = $user;
        $this->drupalContext->login();
    }

}
