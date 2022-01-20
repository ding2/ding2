<?php
/**
 * @file
 * AdditionalInformation class.
 */

class AdditionalInformation {

  public $thumbnailUrl;
  public $detailUrl;
  public $externUrl;
  public $netarchiveUrl;

  /**
   * AdditionalInformation constructor.
   */
  public function __construct($thumbnail_url, $detail_url, $extern_url, $netarchive_url = NULL) {
    $this->thumbnailUrl = $thumbnail_url;
    $this->detailUrl = $detail_url;
    $this->externUrl = $extern_url;
    $this->netarchiveUrl = $netarchive_url;
  }

}
