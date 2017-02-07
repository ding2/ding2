<?php
/**
 * @file
 * ting_new_materials.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ting_new_materials_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function ting_new_materials_image_default_styles() {
  $styles = array();

  // Exported image style: ting_new_materials_cover.
  $styles['ting_new_materials_cover'] = array(
    'name' => 'ting_new_materials_cover',
    'label' => 'ting_new_materials_cover',
    'effects' => array(
      1 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 140,
          'height' => 203,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function ting_new_materials_node_info() {
  $items = array(
    'new_materials' => array(
      'name' => t('New Materials'),
      'base' => 'node_content',
      'description' => t('Creates a list of new materials'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
