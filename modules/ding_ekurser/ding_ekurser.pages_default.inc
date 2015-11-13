<?php
/**
 * @file
 * ding_ekurser.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function ding_ekurser_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'ding_ekurser';
  $page->task = 'page';
  $page->admin_title = 'eKurser';
  $page->admin_description = '';
  $page->path = 'ekurser';
  $page->access = array(
    'logic' => 'and',
  );
  $page->menu = array(
    'type' => 'none',
    'title' => '',
    'name' => 'navigation',
    'weight' => '0',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_ding_ekurser_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'ding_ekurser';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'eKurser',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(
      0 => array(
        'identifier' => 'keyword',
        'keyword' => 'keyword',
        'name' => 'string',
        'string' => 'ekurser.nu',
        'id' => 1,
      ),
    ),
    'relationships' => array(),
    'access' => array(
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
  $display->title = 'e-Kurser';
  $display->uuid = 'b343466b-e46b-4a4e-b7ce-e32227bf1e77';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-2df864ec-6d35-4606-a781-8d4194769c0e';
    $pane->panel = 'left_sidebar';
    $pane->type = 'ding_facetbrowser';
    $pane->subtype = 'ding_facetbrowser';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '2df864ec-6d35-4606-a781-8d4194769c0e';
    $display->content['new-2df864ec-6d35-4606-a781-8d4194769c0e'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-2df864ec-6d35-4606-a781-8d4194769c0e';
    $pane = new stdClass();
    $pane->pid = 'new-ed098fce-39b8-40ce-b809-7510324be5f1';
    $pane->panel = 'main_content';
    $pane->type = 'search_result_count';
    $pane->subtype = 'search_result_count';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'context_string_1',
      'override_title' => 1,
      'override_title_text' => 'eKurser',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'ed098fce-39b8-40ce-b809-7510324be5f1';
    $display->content['new-ed098fce-39b8-40ce-b809-7510324be5f1'] = $pane;
    $display->panels['main_content'][0] = 'new-ed098fce-39b8-40ce-b809-7510324be5f1';
    $pane = new stdClass();
    $pane->pid = 'new-5bbd8677-c1a7-4bf3-9cbe-6c225035c436';
    $pane->panel = 'main_content';
    $pane->type = 'search_per_page';
    $pane->subtype = 'search_per_page';
    $pane->shown = FALSE;
    $pane->access = array();
    $pane->configuration = array(
      'select_type' => 'dropdown',
      'context' => 'context_string_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '5bbd8677-c1a7-4bf3-9cbe-6c225035c436';
    $display->content['new-5bbd8677-c1a7-4bf3-9cbe-6c225035c436'] = $pane;
    $display->panels['main_content'][1] = 'new-5bbd8677-c1a7-4bf3-9cbe-6c225035c436';
    $pane = new stdClass();
    $pane->pid = 'new-ed8b5608-564b-4412-b22b-803d31dc343e';
    $pane->panel = 'main_content';
    $pane->type = 'block';
    $pane->subtype = 'ting_search-sort_form';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'ed8b5608-564b-4412-b22b-803d31dc343e';
    $display->content['new-ed8b5608-564b-4412-b22b-803d31dc343e'] = $pane;
    $display->panels['main_content'][2] = 'new-ed8b5608-564b-4412-b22b-803d31dc343e';
    $pane = new stdClass();
    $pane->pid = 'new-e013e349-9789-486b-9c5a-01eb99184144';
    $pane->panel = 'main_content';
    $pane->type = 'search_result';
    $pane->subtype = 'search_result';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'type' => 'ding_ekurser',
      'log' => 0,
      'override_empty' => 0,
      'empty_title' => '',
      'empty' => '',
      'empty_format' => 'plain_text',
      'override_no_key' => 0,
      'no_key_title' => '',
      'no_key' => '',
      'no_key_format' => 'plain_text',
      'context' => 'context_string_1',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = 'e013e349-9789-486b-9c5a-01eb99184144';
    $display->content['new-e013e349-9789-486b-9c5a-01eb99184144'] = $pane;
    $display->panels['main_content'][3] = 'new-e013e349-9789-486b-9c5a-01eb99184144';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-ed098fce-39b8-40ce-b809-7510324be5f1';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['ding_ekurser'] = $page;

  return $pages;

}
