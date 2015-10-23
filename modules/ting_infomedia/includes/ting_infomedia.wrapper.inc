<?php
/**
 * @file
 * Field wrapper for infomedia.
 */

module_load_include('client.inc', 'ting');

/**
 * Retrieve Infomedia article identified by faust number.
 *
 * @param int $id
 *   Faust number for the article.
 *
 * @return mixed
 *   The result as TingClientInfomediaResult object or FALSE on error.
 */
function ting_infomedia_get_article($id) {
  try {
    $factory = ting_get_request_factory();
  }
  catch(TingClientException $exception) {
    watchdog_exception('infomedia', $exception);

    return FALSE;
  }

  $request = $factory->getInfomediaArticleRequest();
  $request->makeGet();
  $request->setFaust($id);

  ting_infomedia_add_user_creds($request);
  $ret = $request->parse(ting_execute($request->getRequest()));

  return $ret;
}

/**
 * Verify that request of item identify by faust does return an article.
 *
 * @param int $id
 *   Faust number for the article.
 *
 * @return TingClientInfomediaResult
 *   TingClientInfomediaResult for the article.
 */
function ting_infomedia_check_article($id) {
  $request = ting_get_request_factory()->getInfomediaArticleRequest();
  $request->makeCheck();
  $request->setFaust($id);
  $request = ting_infomedia_add_user_creds($request);

  return $request->parse(ting_execute($request));
}

/**
 * Retrieve reviews for an item identified by faust or ISBN.
 *
 * @param int $id
 *   Faust or ISBN
 * @param bool $id_is_isbn
 *   Is $id an ISBN instead of faust
 *
 * @return TingClientInfomediaResult
 *   TingClientInfomediaResult for the article.
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

  return $request->parse(ting_execute($request));
}

/**
 * Count how many reviews an item identified by faust or ISBN has.
 *
 * @param int $id
 *   Faust or ISBN
 * @param bool $id_is_isbn
 *   Is $id an ISBN instead of faust
 *
 * @return TingClientInfomediaResult
 *   TingClientInfomediaResult for the article.
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
  return $request->parse(ting_execute($request));
}

/**
 * Helper function used by infomedia wrapper functions
 *
 * Adds agency and if user is authorized user credentials to request object and
 * returns the object
 *
 * @param TingClientInfomediaRequest $request
 *   Request object to add user credentials to.
 *
 * @return TingClientInfomediaRequest
 *   TingClientInfomediaRequest for the article.
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
  catch(DingProviderAuthException $e) {
    //do nothing
  }

  $name = isset($creds['name']) ? $creds['name'] : '';
  $pass = isset($creds['pass']) ? $creds['pass'] : '';

  // check if user is authenticated
  ding_provider_invoke_page('user', 'authenticate', $name, $pass);
  return $request;
}

