<?php
/**
 * @file
 * ting_infomedia.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function ting_infomedia_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'ting_infomedia';
  $page->task = 'page';
  $page->admin_title = 'ting_infomedia';
  $page->admin_description = 'Displays an Infomedia article';
  $page->path = 'ting/infomedia/%infomedia';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array(
    'infomedia' => array(
      'id' => 1,
      'identifier' => 'infomedia: ID',
      'name' => 'infomedia',
      'settings' => array(),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_ting_infomedia_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'ting_infomedia';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Infomedia Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'panels_breadcrumbs_state' => 1,
    'panels_breadcrumbs_titles' => 'Infomedia',
    'panels_breadcrumbs_paths' => '<none>',
  );
  $display = new panels_display();
  $display->layout = 'threecol_25_50_25';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'left' => NULL,
      'middle' => NULL,
      'right' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '19189b88-b48c-42bb-bde3-4daaccf9184c';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-8b102c7f-69c5-4c01-b991-6438d2177641';
    $pane->panel = 'left';
    $pane->type = 'ding_campaign_plus';
    $pane->subtype = 'ding_campaign_plus';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'style' => 'ribbon',
      'context' => array(
        0 => 'empty',
        1 => 'empty',
        2 => 'empty',
        3 => 'empty',
      ),
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array(
      'method' => '0',
      'settings' => array(),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '8b102c7f-69c5-4c01-b991-6438d2177641';
    $display->content['new-8b102c7f-69c5-4c01-b991-6438d2177641'] = $pane;
    $display->panels['left'][0] = 'new-8b102c7f-69c5-4c01-b991-6438d2177641';
    $pane = new stdClass();
    $pane->pid = 'new-5142c63e-e5d0-4fe3-b5f4-0d91d9b2b9aa';
    $pane->panel = 'middle';
    $pane->type = 'infomedia_content_type';
    $pane->subtype = 'infomedia_content_type';
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
    $pane->locks = '';
    $pane->uuid = '5142c63e-e5d0-4fe3-b5f4-0d91d9b2b9aa';
    $display->content['new-5142c63e-e5d0-4fe3-b5f4-0d91d9b2b9aa'] = $pane;
    $display->panels['middle'][0] = 'new-5142c63e-e5d0-4fe3-b5f4-0d91d9b2b9aa';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-5142c63e-e5d0-4fe3-b5f4-0d91d9b2b9aa';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['ting_infomedia'] = $page;

  $pages['base_page'] = $page;
  return $pages;

}
