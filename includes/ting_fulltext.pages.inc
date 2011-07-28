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
}

