<?php
/**
 * @file
 * ding_groups.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function ding_groups_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view_panel_context_5';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -25;
  $handler->conf = array(
    'title' => 'Groups (OG)',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'logic' => 'and',
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'ding_group' => 'ding_group',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
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
  $display->uuid = '4d5ebb9a-6744-4fab-b173-28619324b293';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-fff67ee4-207e-421d-9fd6-ad12b8078621';
    $pane->panel = 'left_sidebar';
    $pane->type = 'block';
    $pane->subtype = 'og_menu-og_single_menu_block';
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
    $pane->uuid = 'fff67ee4-207e-421d-9fd6-ad12b8078621';
    $display->content['new-fff67ee4-207e-421d-9fd6-ad12b8078621'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-fff67ee4-207e-421d-9fd6-ad12b8078621';
    $pane = new stdClass();
    $pane->pid = 'new-461e8a45-91a4-49de-88b5-24000aad0c33';
    $pane->panel = 'main_content';
    $pane->type = 'node_content';
    $pane->subtype = 'node_content';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'links' => 0,
      'no_extras' => 0,
      'override_title' => 1,
      'override_title_text' => '',
      'identifier' => '',
      'link' => 0,
      'leave_node_title' => 0,
      'build_mode' => 'full',
      'context' => 'argument_entity_id:node_1',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '461e8a45-91a4-49de-88b5-24000aad0c33';
    $display->content['new-461e8a45-91a4-49de-88b5-24000aad0c33'] = $pane;
    $display->panels['main_content'][0] = 'new-461e8a45-91a4-49de-88b5-24000aad0c33';
    $pane = new stdClass();
    $pane->pid = 'new-668dfc7d-4d91-4dff-ad05-ae9da59a4d43';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_news-ding_news_groups_list';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'ding-group-news',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '668dfc7d-4d91-4dff-ad05-ae9da59a4d43';
    $display->content['new-668dfc7d-4d91-4dff-ad05-ae9da59a4d43'] = $pane;
    $display->panels['main_content'][1] = 'new-668dfc7d-4d91-4dff-ad05-ae9da59a4d43';
    $pane = new stdClass();
    $pane->pid = 'new-3bc42ce7-ca5f-4e5c-9176-2bcbaecc961a';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_event-ding_event_groups_list';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'ding-group-events',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '3bc42ce7-ca5f-4e5c-9176-2bcbaecc961a';
    $display->content['new-3bc42ce7-ca5f-4e5c-9176-2bcbaecc961a'] = $pane;
    $display->panels['main_content'][2] = 'new-3bc42ce7-ca5f-4e5c-9176-2bcbaecc961a';
    $pane = new stdClass();
    $pane->pid = 'new-c9969c72-cf63-49ed-b371-61bb19780890';
    $pane->panel = 'right_sidebar';
    $pane->type = 'campaign';
    $pane->subtype = 'campaign';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'ding_campaign_count' => 3,
      'ding_campaign_offset' => 0,
      'ding_campaign_image_style' => 'medium',
      'context' => array(
        0 => 'argument_entity_id:node_1',
        1 => 'empty',
        2 => 'empty',
        3 => 'empty',
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
    $pane->uuid = 'c9969c72-cf63-49ed-b371-61bb19780890';
    $display->content['new-c9969c72-cf63-49ed-b371-61bb19780890'] = $pane;
    $display->panels['right_sidebar'][0] = 'new-c9969c72-cf63-49ed-b371-61bb19780890';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view_panel_context_5'] = $handler;

  return $export;
}

/**
 * Implements hook_default_page_manager_pages().
 */
function ding_groups_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'ding_groups_news';
  $page->task = 'page';
  $page->admin_title = 'Groups news';
  $page->admin_description = '';
  $page->path = 'temaer/%gid/nyheder/!tid';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array(
    'gid' => array(
      'id' => 1,
      'identifier' => 'Node: ID',
      'name' => 'entity_id:node',
      'settings' => array(),
      'keyword' => 'gid',
    ),
    'tid' => array(
      'id' => 1,
      'identifier' => 'Taxonomy term: ID',
      'name' => 'term',
      'settings' => array(
        'input_form' => 'tid',
        'vids' => array(
          1 => 0,
          6 => 0,
          3 => 0,
          4 => 0,
          7 => 0,
          5 => 0,
          2 => 0,
        ),
        'breadcrumb' => 0,
        'transform' => 0,
      ),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_ding_groups_news_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'ding_groups_news';
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
  $display->title = 'Group news';
  $display->uuid = '6f08f11b-a074-4229-a560-23a2c8827724';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-5c9d51d8-08ea-4607-a56b-d02a7b53986a';
    $pane->panel = 'left_sidebar';
    $pane->type = 'block';
    $pane->subtype = 'og_menu-og_single_menu_block';
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
    $pane->uuid = '5c9d51d8-08ea-4607-a56b-d02a7b53986a';
    $display->content['new-5c9d51d8-08ea-4607-a56b-d02a7b53986a'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-5c9d51d8-08ea-4607-a56b-d02a7b53986a';
    $pane = new stdClass();
    $pane->pid = 'new-70d8e19a-09f6-4e3f-8772-56c677c8d37c';
    $pane->panel = 'main_content';
    $pane->type = 'menu_title';
    $pane->subtype = 'menu_title';
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
    $pane->uuid = '70d8e19a-09f6-4e3f-8772-56c677c8d37c';
    $display->content['new-70d8e19a-09f6-4e3f-8772-56c677c8d37c'] = $pane;
    $display->panels['main_content'][0] = 'new-70d8e19a-09f6-4e3f-8772-56c677c8d37c';
    $pane = new stdClass();
    $pane->pid = 'new-87861875-d336-471e-b6fc-748803c4e26e';
    $pane->panel = 'main_content';
    $pane->type = 'taxonomy_menu';
    $pane->subtype = 'taxonomy_menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'slug' => 'nyheder',
      'default_link_text' => 'All terms',
      'dropdown' => 1,
      'context' => array(
        0 => 'argument_term_1',
        1 => 'argument_entity_id:node_1',
      ),
      'override_title' => 0,
      'override_title_text' => '',
      'base' => 'temaer',
      'vocabulary' => 'news_category',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '87861875-d336-471e-b6fc-748803c4e26e';
    $display->content['new-87861875-d336-471e-b6fc-748803c4e26e'] = $pane;
    $display->panels['main_content'][1] = 'new-87861875-d336-471e-b6fc-748803c4e26e';
    $pane = new stdClass();
    $pane->pid = 'new-59163806-75bc-4179-b82c-7ce6e30cefb8';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_news-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
        1 => 'argument_term_1',
      ),
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '59163806-75bc-4179-b82c-7ce6e30cefb8';
    $display->content['new-59163806-75bc-4179-b82c-7ce6e30cefb8'] = $pane;
    $display->panels['main_content'][2] = 'new-59163806-75bc-4179-b82c-7ce6e30cefb8';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['ding_groups_news'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'groups_events';
  $page->task = 'page';
  $page->admin_title = 'Groups events';
  $page->admin_description = '';
  $page->path = 'temaer/%gid/arrangementer/!tid';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array(
    'gid' => array(
      'id' => 1,
      'identifier' => 'Node: ID',
      'name' => 'entity_id:node',
      'settings' => array(),
    ),
    'tid' => array(
      'id' => 1,
      'identifier' => 'Taxonomy term: ID',
      'name' => 'term',
      'settings' => array(
        'input_form' => 'tid',
        'vids' => array(
          3 => '3',
          1 => 0,
          6 => 0,
          4 => 0,
          7 => 0,
          5 => 0,
          2 => 0,
        ),
        'breadcrumb' => 1,
        'transform' => 0,
      ),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_groups_events_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'groups_events';
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
  $display->title = 'Group event';
  $display->uuid = 'a2c495ea-7df9-4df3-9e61-147d98e1e39f';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-13eb1cb6-a5ec-4ba5-97da-1677ebb164ad';
    $pane->panel = 'left_sidebar';
    $pane->type = 'block';
    $pane->subtype = 'og_menu-og_single_menu_block';
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
    $pane->uuid = '13eb1cb6-a5ec-4ba5-97da-1677ebb164ad';
    $display->content['new-13eb1cb6-a5ec-4ba5-97da-1677ebb164ad'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-13eb1cb6-a5ec-4ba5-97da-1677ebb164ad';
    $pane = new stdClass();
    $pane->pid = 'new-6503854d-1108-4c4a-b788-f56cf4de956f';
    $pane->panel = 'main_content';
    $pane->type = 'menu_title';
    $pane->subtype = 'menu_title';
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
    $pane->uuid = '6503854d-1108-4c4a-b788-f56cf4de956f';
    $display->content['new-6503854d-1108-4c4a-b788-f56cf4de956f'] = $pane;
    $display->panels['main_content'][0] = 'new-6503854d-1108-4c4a-b788-f56cf4de956f';
    $pane = new stdClass();
    $pane->pid = 'new-19961c2b-0f6f-4d74-a7cf-967a8575ccc7';
    $pane->panel = 'main_content';
    $pane->type = 'taxonomy_menu';
    $pane->subtype = 'taxonomy_menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'slug' => 'arrangementer',
      'default_link_text' => 'All categories',
      'dropdown' => 1,
      'context' => array(
        0 => 'argument_term_1',
        1 => 'argument_entity_id:node_1',
      ),
      'override_title' => 0,
      'override_title_text' => '',
      'base' => 'temaer',
      'vocabulary' => 'event_category',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '19961c2b-0f6f-4d74-a7cf-967a8575ccc7';
    $display->content['new-19961c2b-0f6f-4d74-a7cf-967a8575ccc7'] = $pane;
    $display->panels['main_content'][1] = 'new-19961c2b-0f6f-4d74-a7cf-967a8575ccc7';
    $pane = new stdClass();
    $pane->pid = 'new-f1da607d-7b57-4ba3-9d57-366153c342b7';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_event-ding_event_groups_list_group';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
        1 => 'argument_term_1',
      ),
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'f1da607d-7b57-4ba3-9d57-366153c342b7';
    $display->content['new-f1da607d-7b57-4ba3-9d57-366153c342b7'] = $pane;
    $display->panels['main_content'][2] = 'new-f1da607d-7b57-4ba3-9d57-366153c342b7';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['groups_events'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'groups_listing';
  $page->task = 'page';
  $page->admin_title = 'Groups listing';
  $page->admin_description = '';
  $page->path = 'temaer';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Themes',
    'name' => 'main-menu',
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
  $handler->name = 'page_groups_listing_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'groups_listing';
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
  $display->title = 'Themes';
  $display->uuid = '988af79c-a413-4a43-8c5d-a1b28aae2988';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-f5c30667-761e-4d84-95e3-d5d724581160';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_groups-ding_group_overview_simple';
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
    $pane->uuid = 'f5c30667-761e-4d84-95e3-d5d724581160';
    $display->content['new-f5c30667-761e-4d84-95e3-d5d724581160'] = $pane;
    $display->panels['main_content'][0] = 'new-f5c30667-761e-4d84-95e3-d5d724581160';
    $pane = new stdClass();
    $pane->pid = 'new-e806ff55-7233-4b24-9383-43f9025629a6';
    $pane->panel = 'right_sidebar';
    $pane->type = 'campaign';
    $pane->subtype = 'campaign';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'ding_campaign_count' => 3,
      'ding_campaign_offset' => 0,
      'ding_campaign_image_style' => 'medium',
      'context' => array(
        0 => 'empty',
        1 => 'empty',
        2 => 'empty',
        3 => 'empty',
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
    $pane->uuid = 'e806ff55-7233-4b24-9383-43f9025629a6';
    $display->content['new-e806ff55-7233-4b24-9383-43f9025629a6'] = $pane;
    $display->panels['right_sidebar'][0] = 'new-e806ff55-7233-4b24-9383-43f9025629a6';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-f5c30667-761e-4d84-95e3-d5d724581160';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['groups_listing'] = $page;

  return $pages;

}
