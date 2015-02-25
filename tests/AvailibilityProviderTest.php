<?php

/**
 * @file
 * Test availability provider functions.
 */

require_once "ProviderTestCase.php";
require_once 'FBS.php';
require_once dirname(__DIR__) . '/vendor/autoload.php';

/**
 * Test availability provider functions.
 */
class AvailabilityProviderTest extends ProviderTestCase {

  /**
   * Test availability items.
   *
   * Expected data:
   * [
   *   localid => [available: bool, reservable: bool (, is_internet: bool)]
   *   ...
   * ]
   */
  public function testItems() {
    $this->provider = 'availability';

    $json_responses = array(
      array(
        array(
          'recordId' => '123',
          'available' => TRUE,
          'reservable' => TRUE,
        ),
      ),

      array(
        array(
          'recordId' => '143',
          'available' => TRUE,
          'reservable' => FALSE,
        ),
        array(
          'recordId' => 'banana',
          'available' => FALSE,
          'reservable' => FALSE,
        ),
      ),
    );
    $httpclient = $this->getHttpClient($json_responses);

    // Run through tests.
    $fbs = FBS::get('', $httpclient);

    // Single item.
    $res = $this->providerInvoke('items', array('123'));
    $expected = array('123' => array('available' => TRUE, 'reservable' => TRUE));
    $this->assertEquals($expected, $res);

    // Multiple items, one with a string key.
    $res = $this->providerInvoke('items', array('143', 'banana'));
    $expected = array(
      '143' => array(
        'available' => TRUE,
        'reservable' => FALSE,
      ),
      'banana' => array(
        'available' => FALSE,
        'reservable' => FALSE,
      ),
    );
    $this->assertEquals($expected, $res);
  }
}
