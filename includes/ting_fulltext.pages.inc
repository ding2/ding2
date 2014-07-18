<?php
/**
 * @file
 * Page callback and related functions for the Ting fulltext module.
 */

/**
 * Fulltext page view.
 */
function ting_fulltext_page_view($xml) {
  return array(
    'ting_fulltext' => array(
      '#theme' => 'ting_fulltext',
      '#fields' => ting_fulltext_parse($xml),
    ),
  );
}

/**
 * Parse given xml. Return an array holding selected values.
 */
function ting_fulltext_parse($xml) {
  // Use static cache as it may be called more than once by the panels
  // plugin.
  $xpath = &drupal_static(__FUNCTION__);
  $ret = array();
  if (!isset($xpath)) {
    $xpath = ting_fulltext_get_xpath($xml);
  }

  // Main title.
  $query = '//docbook:article/docbook:title';
  $nodelist = $xpath->query($query);
  if ($nodelist->length > 0) {
    (isset($nodelist->item(0)->nodeValue) ? $ret['title'] = $nodelist->item(0)->nodeValue : $ret['title'] = '');
  }

  // First name.
  $query = '//docbook:firstname';
  $nodelist = $xpath->query($query);
  if ($nodelist->length > 0) {
    (isset($nodelist->item(0)->nodeValue) ? $ret['firstname'] = $nodelist->item(0)->nodeValue : $ret['firstname'] = '');
  }

  // Surname.
  $query = '//docbook:surname';
  $nodelist = $xpath->query($query);
  if ($nodelist->length > 0) {
    (isset($nodelist->item(0)->nodeValue) ? $ret['surname'] = $nodelist->item(0)->nodeValue : $ret['surname'] = '');
  }

  // Section (there can be more than one section) and furthermore there can be
  // one or more sections in a section..
  $query = '//docbook:section';
  $nodelist = $xpath->query($query);
  if ($nodelist->length > 0) {
    foreach ($nodelist as $node) {
      $sections[] = ting_fulltext_get_section($node);
    }
    $ret['section'] = $sections;
    $ret['section_count'] = count($sections);
  }

  // <docbook:subjectset><docbook:subject><docbook:subjectitem>
  $query = '//docbook:subjectitem';
  $nodelist = $xpath->query($query);
  if ($nodelist->length > 0) {
    foreach ($nodelist as $node) {
      $ret['subject'][] = $node->nodeValue;
    }
  }

  return $ret;
}


/**
 * Not sure whether this is a complete parse of section - there might be more
 * cases.
 *
 * @todo: make this parse complete
 */
function ting_fulltext_get_section($node) {
  $ret = array();

  foreach ($node->childNodes as $child) {
    switch ($child->nodeName) {
      case 'docbook:title':
        $ret['title'] = $child->nodeValue;
        break;

      case 'docbook:para':
        // There might be more than one para in each section.
        $ret['para'][] = $child->nodeValue;
        break;

      case 'docbook:info':
        $ret['title'] = $child->getElementsByTagName('title')->item(0)->nodeValue;
        break;

      case 'docbook:section':
        // Recursive.
        ting_fulltext_get_section($child);
        break;

      case 'docbook:qandaset':
        $ret['title'] = $child->nodeValue;
        break;
    }
  }

  return $ret;
}

function ting_fulltext_get_xpath($xml) {
  // @todo: error handling.
  $dom = new DOMDocument();
  $dom->loadXML($xml);
  $xpath = new DOMXPath($dom);
  $xpath->registerNamespace('docbook', 'http://docbook.org/ns/docbook');
  return $xpath;
}
