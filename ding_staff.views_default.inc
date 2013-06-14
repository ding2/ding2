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
    'field_ding_staff_image' => 'field_ding_staff_surname',
    'field_ding_staff_surname' => 'field_ding_staff_surname',
    'field_ding_staff_position' => 'field_ding_staff_position',
    'field_ding_staff_department' => 'field_ding_staff_department',
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
    'field_ding_staff_image' => array(
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
      'field_ding_staff_image' => array(
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
  /* Field: Profile: Image */
  $handler->display->display_options['fields']['field_ding_staff_image']['id'] = 'field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['table'] = 'field_data_field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['field'] = 'field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_staff_image']['type'] = 'cs_adaptive_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['settings'] = array(
    'image_link' => '',
    'styles' => array(
      'breakpoint_1' => '',
      'style_1' => '',
      'breakpoint_2' => '',
      'style_2' => '',
      'max_style' => 'ding_staff_thumbnail',
      'fallback_style' => 'ding_staff_thumbnail',
    ),
  );
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
  $handler->display->display_options['fields']['field_ding_staff_department']['separator'] = '<br/>';
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
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'footable';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['columns'] = array(
    'user' => 'user',
    'field_ding_staff_forename' => 'field_ding_staff_forename',
    'field_ding_staff_image' => 'field_ding_staff_surname',
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
    'field_ding_staff_image' => array(
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
      'field_ding_staff_image' => array(
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
        'tablet' => 'tablet',
      ),
      'field_ding_staff_library' => array(
        'phone' => 'phone',
        'tablet' => 0,
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
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;

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
  /* Field: Profile: Image */
  $handler->display->display_options['fields']['field_ding_staff_image']['id'] = 'field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['table'] = 'field_data_field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['field'] = 'field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_staff_image']['type'] = 'cs_adaptive_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['settings'] = array(
    'image_link' => '',
    'styles' => array(
      'breakpoint_1' => '',
      'style_1' => '',
      'breakpoint_2' => '',
      'style_2' => '',
      'max_style' => 'ding_staff_thumbnail',
      'fallback_style' => 'ding_staff_thumbnail',
    ),
  );
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

  /* Display: Library departments list */
  $handler = $view->new_display('panel_pane', 'Library departments list', 'ding_staff_library_departments');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'footable';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_ding_staff_department',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['columns'] = array(
    'field_ding_staff_department' => 'field_ding_staff_department',
    'user' => 'user',
    'field_ding_staff_forename' => 'field_ding_staff_forename',
    'field_ding_staff_image' => 'field_ding_staff_surname',
    'field_ding_staff_surname' => 'field_ding_staff_surname',
    'field_ding_staff_position' => 'field_ding_staff_position',
    'field_ding_staff_phone' => 'field_ding_staff_phone',
    'field_ding_staff_email' => 'field_ding_staff_email',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_ding_staff_department' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
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
    'field_ding_staff_image' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_staff_surname' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_staff_position' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_staff_phone' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_staff_email' => array(
      'sortable' => 0,
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
      'field_ding_staff_department' => array(
        'phone' => 'phone',
        'tablet' => 0,
      ),
      'user' => array(
        'phone' => 0,
        'tablet' => 0,
      ),
      'field_ding_staff_forename' => array(
        'phone' => 0,
        'tablet' => 0,
      ),
      'field_ding_staff_image' => array(
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
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Profile: Department (field_ding_staff_department) */
  $handler->display->display_options['relationships']['field_ding_staff_department_tid']['id'] = 'field_ding_staff_department_tid';
  $handler->display->display_options['relationships']['field_ding_staff_department_tid']['table'] = 'field_data_field_ding_staff_department';
  $handler->display->display_options['relationships']['field_ding_staff_department_tid']['field'] = 'field_ding_staff_department_tid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Department (for group header)(excluded) */
  $handler->display->display_options['fields']['field_ding_staff_department']['id'] = 'field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['table'] = 'field_data_field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['field'] = 'field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['ui_name'] = 'Department (for group header)(excluded)';
  $handler->display->display_options['fields']['field_ding_staff_department']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_department']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_department']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_department']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_ding_staff_department']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_department']['delta_offset'] = '0';
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
  /* Field: Profile: Image */
  $handler->display->display_options['fields']['field_ding_staff_image']['id'] = 'field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['table'] = 'field_data_field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['field'] = 'field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_staff_image']['type'] = 'cs_adaptive_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['settings'] = array(
    'image_link' => '',
    'styles' => array(
      'breakpoint_1' => '',
      'style_1' => '',
      'breakpoint_2' => '',
      'style_2' => '',
      'max_style' => 'ding_staff_thumbnail',
      'fallback_style' => 'ding_staff_thumbnail',
    ),
  );
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
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Taxonomy term: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['relationship'] = 'field_ding_staff_department_tid';
  /* Sort criterion: Profile: Surname (field_ding_staff_surname) */
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['id'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['field'] = 'field_ding_staff_surname_value';
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
    t('Library departments list'),
    t('term from field_ding_staff_department'),
  );
  $export['ding_staff'] = $view;

  $view = new view();
  $view->name = 'ding_staff_admin_users';
  $view->description = 'List, add, and edit Ding! users.';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'Administration: Ding users';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'People (D!ng users)';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'name' => 'name',
    'data' => 'name',
    'mail' => 'name',
    'rid' => 'rid',
    'field_ding_staff_forename' => 'field_ding_staff_forename',
    'field_ding_staff_surname' => 'field_ding_staff_forename',
    'status' => 'status',
    'created' => 'created',
    'access' => 'access',
    'edit_node' => 'edit_node',
    'cancel_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = 'access';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '<br />',
      'empty_column' => 0,
    ),
    'data' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mail' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'rid' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_staff_forename' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '&nbsp;',
      'empty_column' => 0,
    ),
    'field_ding_staff_surname' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'access' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '&emsp;',
      'empty_column' => 0,
    ),
    'cancel_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = 'No users available.';
  /* Relationship: Profile: staff */
  $handler->display->display_options['relationships']['profile']['id'] = 'profile';
  $handler->display->display_options['relationships']['profile']['table'] = 'users';
  $handler->display->display_options['relationships']['profile']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile']['ui_name'] = 'Profile: staff';
  $handler->display->display_options['relationships']['profile']['bundle_types'] = array(
    'staff' => 'staff',
  );
  /* Field: Bulk operations: User */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'users';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::user_block_user_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Delete',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::flag_user_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Change value',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_user_roles_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Change user roles',
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::system_send_email_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Send e-mail',
    ),
    'action::pathauto_user_update_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Profile: Image */
  $handler->display->display_options['fields']['field_ding_staff_image']['id'] = 'field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['table'] = 'field_data_field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['field'] = 'field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_ding_staff_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_staff_image']['settings'] = array(
    'image_style' => 'ding_staff_thumbnail',
    'image_link' => '',
  );
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['label'] = '';
  $handler->display->display_options['fields']['mail']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mail']['link_to_user'] = '0';
  /* Field: User: Roles */
  $handler->display->display_options['fields']['rid']['id'] = 'rid';
  $handler->display->display_options['fields']['rid']['table'] = 'users_roles';
  $handler->display->display_options['fields']['rid']['field'] = 'rid';
  $handler->display->display_options['fields']['rid']['type'] = 'ul';
  /* Field: Profile: Forename */
  $handler->display->display_options['fields']['field_ding_staff_forename']['id'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['table'] = 'field_data_field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['field'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_ding_staff_forename']['label'] = 'Name (in Staff)';
  /* Field: Profile: Surname */
  $handler->display->display_options['fields']['field_ding_staff_surname']['id'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['field'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_ding_staff_surname']['label'] = 'Surname (Staff)';
  /* Field: User: Active */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'users';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['type'] = 'active-blocked';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: User: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'users';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Member for';
  $handler->display->display_options['fields']['created']['date_format'] = 'raw time ago';
  /* Field: User: Last access */
  $handler->display->display_options['fields']['access']['id'] = 'access';
  $handler->display->display_options['fields']['access']['table'] = 'users';
  $handler->display->display_options['fields']['access']['field'] = 'access';
  $handler->display->display_options['fields']['access']['date_format'] = 'raw time ago';
  /* Field: User: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'users';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Operations';
  /* Field: User: Cancel link */
  $handler->display->display_options['fields']['cancel_node']['id'] = 'cancel_node';
  $handler->display->display_options['fields']['cancel_node']['table'] = 'users';
  $handler->display->display_options['fields']['cancel_node']['field'] = 'cancel_node';
  $handler->display->display_options['fields']['cancel_node']['label'] = '';
  $handler->display->display_options['fields']['cancel_node']['element_label_colon'] = FALSE;
  /* Sort criterion: User: Created date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'users';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['operator'] = 'not in';
  $handler->display->display_options['filters']['uid']['value'] = array(
    0 => 0,
  );
  $handler->display->display_options['filters']['uid']['group'] = 1;
  /* Filter criterion: User: Name (raw) */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'users';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['operator'] = 'contains';
  $handler->display->display_options['filters']['name']['group'] = 1;
  $handler->display->display_options['filters']['name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Username';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    3 => 0,
    8 => 0,
  );
  /* Filter criterion: User: E-mail */
  $handler->display->display_options['filters']['mail']['id'] = 'mail';
  $handler->display->display_options['filters']['mail']['table'] = 'users';
  $handler->display->display_options['filters']['mail']['field'] = 'mail';
  $handler->display->display_options['filters']['mail']['operator'] = 'contains';
  $handler->display->display_options['filters']['mail']['group'] = 1;
  $handler->display->display_options['filters']['mail']['exposed'] = TRUE;
  $handler->display->display_options['filters']['mail']['expose']['operator_id'] = 'mail_op';
  $handler->display->display_options['filters']['mail']['expose']['label'] = 'E-mail';
  $handler->display->display_options['filters']['mail']['expose']['operator'] = 'mail_op';
  $handler->display->display_options['filters']['mail']['expose']['identifier'] = 'mail';
  $handler->display->display_options['filters']['mail']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    3 => 0,
    8 => 0,
  );
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 'All';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Active';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    3 => 0,
    8 => 0,
  );
  /* Filter criterion: User: Roles */
  $handler->display->display_options['filters']['rid']['id'] = 'rid';
  $handler->display->display_options['filters']['rid']['table'] = 'users_roles';
  $handler->display->display_options['filters']['rid']['field'] = 'rid';
  $handler->display->display_options['filters']['rid']['group'] = 1;
  $handler->display->display_options['filters']['rid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['rid']['expose']['operator_id'] = 'rid_op';
  $handler->display->display_options['filters']['rid']['expose']['label'] = 'Role';
  $handler->display->display_options['filters']['rid']['expose']['operator'] = 'rid_op';
  $handler->display->display_options['filters']['rid']['expose']['identifier'] = 'rid';
  $handler->display->display_options['filters']['rid']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['rid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    3 => 0,
    8 => 0,
  );
  /* Filter criterion: Profile: Forename (field_ding_staff_forename) */
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['id'] = 'field_ding_staff_forename_value';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['table'] = 'field_data_field_ding_staff_forename';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['field'] = 'field_ding_staff_forename_value';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['relationship'] = 'profile';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['group'] = 1;
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['expose']['operator_id'] = 'field_ding_staff_forename_value_op';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['expose']['label'] = 'Forename (Staff)';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['expose']['operator'] = 'field_ding_staff_forename_value_op';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['expose']['identifier'] = 'field_ding_staff_forename_value';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    3 => 0,
    8 => 0,
  );
  /* Filter criterion: Profile: Surname (field_ding_staff_surname) */
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['id'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['field'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['relationship'] = 'profile';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['group'] = 1;
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['expose']['operator_id'] = 'field_ding_staff_surname_value_op';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['expose']['label'] = 'Surname (Staff)';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['expose']['operator'] = 'field_ding_staff_surname_value_op';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['expose']['identifier'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    3 => 0,
    8 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'ding_staff_people_list');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    7 => '7',
    8 => '8',
  );
  $handler->display->display_options['path'] = 'admin/people/ding_users';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'D!ng Users';
  $handler->display->display_options['menu']['description'] = 'Administer users - incl. staff profiles';
  $handler->display->display_options['menu']['weight'] = '-1';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['ding_staff_admin_users'] = array(
    t('Master'),
    t('People (D!ng users)'),
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
    t('No users available.'),
    t('Profile'),
    t('User'),
    t('Name'),
    t('Roles'),
    t('Name (in Staff)'),
    t('Surname (Staff)'),
    t('Status'),
    t('Member for'),
    t('Last access'),
    t('Operations'),
    t('Username'),
    t('E-mail'),
    t('Active'),
    t('Role'),
    t('Forename (Staff)'),
    t('Page'),
  );
  $export['ding_staff_admin_users'] = $view;

  return $export;
}
