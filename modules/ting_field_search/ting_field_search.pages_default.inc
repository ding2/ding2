<?php
/**
 * @file
 * ting_field_search.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function ting_field_search_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'ting_field_search_profile_page';
  $page->task = 'page';
  $page->admin_title = 'Ting field search profile page';
  $page->admin_description = '';
  $page->path = 'ting-field-search/profile/%name';
  $page->access = array(
    'logic' => 'and',
    'plugins' => array(),
  );
  $page->menu = array();
  $page->arguments = array(
    'name' => array(
      'id' => 1,
      'identifier' => 'Ting field search profile: name',
      'name' => 'ting_field_search_profile',
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
  $handler->name = 'page_ting_field_search_profile_page__panel';
  $handler->task = 'page';
  $handler->subtask = 'ting_field_search_profile_page';
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
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'ting_field_search_profile_page',
          'settings' => NULL,
          'context' => 'argument_ting_field_search_profile_1',
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
  $display->uuid = 'dcdb4e3c-3464-49de-a8a5-95889a76ce87';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-163bf6da-e398-44ac-a223-e967e8f1b7a5';
    $pane->panel = 'left_sidebar';
    $pane->type = 'views_panes';
    $pane->subtype = 'ting_field_search_search_guide-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'arguments' => array(
        'field_profile_page_placment_profile_name' => '%name:name',
        'field_profile_page_placment_position' => 'sidebar',
      ),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'ting-field-search-search-guide-sidebar',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '163bf6da-e398-44ac-a223-e967e8f1b7a5';
    $display->content['new-163bf6da-e398-44ac-a223-e967e8f1b7a5'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-163bf6da-e398-44ac-a223-e967e8f1b7a5';
    $pane = new stdClass();
    $pane->pid = 'new-b7cfaa5c-80e1-472c-8c69-56846bba902e';
    $pane->panel = 'main_content';
    $pane->type = 'ting_field_search_profile_page';
    $pane->subtype = 'ting_field_search_profile_page';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'empty',
        1 => 'argument_ting_field_search_profile_1',
      ),
      'override_title' => 1,
      'override_title_text' => '%title',
      'override_title_heading' => 'h1',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'b7cfaa5c-80e1-472c-8c69-56846bba902e';
    $display->content['new-b7cfaa5c-80e1-472c-8c69-56846bba902e'] = $pane;
    $display->panels['main_content'][0] = 'new-b7cfaa5c-80e1-472c-8c69-56846bba902e';
    $pane = new stdClass();
    $pane->pid = 'new-209a91f5-909f-4601-9e8f-08ad5c007265';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ting_field_search_search_guide-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'arguments' => array(
        'field_profile_page_placment_profile_name' => '%name:name',
        'field_profile_page_placment_position' => 'bottomleft',
      ),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'ting-field-search-search-guide-bottom',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '209a91f5-909f-4601-9e8f-08ad5c007265';
    $display->content['new-209a91f5-909f-4601-9e8f-08ad5c007265'] = $pane;
    $display->panels['main_content'][1] = 'new-209a91f5-909f-4601-9e8f-08ad5c007265';
    $pane = new stdClass();
    $pane->pid = 'new-2914d76a-d6d0-4b53-a348-2c849fa86947';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ting_field_search_search_guide-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'arguments' => array(
        'field_profile_page_placment_profile_name' => '%name:name',
        'field_profile_page_placment_position' => 'bottomright',
      ),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'ting-field-search-search-guide-bottom',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '2914d76a-d6d0-4b53-a348-2c849fa86947';
    $display->content['new-2914d76a-d6d0-4b53-a348-2c849fa86947'] = $pane;
    $display->panels['main_content'][2] = 'new-2914d76a-d6d0-4b53-a348-2c849fa86947';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['ting_field_search_profile_page'] = $page;

  return $pages;

}
