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
  private $mail = NULL;
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
   * Send request to the service.
   *
   * @throws \GuzzleHttp\Exception\GuzzleException
   *   If the message fail a non 200 code will be returned as an exception.
   */
  public function send() {
    $options = array(
      'headers' => array(
        'Content-Type' => 'application/xml; charset=UTF8',
      ),
      'body' => $this->buildMessage(),
    );

    $this->client->request('POST', $this->url, $options);

    // We don't look at the response but assumes that everything is okay. This
    // is do to the fact that the service at current time only returns 204
    // regardless of what was sent as long as the XML message is correct. If
    // the message is wrong a non 200 code will be returned, which will
    // trigger and guzzle exception.
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
    $xml->addChild('pid', $this->pid);
    $xml->addChild('userMail', $this->mail);
    $xml->addChild('agencyId', $this->agencyId);
    $xml->addChild('publicationTitle', $this->publicationTitle);
    $xml->addChild('publicationDateOfComponent', $this->publicationDateOfComponent);
    $xml->addChild('publicationYearOfComponent', $this->publicationYearOfComponent);
    $xml->addChild('issueOfComponent', $this->issueOfComponent);
    $xml->addChild('volumeOfComponent', $this->volumeOfComponent);
    $xml->addChild('pagesOfComponent', $this->pagesOfComponent);

    return $xml->asXML();
  }
}
