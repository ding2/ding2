<?php

/**
 * Implements popup for logging in to add comments
 */


/**
 * Implements hook_entity_view
 * hook is implented to alter the 'log in to add comment' part of comments
 * define a new theme for comments if ['comment_forbidden'] is set
 **/
function ding_user_entity_view($comment, $type, $view_mode, $langcode ) {
  //  dpm($comment);
   if( isset($comment->content['links']['comment']['#links']['comment_forbidden']) ) {
    $comment->content['links']['comment']['#theme'] = 'ding_user_comment_post_forbidden';
  }
}

/**
 * Implements hook_theme
 */
function ding_user_theme($existing, $type, $theme, $path){
  return array('ding_user_comment_post_forbidden'=>
	       array('render element' => 'elements',)
	       );
}

/**
 * get a form for displaying the 'log in' to add comments link
 * @return form
 */
function ding_user_comment_forbidden_form() {
  $form['submit'] = 
    array('#type' => 'submit',
	  '#value' => t('Log in'),
	  '#ajax' => 
	  array('callback' => 'ding_user_comment_forbidden_form_callback',),);   
  return $form;
}


/**
 * Theme comment_post_forbidden (log in to add comments)
 */
function theme_ding_user_comment_post_forbidden($variables) {
  $render_array = array();
  $form = drupal_get_form('ding_user_comment_forbidden_form');

  $render_array['#markup'] = drupal_render($form);
  $render_array['#suffix'] = '<span>'.t('to add comments').'</span>';

  return drupal_render($render_array);
}



/**
 * callback for ding_user_comment_forbidden_form form
 */
function ding_user_comment_forbidden_form_callback($form, $form_state) {
  $creds = array('name'=>'','pass'=>'');
  $creds = ding_user_get_creds();

  $name = isset($creds['name']) ? $creds['name'] : '';
  $pass = isset($creds['pass']) ? $creds['pass'] : '';
  try{ $success = ding_provider_invoke('user', 'authenticate', $name, $pass); }
  catch(DingProviderAuthException $e) {
    //do nothing
  }  
  // user sucessfully logged in - reload page

  // @TODO .. there must be an easier way to refresh a page -- drupal_reload???
  // couldn't find any in Ajax framework commands

  ctools_include('ajax');
  ctools_add_js('ajax-responder');

  $url = $form['#action'];
  $base = base_path();
  // base_path might be '/'
  if( strlen($base) > 1 ) {
    $url = str_replace($base,'',$url);
  }
 
  $commands = array();
  $commands[] = ctools_ajax_command_redirect($url);
  return array('#type' => 'ajax','#commands' => $commands);
}
