<?php
/**
 * @file
 * Page callback and related functions for the Ting fulltext module.
 */

/**
 * Fulltext page view.
 */
/*function ting_fulltext_page_view($object) {
  $build = array();
  
  //var_dump($object);
  
  // Load XSL stylesheet and prepare it for using it for transformation.
  $xsl = new DOMDocument();
  $xsl->load(dirname(__FILE__) . '/docbook_transform.xsl', LIBXML_NOCDATA);
  $xslt = new XSLTProcessor();
  $xslt->importStylesheet($xsl);

  // Render the document via XSLT transformation.
  $doc = new DOMDocument();
  $doc->loadXML($object);

  $build['fulltext'] = array(
    '#markup' => $xslt->transformToXML($doc),
  );

  return $build;
  }*/


function ting_fulltext_page_view($object) {
  // echo $object;
  $build['ting_fulltext'] = array(
    '#theme' => 'ting_fulltext',  
    '#fields' => ting_fulltext_parse($object),
  );
  return $build;
}

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
  
  //section (there can be more than one section, but i haven't seen more than one yet)
  $query = '//docbook:section';
  $nodelist = $xpath->query($query);
  if( $nodelist->length > 0 ) {
    foreach($nodelist as $node) {
      $sections[] = 
	array('title' => $node->getElementsByTagname('title')->item(0)->nodeValue,
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

