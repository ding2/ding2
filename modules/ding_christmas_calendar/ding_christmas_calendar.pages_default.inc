<?php
/**
 * @file
 * ding_christmas_calendar.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function ding_christmas_calendar_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'christmas_calendar';
  $page->task = 'page';
  $page->admin_title = 'Christmas calendar';
  $page->admin_description = '';
  $page->path = 'ding-christmas-calendar';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_christmas_calendar__panel';
  $handler->task = 'page';
  $handler->subtask = 'christmas_calendar';
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
    'name' => 'panel',
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'primary' => NULL,
      'secondary' => NULL,
      'tertiary' => NULL,
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
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'd67ab981-5d4d-4d4f-afc9-1170f977ebc2';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-1d09154e-738d-4384-8a72-1467f4e2eeb8';
    $pane->panel = 'middle';
    $pane->type = 'ding_christmas_calendar_widget';
    $pane->subtype = 'ding_christmas_calendar_widget';
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
    $pane->uuid = '1d09154e-738d-4384-8a72-1467f4e2eeb8';
    $display->content['new-1d09154e-738d-4384-8a72-1467f4e2eeb8'] = $pane;
    $display->panels['middle'][0] = 'new-1d09154e-738d-4384-8a72-1467f4e2eeb8';
    $pane = new stdClass();
    $pane->pid = 'new-50a4e080-5ddd-4262-82d8-3a04dba2bcba';
    $pane->panel = 'middle';
    $pane->type = 'ding_christmas_calendar_mobile';
    $pane->subtype = 'ding_christmas_calendar_mobile';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '50a4e080-5ddd-4262-82d8-3a04dba2bcba';
    $display->content['new-50a4e080-5ddd-4262-82d8-3a04dba2bcba'] = $pane;
    $display->panels['middle'][1] = 'new-50a4e080-5ddd-4262-82d8-3a04dba2bcba';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-1d09154e-738d-4384-8a72-1467f4e2eeb8';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['christmas_calendar'] = $page;

  return $pages;

}
