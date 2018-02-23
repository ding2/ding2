<?php

/**
 * @file
 * Field hook implementations.
 */

/**
 * Implements hook_field_info().
 */
function ding_list_field_info() {
  return array(
    'ding_list_in_public_lists' => array(
      'label' => t('Material in public lists'),
      'description' => t('The public lists the material is in.'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ding_list_in_public_lists_default',
      'virtual_field' => array(
        'entity_types' => array('ting_object'),
        'add_widget' => TRUE,
      ),
    ),
  );
}

/**
 * Implements hook_field_load().
 */
function ding_list_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    $items[$id][0] = array(
      'id' => $entity->id,
    );
  }
}

/**
 * Implements hook_field_formatter_info().
 */
function ding_list_field_formatter_info() {
  return array(
    'ding_list_in_public_lists_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ding_list_in_public_lists',
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function ding_list_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();

  foreach ($items as $delta => $item) {
    switch ($display['type']) {
      case 'ding_list_in_public_lists_default':
        $element[$delta] = array(
          '#theme' => 'links',
          '#links' => array(),
        );

        foreach (ding_list_material_in_public_lists($item['id']) as $list) {
          $title = check_plain(entity_label('ding_type', $list));

          $username = ding_list_list_username($list);
          if ($username) {
            $title = t('@list_title, By @list_author', array(
              '@list_title' => $title,
              '@list_author' => $username,
            ));
          }

          $element[$delta]['#links'][] = array(
            'title' => $title,
            'href' => 'list/' . $list->id,
          );
        }
        break;
    }
  }

  return $element;
}

/**
 * Implements hook_widget_info_alter().
 */
function ding_list_widget_info_alter(&$info) {
  if (isset($info['hidden'])) {
    $info['hidden']['field types'][] = 'ding_list_in_public_lists';
  }
}
