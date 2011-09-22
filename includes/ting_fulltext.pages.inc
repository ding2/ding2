<?php
/**
 * @file
 * Page callback and related functions for the Ting fulltext module.
 */

/**
 * Fulltext page view.
 */
function ting_fulltext_page_view($object) {
  // echo $object;
  $build['ting_fulltext'] = array(
    '#theme' => 'ting_fulltext',  
    '#fields' => ting_fulltext_parse($object),
    '#attached' => 
	    array('css' => array(drupal_get_path('module', 'ting_fulltext') . '/ting_fulltext.css'),),
  );
  //  print_r($build);
  return $build;
}


/**
 * Parse given xml. Return an array holding selected values
 */
function ting_fulltext_parse($xml) {
  static $xpath;
  $ret = array();
  if( !isset($xpath) )
    $xpath = ting_fulltext_get_xpath($xml);

  //main title
  $query = '//docbook:article/docbook:title';
  $nodelist = $xpath->query($query);
  if( $nodelist->length > 0 )
    (isset($nodelist->item(0)->nodeValue) ? $ret['title'] = $nodelist->item(0)->nodeValue : $ret['title'] = '');
  
  //firstname
  $query = '//docbook:firstname';
  $nodelist = $xpath->query($query);
  if( $nodelist->length > 0 )
   (isset($nodelist->item(0)->nodeValue) ? $ret['firstname'] = $nodelist->item(0)->nodeValue : $ret['firstname'] = '');

  //surname
  $query = '//docbook:surname';
  $nodelist = $xpath->query($query);
  if( $nodelist->length > 0 )
    (isset($nodelist->item(0)->nodeValue) ? $ret['surname'] = $nodelist->item(0)->nodeValue : $ret['surname'] = '');
  
  //section (there can be more than one section, but i haven't seen more than one yet); note title is not always set
  $query = '//docbook:section';
  $nodelist = $xpath->query($query);
  if( $nodelist->length > 0 ) {
    foreach($nodelist as $node) {
      $sections[] = 
	array('title' => (isset($node->getElementsByTagname('title')->item(0)->nodeValue)) ? $node->getElementsByTagname('title')->item(0)->nodeValue : '',
	      'para' => $node->getElementsByTagname('para')->item(0)->nodeValue);	      
    }
    $ret['section'] = $sections;
  }

  // subjects; there can be more than one subject - haven't found any yet 
  //<docbook:subjectset><docbook:subject><docbook:subjectitem>
  $query = '//docbook:subjectitem';
  $nodelist = $xpath->query($query);
  if( $nodelist->length > 0 ) {
    foreach($nodelist as $node) {
      $ret['subject'][] = $node->nodeValue;
    }
  }
  
  //  print_r($ret);
  return $ret;
}

function ting_fulltext_get_xpath($xml) {
  // TODO errorhandling
  $dom = new DOMDocument();
  $dom->loadXML($xml);
  $xpath = new DOMXPath($dom);
  $xpath->registerNamespace('docbook','http://docbook.org/ns/docbook');
  return $xpath;
 
}

