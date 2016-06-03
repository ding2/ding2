<?php
/**
 * @file
 * AdditionalInformation class.
 */ 

class AdditionalInformation {

  public $thumbnailUrl;
  public $detailUrl;
  public $backPageUrl;

  public function __construct($thumbnail_url, $detail_url, $back_page) {
    $this->thumbnailUrl = $thumbnail_url;
    $this->detailUrl = $detail_url;
    $this->backPageUrl = $back_page;
  }

}
