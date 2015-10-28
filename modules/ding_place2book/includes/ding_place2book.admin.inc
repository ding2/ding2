<?php

/**
 * @file ding_place2book.admin.inc
 * Admin forms, page callbacks and related functions.
 */

/**
 * The main settings form.
 */
function ding_place2book_admin_settings_form($form_state) {
  global $user;

  $form = array(
    '#tree' => TRUE,
  );

  $form['ding_place2book_ticketinfo_labels'] = array(
    '#type' => 'item',
    '#title' => t('Labels for display of ticket information'),
    '#markup' => t('<p>5 texts exist for displaying ticket information:</p><ul><li>"The event has already taken place"</li><li>"The event is closed for admission"</li><li>"Ticket sale has not yet started for this event"</li><li>"Sold out"</li><li>"Book a ticket"</li></ul><p>These can all be translated to local needs - just paste the exact texts into the search box at <a href="/admin/config/regional/translate/translate">/admin/config/regional/translate/translate</a>.</p>'),
  );

  // Load default settings
  $defaults = variable_get('ding_place2book', array());

  // Default settings
  $form['ding_place2book'] = array(
    '#type' => 'fieldset',
    '#title' => t('Place2Book service'),
    '#collapsible' => TRUE,
    '#collapsed' => isset($defaults['service_url']) ? TRUE : FALSE,
  );

  $form['ding_place2book']['service_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book service URL'),
    '#default_value' => isset($defaults['service_url']) ? $defaults['service_url'] : 'https://www.place2book.com/da/event_api',
    '#description' => t('Enter a valid Place2book service endpoint, such as https://www.place2book.com/da/event_api'),
    '#required' => TRUE,
    '#size' => 100,
  );

  $form['ding_place2book']['event_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book events URL'),
    '#default_value' => isset($defaults['event_url']) ? $defaults['event_url'] : 'https://www.place2book.com/da/events',
    '#description' => t('Link to events on Place2Book, such as https://www.place2book.com/da/events. It will be used to generate links to the event at Place2Book'),
    '#required' => TRUE,
    '#size' => 100,
  );

  $form['ding_place2book']['api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book default API key'),
    '#default_value' => isset($defaults['api_key']) ? $defaults['api_key'] : '',
    '#required' => TRUE,
    '#description' => t('This is the default API key used when connecting to Place2book. If you provide API key for a specific library (below), events related to that library will use that key instead of the default key.'),
  );

  $form['ding_place2book']['provider_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book provider name'),
    '#default_value' => isset($defaults['provider_name']) ? $defaults['provider_name'] : $user->name,
    '#required' => TRUE,
    '#description' => t('Name sent to Place2Book as the provider'),
  );

  $form['ding_place2book']['provider_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book provider e-mail'),
    '#default_value' => isset($defaults['provider_mail']) ? $defaults['provider_mail'] : $user->mail,
    '#required' => TRUE,
    '#description' => t('E-mail sent to Place2Book as the provider'),
  );

  $form['ding_place2book_libraries'] = array(
    '#type' => 'fieldset',
    '#title' => t('Library API keys'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  // Load default settings
  $defaults = variable_get('ding_place2book_libraries', array());

  // Find all libraries and order them by title.
  // @todo: Replace with EntityFieldQuery.
  $result = db_query("SELECT n.nid, n.title FROM {node} n
                      WHERE type = 'ding_library'
                      ORDER BY title");

  foreach ($result as $record) {
    $form['ding_place2book_libraries'][$record->nid] = array(
      '#type' => 'textfield',
      '#title' => 'API key ' . check_plain($record->title),
      '#default_value' => isset($defaults[$record->nid]) ? $defaults[$record->nid] : '',
      '#description' => t('Optional. If you have several accounts at Place2book, each library can have their own API key. In that case, the base API key will be overridden by the provided key when sending data on events related to this library.'),
    );
  }

  $form['ding_place2book_event_nodes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Place2Book event node defaults'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  // Load default settings
  $defaults = variable_get('ding_place2book_event_nodes', array());

  $form['ding_place2book_event_nodes']['capacity'] = array(
    '#type' => 'textfield',
    '#title' => t('Capacity'),
    '#default_value' => isset($defaults['capacity']) ? $defaults['capacity'] : 0,
    '#size' => 5,
    '#maxlength' => 5,
    '#description' => t('The default capacity for new events. Set to 0 for unlimited capacity.'),
  );

  $form['ding_place2book_event_nodes']['ticket_type'] = array(
    '#type' => 'textfield',
    '#title' => t('Ticket type'),
    '#default_value' => isset($defaults['ticket_type']) ? $defaults['ticket_type'] : 'Adgang',
    '#size' => 30,
    '#maxlength' => 255,
    '#description' => t('The default ticket type for new events.'),
  );

  $form['ding_place2book_event_nodes']['defaults'] = array(
    '#type' => 'checkboxes',
    '#options' => array(
      'maintain_copy' => t('Maintain copy'),
      'kultunaut_export' => t('Kultunaut export'),
      'passive' => t('Passive event'),
    ),
    '#default_value' => isset($defaults['defaults']) ? $defaults['defaults'] : array(),
  );

  return system_settings_form($form);
}

/**
 * The kultunaut form.
 */
function ding_place2book_kultunaut_form($form_state) {
  $form = array(
    '#tree' => TRUE,
  );

  $form['ding_place2book_category_mappings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mappings of Event Category to Kultunaut categories'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $kultunaut_category_options = array('' => t('Choose')) + place2book_get_kultunaut_categories();

  // Find all terms in the event category vocabulary
  // @todo: Please use the Drupal API to retrieve such information.
  $result = db_query("SELECT t.tid, t.name FROM {taxonomy_term_data} t JOIN {taxonomy_vocabulary} v
                      ON t.vid = v.vid
                      WHERE v.machine_name = 'event_category'
                      ORDER BY name");

  // Load default settings
  $defaults = variable_get('ding_place2book_category_mappings', array());

  foreach ($result as $record) {
    $form['ding_place2book_category_mappings'][$record->tid] = array(
      '#type' => 'select',
      '#title' => 'Term ' . check_plain($record->name),
      '#default_value' => isset($defaults[$record->tid]) ? $defaults[$record->tid] : '',
      '#options' => $kultunaut_category_options,
      '#description' => t('Optional. Select the kultunaut category to map the Ding! event category term to.'),
    );
  }

  $form['ding_place2book_target_mappings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mappings of Event Target to Kultunaut Target'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $kultunaut_target_options = array('' => t('Choose'), 'Alle' => 'Alle', 'Børn' => 'Børn', 'Unge' => 'Unge', 'Voksne' => 'Voksne', 'Ældre' => 'Ældre');

  // Find all terms in the event target vocabulary
  // @todo: Please use the Drupal API to retrieve such information.
  $result = db_query("SELECT t.tid, t.name FROM {taxonomy_term_data} t JOIN {taxonomy_vocabulary} v
                      ON t.vid = v.vid
                      WHERE v.machine_name = 'event_target'
                      ORDER BY name");

  // Load default settings
  $defaults = variable_get('ding_place2book_target_mappings', array());

  foreach ($result as $record) {
    $form['ding_place2book_target_mappings'][$record->tid] = array(
      '#type' => 'select',
      '#title' => 'Term ' . check_plain($record->name),
      '#default_value' => isset($defaults[$record->tid]) ? $defaults[$record->tid] : '',
      '#options' => $kultunaut_target_options,
      '#description' => t('Optional. Select the kultunaut target to map the Ding! event target term to.'),
    );
  }

  $form['ding_place2book_kultunaut_categories'] = array(
    '#type' => 'fieldset',
    '#title' => t('Kultunaut categories'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  // Load default settings
  $defaults = variable_get('ding_place2book_kultunaut_categories', array('kultunaut_cat_array' => ding_place2book_kultunaut_cat_json()));

  $form['ding_place2book_kultunaut_categories']['kultunaut_cat_array'] = array(
      '#type' => 'textarea',
      '#title' => t('Kultunaut category terms'),
      '#default_value' => $defaults['kultunaut_cat_array'],
      '#rows' => 5,
      // @todo: It seems unreasonable to require administrators to enter valid
      // JSON. Can we provide them with a format that is more accessible to
      // non-developers?
      '#description' => t("A valid <a target=\"_blank\" href=\"http://en.wikipedia.org/wiki/JSON\">JSON</a> array containing Kultunaut category terms. The included default should not have to be changed - the values have been derived from the Kultunaut category term definitions at <a target=\"_blank\" href=\"http://www.kultunaut.dk/perl/export/nautgenrerxml\">http://www.kultunaut.dk/perl/export/nautgenrerxml</a>."),
      '#required' => TRUE,
    );

  return system_settings_form($form);
}

function ding_place2book_kultunaut_form_validate($form, &$form_state) {
  $field = $form_state['values']['ding_place2book_kultunaut_categories']['kultunaut_cat_array'];
  if (!is_array(json_decode($field, TRUE))) {
    form_set_error($field, t('Kultunaut categories has malformed JSON: Does not transform to array.'));
  }
}

/*
 * Returns a JSON string containing the default Kultunaut category terms found at http://www.kultunaut.dk/perl/export/nautgenrerxml
 */
function ding_place2book_kultunaut_cat_json() {
  // @todo: Why not retrieve this from
  // http://www.kultunaut.dk/perl/export/nautgenrerxml instead of maintaining
  // a copy here?
  $json  = '{
    "Andet/Ukendt":"(Musik) Andet/Ukendt",
    "Rock/Pop":"(Musik) Rock/Pop",
    "Elektronisk":"(Musik) Elektronisk",
    "Club/DJ":"(Musik) Club/DJ",
    "Funk/Blues/R&B":"(Musik) Funk/Blues/R&B",
    "Jazz":"(Musik) Jazz",
    "Verdensmusik/Latin":"(Musik) Verdensmusik/Latin",
    "Folk/Vise/Country":"(Musik) Folk/Vise/Country",
    "Dansktop/underholdning":"(Musik) Dansktop/underholdning",
    "Hip-Hop/Reggae":"(Musik) Hip-Hop/Reggae",
    "Gospel/Kor/Fællessang":"(Musik) Gospel/Kor/Fællessang",
    "Klassisk":"(Musik) Klassisk",
    "Dansegulv":"(Musik) Dansegulv",
    "Anden forestilling":"(Teater) Anden forestilling",
    "Ballet":"(Teater) Ballet",
    "Dans":"(Teater) Dans",
    "Musical":"(Teater) Musical",
    "Revy/kabaret":"(Teater) Revy/kabaret",
    "Opera/Operette":"(Teater) Opera/Operette",
    "Show/stand up":"(Teater) Show/stand up",
    "Skuespil":"(Teater) Skuespil",
    "Blandet/Ukendt":"(Udstilling) Blandet/Ukendt",
    "Arkitektur":"(Udstilling) Arkitektur",
    "Billedkunst":"(Udstilling) Billedkunst",
    "Foto":"(Udstilling) Foto",
    "Historisk":"(Udstilling) Historisk",
    "Kunsthåndværk":"(Udstilling) Kunsthåndværk",
    "Omvisning":"(Udstilling) Omvisning",
    "Skulptur":"(Udstilling) Skulptur",
    "Messe":"(Udstilling) Messe",
    "Installation":"(Udstilling) Installation",
    "Fernisering":"(Udstilling) Fernisering",
    "Andre Film":"(Film) Andre Film",
    "Komedie/Romantik":"(Film) Komedie/Romantik",
    "Dokumentar":"(Film) Dokumentar",
    "Action/Drama":"(Film) Action/Drama",
    "Tegnefilm/Animation":"(Film) Tegnefilm/Animation",
    "Science Fiction":"(Film) Science Fiction",
    "Thriller/Gyser":"(Film) Thriller/Gyser",
    "Familiefilm":"(Film) Familiefilm",
    "Løb/atletikstævne":"(Sportsturnering) Løb/atletikstævne",
    "Badmintonkamp":"(Sportsturnering) Badmintonkamp",
    "Basketballkamp":"(Sportsturnering) Basketballkamp",
    "Cykelløb":"(Sportsturnering) Cykelløb",
    "Fodboldkamp":"(Sportsturnering) Fodboldkamp",
    "Golfturnering":"(Sportsturnering) Golfturnering",
    "Gymnastikstævne":"(Sportsturnering) Gymnastikstævne",
    "Håndboldkamp":"(Sportsturnering) Håndboldkamp",
    "Ishockeykamp":"(Sportsturnering) Ishockeykamp",
    "Boksestævne":"(Sportsturnering) Boksestævne",
    "Motorsport":"(Sportsturnering) Motorsport",
    "Hestesport":"(Sportsturnering) Hestesport",
    "Svømmestævne":"(Sportsturnering) Svømmestævne",
    "Kapsejlads":"(Sportsturnering) Kapsejlads",
    "Øvrige sportsturneringer":"(Sportsturnering) Øvrige sportsturneringer",
    "Bordtennis":"(Motion) Bordtennis",
    "Løbetræning/jogging":"(Motion) Løbetræning/jogging",
    "Ketchersport":"(Motion) Ketchersport",
    "Cykeltur":"(Motion) Cykeltur",
    "Fodboldtræning":"(Motion) Fodboldtræning",
    "Gymnastik/aerobic":"(Motion) Gymnastik/aerobic",
    "Håndboldtræning":"(Motion) Håndboldtræning",
    "Skøjteløb":"(Motion) Skøjteløb",
    "Kampsporttræning":"(Motion) Kampsporttræning",
    "Ridning":"(Motion) Ridning",
    "Svømmetræning":"(Motion) Svømmetræning",
    "Sejlads/roning":"(Motion) Sejlads/roning",
    "Vandretur/stavgang":"(Motion) Vandretur/stavgang",
    "Danseundervisning":"(Motion) Danseundervisning",
    "Fitness/styrketræning":"(Motion) Fitness/styrketræning",
    "Skate/rulleskøjte":"(Motion) Skate/rulleskøjte",
    "Skydning":"(Motion) Skydning",
    "Andet boldspil":"(Motion) Andet boldspil",
    "Andet motionstilbud":"(Motion) Andet motionstilbud",
    "Andet":"(Diverse) Andet",
    "Auktioner":"(Diverse) Auktioner",
    "Banko":"(Diverse) Banko",
    "Ekskursion":"(Diverse) Ekskursion",
    "Foredrag":"(Diverse) Foredrag",
    "Konference/seminar":"(Diverse) Konference/seminar",
    "Gastronomi":"(Diverse) Gastronomi",
    "Lyrik/oplæsning":"(Diverse) Lyrik/oplæsning",
    "Marked/byfest":"(Diverse) Marked/byfest",
    "Møder":"(Diverse) Møder",
    "Natur":"(Diverse) Natur",
    "Undervisning":"(Diverse) Undervisning",
    "Gudstjeneste":"(Diverse) Gudstjeneste",
    "Workshop":"(Diverse) Workshop",
    "Shopping":"(Diverse) Shopping",
    "Medlemsmøde":"(Lukket) Medlemsmøde",
    "Koncert":"(Lukket) Koncert",
    "Generalforsamling":"(Lukket) Generalforsamling",
    "Ferie/ombygning":"(Lukket) Ferie/ombygning",
    "Intern meddelelse":"(Lukket) Intern meddelelse",
    "Del af aktivitet":"(Lukket) Del af aktivitet"
  }';
  return $json;
}

/*
 * Returns an array of all Kultunaut category terms
 */
function place2book_get_kultunaut_categories() {
  $categories = array();
  $var_kultunaut = variable_get('ding_place2book_kultunaut_categories', array('kultunaut_cat_array' => ding_place2book_kultunaut_cat_json()));

  if (is_array(json_decode($var_kultunaut['kultunaut_cat_array'], TRUE))) {
    $categories = json_decode($var_kultunaut['kultunaut_cat_array'], TRUE);
  }

  return $categories;
}
