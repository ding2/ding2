<?php

/**
 * Extend the ctools export UI class with our own functionality.
 */
class ting_field_search_ctools_export_ui extends ctools_export_ui {

  /**
   * Add our own admin CSS to the listing page.
   */
  function list_css() {
    parent::list_css();
    $path = drupal_get_path('module', 'ting_field_search');
    drupal_add_css($path . '/css/ting_field_search.admin.css');
  }

  /**
   * Modify the default ctools export-ui hook_menu implementation.
   */
  function hook_menu(&$items) {
    parent::hook_menu($items);

    // Ensure the profiles tab is displayed correctly in the contexts of Ting
    // field search tabs.
    unset($items['admin/config/ting/ting-field-search/profiles/list']);
    $items['admin/config/ting/ting-field-search/profiles']['type'] = MENU_LOCAL_TASK;

    // Try to fix the display of the nested profile editing tabs.
    unset($items['admin/config/ting/ting-field-search/profiles/list/%ctools_export_ui/edit']['page callback']);
    unset($items['admin/config/ting/ting-field-search/profiles/list/%ctools_export_ui/edit']['page arguments']);
    unset($items['admin/config/ting/ting-field-search/profiles/list/%ctools_export_ui/edit']['load arguments']);
    unset($items['admin/config/ting/ting-field-search/profiles/list/%ctools_export_ui/edit']['access callback']);
    unset($items['admin/config/ting/ting-field-search/profiles/list/%ctools_export_ui/edit']['access arguments']);
    $items['admin/config/ting/ting-field-search/profiles/list/%ctools_export_ui']['type'] = MENU_NORMAL_ITEM;
    $items['admin/config/ting/ting-field-search/profiles/list/%ctools_export_ui']['title'] = 'Edit';
  }

  /**
   * Modify the profile list form.
   */
  function list_form(&$form, &$form_state) {
    parent::list_form($form, $form_state);

    $all = array('all' => t('- All -'));

    $form['top row']['storage']['#weight'] = -2;
    $form['top row']['disabled']['#weight'] = -1;

    $form['top row']['exposed'] = array(
      '#type' => 'select',
      '#title' => t('Exposed'),
      '#options' => $all + array(
        '0' => t('Hidden'),
        '1' => t('Exposed'),
      ),
      '#default_value' => 'all',
      '#weight' => 0,
    );

    // Change default sort to Title.
    $form['bottom row']['sort']['#default_value'] = 'title';
  }

  /**
   * Implement the filters we added in list_form().
   */
  function list_filter($form_state, $profile) {
    if ($form_state['values']['exposed'] != 'all') {
      if ($form_state['values']['exposed'] != $profile->config['user_interaction']['exposed']) {
        return TRUE;
      }
    }
    return parent::list_filter($form_state, $profile);
  }

  /**
   * Provide our own sort options.
   */
  function list_sort_options() {
    return array(
      'title' => t('Title'),
      'name' => t('Name'),
      'weight' => t('Weight'),
      'exposed' => t('Exposed'),
    );
  }

  function list_build_row($profile, &$form_state, $operations) {
    parent::list_build_row($profile, $form_state, $operations);

    $name = $profile->name;
    $row_data = &$this->rows[$name]['data'];

    // We want the operations last so remove it now, add our stuff and add it
    // again later when we're done.
    $operations = array_pop($row_data);

    $row_data[]['data'] = check_plain($profile->config['search_request']['search_well_profile']);
    $row_data[]['data'] = check_plain($profile->config['search_request']['query']);
    $row_data[]['data'] = $profile->config['user_interaction']['exposed'] ? t('Yes') : t('No');
    $row_data[]['data'] = $profile->weight;

    $row_data[] = $operations;

    // Prepare for the sorting (the parent handles name and title).
    $weight = $profile->weight;
    $exposed = $profile->config['user_interaction']['exposed'];
    switch ($form_state['values']['order']) {
      case 'weight':
        $this->sorts[$name] = $weight;
        break;
      case 'exposed':
        $this->sorts[$name] = $exposed;
        break;
    }
  }

  function list_table_header() {
    $header = parent::list_table_header();

    $operations = array_pop($header);

    $header[]['data'] = t('Search well profile');
    $header[]['data'] = t('Query');
    $header[]['data'] = t('Exposed');
    $header[] = t('Weight');

    $header[] = $operations;

    return $header;
  }

}
