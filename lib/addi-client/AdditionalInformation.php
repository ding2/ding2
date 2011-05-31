<?php 

class AdditionalInformation {

	public $thumbnailUrl;
	public $detailUrl;
	
	public function __construct($thumbnailUrl, $detailUrl)
	{
		$this->thumbnailUrl = $thumbnailUrl;
		$this->detailUrl = $detailUrl;
	}
	
}