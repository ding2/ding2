<?php

$plugin = array(
    'title' => t('Ting object'),
    'description' => t('An object from the Ting database – books, CD-ROMs, magazines, etc.'),
    'context' => 'ting_ting_object_create',
    'settings form' => 'ting_ting_object_context_settings_form',
    'keyword' => 'ting_object',
    'context name' => 'ting_object',
    'convert list' => 'ting_ting_object_convert_list',
    'convert' => 'ting_ting_object_convert',
    'placeholder form' => array(
      '#type' => 'textfield',
      '#description' => t('Enter the object ID for this context'),
    ),
);

/**
 * It's important to remember that $conf is optional here, because contexts
 * are not always created from the UI.
 */
function ting_ting_object_create($empty, $data = NULL, $conf = FALSE) {
  $context = new ctools_context('ting_object');
  $context->plugin = 'ting_object';
  $object_id = FALSE;

  if ($empty) {
    return $context;
  }

  if ($conf) {
    $object_id = is_array($data) && isset($data['object_id']) ? $data['object_id'] : (is_object($data) ? $data->id : 0);
  }

  if (!empty($data)) {
    $context->data     = $data;
    $context->argument = $object_id;
    if (!empty($data->creators_string)) {
      $context->title  = t('@title', array('@title' => $data->title));
      if (!empty($data->creators_string)) {
        $context->title .= t(' by @author', array('@author' => $data->creators_string));
      }
    }
    else {
      $context->title  = check_plain($data->title);
    }

    return $context;
  }
}

/**
 * Settings for when manually creating this context.
 */
function ting_ting_object_context_settings_form($conf) {
  $form = array();
  return $form;
}

/**
 * List of conversion options.
 */
function ting_ting_object_convert_list() {
  return array(
    'title_full' => t('Object title and author names'),
    //'title' => t('Object title'),
  );
}

/**
 * Convert a context into a string.
 */
function ting_ting_object_convert($context, $type) {
  switch ($type) {
    case 'title_full':
      return $context->title;
  }
}


