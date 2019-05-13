<?php

/**
 * @file
 * This file does not contain any code.
 *
 * Instead code is placed in LibContext.php and StepsContext.php.
 * Place generally applicable functions in LibContext and specific step implementations
 * in StepsContext.
 */

use Behat\Behat\Context\Context;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;

/**
 * Defines application features from the specific context.
 */
// phpcs:disable PSR1.Classes.ClassDeclaration.MissingNamespace
class FeatureContext implements Context, SnippetAcceptingContext
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
}
