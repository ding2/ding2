<?php

/**
 * Default exception.
 */
class DingProviderConsentException extends Exception
{
  public function __construct() {
    parent::__construct(t('Missing user consent'), 1);
  }
}
