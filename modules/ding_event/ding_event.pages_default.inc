<?php
/**
 * @file
 * ding_event.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function ding_event_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'ding_event_node_view';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -28;
  $handler->conf = array(
    'title' => 'Event',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(
      0 => array(
        'identifier' => 'User',
        'keyword' => 'user',
        'name' => 'user',
        'type' => 'current',
        'uid' => NULL,
        'id' => 1,
      ),
    ),
    'relationships' => array(
      0 => array(
        'identifier' => 'OG group from event',
        'keyword' => 'group',
        'name' => 'og_group_from_node',
        'context' => 'argument_entity_id:node_1',
        'id' => 1,
      ),
      1 => array(
        'identifier' => 'Library',
        'keyword' => 'library',
        'name' => 'og_node_from_group',
        'context' => 'relationship_og_group_from_node_1',
        'id' => 1,
      ),
      2 => array(
        'identifier' => 'Multiple terms from node',
        'keyword' => 'terms',
        'name' => 'terms_from_node',
        'context' => 'argument_entity_id:node_1',
        'vid' => array(
          3 => '3',
          4 => '4',
          1 => '1',
          2 => '2',
        ),
        'concatenator' => ',',
        'id' => 1,
      ),
      3 => array(
        'identifier' => 'Category term',
        'keyword' => 'taxonomy_term',
        'name' => 'entity_from_field:field_ding_event_category-node-taxonomy_term',
        'delta' => 0,
        'context' => 'argument_entity_id:node_1',
        'id' => 1,
      ),
    ),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'ding_event' => 'ding_event',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
    'panels_breadcrumbs_state' => 1,
    'panels_breadcrumbs_titles' => 'Events
%node:title',
    'panels_breadcrumbs_paths' => 'events
<none>',
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
      'grid_10_center' => NULL,
      'grid_3_left' => NULL,
      'grid_3_right' => NULL,
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
  $display->uuid = '45175b89-df7a-48fe-8118-cb87907dc9df';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-3a3e504a-af80-4e26-a06c-ef5791e7bed9';
    $pane->panel = 'left_sidebar';
    $pane->type = 'taxonomy_menu';
    $pane->subtype = 'taxonomy_menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'slug' => 'arrangementer',
      'default_link_text' => 'All categories',
      'context' => array(
        0 => 'relationship_entity_from_field:field_ding_event_category-node-taxonomy_term_1',
        1 => 'empty',
      ),
      'override_title' => 0,
      'override_title_text' => '',
      'dropdown' => 0,
      'vocabulary' => 'event_category',
      'base' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '3a3e504a-af80-4e26-a06c-ef5791e7bed9';
    $display->content['new-3a3e504a-af80-4e26-a06c-ef5791e7bed9'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-3a3e504a-af80-4e26-a06c-ef5791e7bed9';
    $pane = new stdClass();
    $pane->pid = 'new-a6229377-5925-4728-a26a-48d1d33263ee';
    $pane->panel = 'main_content';
    $pane->type = 'node_content';
    $pane->subtype = 'node_content';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'links' => 1,
      'no_extras' => 0,
      'override_title' => 0,
      'override_title_text' => '',
      'identifier' => '',
      'link' => 0,
      'leave_node_title' => 1,
      'build_mode' => 'full',
      'context' => 'argument_entity_id:node_1',
    );
    $pane->cache = array(
      'method' => '0',
      'settings' => array(),
    );
    $pane->style = array(
      'settings' => NULL,
      'style' => 'naked',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = 'a6229377-5925-4728-a26a-48d1d33263ee';
    $display->content['new-a6229377-5925-4728-a26a-48d1d33263ee'] = $pane;
    $display->panels['main_content'][0] = 'new-a6229377-5925-4728-a26a-48d1d33263ee';
    $pane = new stdClass();
    $pane->pid = 'new-23d5cf27-1799-4f37-9a67-13e1878d7456';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_event-ding_event_list_same_tag';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'relationship_entity_from_field:field_ding_event_category-node-taxonomy_term_1',
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '23d5cf27-1799-4f37-9a67-13e1878d7456';
    $display->content['new-23d5cf27-1799-4f37-9a67-13e1878d7456'] = $pane;
    $display->panels['main_content'][1] = 'new-23d5cf27-1799-4f37-9a67-13e1878d7456';
    $pane = new stdClass();
    $pane->pid = 'new-eb8809fa-a45d-4afe-836c-c22a6ed8a064';
    $pane->panel = 'right_sidebar';
    $pane->type = 'campaign';
    $pane->subtype = 'campaign';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'ding_campaign_count' => 3,
      'ding_campaign_offset' => 0,
      'context' => array(
        0 => 'argument_entity_id:node_1',
        1 => 'relationship_og_node_from_group_1',
        2 => 'empty',
        3 => 'relationship_terms_from_node_1',
      ),
      'override_title' => 0,
      'override_title_text' => '',
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
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = 'eb8809fa-a45d-4afe-836c-c22a6ed8a064';
    $display->content['new-eb8809fa-a45d-4afe-836c-c22a6ed8a064'] = $pane;
    $display->panels['right_sidebar'][0] = 'new-eb8809fa-a45d-4afe-836c-c22a6ed8a064';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['ding_event_node_view'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'term_view_panel_context';
  $handler->task = 'term_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 2;
  $handler->conf = array(
    'title' => 'Ding events',
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
        1 => array(
          'name' => 'entity_bundle:taxonomy_term',
          'settings' => array(
            'type' => array(
              'event_category' => 'event_category',
            ),
          ),
          'context' => 'argument_term_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
    'panels_breadcrumbs_state' => 1,
    'panels_breadcrumbs_titles' => 'Events
%term:name',
    'panels_breadcrumbs_paths' => 'events
taxonomy/term/%term:tid',
    'panels_breadcrumbs_home' => 1,
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
  $display->title = 'Events';
  $display->uuid = 'e6d7ce53-caaa-4af3-8588-00d36e8d512a';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-69e61890-8dde-42c3-b8e4-192813161a0c';
    $pane->panel = 'left_sidebar';
    $pane->type = 'taxonomy_menu';
    $pane->subtype = 'taxonomy_menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'slug' => 'arrangementer',
      'default_link_text' => 'All categories',
      'context' => array(
        0 => 'argument_term_1',
        1 => 'empty',
      ),
      'override_title' => 0,
      'override_title_text' => '',
      'dropdown' => 0,
      'vocabulary' => 'event_category',
      'base' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '69e61890-8dde-42c3-b8e4-192813161a0c';
    $display->content['new-69e61890-8dde-42c3-b8e4-192813161a0c'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-69e61890-8dde-42c3-b8e4-192813161a0c';
    $pane = new stdClass();
    $pane->pid = 'new-ee39a7cd-921c-4424-97bf-5ab8d9033c6f';
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
    $pane->uuid = 'ee39a7cd-921c-4424-97bf-5ab8d9033c6f';
    $display->content['new-ee39a7cd-921c-4424-97bf-5ab8d9033c6f'] = $pane;
    $display->panels['main_content'][0] = 'new-ee39a7cd-921c-4424-97bf-5ab8d9033c6f';
    $pane = new stdClass();
    $pane->pid = 'new-182ac438-746a-48a7-b7f2-1a696f14b582';
    $pane->panel = 'main_content';
    $pane->type = 'library_list';
    $pane->subtype = 'library_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'type' => 'ding_event',
      'context' => array(
        0 => 'argument_term_1',
        1 => 'empty',
      ),
      'override_title' => 0,
      'override_title_text' => '',
      'slug' => 'arrangementer',
      'hide_default' => 0,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '182ac438-746a-48a7-b7f2-1a696f14b582';
    $display->content['new-182ac438-746a-48a7-b7f2-1a696f14b582'] = $pane;
    $display->panels['main_content'][1] = 'new-182ac438-746a-48a7-b7f2-1a696f14b582';
    $pane = new stdClass();
    $pane->pid = 'new-3cb95651-0650-42f1-a8bd-e56688d1a4aa';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_event-ding_event_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_term_1',
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '3cb95651-0650-42f1-a8bd-e56688d1a4aa';
    $display->content['new-3cb95651-0650-42f1-a8bd-e56688d1a4aa'] = $pane;
    $display->panels['main_content'][2] = 'new-3cb95651-0650-42f1-a8bd-e56688d1a4aa';
    $pane = new stdClass();
    $pane->pid = 'new-e96436de-1a68-4813-91aa-63662d84d299';
    $pane->panel = 'right_sidebar';
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
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'e96436de-1a68-4813-91aa-63662d84d299';
    $display->content['new-e96436de-1a68-4813-91aa-63662d84d299'] = $pane;
    $display->panels['right_sidebar'][0] = 'new-e96436de-1a68-4813-91aa-63662d84d299';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['term_view_panel_context'] = $handler;

  return $export;
}

/**
 * Implements hook_default_page_manager_pages().
 */
function ding_event_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'ding_events';
  $page->task = 'page';
  $page->admin_title = 'Ding events';
  $page->admin_description = 'Display the events';
  $page->path = 'arrangementer/!tid';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'perm',
        'settings' => array(
          'perm' => 'access content',
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Events',
    'name' => 'main-menu',
    'weight' => '0',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array(
    'tid' => array(
      'id' => 1,
      'identifier' => 'Category term',
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
  $handler->name = 'page_ding_events_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'ding_events';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Ding events',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'panels_breadcrumbs_state' => 1,
    'panels_breadcrumbs_titles' => 'Home
Events
%tid:name',
    'panels_breadcrumbs_paths' => '<front>
events
<none>',
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
  $display->title = 'Events';
  $display->uuid = 'd49a3b8f-8e68-4ec6-8382-b2d01945b356';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-48f2820d-1223-41f2-ae05-0fa1e907a1a8';
    $pane->panel = 'left_sidebar';
    $pane->type = 'taxonomy_menu';
    $pane->subtype = 'taxonomy_menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_term_1',
        1 => 'empty',
      ),
      'override_title' => 0,
      'override_title_text' => '',
      'slug' => 'arrangementer',
      'default_link' => 'All categories',
      'default_link_text' => 'All categories',
      'dropdown' => 0,
      'vocabulary' => 'event_category',
      'base' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '48f2820d-1223-41f2-ae05-0fa1e907a1a8';
    $display->content['new-48f2820d-1223-41f2-ae05-0fa1e907a1a8'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-48f2820d-1223-41f2-ae05-0fa1e907a1a8';
    $pane = new stdClass();
    $pane->pid = 'new-6961a9f1-4b6a-4bcd-95b2-ca9e6655b1ff';
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
    $pane->locks = '';
    $pane->uuid = '6961a9f1-4b6a-4bcd-95b2-ca9e6655b1ff';
    $display->content['new-6961a9f1-4b6a-4bcd-95b2-ca9e6655b1ff'] = $pane;
    $display->panels['main_content'][0] = 'new-6961a9f1-4b6a-4bcd-95b2-ca9e6655b1ff';
    $pane = new stdClass();
    $pane->pid = 'new-d603ce6a-0b1f-4a83-81ac-a9db9c950d31';
    $pane->panel = 'main_content';
    $pane->type = 'library_list';
    $pane->subtype = 'library_list';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'library_count',
          'settings' => array(
            'count' => '1',
          ),
          'not' => TRUE,
        ),
      ),
    );
    $pane->configuration = array(
      'type' => 'ding_event',
      'context' => array(
        0 => 'argument_term_1',
        1 => 'empty',
      ),
      'override_title' => 0,
      'override_title_text' => '',
      'slug' => 'arrangementer',
      'hide_default' => 0,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = '';
    $pane->uuid = 'd603ce6a-0b1f-4a83-81ac-a9db9c950d31';
    $display->content['new-d603ce6a-0b1f-4a83-81ac-a9db9c950d31'] = $pane;
    $display->panels['main_content'][1] = 'new-d603ce6a-0b1f-4a83-81ac-a9db9c950d31';
    $pane = new stdClass();
    $pane->pid = 'new-5d683c57-a79e-4d16-9046-d2dc04a557d5';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_event-ding_event_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_term_1',
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '5d683c57-a79e-4d16-9046-d2dc04a557d5';
    $display->content['new-5d683c57-a79e-4d16-9046-d2dc04a557d5'] = $pane;
    $display->panels['main_content'][2] = 'new-5d683c57-a79e-4d16-9046-d2dc04a557d5';
    $pane = new stdClass();
    $pane->pid = 'new-fb32e006-e3f2-4f14-a1a2-0513758f77e8';
    $pane->panel = 'right_sidebar';
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
      ),
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array(
      'method' => 'simple',
      'settings' => array(
        'lifetime' => '600',
        'granularity' => 'none',
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = 'fb32e006-e3f2-4f14-a1a2-0513758f77e8';
    $display->content['new-fb32e006-e3f2-4f14-a1a2-0513758f77e8'] = $pane;
    $display->panels['right_sidebar'][0] = 'new-fb32e006-e3f2-4f14-a1a2-0513758f77e8';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['ding_events'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'ding_events_library';
  $page->task = 'page';
  $page->admin_title = 'Library events page';
  $page->admin_description = '';
  $page->path = 'bibliotek/%slug/arrangementer/!tid';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'perm',
        'settings' => array(
          'perm' => 'access content',
        ),
        'context' => 'logged-in-user',
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
    'tid' => array(
      'id' => 1,
      'identifier' => 'Event category term',
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
  $handler->name = 'page_ding_events_library_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'ding_events_library';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Library events',
    'no_blocks' => 0,
    'pipeline' => 'standard',
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
    'panels_breadcrumbs_state' => 1,
    'panels_breadcrumbs_titles' => 'Libraries
%node:title
Events
%tid:name',
    'panels_breadcrumbs_paths' => 'libraries
node/%node:nid
node/%node:nid/events
<none>',
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
  $display->uuid = '242cdbfd-b37b-4e9e-b3b0-415f58651d59';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-806db16f-e712-43d5-872a-01cf6482a01c';
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
    $pane->uuid = '806db16f-e712-43d5-872a-01cf6482a01c';
    $display->content['new-806db16f-e712-43d5-872a-01cf6482a01c'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-806db16f-e712-43d5-872a-01cf6482a01c';
    $pane = new stdClass();
    $pane->pid = 'new-3acc109a-2590-47a1-b9a4-66c45aae8a58';
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
    $pane->locks = '';
    $pane->uuid = '3acc109a-2590-47a1-b9a4-66c45aae8a58';
    $display->content['new-3acc109a-2590-47a1-b9a4-66c45aae8a58'] = $pane;
    $display->panels['main_content'][0] = 'new-3acc109a-2590-47a1-b9a4-66c45aae8a58';
    $pane = new stdClass();
    $pane->pid = 'new-8c3dcd03-d791-4895-b8af-fb15d1d090bb';
    $pane->panel = 'main_content';
    $pane->type = 'taxonomy_menu';
    $pane->subtype = 'taxonomy_menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'slug' => 'arrangementer',
      'default_link_text' => 'All categories',
      'context' => array(
        0 => 'argument_term_1',
        1 => 'argument_slug_1',
      ),
      'override_title' => 0,
      'override_title_text' => '',
      'dropdown' => 1,
      'base' => 'bibliotek',
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
    $pane->uuid = '8c3dcd03-d791-4895-b8af-fb15d1d090bb';
    $display->content['new-8c3dcd03-d791-4895-b8af-fb15d1d090bb'] = $pane;
    $display->panels['main_content'][1] = 'new-8c3dcd03-d791-4895-b8af-fb15d1d090bb';
    $pane = new stdClass();
    $pane->pid = 'new-9bb644a0-3601-4ce3-a16a-c32dd13c12da';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_event-ding_event_list_library';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_slug_1',
        1 => 'argument_term_1',
      ),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '9bb644a0-3601-4ce3-a16a-c32dd13c12da';
    $display->content['new-9bb644a0-3601-4ce3-a16a-c32dd13c12da'] = $pane;
    $display->panels['main_content'][2] = 'new-9bb644a0-3601-4ce3-a16a-c32dd13c12da';
    $pane = new stdClass();
    $pane->pid = 'new-150601e8-429a-4460-8500-c20fc264900a';
    $pane->panel = 'right_sidebar';
    $pane->type = 'campaign';
    $pane->subtype = 'campaign';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'ding_campaign_count' => 3,
      'ding_campaign_offset' => 0,
      'context' => array(
        0 => 'empty',
        1 => 'argument_entity_id:node_1',
        2 => 'empty',
        3 => 'empty',
      ),
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array(
      'method' => 'simple',
      'settings' => array(
        'lifetime' => '1200',
        'granularity' => 'args',
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = '150601e8-429a-4460-8500-c20fc264900a';
    $display->content['new-150601e8-429a-4460-8500-c20fc264900a'] = $pane;
    $display->panels['right_sidebar'][0] = 'new-150601e8-429a-4460-8500-c20fc264900a';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['ding_events_library'] = $page;

  return $pages;

}
