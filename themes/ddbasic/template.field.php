<?php

/**
 * Implements template_preprocess_field().
 */
function ddbasic_preprocess_field(&$vars, $hook) {

  // Remove titles from ting_entities
  if($vars['element']['#field_name'] === 'ting_entities') {
    foreach($vars['items'][0] as &$item) {
      unset($item['#prefix']);
    }
  }
 
  // Get current view mode (teaser).
  $view_mode = $vars['element']['#view_mode'];
  $field_name = $vars['element']['#field_name'];

  // Add suggestion for ddbasic specific field.
  $vars['theme_hook_suggestions'][] = 'field__ddbasic';

  // Add suggestion for ddbasic field with specific name.
  $vars['theme_hook_suggestions'][] = 'field__ddbasic_' . $field_name;

  // Add suggestion for ddbasic field in specific view mode.
  $vars['theme_hook_suggestions'][] = 'field__ddbasic_' . $view_mode;

  // Stream line tags in view modes using the same tpl.
  if ($vars['element']['#field_type'] == 'taxonomy_term_reference') {
    $vars['theme_hook_suggestions'][] = 'field__ddbasic_tags__' . $view_mode;
  }

  //
  // Call our own custom preprocess functions.
  $preprocess_function = 'preprocess__field__' . $vars['element']['#field_type'];
  $preprocess_function = 'preprocess__field__' . $vars['element']['#field_name'];
  if (function_exists($preprocess_function)) {
    call_user_func_array($preprocess_function, array(&$vars));
  }


  // Ensure that all OG group ref field are the same.
  if ($field_name == 'ding_event_groups_ref' || $field_name == 'ding_news_groups_ref' || $field_name == 'og_group_ref') {
    $vars['theme_hook_suggestions'][] = 'field__og_group_ref';

    // Add classes to get label correctly formatted.
    foreach ($vars['items'] as $id => $item) {
      $vars['items'][$id]['#options'] = array(
        'attributes' => array(
          'class' => array(
            'label',
            'label_info',
          ),
        ),
      );
    }
  }

  // Clean up fields in search result view mode aka. search result page.
  if ($view_mode == 'search_result') {
    // Add suggestion that only hits the search result page.
    $vars['theme_hook_suggestions'][] = 'field__' . $vars['element']['#field_type'] . '__' . $view_mode;
    // @TODO Cleanup outcommented text
    // @B14 Outcommented by B14
    //
    //switch ($vars['element']['#field_name']) {
    //  case 'ting_author':
    //  case 'ting_abstract':
    //  case 'ting_subjects':
    //    $vars['classes_array'] = array('content');
    //    break;
    //
    //  case 'ting_title':
    //    $vars['classes_array'] = array('heading');
    //    break;
    //}
  }
  

  // Make suggestion for the availability on the search result page.
  if ($vars['element']['#field_type'] == 'ting_collection_types' &&
      $vars['element']['#formatter'] == 'ding_availability_with_labels') {
      $vars['theme_hook_suggestions'][] = 'field__' . $vars['element']['#field_type'] . '__' . 'search_result';
  }

  // Add class to library OG ref on staff profiles only.
  if ($vars['element']['#bundle'] == 'ding_staff_profile') {
    $staff_fields = array(
      'og_group_ref',
      'field_ding_staff_department',
      'field_ding_staff_email',
      'field_ding_staff_phone',
      'field_ding_staff_work_areas',
    );

    if (in_array($field_name, $staff_fields)) {
      $vars['theme_hook_suggestions'][] = 'field__ding_staff__content_field';

      // Ensure that department is not add label info.
      if ($field_name == 'field_ding_staff_department' || $field_name == 'og_group_ref') {
        foreach ($vars['items'] as $id => $item) {
          // This as little hack to make the user interface look better.
          $vars['items'][$id]['#options']['no_label'] = TRUE;
        }
      }
    }

    if ($field_name == 'og_group_ref') {
      $vars['classes_array'][] = 'field-name-ding-library-name';
    }
  }
}

/**
 * @TODO Wrong function name prefix with theme name.
 * Ting abstract
 */
function preprocess__field__ting_abstract(&$vars) {
  switch ($vars['element']['#view_mode']) {
    case 'search_result':
      $text = $vars['items'][0]['#markup'];
      $vars['items'][0]['#markup'] = mb_strimwidth($text, 0, 120, "...");
      break;
    case 'teaser':
      $text = $vars['items'][0]['#markup'];
      $vars['items'][0]['#markup'] = mb_strimwidth($text, 0, 120, "...");
      break;  
  }
}

/**
 * @TODO Wrong function name prefix with theme name.
 * Ting author
 */
function preprocess__field__ting_author(&$vars) {
  
  // In view mode teaser
  // We overwrite the markup so the creator is no longer a link, 
  // using the same method as in ting module
  if ($vars['element']['#view_mode'] == 'teaser') {
  
    $creators = array();
    foreach ($vars['element']['#object']->creators as $i => $creator) {
      $creators[] = $creator;
    }

    $markup_string = '';
        
    if (count($creators)) {
      if ($vars['element']['#object']->date != '') {
        $markup_string = t('By !author_link (@year)', array(
          '!author_link' => implode(', ', $creators),
          '@year' => $vars['element']['#object']->date,
          ));
      }
      else {
        $markup_string = t('By !author_link', array(
          '!author_link' => implode(', ', $creators),
        ));
      }
    }
    elseif ($vars['element']['#object']->date != '') {
      $markup_string = t('(@year)', array('@year' => $vars['element']['#object']->date));
    }
    $vars['items'][0] = array(
      '#markup' => $markup_string,
    );
  }
  
}

/**
 * @TODO Wrong function name prefix with theme name.
 * Ding library list image
 */
function preprocess__field__field_ding_library_list_image(&$vars) {
  // Set image styling class
  $vars['classes_array'][] = 'image-styling-16-9';
}

/**
 * @TODO Wrong function name prefix with theme name.
 * Ding news list image
 */
function preprocess__field__field_ding_news_list_image(&$vars) {
  // Set image styling class
  $vars['classes_array'][] = 'image-styling-16-9';
}

/**
 * @TODO Wrong function name prefix with theme name.
 * Ding news attachments
 */
function preprocess__field__field_ding_news_files(&$vars) {
  // Add filetype to output
  foreach ($vars['items'] as $delta => $item) {
    $file_type = strstr($item['#file']->filemime, '/');
    $file_type = ltrim($file_type, '/');
    
    $vars['items'][$delta]['#suffix'] = '<span class="file-type">(' . $file_type . ')</span>';

  }
}