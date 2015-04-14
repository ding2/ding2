<?php

/**
 * @file
 * Test availability provider functions.
 */

require_once "ProviderTestCase.php";
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
      // TCA1: Return empty result for empty request
      array(),

      // TCA2: Return empty result for non-existing material
      array(
        array(
          'recordId' => 'iDontExist',
          'available' => FALSE,
          'reservable' => FALSE,
        ),
      ),

      // TCA3: Return availability for material MAT1
      array(
        array(
          'recordId' => '870970-basis:29911363', // ikke i systemet
          'available' => FALSE,
          'reservable' => FALSE,
        ),
      ),
      // TCA4: Return availability for material MAT2
      array(
        array(
          'recordId' => '870970-basis:22629344',
          'available' => FALSE,
          'reservable' => TRUE,
        ),
      ),
      // TCA5: Return availability for material MAT3
      array(
        array(
          'recordId' => '870970-basis:51299116',
          'available' => TRUE,
          'reservable' => FALSE,
        ),
      ),
      // TCA6: Return availability for material MAT4
      array(
        array(
          'recordId' => '870970-basis:44399989',
          'available' => TRUE,
          'reservable' => TRUE,
        ),
      ),
      // TCA7: Return availability for material MAT1, MAT2, MAT3, MAT4
      array(
        array(
          'recordId' => '870970-basis:29911363',
          'available' => FALSE,
          'reservable' => FALSE,
        ),
        array(
          'recordId' => '870970-basis:22629344',
          'available' => FALSE,
          'reservable' => TRUE,
        ),
        array(
          'recordId' => '870970-basis:51299116',
          'available' => TRUE,
          'reservable' => FALSE,
        ),
        array(
          'recordId' => '870970-basis:44399989',
          'available' => TRUE,
          'reservable' => TRUE,
        ),
      ),
      // TCA8: Return availability for material MAT1, MAT2, MAT3, MAT4 (and % for non-existing material)
      array(
        array(
          'recordId' => '870970-basis:29911363',
          'available' => FALSE,
          'reservable' => FALSE,
        ),
        array(
          'recordId' => '870970-basis:22629344',
          'available' => FALSE,
          'reservable' => TRUE,
        ),
        array(
          'recordId' => '870970-basis:51299116',
          'available' => TRUE,
          'reservable' => FALSE,
        ),
        array(
          'recordId' => '870970-basis:44399989',
          'available' => TRUE,
          'reservable' => TRUE,
        ),
        array(
          'recordId' => '',
          'available' => FALSE,
          'reservable' => FALSE,
        ),
        array(
          'recordId' => 'iDontExist',
          'available' => FALSE,
          'reservable' => FALSE,
        ),
      ),
    );
    $this->replies($json_responses);

    // TCA1: Empty request.
    $res = $this->providerInvoke('items', array());
    $expected = array();
    $this->assertEquals($expected, $res);

    // TCA2: Request availability for non-existing item
    $res = $this->providerInvoke('items', array('iDontExist'));
    $expected = array('iDontExist' => array('available' => FALSE, 'reservable' => FALSE));
    $this->assertEquals($expected, $res);

    // TCA3: Request availability for existing item, non-available, non-reservable
    $res = $this->providerInvoke('items', array('870970-basis:29911363'));
    $expected = array('870970-basis:29911363' => array('available' => FALSE, 'reservable' => FALSE));
    $this->assertEquals($expected, $res);

    // TCA4: Request availability for existing item, non-available, reservable
    $res = $this->providerInvoke('items', array('870970-basis:22629344'));
    $expected = array('870970-basis:22629344' => array('available' => FALSE, 'reservable' => TRUE));
    $this->assertEquals($expected, $res);

    // TCA5: Request availability for existing item, available, non-reservable
    $res = $this->providerInvoke('items', array('870970-basis:51299116'));
    $expected = array('870970-basis:51299116' => array('available' => TRUE, 'reservable' => FALSE));
    $this->assertEquals($expected, $res);

    // TCA6: Request availability for existing item, available, reservable
    $res = $this->providerInvoke('items', array('870970-basis:44399989'));
    $expected = array('870970-basis:44399989' => array('available' => TRUE, 'reservable' => TRUE));
    $this->assertEquals($expected, $res);

    // TCA7: Request availability for multiple (valid) items
    $res = $this->providerInvoke('items', array('870970-basis:29911363','870970-basis:22629344','870970-basis:51299116','870970-basis:44399989'));
    $expected = array(
      '870970-basis:29911363' => array(
        'available' => FALSE,
        'reservable' => FALSE,
      ),
      '870970-basis:22629344' => array(
        'available' => FALSE,
        'reservable' => TRUE,
      ),
      '870970-basis:51299116' => array(
        'available' => TRUE,
        'reservable' => FALSE,
      ),
      '870970-basis:44399989' => array(
        'available' => TRUE,
        'reservable' => TRUE,
      ),
    );
    $this->assertEquals($expected, $res);


    // TCA8: Request availability for multiple (including invalid) items
    $res = $this->providerInvoke('items', array('870970-basis:29911363','870970-basis:22629344','870970-basis:51299116','870970-basis:44399989',NULL,'iDontExist'));
    $expected = array(
      '870970-basis:29911363' => array(
        'available' => FALSE,
        'reservable' => FALSE,
      ),
      '870970-basis:22629344' => array(
        'available' => FALSE,
        'reservable' => TRUE,
      ),
      '870970-basis:51299116' => array(
        'available' => TRUE,
        'reservable' => FALSE,
      ),
      '870970-basis:44399989' => array(
        'available' => TRUE,
        'reservable' => TRUE,
      ),
      '' => array(
        'available' => FALSE,
        'reservable' => FALSE,
      ),
      'iDontExist' => array(
        'available' => FALSE,
        'reservable' => FALSE,
      )
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

    $json_responses = array(
      // TCH1: Empty result for empty request
       array(),

      // TCH2: Empty result for unknown material
       array(
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => 'iDontExist',
          'reservable' => FALSE,
          'holdings' => array(),
        ),
      ),

      // TCH3: Return holdings for material MAT1: reservable/available=false
      array(
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => '870970-basis:29911363',
          'reservable' => FALSE,
          'holdings' => array(),
        ),
      ),

      // TCH4: Return holdings for material MAT2: reservable=true/available=false
      array(
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => '870970-basis:22629344',
          'reservable' => TRUE,
          'holdings' => array(
            array(
              // Holding 1
              'materials' => array(
                array(
                  // Material 1
                  'itemNumber' => '4025559679',
                  'available' => FALSE,
                  'materialGroupName' => 'very permissive',
                ),
                array(
                  // Material 2
                  'itemNumber' => '4025560677',
                  'available' => FALSE,
                  'materialGroupName' => 'very permissive',
                ),
              ),
              'branch' => array(
                // AgencyBranch.
                'branchId' => 'DK-761500',
                'title' => 'Horsens Bibliotek',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 'SKN',
                'title' => 'Skønlitteratur',
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 'MUS',
                'title' => 'Musik',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 'JAZZ',
                'title' => 'Jazz',
              ),
            ),
          ),
        ),
      ),

      // TCH5: Return holdings for material MAT3: reservable=false/available=true
       array(
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => '870970-basis:51299116',
          'reservable' => FALSE,
          'holdings' => array(
            array(
              // Holding 1
              'materials' => array(
                array(
                  // ITEM
                  'itemNumber' => '5829213644',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                ),
              ),
              'branch' => array(
                // AgencyBranch.
                'branchId' => 'DK-761500',
                'title' => 'Horsens Bibliotek',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 'LOK',
                'title' => 'Lokal',
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 'MAG',
                'title' => 'Magasin',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 'LKR',
                'title' => 'Læsekreds',
              ),
            ),
            array(
              // Holding 2
              'materials' => array(
                array(
                  // ITEM 0
                  'itemNumber' => '5829213636',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                ),
                array(
                  // ITEM 1
                  'itemNumber' => '5829213637',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                ),
                array(
                  // ITEM 2
                  'itemNumber' => '5829213638',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                ),
                array(
                  // ITEM 3
                  'itemNumber' => '5829213639',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                ),
                array(
                  // ITEM 4
                  'itemNumber' => '5829213640',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                ),
                array(
                  // ITEM 5
                  'itemNumber' => '5829213641',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                ),
                array(
                  // ITEM 6
                  'itemNumber' => '5829213642',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                ),
                array(
                  // ITEM 7
                  'itemNumber' => '5829213643',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                ),
                array(
                  // ITEM 8
                  'itemNumber' => '5829213645',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                ),
              ),
              'branch' => array(
                // AgencyBranch.
                'branchId' => 'DK-761500',
                'title' => 'Horsens Bibliotek',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 'SKN',
                'title' => 'Skønlitteratur',
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 'UNG',
                'title' => 'Ungdom',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 'LKR',
                'title' => 'Læsekreds',
              ),
            ),
          ),
        ),
      ),

      // TCH6: Return holdings for material MAT4: reservable/available=true
      array(
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => '870970-basis:44399989',
          'reservable' => TRUE,
          'holdings' => array(
            array(
              // Holdings.
              'materials' => array(
                array(
                  // ITEM 1
                  'itemNumber' => '4025570672',
                  'materialGroupName' => 'medium permissive',
                  'available' => TRUE,
                ),
              ),
              'branch' => array(
                // AgencyBranch.
                'branchId' => 'DK-761500',
                'title' => 'Horsens Bibliotek',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 'FOY',
                'title' => 'Foyeren',
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 'UNG',
                'title' => 'Ungdom',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 'HNG',
                'title' => 'Håndbøger',
              ),
            ),
          ),
        ),
      ),

      // TCH8: Return holdings for MAT1 & MAT2
      array(
        // MAT1
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => '870970-basis:29911363',
          'reservable' => FALSE,
          'holdings' => array(),
        ),
        // MAT2
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => '870970-basis:22629344',
          'reservable' => TRUE,
          'holdings' => array(
            array(
              // Holding 1
              'materials' => array(
                array(
                  // Material 1
                  'itemNumber' => '4025559679',
                  'available' => FALSE,
                  'materialGroupName' => 'very permissive',
                ),
                array(
                  // Material 2
                  'itemNumber' => '4025560677',
                  'available' => FALSE,
                  'materialGroupName' => 'very permissive',
                ),
              ),
              'branch' => array(
                // AgencyBranch.
                'branchId' => 'DK-761500',
                'title' => 'Horsens Bibliotek',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 'SKN',
                'title' => 'Skønlitteratur',
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 'MUS',
                'title' => 'Musik',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 'JAZZ',
                'title' => 'Jazz',
              ),
            ),
          ),
        ),
      ),

      // TCH9: Return holdings for MAT4 & iDontExist
      array(
        // MAT4
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => '870970-basis:44399989',
          'reservable' => TRUE,
          'holdings' => array(
            array(
              // Holdings.
              'materials' => array(
                array(
                  // ITEM 1
                  'itemNumber' => '4025570672',
                  'materialGroupName' => 'medium permissive',
                  'available' => TRUE,
                ),
              ),
              'branch' => array(
                // AgencyBranch.
                'branchId' => 'DK-761500',
                'title' => 'Horsens Bibliotek',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 'FOY',
                'title' => 'Foyeren',
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 'UNG',
                'title' => 'Ungdom',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 'HNG',
                'title' => 'Håndbøger',
              ),
            ),
          ),
        ),
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => 'iDontExist',
          'reservable' => FALSE,
          'holdings' => array(),
        ),
      ),
    );
    $this->replies($json_responses);

    // TCH1: Empty request
    $res = $this->providerInvoke('holdings', array());
    $expected = array();
    $this->assertEquals($expected, $res);

    // TCH2: Request holdings for non-existing item
    $res = $this->providerInvoke('holdings', array('iDontExist'));
    $expected = array(
      // MAT iDontExist
      'iDontExist' => array(
        'reservable' => FALSE,
        'available' => FALSE,
        'holdings' => array(),
        'is_internet' => FALSE,
        'total_count' => 0,
        'reserved_count' => 0,
        'is_periodical' => FALSE,
      ),
    );
    $this->assertEquals($expected, $res);

    // TCH3: Request holdings for "existing" item (MAT1), non-available, non-reservable
    $res = $this->providerInvoke('holdings', array('870970-basis:29911363'));
    $expected = array(
      // MAT1
      '870970-basis:29911363' => array(
        'reservable' => FALSE,
        'available' => FALSE,
        'holdings' => array(
        ),
        'is_internet' => FALSE,
        'total_count' => 0,
        'reserved_count' => 0,
        'is_periodical' => FALSE,
      ),
    );
    $this->assertEquals($expected, $res);

    // TCH4: Request holdings for existing item (MAT2), non-available, reservable
    $res = $this->providerInvoke('holdings', array('870970-basis:22629344'));
    $expected = array(
      // MAT2
      '870970-basis:22629344' => array(
        'reservable' => TRUE,
        'available' => FALSE,
        'holdings' => array(
          array(
            // ITEM21
            'placement' => array(
              'Horsens Bibliotek',
              'Skønlitteratur',
              'Musik',
              'Jazz',
            ),
            'available_count' => 0,
            'total_count' => 2,
            'reference_count' => 0,
          ),
        ),
        'is_internet' => FALSE,
        'total_count' => 2,
        'reserved_count' => 0,
        'is_periodical' => FALSE,
      ),
    );
    $this->assertEquals($expected, $res);

    // TCH5: Request holdings for existing item (MAT3), available, non-reservable
    $res = $this->providerInvoke('holdings', array('870970-basis:51299116'));
    $expected = array(
      // MAT3
      '870970-basis:51299116' => array(
        'reservable' => FALSE,
        'available' => TRUE,
        'holdings' => array(
          // Holding 1
          array(
            'placement' => array(
              'Horsens Bibliotek',
              'Lokal',
              'Magasin',
              'Læsekreds',
            ),
            'available_count' => 1,
            'total_count' => 1,
            'reference_count' => 0,
          ),
          // Holding 2
          array(
            'placement' => array(
              'Horsens Bibliotek',
              'Skønlitteratur',
              'Ungdom',
              'Læsekreds',
            ),
            'available_count' => 9,
            'total_count' => 9,
            'reference_count' => 0,
          ),
        ),
        'is_internet' => FALSE,
        'total_count' => 10,
        'reserved_count' => 0,
        'is_periodical' => FALSE,
      ),
    );
    $this->assertEquals($expected, $res);

    // TCH6: Request holdings for existing item (MAT4), available, reservable
    $res = $this->providerInvoke('holdings', array('870970-basis:44399989'));
    $expected = array(
      // MAT4
      '870970-basis:44399989' => array(
        'reservable' => TRUE,
        'available' => TRUE,
        'holdings' => array(
          // ITEM41
          array(
            'placement' => array(
              'Horsens Bibliotek',
              'Foyeren',
              'Ungdom',
              'Håndbøger',
            ),
            'available_count' => 1,
            'total_count' => 1,
            'reference_count' => 0,
          ),
        ),
        'is_internet' => FALSE,
        'total_count' => 1,
        'reserved_count' => 0,
        'is_periodical' => FALSE,
      ),
    );
    $this->assertEquals($expected, $res);


    // TCH8: Request holdings for multiple items
    $res = $this->providerInvoke('holdings', array('870970-basis:29911363', '870970-basis:22629344'));
    $expected = array(
      // MAT1
      '870970-basis:29911363' => array(
        'reservable' => FALSE,
        'available' => FALSE,
        'holdings' => array(),
        'is_internet' => FALSE,
        'total_count' => 0,
        'reserved_count' => 0,
        'is_periodical' => FALSE,
      ),
      // MAT2
      '870970-basis:22629344' => array(
        'reservable' => TRUE,
        'available' => FALSE,
        'holdings' => array(
          array(
            // ITEM21
            'placement' => array(
              'Horsens Bibliotek',
              'Skønlitteratur',
              'Musik',
              'Jazz',
            ),
            'available_count' => 0,
            'total_count' => 2,
            'reference_count' => 0,
          ),
        ),
        'is_internet' => FALSE,
        'total_count' => 2,
        'reserved_count' => 0,
        'is_periodical' => FALSE,
      ),
    );
    $this->assertEquals($expected, $res);

    // TCH9: Request holdings for multiple (inclusiv invalid) items
    $res = $this->providerInvoke('holdings', array('870970-basis:44399989','iDontExist'));
    $expected = array(
      // MAT4
      '870970-basis:44399989' => array(
        'reservable' => TRUE,
        'available' => TRUE,
        'holdings' => array(
          // ITEM41
          array(
            'placement' => array(
              'Horsens Bibliotek',
              'Foyeren',
              'Ungdom',
              'Håndbøger',
            ),
            'available_count' => 1,
            'total_count' => 1,
            'reference_count' => 0,
          ),
        ),
        'is_internet' => FALSE,
        'total_count' => 1,
        'reserved_count' => 0,
        'is_periodical' => FALSE,
      ),
       // MAT iDontExist
      'iDontExist' => array(
        'reservable' => FALSE,
        'available' => FALSE,
        'holdings' => array(),
        'is_internet' => FALSE,
        'total_count' => 0,
        'reserved_count' => 0,
        'is_periodical' => FALSE,
      ),
    );
    $this->assertEquals($expected, $res);

  }

  /**
   * Test that periodicals are properly represented.
   */
  public function testPeriodical() {
    $this->provider = 'availability';

    // reusing TCH5 somewhat
    $json_responses = array(
      array(
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => '870970-basis:51299116',
          'reservable' => FALSE,
          'holdings' => array(
            array(
              // Holding 1
              'materials' => array(
                array(
                  // ITEM
                  'itemNumber' => '5829213644',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                  'periodical' => array(
                    // Periodical.
                    'volume' => 1,
                    'volumeYear' => 2009,
                    'volumeNumber' => NULL,
                  ),
                ),
              ),
              'branch' => array(
                // AgencyBranch.
                'branchId' => 'DK-761500',
                'title' => 'Horsens Bibliotek',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 'LOK',
                'title' => 'Lokal',
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 'MAG',
                'title' => 'Magasin',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 'LKR',
                'title' => 'Læsekreds',
              ),
            ),
            array(
              // Holding 2
              'materials' => array(
                array(
                  // ITEM 0
                  'itemNumber' => '5829213636',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                  'periodical' => array(
                    // Periodical.
                    'volume' => 1,
                    'volumeYear' => 2010,
                  ),
                ),
                array(
                  // ITEM 1
                  'itemNumber' => '5829213637',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                  'periodical' => array(
                    // Periodical.
                    'volume' => 2,
                    'volumeYear' => 2010,
                  ),
                ),
                array(
                  // ITEM 2
                  'itemNumber' => '5829213638',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                  'periodical' => array(
                    // Periodical.
                    'volume' => 3,
                    'volumeYear' => 2010,
                  ),
                ),
                array(
                  // ITEM 3
                  'itemNumber' => '5829213639',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                  'periodical' => array(
                    // Periodical.
                    'volume' => 1,
                    'volumeYear' => 2011,
                    'volumeNumber' => 1,
                  ),
                ),
                array(
                  // ITEM 4
                  'itemNumber' => '5829213640',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                  'periodical' => array(
                    // Periodical.
                    'volume' => 2,
                    'volumeYear' => 2011,
                    'volumeNumber' => 1,
                  ),
                ),
                array(
                  // ITEM 5
                  'itemNumber' => '5829213641',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                  'periodical' => array(
                    // Periodical.
                    'volume' => 2,
                    'volumeYear' => 2011,
                    'volumeNumber' => 2,
                  ),
                ),
                array(
                  // ITEM 6
                  'itemNumber' => '5829213642',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                  'periodical' => array(
                    // Periodical.
                    'volume' => 1,
                    'volumeYear' => 2012,
                  ),
                ),
                array(
                  // ITEM 7
                  'itemNumber' => '5829213643',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                  'periodical' => array(
                    // Periodical.
                    'volume' => 2,
                    'volumeYear' => 2010,
                  ),
                ),
                array(
                  // ITEM 8
                  'itemNumber' => '5829213645',
                  'materialGroupName' => 'bookable',
                  'available' => TRUE,
                  'periodical' => null,
                ),
              ),
              'branch' => array(
                // AgencyBranch.
                'branchId' => 'DK-761500',
                'title' => 'Horsens Bibliotek',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 'SKN',
                'title' => 'Skønlitteratur',
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 'UNG',
                'title' => 'Ungdom',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 'LKR',
                'title' => 'Læsekreds',
              ),
            ),
          ),
        ),
      )
    );
    $this->replies($json_responses);

    // TCH5: Request holdings for existing item (MAT3), available, non-reservable
    $res = $this->providerInvoke('holdings', array('870970-basis:51299116'));
    $expected = array(
      // MAT3
      '870970-basis:51299116' => array(
        'reservable' => FALSE,
        'available' => TRUE,
        'holdings' => array(
          // Holding 1
          array(
            'placement' => array(
              'Horsens Bibliotek',
              'Lokal',
              'Magasin',
              'Læsekreds',
            ),
            'available_count' => 1,
            'total_count' => 1,
            'reference_count' => 0,
          ),
          // Holding 2
          array(
            'placement' => array(
              'Horsens Bibliotek',
              'Skønlitteratur',
              'Ungdom',
              'Læsekreds',
            ),
            'available_count' => 9,
            'total_count' => 9,
            'reference_count' => 0,
          ),
        ),
        'issues' => array(
          2010 => array(
            1 => array(
              'local_id' => 'fbs-1:2010:-:870970-basis::51299116',
              'placement' => array(
                'reservable' => FALSE,
                'available_count' => 1,
                'location' => 'Horsens Bibliotek > Skønlitteratur > Ungdom > Læsekreds',
                'total_count' => 1,
              ),
            ),
            2 => array(
              'local_id' => 'fbs-2:2010:-:870970-basis::51299116',
              'placement' => array(
                'reservable' => FALSE,
                'available_count' => 2,
                'location' => 'Horsens Bibliotek > Skønlitteratur > Ungdom > Læsekreds',
                'total_count' => 2,
              ),
            ),
            3 => array(
              'local_id' => 'fbs-3:2010:-:870970-basis::51299116',
              'placement' => array(
                'reservable' => FALSE,
                'available_count' => 1,
                'location' => 'Horsens Bibliotek > Skønlitteratur > Ungdom > Læsekreds',
                'total_count' => 1,
              ),
            ),
          ),
          2011 => array(
            '1-1' => array(
              'local_id' => 'fbs-1:2011:1:870970-basis::51299116',
              'placement' => array(
                'reservable' => FALSE,
                'available_count' => 1,
                'location' => 'Horsens Bibliotek > Skønlitteratur > Ungdom > Læsekreds',
                'total_count' => 1,
              ),
            ),
            '2-1' => array(
              'local_id' => 'fbs-2:2011:1:870970-basis::51299116',
              'placement' => array(
                'reservable' => FALSE,
                'available_count' => 1,
                'location' => 'Horsens Bibliotek > Skønlitteratur > Ungdom > Læsekreds',
                'total_count' => 1,
              ),
            ),
            '2-2' => array(
              'local_id' => 'fbs-2:2011:2:870970-basis::51299116',
              'placement' => array(
                'reservable' => FALSE,
                'available_count' => 1,
                'location' => 'Horsens Bibliotek > Skønlitteratur > Ungdom > Læsekreds',
                'total_count' => 1,
              ),
            ),
          ),
          2012 => array(
            1 => array(
              'local_id' => 'fbs-1:2012:-:870970-basis::51299116',
              'placement' => array(
                'reservable' => FALSE,
                'available_count' => 1,
                'location' => 'Horsens Bibliotek > Skønlitteratur > Ungdom > Læsekreds',
                'total_count' => 1,
              ),
            ),
          ),
          2009 => array(
            1 => array(
              'local_id' => 'fbs-1:2009:-:870970-basis::51299116',
              'placement' => array(
                'reservable' => FALSE,
                'available_count' => 1,
                'location' => 'Horsens Bibliotek > Lokal > Magasin > Læsekreds',
                'total_count' => 1,
              ),
            ),
          ),
        ),
        'is_internet' => FALSE,
        'total_count' => 10,
        'reserved_count' => 0,
        'is_periodical' => TRUE,
      ),
    );
    $this->assertEquals($expected, $res);
  }
}
