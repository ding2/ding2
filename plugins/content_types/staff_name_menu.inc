<?php
/**
 * @file
 * Creates a menu with links of staff grouped by libraries.
 */

$plugin = array(
  'title' => t('Ding staff name menu'),
  'description' => t('Generates links menu to staff members and their libraries.'),
  'single' => TRUE,
  'edit form' => 'ding_staff_name_menu_content_type_edit_form',
  'render callback' => 'ding_staff_name_menu_content_type_render',
  'category' => t('Ding!'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'defaults' => array(
    'menu_levels' => 1,
  ),
);

/**
 * Implements hook_ID_content_type_render().
 */
function ding_staff_name_menu_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();
  $selected_name = FALSE;
  $items = array();

  // Default link of 'All libraries' links to staff list page. Set active class
  // if no library is given in the context.
  $options = array('attributes' => array('class' => array('active')));
  if (isset($context->data)) {
    $selected_name = $context->data;
    $options = array();
  }

  // Select libraries with connected staff
  $results = db_query("SELECT 
    n.nid,
    n.title,
    u.uid,
    fs.field_ding_staff_surname_value AS surname,
    ff.field_ding_staff_forename_value AS forename
    FROM users u
    JOIN users_roles ur ON u.uid = ur.uid
    JOIN role r ON ur.rid = r.rid 
    JOIN profile p ON u.uid = p.uid
    JOIN og_membership om ON p.pid = om.etid 
    JOIN field_data_field_ding_staff_surname fs ON p.pid = fs.entity_id
    LEFT JOIN field_data_field_ding_staff_forename ff ON p.pid = ff.entity_id
    JOIN node n ON om.gid = n.nid
    WHERE r.name = 'staff'
    AND p.type = 'ding_staff_profile'
    ORDER BY n.title, fs.field_ding_staff_surname_value, ff.field_ding_staff_forename_value");

  // Create links for each library found to that libraries staff page.
  $currentlib = NULL;
  foreach ($results as $row) {
    // Mark this name as active if matching the user coming from context
    $options = array();
    if ($selected_name && $selected_name->uid == $row->uid) {
      $options = array('attributes' => array('class' => array('active')));
    }
    if ($conf['menu_levels'] == 2) {
      if ($currentlib == NULL || $row->nid != $currentlib['id']) {
        $currentlib = array(
          'id' => $row->nid,
          'data' => l($row->title, 'bibliotek/' . $row->nid),
          'children' => array(),
        );
        $items[$row->nid] = $currentlib;
      }
      $items[$row->nid]['children'][] = l($row->surname . ', ' . $row->forename, 'user/' . $row->uid, $options);
    } else {
      $items[$row->nid] = l($row->title, 'bibliotek/' . $row->nid, $options);
    }
  }

  $block->content = array(
    '#theme' => 'item_list',
    '#items' => $items,
    '#attributes' => array(
      'class' => array('sub-menu'),
    ),
  );

  return $block;
}

/**
 * Returns an edit form for the content type.
 *
 */
function ding_staff_name_menu_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
 
  $form['menu_levels'] = array(
    '#title' => t('Menu levels to show'),
    '#description' => t('1 level deep shows library links, 2 levels deep shows staff name links in 2nd level. Defaults to 1.'),
    '#type' => 'select',
    '#options' => array(
      1 => t('1 level (just library links)'),
      2 => t('2 levels - (staff names under libraries)'),
    ),
    '#default_value' => $conf['menu_levels'],
    '#required' => TRUE,
  );
 
  return $form;
}

/**
 * Submit handler for the content type.
 */
function ding_staff_name_menu_content_type_edit_form_submit($form, &$form_state) {
  // Copy everything from our defaults.
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}