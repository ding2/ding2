<?php
/**
 * @file
 * Theming functions for ting.
 */

/**
 * Template preprocessor for ting objects.
 */
function template_preprocess_ting_object(&$variables) {
  $variables['object'] = $variables['elements']['#object'];

  $variables['page'] = $variables['elements']['#view_mode'] == 'full';
  $variables['classes_array'][] = drupal_html_class('view-mode-' . $variables['elements']['#view_mode']);
  $variables['attributes_array']['ting-object-id'] = $variables['object']->id;
  // Helpful $content variable for templates.
  foreach (element_children($variables['elements']) as $key) {
    $variables['content'][$key] = $variables['elements'][$key];
  }

  if (isset($variables['content']['entities'])) {
    foreach ($variables['content']['entities'] as $key => $val) {
      $variables['content']['overview']['types'][] = $key;
    }
  }

  // Modify 'alt' attribute for list items.
  if (!empty($variables['content']['ting_cover']) && !empty($variables['content']['group_collection_list'])) {
    // Find a object we can pull the data from and add alt-data.
    $data_object = NULL;
    if ($variables['object'] instanceof TingEntity) {
      $data_object = $variables['object'];
    }
    if ($variables['object'] instanceof TingCollection) {
      $data_object = $variables['object']->getPrimary_object();
    }

    if (NULL !== $data_object) {
      $variables['content']['ting_cover'][0]['#alt'] = implode(' ', [
        $data_object->getTitle(),
        $data_object->getType(),
        $data_object->getDate(),
      ]
      );
    }
  }
}
