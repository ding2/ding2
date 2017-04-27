<?php

/**
 * @file
 * Field hook implementations.
 */

/**
 * Implements hook_field_info().
 */
function ding_periodical_field_info() {
  return array(
    'ding_periodical_issues' => array(
      'label' => t('Issue list for periodicals.'),
      'description' => t('Issue list for periodicals.'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ding_periodical_issues_default',
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
function ding_periodical_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    // Only bother with entities that are periodicals. This is cached, but
    // entities are unlikely to change type.
    if ($entity->is('periodical')) {
      $items[$id][0] = array(
        'provider_id' => $entity->localId,
      );
    }
  }
}

/**
 * Implements hook_widget_info_alter().
 */
function ding_periodical_widget_info_alter(&$info) {
  if (isset($info['hidden'])) {
    $info['hidden']['field types'][] = 'ding_periodical_issues';
  }
}

/**
 * Implements hook_field_formatter_info().
 */
function ding_periodical_field_formatter_info() {
  return array(
    'ding_periodical_issues_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ding_periodical_issues',
      ),
    ),
    'ding_periodical_issues_ajax' => array(
      'label' => t('Ajax load'),
      'field types' => array(
        'ding_periodical_issues',
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function ding_periodical_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();

  // Check that the provider provides holdings information.
  if (!ding_provider_implements('availability', 'holdings')) {
    return $element;
  }

  // Switch over the different formatters.
  switch ($display['type']) {
    case 'ding_periodical_issues_ajax':
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#theme' => 'ding_periodical_issues_ajax',
          '#ding_entity_id' => $entity->ding_entity_id,
          '#attached' => array(
            'js' => array(
              array(
                'data' => drupal_get_path('module', 'ding_periodical') . '/js/ding_periodical_ajax.js',
              ),
              array(
                'data' => array(
                  'ding_periodical' => array(
                    'id' => drupal_html_class($entity->ding_entity_id),
                    'ding_entity_id' => $entity->ding_entity_id,
                  ),
                ),
                'type' => 'setting',
              ),
            ),
          ),
        );
      }
      break;

    default:
      // Handles the default formatter.
      foreach ($items as $delta => $item) {
        $availability = ding_provider_invoke('availability', 'holdings', array($entity->provider_id));
        if (isset($availability[$entity->provider_id])) {
          $issues = $availability[$entity->provider_id]['issues'];
          krsort($issues);

          if ($issues) {
            $element[$delta] = array(
              '#theme' => 'ding_periodical_issues',
              '#entity' => $entity,
              '#issues' => $issues,
              '#availability' => $availability,
            );
          }
        }
      }
      break;
  }

  // Add script to collapsed the issue list, if any elements found.
  if (!empty($element)) {
    $element['#attached']['js'] = array(
      array(
        'data' => drupal_get_path('module', 'ding_periodical') . '/js/ding_periodical.js',
      ),
    );
  }

  return $element;
}
