<?php
/**
 * @file
 * ding_content.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function ding_content_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: views_view
  $overrides["views_view.workbench_recent_content.display|default|display_options|fields|field_ding_staff_forename"] = array(
    'id' => 'field_ding_staff_forename',
    'table' => 'field_data_field_ding_staff_forename',
    'field' => 'field_ding_staff_forename',
    'relationship' => 'profile',
    'label' => '',
    'exclude' => TRUE,
    'element_label_colon' => FALSE,
  );
  $overrides["views_view.workbench_recent_content.display|default|display_options|fields|field_ding_staff_surname"] = array(
    'id' => 'field_ding_staff_surname',
    'table' => 'field_data_field_ding_staff_surname',
    'field' => 'field_ding_staff_surname',
    'relationship' => 'profile',
    'label' => 'Author',
    'alter' => array(
      'alter_text' => TRUE,
      'text' => '[field_ding_staff_forename] [field_ding_staff_surname]',
      'make_link' => TRUE,
      'path' => 'user/[uid]',
    ),
    'element_label_colon' => FALSE,
    'empty' => '[name]',
  );
  $overrides["views_view.workbench_recent_content.display|default|display_options|fields|name|exclude"] = TRUE;
  $overrides["views_view.workbench_recent_content.display|default|display_options|fields|name|label"] = '';
  $overrides["views_view.workbench_recent_content.display|default|display_options|fields|status"] = array(
    'id' => 'status',
    'table' => 'node',
    'field' => 'status',
    'label' => 'Udgivet',
    'not' => 0,
  );
  $overrides["views_view.workbench_recent_content.display|default|display_options|fields|title_1"] = array(
    'id' => 'title_1',
    'table' => 'node',
    'field' => 'title',
    'relationship' => 'og_group_ref_target_id',
    'label' => 'Library',
  );
  $overrides["views_view.workbench_recent_content.display|default|display_options|fields|uid"] = array(
    'id' => 'uid',
    'table' => 'users',
    'field' => 'uid',
    'relationship' => 'uid',
    'label' => '',
    'exclude' => TRUE,
    'element_label_colon' => FALSE,
    'link_to_user' => FALSE,
  );
  $overrides["views_view.workbench_recent_content.display|default|display_options|filter_groups"] = array(
    'groups' => array(
      1 => 'AND',
      2 => 'OR',
    ),
  );
  $overrides["views_view.workbench_recent_content.display|default|display_options|filters|field_ding_staff_forename_value"] = array(
    'id' => 'field_ding_staff_forename_value',
    'table' => 'field_data_field_ding_staff_forename',
    'field' => 'field_ding_staff_forename_value',
    'relationship' => 'profile',
    'operator' => 'contains',
    'exposed' => TRUE,
    'expose' => array(
      'operator_id' => 'field_ding_staff_forename_value_op',
      'label' => 'Forename',
      'operator' => 'field_ding_staff_forename_value_op',
      'identifier' => 'field_ding_staff_forename_value',
      'remember' => TRUE,
      'remember_roles' => array(
        2 => 2,
        1 => 0,
        3 => 0,
        4 => 0,
        5 => 0,
        6 => 0,
        7 => 0,
        8 => 0,
        9 => 0,
      ),
    ),
    'group_info' => array(
      'label' => 'Forename (field_ding_staff_forename)',
      'identifier' => 'field_ding_staff_forename_value',
      'remember' => FALSE,
      'group_items' => array(
        1 => array(),
        2 => array(),
        3 => array(),
      ),
    ),
  );
  $overrides["views_view.workbench_recent_content.display|default|display_options|filters|field_ding_staff_surname_value"] = array(
    'id' => 'field_ding_staff_surname_value',
    'table' => 'field_data_field_ding_staff_surname',
    'field' => 'field_ding_staff_surname_value',
    'relationship' => 'profile',
    'operator' => 'contains',
    'exposed' => TRUE,
    'expose' => array(
      'operator_id' => 'field_ding_staff_surname_value_op',
      'label' => 'Surname',
      'operator' => 'field_ding_staff_surname_value_op',
      'identifier' => 'field_ding_staff_surname_value',
      'remember' => TRUE,
      'remember_roles' => array(
        2 => 2,
        1 => 0,
        3 => 0,
        4 => 0,
        5 => 0,
        6 => 0,
        7 => 0,
        8 => 0,
        9 => 0,
      ),
    ),
  );
  $overrides["views_view.workbench_recent_content.display|default|display_options|filters|og_group_ref_target_id"] = array(
    'id' => 'og_group_ref_target_id',
    'table' => 'og_membership',
    'field' => 'og_group_ref_target_id',
    'operator' => 'empty',
    'group' => 2,
  );
  $overrides["views_view.workbench_recent_content.display|default|display_options|filters|status_extra|group"] = 1;
  $overrides["views_view.workbench_recent_content.display|default|display_options|filters|status|group"] = 1;
  $overrides["views_view.workbench_recent_content.display|default|display_options|filters|title_1"] = array(
    'id' => 'title_1',
    'table' => 'node',
    'field' => 'title',
    'relationship' => 'og_group_ref_target_id',
    'operator' => 'contains',
    'exposed' => TRUE,
    'expose' => array(
      'operator_id' => 'title_1_op',
      'label' => 'Library',
      'operator' => 'title_1_op',
      'identifier' => 'title_1',
      'remember' => TRUE,
      'remember_roles' => array(
        2 => 2,
        1 => 0,
        3 => 0,
        4 => 0,
        5 => 0,
        6 => 0,
        7 => 0,
        8 => 0,
        9 => 0,
      ),
    ),
  );
  $overrides["views_view.workbench_recent_content.display|default|display_options|filters|title|group"] = 1;
  $overrides["views_view.workbench_recent_content.display|default|display_options|filters|type_1"] = array(
    'id' => 'type_1',
    'table' => 'node',
    'field' => 'type',
    'relationship' => 'og_group_ref_target_id',
    'value' => array(
      'ding_library' => 'ding_library',
    ),
    'group' => 2,
  );
  $overrides["views_view.workbench_recent_content.display|default|display_options|filters|type|group"] = 1;
  $overrides["views_view.workbench_recent_content.display|default|display_options|relationships|og_group_ref_target_id"] = array(
    'id' => 'og_group_ref_target_id',
    'table' => 'og_membership',
    'field' => 'og_group_ref_target_id',
    'label' => 'Library',
  );
  $overrides["views_view.workbench_recent_content.display|default|display_options|relationships|profile"] = array(
    'id' => 'profile',
    'table' => 'users',
    'field' => 'profile',
    'relationship' => 'uid',
    'bundle_types' => array(
      'ding_staff_profile' => 'ding_staff_profile',
    ),
  );
  $overrides["views_view.workbench_recent_content.display|default|display_options|style_options|columns|field_ding_staff_forename"] = 'field_ding_staff_forename';
  $overrides["views_view.workbench_recent_content.display|default|display_options|style_options|columns|field_ding_staff_surname"] = 'field_ding_staff_surname';
  $overrides["views_view.workbench_recent_content.display|default|display_options|style_options|columns|title_1"] = 'title_1';
  $overrides["views_view.workbench_recent_content.display|default|display_options|style_options|columns|uid"] = 'uid';
  $overrides["views_view.workbench_recent_content.display|default|display_options|style_options|info|changed|empty_column"] = 0;
  $overrides["views_view.workbench_recent_content.display|default|display_options|style_options|info|edit_node|empty_column"] = 0;
  $overrides["views_view.workbench_recent_content.display|default|display_options|style_options|info|field_ding_staff_forename"] = array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  );
  $overrides["views_view.workbench_recent_content.display|default|display_options|style_options|info|field_ding_staff_surname"] = array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  );
  $overrides["views_view.workbench_recent_content.display|default|display_options|style_options|info|name|empty_column"] = 0;
  $overrides["views_view.workbench_recent_content.display|default|display_options|style_options|info|name|sortable"] = 0;
  $overrides["views_view.workbench_recent_content.display|default|display_options|style_options|info|status|empty_column"] = 0;
  $overrides["views_view.workbench_recent_content.display|default|display_options|style_options|info|title_1"] = array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  );
  $overrides["views_view.workbench_recent_content.display|default|display_options|style_options|info|title|empty_column"] = 0;
  $overrides["views_view.workbench_recent_content.display|default|display_options|style_options|info|type|empty_column"] = 0;
  $overrides["views_view.workbench_recent_content.display|default|display_options|style_options|info|uid"] = array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  );
  $overrides["views_view.workbench_recent_content.display|default|display_options|style_options|order"]["DELETED"] = TRUE;
  $overrides["views_view.workbench_recent_content.display|page_1|display_options|defaults|fields"]["DELETED"] = TRUE;
  $overrides["views_view.workbench_recent_content.display|page_1|display_options|fields"]["DELETED"] = TRUE;

 return $overrides;
}
