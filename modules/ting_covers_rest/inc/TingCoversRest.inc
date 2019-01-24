<?php

use GuzzleHttp\Client;
use OpenAPI\Client\Configuration;
use OpenAPI\Client\Api\DefaultApi;

/**
 * @file
 * High level implementation of the Ting Covers REST API.
 */
class TingCoversRest {
  private $config;
  private $api;

  /**
   * Construct an API instance.
   */
  public function __construct() {
    // Handle autoload.
    $autoload = drupal_get_path('module', 'ting_covers_rest') . '/vendor/autoload.php';

    if (file_exists($autoload)) {
      require_once $autoload;
    }

    // Initialize settings from admin form in Drupal.
    $this->config = new Configuration();

    $this->config->setHost(variable_get(
      'ting_covers_rest_url',
      ''
    ));

    $this->config->setDebug(variable_get(
      'ting_covers_rest_enable_logging',
      FALSE
    ));

    $api_instance = new DefaultApi(
      new Client(),
      $this->getConfig()
    );

    $this->api = $api_instance;
  }

  /**
   * Returns the configuration object for OpenAPI.
   *
   * @return \OpenAPI\Client\Configuration
   */
  public function getConfig() {
    return $this->config;
  }

  /**
   * Returns the host string for the requested API.
   *
   * @return string
   *    The hostname for the API.
   */
  public function getHost() {
    return $this->config->getHost();
  }

  /**
   * Returns the OAuth token used by the API.
   *
   * @return string
   *    The OAuth token used by the API.
   */
  public function getToken() {
    return $this->config->getAccessToken();
  }

  /**
   * Get cover objects by ID type and IDs.
   *
   * @param string $type
   *    The ID type, for example 'pid' or 'issn'.
   *
   * @param array $ids
   *    IDs to lookup of the specified type.
   *
   * @return array|\OpenAPI\Client\Model\Cover[]
   */
  public function getCovers($type, $ids) {
    $covers = array();
    try {
      $covers = $this->api->coverTypeGet($type, $ids);
    }
    catch (Exception $e) {
      watchdog(
        'REST Coverservice',
        'Exception when fetching covers: @error',
        array('@error' => $e->getMessage()),
        WATCHDOG_ERROR
      );
    }
    return $covers;
  }

  /**
   * Return covers images from covers, by image format and size.
   *
   * @param \OpenAPI\Client\Model\Cover[] $covers
   *    Array of cover objects to get cover images from.
   *
   * @param $format
   *    The image format.
   *
   * @param array $size
   *    The image sizes to return.
   *
   * @todo
   *    Get default image sizes from generated swagger code.
   *
   * @return array|\OpenAPI\Client\Model\CoverImageUrls[]
   */
  public function getCoverImages($covers, $format, $size = array('default', 'original', 'thumbnail')) {
    $image_urls = array();

    /** @var \OpenAPI\Client\Model\Cover $cover */
    foreach ($covers as $cover) {
      foreach ($cover->getImageUrls() as $imageUrl) {
        $is_correct_size = in_array($imageUrl->getSize(), $size, TRUE);
        // Check for requested size and format.
        if ($is_correct_size && $imageUrl->getFormat() === $format) {
          $image_urls[$cover->getId()] = $imageUrl->getUrl();
        }
      }
    }

    return $image_urls;
  }
}
