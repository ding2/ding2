<?php

/**
 * @file
 * Ding wishlist pages.
 */

/**
 * Menu callback; Display user wishlist items.
 */
function ding_wishlist_user_wishlist_page($account) {
  $content_ids = flag_load('wishlist')->get_user_content_ids($account->uid);

  if ($content_ids) {
    $rendered_form = drupal_get_form('ding_wishlist_remove_form', $content_ids);
    if (!empty($rendered_form)) {
      return $rendered_form;
    }
  }

  return ding_wishlist_user_wishlist_empty_page();
}

/**
 * Wishlist page empty text.
 */
function ding_wishlist_user_wishlist_empty_page() {
  return t('Wishlist is empty');
}

/**
 * Wishlist manage form.
 */
function ding_wishlist_remove_form($form, &$form_state, $entities) {
  $item_options = array();
  foreach ($entities as $entity_id => $entity_type) {
    // Build item view.
    $item_view_build = ding_wishlist_item_view($entity_type, $entity_id);
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
function ding_wishlist_remove_form_submit($form, &$form_state) {
  // Filter selected items.
  $items_to_delete = array_filter($form_state['values']['items']);
  if ($items_to_delete) {
    // Unflag all selected items.
    $flag = flag_get_flag('wishlist');
    foreach ($items_to_delete as $item_wid) {
      $flag->flag('unflag', $item_wid);
    }
  }
}

/**
 * Theme form as a table.
 */
function theme_ding_wishlist_remove_form($variables) {
  $output = "";
  $form = $variables['form'];
  $flag = flag_get_flag('wishlist');

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
      $button = '<input type="button" class="form-submit" value="' . t($flag->unflag_short) . '">';
      $delete_link_query = drupal_get_destination() + array('token' => flag_get_token($item_wid));
      $delete_link = l($button, 'flag/unflag/wishlist/' . $item_wid, array('query' => $delete_link_query, 'html' => TRUE));

      //Add row.
      $rows[] = array(
        drupal_render($form['items'][$key]),
        drupal_render($form['#builded_entities'][$item_wid]), // Theme item as a teaser.
        $delete_link,
      );
    }
  }

  if (count($rows)) {
    $output .= theme('table', array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('width' => '100%'),
    ));

    // Render all remaining elements.
    $output .= drupal_render_children($form);
  }

  return $output;
}
