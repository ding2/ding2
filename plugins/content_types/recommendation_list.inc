<?php

/**
 * @file
 * Provides several list of recommended Ting objects as Panels content types.
 */

/**
 * Callback function to supply a list of content types.
 *
 * This is only required to make CTools know that we're providing
 * multiple types here (since we have no single => TRUE in the array).
 */
function ding_adhl_frontend_recommendation_list_ctools_content_types() {
  return array(
    'title' => t('Recommendation list'),
  );
}

/**
 * Callback function to supply a list of content types.
 */
function ding_adhl_frontend_recommendation_list_content_type_content_types() {
  $types = array(
    'recommendation_list' => array(
      'title' => t('Ting recommendation list'),
      'description' => t('Displays a list of recommended Ting objects.'),
    ),
  );

  // Append our default settings to every type.
  foreach ($types as $name => $type) {
    $types[$name] += array(
      'category' => t('Ting'),
      'required context' => array(
        new ctools_context_optional(t('Ting object'), 'ting_object'),
        new ctools_context_optional(t('Ting collection'), 'ting_collection'),
      ),
    );
  }
  return $types;
}

/**
 * Return the pane contents.
 */
function ding_adhl_frontend_recommendation_list_content_type_render($subtype, $conf, $panel_args, $context) {
  //get the objects to base the recommendation on based on the first supplied context
  $objects = FALSE;
  foreach ($context as $c) {
    switch ($c->type) {
      case 'ting_object':
        $objects = ting_get_object($c->get_original_argument()->getId());
        break 2;
      case 'ting_collection':
        $objects = ting_get_object($c->get_original_argument()->getId(), TRUE);
        break 2;
    }
  }

  $block = new stdClass();

  if ($objects) {
    $recommended_objects = ding_adhl_frontend_get_recommended_objects($objects);

    $model = array();
    foreach ($recommended_objects as $recommended_object) {
      $url = entity_uri("ting_object", $recommended_object);
      $url = $url['path'];
      $model[] = array(
        "url" => $url,
        "creators" => $recommended_object->creators,
        "title" => $recommended_object->title,
        );
    }
    switch ($subtype) {
      case 'recommendation_list':
        $block->content = theme('ding_adhl_frontend_recommendation_list', array('models' => $model));
        break;
    }
  }

  return $block;
}

/**
 * Return the pane titles.
 */
function ding_adhl_frontend_recommendation_list_content_type_admin_title($subtype, $conf, $context) {
  $context_identifiers =  array();
  foreach ($context as $c) {
    if ($c->type != 'any') {
      $context_identifiers[] = $c->identifier;
    }
  }
  $context_identifiers = implode(', ', $context_identifiers);

  switch ($subtype) {
    case 'recommendation_list':
      return t('“@s”: Ting recommendation list', array('@s' => $context_identifiers));
  }
}

/**
 * Returns an edit form for the content type.
 */
function ding_adhl_frontend_recommendation_list_content_type_edit_form($form, &$form_state) {
  return $form;
}
