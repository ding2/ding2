<?php
/**
 * @file
 * Page callback and related functions for the Ting fulltext module.
 */

/**
 * Fulltext page view.
 */
function ting_fulltext_page_view($object) {
  $build = array();

  $doc = new DOMDocument();
  $doc->loadXML($object);

  foreach ($doc->getElementsByTagName('para') as $node) {
    $build[] = array(
      '#markup' => $node->textContent, 
    );
  }

  return $build;
}

