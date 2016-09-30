<?php

/**
 * @file
 * ting_new_materials.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function ting_new_materials_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view_panel_context_new_materials';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -29;
  $handler->conf = array(
    'title' => 'New Materials',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'new_materials' => 'new_materials',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
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
  $display->uuid = '36835cd4-cd1b-4616-a833-0ecb235494cb';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-0e287121-f776-49bb-8663-c4a21de2a5b6';
  $pane->panel = 'left_sidebar';
  $pane->type = 'block';
  $pane->subtype = 'menu_block-3';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '0e287121-f776-49bb-8663-c4a21de2a5b6';
  $display->content['new-0e287121-f776-49bb-8663-c4a21de2a5b6'] = $pane;
  $display->panels['left_sidebar'][0] = 'new-0e287121-f776-49bb-8663-c4a21de2a5b6';
  $pane = new stdClass();
  $pane->pid = 'new-88baaf0d-bddf-4649-9029-d84fec86a486';
  $pane->panel = 'main_content';
  $pane->type = 'new_materials';
  $pane->subtype = 'new_materials';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'context' => array(
      0 => 'argument_entity_id:node_1',
    ),
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '88baaf0d-bddf-4649-9029-d84fec86a486';
  $display->content['new-88baaf0d-bddf-4649-9029-d84fec86a486'] = $pane;
  $display->panels['main_content'][0] = 'new-88baaf0d-bddf-4649-9029-d84fec86a486';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-88baaf0d-bddf-4649-9029-d84fec86a486';
  $handler->conf['display'] = $display;

  $export['node_view_panel_context_new_materials'] = $handler;

  return $export;
}
