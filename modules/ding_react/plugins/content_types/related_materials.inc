<?php

/**
 * @file
 * Add the checklist app content type.
 */

use Ting\TingObjectInterface;

$plugin = [
  'title' => t('Related materials app'),
  'single' => TRUE,
  'description' => t('Display related materials for an object.'),
  'category' => t('DDB React'),
  'required context' => [
    new ctools_context_optional(t('Ting object'), 'ting_object'),
    new ctools_context_optional(t('Ting collection'), 'ting_collection'),
  ],
];

/**
 * Return pane content.
 */
function ding_react_related_materials_content_type_render($subtype, $conf, $panel_args, $contexts) {
  $block = new stdClass();

  // We support multiple contexts which can result in a Ting object.
  // Find the ones available and extract an object accordingly.
  $contexts_with_data = array_filter($contexts,
    function (ctools_context $context) {
      return !empty($context->data);
    }
  );
  $ting_objects = array_map(function (ctools_context $context) {
    $data = $context->data;
    if ($data instanceof TingCollection) {
      return $data->getPrimary_object()->getTingObject();
    }
    elseif ($data instanceof TingEntity) {
      return $data->getTingObject();
    }
  }, $contexts_with_data);
  // Contexts are in prioritized order so get the first which yielded an object.
  $object = array_shift($ting_objects);

  // Only show related materials if the object has subjects. If not then there
  // is not enough data to display meaningful results.
  if ($object instanceof TingObjectInterface && !empty($object->getSubjects())) {
    // Support setting allowed sources through a variable in case our hard-coded
    // list is not sufficient. NB: There is currently no admin UI for setting
    // this.
    $sources = variable_get('ding_react_related_materials_sources', implode(',', [
      // These are sources containing well-known materials which are also
      // likely to have cover images. This makes the list more appealing.
      'bibliotekskatalog',
      'ereolen',
      'ereolen global',
      'comics plus',
      'ebook central',
      'rbdigital magazines',
    ]));
    $sources = explode(',', $sources);

    $data = [
      'subjects' => ding_react_related_materials_format_strings($object->getSubjects()),
      'categories' => ding_react_related_materials_format_strings($object->getAudience()),
      'sources' => ding_react_related_materials_format_strings($sources),
      'exclude-title' => ding_react_related_materials_format_string($object->getTitle()),
      // We cannot use url() here as it will encode the colon in the placeholder.
      'search-url' => '/search/ting/:query?sort=:sort',
      'material-url' => '/ting/object/:pid',
      'cover-service-url' => ding_react_cover_service_url(),
      'title-text' => t('Related materials'),
      'search-text' => t('Show search result for related materials'),
    ];
    $block->content = ding_react_app('related-materials', $data);
  }

  return $block;
}

/**
 * Format a set of string values to a format suitable for React app data.
 *
 * @param string[] $strings
 *   The string values.
 *
 * @return string
 *   A single formatted string containing all the values.
 */
function ding_react_related_materials_format_strings(array $strings) {
  $formatted_strings = array_map('ding_react_related_materials_format_string', $strings);
  return implode(",", $formatted_strings);
}

/**
 * Format a single string to a format suitable for React app data.
 *
 * @param string $string
 *   The string value.
 *
 * @return string
 *   The formatted string value.
 */
function ding_react_related_materials_format_string($string) {
  // Remove , from strings. React components can handle , even though it is also
  // used as a separator by replacing with \, but OpenPlatform does not seem to
  // support , in values at the moment. It fails with the error "q is not of a
  // type(s) string" if we include , so instead we just remove it.
  // We will probably not get a match on this exact string but that is
  // preferable to failing with 0 results.
  return str_replace(',', '', $string);
}
