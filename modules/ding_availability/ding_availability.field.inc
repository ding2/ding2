<?php

/**
 * @file
 * Field hook implementations.
 */

/**
 * Implements hook_field_info().
 */
function ding_availability_field_info() {
  return array(
    'ding_availability_item' => array(
      'label' => t('Availability information.'),
      'description' => t('Availability information.'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ding_availability_default',
      'virtual_field' => array(
        'entity_types' => array('ting_object'),
        'add_widget' => TRUE,
      ),
    ),
    'ding_availability_holdings' => array(
      'label' => t('Holdings information.'),
      'description' => t('Holdings information.'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ding_availability_default',
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
function ding_availability_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    $items[$id][0] = array(
      'provider_id' => $entity->localId,
    );
  }
}

/**
 * Implements hook_widget_info_alter().
 */
function ding_availability_widget_info_alter(&$info) {
  if (isset($info['hidden'])) {
    $info['hidden']['field types'][] = 'ding_availability_item';
    $info['hidden']['field types'][] = 'ding_availability_holdings';
  }
}

/**
 * Implements hook_field_formatter_info().
 */
function ding_availability_field_formatter_info() {
  return array(
    'ding_availability_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ding_availability_item',
        'ding_availability_holdings',
      ),
    ),
    'ding_availability_type' => array(
      'label' => t('With availability information'),
      'field types' => array(
        'ting_type',
      ),
    ),
    'ding_availability_with_labels' => array(
      'label' => t('Availability information with labels'),
      'field types' => array(
        'ting_collection_types',
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function ding_availability_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $online_types = array_filter(variable_get('ting_online_types', _ting_default_online_types()));
  $reservable_sources = array_filter(variable_get('ting_reservable_sources', _ting_default_reservable_sources()));

  // Attach front-end style and JS to the element.
  foreach ($items as $delta => $item) {
    $attached = array(
      'css' => array(
        drupal_get_path('module', 'ding_availability') . '/css/ding_availability.css',
      ),
    );

    // Extract records' source.
    if ($field['type'] != 'ting_collection_types') {
      $ac_source = $entity->reply->record['ac:source'][''][0];
    }

    switch ($display['type']) {
      case 'ding_availability_default':
        // Generate an unique id.
        $id = drupal_html_id('holdings-' . $entity->id);

        // Add javascript.
        $attached['js'] = array(
          drupal_get_path('module', 'ding_availability') . '/js/ding_availability.js',
        );

        // If item is of type 'library materials' (where we can lookup holding
        // data), prepare to check holding on the item.
        $holding_types = variable_get('ding_availability_holdings_types', _ding_availability_holdings_default_types());
        if (in_array(drupal_strtolower($ac_source), $reservable_sources) && in_array(drupal_strtolower($entity->type), $holding_types)) {
          $attached['js'][] = array(
            'data' => array(
              'ding_availability_mode' => 'holdings',
              'ding_availability' => array(
                $id => array($entity->localId),
              ),
            ),
            'type' => 'setting',
          );

          $element[$delta] = array(
            // @todo: move this into tpl file.
            '#markup' => '<div id="' . $id . '" class="holdings holdings-' . $entity->localId . '"><div class="loader"><i class="icon icon-spinner icon-spin"></i><p class="loader-text">' . t('Fetching holdings information.') . '<p></div></div>',
            '#attached' => $attached,
          );
        }

        break;

      case 'ding_availability_item':
        // Add javascript.
        $attached['js'] = array(
          drupal_get_path('module', 'ding_availability') . '/js/ding_availability.js',
        );

        $element[$delta] = array(
          '#markup' => '<div class="availability availability-' . $item['provider_id'] . '"></div>',
          '#attached' => $attached,
        );
        break;

      case 'ding_availability_type':
        // Generate an unique id.
        $id = drupal_html_id('availability-' . $entity->id);

        // Mark as available if it is an online resource,
        $available_online = (in_array(drupal_strtolower($entity->type), $online_types)) ? 'available' : 'not-available-online';

        // Add javascript.
        $attached['js'] = array(
          drupal_get_path('module', 'ding_availability') . '/js/ding_availability.js',
        );

        // If item is of type 'library materials' (where we can lookup holding
        // data), prepare to check holding on the item.
        if (in_array(strtolower($ac_source), $reservable_sources)) {
          $attached['js'][1] = array(
            'data' => array(
              'ding_availability' => array(
                $id => array($entity->localId),
              ),
            ),
            'type' => 'setting',
          );
        }

        $element[$delta] = array(
          '#theme' => 'item_list',
          '#attached' => $attached,
          '#items' => array(
            array(
              'data' => $entity->type,
              'id' => $id,
              'class' => array(
                'availability',
                drupal_html_class($entity->type),
                $available_online,
                'pending',
              ),
            ),
          ),
        );
        break;

      case 'ding_availability_with_labels':
        $id_mapping = array();
        $typed_entities = array();

        // Sort entities into type -> ids.
        foreach ($entity->entities as $ent) {
          $typed_entities[$ent->type][] = $ent;
        }

        // Build basic output render array.
        $output = array(
          '#theme' => 'ding_availability_types',
          '#types' => array(),
          '#attached' => $attached,
        );

        // Loop over the different material types.
        foreach ($typed_entities as $type => $entities) {
          // Generate an unique id.
          $id = drupal_html_id('availability-' . $entities[0]->id . '-' . $type);

          // Extract records' source.
          $ac_source = $entities[0]->reply->record['ac:source'][''][0];

          // Get link to first element in the collection of the current type.
          // If more than one exists link to the collection.
          if (count($entities) == 1) {
            $url = entity_uri('ting_object', $entities[0]);
          }
          else {
            $url = entity_uri('ting_collection', $entities[0]);
          }

          // Mark as available if it is an online resource.
          if (in_array(drupal_strtolower($type), $online_types) || $entities[0]->getOnline_url(FALSE)) {
            if (!isset($output['#types']['online'])) {
              // Add label "online" to output.
              $output['#types']['online'] = array(
                '#theme' => 'ding_availability_type',
                '#class' => 'js-online',
                '#label' => t('Online'),
                '#links' => array(),
              );
            }
            // Add it to the online label.
            $output['#types']['online']['#links'][] = array(
              'status' => 'available',
              'type' => $type,
              'link' => array(
                // The online url can't be used with l(), has it will encode
                // it.
                '#markup' => '<a id="' . $id . '" class="search-result--availability-link availability available" href="/' . $url['path'] . '">' . check_plain($type) . '</a>',
              ),
            );
          }
          else {
            if (!isset($output['#types']['pending'])) {
              // Add label "Pending" to output as in waiting for information.
              $output['#types']['pending'] = array(
                '#theme' => 'ding_availability_type',
                '#class' => 'js-pending',
                '#label' => t('Pending availability'),
                '#links' => array(),
              );
            }
            $output['#types']['pending']['#links'][] = array(
              'status' => 'pending',
              'type' => $type,
              'link' => array(
                '#theme' => 'link',
                '#text' => check_plain($type),
                '#path' => $url['path'],
                '#options' => array(
                  'attributes' => array(
                    'class' => array(
                      'search-result--availability-link',
                      'availability',
                      'pending',
                    ),
                    'id' => $id,
                  ),
                  'html' => FALSE,
                ),
              ),
            );
          }

          // If item is of type 'library materials' (where we can lookup
          // availability data), map the HTML id to the list of entity ids.
          // This is for the current material type group (book, cd, etc.).
          if (in_array(drupal_strtolower($ac_source), $reservable_sources) && !in_array(drupal_strtolower($type), $online_types)) {
            $id_mapping[$id] = array();
            foreach ($entities as $object_entity) {
              $id_mapping[$id][] = $object_entity->localId;
            }
          }
        }

        // Prepare to check holding on the item.
        // It's important that this is attached even if empty, else javascript
        // will fail because it gets an empty object.
        $output['#attached']['js'][] = array(
          'data' => array(
            'ding_availability' => $id_mapping,
          ), 'type' => 'setting',
        );
        $output['#attached']['js'][] = drupal_get_path('module', 'ding_availability') . '/js/ding_availability_labels.js';

        $element[$delta] = $output;
        break;
    }
  }

  return $element;
}
