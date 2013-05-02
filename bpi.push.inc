<?php
/**
 * @file
 * Syndication logic here.
 */

/**
 * Start a content push session.
 *
 * @see bpi_menu()
 *
 * @param string $type
 *   Request type, simple http or ajax.
 * @param int $nid
 *   Node id, whose content is to be pushed.
 * @return Array/string
 *   Ajax command set in case of ajax request, push content page
 *   markup otherwise.
 */
function bpi_push_action($type, $nid) {
  $is_ajax = ($type == 'ajax') ? TRUE : FALSE;

  if (empty($nid)) {
    drupal_goto('admin/content');
  }

  if ($is_ajax) {
    $commands = array();

    $commands[] = ajax_command_ding_popup(
      'bpi-push',
      t('Push to BPI'),
      drupal_render(drupal_get_form('bpi_push_form'))
    );

    return array('#type' => 'ajax', '#commands' => $commands);
  }
  else {
    return drupal_get_form('bpi_push_form');
  }
}

function bpi_push_form($form, $form_state) {
  $form['bpi_push_category'] = array(
    '#type' => 'select',
    '#title' => t('Category'),
    '#options' => bpi_get_bpi_categories(),
    '#default_value' => ','
  );

  $form['bpi_push_audience'] = array(
    '#type' => 'select',
    '#title' => t('Audience'),
    '#options' => bpi_get_bpi_audience(),
    '#default_value' => ','
  );

  $form['bpi_push_images'] = array(
    '#type' => 'checkbox',
    '#title' => t('Push with images'),
  );

  $form['bpi_push_ccl'] = array(
    '#type' => 'checkbox',
    '#title' => t('Written under Creative Commons License'),
  );

  $form['bpi_push_cancel'] = array(
    '#type' => 'button',
    '#value' => t('Cancel'),
    '#ajax' => array(
      ''
    ),
  );

  $form['bpi_push_submit'] = array(
    '#type' => 'button',
    '#value' => t('Push'),
  );

  return $form;
}

function bpi_get_bpi_categories() {
  return array(
    'dummy_1' => 'dummy_1',
    'dummy_1' => 'dummy_1',
  );
}

function bpi_get_bpi_audience() {
  return array(
    'dummy_1' => 'dummy_1',
    'dummy_1' => 'dummy_1',
  );
}
