<?php
/**
 * @file
 * tabroll.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_tabroll_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ding_tabroll_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ding_tabroll_image_default_styles() {
  $styles = array();

  // Exported image style: ding_tabroll.
  $styles['ding_tabroll'] = array(
    'name' => 'ding_tabroll',
    'effects' => array(
      13 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '460',
          'height' => '240',
        ),
        'weight' => '1',
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function ding_tabroll_node_info() {
  $items = array(
    'ding_tabroll' => array(
      'name' => t('Tabroll'),
      'base' => 'node_content',
      'description' => t('ding_tabroll'),
      'has_title' => '1',
      'custom' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
