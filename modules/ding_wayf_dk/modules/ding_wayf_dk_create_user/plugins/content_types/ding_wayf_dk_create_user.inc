<?php
/**
 * @file
 * The create user content pane
 */

$plugin = array(
  'title' => t('Ding WAYF create user link'),
  'single' => TRUE,
  'category' => t('Ding!'),
  'edit form' => 'ding_wayf_dk_login_create_user_content_type_edit_form',
  'render callback' => 'ding_wayf_dk_login_create_user_content_type_render',
);

/**
 * Run-time rendering of the body of the login block.
 */
function ding_wayf_dk_login_create_user_content_type_render($subtype, $conf, $context = NULL) {
  $block = new stdClass();

  // Don't show the login icon if a user is already logged in.
  if (user_is_anonymous()) {
    $block->content = array(
      '#theme' => 'ding_wayf_dk_create_user_link',
      '#link' => array(
        '#theme' => 'link',
        '#text' => t('Create user'),
        '#path' => 'wayf/create-user/before-page',
        '#options' => array(
          'attributes' => array(
            'class' => array('create-user-link'),
          ),
          'html' => TRUE,
        ),
      ),
    );
  }

  return $block;
}

/**
 * Edit form callback for the content type.
 */
function ding_wayf_dk_login_create_user_content_type_edit_form($form, &$form_state) {
  return $form;
}


/**
 * Submit function.
 */
function ding_wayf_dk_login_create_user_content_type_edit_form_submit(&$form, &$form_state) {
  $form_state['conf']['icon'] = $form_state['values']['icon'];
}
