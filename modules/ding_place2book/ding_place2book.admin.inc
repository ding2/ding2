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
  // Gets stored configs.
  $path = drupal_get_path('module', 'ding_place2book');
  $path .= '/lib/p2b/p2b.conf';
  $data = file_get_contents($path, FILE_USE_INCLUDE_PATH);
  $settings = new stdClass();
  if ($data) {
    $settings = new \SimpleXMLElement($data);
  }

  $form['ding_place2book'] = [
    '#type' => 'fieldset',
    '#title' => t('Place2Book service'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  ];

  $form['ding_place2book']['url'] = [
    '#type' => 'textfield',
    '#title' => t('Place2Book service URL'),
    '#default_value' => isset($settings->url) ? $settings->url : 'https://apitest.place2book.com',
    '#description' => t('Enter a valid Place2book service endpoint, such as https://www.place2book.com/da/event_api'),
    '#size' => 100,
  ];

  $form['ding_place2book']['token'] = [
    '#type' => 'textfield',
    '#title' => t('Place2Book authorisation token'),
    '#default_value' => isset($settings->token) ? $settings->token : '',
    '#description' => t('This is the default API key used when connecting to Place2book.'),
  ];

  $form['ding_place2book']['eventMakers'] = [
    '#type' => 'textfield',
    '#title' => t('Place2Book event makers URL'),
    '#default_value' => isset($settings->eventMakers) ? $settings->eventMakers : 'https://apitest.place2book.com/event_makers',
    '#required' => TRUE,
    '#size' => 100,
  ];

  $form['ding_place2book']['editEvent'] = [
    '#type' => 'textfield',
    '#title' => t('Place2Book edit event URL'),
    '#default_value' => isset($settings->editEvent) ? $settings->editEvent : 'https://apitest.place2book.com/event_makers/:event_maker_id/events/:event_id',
    '#required' => TRUE,
    '#size' => 100,
  ];

  $form['ding_place2book']['getEvent'] = [
    '#type' => 'textfield',
    '#title' => t('Place2Book get event URL'),
    '#default_value' => isset($settings->getEvent) ? $settings->getEvent : 'https://apitest.place2book.com/event_makers/:event_maker_id/events/:event_id',
    '#required' => TRUE,
    '#size' => 100,
  ];

  $form['ding_place2book']['updateEvent'] = [
    '#type' => 'textfield',
    '#title' => t('Place2Book update event URL'),
    '#default_value' => isset($settings->updateEvent) ? $settings->updateEvent : 'https://apitest.place2book.com/event_makers/:event_maker_id/events/:event_id',
    '#required' => TRUE,
    '#size' => 100,
  ];

  $form['ding_place2book']['deleteEvent'] = [
    '#type' => 'textfield',
    '#title' => t('Place2Book delete event URL'),
    '#default_value' => isset($settings->deleteEvent) ? $settings->deleteEvent : 'https://apitest.place2book.com/event_makers/:event_maker_id/events/:event_id',
    '#required' => TRUE,
    '#size' => 100,
  ];

  $form['ding_place2book']['createEvent'] = [
    '#type' => 'textfield',
    '#title' => t('Place2Book create event URL'),
    '#default_value' => isset($settings->createEvent) ? $settings->createEvent : 'https://apitest.place2book.com/event_makers/:event_maker_id/events',
    '#required' => TRUE,
    '#size' => 100,
  ];

  $form['ding_place2book']['createPrice'] = [
    '#type' => 'textfield',
    '#title' => t('Place2Book create price URL'),
    '#default_value' => isset($settings->createPrice) ? $settings->createPrice : 'https://apitest.place2book.com/event_makers/:event_maker_id/events/:event_id/prices',
    '#required' => TRUE,
    '#size' => 100,
  ];

  $form['ding_place2book']['getPrice'] = [
    '#type' => 'textfield',
    '#title' => t('Place2Book get price URL'),
    '#default_value' => isset($settings->getPrice) ? $settings->getPrice : 'https://apitest.place2book.com//event_makers/:event_maker_id/events/:event_id/prices/:price_id',
    '#required' => TRUE,
    '#size' => 100,
  ];

  $form['ding_place2book']['updatePrice'] = [
    '#type' => 'textfield',
    '#title' => t('Place2Book update price URL'),
    '#default_value' => isset($settings->updatePrice) ? $settings->updatePrice : 'https://apitest.place2book.com//event_makers/:event_maker_id/events/:event_id/prices/:price_id',
    '#required' => TRUE,
    '#size' => 100,
  ];

  $form['ding_place2book']['deletePrice'] = [
    '#type' => 'textfield',
    '#title' => t('Place2Book delete price URL'),
    '#default_value' => isset($settings->deletePrice) ? $settings->deletePrice : 'https://apitest.place2book.com//event_makers/:event_maker_id/events/:event_id/prices/:price_id',
    '#required' => TRUE,
    '#size' => 100,
  ];

  $form['settings'] = [
    '#type' => 'value',
    '#value' => $settings,
  ];

  $form['path'] = [
    '#type' => 'value',
    '#value' => $path,
  ];

  $form['submit'] = [
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => ['ding_place2book_service_admin_form_submit'],
  ];

  return $form;
}

/**
 * Submit handler for configuration page of p2b library.
 */
function ding_place2book_service_admin_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $data = $values['settings'];
  $path = $values['path'];

  foreach ($values['ding_place2book'] as $attribute => $value) {
    $data->{$attribute} = $value;
  }

  $message = t('Configuration successfully saved');
  $type = 'status';
  try {
    file_put_contents($path, $data->asXml());
  }
  catch (Exception $ex) {
    $message = t('Error. Check reports for additional information.');
    $type = 'erorr';
    watchdog_exception('ding_place2book', $ex, t('Error on writing configs to file.'));
  }
  drupal_set_message($message, $type);
}

/**
 * Form handler for configuration Event makers.
 */
function ding_place2book_defaults_admin_form($form, &$form_state) {
  $p2b = P2b\P2b::getInstance();
  $event_makers = $p2b->getEventMakers();

  $options = [];
  array_map(function ($i) use (&$options) {
    $options[$i->id] = $i->name;
  }, $event_makers);

  $form['ding_p2b_default_event_maker'] = [
    '#type' => 'radios',
    '#title' => t('Default event maker'),
    '#options' => $options,
    '#default_value' => variable_get('ding_p2b_default_event_maker', NULL),
    '#description' => t('It will be used in case when will be missed mappings from library.'),
  ];

  $form['ding_p2b_default_synchronize'] = [
    '#type' => 'checkbox',
    '#title' => t('Default status of syncronisation'),
    '#default_value' => variable_get('ding_p2b_default_synchronize', FALSE),
    '#description' => t('Indicates status of event. If checked, then event will be synchronized with P2b by default.'),
  ];

  $form['ding_p2b_default_kultunaut_export'] = [
    '#type' => 'checkbox',
    '#title' => t('Default status of kultunaut export'),
    '#default_value' => variable_get('ding_p2b_default_kultunaut_export', FALSE),
    '#description' => t('If checked, then kultunaut export will be enabled by default.'),
  ];

  $form['ding_p2b_default_passive'] = [
    '#type' => 'checkbox',
    '#title' => t('Default status of passive attribute'),
    '#default_value' => variable_get('ding_p2b_default_passive', FALSE),
    '#description' => t('If checked, then event will be marked as passive by default.'),
  ];

  $form['ding_p2b_default_capacity'] = [
    '#type' => 'textfield',
    '#title' => t('Default value for capacity of event'),
    '#default_value' => variable_get('ding_p2b_default_capacity', 0),
    '#description' => t('By default event capacity will be set to entered value(0 - unlimited).'),
    '#element_validate' => ['element_validate_integer'],
  ];

  $form['ding_p2b_default_price_name'] = [
    '#type' => 'textfield',
    '#title' => t('Default name of event\'s price.'),
    '#default_value' => variable_get('ding_p2b_default_price_name', 'Adgang'),
    '#description' => t('Represents default name of price.'),
  ];

  return system_settings_form($form);
}


/**
 * Form handler for configuration Event makers.
 */
function ding_place2book_mappings_admin_form($form, &$form_state) {
  $form['#tree'] = TRUE;

  $p2b = P2b\P2b::getInstance();
  $event_makers = $p2b->getEventMakers();
  $options = [];
  array_map(function ($i) use (&$options) {
    $options[$i->id] = $i->name;
  }, $event_makers);
  $form['ding_p2b_library_event_makers'] = [
    '#type' => 'fieldset',
    '#title' => t('Event makers'),
    '#description' => t('Associate each library with some event maker.'),
    '#tree' => TRUE,
  ];
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'ding_library')
    ->execute();
  $defaults = variable_get('ding_p2b_library_event_makers', []);
  if (isset($result['node'])) {
    foreach ($result['node'] as $value) {
      $node = node_load($value->nid);
      $form['ding_p2b_library_event_makers'][$node->nid] = [
        '#type' => 'select',
        '#title' => $node->title,
        '#default_value' => isset($defaults[$node->nid]) ? $defaults[$node->nid] : NULL,
        '#options' => $options,
        '#required' => TRUE,
      ];
    }
  }

  $form['ding_p2b_kultunaut_age_group'] = [
    '#type' => 'fieldset',
    '#title' => t('Kultunaut age group'),
  ];
  $vocabulary = taxonomy_vocabulary_machine_name_load('event_target');
  $terms = taxonomy_get_tree($vocabulary->vid);
  $options = [
    'Alle' => 'Alle',
    'Børn' => 'Børn',
    'Unge' => 'Unge',
    'Voksne' => 'Voksne',
    'Ældre' => 'Ældre',
  ];
  $defaults = variable_get('ding_p2b_kultunaut_age_group', []);
  foreach ($terms as $term) {
    $form['ding_p2b_kultunaut_age_group'][$term->tid] = [
      '#type' => 'select',
      '#title' => $term->name,
      '#description' => t('Associate event target :term with kultunaut age group.', [':term' => $term->name]),
      '#default_value' => isset($defaults[$term->tid]) ? $defaults[$term->tid] : NULL,
      '#options' => $options,
      '#required' => TRUE,
    ];
  }

  $form['ding_p2b_kultunaut_export_category'] = [
    '#type' => 'fieldset',
    '#title' => t('Kultunaut export category'),
  ];
  $vocabulary = taxonomy_vocabulary_machine_name_load('event_category');
  $terms = taxonomy_get_tree($vocabulary->vid);
  $options = _ding_place2book_load_export_category();
  $defaults = variable_get('ding_p2b_kultunaut_export_category', []);
  foreach ($terms as $term) {
    $form['ding_p2b_kultunaut_export_category'][$term->tid] = [
      '#type' => 'select',
      '#title' => $term->name,
      '#description' => t('Associate event category :term with kultunaut category.', [':term' => $term->name]),
      '#default_value' => isset($defaults[$term->tid]) ? $defaults[$term->tid] : NULL,
      '#options' => $options,
      '#required' => TRUE,
    ];
  }

  $form['save'] = [
    '#type' => 'submit',
    '#value' => t('Save'),
  ];

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
  $options = [];
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
