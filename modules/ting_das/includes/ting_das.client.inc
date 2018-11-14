<?php

/**
 * @file
 * Client to communicate with the Digital Article Services (DAS).
 */

use GuzzleHttp\Exception\GuzzleException;

/**
 * Class TingDasCopyRequest.
 */
class TingDasCopyRequest {

  private $client;
  private $url;
  private $wsUsername;
  private $wsPassword;

  private $pid = NULL;
  private $userLoanerId = NULL;
  private $userName = NULL;
  private $mail = NULL;
  private $userInterestDays = NULL;
  private $pickupAgencyId = NULL;
  private $agencyId = NULL;
  private $publicationTitle = NULL;
  private $publicationDateOfComponent = NULL;
  private $publicationYearOfComponent = NULL;
  private $issueOfComponent = NULL;
  private $volumeOfComponent = NULL;
  private $pagesOfComponent = NULL;

  /**
   * TingDasCopyRequest constructor.
   *
   * @param \GuzzleHttp\ClientInterface $client
   *   The client used to send the http request.
   * @param string $url
   *   The service endpoint for digital article service.
   * @param string $username
   *   The username to login with.
   * @param string $password
   *   The password to login with.
   */
  public function __construct(\GuzzleHttp\ClientInterface $client, string $url, string $username, string $password) {
    $this->client = $client;
    $this->url = $url;
    $this->wsUsername = $username;
    $this->wsPassword = $password;
  }

  /**
   * Set date well id.
   *
   * @param string $pid
   *   The date well id for the material requested.
   *
   * @return TingDasCopyRequest
   *   The current request object.
   */
  public function setPid(string $pid) {
    $this->pid = $pid;
    return $this;
  }

  /**
   * The data well id.
   *
   * @return string|null
   *   The data well pid if set else NULL.
   */
  public function getPid() {
    return $this->pid;
  }

  /**
   * Set the users loaner id.
   *
   * @param string $userLoanerId
   *   The users loaner id (borrow id/CPR).
   *
   * @return TingDasCopyRequest
   *   The current request object.
   */
  public function setUserLoanerId(string $userLoanerId) {
    $this->userLoanerId = $userLoanerId;
    return $this;
  }

  /**
   * Get the user loaner id.
   *
   * @return string|null
   *   The loaner id or null if not set.
   */
  public function getUserLoanerId() {
    return $this->userLoanerId;
  }

  /**
   * Set the username (full name of the user).
   *
   * @param string $userName
   *   The users full name.
   *
   * @return TingDasCopyRequest
   *   The current request object.
   */
  public function setUserName(string $userName) {
    $this->userName = $userName;
    return $this;
  }

  /**
   * Get the users full name.
   *
   * @return string|null
   *   The users full name.
   */
  public function getUserName() {
    return $this->userName;
  }

  /**
   * Set the users e-mail-address.
   *
   * @param string $mail
   *   The users e-mail-address.
   *
   * @return TingDasCopyRequest
   *   The current request object.
   */
  public function setUserMail(string $mail) {
    $this->mail = $mail;
    return $this;
  }

  /**
   * Get the users e-mail-address.
   *
   * @return string|null
   *   The users e-mail-address.
   */
  public function getUserMail() {
    return $this->mail;
  }

  /**
   * The interest date for the user.
   *
   * The date until the user is not longer interested in getting the material.
   *
   * @param int $userInterestDays
   *   The users interest date in number of days.
   *
   * @return TingDasCopyRequest
   *   The current request object.
   */
  public function setUserInterestDate(int $userInterestDays) {
    $this->userInterestDays = $userInterestDays;
    return $this;
  }

  /**
   * Get the users interest date.
   *
   * @param string $format
   *   The date format to use.
   *
   * @return string|FALSE
   *   The users interest date in the format given from now.
   */
  public function getUserInterestDate($format = 'Y-m-d') {
    $date = strtotime('+' . $this->userInterestDays . ' day');
    return date($format, $date);
  }

  /**
   * Set the agency id for pickup.
   *
   * @param string $pickupAgencyId
   *   The pickup agency id.
   *
   * @return TingDasCopyRequest
   *   The current request object.
   */
  public function setPickupAgencyId(string $pickupAgencyId) {
    $this->pickupAgencyId = $pickupAgencyId;
    return $this;
  }

  /**
   * Get pickup agency id.
   *
   * @return string|null
   *   The pickup agency id.
   */
  public function getPickupAgencyId() {
    return $this->pickupAgencyId;
  }

  /**
   * Set agency id.
   *
   * @param string $agencyId
   *   The agency id.
   *
   * @return TingDasCopyRequest
   *   The current request object.
   */
  public function setAgencyId(string $agencyId) {
    $this->agencyId = $agencyId;
    return $this;
  }

  /**
   * Get agency id.
   *
   * @return string|null
   *   The agency id.
   */
  public function getAgencyId() {
    return $this->agencyId;
  }

  /**
   * The title of the publication.
   *
   * @param string $publicationTitle
   *   The publications title.
   *
   * @return TingDasCopyRequest
   *   The current request object.
   */
  public function setPublicationTitle(string $publicationTitle) {
    $this->publicationTitle = $publicationTitle;
    return $this;
  }

  /**
   * Get article title.
   *
   * @return string|null
   *   The article title.
   */
  public function getPublicationTitle() {
    return $this->publicationTitle;
  }

  /**
   * Set the date of publication.
   *
   * @param string $publicationDateOfComponent
   *   Article publication date.
   *
   * @return TingDasCopyRequest
   *   The current request object.
   */
  public function setPublicationDateOfComponent(string $publicationDateOfComponent) {
    $this->publicationDateOfComponent = $publicationDateOfComponent;
    return $this;
  }

  /**
   * Get article date.
   *
   * @return string|null
   *   The article date.
   */
  public function getPublicationDateOfComponent() {
    return $this->publicationDateOfComponent;
  }

  /**
   * Set the article year.
   *
   * @param string $publicationYearOfComponent
   *   Article year.
   *
   * @return TingDasCopyRequest
   *   The current request object.
   */
  public function setPublicationYearOfComponent(string $publicationYearOfComponent) {
    $this->publicationYearOfComponent = $publicationYearOfComponent;
    return $this;
  }

  /**
   * Get the article year.
   *
   * @return string|null
   *   The article year.
   */
  public function getPublicationYearOfComponent() {
    return $this->publicationYearOfComponent;
  }

  /**
   * Set article issue number.
   *
   * @param string $issueOfComponent
   *   Article issue number.
   *
   * @return TingDasCopyRequest
   *   The current request object.
   */
  public function setIssueOfComponent(string $issueOfComponent) {
    $this->issueOfComponent = $issueOfComponent;
    return $this;
  }

  /**
   * Get article issue number.
   *
   * @return string
   *    The issue number.
   */
  public function getIssueOfComponent() {
    return $this->issueOfComponent;
  }

  /**
   * Set the the volume number.
   *
   * @param string $volumeOfComponent
   *   The article volume number.
   *
   * @return TingDasCopyRequest
   *   The current request object.
   */
  public function setVolumeOfComponent(string $volumeOfComponent) {
    $this->volumeOfComponent = $volumeOfComponent;
    return $this;
  }

  /**
   * Get the article volume number.
   *
   * @return string|null
   *   The article volume number.
   */
  public function getVolumeOfComponent() {
    return $this->volumeOfComponent;
  }

  /**
   * Set the page number in the publication.
   *
   * @param int $pagesOfComponent
   *   The page number.
   *
   * @return TingDasCopyRequest
   *   The current request object.
   */
  public function setPagesOfComponent(int $pagesOfComponent) {
    $this->pagesOfComponent = $pagesOfComponent;
    return $this;
  }

  /**
   * Get the page number.
   *
   * @return string|null
   *   The page number.
   */
  public function getPagesOfComponent() {
    return $this->pagesOfComponent;
  }

  /**
   * Send request to the service.
   *
   * @return bool
   *   TRUE if request was send else FALSE.
   */
  public function send() {
    $options = array(
      'headers' => array(
        'Content-Type' => 'application/xml; charset=UTF8',
      ),
      'body' => $this->buildMessage(),
    );

    try {
      $this->client->request('POST', $this->url, $options);

      // We don't look at the response but assumes that everything is okay. This
      // is do to the fact that the service at current time only returns 204
      // regardless of what was sent as long as the XML message is correct. If
      // the message is wrong a non 200 code will be returned, which will
      // trigger and guzzle exception (handled below).
      return TRUE;
    }
    catch (GuzzleException $exception) {
      watchdog_exception('ting_das', $exception);
    }

    return FALSE;
  }

  /**
   * Build XML message.
   *
   * @return string
   *   The message as XML.
   */
  private function buildMessage() {
    $xml = new SimpleXMLElement('<?xml version="1.0" encoding="utf-8"?><placeCopyRequest xmlns="http://statsbiblioteket.dk/xws/elba-placecopyrequest-schema"/>');

    // Set required fields.
    $xml->addChild('ws_user', $this->wsUsername);
    $xml->addChild('ws_password', $this->wsPassword);
    $xml->addChild('pid', $this->getPid());
    $xml->addChild('user_loaner_id', $this->getUserLoanerId());
    $xml->addChild('userName', $this->getUserName());
    $xml->addChild('userMail', $this->getUserMail());
    $xml->addChild('user_interest_date', $this->getUserInterestDate('Y-m-d'));
    $xml->addChild('pickupAgencyId', $this->getPickupAgencyId());
    $xml->addChild('agencyId', $this->getAgencyId());
    $xml->addChild('publicationTitle', $this->getPublicationTitle());
    $xml->addChild('publicationDateOfComponent', $this->getPublicationDateOfComponent());
    $xml->addChild('publicationYearOfComponent', $this->getPublicationYearOfComponent());
    $xml->addChild('issueOfComponent', $this->getIssueOfComponent());
    $xml->addChild('volumeOfComponent', $this->getVolumeOfComponent());
    $xml->addChild('pagesOfComponent', $this->getPagesOfComponent());

    return $xml->asXML();
  }

}
