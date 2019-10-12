<?php

/**
 * @file
 * Token callbacks for the ting module.
 */

/**
 * Implements hook_token_info()
 */
function ting_token_info() {
  // Note: Token module provides additional tokens on ting_object from instances
  // of our custom field types via the Field API, but these use formatters. The
  // tokens provided here return unformatted data well values directly from
  // the loaded the TingEntity object and could therefore be useful as an
  // alterantive to the field tokens.
  // By providing a type with the name of an entity here, token module will pick
  // it up and provide a URL token for the entity via the API.
  // See: token_token_info_alter().
  $info['types']['ting_object'] = [
    'name' => t('Ting object'),
    'description' => t('Tokens related to Ting object entities (data well materials)'),
    'needs-data' => 'ting_object',
  ];
  // All field type names are prefixed with "ting_" which will be used for the
  // field tokens. We can therefore safely provide convenient tokens without
  // that prefix and avoid collisions.
  $info['tokens']['ting_object']['title'] = [
    'name' => t('Title'),
    'description' => t('The title of the material'),
  ];
  $info['tokens']['ting_object']['creators'] = [
    'name' => t('Author'),
    'description' => t('The creators of the material (comma separated)'),
  ];
  $info['tokens']['ting_object']['creators_inverted'] = [
    'name' => t('Author inverted'),
    'description' => t('The creators of the material inverted (comma separated)'),
  ];
  $info['tokens']['ting_object']['contributers'] = [
    'name' => t('Contributers'),
    'description' => t('Contributers to the material (comma separated)'),
  ];
  $info['tokens']['ting_object']['creators_contributers'] = [
    'name' => t('Contributers and Contributers'),
    'description' => t('Creators of and contributers to the material combined (comma separated)'),
  ];
  $info['tokens']['ting_object']['abstract'] = [
    'name' => t('Abstract'),
    'description' => t('A short resume of the material'),
  ];

  return $info;
}

/**
 * Implements hook_tokens().
 */
function ting_tokens($type, $tokens, array $data, array $options) {
  $sanitize = !empty($options['sanitize']);
  $replacements = [];

  // Ting object tokens.
  if ($type == 'ting_object' && !empty($data['ting_object'])) {
    $ting_object = $data['ting_object'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'title':
          $replacements[$original] = $ting_object->getTitle();
          break;
        case 'creators':
          $replacements[$original] = implode(', ', $ting_object->getCreators());
          break;
        case 'creators_inverted':
          $replacements[$original] = implode(', ', $ting_object->getInvertedCreators());
          break;
        case 'contributers':
          $replacements[$original] = implode(', ', $ting_object->getContributors());
          break;
        case 'creators_contributers':
          $replacements[$original] = implode(', ', array_merge($ting_object->getCreators(), $ting_object->getContributors()));
          break;
        case 'abstract':
          $replacements[$original] = $ting_object->getAbstract();
          break;
      }

      if ($sanitize) {
        $replacements[$original] = check_plain($replacements[$original]);
      }
    }
  }

  return $replacements;
}
