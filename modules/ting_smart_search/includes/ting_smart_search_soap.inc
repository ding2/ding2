<?php

/**
 * Admin page menu callback.
 *
 * @return array
 *   Admin form.
 */
function ting_smart_search_soap_page() {
  $output = '';

  // Configuration
  $wsdl_path = 'http://report2.webtrekk.de/SOAPv3.wsdl';
  $method = 'getReportData';
  $parameter = array (
  'customerId' => variable_get('ting_smart_search_webtrekk_customerid', '111111111111111'),
  'login' => variable_get('ting_smart_search_webtrekk_customerlogin', 'mylogin'),
  'pass' => variable_get('ting_smart_search_webtrekk_customerpassword', 'mypass'),
  'report_name' => 'smartsearch',
  'is_java' => 1,
  );

  // Create nusoap Client instance and check for errors
  $client = new SOAPClient($wsdl_path); // possibly new nusoap_client(…)
  //$err = $client->getError();
  /*
    if ($err) {
      drupal_set_message('<h2>Error while creating SOAP-instance</h2><pre>' . $err . '</pre>');
    exit(1);
    }
  */
  // Retrieve data and check for errors
  $result = $client->__call($method, array ($parameter));
  if ($client->fault) {
    drupal_set_message('<h2>Server reports errors</h2>');
    drupal_set_message($result);
  exit(1);
  }
  $err = $client->getError();
  if ($err) {
    drupal_set_message('<h2>Error while retrieving data</h2><pre>' . $err . '</pre>');
  exit(1);
  }
  // Hand out results
  $output .= '<h2>'.t('Result').'</h2><pre>';
  $output .= $result;
  $output .= '</pre>';

  return $output;
}
