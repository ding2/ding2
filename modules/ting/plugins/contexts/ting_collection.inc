<?php

$plugin = array(
    'title' => t('Ting collection'),
    'description' => t('An collection from the Ting database – books, CD-ROMs, magazines, etc.'),
    'context' => 'ting_ting_collection_create',
    'settings form' => 'ting_ting_collection_context_settings_form',
    'keyword' => 'ting_collection',
    'context name' => 'ting_collection',
    'convert list' => 'ting_ting_collection_convert_list',
    'convert' => 'ting_ting_collection_convert',
    'placeholder form' => array(
      '#type' => 'textfield',
      '#description' => t('Enter the collection ID for this context'),
    ),
);

/**
 * It's important to remember that $conf is optional here, because contexts
 * are not always created from the UI.
 */
function ting_ting_collection_create($empty, $data = NULL, $conf = FALSE) {
  $context = new ctools_context('ting_collection');
  $context->plugin = 'ting_collection';
  $collection_id = FALSE;

  if ($empty) {
    return $context;
  }

  if ($conf) {
    $collection_id = is_array($data) && isset($data['collection_id']) ? $data['collection_id'] : (is_collection($data) ? $data->id : 0);
  }

  if (!empty($data)) {
    $context->data     = $data;
    $context->argument = $collection_id;
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
function ting_ting_collection_context_settings_form($conf) {
  $form = array();
  return $form;
}

/**
 * List of conversion options.
 */
function ting_ting_collection_convert_list() {
  return array(
    'title_full' => t('collection title and author names'),
    //'title' => t('collection title'),
  );
}

/**
 * Convert a context into a string.
 */
function ting_ting_collection_convert($context, $type) {
  switch ($type) {
    case 'title_full':
      return $context->title;
  }
}



