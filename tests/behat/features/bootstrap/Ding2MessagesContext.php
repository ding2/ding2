<?php

use Behat\Behat\Context\Context;
use Behat\Behat\Hook\Scope\AfterScenarioScope;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;

/**
 * Context that checks Drupal messages.
 *
 * In particular it'll fail scenarios that have error messages that's
 * unaccounted for. Tag a scenario with @no_messages_check to suppress.
 */
class Ding2MessagesContext implements Context
{
    /**
     * Hash of last seen page URL and messages.
     *
     * @var string
     */
    private $lastHash = null;

    /**
     * Collection of messages for pages seen.
     *
     * @var array
     */
    private $messages = [];

    /** @var \Drupal\DrupalExtension\Context\MinkContext */
    private $minkContext;

    /** @BeforeScenario */
    public function gatherContexts(BeforeScenarioScope $scope)
    {
        $environment = $scope->getEnvironment();

        $this->minkContext = $environment->getContext('Drupal\DrupalExtension\Context\MinkContext');
    }

    /**
     * Extract messages from current page.
     *
     * @param string $type
     *   Type of messages to extract (warning or error)
     *
     * @return array
     *   Array of messages.
     */
    protected function getMessages($type)
    {
        $messages = [];
        $messageGroups = $this->minkContext->getSession()->getPage()->findAll("css", '.messages.' . $type);
        foreach ($messageGroups as $group) {
            $groupMessages = $group->findAll('css', 'li');
            if ($groupMessages) {
                foreach ($groupMessages as $groupMessage) {
                    $messages[] = $groupMessage->getText();
                }
            } else {
                // Single messages isn't wrapped in a <li>. The title is
                // invisible, hook onto that.
                $header = $group->find('css', '.element-invisible')->getText();
                // Remove the header text from the message.
                $messages[] = trim(str_replace($header, '', $group->getText()));
            }
        }
        return $messages;
    }

    /**
     * Collect messages.
     *
     * @AfterStep
     */
    public function collectMessages()
    {
        $messages = [];
        $currentUrl = $this->minkContext->getSession()->getCurrentUrl();

        // Collect both warnings an errors.
        $messages = [
            'warning' => $this->getMessages('warning'),
            'error' => $this->getMessages('error'),
        ];

        $hash = hash('sha1', serialize([$currentUrl, $messages]));

        // We skip if the it's equal to the last. It's assumed that the
        // browser haven't navigated.
        if ($hash !== $this->lastHash) {
            $this->lastHash = $hash;
            if ($messages['warning'] || $messages['error']) {
                if (isset($this->messages[$currentUrl])) {
                    $this->messages[$currentUrl] = array_merge_recursive($this->messages[$currentUrl], $messages);
                } else {
                    $this->messages[$currentUrl] = $messages;
                }
            }
        }
    }

    /**
     * Throw exception if unaccounted messages exists.
     *
     * @AfterScenario
     */
    public function checkMessages(AfterScenarioScope $scope)
    {
        // The docs state that the scenario should also return the feature
        // tags, but that doesn't seem to be the case.
        if ($scope->getScenario()->hasTag('no_messages_check') ||
            $scope->getFeature()->hasTag('no_messages_check')) {
            return;
        }

        $errorMessages = ['warning' => [], 'error' => []];
        foreach (['warning', 'error'] as $type) {
            foreach ($this->messages as $url => $messages) {
                foreach ($messages[$type] as $message) {
                    $errorMessages[$type][] = 'On page ' . $url . ': "' . $message . '"';
                }
            }

            if ($errorMessages[$type]) {
                $errorMessages[$type] = "Unexpected " . $type .
                    " messages during scenario:\n" .
                    implode("\n", $errorMessages[$type]) . "\n";
            } else {
                unset($errorMessages[$type]);
            }
        }

        if ($errorMessages) {
            throw new Exception(implode("\n", $errorMessages));
        }
    }

    /**
     * @Then /^I should see the (?P<type>error|warning) message "(?P<message>(?:[^"]|\\")*)"$/
     */
    public function iShouldSeeTheErrorMessage($type, $message)
    {
        $currentUrl = $this->minkContext->getSession()->getCurrentUrl();

        if (isset($this->messages[$currentUrl][$type]) &&
            is_int($index = array_search($message, $this->messages[$currentUrl][$type]))) {
            unset($this->messages[$currentUrl][$type][$index]);

        } else {
            throw new Exception(ucfirst($type) . ' message "' . $message . '" not present on ' . $currentUrl);
        }
    }
}
