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
        'volume' => '1',
        'volumeYear' => '2012',
        'volumeNumber' => NULL,
        'expected' => 'fbs-1:2012:-:870970-basis::51299116',
      ),
      array(
        'recordId' => '870970-basis:51299116',
        'volume' => '1',
        'volumeYear' => '2012',
        'volumeNumber' => '13',
        'expected' => 'fbs-1:2012:13:870970-basis::51299116',
      ),
      array(
        'recordId' => '870970-basis::51299116',
        'volume' => '1',
        'volumeYear' => '2012',
        'volumeNumber' => '13',
        'expected' => 'fbs-1:2012:13:870970-basis::::51299116',
      ),
    );

    foreach ($cases as $case) {
      $periodical = new FBS\Model\Periodical();
      $periodicalRes = new FBS\Model\PeriodicalReservation();
      $periodicalRes->volume = $periodical->volume = $case['volume'];
      $periodicalRes->volumeYear = $periodical->volumeYear = $case['volumeYear'];
      $periodicalRes->volumeNumber = $periodical->volumeNumber = $case['volumeNumber'];

      $local_id = _fbs_periodical_get_local_id($case['recordId'], $periodical);

      $this->assertEquals($case['expected'], $local_id);

      list($record_id, $new_periodical) = _fbs_periodical_parse_local_id($local_id);
      $this->assertSame($case['recordId'], $record_id);
      $this->assertEquals($periodicalRes, $new_periodical);
      // Assert that the individual properties aren't just effectually equal,
      // but of the same type. We can't use assertSame on the periodical
      // objects, as they're not the same object.
      $this->assertSame($periodicalRes->volume, $new_periodical->volume);
      $this->assertSame($periodicalRes->volumeYear, $new_periodical->volumeYear);
      $this->assertSame($periodicalRes->volumeNumber, $new_periodical->volumeNumber);
    }
  }
}
