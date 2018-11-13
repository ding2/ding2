<?php
/**
 * @file
 * Defines a generic storage communicator.
 */

namespace NationalStorageComponent;

/**
 * Defines required methods for CRUD operations.
 */
interface StorageCrudInterface {
  /**
   * Creates an entry in the content collection at the remote endpoint.
   *
   * @param array $params
   *   Entry properties.
   */
  public function addContent(array $params);

  /**
   * {@inheritdoc}
   */
  public function addMenu(array $params);
  
  /**
   * {@inheritdoc}
   */
  public function addList(array $params);

  /**
   * Updates an entry in the content collection at the remote endpoint.
   *
   * @param array $params
   *   Entry properties to be replaced with.
   */
  public function updateContent(array $params);

  /**
   * {@inheritdoc}
   */
  public function updateMenu(array $params);

  /**
   * {@inheritdoc}
   */
  public function updateList(array $params);

  /**
   * Removed a single entry from the collection at the remote endpoint.
   *
   * @param array $params
   *   Entry properties.
   */
  public function deleteContent(array $params);

  /**
   * {@inheritdoc}
   */
  public function deleteMenu(array $params);

  /**
   * {@inheritdoc}
   */
  public function deleteList(array $params);
}

/**
 * Defines required methods for remote endpoint communication.
 */
interface StorageCommunicatorInterface {

  /**
   * {@inheritdoc}
   */
  public function sendRequest($uri, $params, $method);
}

/**
 * Defines an abstract analogy of a storage communicator.
 */
abstract class GenericStorage implements \NationalStorageComponent\StorageCrudInterface, \NationalStorageComponent\StorageCommunicatorInterface {
  private $endpoint;
  private $response;
  private $requestBody;

  /**
   * Sets the service endpoint.
   *
   * @param string $endpoint
   *   Endpoint url.
   */
  public function setEndpoint($endpoint) {
    $this->endpoint = $endpoint;
  }

  /**
   * Gets the remote endpoint.
   *
   * @return string
   *   Endpoint url.
   */
  public function getEndpoint() {
    return $this->endpoint;
  }

  /**
   * Gets the response from a performed request.
   *
   * @return array
   *   Response information.
   */
  public function getResponse() {
    return $this->response;
  }

  /**
   * Sets the response from a performed request.
   *
   * @param array $response
   *   Response information.
   */
  protected function setResponse(array $response) {
    $this->response = $response;
  }

  /**
   * Gets the request body.
   *
   * @return string
   *   Request body string.
   */
  public function getRequest() {
    return $this->requestBody;
  }

  /**
   * Sets the request body string.
   *
   * @param string $request
   *   Request body string.
   */
  protected function setRequest($request) {
    $this->requestBody = $request;
  }

  /**
   * {@inheritdoc}
   *
   * @see \NationalStorageComponent\StorageCrudInterface::addContent($params)
   */
  public function addContent(array $params) {
    $uri = 'content';
    $json = json_encode($params);

    $this->setRequest($json);
    $this->sendRequest($uri, $json, 'PUT');
  }

  /**
   * {@inheritdoc}
   *
   * @see \NationalStorageComponent\StorageCrudInterface::updateContent()
   */
  public function updateContent(array $params) {
    $uri = 'content';
    $json = json_encode($params);

    $this->setRequest($json);
    $this->sendRequest($uri, $json, 'POST');
  }

  /**
   * {@inheritdoc}
   *
   * @see \NationalStorageComponent\StorageCrudInterface::deleteContent($params)
   */
  public function deleteContent(array $params) {
    $uri = 'content';
    $json = json_encode($params);

    $this->setRequest($json);
    $this->sendRequest($uri, $json, 'DELETE');
  }

  /**
   * {@inheritdoc}
   *
   * @see \NationalStorageComponent\StorageCrudInterface::addMenu($params)
   */
  public function addMenu(array $params) {
    $uri = 'menu';
    $json = json_encode($params);

    $this->setRequest($json);
    $this->sendRequest($uri, $json, 'PUT');
  }

  /**
   * {@inheritdoc}
   *
   * @see \NationalStorageComponent\StorageCrudInterface::updateMenu($params)
   */
  public function updateMenu(array $params) {
    $uri = 'menu';
    $json = json_encode($params);

    $this->setRequest($json);
    $this->sendRequest($uri, $json, 'POST');
  }

  /**
   * {@inheritdoc}
   *
   * @see \NationalStorageComponent\StorageCrudInterface::deleteMenu($params)
   */
  public function deleteMenu(array $params) {
    $uri = 'menu';
    $json = json_encode($params);

    $this->setRequest($json);
    $this->sendRequest($uri, $json, 'DELETE');
  }

  /**
   * {@inheritdoc}
   *
   * @see \NationalStorageComponent\StorageCrudInterface::addList($params)
   */
  public function addList(array $params) {
    $uri = 'list';
    $json = json_encode($params);

    $this->setRequest($json);
    $this->sendRequest($uri, $json, 'PUT');
  }

  /**
   * {@inheritdoc}
   *
   * @see \NationalStorageComponent\StorageCrudInterface::updateList($params)
   */
  public function updateList(array $params) {
    $uri = 'list';
    $json = json_encode($params);

    $this->setRequest($json);
    $this->sendRequest($uri, $json, 'POST');
  }

  /**
   * {@inheritdoc}
   *
   * @see \NationalStorageComponent\StorageCrudInterface::deleteList($params)
   */
  public function deleteList(array $params) {
    $uri = 'list';
    $json = json_encode($params);

    $this->setRequest($json);
    $this->sendRequest($uri, $json, 'DELETE');
  }

  /**
   * Performs communication with the remote endpoint.
   *
   * @param string $url
   *   Endpoint url.
   * @param string $body
   *   Data to be sent.
   * @param string $method
   *   Method to be called.
   */
  protected abstract function callEndpoint($url, $body, $method);

  /**
   * Processes the raw response executed at the remote endpoint.
   *
   * @param string $response
   *   Response string.
   */
  protected abstract function processResponse($response);
}
