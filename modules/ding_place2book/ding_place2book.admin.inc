<?php
/**
 * @file
 * Contains all administration forms and related functions.
 */

/**
 * Form handler for configuration service settings.
 */
function ding_place2book_service_admin_form($form, &$form_state) {
  $form['#tree'] = TRUE;
  $settings = variable_get('ding_place2book_settings', array());

  $form['ding_place2book'] = array(
    '#type' => 'fieldset',
    '#title' => t('Place2Book service'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['ding_place2book']['url'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book service URL'),
    '#default_value' => isset($settings['url']) ? $settings['url'] : 'https://api.place2book.com',
    '#description' => t('Enter a valid Place2book service endpoint, such as https://www.place2book.com/da/event_api'),
    '#size' => 100,
  );

  $form['ding_place2book']['token'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book authorisation token'),
    '#default_value' => isset($settings['token']) ? $settings['token'] : '',
    '#description' => t('This is the default API key used when connecting to Place2book.'),
  );

  $form['ding_place2book']['eventMakers'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book event makers URL'),
    '#default_value' => isset($settings['eventMakers']) ? $settings['eventMakers'] : 'https://api.place2book.com/event_makers',
    '#required' => TRUE,
    '#size' => 100,
  );

  $form['ding_place2book']['editEvent'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book edit event URL'),
    '#default_value' => isset($settings['editEvent']) ? $settings['editEvent'] : 'https://api.place2book.com/event_makers/:event_maker_id/events/:event_id',
    '#required' => TRUE,
    '#size' => 100,
  );

  $form['ding_place2book']['getEvent'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book get event URL'),
    '#default_value' => isset($settings['getEvent']) ? $settings['getEvent'] : 'https://api.place2book.com/event_makers/:event_maker_id/events/:event_id',
    '#required' => TRUE,
    '#size' => 100,
  );

  $form['ding_place2book']['updateEvent'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book update event URL'),
    '#default_value' => isset($settings['updateEvent']) ? $settings['updateEvent'] : 'https://api.place2book.com/event_makers/:event_maker_id/events/:event_id',
    '#required' => TRUE,
    '#size' => 100,
  );

  $form['ding_place2book']['deleteEvent'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book delete event URL'),
    '#default_value' => isset($settings['deleteEvent']) ? $settings['deleteEvent'] : 'https://api.place2book.com/event_makers/:event_maker_id/events/:event_id',
    '#required' => TRUE,
    '#size' => 100,
  );

  $form['ding_place2book']['createEvent'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book create event URL'),
    '#default_value' => isset($settings['createEvent']) ? $settings['createEvent'] : 'https://api.place2book.com/event_makers/:event_maker_id/events',
    '#required' => TRUE,
    '#size' => 100,
  );

  $form['ding_place2book']['createPrice'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book create price URL'),
    '#default_value' => isset($settings['createPrice']) ? $settings['createPrice'] : 'https://api.place2book.com/event_makers/:event_maker_id/events/:event_id/prices',
    '#required' => TRUE,
    '#size' => 100,
  );

  $form['ding_place2book']['getPrices'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book get prices of event URL'),
    '#default_value' => isset($settings['getPrices']) ? $settings['getPrices'] : 'https://api.place2book.com//event_makers/:event_maker_id/events/:event_id/prices',
    '#required' => TRUE,
    '#size' => 100,
  );

  $form['ding_place2book']['getPrice'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book get price URL'),
    '#default_value' => isset($settings['getPrice']) ? $settings['getPrice'] : 'https://api.place2book.com//event_makers/:event_maker_id/events/:event_id/prices/:price_id',
    '#required' => TRUE,
    '#size' => 100,
  );

  $form['ding_place2book']['updatePrice'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book update price URL'),
    '#default_value' => isset($settings['updatePrice']) ? $settings['updatePrice'] : 'https://api.place2book.com//event_makers/:event_maker_id/events/:event_id/prices/:price_id',
    '#required' => TRUE,
    '#size' => 100,
  );

  $form['ding_place2book']['deletePrice'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book delete price URL'),
    '#default_value' => isset($settings['deletePrice']) ? $settings['deletePrice'] : 'https://api.place2book.com//event_makers/:event_maker_id/events/:event_id/prices/:price_id',
    '#required' => TRUE,
    '#size' => 100,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => array('ding_place2book_service_admin_form_submit'),
  );

  return $form;
}

/**
 * Submit handler for configuration page of p2b library.
 */
function ding_place2book_service_admin_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $settings = $values['ding_place2book'];
  variable_set('ding_place2book_settings', $settings);

  drupal_set_message(t('Configuration successfully saved'));
}

/**
 * Form handler for configuration Event makers.
 */
function ding_place2book_defaults_admin_form($form, &$form_state) {
  $event_makers = array();
  try {
    $p2b = ding_place2book_instance();
    $event_makers = $p2b->getEventMakers();
  }
  catch (Exception $ex) {
    watchdog_exception('ding_place2book', $ex);
    drupal_set_message($ex->getMessage(), 'error');
  }

  $options = array();
  array_map(function ($i) use (&$options) {
    $options[$i->id] = $i->name;
  }, $event_makers);

  $form['ding_p2b_default_event_maker'] = array(
    '#type' => 'radios',
    '#title' => t('Default event maker'),
    '#options' => $options,
    '#default_value' => variable_get('ding_p2b_default_event_maker', NULL),
    '#description' => t('It will be used in case when will be missed mappings from library.'),
  );

  $form['ding_p2b_default_synchronize'] = array(
    '#type' => 'checkbox',
    '#title' => t('Maintain copy'),
    '#default_value' => variable_get('ding_p2b_default_synchronize', FALSE),
    '#description' => t('When set, a corresponding event is created and updated on the ticket booking service Place2Book.com.'),
  );

  $form['ding_p2b_default_kultunaut_export'] = array(
    '#type' => 'checkbox',
    '#title' => t('Kultunaut export'),
    '#default_value' => variable_get('ding_p2b_default_kultunaut_export', FALSE),
    '#description' => t('If checked, Place2book will forward this ding-event to Kultunaut.'),
  );

  $form['ding_p2b_default_passive'] = array(
    '#type' => 'checkbox',
    '#title' => t('Passive event'),
    '#default_value' => variable_get('ding_p2b_default_passive', FALSE),
    '#description' => t('If checked, Place2book flags the event as passive with no ticket sale. This can be useful for sending events to Kultunaut without actually using Place2book, or using Place2book for keeping record of all events with or without tickets.'),
  );

  $form['ding_p2b_default_capacity'] = array(
    '#type' => 'textfield',
    '#title' => t('Capacity'),
    '#default_value' => variable_get('ding_p2b_default_capacity', 0),
    '#description' => t('Optional. Maximum capacity on this event. Set to 0 for unlimited capacity.'),
    '#element_validate' => array('element_validate_integer'),
  );

  $form['ding_p2b_default_price_name'] = array(
    '#type' => 'textfield',
    '#title' => t("Ticket type"),
    '#default_value' => variable_get('ding_p2b_default_price_name', 'Adgang'),
    '#description' => t('E. g. Adult, Child or Standard. Adgang is the default ticket type.'),
  );

  return system_settings_form($form);
}


/**
 * Form handler for configuration Event makers.
 */
function ding_place2book_mappings_admin_form($form, &$form_state) {
  $form['#tree'] = TRUE;
  $event_makers = array();
  try {
    $p2b = ding_place2book_instance();
    $event_makers = $p2b->getEventMakers();
  }
  catch (Exception $ex) {
    watchdog_exception('ding_place2book', $ex);
    drupal_set_message('Error on getting data from p2b. Check reports.');
  }
  $options = array();
  array_map(function ($i) use (&$options) {
    $options[$i->id] = $i->name;
  }, $event_makers);
  $form['ding_p2b_library_event_makers'] = array(
    '#type' => 'fieldset',
    '#title' => t('Event makers'),
    '#description' => t('Associate each library with some event maker.'),
    '#tree' => TRUE,
  );
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'ding_library')
    ->execute();
  $defaults = variable_get('ding_p2b_library_event_makers', array());
  if (isset($result['node'])) {
    foreach ($result['node'] as $value) {
      $node = node_load($value->nid);
      $form['ding_p2b_library_event_makers'][$node->nid] = array(
        '#type' => 'select',
        '#title' => $node->title,
        '#default_value' => isset($defaults[$node->nid]) ? $defaults[$node->nid] : NULL,
        '#options' => $options,
        '#required' => TRUE,
      );
    }
  }

  $form['ding_p2b_kultunaut_age_group'] = array(
    '#type' => 'fieldset',
    '#title' => t('Kultunaut age group'),
  );
  $vocabulary = taxonomy_vocabulary_machine_name_load('event_target');
  $terms = taxonomy_get_tree($vocabulary->vid);
  $options = array(
    'Alle' => 'Alle',
    'Børn' => 'Børn',
    'Unge' => 'Unge',
    'Voksne' => 'Voksne',
    'Ældre' => 'Ældre',
  );
  $defaults = variable_get('ding_p2b_kultunaut_age_group', array());
  foreach ($terms as $term) {
    $form['ding_p2b_kultunaut_age_group'][$term->tid] = array(
      '#type' => 'select',
      '#title' => $term->name,
      '#description' => t('Associate event target :term with kultunaut age group.', array(':term' => $term->name)),
      '#default_value' => isset($defaults[$term->tid]) ? $defaults[$term->tid] : NULL,
      '#options' => $options,
      '#required' => TRUE,
    );
  }

  $form['ding_p2b_kultunaut_export_category'] = array(
    '#type' => 'fieldset',
    '#title' => t('Kultunaut export category'),
  );
  $vocabulary = taxonomy_vocabulary_machine_name_load('event_category');
  $terms = taxonomy_get_tree($vocabulary->vid);
  $options = _ding_place2book_load_export_category();
  $defaults = variable_get('ding_p2b_kultunaut_export_category', array());
  foreach ($terms as $term) {
    $form['ding_p2b_kultunaut_export_category'][$term->tid] = array(
      '#type' => 'select',
      '#title' => $term->name,
      '#description' => t('Associate event category :term with kultunaut category.', array(':term' => $term->name)),
      '#default_value' => isset($defaults[$term->tid]) ? $defaults[$term->tid] : NULL,
      '#options' => $options,
      '#required' => TRUE,
    );
  }

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Submit handler for processing and storing values.
 */
function ding_place2book_mappings_admin_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  if (!empty($values['ding_p2b_kultunaut_age_group'])) {
    variable_set('ding_p2b_kultunaut_age_group', $values['ding_p2b_kultunaut_age_group']);
  }
  if (!empty($values['ding_p2b_kultunaut_export_category'])) {
    variable_set('ding_p2b_kultunaut_export_category', $values['ding_p2b_kultunaut_export_category']);
  }
  if (!empty($values['ding_p2b_library_event_makers'])) {
    $vals = array_filter($values['ding_p2b_library_event_makers']);
    variable_set('ding_p2b_library_event_makers', $vals);
  }
}

/**
 * Load and parse XML with export category.
 *
 * @return array
 *   Array with export category.
 *
 * @see http://www.kultunaut.dk/perl/export/nautgenrerxml
 */
function _ding_place2book_load_export_category() {
  $path = 'http://www.kultunaut.dk/perl/export/nautgenrerxml';
  $options = array();
  $data = file_get_contents($path);
  if ($data) {
    $xml = new \SimpleXMLElement($data);
    foreach ($xml->genregroup as $genregroup) {
      $group = (string) $genregroup['id'];
      foreach ($genregroup as $genre) {
        $val = "{$group}: {$genre}";
        $options[$val] = $val;
      }
    }
  }
  return $options;
}
