<?php
/**
 * @file
 * Theming functions for ting.
 */

use Ting\TingObjectInterface;

/**
 * Template preprocessor for ting objects.
 */
function template_preprocess_ting_object(&$variables) {
  $variables['object'] = $variables['elements']['#object'];

  $variables['page'] = $variables['elements']['#view_mode'] == 'full';
  $variables['classes_array'][] = drupal_html_class('view-mode-' . $variables['elements']['#view_mode']);
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

/**
 * Template preprocessor for ting titles.
 *
 * @param array $variables Template variables.
 */
function template_preprocess_ting_title(&$variables) {
  /** @var \Ting\TingObjectCollectionInterface $collection */
  $collection = $variables['collection'];
  /** @var array $uri */
  $uri = $variables['uri'];

  $object = $collection->getPrimaryObject();
  $type = $object->getType();
  $types = array_unique(array_map(function(TingObjectInterface $object) {
    return $object->getType();
  }, $collection->getObjects()));

  $title = $object->getTitle();
  $titles = array_unique(array_map(function(TingObjectInterface $object) {
    return $object->getTitle();
  }, $collection->getObjects()));

  // Use the generic collection title if:
  // - A collection has items with different types
  // - A collection has items of the same type but with different titles
  // Note that this intentionally disregards collections with multiple objects
  // with the same type and title.
  if (count($types) > 1 || count($titles) > 1) {
    $type = t('Material collection');
  }

  if (!empty($uri)) {
    $title = l($title, $uri['path'], $uri['options']);
  } else {
    $title = check_plain($title);
  }

  // Append the language as a suffix to the title for certain material
  // types if the material language is not the default language.
  $title_suffix_types = variable_get('ting_language_type_title_suffix', []);
  $default_language = variable_get('ting_language_default');
  $is_title_suffix_type = (!empty($title_suffix_types[strtolower($object->getType())]));
  $language = $object->getLanguage();
  $has_language = !empty($language);
  $is_default_language = $language == $default_language;

  $show_language = $is_title_suffix_type && $has_language && !$is_default_language;

  $variables += [
    'title' => $title,
    'type' => $type,
    'show_language' => $show_language,
    'language' => $language,
  ];
}
