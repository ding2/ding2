<?php

/**
 * @file
 * Ding bookmark pages.
 */

/**
 * Menu callback; Display user bookmark items.
 */
function ding_bookmark_user_bookmark_page($account) {
  $content_ids = flag_load('bookmark')->get_user_content_ids($account->uid);

  if ($content_ids) {
    $rendered_form = drupal_get_form('ding_bookmark_remove_form', $content_ids);
    if (!empty($rendered_form)) {
      return $rendered_form;
    }
  }

  return ding_bookmark_user_bookmark_empty_page();
}

/**
 * Bookmark page empty text.
 */
function ding_bookmark_user_bookmark_empty_page() {
  return t('Bookmarks is empty');
}

/**
 * Bookmark manage form.
 */
function ding_bookmark_remove_form($form, &$form_state, $entities) {
  $item_options = array();
  foreach ($entities as $entity_id => $entity_type) {
    // Build item view.
    $item_view_build = ding_bookmark_item_view($entity_type, $entity_id);
    if ($item_view_build) {
      $item_options[$entity_id] = $entity_id;
      $form['#builded_entities'][$entity_id] = $item_view_build;
    }
  }

  $form['items'] = array(
    '#type' => 'checkboxes',
    '#options' => $item_options,
    '#required' => TRUE,
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Delete selected'),
  );

  return $form;
}

/**
 * Submit handler.
 */
function ding_bookmark_remove_form_submit($form, &$form_state) {
  // Filter selected items.
  $items_to_delete = array_filter($form_state['values']['items']);
  if ($items_to_delete) {
    // Unflag all selected items.
    $flag = flag_get_flag('bookmark');
    foreach ($items_to_delete as $item_wid) {
      $flag->flag('unflag', $item_wid);
    }
  }
}

/**
 * Theme form as a table.
 */
function theme_ding_bookmark_remove_form($variables) {
  $output = "";
  $form = $variables['form'];
  $flag = flag_get_flag('bookmark');

  // Add 'select all' checkbox.
  drupal_add_js('misc/tableselect.js');
  $header = array(
    array('class' => array('select-all')),
    t('Title'),
    '',
  );

  // Create table rows.
  $rows = array();
  if (!empty($form['items']['#options'])) {

    foreach (element_children($form['items']) as $key) {
      $item_wid = $key;
      // Clean checkbox
      unset($form['items'][$key]['#title']) ;
      // Create delete link.
      $delete_link_query = drupal_get_destination() + array('token' => flag_get_token($item_wid));
      $delete_link = array(
        '#prefix' => '<p class="ding-entity-button">',
        '#suffix' => '</p>',
        '#type' => 'markup',
        '#markup' => l(t($flag->unflag_short), 'flag/unflag/bookmark/' . $item_wid, array('query' => $delete_link_query)),
      );

      // reservation button
      // NB: Nested forms does not validate as XHTML
      $reservation_div = NULL;
      if ( $form['#builded_entities'][$item_wid]['#object']->ding_entity_type == 'ding_entity' &&
           $form['#builded_entities'][$item_wid]['#object']->is('reservable')
         ) {
        $reservation_form = array(ding_provider_get_form('ding_reservation_reserve_form', new DingReservationReservableEntity($form['#builded_entities'][$item_wid]['#object']), TRUE));
        $reservation_div = array(
          '#prefix' => '<div class="ding-entity-button-reserve">',
          '#suffix' => '</div>',
          '#type' => 'markup',
          '#markup' => drupal_render($reservation_form),
        );
        $reservation_div = drupal_render($reservation_div);
      }

      //Add row.
      $rows[] = array(
        drupal_render($form['items'][$key]),
        drupal_render($form['#builded_entities'][$item_wid]), // Theme item as a teaser.
        drupal_render($delete_link) . $reservation_div,
      );
    }
  }


  if (count($rows)) {

    // ugly hack : Browsers ignores first nested form in XHTML.
    // add dummy form as first nested form.
    $dummy_form = drupal_get_form('ding_bookmark_dummy_form');
    // dpm(drupal_render($dummy_form));
    $rows[0][2] = drupal_render($dummy_form) . $rows[0][2];

    $output .= theme('table', array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('width' => 'auto'),
    ));

    // Render all remaining elements.
    $output .= drupal_render_children($form);
  }

  return $output;
}




/**
 * Bookmark dummy form.
 */
function ding_bookmark_dummy_form($form, &$form_state) {
  $form = array();
  return $form;
}
