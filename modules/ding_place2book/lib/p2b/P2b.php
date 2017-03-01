<?php
/**
 * @file
 * Represents a library for communication with Place2book service.
 */

namespace P2b;
use GuzzleHttp\Client as HttpClient;

/**
 * Main class for communication with place2book.
 *
 * Implements Singleton design pattern.
 *
 * @see http://developer.place2book.com/
 */
class P2b {

  /**
   * Represents instance of P2b class.
   *
   * @var object
   */
  private static $instance;

  /**
   * Represents http client.
   *
   * @var object
   */
  private $client;

  /**
   * Represents token for authorisation on remote service.
   *
   * @var string
   */
  private $token;

  /**
   * Url of remote service.
   *
   * @var string
   */
  private $url;

  /**
   * Url on remote service for getting list of event makers.
   *
   * @var string
   */
  private $eventMakers;

  /**
   * Url on remote service for getting specific event.
   *
   * @var string
   */
  private $getEvent;

  /**
   * Url on remote service for creating a event.
   *
   * @var string
   */
  private $createEvent;

  /**
   * Url on remote service for updating specific event.
   *
   * @var string
   */
  private $updateEvent;

  /**
   * Url on remote service for deleting specific event.
   *
   * @var string
   */
  private $deleteEvent;

  /**
   * Url on remote service for creating price.
   *
   * @var string
   */
  private $createPrice;

  /**
   * Url on remote service for getting price.
   *
   * @var string
   */
  private $getPrice;

  /**
   * Url on remote service for getting list of prices.
   *
   * @var string
   */
  private $getPrices;

  /**
   * Url on remote service for update price.
   *
   * @var string
   */
  private $updatePrice;

  /**
   * Url on remote service for delete price.
   *
   * @var string
   */
  private $deletePrice;

  /**
   * Divider for prices values.
   *
   * @var int
   */
  private $divider = 100;

  /**
   * P2b protected constructor for realisation singleton design pattern.
   *
   * @param array $settings
   *   Contains list of urls for initialising.
   *
   * @throws \Exception
   *   On assigning empty value.
   */
  protected function __construct(array $settings) {
    $this->client = new HttpClient();
    foreach ($settings as $name => $value) {
      if (property_exists($this, $name)) {
        if (empty($value)) {
          throw new \Exception("Error. Value {$value} can not be assigned to {$name}.");
        }
        $this->{$name} = $value;
      }
    }
  }

  /**
   * Private clone method for preventing cloning object.
   */
  private function __clone() {
  }

  /**
   * Static method for getting instance of P2b client.
   *
   * @param array $settings
   *   Represents array of url for initialising.
   *
   * @return object
   *   Instance of P2b class.
   */
  public static function getInstance(array $settings) {
    if (self::$instance === NULL) {
      self::$instance = new P2b($settings);
    }
    return self::$instance;
  }

  /**
   * Request to p2b for getting all eventMakers.
   *
   * @return array
   *   Return array where index is eventMaker id and value eventMaker data.
   *
   * @see http://developer.place2book.com/v1/event_makers
   */
  public function getEventMakers() {
    $event_makers = array();
    $result = $this->p2bRequest($this->eventMakers, 'GET');
    foreach ($result as $item) {
      $event_makers[$item->id] = $item;
    }

    return $event_makers;
  }

  /**
   * Request to p2b for getting event.
   *
   * @param string $event_maker_id
   *   String that represents eventMaker id on p2b service.
   * @param string $event_id
   *   String that represents event id on p2b service.
   *
   * @return object
   *   Return object with data related to event.
   *
   * @throws \Exception
   *   In case when not all required params was given.
   *
   * @see http://developer.place2book.com/v1/events/
   */
  public function getEvent($event_maker_id, $event_id) {
    if (empty($event_id) || empty($event_maker_id)) {
      throw new \Exception("Params event_id, event_maker_id are required. Was given event_maker_id: {$event_maker_id}, event_id: {$event_id}.");
    }

    $placeholders = array(
      ':event_id' => $event_id,
      ':event_maker_id' => $event_maker_id,
    );

    $url = $this->p2bFormatUrl($this->getEvent, $placeholders);
    $result = $this->p2bRequest($url, 'GET');

    return $result->event;
  }

  /**
   * Request to p2b for creating event.
   *
   * @param string $event_maker_id
   *   String that represents eventMaker id on p2b service.
   * @param array $data
   *   Array with all needed data for creating event.
   *
   * @return array
   *   Return object with data related to event.
   *
   * @throws \Exception
   *   In case when not all required params was given.
   *
   * @see http://developer.place2book.com/v1/events/
   */
  public function createEvent($event_maker_id, array $data) {
    if (empty($event_maker_id) && !empty($data['event'])) {
      throw new \Exception("Params event_maker_id is required. Was given event_id: {$event_maker_id} and empty $data param.");
    }

    $required = array(
      'name' => FALSE,
      'begin_at' => FALSE,
      'capacity' => FALSE,
      'address' => array(
        'address1' => FALSE,
        'postal_code' => FALSE,
        'city' => FALSE,
        'phone' => FALSE,
        'country' => FALSE,
        'name' => FALSE,
      ),
    );
    $this->p2bCheckRequired($required, $data['event']);
    $this->p2bGenerateException($required, __FUNCTION__);

    $placeholders = array(
      ':event_maker_id' => $event_maker_id,
    );
    $url = $this->p2bFormatUrl($this->createEvent, $placeholders);

    $event = $this->p2bRequest($url, 'POST', $data, 201);

    return $event->event;
  }

  /**
   * Request to p2b for updating event.
   *
   * @param string $event_maker_id
   *   String that represents eventMaker id on p2b service.
   * @param string $event_id
   *   String that represents event id on p2b service.
   * @param array $data
   *   Array with all needed data for updating event.
   *
   * @return array
   *   Return object with data related to event.
   *
   * @throws \Exception
   *   In case when not all required params was given.
   *
   * @see http://developer.place2book.com/v1/events/
   */
  public function updateEvent($event_maker_id, $event_id, array $data) {
    if (empty($event_id) || empty($event_maker_id)) {
      throw new \Exception("Params event_id, event_maker_id are required. Was given event_maker_id: {$event_maker_id}, event_id: {$event_id}.");
    }

    $required = array(
      'name' => FALSE,
      'begin_at' => FALSE,
      'capacity' => FALSE,
      'address' => array(
        'address1' => FALSE,
        'postal_code' => FALSE,
        'city' => FALSE,
        'phone' => FALSE,
        'country' => FALSE,
        'name' => FALSE,
      ),
    );
    $this->p2bCheckRequired($required, $data['event']);
    $this->p2bGenerateException($required, __FUNCTION__);

    $placeholders = array(
      ':event_id' => $event_id,
      ':event_maker_id' => $event_maker_id,
    );
    $url = $this->p2bFormatUrl($this->updateEvent, $placeholders);
    $event = $this->p2bRequest($url, 'PUT', $data);

    return $event->event;
  }

  /**
   * Request to p2b for deleting event.
   *
   * @param string $event_maker_id
   *   String that represents eventMaker id on p2b service.
   * @param string $event_id
   *   String that represents event id on p2b service.
   *
   * @return array
   *   Return object with data related to event.
   *
   * @throws \Exception
   *   In case when not all required params was given.
   *
   * @see http://developer.place2book.com/v1/events/
   */
  public function deleteEvent($event_maker_id, $event_id) {
    if (empty($event_id) || empty($event_maker_id)) {
      throw new \Exception("Params event_id, event_maker_id are required. Was given event_maker_id: {$event_maker_id}, event_id: {$event_id}.");
    }

    $placeholders = array(
      ':event_id' => $event_id,
      ':event_maker_id' => $event_maker_id,
    );
    $url = $this->p2bFormatUrl($this->deleteEvent, $placeholders);
    $event = $this->p2bRequest($url, 'DELETE', array(), 204);

    return $event;
  }

  /**
   * Request to p2b for creating price.
   *
   * @param string $event_maker_id
   *   String that represents eventMaker id on p2b service.
   * @param string $event_id
   *   String that represents event id on p2b service.
   * @param array $data
   *   Array with all needed data for creating event.
   *
   * @return array
   *   Return object with data related to event.
   *
   * @throws \Exception
   *   In case when not all required params was given.
   *
   * @see http://developer.place2book.com/v1/prices/
   */
  public function createPrice($event_maker_id, $event_id, array $data) {
    if (empty($event_id) || empty($event_maker_id)) {
      throw new \Exception("Params event_id, event_maker_id are required. Was given event_maker_id: {$event_maker_id}, event_id: {$event_id}.");
    }

    $required = array(
      'name' => FALSE,
      'value' => FALSE,
    );
    $this->p2bCheckRequired($required, $data['price']);
    $this->p2bGenerateException($required, __FUNCTION__);

    $placeholders = array(
      ':event_maker_id' => $event_maker_id,
      ':event_id' => $event_id,
    );
    $url = $this->p2bFormatUrl($this->createPrice, $placeholders);
    $data['price']['value'] *= $this->divider;
    $price = $this->p2bRequest($url, 'POST', $data, 201);

    return $price;
  }


  /**
   * Request to p2b for getting price of event.
   *
   * @param string $event_maker_id
   *   String that represents eventMaker id on p2b service.
   * @param string $event_id
   *   String that represents event id on p2b service.
   * @param string $price_id
   *   String that represents price id id on p2b service.
   *
   * @return object
   *   Return object with data related to event price.
   *
   * @throws \Exception
   *   In case when not all required params was given.
   *
   * @see http://developer.place2book.com/v1/prices/
   */
  public function getPrice($event_maker_id, $event_id, $price_id) {
    if (empty($event_id) || empty($event_maker_id) || empty($price_id)) {
      throw new \Exception("Params event_id, event_maker_id and price_id are required. Was given event_maker_id: {$event_maker_id}, event_id: {$event_id}, price_id: {$price_id}.");
    }
    $placeholders = array(
      ':event_id' => $event_id,
      ':event_maker_id' => $event_maker_id,
      ':price_id' => $price_id,
    );
    $url = $this->p2bFormatUrl($this->getPrice, $placeholders);
    $result = $this->p2bRequest($url, 'GET');
    foreach ($result as $price) {
      $price->value /= $this->divider;
    }

    return $result;
  }

  /**
   * Request to p2b for getting prices of event.
   *
   * @param string $event_maker_id
   *   String that represents eventMaker id on p2b service.
   * @param string $event_id
   *   String that represents event id on p2b service.
   *
   * @return object
   *   Return object with list of prices.
   *
   * @throws \Exception
   *   In case when not all required params was given.
   *
   * @see http://developer.place2book.com/v1/prices/
   */
  public function getPrices($event_maker_id, $event_id) {
    if (empty($event_id) || empty($event_maker_id)) {
      throw new \Exception("Params event_id, event_maker_id are required. Was given event_maker_id: {$event_maker_id}, event_id: {$event_id}.");
    }
    $placeholders = array(
      ':event_id' => $event_id,
      ':event_maker_id' => $event_maker_id,
    );
    $url = $this->p2bFormatUrl($this->getPrices, $placeholders);
    $result = $this->p2bRequest($url, 'GET');
    foreach ($result as $price) {
      $price->value /= $this->divider;
    }
    return $result;
  }
  /**
   * Request to p2b for update price.
   *
   * @param string $event_maker_id
   *   String that represents eventMaker id on p2b service.
   * @param string $event_id
   *   String that represents event id on p2b service.
   * @param string $price_id
   *   String that represents price id id on p2b service.
   * @param array $data
   *   Array with all needed data for creating event.
   *
   * @return array
   *   Return object with data related to event.
   *
   * @throws \Exception
   *   In case when not all required params was given.
   *
   * @see http://developer.place2book.com/v1/prices/
   */
  public function updatePrice($event_maker_id, $event_id, $price_id, array $data) {
    if (empty($event_id) || empty($event_maker_id) || empty($price_id)) {
      throw new \Exception("Params event_id, event_maker_id and price_id are required. Was given event_maker_id: {$event_maker_id}, event_id: {$event_id}, price_id: {$price_id}.");
    }

    $required = array(
      'name' => FALSE,
      'value' => FALSE,
    );
    $this->p2bCheckRequired($required, $data['price']);
    $this->p2bGenerateException($required, __FUNCTION__);

    $placeholders = array(
      ':event_maker_id' => $event_maker_id,
      ':event_id' => $event_id,
      ':price_id' => $price_id,
    );
    $url = $this->p2bFormatUrl($this->updatePrice, $placeholders);
    $data['price']['value'] *= $this->divider;
    $result = $this->p2bRequest($url, 'PUT', $data);

    return $result;
  }

  /**
   * Request to p2b for delete price.
   *
   * @param string $event_maker_id
   *   String that represents eventMaker id on p2b service.
   * @param string $event_id
   *   String that represents event id on p2b service.
   * @param string $price_id
   *   String that represents price id id on p2b service.
   *
   * @return array
   *   Return object with data related to event.
   *
   * @throws \Exception
   *   In case when not all required params was given.
   *
   * @see http://developer.place2book.com/v1/prices/
   */
  public function deletePrice($event_maker_id, $event_id, $price_id) {
    if (empty($event_id) || empty($event_maker_id) || empty($price_id)) {
      throw new \Exception("Params event_id, event_maker_id and required are required. Was given event_maker_id: {$event_maker_id}, event_id: {$event_id}, price_id: {$price_id}.");
    }

    $placeholders = array(
      ':event_maker_id' => $event_maker_id,
      ':event_id' => $event_id,
      ':price_id' => $price_id,
    );
    $url = $this->p2bFormatUrl($this->deletePrice, $placeholders);
    $result = $this->p2bRequest($url, 'DELETE', array(), 204);

    return $result;
  }

  /**
   * Main method. Make a http request.
   *
   * @param string $url
   *   String that represents url to p2b service.
   * @param string $type
   *   String that represents type of HTTP request - GET/POST.
   * @param array $params
   *   Array with addition params for HTTP request.
   * @param int $code
   *   Correct code of response.
   *
   * @return object
   *   If we have result or throws exception.
   *
   * @throws \Exception
   *   In case when response code not equal to excepted.
   */
  private function p2bRequest($url, $type, array $params = array(), $code = 200) {

    if (empty( $this->token)) {
      throw new \Exception("Token empty.");
    }
    $options = array();
    $options['headers'] = array(
      "X-PLACE2BOOK-API-TOKEN" => $this->token,
      "Accept" => "application/vnd.place2book.v1+json",
    );

    if (!empty($params)) {
      if ($type == 'POST') {
        $options['json'] = $params;
      }
      else {
        $options['query'] = $params;
      }
    }

    $options['http_errors'] = FALSE;
    $response = $this->client->request($type, $url, $options);
    if ($response->getStatusCode() == $code) {
      $data = $type == 'DELETE' ? new \stdClass() : $this->parseResponse($response->getBody());
    }
    else {
      $res_code = $response->getStatusCode();
      throw new \Exception("Wrong code. Expected - {$code}, was returned - {$res_code}.");
    }

    return $data;
  }

  /**
   * Parse json response from service.
   *
   * @param string $response
   *   Json response from service.
   *
   * @return object
   *   Parsed reponse as object.
   *
   * @throws \Exception
   *   In case when response code not equal to excepted.
   */
  private function parseResponse($response) {
    $data = json_decode($response);
    if (empty($data)) {
      throw new \Exception('Empty response body.');
    }

    return $data;
  }

  /**
   * Checks if given data has all required values.
   *
   * @param array $required
   *   Array with required params.
   * @param array $given
   *   Given params for some method.
   */
  private function p2bCheckRequired(array &$required, array $given) {
    foreach ($required as $key => &$value) {
      if (is_array($value)) {
        $this->p2bCheckRequired($required[$key], $given[$key]);
      }
      else {
        $value = empty($given[$key]) && $given[$key] !== '0';
      }
    }
  }

  /**
   * Replace placholders with actual values in string.
   *
   * @param string $url
   *   String with placeholders.
   * @param array $placeholders
   *   Array with actual values.
   *
   * @return string
   *   Formated string with actual values.
   */
  private function p2bFormatUrl($url, array $placeholders) {
    foreach ($placeholders as $placeholder => $value) {
      $url = str_replace($placeholder, $value, $url);
    }
    return $url;
  }

  /**
   * Generates exception message and throws it.
   *
   * @param array $required
   *   Array with verified input data.
   * @param string $method
   *   Name of method which requires these params.
   *
   * @throws \Exception
   *   Information about required params.
   */
  private function p2bGenerateException(array $required, $method) {
    $required = $this->p2bArrayFilterRecursive($required);
    $missed = array();
    foreach ($required as $key => $v) {
      if (is_array($v)) {
        $missed += array_keys($v);
      }
      else {
        $missed[] = $key;
      }
    }

    if (!empty($missed)) {
      $missed = implode(', ', $missed);
      throw new \Exception("Error. {$method} requires: [{$missed}]");
    }
  }

  /**
   * Recursive version of array_filter.
   *
   * @param array $input
   *   Input array which should be filtered.
   *
   * @return array
   *   Result of filtering.
   */
  private function p2bArrayFilterRecursive(array $input) {
    foreach ($input as &$value) {
      if (is_array($value)) {
        $value = $this->p2bArrayFilterRecursive($value);
      }
    }

    return array_filter($input);
  }

}
