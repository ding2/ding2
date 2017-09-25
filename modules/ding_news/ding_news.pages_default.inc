<?php
/**
 * @file
 * ding_news.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function ding_news_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__news-story-alternative-layout';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -30;
  $handler->conf = array(
    'title' => 'News story alternative layout',
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
        'identifier' => 'OG group from news node',
        'keyword' => 'group',
        'name' => 'og_group_from_node',
        'context' => 'argument_entity_id:node_1',
        'id' => 1,
      ),
      1 => array(
        'identifier' => 'Library node from OG group',
        'keyword' => 'library',
        'name' => 'og_node_from_group',
        'context' => 'relationship_og_group_from_node_1',
        'id' => 1,
      ),
      2 => array(
        'identifier' => 'All terms from node',
        'keyword' => 'terms',
        'name' => 'terms_from_node',
        'context' => 'argument_entity_id:node_1',
        'vid' => array(
          1 => '1',
          2 => '2',
        ),
        'concatenator' => ',',
        'id' => 1,
      ),
      3 => array(
        'identifier' => 'Category term',
        'keyword' => 'taxonomy_term',
        'name' => 'entity_from_field:field_ding_news_category-node-taxonomy_term',
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
              'ding_news' => 'ding_news',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'entity_field_value:node:ding_news:field_ding_news_show_as_list',
          'settings' => array(
            'field_ding_news_show_as_list' => array(
              'und' => array(
                0 => array(
                  'value' => 1,
                ),
              ),
            ),
            'field_ding_news_show_as_list_value' => array(
              0 => 1,
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
    'panels_breadcrumbs_state' => 1,
    'panels_breadcrumbs_titles' => 'News
%node:title',
    'panels_breadcrumbs_paths' => 'news
<none>',
    'name' => 'news-story-alternative-layout',
    'metatag_panels' => array(
      'enabled' => 1,
      'metatags' => array(
        'title' => array(
          'value' => '[node:title] | [current-page:pager][site:name]',
        ),
        'description' => array(
          'value' => '[node:field_ding_news_lead]',
        ),
        'image_src' => array(
          'value' => '[node:field_ding_news_title_image]',
        ),
      ),
    ),
  );
  $display = new panels_display();
  $display->layout = 'ding2_site_template';
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
      'branding' => NULL,
      'header' => NULL,
      'navigation' => NULL,
      'content' => NULL,
      'footer' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '6f0ec498-237a-4aab-a29c-376d9fac2cc6';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-8f21a367-0964-40c8-a9c6-231278b832ee';
    $pane->panel = 'content';
    $pane->type = 'block';
    $pane->subtype = 'similarterms-ding_content_tags';
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
    $pane->locks = '';
    $pane->uuid = '8f21a367-0964-40c8-a9c6-231278b832ee';
    $display->content['new-8f21a367-0964-40c8-a9c6-231278b832ee'] = $pane;
    $display->panels['content'][0] = 'new-8f21a367-0964-40c8-a9c6-231278b832ee';
    $pane = new stdClass();
    $pane->pid = 'new-98fddea0-c7eb-4b7c-82a3-be24fe3a73c2';
    $pane->panel = 'content';
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
      'build_mode' => 'alternative_layout_full',
      'context' => 'argument_entity_id:node_1',
      'override_title_heading' => 'h2',
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
    $pane->position = 1;
    $pane->locks = '';
    $pane->uuid = '98fddea0-c7eb-4b7c-82a3-be24fe3a73c2';
    $display->content['new-98fddea0-c7eb-4b7c-82a3-be24fe3a73c2'] = $pane;
    $display->panels['content'][1] = 'new-98fddea0-c7eb-4b7c-82a3-be24fe3a73c2';
    $pane = new stdClass();
    $pane->pid = 'new-a1c43371-47f9-4370-a57f-ccbdd958de1a';
    $pane->panel = 'content';
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'a1c43371-47f9-4370-a57f-ccbdd958de1a';
    $display->content['new-a1c43371-47f9-4370-a57f-ccbdd958de1a'] = $pane;
    $display->panels['content'][2] = 'new-a1c43371-47f9-4370-a57f-ccbdd958de1a';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-98fddea0-c7eb-4b7c-82a3-be24fe3a73c2';
  $handler->conf['display'] = $display;
  $export['node_view__news-story-alternative-layout'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view_panel_context';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -29;
  $handler->conf = array(
    'title' => 'News story',
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
        'identifier' => 'OG group from news node',
        'keyword' => 'group',
        'name' => 'og_group_from_node',
        'context' => 'argument_entity_id:node_1',
        'id' => 1,
      ),
      1 => array(
        'identifier' => 'Library node from OG group',
        'keyword' => 'library',
        'name' => 'og_node_from_group',
        'context' => 'relationship_og_group_from_node_1',
        'id' => 1,
      ),
      2 => array(
        'identifier' => 'All terms from node',
        'keyword' => 'terms',
        'name' => 'terms_from_node',
        'context' => 'argument_entity_id:node_1',
        'vid' => array(
          1 => '1',
          2 => '2',
        ),
        'concatenator' => ',',
        'id' => 1,
      ),
      3 => array(
        'identifier' => 'Category term',
        'keyword' => 'taxonomy_term',
        'name' => 'entity_from_field:field_ding_news_category-node-taxonomy_term',
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
              'ding_news' => 'ding_news',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
    'panels_breadcrumbs_state' => 1,
    'panels_breadcrumbs_titles' => 'News
%node:title',
    'panels_breadcrumbs_paths' => 'news
<none>',
    'metatag_panels' => array(
      'enabled' => 1,
      'metatags' => array(
        'title' => array(
          'value' => '[node:title] | [current-page:pager][site:name]',
        ),
        'description' => array(
          'value' => '[node:field_ding_news_lead]',
        ),
        'image_src' => array(
          'value' => '[node:field_ding_news_title_image]',
        ),
      ),
    ),
  );
  $display = new panels_display();
  $display->layout = 'ding2_site_template';
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
      'branding' => NULL,
      'header' => NULL,
      'navigation' => NULL,
      'content' => NULL,
      'footer' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '6f0ec498-237a-4aab-a29c-376d9fac2cc6';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-8f21a367-0964-40c8-a9c6-231278b832ee';
    $pane->panel = 'content';
    $pane->type = 'block';
    $pane->subtype = 'similarterms-ding_content_tags';
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
    $pane->locks = '';
    $pane->uuid = '8f21a367-0964-40c8-a9c6-231278b832ee';
    $display->content['new-8f21a367-0964-40c8-a9c6-231278b832ee'] = $pane;
    $display->panels['content'][0] = 'new-8f21a367-0964-40c8-a9c6-231278b832ee';
    $pane = new stdClass();
    $pane->pid = 'new-98fddea0-c7eb-4b7c-82a3-be24fe3a73c2';
    $pane->panel = 'content';
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
    $pane->position = 1;
    $pane->locks = '';
    $pane->uuid = '98fddea0-c7eb-4b7c-82a3-be24fe3a73c2';
    $display->content['new-98fddea0-c7eb-4b7c-82a3-be24fe3a73c2'] = $pane;
    $display->panels['content'][1] = 'new-98fddea0-c7eb-4b7c-82a3-be24fe3a73c2';
    $pane = new stdClass();
    $pane->pid = 'new-64165907-ccee-4974-998a-8b306b9fee5b';
    $pane->panel = 'content';
    $pane->type = 'campaign';
    $pane->subtype = 'campaign';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'ding_campaign_count' => 3,
      'ding_campaign_offset' => 0,
      'ding_campaign_style' => 'ding_campaign_full_width',
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
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '64165907-ccee-4974-998a-8b306b9fee5b';
    $display->content['new-64165907-ccee-4974-998a-8b306b9fee5b'] = $pane;
    $display->panels['content'][2] = 'new-64165907-ccee-4974-998a-8b306b9fee5b';
    $pane = new stdClass();
    $pane->pid = 'new-d718e319-abdc-4688-a6ba-107c5e8f6c1e';
    $pane->panel = 'content';
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
    $pane->uuid = 'd718e319-abdc-4688-a6ba-107c5e8f6c1e';
    $display->content['new-d718e319-abdc-4688-a6ba-107c5e8f6c1e'] = $pane;
    $display->panels['content'][3] = 'new-d718e319-abdc-4688-a6ba-107c5e8f6c1e';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-98fddea0-c7eb-4b7c-82a3-be24fe3a73c2';
  $handler->conf['display'] = $display;
  $export['node_view_panel_context'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'term_view_panel_context_2';
  $handler->task = 'term_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 1;
  $handler->conf = array(
    'title' => 'Ding news',
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
              'news_category' => 'news_category',
            ),
          ),
          'context' => 'argument_term_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
    'panels_breadcrumbs_state' => 1,
    'panels_breadcrumbs_titles' => 'News
%term:name',
    'panels_breadcrumbs_paths' => 'news
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
  $display->title = '';
  $display->uuid = 'e44759b7-363f-497d-8677-2af8a2e33b70';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-af0b4dab-20c3-42c8-b489-aebf3fda7a8c';
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
      'override_title_text' => 'News',
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
    $pane->uuid = 'af0b4dab-20c3-42c8-b489-aebf3fda7a8c';
    $display->content['new-af0b4dab-20c3-42c8-b489-aebf3fda7a8c'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-af0b4dab-20c3-42c8-b489-aebf3fda7a8c';
    $pane = new stdClass();
    $pane->pid = 'new-64a515e4-fb15-435d-bcf6-241785791333';
    $pane->panel = 'left_sidebar';
    $pane->type = 'taxonomy_menu';
    $pane->subtype = 'taxonomy_menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'slug' => 'nyheder',
      'default_link_text' => 'All categories',
      'context' => array(
        0 => 'argument_term_1',
        1 => 'empty',
      ),
      'override_title' => 0,
      'override_title_text' => '',
      'dropdown' => 0,
      'vocabulary' => 'news_category',
      'base' => '',
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '64a515e4-fb15-435d-bcf6-241785791333';
    $display->content['new-64a515e4-fb15-435d-bcf6-241785791333'] = $pane;
    $display->panels['left_sidebar'][1] = 'new-64a515e4-fb15-435d-bcf6-241785791333';
    $pane = new stdClass();
    $pane->pid = 'new-a92ba7cb-7cd3-4a24-90c0-7fc52c30bc11';
    $pane->panel = 'left_sidebar';
    $pane->type = 'library_list';
    $pane->subtype = 'library_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'type' => 'ding_news',
      'context' => array(
        0 => 'argument_term_1',
        1 => 'empty',
      ),
      'override_title' => 0,
      'override_title_text' => '',
      'slug' => 'nyheder',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'a92ba7cb-7cd3-4a24-90c0-7fc52c30bc11';
    $display->content['new-a92ba7cb-7cd3-4a24-90c0-7fc52c30bc11'] = $pane;
    $display->panels['left_sidebar'][2] = 'new-a92ba7cb-7cd3-4a24-90c0-7fc52c30bc11';
    $pane = new stdClass();
    $pane->pid = 'new-f761af87-a40a-4bcf-99c2-0320ab254d4e';
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
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = 'f761af87-a40a-4bcf-99c2-0320ab254d4e';
    $display->content['new-f761af87-a40a-4bcf-99c2-0320ab254d4e'] = $pane;
    $display->panels['left_sidebar'][3] = 'new-f761af87-a40a-4bcf-99c2-0320ab254d4e';
    $pane = new stdClass();
    $pane->pid = 'new-26d16112-d9b0-4d46-8192-b301259f9e3c';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_news-ding_news_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
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
    $pane->uuid = '26d16112-d9b0-4d46-8192-b301259f9e3c';
    $display->content['new-26d16112-d9b0-4d46-8192-b301259f9e3c'] = $pane;
    $display->panels['main_content'][0] = 'new-26d16112-d9b0-4d46-8192-b301259f9e3c';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-26d16112-d9b0-4d46-8192-b301259f9e3c';
  $handler->conf['display'] = $display;
  $export['term_view_panel_context_2'] = $handler;

  return $export;
}

/**
 * Implements hook_default_page_manager_pages().
 */
function ding_news_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'ding_news';
  $page->task = 'page';
  $page->admin_title = 'Ding news';
  $page->admin_description = '';
  $page->path = 'nyheder/!tid';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
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
  );
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Nyheder',
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
  $handler->name = 'page_ding_news_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'ding_news';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Ding news',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'panels_breadcrumbs_state' => 1,
    'panels_breadcrumbs_titles' => 'Home
News
%tid:name',
    'panels_breadcrumbs_paths' => '<front>
news
news/%tid:name',
    'metatag_panels' => array(
      'enabled' => 1,
      'metatags' => array(
        'title' => array(
          'value' => 'News | [current-page:pager][site:name]',
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
  $display->title = 'News';
  $display->uuid = 'e7aff876-739a-4f3b-8c46-de73e134a42f';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-bb26b1db-7e7e-4c3f-8956-183ed5e31146';
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
    $pane->uuid = 'bb26b1db-7e7e-4c3f-8956-183ed5e31146';
    $display->content['new-bb26b1db-7e7e-4c3f-8956-183ed5e31146'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-bb26b1db-7e7e-4c3f-8956-183ed5e31146';
    $pane = new stdClass();
    $pane->pid = 'new-b4813802-1a27-4792-b1e2-90500530a32b';
    $pane->panel = 'left_sidebar';
    $pane->type = 'taxonomy_menu';
    $pane->subtype = 'taxonomy_menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'slug' => 'nyheder',
      'default_link_text' => 'All categories',
      'context' => array(
        0 => 'argument_term_1',
        1 => 'empty',
      ),
      'override_title' => 0,
      'override_title_text' => 'News categories',
      'dropdown' => 0,
      'base' => '',
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
    $pane->uuid = 'b4813802-1a27-4792-b1e2-90500530a32b';
    $display->content['new-b4813802-1a27-4792-b1e2-90500530a32b'] = $pane;
    $display->panels['left_sidebar'][1] = 'new-b4813802-1a27-4792-b1e2-90500530a32b';
    $pane = new stdClass();
    $pane->pid = 'new-1b296b9b-ddc2-4c6a-8447-84b7e4380270';
    $pane->panel = 'left_sidebar';
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
      'logic' => 'and',
    );
    $pane->configuration = array(
      'type' => 'ding_news',
      'context' => array(
        0 => 'argument_term_1',
        1 => 'empty',
      ),
      'override_title' => 0,
      'override_title_text' => '',
      'slug' => 'nyheder',
      'hide_default' => 0,
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = '';
    $pane->uuid = '1b296b9b-ddc2-4c6a-8447-84b7e4380270';
    $display->content['new-1b296b9b-ddc2-4c6a-8447-84b7e4380270'] = $pane;
    $display->panels['left_sidebar'][2] = 'new-1b296b9b-ddc2-4c6a-8447-84b7e4380270';
    $pane = new stdClass();
    $pane->pid = 'new-ed3bd36b-3b75-4103-8826-db8e20c8b8d6';
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
        'lifetime' => '600',
        'granularity' => 'context',
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = '';
    $pane->uuid = 'ed3bd36b-3b75-4103-8826-db8e20c8b8d6';
    $display->content['new-ed3bd36b-3b75-4103-8826-db8e20c8b8d6'] = $pane;
    $display->panels['left_sidebar'][3] = 'new-ed3bd36b-3b75-4103-8826-db8e20c8b8d6';
    $pane = new stdClass();
    $pane->pid = 'new-253b275c-0dd3-419b-b9b2-dfa9d2d44789';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_news-ding_news_list';
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
      'css_class' => 'grid-medium',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '253b275c-0dd3-419b-b9b2-dfa9d2d44789';
    $display->content['new-253b275c-0dd3-419b-b9b2-dfa9d2d44789'] = $pane;
    $display->panels['main_content'][0] = 'new-253b275c-0dd3-419b-b9b2-dfa9d2d44789';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-bb26b1db-7e7e-4c3f-8956-183ed5e31146';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['ding_news'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'ding_news_library';
  $page->task = 'page';
  $page->admin_title = 'Library news page';
  $page->admin_description = '';
  $page->path = 'bibliotek/%slug/nyheder/!tid';
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
      'identifier' => 'Node: Ding library slug',
      'name' => 'slug',
      'settings' => array(),
      'keyword' => 'slug',
    ),
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
  $handler->name = 'page_ding_news_library_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'ding_news_library';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Library news',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(
      0 => array(
        'identifier' => 'OG group from library node',
        'keyword' => 'group',
        'name' => 'og_group_from_node',
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
News
%tid:name
',
    'panels_breadcrumbs_paths' => 'libraries
node/%node:nid
node/%node:nid/news
<none>',
    'metatag_panels' => array(
      'enabled' => 1,
      'metatags' => array(
        'title' => array(
          'value' => '%slug:title | News | [current-page:pager][site:name]',
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
  $display->uuid = 'cb65f5e8-be69-4a06-bdc7-d541b858b43a';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-4805a5cd-fc15-4209-ab7f-b02a1c4a5e42';
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
    $pane->uuid = '4805a5cd-fc15-4209-ab7f-b02a1c4a5e42';
    $display->content['new-4805a5cd-fc15-4209-ab7f-b02a1c4a5e42'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-4805a5cd-fc15-4209-ab7f-b02a1c4a5e42';
    $pane = new stdClass();
    $pane->pid = 'new-02346cd3-2799-49cb-8585-9e1530d2688f';
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
    $pane->uuid = '02346cd3-2799-49cb-8585-9e1530d2688f';
    $display->content['new-02346cd3-2799-49cb-8585-9e1530d2688f'] = $pane;
    $display->panels['left_sidebar'][1] = 'new-02346cd3-2799-49cb-8585-9e1530d2688f';
    $pane = new stdClass();
    $pane->pid = 'new-36b2e2c6-02b1-471b-b60f-d96815d9f580';
    $pane->panel = 'left_sidebar';
    $pane->type = 'taxonomy_menu';
    $pane->subtype = 'taxonomy_menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'slug' => 'nyheder',
      'default_link_text' => 'All categories',
      'context' => array(
        0 => 'argument_term_1',
        1 => 'argument_slug_1',
      ),
      'override_title' => 0,
      'override_title_text' => '',
      'dropdown' => 0,
      'base' => 'bibliotek',
      'vocabulary' => 'news_category',
      'override_title_heading' => 'h2',
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
    $pane->uuid = '36b2e2c6-02b1-471b-b60f-d96815d9f580';
    $display->content['new-36b2e2c6-02b1-471b-b60f-d96815d9f580'] = $pane;
    $display->panels['left_sidebar'][2] = 'new-36b2e2c6-02b1-471b-b60f-d96815d9f580';
    $pane = new stdClass();
    $pane->pid = 'new-f6b51cdf-2a4b-43bf-b075-b9acbc768fba';
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
        1 => 'argument_slug_1',
        2 => 'empty',
        3 => 'argument_term_1',
      ),
      'override_title' => 0,
      'override_title_text' => '',
      'ding_campaign_image_style' => 'medium',
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
    $pane->position = 3;
    $pane->locks = '';
    $pane->uuid = 'f6b51cdf-2a4b-43bf-b075-b9acbc768fba';
    $display->content['new-f6b51cdf-2a4b-43bf-b075-b9acbc768fba'] = $pane;
    $display->panels['left_sidebar'][3] = 'new-f6b51cdf-2a4b-43bf-b075-b9acbc768fba';
    $pane = new stdClass();
    $pane->pid = 'new-3cd2d6b7-343e-46a4-af19-26725235ccb0';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_news-ding_news_list_library';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_slug_1',
        1 => 'argument_term_1',
      ),
      'override_title' => 1,
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
    $pane->uuid = '3cd2d6b7-343e-46a4-af19-26725235ccb0';
    $display->content['new-3cd2d6b7-343e-46a4-af19-26725235ccb0'] = $pane;
    $display->panels['main_content'][0] = 'new-3cd2d6b7-343e-46a4-af19-26725235ccb0';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['ding_news_library'] = $page;

  return $pages;

}
