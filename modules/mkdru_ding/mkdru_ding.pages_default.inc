<?php
/**
 * @file
 * mkdru_ding.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function mkdru_ding_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'search_mkdru_ding__panel_context_45d2ee5b-af3f-4acd-8f14-c86e310ed0c7';
  $handler->task = 'search';
  $handler->subtask = 'mkdru_ding';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
  );
  $display = new panels_display();
  $display->layout = '25_50_25';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'left_sidebar' => NULL,
      'main_content' => NULL,
      'right_sidebar' => NULL,
      'attachment_4_1' => NULL,
      'attachment_4_2' => NULL,
      'attachment_4_3' => NULL,
      'attachment_4_4' => NULL,
      'attachment_3_1' => NULL,
      'attachment_3_2' => NULL,
      'attachment_3_3' => NULL,
      'attachment_2_1' => NULL,
      'attachment_2_2' => NULL,
      'attachment_1_1' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '1d650cd9-ef04-405b-86f3-bf8e84918589';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-8b0b2c4f-dc4e-456b-92bf-feb433c6e8c5';
    $pane->panel = 'left_sidebar';
    $pane->type = 'search_backends';
    $pane->subtype = 'search_backends';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '8b0b2c4f-dc4e-456b-92bf-feb433c6e8c5';
    $display->content['new-8b0b2c4f-dc4e-456b-92bf-feb433c6e8c5'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-8b0b2c4f-dc4e-456b-92bf-feb433c6e8c5';
    $pane = new stdClass();
    $pane->pid = 'new-81b5e246-5895-4674-b074-274a04d5ca1f';
    $pane->panel = 'left_sidebar';
    $pane->type = 'search_facets';
    $pane->subtype = 'search_facets';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_string_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '81b5e246-5895-4674-b074-274a04d5ca1f';
    $display->content['new-81b5e246-5895-4674-b074-274a04d5ca1f'] = $pane;
    $display->panels['left_sidebar'][1] = 'new-81b5e246-5895-4674-b074-274a04d5ca1f';
    $pane = new stdClass();
    $pane->pid = 'new-60fded5e-de61-4eb3-abb7-0d8cf66cbae1';
    $pane->panel = 'main_content';
    $pane->type = 'search_form';
    $pane->subtype = 'search_form';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '60fded5e-de61-4eb3-abb7-0d8cf66cbae1';
    $display->content['new-60fded5e-de61-4eb3-abb7-0d8cf66cbae1'] = $pane;
    $display->panels['main_content'][0] = 'new-60fded5e-de61-4eb3-abb7-0d8cf66cbae1';
    $pane = new stdClass();
    $pane->pid = 'new-edd85fdc-a93f-4f4d-9abe-4e3054763919';
    $pane->panel = 'main_content';
    $pane->type = 'search_results';
    $pane->subtype = 'search_results';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_string_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'edd85fdc-a93f-4f4d-9abe-4e3054763919';
    $display->content['new-edd85fdc-a93f-4f4d-9abe-4e3054763919'] = $pane;
    $display->panels['main_content'][1] = 'new-edd85fdc-a93f-4f4d-9abe-4e3054763919';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['search_mkdru_ding__panel_context_45d2ee5b-af3f-4acd-8f14-c86e310ed0c7'] = $handler;

  return $export;
}
