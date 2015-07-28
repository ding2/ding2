<?php
/**
 * Infomedia - retrieve article identified by faust
 *
 * @param int $id Faust
 * @return TingClientInfomediaResult
 */

module_load_include('client.inc', 'ting');

function ting_infomedia_get_article($id) {
  try {
    $factory = ting_get_request_factory();
  }
  catch( TingClientException $e ) {
    watchdog($e->message);
  }

  $request = $factory->getInfomediaArticleRequest();
  $request->makeGet();
  $request->setFaust($id);
 
  ting_infomedia_add_user_creds($request);
  $ret = $request->parse(ting_execute($request->getRequest()));

  return $ret;
}

/**
 * Infomedia - verify that request of item identify by faust does return an article
 *
 * @param int $id Faust
 * @return TingClientInfomediaResult
 */
function ting_infomedia_check_article($id) {
  $request = ting_get_request_factory()->getInfomediaArticleRequest();
  $request->makeCheck();
  $request->setFaust($id);
  $request = ting_infomedia_add_user_creds($request);
  return TingClientInfomediaArticleRequest::parse(ting_execute($request));
}

/**
 * Infomedia - retrieve reviews for an item identified by faust or ISBN
 *
 * @param int $id
 *   Faust or ISBN
 * @param bool $id_is_isbn
 *   Is $id an ISBN instead of faust
 * @return TingClientInfomediaResult
 */
function ting_infomedia_get_review($id, $id_is_isbn = FALSE) {
  $request = ting_get_request_factory()->getInfomediaReviewRequest();
  $request->makeGet();

  if ($id_is_isbn) {
    $request->setISBN($id);
  }
  else {
    $request->setFaust($id);
  }

  $request = ting_infomedia_add_user_creds($request);
  return TingClientInfomediaReviewRequest::parse(ting_execute($request));
}

function checkUser() {
  return TRUE;
  // TODO implement
}

/**
 * Infomedia - count how many reviews an item identified by faust or ISBN has
 *
 * @param int $id
 *   Faust or ISBN
 * @param bool $id_is_isbn
 *   Is $id an ISBN instead of faust
 * @return TingClientInfomediaResult
 */
function ting_infomedia_check_review($id, $id_is_isbn = FALSE) {
  $request = ting_get_request_factory()->getInfomediaReviewRequest();
  $request->makeCheck();

  if ($id_is_isbn) {
    $request->setISBN($id);
  }
  else {
    $request->setFaust($id);
  }

  $request = ting_infomedia_add_user_creds($request);
  return TingClientInfomediaReviewRequest::parse(ting_execute($request));
}

/**
 * Helper function used by infomedia wrapper functions
 *
 * Adds agency and if user is authorized user credentials to request object and
 * returns the object
 *
 * @param TingClientInfomediaResult $request
 *   Request object to add user credentials to
 * @return TingClientInfomediaRequest
 */
function ting_infomedia_add_user_creds(TingClientInfomediaRequest $request) {
  try {
    $creds = ding_user_get_creds();
    $request->setUser($creds['name']);
    $request->setPin($creds['pass']);
    if ($agency = variable_get('ting_agency', FALSE)) {
      $request->setAgency($agency);
    }
  }
  catch(DingProviderAuthException $e) {//do nothing 
  }

  $name = isset($creds['name']) ? $creds['name'] : '';
  $pass = isset($creds['pass']) ? $creds['pass'] : '';  
 
  // check if user is authenticated
  ding_provider_invoke_page('user', 'authenticate', $name, $pass); 
  return $request;
}

