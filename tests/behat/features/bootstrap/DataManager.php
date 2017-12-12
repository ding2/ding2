<?php

/**
 * @file
 * DataManager. Handles data from files.
 */

/**
 * Class DataManager
 */
class DataManager extends \Page\PageBase {
  /**
   * Filename.
   *
   * @var string $filename
   */
  protected $filename = '';

  /**
   * Flag for reservable only.
   *
   * @var bool $onlyReservable
   *    True if only finding reservable objects.
   */
  protected $onlyReservable = false;

  /**
   * GetFilename.
   *
   * @return mixed
   *    The current filename.
   */
  public function getFilename() {
    return $this->filename;
  }

  /**
   * GetRandomPID
   *
   * @return mixed|string
   *    Return the PID that was found.
   *
   * @throws Exception
   *    In case of error.
   */
  public function getRandomPID() {
    $marray = [];
    if (is_readable($this->filename)) {

      // Now open, and read in all lines until no more data is returned, or we found a match.
      $mfilehandle = fopen($this->filename, "r");

      $fline = fgets($mfilehandle);
      if ($fline != "") {
        $marray[] = $fline;
      }
      // Now go through the rest of the file.
      while (($fline = fgets($mfilehandle)) !== false) {
        if ($fline != "") {
          $marray[] = $fline;
        }
      }
      fclose($mfilehandle);
      if (count($marray) < 1) {
        return "File '" . $this->filename . "' was empty";
      }

      $tmp = explode("\t", $marray[(random_int(0, count($marray) - 1))]);
      if (count($tmp) != 2) {
        return "File '" . $this->filename . "' expected to have two columns.";
      }
      $max = 200;
      while (--$max > 0 && $this->onlyReservable && !$this->isReservable($tmp[0])) {
        $tmp = explode("\t", $marray[(random_int(0, count($marray) - 1))]);
        if (count($tmp) != 2) {
          return "File '" . $this->filename . "' expected to have two columns.";
        }
      }
      if ($max == 0) {
        return "Error - no reservable information found";
      }
      // Return the PID.
      return $tmp[0];
    }
  }

  /**
   * Returns false only if material is reservable according to Connie rules.
   *
   * @todo: how to do this on other providers?
   */
  private function isReservable($mpid) {
    $xx = explode(":", $mpid);
    $provider = $xx[count($xx) - 1];
    if ($provider % 2 == 0) {
      if (($provider / 10) % 2 == 0) {
        return true;
      }
    }
    return false;
  }

  /**
   * SetFilename
   *
   * @param string $setFilename
   *    Filename to use.
   */
  public function setFilename($setFilename) {
    $this->filename = $setFilename;
  }

  /**
   * SetReservable.
   *
   * @param bool $truefalse
   *    Set flag for whether material should be reservable or not.
   */
  public function setReservable($truefalse) {
    $this->onlyReservable = $truefalse;
  }
}
