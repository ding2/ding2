<?php
/**
 * @file
 * Defines a CURL communicator with the remote National Database.
 */

namespace NationalStorageComponent;

/**
 * {@inheritdoc}
 */
class NationalStorageException extends \Exception {}

/**
 * {@inheritdoc}
 */
class NationalStorage extends \NationalStorageComponent\GenericStorage {
  /**
   * Creates a new object of the storage communicator.
   *
   * @param string $endpoint
   *   Endpoint url.
   */
  public function __construct($endpoint) {
    $this->setEndpoint($endpoint);
  }

  /**
   * {@inheritdoc}
   *
   * @see \NationalStorageComponent\StorageCommunicatorInterface::sendRequest()
   */
  public function sendRequest($uri, $params, $method) {
    $url = $this->getEndpoint() . $uri;
    $this->callEndpoint($url, $params, $method);
  }

  /**
   * {@inheritdoc}
   *
   * @see \NationalStorageComponent\GenericStorage::callEndpoint()
   */
  protected function callEndpoint($url, $body, $method) {
    // Uses cURL as a primary communicator.
    $headers = array(
      'Content-Type: application/json',
      'Content-Length: ' . mb_strlen($body),
    );

    $ch = curl_init();
    curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, $method);
    curl_setopt($ch, CURLOPT_POSTFIELDS, $body);
    curl_setopt($ch, CURLOPT_URL, $url);
    $result = curl_exec($ch);

    if (!$result) {
      $curl_error = curl_error($ch);
      $curl_errno = curl_errno($ch);
      $message = 'Communication failed with error: ' . $curl_error . '.';
      $message .= ' Error number: ' . $curl_errno . '.';
      throw new \NationalStorageComponent\NationalStorageException($message);
    }

    curl_close($ch);

    $this->setResponse($this->processResponse($result));
  }

  /**
   * {@inheritdoc}
   *
   * @see \NationalStorageComponent\GenericStorage::processResponse()
   */
  protected function processResponse($response) {
    $decoded_response = json_decode($response);

    return array(
      'status' => isset($decoded_response->status) ? $decoded_response->status : FALSE,
      'response' => isset($decoded_response->message) ? $decoded_response->message : (string) $response,
    );
  }
}
