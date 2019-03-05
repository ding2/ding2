<?php
/**
 * @file
 * Provides a category browser for the E-resource overview page.
 */

$plugin = array(
  'title' => t('Ding e-resource alfabetical index'),
  'description' => t('Provides alfabetical index links to e-resource titles.'),
  'single' => TRUE,
  'render callback' => 'ding_eresource_ding_eresource_index_content_type_render',
  'category' => t('Ding!'),
);

/**
 * Return the pane contents.
 */
function ding_eresource_ding_eresource_index_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $selected_letter = FALSE;
  $links = array();
  $options = array('attributes' => array('class' => array('active')));
  $base_path = 'e-materialer/all';
  
  // Select library nids and titles.
  $results = db_query("SELECT DISTINCT
    SUBSTR( n.title, 1, 1 ) AS first_letter
    FROM node n
    WHERE n.type = 'ding_eresource'
    AND n.status = 1
    ORDER BY n.title;");
  
  // Create links for each initial letter in the list of E-resource titles.
  foreach ($results as $row) {
    $options = array();
    if ($selected_letter && $selected_letter == $row->first_letter) {
      $options = array('attributes' => array('class' => array('active')));
    }
    $links[] = l($row->first_letter, $base_path . '/' . $row->first_letter, $options);
  }

  $block->content = array(
    '#theme' => 'item_list',
    '#items' => $links,
    '#attributes' => array(
      'class' => array('eresource-index clearfix'),
    ),
  );
  
  return $block;
}

/**
 * Returns an edit form for the content type.
 *
 * We're not actually doing anything here, but we need to have this hook
 * for this content type to work.
 */
function ding_eresource_ding_eresource_index_content_type_edit_form($form, &$form_state) {
  return $form;
}