<?php

/**
 * @file
 * High level implementation of the Ting Covers REST API.
 */

use GuzzleHttp\Client;
use OpenAPI\Client\Configuration;
use OpenAPI\Client\Api\DefaultApi;
use OpenAPI\Client\Model\Type;

/**
 * Wrapper for the OpenAPI client.
 */
class TingCoversRestService {
  private $config;
  private $api;

  /**
   * Construct an API instance.
   *
   * @param string|null $token
   *   The OAuth2 token.
   * @param string|null $host
   *   The REST service hostname.
   * @param bool $debug
   *   Enable/disable debugging.
   */
  public function __construct($token = NULL, $host = NULL, $debug = FALSE) {
    $this->config = new Configuration();
    $this->config->setDebug($debug);

    if ($token) {
      $this->config->setAccessToken($token);
    }

    if ($host) {
      $this->config->setHost($host);
    }

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
   *   The configuration object with settings for the OpenAPI client.
   */
  public function getConfig() {
    return $this->config;
  }

  /**
   * Returns the host string for the requested API.
   *
   * @return string
   *   The hostname for the API.
   */
  public function getHost() {
    return $this->config->getHost();
  }

  /**
   * Returns the OAuth token used by the API.
   *
   * @return string
   *   The OAuth token used by the API.
   */
  public function getToken() {
    return $this->config->getAccessToken();
  }

  /**
   * Get cover objects by ID type and IDs.
   *
   * @param \OpenAPI\Client\Model\Type $type
   *   The ID type, for example 'pid' or 'issn'.
   * @param array $ids
   *   IDs to lookup of the specified type.
   * @param array $format
   *   The image format(s) of the fetched covers.
   * @param array $size
   *   The size(s) of the fetched images.
   *
   * @return \OpenAPI\Client\Model\Cover[]
   *   Array of Cover objects containing the cover image URLs.
   */
  public function getCovers(Type $type, array $ids, array $format, array $size) {
    $covers = array();
    try {
      $covers = $this->api->coverTypeGet(
        $type, $ids, $format, $generic = TRUE, $size, $limit = NULL, $offset = 0
      );
    }
    catch (\Exception $e) {
      watchdog_exception('ting_covers_rest', $e);
    }
    return $covers;
  }

  /**
   * Return covers images from covers, by image format and size.
   *
   * @param \OpenAPI\Client\Model\Cover[] $covers
   *   Array of cover objects to get cover images from.
   *
   * @return array
   *   Associative array; ting object ID as key and the cover URL as value.
   */
  public function getCoverImages(array $covers) {
    $image_urls = array();

    /** @var \OpenAPI\Client\Model\Cover $cover */
    foreach ($covers as $cover) {
      foreach ($cover->getImageUrls() as $imageUrl) {
        $image_urls[$cover->getId()] = $imageUrl->getUrl();
      }
    }

    return $image_urls;
  }

}
