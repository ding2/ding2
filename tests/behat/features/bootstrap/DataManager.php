<?php

class DataManager extends \Page\PageBase
{
  /**
   * @var string $filename
   */
  protected $filename = '';

  /**
   * @var bool $onlyReservable
   */
  protected $onlyReservable = false;
  /**
   * @return mixed getFilename
   */
  public function getFilename()
  {
    return $this->filename;
  }

  /**
   * @param bool $reservable
   * @return mixed|string
   * @throws Exception
   */
  public function getRandomPID() {
    $marray = [];
    if (is_readable($this->filename)) {

      // now open, and read in all lines until no more data is returned, or we found a match
      $mfilehandle = fopen($this->filename, "r");
      $foundit=false;

      $fline = fgets($mfilehandle);
      if ($fline!="") {
        $marray[] = $fline;
      }
      // now go through the rest of the file
      while (($fline = fgets($mfilehandle)) !== false) {
        if ($fline!="") {
          $marray[] = $fline;
        }
      }
      fclose($mfilehandle);
      if (count($marray) < 1) {
        return "File '" . $this->filename . "' was empty";
      }

      $tmp = explode("\t", $marray[(random_int(0, count($marray)-1))] );
      if (count($tmp)!=2) {
        return "File '" . $this->filename . "' expected to have two columns.";
      }
      $max = 200;
      while (--$max>0 && $this->onlyReservable && !$this->isReservable($tmp[0])) {
        $tmp = explode("\t", $marray[(random_int(0, count($marray)-1))] );
        if (count($tmp)!=2) {
          return "File '" . $this->filename . "' expected to have two columns.";
        }
      }
      if ($max==0) {
        return "Error - no reservable information found";
      }
      // return the PID
      return $tmp[0];
    }
  }

  /* returns false only if material is reservable according to Connie rules.
   ** todo: how to do this on other providers?
    *
    */
  private function isReservable($mpid)
  {
    $xx = explode(":", $mpid);
    $provider = $xx[count($xx)-1];
    if ($provider % 2 == 0) {
      if (($provider / 10) % 2 == 0) {
        return true;
      }
    }
    return false;
  }

  /**
   * @param $setFilename
   */
  public function setFilename($setFilename) {
    $this->filename = $setFilename;
  }

  public function setReservable($truefalse) {
    $this->onlyReservable = $truefalse;
  }


}