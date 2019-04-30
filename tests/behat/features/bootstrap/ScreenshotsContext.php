<?php

/**
 * @file
 * Screenshotting steps and helpers.
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

// phpcs:disable PSR1.Classes.ClassDeclaration.MissingNamespace
class ScreenshotsContext implements Context, SnippetAcceptingContext
{
    /**
     * Holds the name of the current feature being run
     *
     * @var string
     */
    private $currentFeature;

    /**
     * Holds the name of the current scenario being run
     *
     * @var string
     */
    private $currentScenario;

    /**
     * Holds the MinkContext to drive the browser
     *
     * @var \Drupal\DrupalExtension\Context\MinkContext
     */
    protected $minkContext;

    /**
     * Hold the flag for whether screendumps are created or not.
     *
     * @var bool
     */
    protected $enabled;

    /**
     * Folder to save screenshots in.
     *
     * @var string
     */
    protected $directory = '';

    /**
     * Whether to create sub-folders for features.
     *
     * @var bool
     */
    protected $createFeatureFolders = '';

    /**
     * LibContext constructor.
     *
     * @param bool $NoScreenDump
     *    Retrieved from behat.yml to indicate if screendumps are to be made or not.
     */
    public function __construct(
        $NoScreenDump
    ) {
        $this->enabled = !$NoScreenDump;

        $scrShotDir = getenv('SCREENSHOT_DIR');
        if ($scrShotDir) {
            $this->directory = $scrShotDir;
        }

        $scrShotFeatureFolder = getenv('SCREENSHOT_FEATURE_FOLDER');
        if ($scrShotFeatureFolder) {
            $this->createFeatureFolders = (bool) preg_match('/^(t(rue)?|y(es)?)$/i', $scrShotFeatureFolder);
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
    public function beforeScenario(BeforeScenarioScope $scope)
    {
        // Gather contexts.
        $environment = $scope->getEnvironment();
        $this->currentFeature = $scope->getFeature()->getTitle();
        $this->currentScenario = $scope->getScenario()->getTitle();

        $this->minkContext = $environment->getContext('Drupal\DrupalExtension\Context\MinkContext');
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
    public function afterScenario(\Behat\Behat\Hook\Scope\AfterScenarioScope $scope)
    {
        if ($scope->getTestResult()->getResultCode() > 0) {
            // Allow animations to settle.
            sleep(3);
            $this->saveScreenshot();
        }
    }

    /**
     * Step to save a screenshot on demand
     *
     * @Then I save (a) screenshot
     */
    public function saveScreenshot()
    {
        // Initially check if we are taking screenshots at all. The setting is in the behat.yml file.
        if (!$this->enabled) {
            print_r("Due to screendump setting in behat.yml, screendumps are currently not being saved.\n");
            return;
        }

        // Setup folders and make sure the folders exists.
        $featureFolder = "";
        if ($this->createFeatureFolders) {
            $featureFolder = preg_replace('/\W/', '', ucwords(strtolower($this->currentFeature)));
            if (!file_exists($this->directory . $featureFolder)) {
                mkdir($this->directory . $featureFolder);
            }
            // Add the slash to make the following code work in all circumstances.
            $featureFolder = $featureFolder . "/";
        }

        // Setup filename and make sure it is unique, by adding a postfix (simple number).
        $fileName = $this->directory . $featureFolder
            . preg_replace('/\W/', '', ucwords(strtolower($this->currentScenario)));
        $fileNamePostfix = "";
        while (file_exists($fileName . $fileNamePostfix . '.png')) {
            $fileNamePostfix++;
        }
        $fileName = $fileName . $fileNamePostfix . '.png';

        // Log the filename of the screenshot to notify the user.
        print("Screenshot in: " . $fileName . "\n");

        // Now find the actual height of the shown page.
        $height = $this->minkContext->getSession()->evaluateScript("return document.body.scrollHeight;");
        // Save the screenshot.
        $this->minkContext->getSession()
            ->getDriver()
            ->resizeWindow(1280, $height, 'current');
        file_put_contents($fileName, $this->minkContext->getSession()->getDriver()->getScreenshot());
    }
}
