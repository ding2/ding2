<?php

/**
 * @file
 * Test the periodical local_id roundtrip.
 */

require_once 'includes/classes/FBS.php';

/**
 * Test getter/parser agaist a selection of periodicals.
 */
class PeriodicalLocalIdTest extends PHPUnit_Framework_TestCase {
  /**
   * Set up the test.
   */
  public function setUp() {
    require_once "fbs.module";
  }

  public function testLocalId() {
    $cases = array(
      array(
        'recordId' => '870970-basis:51299116',
        'volume' => 1,
        'volumeYear' => 2012,
        'volumeNumber' => NULL,
        'expected' => 'fbs-1:2012:-:870970-basis::51299116',
      ),
      array(
        'recordId' => '870970-basis:51299116',
        'volume' => 1,
        'volumeYear' => 2012,
        'volumeNumber' => 13,
        'expected' => 'fbs-1:2012:13:870970-basis::51299116',
      ),
      array(
        'recordId' => '870970-basis::51299116',
        'volume' => 1,
        'volumeYear' => 2012,
        'volumeNumber' => 13,
        'expected' => 'fbs-1:2012:13:870970-basis::::51299116',
      ),
    );

    foreach ($cases as $case) {
      $periodical = new FBS\Model\PeriodicalReservation();
      $periodical->volume = $case['volume'];
      $periodical->volumeYear = $case['volumeYear'];
      $periodical->volumeNumber = $case['volumeNumber'];

      $local_id = _fbs_periodical_get_local_id($case['recordId'], $periodical);

      $this->assertEquals($case['expected'], $local_id);

      list($record_id, $new_periodical) = _fbs_periodical_parse_local_id($local_id);
      $this->assertEquals($case['recordId'], $record_id);
      $this->assertEquals($periodical, $new_periodical);
    }
  }
}
