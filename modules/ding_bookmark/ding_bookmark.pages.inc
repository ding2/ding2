<?php
/**
 * @file
 * Ding bookmark pages.
 */

/**
 * Menu callback; Display user bookmark items.
 */
function ding_bookmark_user_bookmark_page($account) {
  $output = t('You do not have any bookmarks yet.');

  // Try to load all bookmarks for the user.
  $entities = ding_bookmark_load_bookmarks($account);
  if (!empty($entities)) {
    // Bookmarks found, so render them as a material list form.
    $bookmark_form = drupal_get_form('ding_bookmark_remove_form', $entities);
    $output = drupal_render($bookmark_form);
  }

  return $output;
}

/**
 * Bookmark manage form.
 */
function ding_bookmark_remove_form($form, &$form_state, $entities) {
  $form['bookmarks'] = array(
    '#tree' => TRUE,
  );

  // Add select all title.
  $form['title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Select all bookmarks'),
    '#prefix' => '<div class="select-all bookmarks">',
    '#suffix' => '</div>',
    '#attached' => array(
      'js' => array(
        drupal_get_path('module', 'ding_bookmark') . '/js/ding_bookmark.js',
      ),
    ),
    '#weight' => -10,
  );

  foreach ($entities as $entity) {
    // Create title that links to the object.
    $uri = entity_uri('ting_object', $entity);
    $title = l($entity->getTitle(), $uri['path']);

    // Create basic information.
    $author = field_view_field('ting_object', $entity, 'ting_author', 'user_list');
    $type = field_view_field('ting_object', $entity, 'ting_type', 'user_list');

    // Reservation button.
    $button = ding_reservation_ding_entity_buttons('ding_entity', $entity, 'ajax');

    // Generate an unique id.
    $id = drupal_html_id('availability-' . $entity->id);

    // Add javascript.
    $attached['js'] = array(
      drupal_get_path('module', 'ding_availability') . '/js/ding_availability.js',
    );

    $attached['js'][] = array(
      'data' => array(
        'ding_availability_mode' => 'holdings',
        'ding_availability' => array(
          $id => array($entity->localId),
        ),
      ),
      'type' => 'setting',
    );

    // Build the material item element.
    $item = array(
      '#type' => 'material_item',
      '#id' => $entity->tid,
      '#availability_id' => $id,
      '#title' => $title,
      '#cover' => field_view_field('ting_object', $entity, 'ting_cover', 'user_list'),
      '#attached' => $attached,
      '#information' => array(
        'author' => array(
          'label' => t('Author'),
          'data' => drupal_render($author),
          'class' => 'author',
          '#weight' => 2,
        ),
        'type' => array(
          'label' => t('Type'),
          'data' => drupal_render($type),
          'class' => 'type',
          '#weight' => 0,
        ),
        'reserve' => array(
          'class' => 'reserve',
          'data' => drupal_render($button),
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
  // Un-flag all selected items.
  $flag = flag_get_flag('bookmark');

  // Filter selected items.
  foreach ($form_state['values']['bookmarks'] as $item) {
    $tid = array_pop($item);
    if ($tid) {
      $flag->flag('unflag', $tid);
    }
  }
}
