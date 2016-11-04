<?php
/**
 * Implements hook_form_alter().
 */
function ddbasic_form_alter(&$form, &$form_state, $form_id) {
  // Reservations & Bookmarks, group select-all button and action-buttons in div.
  if(
    $form_id == 'ding_reservation_reservations_ready_form' ||
    $form_id == 'ding_reservation_reservations_notready_form' ||
    $form_id == 'ding_bookmark_remove_form' ||
    $form_id == 'ding_bookmark_import_form'
  ) {
    $form['title']['#title'] = "Vælg alle";
    $form['title']['#weight'] = "-30";
    $form['title']['#prefix'] = "<div class='actions-container'><div class='select-all'>";
    $form['title']['#suffix'] = "</div>";
    $form['actions_top']['#suffix'] = "</div></div>";
    $form['actions_top']['delete']['#prefix'] = "<div class='delete-reservations'>";
    if(isset($form['actions_top']['update'])) {
      $form['actions_top']['update']['#prefix'] = "<div class='update-reservations'>";
    }
  }

  // Change all-text in select list in exposed filter for e-resources
  if($form['#id'] == 'views-exposed-form-ding-eresource-ding-eresource-list') {
    if (!empty($form['access']['#options']['All'])) {
      $form['access']['#options']['All'] = t('Access: All e-materials');
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ddbasic_form_ding_library_library_list_select_library_alter(&$form, &$form_state, $form_id) {
  $links = array();

  foreach ($form['select_library']['#options'] as $href => $title) {
    $links[] = array(
      'title' => $title,
      'href' => $href,
      'attributes' => array('class' => array('list-item')),
    );
  }

  $form['select_library'] = array(
    '#theme' => 'links',
    '#links' => $links,
    '#attributes' => array(
      'class' => array('list-items'),
    ),
    '#heading' => array(
      'text' => t('Select library'),
      'level' => 'h2',
      'class' => array('list-title', 'sub-menu-title'),
    ),
    '#prefix' => '<div class="select-list">',
    '#suffix' => '</div>',
  );
  unset($form['submit']);
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ddbasic_form_search_block_form_alter(&$form, &$form_state, $form_id) {
  $form['search_block_form']['#attributes']['placeholder'] = t('Search the library');
  $form['search_block_form']['#title'] = t('Search the library database and the website');

  //Placeholder on extended form.
  if(ding_ddbasic_is_ting_search_extend_form()) {
    $form['search_field']['search_block_form']['#attributes']['placeholder'] = t('Search the library');
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ddbasic_form_user_login_block_alter(&$form, &$form_state, $form_id) {

  $form['#attributes']['class'][] = 'user-login-form';

  $form['intro_text']['#markup'] = '<div class="intro-text"><div class="lead">' . t('If you want to see what you have borrowed, reserve books or edit your user profile, you must be logged in.') . '</div>';

  $user_signup_link = ddbasic_theme_setting('user_signup_link');
  if (!empty($user_signup_link)) {
    $form['intro_text']['#markup'] .= '<div class="text">' . t('If you are not a registered user, you can register ') . l(t('here'), $user_signup_link, array('external' => TRUE)) . t(', or you can sign up in person at your local library.') . '</div></div>';
  } else {
    $form['intro_text']['#markup'] .= '<div class="text">' . t('If you are not a registered user, you can sign up in person at your local library.') . '</div></div>';
  }
  $form['intro_text']['#weight'] = -9999;

  $form['close']['#markup'] = '<div class="user-login-container"><div class="close-user-login"></div>';
  $form['close']['#weight'] = -9998;

  $form['name']['#title'] = t('Loan or social security number');
  $form['name']['#attributes']['placeholder'] = t('Loan/social security number (without dash)');
  $form['name']['#type'] = 'password';

  $form['pass']['#title'] = t('Pincode');
  $form['pass']['#attributes']['placeholder'] = t('Pincode (4 digits)');

  unset($form['links']);
  //$form['links']['#weight'] = 9999;
  //$form['links']['#prefix'] = '<div class="form-links">';
  //$form['links']['#suffix'] = '</div></div>';

  $form['actions']['submit']['#prefix'] = '<div class="submit-button-with-icon"><div class="color-and-icon"></div>';
  $form['actions']['submit']['#suffix'] = '</div>';

  // Add NemID if the gatewayf module exists.
  if (module_exists('ding_gatewayf')) {
    $form['#attributes']['class'][] = 'has-nemid-login';
    $block = module_invoke('ding_gatewayf', 'block_view', 'login');
    $block->content['#link']['#text'] = t('Login with');
    $form['actions']['nemid'] = array('#markup' => render($block->content));
  }

  // Temporary hack to get rid of open id links.
  unset($form['openid_links']);
  unset($form['#attached']['js']);

}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ddbasic_form_user_login_alter(&$form, &$form_state, $form_id) {

  $form['#attributes']['class'][] = 'user-login-form';

  $form['intro_text']['#markup'] = '<div class="intro-text"><div class="lead">' . t('If you want to see what you have borrowed, reserve books or edit your user profile, you must be logged in.') . '</div>';

  $user_signup_link = ddbasic_theme_setting('user_signup_link');
  if (!empty($user_signup_link)) {
    $form['intro_text']['#markup'] .= '<div class="text">' . t('If you are not a registered user, you can register ') . l(t('here'), $user_signup_link, array('external' => TRUE)) . t(', or you can sign up in person at your local library.') . '</div></div>';
  } else {
    $form['intro_text']['#markup'] .= '<div class="text">' . t('If you are not a registered user, you can sign up in person at your local library.') . '</div></div>';
  }
  $form['intro_text']['#weight'] = -9999;

  $form['container']['#markup'] = '<div class="user-login-container">';
  $form['container']['#weight'] = -9998;

  $form['name']['#title'] = t('Loan or social security number');
  $form['name']['#attributes']['placeholder'] = t('Loan/social security number (without dash)');
  $form['name']['#type'] = 'password';

  $form['pass']['#title'] = t('Pincode');
  $form['pass']['#attributes']['placeholder'] = t('Pincode (4 digits)');

  unset($form['links']);
  //$form['links']['#weight'] = 9999;
  //$form['links']['#prefix'] = '<div class="form-links">';
  //$form['links']['#suffix'] = '</div></div>';

  $form['actions']['submit']['#prefix'] = '<div class="submit-button-with-icon"><div class="color-and-icon"></div>';
  $form['actions']['submit']['#suffix'] = '</div>';

}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ddbasic_form_ding_facetbrowser_form_alter(&$form, &$form_state, $form_id) {
  foreach (element_children($form) as $key) {
    $item = &$form[$key];
    if($item['#type'] === 'fieldset') {
      $item['#collapsible'] = TRUE;
      $item['#collapsed'] = TRUE;
    }
  }
}

/**
 * Implements hook_preprocess_select().
 *
 * Adds wrapper div to all select form elements, for better styling in FF
 */
function ddbasic_select($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'size'));
  _form_set_class($element, array('form-select'));

  return '<div class="select-wrapper"><select' . drupal_attributes($element['#attributes']) . '>' . form_select_options($element) . '</select></div>';
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ddbasic_form_ding_loan_loans_form_alter(&$form, &$form_state, $form_id) {
  $form['actions_top']['renew_all'] = array(
    '#type' => 'markup',
    '#prefix' => '<div class="renew-all action-all action-button">',
    '#markup' => '<a href="#">' . t('Forny alle') . '</a>',
    '#suffix' => '</div>',
  );
  // Create url to ting object
  foreach ($form['loans'] as &$loans) {
    foreach ($loans as &$loan) {
      if ($loan['#type'] == 'material_item') {
        $id = $loan['#id'];
        $entity = $form['items']['#value'][$id]->entity;
        $uri_object = entity_uri('ting_object', $entity);
        $loan['#information']['ting_object_url_object']['url'] = url($uri_object['path']);
      }
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ddbasic_form_ding_reservation_reservations_ready_form_alter(&$form, &$form_state, $form_id) {
  $form['actions_top']['delete_all'] = array(
    '#type' => 'markup',
    '#prefix' => '<div class="delete-all action-all action-button">',
    '#markup' => '<a href="#">' . t('Delete all') . '</a>',
    '#suffix' => '</div>',
  );
  // Create url to ting object
  foreach ($form['reservations'] as &$reservation) {
    $id = $reservation['#id'];
    $entity = $form_state['build_info']['args'][0][$id]->entity;
    $uri_object = entity_uri('ting_object', $entity);
    $reservation['#information']['ting_object_url_object']['url'] = url($uri_object['path']);
    $reservation['#information']['ting_object_url_object']['class'] = 'url';
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ddbasic_form_ding_reservation_reservations_notready_form_alter(&$form, &$form_state, $form_id) {
  $form['actions_top']['delete_all'] = array(
    '#type' => 'markup',
    '#prefix' => '<div class="delete-all action-all action-button">',
    '#markup' => '<a href="#">' . t('Delete all') . '</a>',
    '#suffix' => '</div>',
  );
  // Create url to ting object
  foreach ($form['reservations'] as &$reservation) {
    $id = $reservation['#id'];
    $entity = $form_state['build_info']['args'][0][$id]->entity;
    $uri_object = entity_uri('ting_object', $entity);
    $reservation['#information']['ting_object_url_object']['url'] = url($uri_object['path']);
    $reservation['#information']['ting_object_url_object']['class'] = 'url';
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ddbasic_form_ding_bookmark_remove_form_alter(&$form, &$form_state, $form_id) {
  $form['actions_top']['delete_all'] = array(
    '#type' => 'markup',
    '#prefix' => '<div class="delete-all action-all action-button">',
    '#markup' => '<a href="#">' . t('Delete all') . '</a>',
    '#suffix' => '</div>',
  );
  foreach ($form_state['build_info']['args'][0] as $bookmark) {
    $uri_object = entity_uri('ting_object', $bookmark);
    $form['bookmarks'][$bookmark->ding_entity_id]['#information']['ting_object_url_object']['url'] = url($uri_object['path']);
    $form['bookmarks'][$bookmark->ding_entity_id]['#information']['ting_object_url_object']['class'] = 'url';
  }
}
