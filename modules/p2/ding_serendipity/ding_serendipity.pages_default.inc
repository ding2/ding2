<?php

/**
 * @file
 * ding_news.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function ding_serendipity_default_page_manager_pages() {
  $export = array();
  $page = new stdClass();
  /* Edit this to true to make a default page disabled initially */

  $page->disabled = FALSE;
  $page->api_version = 1;
  $page->name = 'serendipitive_forslag';
  $page->task = 'page';
  $page->admin_title = 'Serendipitive forslag';
  $page->admin_description = '';
  $page->path = 'forslag';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  /* Edit this to true to make a default handler disabled initially */

  $handler->disabled = FALSE;
  $handler->api_version = 1;
  $handler->name = 'page_serendipitive_forslag_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'serendipitive_forslag';
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
  );
  $display = new panels_display();
  $display->layout = 'ding2_site_template';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'branding' => NULL,
      'header' => NULL,
      'navigation' => NULL,
      'content' => NULL,
      'footer' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-1';
  $pane->panel = 'content';
  $pane->type = 'serendipity_ting_object';
  $pane->subtype = 'serendipity_ting_object';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'view_mode' => 'teaser',
    'sort_weight' => FALSE,
    'max' => '30',
    'min' => 0,
    'random' => FALSE,
    'selected_keys' => array(
      'ting_object' => 'ting_object',
      'frontpage' => 'frontpage',
    ),
    'context' => array(
      0 => 'empty',
      1 => 'empty',
      2 => 'empty',
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
  $display->content['new-1'] = $pane;
  $display->panels['content'][0] = 'new-1';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-1';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;

  return $export;
}
