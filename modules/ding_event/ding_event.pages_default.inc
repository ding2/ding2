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
  $handler->weight = -27;
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
    'metatag_panels' => array(
      'enabled' => 1,
      'metatags' => array(
        'title' => array(
          'value' => '[node:title] | [current-page:pager][site:name]',
        ),
        'description' => array(
          'value' => '[node:field_ding_event_lead] - [node:og_group_ref] - [node:field-ding-event-date:value] - [node:field_ding_event_price] kr.',
        ),
        'image_src' => array(
          'value' => '[node:field_ding_event_title_image]',
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
      'branding' => NULL,
      'header' => NULL,
      'navigation' => NULL,
      'content' => NULL,
      'footer' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = '45175b89-df7a-48fe-8118-cb87907dc9df';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-a6229377-5925-4728-a26a-48d1d33263ee';
    $pane->panel = 'attachment_1_1';
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
    $display->panels['attachment_1_1'][0] = 'new-a6229377-5925-4728-a26a-48d1d33263ee';
    $pane = new stdClass();
    $pane->pid = 'new-a4e41bd1-00ba-4f94-afa8-3e20064bb082';
    $pane->panel = 'attachment_1_1';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_ding_event_materials';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'title',
      'formatter' => 'ding_carousel',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(
        'view_mode' => 'teaser',
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'grid-small no-gradient',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'a4e41bd1-00ba-4f94-afa8-3e20064bb082';
    $display->content['new-a4e41bd1-00ba-4f94-afa8-3e20064bb082'] = $pane;
    $display->panels['attachment_1_1'][1] = 'new-a4e41bd1-00ba-4f94-afa8-3e20064bb082';
    $pane = new stdClass();
    $pane->pid = 'new-6edd44b6-c604-4732-885f-2765820bb2a7';
    $pane->panel = 'attachment_1_1';
    $pane->type = 'ding_campaign_plus';
    $pane->subtype = 'ding_campaign_plus';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'style' => 'ribbon',
      'context' => array(
        0 => 'argument_entity_id:node_1',
        1 => 'argument_entity_id:node_1',
        2 => 'empty',
        3 => 'relationship_terms_from_node_1',
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '6edd44b6-c604-4732-885f-2765820bb2a7';
    $display->content['new-6edd44b6-c604-4732-885f-2765820bb2a7'] = $pane;
    $display->panels['attachment_1_1'][2] = 'new-6edd44b6-c604-4732-885f-2765820bb2a7';
    $pane = new stdClass();
    $pane->pid = 'new-8fa01e13-dc8b-4ce2-b791-60e54159e8d7';
    $pane->panel = 'attachment_1_1';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_related_content-news_events';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Related',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '8fa01e13-dc8b-4ce2-b791-60e54159e8d7';
    $display->content['new-8fa01e13-dc8b-4ce2-b791-60e54159e8d7'] = $pane;
    $display->panels['attachment_1_1'][3] = 'new-8fa01e13-dc8b-4ce2-b791-60e54159e8d7';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['ding_event_node_view'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'term_view__ding-organizer';
  $handler->task = 'term_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 6;
  $handler->conf = array(
    'title' => 'Ding organizer',
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
            'machine_name' => array(
              'event_organizer' => 'event_organizer',
            ),
          ),
          'context' => 'argument_term_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
    'name' => 'ding-organizer',
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
      'top_banner' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%term:name';
  $display->uuid = '4b241667-11e0-4198-b244-e01ca4d6529d';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-e433f54f-8481-4005-b77f-02c5a4c341d5';
    $pane->panel = 'attachment_1_1';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'grid-medium',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'e433f54f-8481-4005-b77f-02c5a4c341d5';
    $display->content['new-e433f54f-8481-4005-b77f-02c5a4c341d5'] = $pane;
    $display->panels['attachment_1_1'][0] = 'new-e433f54f-8481-4005-b77f-02c5a4c341d5';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['term_view__ding-organizer'] = $handler;

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
    $pane->pid = 'new-6e9f816e-5b11-47ae-aaea-ffecb41d4ac3';
    $pane->panel = 'left_sidebar';
    $pane->type = 'page_title';
    $pane->subtype = 'page_title';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'markup' => 'h2',
      'class' => '',
      'id' => '',
      'override_title' => 1,
      'override_title_text' => 'Arrangementer',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '6e9f816e-5b11-47ae-aaea-ffecb41d4ac3';
    $display->content['new-6e9f816e-5b11-47ae-aaea-ffecb41d4ac3'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-6e9f816e-5b11-47ae-aaea-ffecb41d4ac3';
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '69e61890-8dde-42c3-b8e4-192813161a0c';
    $display->content['new-69e61890-8dde-42c3-b8e4-192813161a0c'] = $pane;
    $display->panels['left_sidebar'][1] = 'new-69e61890-8dde-42c3-b8e4-192813161a0c';
    $pane = new stdClass();
    $pane->pid = 'new-e96436de-1a68-4813-91aa-63662d84d299';
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
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'e96436de-1a68-4813-91aa-63662d84d299';
    $display->content['new-e96436de-1a68-4813-91aa-63662d84d299'] = $pane;
    $display->panels['left_sidebar'][2] = 'new-e96436de-1a68-4813-91aa-63662d84d299';
    $pane = new stdClass();
    $pane->pid = 'new-d74a03a2-ca3d-4e54-8d60-b6e638cfa224';
    $pane->panel = 'left_sidebar';
    $pane->type = 'ding_campaign_plus';
    $pane->subtype = 'ding_campaign_plus';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'style' => 'box',
      'context' => array(
        0 => 'empty',
        1 => 'empty',
        2 => 'argument_string_1',
        3 => 'argument_term_1',
      ),
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = 'd74a03a2-ca3d-4e54-8d60-b6e638cfa224';
    $display->content['new-d74a03a2-ca3d-4e54-8d60-b6e638cfa224'] = $pane;
    $display->panels['left_sidebar'][3] = 'new-d74a03a2-ca3d-4e54-8d60-b6e638cfa224';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'grid-medium',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '3cb95651-0650-42f1-a8bd-e56688d1a4aa';
    $display->content['new-3cb95651-0650-42f1-a8bd-e56688d1a4aa'] = $pane;
    $display->panels['main_content'][0] = 'new-3cb95651-0650-42f1-a8bd-e56688d1a4aa';
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
    'metatag_panels' => array(
      'enabled' => 1,
      'metatags' => array(
        'title' => array(
          'value' => 'Events | [current-page:pager][site:name]',
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
    $pane->pid = 'new-6961a9f1-4b6a-4bcd-95b2-ca9e6655b1ff';
    $pane->panel = 'left_sidebar';
    $pane->type = 'menu_title';
    $pane->subtype = 'menu_title';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h1',
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
    $display->panels['left_sidebar'][0] = 'new-6961a9f1-4b6a-4bcd-95b2-ca9e6655b1ff';
    $pane = new stdClass();
    $pane->pid = 'new-585c8154-7b8f-4b93-95cf-b4109fe22671';
    $pane->panel = 'left_sidebar';
    $pane->type = 'block';
    $pane->subtype = 'views--exp-ding_event-ding_event_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'inherit_path' => 1,
      'override_title' => 0,
      'override_title_text' => 'Date',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '585c8154-7b8f-4b93-95cf-b4109fe22671';
    $display->content['new-585c8154-7b8f-4b93-95cf-b4109fe22671'] = $pane;
    $display->panels['left_sidebar'][1] = 'new-585c8154-7b8f-4b93-95cf-b4109fe22671';
    $pane = new stdClass();
    $pane->pid = 'new-fb32e006-e3f2-4f14-a1a2-0513758f77e8';
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
    $pane->position = 2;
    $pane->locks = '';
    $pane->uuid = 'fb32e006-e3f2-4f14-a1a2-0513758f77e8';
    $display->content['new-fb32e006-e3f2-4f14-a1a2-0513758f77e8'] = $pane;
    $display->panels['left_sidebar'][2] = 'new-fb32e006-e3f2-4f14-a1a2-0513758f77e8';
    $pane = new stdClass();
    $pane->pid = 'new-ce509a1c-beb2-4c57-8640-cb3ddc482bce';
    $pane->panel = 'left_sidebar';
    $pane->type = 'ding_campaign_plus';
    $pane->subtype = 'ding_campaign_plus';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'style' => 'box',
      'context' => array(
        0 => 'empty',
        1 => 'empty',
        2 => 'empty',
        3 => 'argument_term_1',
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
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = 'ce509a1c-beb2-4c57-8640-cb3ddc482bce';
    $display->content['new-ce509a1c-beb2-4c57-8640-cb3ddc482bce'] = $pane;
    $display->panels['left_sidebar'][3] = 'new-ce509a1c-beb2-4c57-8640-cb3ddc482bce';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'grid-medium',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '5d683c57-a79e-4d16-9046-d2dc04a557d5';
    $display->content['new-5d683c57-a79e-4d16-9046-d2dc04a557d5'] = $pane;
    $display->panels['main_content'][0] = 'new-5d683c57-a79e-4d16-9046-d2dc04a557d5';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-585c8154-7b8f-4b93-95cf-b4109fe22671';
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
    'metatag_panels' => array(
      'enabled' => 1,
      'metatags' => array(
        'title' => array(
          'value' => '%slug:title | Events | [current-page:pager][site:name]',
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
    $pane->pid = 'new-3acc109a-2590-47a1-b9a4-66c45aae8a58';
    $pane->panel = 'left_sidebar';
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
    $display->panels['left_sidebar'][0] = 'new-3acc109a-2590-47a1-b9a4-66c45aae8a58';
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '806db16f-e712-43d5-872a-01cf6482a01c';
    $display->content['new-806db16f-e712-43d5-872a-01cf6482a01c'] = $pane;
    $display->panels['left_sidebar'][1] = 'new-806db16f-e712-43d5-872a-01cf6482a01c';
    $pane = new stdClass();
    $pane->pid = 'new-8c3dcd03-d791-4895-b8af-fb15d1d090bb';
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
        1 => 'argument_slug_1',
      ),
      'override_title' => 0,
      'override_title_text' => '',
      'dropdown' => 0,
      'base' => 'bibliotek',
      'vocabulary' => 'event_category',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '8c3dcd03-d791-4895-b8af-fb15d1d090bb';
    $display->content['new-8c3dcd03-d791-4895-b8af-fb15d1d090bb'] = $pane;
    $display->panels['left_sidebar'][2] = 'new-8c3dcd03-d791-4895-b8af-fb15d1d090bb';
    $pane = new stdClass();
    $pane->pid = 'new-150601e8-429a-4460-8500-c20fc264900a';
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
    $pane->position = 3;
    $pane->locks = '';
    $pane->uuid = '150601e8-429a-4460-8500-c20fc264900a';
    $display->content['new-150601e8-429a-4460-8500-c20fc264900a'] = $pane;
    $display->panels['left_sidebar'][3] = 'new-150601e8-429a-4460-8500-c20fc264900a';
    $pane = new stdClass();
    $pane->pid = 'new-4f3d4064-bf6d-4734-8125-94dbb93d91c0';
    $pane->panel = 'left_sidebar';
    $pane->type = 'ding_campaign_plus';
    $pane->subtype = 'ding_campaign_plus';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'style' => 'box',
      'context' => array(
        0 => 'argument_slug_1',
        1 => 'argument_slug_1',
        2 => 'empty',
        3 => 'argument_term_1',
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
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '4f3d4064-bf6d-4734-8125-94dbb93d91c0';
    $display->content['new-4f3d4064-bf6d-4734-8125-94dbb93d91c0'] = $pane;
    $display->panels['left_sidebar'][4] = 'new-4f3d4064-bf6d-4734-8125-94dbb93d91c0';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'grid-medium',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '9bb644a0-3601-4ce3-a16a-c32dd13c12da';
    $display->content['new-9bb644a0-3601-4ce3-a16a-c32dd13c12da'] = $pane;
    $display->panels['main_content'][0] = 'new-9bb644a0-3601-4ce3-a16a-c32dd13c12da';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['ding_events_library'] = $page;

  return $pages;

}
