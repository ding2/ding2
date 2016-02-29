<?php
/**
 * @file
 * Ctools plugin definition file.
 */

/**
 * General ctools plugin settings.
 */
$plugin = array(
  'title' => t('Nodelist'),
  'category' => t('easyDDB'),
  'description' => t('Allows to create highliy customizeable list of contents'),
  'single' => TRUE,
  'content_types' => 'ding_nodelist_content_type',
  'render callback' => 'ding_nodelist_content_type_render',
  'admin title' => 'ding_nodelist_content_type_admin_title',
  'admin info' => 'ding_nodelist_content_type_admin_info',
  'edit form' => 'ding_nodelist_content_type_edit_form',
);
