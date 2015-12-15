<?php
/**
 * @file
 * ding_library.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function ding_library_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view_panel_context_3';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -27;
  $handler->conf = array(
    'title' => 'Library (organic group)',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => 'ding-library-front',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'ding_library' => 'ding_library',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'og_is_node_group',
          'settings' => NULL,
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
      'left' => NULL,
      'right' => NULL,
      'top' => NULL,
      'middle' => NULL,
      'bottom' => NULL,
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
  $display->title = '%node:title';
  $display->uuid = 'a6f6496f-682d-4e38-b2a8-18197fe211fd';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-265e2bee-9412-47c5-b0bd-502ed0ac5676';
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
    $pane->uuid = '265e2bee-9412-47c5-b0bd-502ed0ac5676';
    $display->content['new-265e2bee-9412-47c5-b0bd-502ed0ac5676'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-265e2bee-9412-47c5-b0bd-502ed0ac5676';
    $pane = new stdClass();
    $pane->pid = 'new-acf0a41a-33dc-41d3-8f5f-a539f1c2dddd';
    $pane->panel = 'main_content';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_ding_library_title_image';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'cs_adaptive_image',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'image_style' => 'ding_large',
        'image_link' => '',
        'styles' => array(
          'breakpoint_1' => '768',
          'style_1' => 'ding_secondary_medium',
          'breakpoint_2' => '500',
          'style_2' => 'ding_secondary_small',
          'max_style' => 'ding_secondary_large',
          'fallback_style' => 'ding_secondary_large',
        ),
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array(
      'method' => '0',
      'settings' => array(),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'ding-library-image',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'acf0a41a-33dc-41d3-8f5f-a539f1c2dddd';
    $display->content['new-acf0a41a-33dc-41d3-8f5f-a539f1c2dddd'] = $pane;
    $display->panels['main_content'][0] = 'new-acf0a41a-33dc-41d3-8f5f-a539f1c2dddd';
    $pane = new stdClass();
    $pane->pid = 'new-4bf5048e-e0db-458b-95a7-779a093a9c29';
    $pane->panel = 'main_content';
    $pane->type = 'address';
    $pane->subtype = 'address';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'ding-library-address',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '4bf5048e-e0db-458b-95a7-779a093a9c29';
    $display->content['new-4bf5048e-e0db-458b-95a7-779a093a9c29'] = $pane;
    $display->panels['main_content'][1] = 'new-4bf5048e-e0db-458b-95a7-779a093a9c29';
    $pane = new stdClass();
    $pane->pid = 'new-4602ba44-8551-4fb5-bc15-d71383f42cbc';
    $pane->panel = 'main_content';
    $pane->type = 'contact';
    $pane->subtype = 'contact';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
      'context' => 'argument_entity_id:node_1',
    );
    $pane->cache = array(
      'method' => 'simple',
      'settings' => array(
        'lifetime' => '600',
        'granularity' => 'context',
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'ding-library-contact',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = '';
    $pane->uuid = '4602ba44-8551-4fb5-bc15-d71383f42cbc';
    $display->content['new-4602ba44-8551-4fb5-bc15-d71383f42cbc'] = $pane;
    $display->panels['main_content'][2] = 'new-4602ba44-8551-4fb5-bc15-d71383f42cbc';
    $pane = new stdClass();
    $pane->pid = 'new-21110f84-c932-4a89-8505-63d45b61c778';
    $pane->panel = 'main_content';
    $pane->type = 'week';
    $pane->subtype = 'week';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'hide_if_empty' => 0,
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'ding-library-opening-hours js-opening-hours-toggle-element',
    );
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '21110f84-c932-4a89-8505-63d45b61c778';
    $display->content['new-21110f84-c932-4a89-8505-63d45b61c778'] = $pane;
    $display->panels['main_content'][3] = 'new-21110f84-c932-4a89-8505-63d45b61c778';
    $pane = new stdClass();
    $pane->pid = 'new-e75bb4dd-8e1f-4738-b12c-d02f04cd587b';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_news-ding_news_library_list';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'entity_field_value:node:ding_library:field_hide_news_and_events',
          'settings' => array(
            'field_hide_news_and_events' => array(
              'und' => array(
                0 => array(
                  'value' => 0,
                ),
              ),
            ),
            'field_hide_news_and_events_value' => NULL,
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
    );
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
      'css_class' => 'ding-library-news',
    );
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = 'e75bb4dd-8e1f-4738-b12c-d02f04cd587b';
    $display->content['new-e75bb4dd-8e1f-4738-b12c-d02f04cd587b'] = $pane;
    $display->panels['main_content'][4] = 'new-e75bb4dd-8e1f-4738-b12c-d02f04cd587b';
    $pane = new stdClass();
    $pane->pid = 'new-0d5ac3d3-3666-431f-8672-226f8d6b8694';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_event-ding_event_library_list';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'entity_field_value:node:ding_library:field_hide_news_and_events',
          'settings' => array(
            'field_hide_news_and_events' => array(
              'und' => array(
                0 => array(
                  'value' => 0,
                ),
              ),
            ),
            'field_hide_news_and_events_value' => NULL,
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Library events',
      'arguments' => array(
        'og_group_ref_target_id' => '',
      ),
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'ding-library-events',
    );
    $pane->extras = array();
    $pane->position = 5;
    $pane->locks = array();
    $pane->uuid = '0d5ac3d3-3666-431f-8672-226f8d6b8694';
    $display->content['new-0d5ac3d3-3666-431f-8672-226f8d6b8694'] = $pane;
    $display->panels['main_content'][5] = 'new-0d5ac3d3-3666-431f-8672-226f8d6b8694';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view_panel_context_3'] = $handler;

  return $export;
}

/**
 * Implements hook_default_page_manager_pages().
 */
function ding_library_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'ding_libraries';
  $page->task = 'page';
  $page->admin_title = 'Ding libraries';
  $page->admin_description = 'Detailed list of all local libraries on the site.';
  $page->path = 'libraries';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Libraries',
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
  $handler->name = 'page_ding_libraries_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'ding_libraries';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Ding libraries',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => 'ding-library-page',
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
      'top' => NULL,
      'left' => NULL,
      'middle' => NULL,
      'right' => NULL,
      'bottom' => NULL,
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
  $display->title = 'Libraries';
  $display->uuid = '608e59aa-498b-4237-b789-65edaaf222de';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-265108a0-31ea-47f3-9b44-376a47724f4a';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_library-ding_library_leaflet';
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
    $pane->uuid = '265108a0-31ea-47f3-9b44-376a47724f4a';
    $display->content['new-265108a0-31ea-47f3-9b44-376a47724f4a'] = $pane;
    $display->panels['main_content'][0] = 'new-265108a0-31ea-47f3-9b44-376a47724f4a';
    $pane = new stdClass();
    $pane->pid = 'new-1e2eec2e-7d03-48ca-b59c-76ce5247dff7';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_library-ding_library_libraries_list';
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '1e2eec2e-7d03-48ca-b59c-76ce5247dff7';
    $display->content['new-1e2eec2e-7d03-48ca-b59c-76ce5247dff7'] = $pane;
    $display->panels['main_content'][1] = 'new-1e2eec2e-7d03-48ca-b59c-76ce5247dff7';
    $pane = new stdClass();
    $pane->pid = 'new-d62be472-164d-4035-8ac5-a92a0ca855ae';
    $pane->panel = 'left_sidebar';
    $pane->type = 'campaign';
    $pane->subtype = 'campaign';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'ding_campaign_count' => 3,
      'ding_campaign_offset' => 0,
      'context' => array(
        0 => 'empty',
        1 => 'empty',
        2 => 'empty',
        3 => 'empty',
      ),
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array(
      'method' => 'simple',
      'settings' => array(
        'lifetime' => '3600',
        'granularity' => 'context',
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = 'd62be472-164d-4035-8ac5-a92a0ca855ae';
    $display->content['new-d62be472-164d-4035-8ac5-a92a0ca855ae'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-d62be472-164d-4035-8ac5-a92a0ca855ae';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['ding_libraries'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'ding_library_about';
  $page->task = 'page';
  $page->admin_title = 'About library';
  $page->admin_description = '';
  $page->path = 'bibliotek/%slug/om';
  $page->access = array(
    'plugins' => array(
      2 => array(
        'name' => 'node_access',
        'settings' => array(
          'type' => 'view',
        ),
        'context' => array(
          0 => 'logged-in-user',
          1 => 'argument_entity_id:node_1',
        ),
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array(
    'slug' => array(
      'id' => 1,
      'identifier' => 'Library node',
      'name' => 'slug',
      'settings' => array(),
      'keyword' => 'slug',
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_ding_library_about_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'ding_library_about';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => 'ding-library-about',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'ding_library' => 'ding_library',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'og_is_node_group',
          'settings' => NULL,
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
      'left' => NULL,
      'middle' => NULL,
      'right' => NULL,
      'top' => NULL,
      'bottom' => NULL,
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
  $display->uuid = '895bbe6b-994e-46a3-8ef1-3c2b968fcf51';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-66e40086-6a23-4d03-b022-c3d7e5cbf914';
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
    $pane->uuid = '66e40086-6a23-4d03-b022-c3d7e5cbf914';
    $display->content['new-66e40086-6a23-4d03-b022-c3d7e5cbf914'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-66e40086-6a23-4d03-b022-c3d7e5cbf914';
    $pane = new stdClass();
    $pane->pid = 'new-bd3bb4dd-dc12-4b88-9d1a-a61d32542553';
    $pane->panel = 'main_content';
    $pane->type = 'menu_title';
    $pane->subtype = 'menu_title';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array(
      'method' => 'rules',
      'settings' => array(
        'granularity' => 'context',
        'language' => 1,
        'language_content' => 0,
        'advanced' => array(),
        'cache_key' => '5059b585d2856',
        'substitute' => 0,
        'new' => TRUE,
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = 'bd3bb4dd-dc12-4b88-9d1a-a61d32542553';
    $display->content['new-bd3bb4dd-dc12-4b88-9d1a-a61d32542553'] = $pane;
    $display->panels['main_content'][0] = 'new-bd3bb4dd-dc12-4b88-9d1a-a61d32542553';
    $pane = new stdClass();
    $pane->pid = 'new-0be7b2bd-f791-4cfe-8650-df3f3bfa146d';
    $pane->panel = 'main_content';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_ding_library_title_image';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'cs_adaptive_image',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'image_style' => 'ding_medium',
        'image_link' => '',
        'styles' => array(
          'breakpoint_1' => '768',
          'style_1' => 'ding_primary_medium',
          'breakpoint_2' => '500',
          'style_2' => 'ding_primary_small',
          'max_style' => 'ding_primary_large',
          'fallback_style' => 'ding_primary_large',
        ),
      ),
      'context' => 'argument_entity_id:node_1',
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
    $pane->uuid = '0be7b2bd-f791-4cfe-8650-df3f3bfa146d';
    $display->content['new-0be7b2bd-f791-4cfe-8650-df3f3bfa146d'] = $pane;
    $display->panels['main_content'][1] = 'new-0be7b2bd-f791-4cfe-8650-df3f3bfa146d';
    $pane = new stdClass();
    $pane->pid = 'new-340e4d90-b7d8-430c-9e38-f14b9d6f3320';
    $pane->panel = 'main_content';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_ding_library_body';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
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
    $pane->uuid = '340e4d90-b7d8-430c-9e38-f14b9d6f3320';
    $display->content['new-340e4d90-b7d8-430c-9e38-f14b9d6f3320'] = $pane;
    $display->panels['main_content'][2] = 'new-340e4d90-b7d8-430c-9e38-f14b9d6f3320';
    $pane = new stdClass();
    $pane->pid = 'new-c05787bc-8016-4669-8c82-10c349af2dea';
    $pane->panel = 'left_sidebar';
    $pane->type = 'contact';
    $pane->subtype = 'contact';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array(
      'method' => 'rules',
      'settings' => array(
        'granularity' => 'context',
        'language' => 1,
        'language_content' => 0,
        'advanced' => array(),
        'cache_key' => '5059b59c7bd40',
        'substitute' => 0,
        'new' => TRUE,
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'ding-library-contact',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = '';
    $pane->uuid = 'c05787bc-8016-4669-8c82-10c349af2dea';
    $display->content['new-c05787bc-8016-4669-8c82-10c349af2dea'] = $pane;
    $display->panels['left_sidebar'][1] = 'new-c05787bc-8016-4669-8c82-10c349af2dea';
    $pane = new stdClass();
    $pane->pid = 'new-71b33eb2-cf7e-4599-a7fb-2958933fe904';
    $pane->panel = 'left_sidebar';
    $pane->type = 'campaign';
    $pane->subtype = 'campaign';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'ding_campaign_count' => 3,
      'ding_campaign_offset' => 0,
      'context' => array(
        0 => 'empty',
        1 => 'empty',
        2 => 'empty',
        3 => 'empty',
      ),
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array(
      'method' => 'rules',
      'settings' => array(
        'granularity' => 'context',
        'language' => 1,
        'language_content' => 0,
        'advanced' => array(),
        'cache_key' => '5059b5b12c9bf',
        'substitute' => 0,
        'new' => TRUE,
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = '';
    $pane->uuid = '71b33eb2-cf7e-4599-a7fb-2958933fe904';
    $display->content['new-71b33eb2-cf7e-4599-a7fb-2958933fe904'] = $pane;
    $display->panels['left_sidebar'][2] = 'new-71b33eb2-cf7e-4599-a7fb-2958933fe904';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['ding_library_about'] = $page;

  return $pages;

}
