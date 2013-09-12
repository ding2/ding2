<?php
/**
 * @file
 * Ding bookmark pages.
 */

/**
 * Menu callback; Display user bookmark items.
 */
function ding_bookmark_user_bookmark_page($account) {
  $entities = ding_bookmark_load_bookmarks($account);

  if (!empty($entities)) {
    $bookmark_form = drupal_get_form('ding_bookmark_remove_form', $entities);

    // Render reservation buttons outside bookmark form, so it's valid XHTML.
//    $reservation_forms = ding_bookmark_reservation_forms($entity_ids);

    // Add Javascript and CSS (hides reservation forms outside the main form) to
    // handle the bookmarks.
    drupal_add_js(drupal_get_path('module', 'ding_bookmark') . '/js/ding_bookmark.js');
    drupal_add_css(drupal_get_path('module', 'ding_bookmark') . '/css/ding_bookmark.css');

//  return $reservation_forms .
    return drupal_render($bookmark_form);
  }

  return t('Bookmarks is empty');
}

/**
 * Bookmark manage form.
 */
function ding_bookmark_remove_form($form, &$form_state, $entities) {

  foreach ($entities as $entity) {
    // Create title that links to the object.
    $uri = entity_uri('ting_object', $entity);
    $title = l($entity->getTitle(), $uri['path']);

    // Create basic information.
    $author = field_view_field('ting_object', $entity, 'ting_author', 'full');
    $abstract = field_view_field('ting_object', $entity, 'ting_abstract', 'full');

    // Build the material item element.
    $item = array(
      '#type' => 'material_item',
      '#id' => $entity->id,
      '#title' => $title,
      '#cover' => field_view_field('ting_object', $entity, 'ting_cover', 'user_list'),
      '#information' => array(
        'author' => array(
          'label' => t('Author'),
          'data' => drupal_render($author),
          'class' => 'author',
          '#weight' => 0,
        ),
        'abstract' => array(
          'label' => t('Abstract'),
          'data' => drupal_render($abstract),
          'class' => 'abstract',
          '#weight' => 4,
        ),
      ),
    );

    // Add the reservation to the form.
    $form['bookmarks'][$entity->id] = $item;
  }

  // Add action buttons to the top of the form.
  $form['actions_top'] = array(
    '#prefix' => '<div class="action-buttons">',
    '#suffix' => '</div>',
    '#weight' => -20,
  );

  // Add action buttons to the bottom of the form.
  $form['actions_bottom'] = array(
    '#prefix' => '<div class="action-buttons">',
    '#suffix' => '</div>',
    '#weight' => 10,
  );

  // Add the delete button to both top and bottom.
  $form['actions_top']['delete'] = array(
    '#prefix' => '<div class="delete-bookmarks action-button">',
    '#suffix' => '</div>',
    '#type' => 'submit',
    '#value' => t('Delete selected (@count)', array('@count' => 0)),
  );
  $form['actions_bottom']['delete'] = $form['actions_top']['delete'];

  return $form;
}

/**
 * Submit handler.
 */
function ding_bookmark_remove_form_submit($form, &$form_state) {
  // Filter selected items.
  $items_to_delete = array_filter($form_state['values']['items']);
  if ($items_to_delete) {
    // Un-flag all selected items.
    $flag = flag_get_flag('bookmark');
    foreach ($items_to_delete as $item_wid) {
      $flag->flag('unflag', $item_wid);
    }
  }
}

//
//function ding_bookmark_reservation_forms($content_ids) {
//  $reservation_block = '';
//  foreach ($content_ids as $entity_id => $entity_type) {
//    // Build item view.
//    $item_view_build = ding_bookmark_item_view($entity_type, $entity_id);
//    // Reservation buttons.
//    if ($item_view_build['#object']->ding_entity_type == 'ding_entity' && $item_view_build['#object']->is('reservable')) {
//      $reservation_form = array(ding_provider_get_form('ding_reservation_reserve_form', new DingReservationReservableEntity($item_view_build['#object']), TRUE));
//      $reservation_form[0]['#id'] = 'ding-reservation-reserve-form-wid' . $entity_id;
//      // @TODO Update this, so class can be change in the theme layer.
//      $reservation_div = array(
//        '#prefix' => '<div class="ding-entity-button-reserve">',
//        '#suffix' => '</div>',
//        '#type' => 'markup',
//        '#markup' => drupal_render($reservation_form),
//      );
//      $reservation_block .= drupal_render($reservation_div);
//    }
//  }
//  return $reservation_block;
//}
