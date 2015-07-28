<?php
/**
 * @file
 * ding_content.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function ding_content_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'myworkbench_panel_context';
  $handler->task = 'myworkbench';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -30;
  $handler->conf = array(
    'title' => 'Ding! Workbench',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
  );
  $display = new panels_display();
  $display->layout = 'twocol_bricks';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
      'top' => NULL,
      'left_above' => NULL,
      'right_above' => NULL,
      'left_below' => NULL,
      'right_below' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'My Workbench';
  $display->uuid = '591b7dc8-0df8-4424-9127-7fa8f038920e';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-70178104-cffb-4e1f-a96c-2aa96323df6d';
    $pane->panel = 'left_above';
    $pane->type = 'views';
    $pane->subtype = 'workbench_current_user';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '0',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'default',
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
    $pane->locks = '';
    $pane->uuid = '70178104-cffb-4e1f-a96c-2aa96323df6d';
    $display->content['new-70178104-cffb-4e1f-a96c-2aa96323df6d'] = $pane;
    $display->panels['left_above'][0] = 'new-70178104-cffb-4e1f-a96c-2aa96323df6d';
    $pane = new stdClass();
    $pane->pid = 'new-1b65f4db-dc0d-401b-af88-439627f5e28c';
    $pane->panel = 'middle';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_content_workbench-summary';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => 'All Recent Content',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '1b65f4db-dc0d-401b-af88-439627f5e28c';
    $display->content['new-1b65f4db-dc0d-401b-af88-439627f5e28c'] = $pane;
    $display->panels['middle'][0] = 'new-1b65f4db-dc0d-401b-af88-439627f5e28c';
    $pane = new stdClass();
    $pane->pid = 'new-2d074fc0-47d1-4ba5-9d67-1d846a66606b';
    $pane->panel = 'right_above';
    $pane->type = 'views';
    $pane->subtype = 'workbench_edited';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '5',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block_1',
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
    $pane->locks = '';
    $pane->uuid = '2d074fc0-47d1-4ba5-9d67-1d846a66606b';
    $display->content['new-2d074fc0-47d1-4ba5-9d67-1d846a66606b'] = $pane;
    $display->panels['right_above'][0] = 'new-2d074fc0-47d1-4ba5-9d67-1d846a66606b';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['myworkbench_panel_context'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'pm_existing_pages_ding_content_workbench_recent_content_panel_context';
  $handler->task = 'pm_existing_pages';
  $handler->subtask = 'ding_content_workbench_recent_content';
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
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '7793e5c6-c254-4c70-8c32-7800648a854c';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-63ed6922-b864-4840-acf6-d6526f24d291';
    $pane->panel = 'middle';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_content_workbench-content_list';
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
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '63ed6922-b864-4840-acf6-d6526f24d291';
    $display->content['new-63ed6922-b864-4840-acf6-d6526f24d291'] = $pane;
    $display->panels['middle'][0] = 'new-63ed6922-b864-4840-acf6-d6526f24d291';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['pm_existing_pages_ding_content_workbench_recent_content_panel_context'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'term_view_panel_context_3';
  $handler->task = 'term_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 3;
  $handler->conf = array(
    'title' => 'Tags',
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
          'name' => 'term_vocabulary',
          'settings' => array(
            'vids' => array(
              2 => '2',
            ),
          ),
          'context' => 'argument_term_1',
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
  $display->title = '%term:name';
  $display->uuid = '4b241667-11e0-4198-b244-e01ca4d6529d';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-2a68751d-d16f-4b46-8ee7-054a37ed5f0d';
    $pane->panel = 'main_content';
    $pane->type = 'page_title';
    $pane->subtype = 'page_title';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'markup' => 'h1',
      'class' => '',
      'id' => '',
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
    $pane->uuid = '2a68751d-d16f-4b46-8ee7-054a37ed5f0d';
    $display->content['new-2a68751d-d16f-4b46-8ee7-054a37ed5f0d'] = $pane;
    $display->panels['main_content'][0] = 'new-2a68751d-d16f-4b46-8ee7-054a37ed5f0d';
    $pane = new stdClass();
    $pane->pid = 'new-e433f54f-8481-4005-b77f-02c5a4c341d5';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'tags_list-ding_content_tags';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_term_1',
      ),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'e433f54f-8481-4005-b77f-02c5a4c341d5';
    $display->content['new-e433f54f-8481-4005-b77f-02c5a4c341d5'] = $pane;
    $display->panels['main_content'][1] = 'new-e433f54f-8481-4005-b77f-02c5a4c341d5';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['term_view_panel_context_3'] = $handler;

  return $export;
}
