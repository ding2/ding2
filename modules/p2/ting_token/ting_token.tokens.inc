<?php

/**
 * @file
 * Main tokens
 */

/**
 * Implements hook_token_info().
 */
function ting_token_token_info() {
  $type = array(
    'name' => t('Ding enity'),
    'description' => t('Display a ding entity.'),
  );

  // Core tokens for nodes.
  $consent['ting'] = array(
    'name' => t("Ding entity"),
    'description' => t("Show a ding entity."),
  );

  return array(
    'types' => array('ting' => $type),
    'tokens' => array('ting' => $consent),
  );
}

/**
 * Implements hook_tokens().
 */
function ting_token_tokens($type, $tokens, $data = array(), $options = array()) {
  $url_options = array('absolute' => TRUE);
  
  $replacements = array();
  if ($type == 'ting') {
    foreach ($tokens as $name => $original) {
      $args = explode(':', $name);
      $view_mode = array_shift($args);
      $eid = implode(':', $args);
      if (strpos($eid, ',') !== FALSE) {
        $eids = explode(',', rawurldecode($eid));
      }
      else {
        $eids = array(rawurldecode($eid));
      }

      foreach ($eids as & $eid) {
        $eid = ding_list_convert_cql($eid);
      }

      $entities = ding_entity_load_multiple($eids);
      $output = '<div class="ding-inline-list">';
      foreach ($entities as $id => $entity) {
        $object = ding_entity_view($entity, $view_mode);
        if ($view_mode == 'list_item') {
          $object['#attributes']['class'][] = format_string('compact');
        }
        $output .= drupal_render($object);
      }
      $output .= '</div>';
      $replacements[$original] = $output;
    }
  }

  return $replacements;
}
