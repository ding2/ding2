<?php
/**
 * @file
 * This panels content type defines panes that can be used to add a user
 * sub-menu base on the tabs on the user page.
 */

$plugin = array(
  'title' => t('User sub-menu'),
  'description' => t('The current users sub-menu'),
  'edit form' => 'ding_user_frontend_user_menu_edit_form',
  'render callback' => 'ding_user_frontend_user_menu_content_type_render',
  'single' => TRUE,
  'content_types' => array('list'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
  'defaults' => array(
    'path' => NULL,
  ),
);

/**
 * Implements hook_ID_content_type_render().
 */
function ding_user_frontend_user_menu_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();

  // Try to get configuration.
  $path = NULL;
  if (!empty($conf['path'])) {
    global $user;
    $path = token_replace($conf['path'], array('user' => $user));
  }

  $block->title = '<a href="/user">' . t('My account') . '</a>';
  $block->content = ding_user_frontend_build_menu($path);

  return $block;
}

/**
 * Edit form callback for the content type.
 */
function ding_user_frontend_user_menu_edit_form($form, &$form_state) {
  $form['path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path'),
    '#description' => t('The path to generate the menu based on. Defaults to current path.'),
    '#required' => FALSE,
    '#default_value' => $form_state['conf']['path'],
  );

  $form['token_help'] = array(
    '#title' => t('Replacement patterns'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Prefer raw-text replacements for text to avoid problems with HTML entities!'),
  );

  $form['token_help']['help'] = array(
    '#theme' => 'token_tree',
    '#token_types' => array('user'),
  );

  return $form;
}

/**
 * Submit handler for the settings form.
 */
function ding_user_frontend_user_menu_edit_form_submit($form, &$form_state) {
  $form_state['conf']['path'] = $form_state['values']['path'];
}
