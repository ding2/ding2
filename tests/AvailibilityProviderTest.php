<?php

/**
 * @file
 * Test availability provider functions.
 */

require_once "ProviderTestCase.php";
require_once 'includes/classes/FBS.php';
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
    $fbs = fbs_service('1234', '', $httpclient, NULL, TRUE);

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

  /**
   * Test availability items.
   *
   * Expected data:
   * -
   *   reservable: # bool, optional
   *   available: # bool, optional
   *   holdings: # optional
   *     -
   *       placement: # array
   *       total_count: # int, optional
   *       available_count: # int, optional
   *       reference_count: # int, optional
   *   is_internet: # bool, optional
   *   total_count: # int
   *   reserved_count: # int
   */
  public function testHoldings() {
    $this->provider = 'availability';

    // @todo: multiple materials on same branch/department/etc.
    $json_responses = array(
      // First response.
      array(
        // Array of ...
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => 'one1234',
          'reservable' => TRUE,
          'holdings' => array(
            // Array of ...
            array(
              // Holdings.
              'materials' => array(
                // Array of ...
                array(
                  // Material.
                  'itemNumber' => '123456',
                  'available' => FALSE,
                ),
                array(
                  // Material.
                  'itemNumber' => '123457',
                  'available' => TRUE,
                ),
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 14,
                'title' => 'Reol 14',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 3,
                'title' => 'Hylde 3',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 2,
                'title' => 'Børn',
              ),
              'branch' => array(
                // AgencyBranch..
                'branchId' => 1,
                'title' => 'Hovedbiblioteket',
              ),
            ),
          ),
        ),
      ),

      // Second response.
      array(
        // Array of ...
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => 'two1234',
          'reservable' => TRUE,
          'holdings' => array(
            // Array of ...
            array(
              // Holdings.
              'materials' => array(
                // Array of ...
                array(
                  // Material.
                  'itemNumber' => '123456',
                  'available' => FALSE,
                ),
                array(
                  // Material.
                  'itemNumber' => '123457',
                  'available' => TRUE,
                ),
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 14,
                'title' => 'Reol 14',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 3,
                'title' => 'Hylde 3',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 2,
                'title' => 'Børn',
              ),
              'branch' => array(
                // AgencyBranch..
                'branchId' => 1,
                'title' => 'Hovedbiblioteket',
              ),
            ),
            array(
              // Holdings.
              'materials' => array(
                // Array of ...
                array(
                  // Material.
                  'itemNumber' => '223456',
                  'available' => FALSE,
                ),
                array(
                  // Material.
                  'itemNumber' => '223457',
                  'available' => TRUE,
                ),
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 14,
                'title' => 'Reol 14',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 4,
                'title' => 'Hylde 4',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 2,
                'title' => 'Børn',
              ),
              'branch' => array(
                // AgencyBranch..
                'branchId' => 1,
                'title' => 'Hovedbiblioteket',
              ),
            ),
          ),
        ),
      ),
    );
    $httpclient = $this->getHttpClient($json_responses);


    // Run through tests.
    $fbs = fbs_service('1234', '', $httpclient, NULL, TRUE);

    // Single item.
    $res = $this->providerInvoke('holdings', array('one1234'));
    $expected = array(
      'one1234' => array(
        'reservable' => TRUE,
        'available' => TRUE,
        'holdings' => array(
          array(
            'placement' => array(
              'Hovedbiblioteket',
              'Børn',
              'Reol 14',
              'Hylde 3',
            ),
            'available_count' => 1,
            'total_count' => 2,
            'reference_count' => 0,
          ),
        ),
        'is_internet' => FALSE,
        'total_count' => 2,
        'reserved_count' => 0,
      ),
    );
    $this->assertEquals($expected, $res);

    // More holdings.
    $res = $this->providerInvoke('holdings', array('one1234'));
    $expected = array(
      'two1234' => array(
        'reservable' => TRUE,
        'available' => TRUE,
        'holdings' => array(
          array(
            'placement' => array(
              'Hovedbiblioteket',
              'Børn',
              'Reol 14',
              'Hylde 3',
            ),
            'available_count' => 1,
            'total_count' => 2,
            'reference_count' => 0,
          ),
          array(
            'placement' => array(
              'Hovedbiblioteket',
              'Børn',
              'Reol 14',
              'Hylde 4',
            ),
            'available_count' => 1,
            'total_count' => 2,
            'reference_count' => 0,
          ),
        ),
        'is_internet' => FALSE,
        'total_count' => 4,
        'reserved_count' => 0,
      ),
    );
    $this->assertEquals($expected, $res);

  }
}
