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
      // If we only want reservables, we only read in objects of type Bog*.
      $mfilehandle = fopen($this->filename, "r");
      while (($fline = fgets($mfilehandle)) !== false) {
        if ($fline != "") {
          // If we are only looking for reservables, we should only add real books.
          if ($this->onlyReservable) {
            $columns = explode("\t", $fline);
            if (count($columns) != 3) {
              return "Error: File '" . $this->filename . "' is expected to have three columns.";
            }
            if (substr($columns[2], 0, 3) == "Bog") {
              $marray[] = $fline;
            }
          }
          else {
            $marray[] = $fline;
          }
        }
      }
      fclose($mfilehandle);
      if (count($marray) < 1) {
        return "Error: file '" . $this->filename . "' was empty or did not contain any books.";
      }

      // Pick a random line of the ones read in, and dissolve it into fields, separated by tabs.
      $pointer = random_int(0, count($marray) - 1);
      $columns = explode("\t", $marray[$pointer]);

      // If the flag is set for only finding reservables, try up to 200 times to
      // find one that is reservable according to Connie conventions. Notice we
      // only try this for books, because other types are generally not reservable.
      $max = 200;
      while (--$max > 0 && $this->onlyReservable && !$this->isReservable($columns[0]) ) {
        // We found a random one to start with, now we spin forward until we
        // find a reservable one and loop around if we get to the end.
        $pointer++;
        if ($pointer == count($marray)) {
          $pointer = 0;
        }
        $columns = explode("\t", $marray[$pointer]);
      }
      if ($max == 0) {
        return "Error: no reservable information found " . $columns[0] . " " . $columns[2];
      }
      // Return the PID.
      return $columns[0];
    }
    else {
      return "Error: file " . $this->filename . " does not exist or is not readable!";
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
