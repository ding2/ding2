<?php
/**
 * @file
 * Implements popup for logging in to add comments
 */

/**
 * Implements hook_entity_view().
 *
 * Hook is implemented to alter the 'log in to add comment' part of comments
 * define a new theme for comments if ['comment_forbidden'] is set
 */
function ding_user_entity_view($comment, $type, $view_mode, $langcode) {
  if (isset($comment->content['links']['comment']['#links']['comment_forbidden'])) {
    $comment->content['links']['comment']['#theme'] = 'ding_user_comment_post_forbidden';
  }
}

/**
 * Implements hook_theme().
 */
function ding_user_theme() {
  return array(
    'ding_user_comment_post_forbidden' => array('render element' => 'elements'),
  );
}

/**
 * Get a form for displaying the 'log in' to add comments link.
 *
 * @return array
 *   Form with login button.
 */
function ding_user_comment_forbidden_form() {
  $form = array();

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Log in'),
    '#ajax' => array('callback' => 'ding_user_comment_forbidden_form_callback'),
  );

  return $form;
}

/**
 * Theme comment_post_forbidden (log in to add comments).
 */
function theme_ding_user_comment_post_forbidden($variables) {
  $render_array = array();
  $form = drupal_get_form('ding_user_comment_forbidden_form');

  $class = drupal_html_class('ding_user_comment_forbidden_form');

  $render_array['#prefix'] = '<div class="' . $class . '">';
  $render_array['#markup'] = drupal_render($form);
  $render_array['#suffix'] = '<span>' . t('to add comments') . '</span></div>';

  return drupal_render($render_array);
}


/**
 * Callback for ding_user_comment_forbidden_form form.
 */
function ding_user_comment_forbidden_form_callback($form, $form_state) {
  global $base_root;

  $creds = ding_user_get_creds();
  $name = isset($creds['name']) ? $creds['name'] : '';
  $pass = isset($creds['pass']) ? $creds['pass'] : '';
  try {
    ding_provider_invoke('user', 'authenticate', $name, $pass);
  }
  catch (DingProviderAuthException $e) {
    // Do nothing.
  }

  // User successful logged in - reload page.
  // @TODO .. there must be an easier way to refresh a page -- drupal_reload???
  // Couldn't find any in Ajax framework commands.
  ctools_include('ajax');
  ctools_add_js('ajax-responder');

  $commands = array();
  $commands[] = ctools_ajax_command_redirect($base_root . $form['#action']);
  return array('#type' => 'ajax', '#commands' => $commands);
}
