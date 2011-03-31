<?php

/**
 * @file recommendation_list.inc
 * Provides several list of recommended Ting objects as Panels content types.
 */

/**
 * Callback function to supply a list of content types.
 *
 * This is only required to make CTools know that we're providing 
 * multiple types here (since we have no single => TRUE in the array).
 */
function ting_recommendation_panes_recommendation_list_ctools_content_types() {
  return array(
    'title' => t('Recommendation list'),
  );
}

/**
 * Callback function to supply a list of content types.
 */
function ting_recommendation_panes_recommendation_list_content_type_content_types() {
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
function ting_recommendation_panes_recommendation_list_content_type_render($subtype, $conf, $panel_args, $context) {
  $basePath = drupal_get_path('module', 'ting_recommendation_panes');
  drupal_add_css($basePath.'/css/ting_recommendation_panes.css');
  
	//get the objects to base the recommendation on based on the first supplied context
	$objects = FALSE;
	foreach ($context as $c) {
  	switch ($c->type) {
  		case 'ting_object':
  		  $objects = ting_get_object_by_id($c->original_argument);
  		break 2;
      case 'ting_collection':
        $objects = ting_get_collection_by_id($c->original_argument);
      break 2;  		
  	}
  }
  
  $block = new stdClass();
  
  if ($objects) {
	  $recommendedObjects = ting_recommendation_panes_get_recommended_objects($objects);
	  
	  switch($subtype) {
	    case 'recommendation_list':
	      $block->content = theme('ting_recommendation_panes_recommendation_list', $recommendedObjects);
	      break;
	  }
  }
  
  return $block;
}

/**
 * Return the pane titles.
 */
function ting_recommendation_panes_recommendation_list_content_type_admin_title($subtype, $conf, $context) {
  $contextIdentifiers =  array();
	foreach ($context as $c)
  {
  	if ($c->type != 'any')
  	{
      $contextIdentifiers[] = $c->identifier;
  	}
  }
  $contextIdentifiers = implode(', ', $contextIdentifiers);
	
	switch($subtype) {
    case 'recommendation_list':
      return t('“@s”: Ting recommendation list', array('@s' => $contextIdentifiers));
  }
}

/**
 * Returns an edit form for the content type.
 */
function ting_recommendation_panes_recommendation_list_content_type_edit_form(&$form, &$form_state) {
  return $form;
}
