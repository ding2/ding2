<?php

use GuzzleHttp\Client;
use OpenAPI\Client\Configuration;
use OpenAPI\Client\Api\DefaultApi;

/**
 * @file
 * High level implementation of the Ting Covers REST API.
 */
class TingCoversRestService {
  private $config;
  private $api;

  /**
   * Construct an API instance.
   *
   * @param $host
   *    The REST service hostname.
   *
   * @param bool $token
   *    The OAuth2 token.
   *
   * @param bool $debug
   *    Enable/disable debugging.
   */
  public function __construct($host, $token = FALSE, $debug = FALSE) {
    // Handle autoload.
    $autoload = drupal_get_path('module', 'ting_covers_rest') . '/vendor/autoload.php';

    if (file_exists($autoload)) {
      require_once $autoload;
    }

    $this->config = new Configuration();
    $this->config->setHost($host)->setDebug($debug);
    $token ?: $this->config->setAccessToken($token);

    $api_instance = new DefaultApi(
      new Client(),
      $this->config
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
   * @param \OpenAPI\Client\Model\Type $type
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
      watchdog_exception('ting_covers_rest', $e);
    }
    return $covers;
  }

  /**
   * Return covers images from covers, by image format and size.
   *
   * @param \OpenAPI\Client\Model\Cover[] $covers
   *    Array of cover objects to get cover images from.
   *
   * @param array $format
   *    The image formats to return.
   *
   * @param array $size
   *    The image sizes to return.
   *
   * @todo
   *    Get default image sizes from generated swagger code.
   *
   * @return array|\OpenAPI\Client\Model\CoverImageUrls[]
   */
  public function getCoverImages($covers, $format = array('jpeg', 'png'), $size = array('default', 'original', 'thumbnail')) {
    $image_urls = array();

    /** @var \OpenAPI\Client\Model\Cover $cover */
    foreach ($covers as $cover) {
      foreach ($cover->getImageUrls() as $imageUrl) {
        $is_correct_size = in_array($imageUrl->getSize(), $size, TRUE);
        $is_correct_format = in_array($imageUrl->getFormat(), $format, TRUE);
        // Check for requested size and format.
        if ($is_correct_size && $is_correct_format) {
          $image_urls[$cover->getId()] = $imageUrl->getUrl();
        }
      }
    }

    return $image_urls;
  }
}
