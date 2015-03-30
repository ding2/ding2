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
      array(),

      // TCA3: Return availability for material MAT1
      array(
        array(
          'recordId' => 'REC1',
          'available' => FALSE,
          'reservable' => FALSE,
        ),
      ),
      // TCA4: Return availability for material MAT2
      array(
        array(
          'recordId' => 'REC2',
          'available' => FALSE,
          'reservable' => TRUE,
        ),
      ),
      // TCA5: Return availability for material MAT3
      array(
        array(
          'recordId' => 'REC3',
          'available' => TRUE,
          'reservable' => FALSE,
        ),
      ),
      // TCA6: Return availability for material MAT4
      array(
        array(
          'recordId' => 'REC4',
          'available' => TRUE,
          'reservable' => TRUE,
        ),
      ),
      // TCA7: Return availability for material MAT1, MAT2, MAT3, MAT4
      array(
        array(
          'recordId' => 'REC1',
          'available' => FALSE,
          'reservable' => FALSE,
        ),
        array(
          'recordId' => 'REC2',
          'available' => FALSE,
          'reservable' => TRUE,
        ),
        array(
          'recordId' => 'REC3',
          'available' => TRUE,
          'reservable' => FALSE,
        ),
        array(
          'recordId' => 'REC4',
          'available' => TRUE,
          'reservable' => TRUE,
        ),
      ),
      // TCA8: Return availability for material MAT1, MAT2, MAT3, MAT4 (and % for non-existing material)
      array(
        array(
          'recordId' => 'REC1',
          'available' => FALSE,
          'reservable' => FALSE,
        ),
        array(
          'recordId' => 'REC2',
          'available' => FALSE,
          'reservable' => TRUE,
        ),
        array(
          'recordId' => 'REC3',
          'available' => TRUE,
          'reservable' => FALSE,
        ),
        array(
          'recordId' => 'REC4',
          'available' => TRUE,
          'reservable' => TRUE,
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
    $expected = array();
    $this->assertEquals($expected, $res);

    // TCA3: Request availability for existing item, non-available, non-reservable
    $res = $this->providerInvoke('items', array('REC1'));
    $expected = array('REC1' => array('available' => FALSE, 'reservable' => FALSE));
    $this->assertEquals($expected, $res);

    // TCA4: Request availability for existing item, non-available, reservable
    $res = $this->providerInvoke('items', array('REC2'));
    $expected = array('REC2' => array('available' => FALSE, 'reservable' => TRUE));
    $this->assertEquals($expected, $res);

    // TCA5: Request availability for existing item, available, non-reservable
    $res = $this->providerInvoke('items', array('REC3'));
    $expected = array('REC3' => array('available' => TRUE, 'reservable' => FALSE));
    $this->assertEquals($expected, $res);

    // TCA6: Request availability for existing item, available, reservable
    $res = $this->providerInvoke('items', array('REC4'));
    $expected = array('REC4' => array('available' => TRUE, 'reservable' => TRUE));
    $this->assertEquals($expected, $res);

    // TCA7: Request availability for multiple (valid) items
    $res = $this->providerInvoke('items', array('REC1','REC2','REC3','REC4'));
    $expected = array(
      'REC1' => array(
        'available' => FALSE,
        'reservable' => FALSE,
      ),
      'REC2' => array(
        'available' => FALSE,
        'reservable' => TRUE,
      ),
      'REC3' => array(
        'available' => TRUE,
        'reservable' => FALSE,
      ),
      'REC4' => array(
        'available' => TRUE,
        'reservable' => TRUE,
      ),
    );

    // TCA8: Request availability for multiple (including invalid) items
    $res = $this->providerInvoke('items', array('REC1','REC2','REC3','REC4',NULL,'iDontExist'));
    $expected = array(
      'REC1' => array(
        'available' => FALSE,
        'reservable' => FALSE,
      ),
      'REC2' => array(
        'available' => FALSE,
        'reservable' => TRUE,
      ),
      'REC3' => array(
        'available' => TRUE,
        'reservable' => FALSE,
      ),
      'REC4' => array(
        'available' => TRUE,
        'reservable' => TRUE,
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
      array(),

      // TCH3: Return holdings for material MAT1: reservable/available=false
      array(
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => 'REC1',
          'reservable' => FALSE,
          'holdings' => array(
            array(
              // Holding.
              'materials' => array(
                array(
                  // Material.
                  'itemNumber' => 'ITEMNUM11',
                  'available' => FALSE,
                  'materialGroupName' => 'Material group',
                ),
              ),
              'branch' => array(
                // AgencyBranch.
                'branchId' => 'BRA1',
                'title' => 'TBRA1',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 'DEP1',
                'title' => 'TDEP1',
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 'LOC1',
                'title' => 'TLOC1',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 'SUB1',
                'title' => 'TSUB1',
              ),
            ),
          ),
        ),
      ),

      // TCH4: Return holdings for material MAT2: reservable=true/available=false
      array(
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => 'REC2',
          'reservable' => TRUE,
          'holdings' => array(
            array(
              // Holding 1
              'materials' => array(
                array(
                  // Material.
                  'itemNumber' => 'ITEMNUM21',
                  'available' => FALSE,
                  'materialGroupName' => 'Material group',
                ),
              ),
              'branch' => array(
                // AgencyBranch.
                'branchId' => 'BRA1',
                'title' => 'TBRA1',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 'DEP1',
                'title' => 'TDEP1',
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 'LOC1',
                'title' => 'TLOC1',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 'SUB1',
                'title' => 'TSUB1',
              ),
            ),
            array(
              // Holding 2
              'materials' => array(
                array(
                  // Material.
                  'itemNumber' => 'ITEMNUM22',
                  'available' => FALSE,
                  'materialGroupName' => 'Material group',
                ),
              ),
              'branch' => array(
                // AgencyBranch.
                'branchId' => 'BRA1',
                'title' => 'TBRA1',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 'DEP1',
                'title' => 'TDEP1',
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 'LOC2',
                'title' => 'TLOC2',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 'SUB2',
                'title' => 'TSUB2',
              ),
            ),
            array(
              // Holding 3
              'materials' => array(
                array(
                  // Material.
                  'itemNumber' => 'ITEMNUM23',
                  'available' => FALSE,
                  'materialGroupName' => 'Material group',
                ),
              ),
              'branch' => array(
                // AgencyBranch.
                'branchId' => 'BRA1',
                'title' => 'TBRA1',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 'DEP2',
                'title' => 'TDEP2',
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 'LOC1',
                'title' => 'TLOC1',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 'SUB3',
                'title' => 'TSUB3',
              ),
            ),
          ),
        ),
      ),

      // TCH5: Return holdings for material MAT3: reservable=false/available=true
      array(
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => 'REC3',
          'reservable' => FALSE,
          'holdings' => array(
            array(
              // Holding
              'materials' => array(
                array(
                  // ITEM
                  'itemNumber' => 'ITEMNUM31',
                  'available' => TRUE,
                ),
              ),
              'branch' => array(
                // AgencyBranch.
                'branchId' => 'BRA1',
                'title' => 'TBRA1',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 'DEP2',
                'title' => 'TDEP2',
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 'LOC2',
                'title' => 'TLOC2',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 'SUB2',
                'title' => 'TSUB2',
              ),
            ),
          ),
        ),
      ),

      // TCH6: Return holdings for material MAT4: reservable/available=true
      array(
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => 'REC4',
          'reservable' => TRUE,
          'holdings' => array(
            array(
              // Holdings.
              'materials' => array(
                array(
                  // ITEM 1
                  'itemNumber' => 'ITEMNUM41',
                  'available' => TRUE,
                ),
                array(
                  // ITEM 2
                  'itemNumber' => 'ITEMNUM42',
                  'available' => TRUE,
                ),
                array(
                  // ITEM 3
                  'itemNumber' => 'ITEMNUM43',
                  'available' => FALSE,
                ),
              ),
              'branch' => array(
                // AgencyBranch.
                'branchId' => 'BRA1',
                'title' => 'TBRA1',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 'DEP2',
                'title' => 'TDEP2',
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 'LOC1',
                'title' => 'TLOC1',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 'SUB4',
                'title' => 'TSUB4',
              ),
            ),
          ),
        ),
      ),

      // TCH7: Return holdings for MAT5
      array(
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => 'REC5',
          'reservable' => TRUE,
          'holdings' => array(
            array(
              // Holdings.
              'materials' => array(
                array(
                  // Material.
                  'itemNumber' => 'ITEMNUM51',
                  'available' => TRUE,
                  'materialGroupName' => 'Material group',
                ),
              ),
              'branch' => array(
                // AgencyBranch.
                'branchId' => 'BRA1',
                'title' => 'TBRA1',
              ),
              'department' => NULL,
              'location' => NULL,
              'sublocation' => NULL,
            ),
          ),
        ),
      ),

      // TCH8: Return holdings for MAT1 & MAT3
      array(
        // MAT1
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => 'REC1',
          'reservable' => FALSE,
          'holdings' => array(
            array(
              // Holding.
              'materials' => array(
                array(
                  // Material.
                  'itemNumber' => 'ITEMNUM11',
                  'available' => FALSE,
                  'materialGroupName' => 'Material group',
                ),
              ),
              'branch' => array(
                // AgencyBranch.
                'branchId' => 'BRA1',
                'title' => 'TBRA1',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 'DEP1',
                'title' => 'TDEP1',
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 'LOC1',
                'title' => 'TLOC1',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 'SUB1',
                'title' => 'TSUB1',
              ),
            ),
          ),
        ),
        // MAT3
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => 'REC3',
          'reservable' => FALSE,
          'holdings' => array(
            array(
              // Holding
              'materials' => array(
                array(
                  // ITEM
                  'itemNumber' => 'ITEMNUM31',
                  'available' => TRUE,
                ),
              ),
              'branch' => array(
                // AgencyBranch.
                'branchId' => 'BRA1',
                'title' => 'TBRA1',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 'DEP2',
                'title' => 'TDEP2',
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 'LOC2',
                'title' => 'TLOC2',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 'SUB2',
                'title' => 'TSUB2',
              ),
            ),
          ),
        ),
      ),

      // TCH9: Return holdings for MAT1 & iDontExist
      array(
        // MAT1
        array(
          // HoldingsForBibliographicalRecord.
          'recordId' => 'REC1',
          'reservable' => FALSE,
          'holdings' => array(
            array(
              // Holding.
              'materials' => array(
                array(
                  // Material.
                  'itemNumber' => 'ITEMNUM11',
                  'available' => FALSE,
                  'materialGroupName' => 'Material group',
                ),
              ),
              'branch' => array(
                // AgencyBranch.
                'branchId' => 'BRA1',
                'title' => 'TBRA1',
              ),
              'department' => array(
                // AgencyDepartment.
                'departmentId' => 'DEP1',
                'title' => 'TDEP1',
              ),
              'location' => array(
                // AgencyLocation.
                'locationId' => 'LOC1',
                'title' => 'TLOC1',
              ),
              'sublocation' => array(
                // AgencySublocation.
                'sublocationId' => 'SUB1',
                'title' => 'TSUB1',
              ),
            ),
          ),
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
    $expected = array();
    $this->assertEquals($expected, $res);

    // TCH3: Request holdings for existing item (MAT1), non-available, non-reservable
    $res = $this->providerInvoke('holdings', array('REC1'));
    $expected = array(
      // MAT1
      'REC1' => array(
        'reservable' => FALSE,
        'available' => FALSE,
        'holdings' => array(
          // ITEM11
          array(
            'placement' => array(
              'TBRA1',
              'TDEP1',
              'TLOC1',
              'TSUB1',
            ),
            'available_count' => 0,
            'total_count' => 1,
            'reference_count' => 0,
          ),
        ),
        'is_internet' => FALSE,
        'total_count' => 1,
        'reserved_count' => 0,
      ),
    );
    $this->assertEquals($expected, $res);

    // TCH4: Request holdings for existing item (MAT2), non-available, reservable
    $res = $this->providerInvoke('holdings', array('REC2'));
    $expected = array(
      // MAT2
      'REC2' => array(
        'reservable' => TRUE,
        'available' => FALSE,
        'holdings' => array(
          array(
            // ITEM21
            'placement' => array(
              'TBRA1',
              'TDEP1',
              'TLOC1',
              'TSUB1',
            ),
            'available_count' => 0,
            'total_count' => 1,
            'reference_count' => 0,
          ),
          // ITEM22
          array(
            'placement' => array(
              'TBRA1',
              'TDEP1',
              'TLOC2',
              'TSUB2',
            ),
            'available_count' => 0,
            'total_count' => 1,
            'reference_count' => 0,
          ),
          // ITEM23
          array(
            'placement' => array(
              'TBRA1',
              'TDEP2',
              'TLOC1',
              'TSUB3',
            ),
            'available_count' => 0,
            'total_count' => 1,
            'reference_count' => 0,
          ),
        ),
        'is_internet' => FALSE,
        'total_count' => 3,
        'reserved_count' => 0,
      ),
    );
    $this->assertEquals($expected, $res);

    // TCH5: Request holdings for existing item (MAT3), available, non-reservable
    $res = $this->providerInvoke('holdings', array('REC3'));
    $expected = array(
      // MAT3
      'REC3' => array(
        'reservable' => FALSE,
        'available' => TRUE,
        'holdings' => array(
          // ITEM31
          array(
            'placement' => array(
              'TBRA1',
              'TDEP2',
              'TLOC2',
              'TSUB2',
            ),
            'available_count' => 1,
            'total_count' => 1,
            'reference_count' => 0,
          ),
        ),
        'is_internet' => FALSE,
        'total_count' => 1,
        'reserved_count' => 0,
      ),
    );
    $this->assertEquals($expected, $res);

    // TCH6: Request holdings for existing item (MAT4), available, reservable
    $res = $this->providerInvoke('holdings', array('REC4'));
    $expected = array(
      // MAT4
      'REC4' => array(
        'reservable' => TRUE,
        'available' => TRUE,
        'holdings' => array(
          // ITEM41 & ITEM42
          array(
            'placement' => array(
              'TBRA1',
              'TDEP2',
              'TLOC1',
              'TSUB4',
            ),
            'available_count' => 2,
            'total_count' => 3,
            'reference_count' => 0,
          ),
        ),
        'is_internet' => FALSE,
        'total_count' => 3,
        'reserved_count' => 0,
      ),
    );
    $this->assertEquals($expected, $res);

    // TCH7: Request holdings for existing item (MAT5) without placement info
    $res = $this->providerInvoke('holdings', array('REC5'));
    $expected = array(
      'REC5' => array(
        'reservable' => TRUE,
        'available' => TRUE,
        'holdings' => array(
          array(
            'placement' => array(
              'TBRA1'
            ),
            'available_count' => 1,
            'total_count' => 1,
            'reference_count' => 0,
          ),
        ),
        'is_internet' => FALSE,
        'total_count' => 1,
        'reserved_count' => 0,
      ),
    );
    $this->assertEquals($expected, $res);

    // TCH8: Request holdings for multiple (valid) items
    $res = $this->providerInvoke('holdings', array('REC1', 'REC3'));
    $expected = array(
      // MAT1
      'REC1' => array(
        'reservable' => FALSE,
        'available' => FALSE,
        'holdings' => array(
          // ITEM11
          array(
            'placement' => array(
              'TBRA1',
              'TDEP1',
              'TLOC1',
              'TSUB1',
            ),
            'available_count' => 0,
            'total_count' => 1,
            'reference_count' => 0,
          ),
        ),
        'is_internet' => FALSE,
        'total_count' => 1,
        'reserved_count' => 0,
      ),
      // MAT3
      'REC3' => array(
        'reservable' => FALSE,
        'available' => TRUE,
        'holdings' => array(
          // ITEM31
          array(
            'placement' => array(
              'TBRA1',
              'TDEP2',
              'TLOC2',
              'TSUB2',
            ),
            'available_count' => 1,
            'total_count' => 1,
            'reference_count' => 0,
          ),
        ),
        'is_internet' => FALSE,
        'total_count' => 1,
        'reserved_count' => 0,
      ),
    );
    $this->assertEquals($expected, $res);

    // TCH9: Request holdings for multiple (inclusiv invalid) items
    $res = $this->providerInvoke('holdings', array('REC1','iDontExist'));
    $expected = array(
      // MAT1
      'REC1' => array(
        'reservable' => FALSE,
        'available' => FALSE,
        'holdings' => array(
          // ITEM11
          array(
            'placement' => array(
              'TBRA1',
              'TDEP1',
              'TLOC1',
              'TSUB1',
            ),
            'available_count' => 0,
            'total_count' => 1,
            'reference_count' => 0,
          ),
        ),
        'is_internet' => FALSE,
        'total_count' => 1,
        'reserved_count' => 0,
      ),
    );
    $this->assertEquals($expected, $res);

  }
}
