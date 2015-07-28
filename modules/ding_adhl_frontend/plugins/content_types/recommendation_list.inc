<?php

/**
 * @file
 * Provides lists of recommended ting objects/entities as panels content types
 * based on the object/entity being display.
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
      'description' => t('Displays a list of recommended ting entities.'),
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
function ding_adhl_frontend_recommendation_list_content_type_render($subtype, $conf, $panel_args, $contexts) {
  // Get the objects to base the recommendation on based on the first supplied
  // context.
  $object = FALSE;
  foreach ($contexts as $context) {
    $ting_object_id = $context->get_original_argument()->getId();
    switch ($context->type) {
      case 'ting_object':
        $object = ting_get_object($ting_object_id);
        break 2;

      case 'ting_collection':
        $object = ting_get_object($ting_object_id, TRUE);
        break 2;
    }
  }

  // Build the block, if then context was present.
  $block = new stdClass();
  if ($object) {
    // Get recommendations based on the current object.
    $entities = ding_adhl_frontend_get_recommended_objects($object);

    // Build render array with the recommendations found.
    $items = array();
    foreach ($entities as $entity) {
      $items[] = array(
        '#theme' => 'ding_adhl_frontend_recommendation_list_entry',
        '#item' => $entity,
      );
    }

    // Fill the found results into the block.
    $block->subject = t("Others borrowed");
    $block->content = array(
      '#theme' => 'ding_adhl_frontend_recommendation_list',
      '#type' => 'ul',
      '#items' => $items,
    );
  }

  return $block;
}

/**
 * Return the pane titles.
 */
function ding_adhl_frontend_recommendation_list_content_type_admin_title($subtype, $conf, $contexts) {
  $identifiers = array();
  foreach ($contexts as $context) {
    if ($context->type != 'any') {
      $identifiers[] = $context->identifier;
    }
  }
  $identifiers = implode(', ', $identifiers);

  switch ($subtype) {
    case 'recommendation_list':
      return t('“@s”: Ting recommendation list', array('@s' => $identifiers));
  }
}

/**
 * Returns an edit form for the content type.
 */
function ding_adhl_frontend_recommendation_list_content_type_edit_form($form, &$form_state) {
  return $form;
}
