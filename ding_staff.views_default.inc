<?php
/**
 * @file
 * ding_staff.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ding_staff_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ding_staff';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'profile';
  $view->human_name = 'Ding staff';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Staff';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'footable';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['columns'] = array(
    'user' => 'user',
    'field_ding_staff_forename' => 'field_ding_staff_forename',
    'field_ding_staff_surname' => 'field_ding_staff_surname',
    'field_ding_staff_position' => 'field_ding_staff_position',
    'field_ding_staff_department' => 'field_ding_staff_department',
    'field_ding_staff_library' => 'field_ding_staff_library',
    'field_ding_staff_phone' => 'field_ding_staff_phone',
    'field_ding_staff_email' => 'field_ding_staff_email',
  );
  $handler->display->display_options['style_options']['default'] = 'field_ding_staff_surname';
  $handler->display->display_options['style_options']['info'] = array(
    'user' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_staff_forename' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_staff_surname' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_staff_position' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_staff_department' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_staff_library' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_staff_phone' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_staff_email' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['footable'] = array(
    'expand' => 'field_ding_staff_surname',
    'hide' => array(
      'user' => array(
        'phone' => 0,
        'tablet' => 0,
      ),
      'field_ding_staff_forename' => array(
        'phone' => 0,
        'tablet' => 0,
      ),
      'field_ding_staff_surname' => array(
        'phone' => 0,
        'tablet' => 0,
      ),
      'field_ding_staff_position' => array(
        'phone' => 'phone',
        'tablet' => 'tablet',
      ),
      'field_ding_staff_department' => array(
        'phone' => 'phone',
        'tablet' => 0,
      ),
      'field_ding_staff_library' => array(
        'phone' => 'phone',
        'tablet' => 'tablet',
      ),
      'field_ding_staff_phone' => array(
        'phone' => 0,
        'tablet' => 0,
      ),
      'field_ding_staff_email' => array(
        'phone' => 'phone',
        'tablet' => 0,
      ),
    ),
  );
  /* Field: User uid (excluded) */
  $handler->display->display_options['fields']['user']['id'] = 'user';
  $handler->display->display_options['fields']['user']['table'] = 'profile';
  $handler->display->display_options['fields']['user']['field'] = 'user';
  $handler->display->display_options['fields']['user']['ui_name'] = 'User uid (excluded)';
  $handler->display->display_options['fields']['user']['label'] = '';
  $handler->display->display_options['fields']['user']['exclude'] = TRUE;
  $handler->display->display_options['fields']['user']['element_label_colon'] = FALSE;
  /* Field: Forename (excluded) */
  $handler->display->display_options['fields']['field_ding_staff_forename']['id'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['table'] = 'field_data_field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['field'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['ui_name'] = 'Forename (excluded)';
  $handler->display->display_options['fields']['field_ding_staff_forename']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_forename']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_forename']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_forename']['alter']['path'] = 'staff/[user]';
  $handler->display->display_options['fields']['field_ding_staff_forename']['element_label_colon'] = FALSE;
  /* Field: Surname Forename (Link) */
  $handler->display->display_options['fields']['field_ding_staff_surname']['id'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['field'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['ui_name'] = 'Surname Forename (Link)';
  $handler->display->display_options['fields']['field_ding_staff_surname']['label'] = 'Name';
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['text'] = '[field_ding_staff_surname], [field_ding_staff_forename]';
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['path'] = 'staff/[user]';
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_label_colon'] = FALSE;
  /* Field: Profile: Position */
  $handler->display->display_options['fields']['field_ding_staff_position']['id'] = 'field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['table'] = 'field_data_field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['field'] = 'field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_label_colon'] = FALSE;
  /* Field: Profile: Department */
  $handler->display->display_options['fields']['field_ding_staff_department']['id'] = 'field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['table'] = 'field_data_field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['field'] = 'field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_department']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_ding_staff_department']['delta_offset'] = '0';
  /* Field: Profile: Library */
  $handler->display->display_options['fields']['field_ding_staff_library']['id'] = 'field_ding_staff_library';
  $handler->display->display_options['fields']['field_ding_staff_library']['table'] = 'field_data_field_ding_staff_library';
  $handler->display->display_options['fields']['field_ding_staff_library']['field'] = 'field_ding_staff_library';
  $handler->display->display_options['fields']['field_ding_staff_library']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_library']['click_sort_column'] = 'gid';
  $handler->display->display_options['fields']['field_ding_staff_library']['delta_offset'] = '0';
  /* Field: Profile: Phone */
  $handler->display->display_options['fields']['field_ding_staff_phone']['id'] = 'field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['table'] = 'field_data_field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['field'] = 'field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_label_colon'] = FALSE;
  /* Field: Profile: Email */
  $handler->display->display_options['fields']['field_ding_staff_email']['id'] = 'field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['table'] = 'field_data_field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['field'] = 'field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_label_colon'] = FALSE;
  /* Sort criterion: Profile: Surname (field_ding_staff_surname) */
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['id'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['field'] = 'field_ding_staff_surname_value';
  /* Filter criterion: Profile: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'profile';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'staff' => 'staff',
  );

  /* Display: Staff list */
  $handler = $view->new_display('panel_pane', 'Staff list', 'ding_staff_list');

  /* Display: Library staff list */
  $handler = $view->new_display('panel_pane', 'Library staff list', 'ding_staff_list_library');
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User uid (excluded) */
  $handler->display->display_options['fields']['user']['id'] = 'user';
  $handler->display->display_options['fields']['user']['table'] = 'profile';
  $handler->display->display_options['fields']['user']['field'] = 'user';
  $handler->display->display_options['fields']['user']['ui_name'] = 'User uid (excluded)';
  $handler->display->display_options['fields']['user']['label'] = '';
  $handler->display->display_options['fields']['user']['exclude'] = TRUE;
  $handler->display->display_options['fields']['user']['element_label_colon'] = FALSE;
  /* Field: Forename (excluded) */
  $handler->display->display_options['fields']['field_ding_staff_forename']['id'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['table'] = 'field_data_field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['field'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['ui_name'] = 'Forename (excluded)';
  $handler->display->display_options['fields']['field_ding_staff_forename']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_forename']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_forename']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_forename']['alter']['path'] = 'staff/[user]';
  $handler->display->display_options['fields']['field_ding_staff_forename']['element_label_colon'] = FALSE;
  /* Field: Surname Forename (Link) */
  $handler->display->display_options['fields']['field_ding_staff_surname']['id'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['field'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['ui_name'] = 'Surname Forename (Link)';
  $handler->display->display_options['fields']['field_ding_staff_surname']['label'] = 'Name';
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['text'] = '[field_ding_staff_surname], [field_ding_staff_forename]';
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['path'] = 'staff/[user]';
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_label_colon'] = FALSE;
  /* Field: Profile: Position */
  $handler->display->display_options['fields']['field_ding_staff_position']['id'] = 'field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['table'] = 'field_data_field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['field'] = 'field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_label_colon'] = FALSE;
  /* Field: Profile: Department */
  $handler->display->display_options['fields']['field_ding_staff_department']['id'] = 'field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['table'] = 'field_data_field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['field'] = 'field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_department']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_ding_staff_department']['delta_offset'] = '0';
  /* Field: Profile: Phone */
  $handler->display->display_options['fields']['field_ding_staff_phone']['id'] = 'field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['table'] = 'field_data_field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['field'] = 'field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_label_colon'] = FALSE;
  /* Field: Profile: Email */
  $handler->display->display_options['fields']['field_ding_staff_email']['id'] = 'field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['table'] = 'field_data_field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['field'] = 'field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Profile: Library (field_ding_staff_library:nid) */
  $handler->display->display_options['arguments']['ding_library_nid']['id'] = 'ding_library_nid';
  $handler->display->display_options['arguments']['ding_library_nid']['table'] = 'field_data_field_ding_staff_library';
  $handler->display->display_options['arguments']['ding_library_nid']['field'] = 'ding_library_nid';
  $handler->display->display_options['arguments']['ding_library_nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['ding_library_nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['ding_library_nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['ding_library_nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Profile: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'profile';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'staff' => 'staff',
  );
  $handler->display->display_options['argument_input'] = array(
    'ding_library_nid' => array(
      'type' => 'panel',
      'context' => 'entity:comment.author',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Profile: Library (field_ding_staff_library:nid)',
    ),
  );
  $translatables['ding_staff'] = array(
    t('Master'),
    t('Staff'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('.'),
    t(','),
    t('Name'),
    t('[field_ding_staff_surname], [field_ding_staff_forename]'),
    t('Position'),
    t('Department'),
    t('Library'),
    t('Phone'),
    t('Email'),
    t('Staff list'),
    t('View panes'),
    t('Library staff list'),
    t('All'),
  );
  $export['ding_staff'] = $view;

  return $export;
}
