<?php

require_once(__DIR__ . '/../bootstrap.php');

class Ding2TestBase extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstractedPage;
  protected $config;

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();
    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());

    $screenshot_path = $this->cnofig->getScreenshotPath();
    if ($screenshot_path) {
      $this->captureScreenshotOnFailure = TRUE;
      $this->screenshotPath = $screenshot_path;
      $screenshot_url = $this->getScreenshotPath();
      $this->screenshotUrl = $screenshot_url ? $screenshot_url : $this->getScreenshotPath();
    }
  }
}
