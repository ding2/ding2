<?php
/**
 * Field API file.
 */


/**
 * Implements hook_field_formatter_info().
 */
function ding_item_viewer_field_formatter_info() {
  $formatters = array();

  $formatters['ting_title_ding_item_viewer'] = array(
    'label' => t('Ding item viewer'),
    'description' => t('Show title (truncates if it is too long)'),
    'field types' => array(
      'ting_title',
    ),
    'settings' => array('link_type' => 'none'),
  );

  $formatters['ting_author_ding_item_viewer'] = array(
    'label' => t('Ding item viewer'),
    'description' => t('Show authors as plain text (without links)'),
    'field types' => array(
      'ting_author',
    ),
  );

  $formatters['ting_subjects_ding_item_viewer'] = array(
    'label' => t('Ding item viewer'),
    'description' => t('Show one subject'),
    'field types' => array(
      'ting_subjects',
    ),
  );

  $formatters['ting_abstract_ding_item_viewer'] = array(
    'label' => t('Ding item viewer'),
    'description' => t('Show trimmed abstract'),
    'settings' => array('trim_length' => 600),
    'field types' => array(
      'ting_abstract',
    ),
  );

  $formatters['ting_cover_ding_item_viewer'] = array(
    'label' => t('Ding item viewer'),
    'description' => t('Cover image without ajax'),
    'field types' => array('ting_cover'),
    'settings' => array('image_style' => 'thumbnail'),
  );

  return $formatters;
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function ding_item_viewer_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $element = array();

  if ($display['type'] == 'ting_title_ding_item_viewer') {
    $element['link_type'] = array(
      '#type' => 'radios',
      '#title' => t('Link title to'),
      '#options' => array(
        'none' => t("Don't link"),
        'object' => t('Object'),
        'collection' => t('Collection, if part of a collection'),
      ),
      '#default_value' => $settings['link_type'],
    );
  }

  if ($display['type'] == 'ting_abstract_ding_item_viewer') {
    $element['trim_length'] = array(
      '#title' => t('Trim length'),
      '#type' => 'textfield',
      '#size' => 10,
      '#default_value' => $settings['trim_length'],
      '#element_validate' => array('element_validate_integer_positive'),
      '#required' => TRUE,
    );
  }

  if ($display['type'] == 'ting_cover_ding_item_viewer') {
    return ting_covers_field_formatter_settings_form(
      $field,
      $instance,
      $view_mode,
      $form,
      $form_state
    );
  }

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function ding_item_viewer_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $summary = '';

  if ($display['type'] == 'ting_title_ding_item_viewer') {
    $summary = t('Link type: @type', array('@type' => $settings['link_type']));
  }

  if ($display['type'] == 'ting_abstract_ding_item_viewer') {
    $summary = t('Trim length') . ': ' . $settings['trim_length'];
  }

  if ($display['type'] == 'ting_cover_ding_item_viewer') {
    return ting_covers_field_formatter_settings_summary(
      $field,
      $instance,
      $view_mode
    );
  }

  return $summary;
}

/**
 * Implements hook_field_formatter_view().
 */
function ding_item_viewer_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();

  foreach ($items as $delta => $item) {
    switch ($display['type']) {
      case 'ting_title_ding_item_viewer':
        $type = 'ting_object';
        $title = $entity->title;
        // Truncate title.
        if (strlen($title) > 50) {
          $title = substr($title, 0, 50) . '...';
        }

        if (!empty($display['settings']['link_type']) && $display['settings']['link_type'] == 'collection') {
          $type = 'ting_collection';
        }

        if (!empty($display['settings']['link_type']) && $display['settings']['link_type'] != 'none') {
          $url = entity_uri($type, $entity);
          $title = l($title, $url['path'], $url['options']);
        }
        else {
          $title = check_plain($title);
        }

        $element[$delta] = array(
          '#prefix' => '<h2>',
          '#suffix' => '</h2>',
          '#markup' => $title,
        );
        break;

        // Use same logic as for default view, but without adding URLs.
      case 'ting_author_ding_item_viewer':
        $creator = NULL;
        if (isset($entity->reply->record['dc:creator'])) {
          if (isset($entity->reply->record['dc:creator']['oss:aut'][0])) {
            $creator = $entity->reply->record['dc:creator']['oss:aut'][0];
          }
          elseif (isset($entity->reply->record['dc:creator']['oss:mus'][0])) {
            $creator = $entity->reply->record['dc:creator']['oss:mus'][0];
          }
          elseif (isset($entity->reply->record['dc:creator']['oss:sort'][0])) {
            $creator = $entity->reply->record['dc:creator']['oss:sort'][0];
          }
        }

        if (!empty($creator) && !empty($entity->date)) {
          $creator .= ' (' . $entity->date . ')';
        }
        $element[$delta] = array('#markup' => $creator);
        break;

      case 'ting_subjects_ding_item_viewer':
        $subject = NULL;
        if (isset($entity->reply->record['dc:subject']['dkdcplus:DK5-Text'][0])) {
          $subject = $entity->reply->record['dc:subject']['dkdcplus:DK5-Text'][0];
        }
        elseif (isset($entity->reply->record['dc:subject']['oss:genre'][0])) {
          $subject = $entity->reply->record['dc:subject']['oss:genre'][0];
        }
        elseif (isset($entity->reply->record['dc:subject'][''][0])) {
          $subject = $entity->reply->record['dc:subject'][''][0];
        }

        if ($subject) {
          $subject = l(
            $subject,
            'search/ting/term.subject="' . $subject . '"',
            array('attributes' => array('class' => array('subject')))
          );
        }

        $element[$delta] = array(
          '#markup' => $subject,
        );
        break;

      case 'ting_abstract_ding_item_viewer':
        $abstract = check_plain($entity->abstract);
        $output = text_summary($abstract, NULL, $display['settings']['trim_length']);
        if ($abstract != $output) {
          $output .= ' ...';
        }
        $element[$delta] = array('#markup' => $output);
        break;

      case 'ting_cover_ding_item_viewer':
        module_load_include('inc', 'ting_covers', 'ting_covers.pages');
        list($owner_id, $local_id) = explode(':', $entity->ding_entity_id);
        $cover_data = array(
          array(
            'image_style' => $display['settings']['image_style'],
            'local_id' => $local_id,
            'owner_id' => $owner_id,
          ),
        );
        $images = ting_covers_objects(FALSE, $cover_data);
        $element[$delta] = array(
          '#theme' => 'image',
          '#path' => $images[0]['url'],
          '#width' => '',
          '#height' => '',
          '#alt' => '',
          '#title' => '',
        );
        break;
    }
  }

  return $element;
}

/**
 * Implements hook_field_load().
 */
function ding_item_viewer_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    $items[$id][0]['safe_value'] = t('More info');
    $items[$id][0]['value'] = t('More info');
  }
}
