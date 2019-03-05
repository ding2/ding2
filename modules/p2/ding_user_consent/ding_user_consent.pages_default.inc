<?php
/**
 * @file
 * ding_user_consent.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function ding_user_consent_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'consent_info';
  $page->task = 'page';
  $page->admin_title = 'Consent info';
  $page->admin_description = '';
  $page->path = 'privatlivspolitik';
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
  $handler->name = 'page_consent_info__panel';
  $handler->task = 'page';
  $handler->subtask = 'consent_info';
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
  $display->uuid = 'eaee81e4-2703-4aea-a603-031775195dde';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-0b8f540d-189c-44c4-8a00-9e76f475efb8';
    $pane->panel = 'main_content';
    $pane->type = 'consent_text';
    $pane->subtype = 'consent_text';
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
    $pane->uuid = '0b8f540d-189c-44c4-8a00-9e76f475efb8';
    $display->content['new-0b8f540d-189c-44c4-8a00-9e76f475efb8'] = $pane;
    $display->panels['main_content'][0] = 'new-0b8f540d-189c-44c4-8a00-9e76f475efb8';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-0b8f540d-189c-44c4-8a00-9e76f475efb8';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['consent_info'] = $page;

  return $pages;

}
