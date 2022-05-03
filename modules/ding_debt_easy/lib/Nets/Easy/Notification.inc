<?php

namespace Nets\Easy;

/**
 * Representation of Nets Easy notification.
 */
class Notification {

  private $name = '';
  private $url = '';
  private $authorization = '';

  /**
   * Get event name.
   *
   * @see https://developers.nets.eu/nets-easy/en-EU/api/webhooks/
   *
   * @return string
   *   The event name.
   */
  public function getName() {
    return $this->name;
  }

  /**
   * Set event name.
   *
   * @param string $name
   *   Name of the event.
   *
   * @see https://developers.nets.eu/nets-easy/en-EU/api/webhooks/
   *
   * @return $this
   */
  public function setName($name) {
    $this->name = $name;

    return $this;
  }

  /**
   * Get webhook callback url.
   *
   * @return string
   *   The URL to call when the event happens.
   */
  public function getUrl() {
    return $this->url;
  }

  /**
   * Set the URL to call when the event happens.
   *
   * @param string $url
   *   The URL to call.
   *
   * @return $this
   */
  public function setUrl($url) {
    $this->url = $url;

    return $this;
  }

  /**
   * Get authorization used to identify the callback.
   *
   * @return string
   *   The token.
   */
  public function getAuthorization() {
    return $this->authorization;
  }

  /**
   * Set authorization used to identify the callback.
   *
   * @param string $authorization
   *   The token to use.
   *
   * @return $this
   */
  public function setAuthorization($authorization) {
    $this->authorization = $authorization;

    return $this;
  }

  /**
   * Convert the notification to an array.
   *
   * @return string[]
   *   The notification as array.
   */
  public function toArray() {
    return [
      'eventName' => $this->getName(),
      'url' => $this->getUrl(),
      'authorization' => $this->getAuthorization(),
      // Header add here to make testing webhooks through localtunnel as
      // recommend by Nets-easy support to local development setup.
      'headers' => [
        [
          'Bypass-Tunnel-Reminder' => TRUE,
        ]
      ]
    ];
  }

}
