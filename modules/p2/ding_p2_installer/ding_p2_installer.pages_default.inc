<?php
/**
 * @file
 * ding_p2_installer.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 *
 * Defines variants used by p2.
 * Most of them are overridden copies of Ding core page variants.
 */
function ding_p2_installer_default_page_manager_handlers() {
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_ding_frontpage__panel_context_1';
  $handler->task = 'page';
  $handler->subtask = 'ding_frontpage';
  $handler->handler = 'panel_context';
  $handler->weight = -1;
  $handler->conf = array(
    'title' => 'Ding frontpage P2',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
  );
  $display = new panels_display();
  $display->layout = 'ding_layout_1';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'left' => NULL,
      'right' => NULL,
      'bottom' => NULL,
      'top_secondary' => NULL,
      'main_content' => NULL,
      'main_left_right' => NULL,
      'main_right_right' => NULL,
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
      'primary' => NULL,
      'secondary' => NULL,
      'tertiary' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '6795d6ae-3c57-4fb4-b339-3d6373acce88';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-a3e659f7-e285-4383-aefa-dd87b563ade6';
    $pane->panel = 'attachment_1_1';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_groups-panel_pane_1';
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
    $pane->uuid = 'a3e659f7-e285-4383-aefa-dd87b563ade6';
    $display->content['new-a3e659f7-e285-4383-aefa-dd87b563ade6'] = $pane;
    $display->panels['attachment_1_1'][0] = 'new-a3e659f7-e285-4383-aefa-dd87b563ade6';
    $pane = new stdClass();
    $pane->pid = 'new-74a49488-f11d-40b6-8211-52e84c8b296a';
    $pane->panel = 'primary';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_tabroll-ding_frontpage_tabroll';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'frontpage_promoter',
          'settings' => array(
            'promoter' => 'ding_tabroll',
          ),
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '74a49488-f11d-40b6-8211-52e84c8b296a';
    $display->content['new-74a49488-f11d-40b6-8211-52e84c8b296a'] = $pane;
    $display->panels['primary'][0] = 'new-74a49488-f11d-40b6-8211-52e84c8b296a';
    $pane = new stdClass();
    $pane->pid = 'new-18cfc092-1d0f-42e4-bde8-8a6e314c9bd0';
    $pane->panel = 'primary';
    $pane->type = 'carousel';
    $pane->subtype = 'carousel';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(),
    );
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '18cfc092-1d0f-42e4-bde8-8a6e314c9bd0';
    $display->content['new-18cfc092-1d0f-42e4-bde8-8a6e314c9bd0'] = $pane;
    $display->panels['primary'][1] = 'new-18cfc092-1d0f-42e4-bde8-8a6e314c9bd0';
    $pane = new stdClass();
    $pane->pid = 'new-5bf05877-cd2f-42d8-92a9-fbe2ef5163ba';
    $pane->panel = 'primary';
    $pane->type = 'interaction_pane';
    $pane->subtype = 'interaction_pane';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'count' => '5',
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
    $pane->uuid = '5bf05877-cd2f-42d8-92a9-fbe2ef5163ba';
    $display->content['new-5bf05877-cd2f-42d8-92a9-fbe2ef5163ba'] = $pane;
    $display->panels['primary'][2] = 'new-5bf05877-cd2f-42d8-92a9-fbe2ef5163ba';
    $pane = new stdClass();
    $pane->pid = 'new-4f1daf85-2201-4a37-8823-f4ee028e1b5a';
    $pane->panel = 'primary';
    $pane->type = 'serendipity_ting_object';
    $pane->subtype = 'serendipity_ting_object';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'compact',
      'sort_weight' => FALSE,
      'max' => '20',
      'min' => '10',
      'random' => 1,
      'selected_keys' => array(
        'ting_object' => 'ting_object',
        'frontpage' => 'frontpage',
      ),
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
      'method' => 'lazy',
      'settings' => array(
        'load_strategy' => 'pane-visible',
        'show_spinner' => 1,
        'load_text' => '',
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '4f1daf85-2201-4a37-8823-f4ee028e1b5a';
    $display->content['new-4f1daf85-2201-4a37-8823-f4ee028e1b5a'] = $pane;
    $display->panels['primary'][3] = 'new-4f1daf85-2201-4a37-8823-f4ee028e1b5a';
    $pane = new stdClass();
    $pane->pid = 'new-f07e8331-b359-407f-9361-860846c78da1';
    $pane->panel = 'primary';
    $pane->type = 'popular';
    $pane->subtype = 'popular';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(),
    );
    $pane->configuration = array(
      'month' => '',
      'libcode' => 0,
      'override_title' => 1,
      'override_title_text' => 'Månedens populæreste titler',
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
    $pane->uuid = 'f07e8331-b359-407f-9361-860846c78da1';
    $display->content['new-f07e8331-b359-407f-9361-860846c78da1'] = $pane;
    $display->panels['primary'][4] = 'new-f07e8331-b359-407f-9361-860846c78da1';
    $pane = new stdClass();
    $pane->pid = 'new-20a8af4e-90a0-42a4-be60-89cb72e44127';
    $pane->panel = 'secondary';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_news-ding_news_frontpage_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Library news',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '20a8af4e-90a0-42a4-be60-89cb72e44127';
    $display->content['new-20a8af4e-90a0-42a4-be60-89cb72e44127'] = $pane;
    $display->panels['secondary'][0] = 'new-20a8af4e-90a0-42a4-be60-89cb72e44127';
    $pane = new stdClass();
    $pane->pid = 'new-1235d134-3c15-4d11-86e4-a48f9c8737b3';
    $pane->panel = 'tertiary';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_event-ding_event_list_frontpage';
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
    $pane->uuid = '1235d134-3c15-4d11-86e4-a48f9c8737b3';
    $display->content['new-1235d134-3c15-4d11-86e4-a48f9c8737b3'] = $pane;
    $display->panels['tertiary'][0] = 'new-1235d134-3c15-4d11-86e4-a48f9c8737b3';
    $pane = new stdClass();
    $pane->pid = 'new-b14f0ccc-f81c-4267-b843-2fd333f260f8';
    $pane->panel = 'tertiary';
    $pane->type = 'block';
    $pane->subtype = 'finurlig_widget-fffWidget';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Finurlige fakta',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'b14f0ccc-f81c-4267-b843-2fd333f260f8';
    $display->content['new-b14f0ccc-f81c-4267-b843-2fd333f260f8'] = $pane;
    $display->panels['tertiary'][1] = 'new-b14f0ccc-f81c-4267-b843-2fd333f260f8';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;


  $handlers['page_ding_frontpage__panel_context_1'] = $handler;

  // Tags variant
  $handler = new stdClass();
  $handler->disabled = FALSE;
  $handler->api_version = 1;
  $handler->name = 'term_view_panel_context_4';
  $handler->task = 'term_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 2;
  $handler->conf = array(
    'title' => 'Tags P2',
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
  $display->layout = 'twocol_bricks';
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
      'top' => NULL,
      'left_above' => NULL,
      'right_above' => NULL,
      'middle' => NULL,
      'left_below' => NULL,
      'right_below' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%term:name';
  $display->uuid = '4b241667-11e0-4198-b244-e01ca4d6529d';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-2a68751d-d16f-4b46-8ee7-054a37ed5f0d';
    $pane->panel = 'left_above';
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
    $display->panels['left_above'][0] = 'new-2a68751d-d16f-4b46-8ee7-054a37ed5f0d';
    $pane = new stdClass();
    $pane->pid = 'new-4aca7e2f-ca95-4683-bcea-d8ba84654580';
    $pane->panel = 'left_above';
    $pane->type = 'entity_view';
    $pane->subtype = 'taxonomy_term';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'full',
      'context' => 'argument_term_1',
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '4aca7e2f-ca95-4683-bcea-d8ba84654580';
    $display->content['new-4aca7e2f-ca95-4683-bcea-d8ba84654580'] = $pane;
    $display->panels['left_above'][1] = 'new-4aca7e2f-ca95-4683-bcea-d8ba84654580';
    $pane = new stdClass();
    $pane->pid = 'new-441bdd0d-6385-4e6f-872c-1188529e3bbf';
    $pane->panel = 'middle';
    $pane->type = 'term_ting_objects';
    $pane->subtype = 'term_ting_objects';
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
    $pane->uuid = '441bdd0d-6385-4e6f-872c-1188529e3bbf';
    $display->content['new-441bdd0d-6385-4e6f-872c-1188529e3bbf'] = $pane;
    $display->panels['middle'][0] = 'new-441bdd0d-6385-4e6f-872c-1188529e3bbf';
    $pane = new stdClass();
    $pane->pid = 'new-d96d3026-f2f7-4aab-92a1-64f5f007d16d';
    $pane->panel = 'middle';
    $pane->type = 'serendipity_term';
    $pane->subtype = 'serendipity_term';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'teaser',
      'sort_weight' => FALSE,
      'max' => '10',
      'min' => '5',
      'random' => 1,
      'entity_type' => 'ting_object',
      'bundle' => 'ding_event',
      'context' => array(
        0 => 'argument_term_1',
      ),
      'override_title' => 1,
      'override_title_text' => 'Relaterede materialer',
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
    $pane->uuid = 'd96d3026-f2f7-4aab-92a1-64f5f007d16d';
    $display->content['new-d96d3026-f2f7-4aab-92a1-64f5f007d16d'] = $pane;
    $display->panels['middle'][1] = 'new-d96d3026-f2f7-4aab-92a1-64f5f007d16d';
    $pane = new stdClass();
    $pane->pid = 'new-e433f54f-8481-4005-b77f-02c5a4c341d5';
    $pane->panel = 'middle';
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'e433f54f-8481-4005-b77f-02c5a4c341d5';
    $display->content['new-e433f54f-8481-4005-b77f-02c5a4c341d5'] = $pane;
    $display->panels['middle'][2] = 'new-e433f54f-8481-4005-b77f-02c5a4c341d5';
    $pane = new stdClass();
    $pane->pid = 'new-7c11deac-47b5-49fc-9032-0513db2c4887';
    $pane->panel = 'right_above';
    $pane->type = 'entity_view';
    $pane->subtype = 'taxonomy_term';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'teaser',
      'context' => 'argument_term_1',
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
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '7c11deac-47b5-49fc-9032-0513db2c4887';
    $display->content['new-7c11deac-47b5-49fc-9032-0513db2c4887'] = $pane;
    $display->panels['right_above'][0] = 'new-7c11deac-47b5-49fc-9032-0513db2c4887';
    $pane = new stdClass();
    $pane->pid = 'new-663881b3-7002-4939-b474-94f1a296dbb5';
    $pane->panel = 'right_above';
    $pane->type = 'term_tree';
    $pane->subtype = 'term_tree';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '663881b3-7002-4939-b474-94f1a296dbb5';
    $display->content['new-663881b3-7002-4939-b474-94f1a296dbb5'] = $pane;
    $display->panels['right_above'][1] = 'new-663881b3-7002-4939-b474-94f1a296dbb5';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  
  $handlers['term_view_panel_context_4'] = $handler;
  
  // Ding site template
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'site_template_panel_context_1';
  $handler->task = 'site_template';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -1;
  $handler->conf = array(
    'title' => 'Ding site template P2',
    'no_blocks' => 1,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(),
      'logic' => 'and',
    ),
    'panels_breadcrumbs_state' => 0,
    'panels_breadcrumbs_titles' => '',
    'panels_breadcrumbs_paths' => '',
    'panels_breadcrumbs_home' => 1,
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
  );
  $display = new panels_display();
  $display->layout = 'ding2_site_template';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'branding_top' => NULL,
      'header' => NULL,
      'content' => NULL,
      'footer' => NULL,
      'branding_bottom' => NULL,
      'branding' => NULL,
      'bottom' => NULL,
      'navigation' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '92a45db0-147b-411f-8833-8377a52f5198';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-e999c9e4-00d5-4222-8690-5c8e6f3d5339';
    $pane->panel = 'bottom';
    $pane->type = 'block';
    $pane->subtype = 'block-1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '<none>',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'e999c9e4-00d5-4222-8690-5c8e6f3d5339';
    $display->content['new-e999c9e4-00d5-4222-8690-5c8e6f3d5339'] = $pane;
    $display->panels['bottom'][0] = 'new-e999c9e4-00d5-4222-8690-5c8e6f3d5339';
    $pane = new stdClass();
    $pane->pid = 'new-3c879038-1011-4427-8465-f638e18375e1';
    $pane->panel = 'branding';
    $pane->type = 'pane_header';
    $pane->subtype = 'pane_header';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'naked',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '3c879038-1011-4427-8465-f638e18375e1';
    $display->content['new-3c879038-1011-4427-8465-f638e18375e1'] = $pane;
    $display->panels['branding'][0] = 'new-3c879038-1011-4427-8465-f638e18375e1';
    $pane = new stdClass();
    $pane->pid = 'new-10bf5aa9-f209-42b0-bba4-cc6ba8aee079';
    $pane->panel = 'branding';
    $pane->type = 'block';
    $pane->subtype = 'menu-menu-tabs-menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'naked',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '10bf5aa9-f209-42b0-bba4-cc6ba8aee079';
    $display->content['new-10bf5aa9-f209-42b0-bba4-cc6ba8aee079'] = $pane;
    $display->panels['branding'][1] = 'new-10bf5aa9-f209-42b0-bba4-cc6ba8aee079';
    $pane = new stdClass();
    $pane->pid = 'new-406c552b-fa91-45cd-b758-bc32b9088384';
    $pane->panel = 'branding';
    $pane->type = 'notifications_top_menu';
    $pane->subtype = 'notifications_top_menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'top_menu_items' => array(
        'loans' => 'loans',
        'ready_to_pickup' => 'ready_to_pickup',
        'reservations' => 'reservations',
        'dept' => 'dept',
      ),
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array(
      'method' => 'lazy',
      'settings' => array(
        'load_strategy' => 'page-loaded',
        'show_spinner' => 0,
        'load_text' => '',
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '406c552b-fa91-45cd-b758-bc32b9088384';
    $display->content['new-406c552b-fa91-45cd-b758-bc32b9088384'] = $pane;
    $display->panels['branding'][2] = 'new-406c552b-fa91-45cd-b758-bc32b9088384';
    $pane = new stdClass();
    $pane->pid = 'new-1769a64d-2cbe-490d-87aa-a2c3ee082997';
    $pane->panel = 'content';
    $pane->type = 'page_messages';
    $pane->subtype = 'page_messages';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'default',
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'system-messages',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = '1769a64d-2cbe-490d-87aa-a2c3ee082997';
    $display->content['new-1769a64d-2cbe-490d-87aa-a2c3ee082997'] = $pane;
    $display->panels['content'][0] = 'new-1769a64d-2cbe-490d-87aa-a2c3ee082997';
    $pane = new stdClass();
    $pane->pid = 'new-76338aa5-3ee9-4256-9414-eab9979db07b';
    $pane->panel = 'content';
    $pane->type = 'page_tabs';
    $pane->subtype = 'page_tabs';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        1 => array(
          'name' => 'external_user',
          'settings' => NULL,
          'context' => array(
            0 => 'logged-in-user',
          ),
          'not' => TRUE,
        ),
        2 => array(
          'name' => 'path_visibility',
          'settings' => array(
            'visibility_setting' => '1',
            'paths' => 'user/*',
          ),
          'context' => 'empty',
          'not' => TRUE,
        ),
      ),
      'logic' => 'or',
    );
    $pane->configuration = array(
      'type' => 'both',
      'id' => 'tabs',
      'override_title' => 1,
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
    $pane->uuid = '76338aa5-3ee9-4256-9414-eab9979db07b';
    $display->content['new-76338aa5-3ee9-4256-9414-eab9979db07b'] = $pane;
    $display->panels['content'][1] = 'new-76338aa5-3ee9-4256-9414-eab9979db07b';
    $pane = new stdClass();
    $pane->pid = 'new-4637ed6a-8c15-46bb-ae3b-4de4089e860d';
    $pane->panel = 'content';
    $pane->type = 'page_content';
    $pane->subtype = 'page_content';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_page_content_1',
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
    $pane->locks = '';
    $pane->uuid = '4637ed6a-8c15-46bb-ae3b-4de4089e860d';
    $display->content['new-4637ed6a-8c15-46bb-ae3b-4de4089e860d'] = $pane;
    $display->panels['content'][2] = 'new-4637ed6a-8c15-46bb-ae3b-4de4089e860d';
    $pane = new stdClass();
    $pane->pid = 'new-fd6dbb4f-c7b5-4881-96d2-769a6c16bfc2';
    $pane->panel = 'footer';
    $pane->type = 'block';
    $pane->subtype = 'menu-menu-footer-menu-1';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'attachment-first',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = 'fd6dbb4f-c7b5-4881-96d2-769a6c16bfc2';
    $display->content['new-fd6dbb4f-c7b5-4881-96d2-769a6c16bfc2'] = $pane;
    $display->panels['footer'][0] = 'new-fd6dbb4f-c7b5-4881-96d2-769a6c16bfc2';
    $pane = new stdClass();
    $pane->pid = 'new-3a72e819-3274-4d12-8fe3-414c0cbc3151';
    $pane->panel = 'footer';
    $pane->type = 'block';
    $pane->subtype = 'menu-menu-footer-menu-2';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'attachment-second',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = '';
    $pane->uuid = '3a72e819-3274-4d12-8fe3-414c0cbc3151';
    $display->content['new-3a72e819-3274-4d12-8fe3-414c0cbc3151'] = $pane;
    $display->panels['footer'][1] = 'new-3a72e819-3274-4d12-8fe3-414c0cbc3151';
    $pane = new stdClass();
    $pane->pid = 'new-d9877e3c-cae9-4067-99af-305cb0e70bf9';
    $pane->panel = 'footer';
    $pane->type = 'block';
    $pane->subtype = 'menu-menu-footer-menu-3';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'attachment-third',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = '';
    $pane->uuid = 'd9877e3c-cae9-4067-99af-305cb0e70bf9';
    $display->content['new-d9877e3c-cae9-4067-99af-305cb0e70bf9'] = $pane;
    $display->panels['footer'][2] = 'new-d9877e3c-cae9-4067-99af-305cb0e70bf9';
    $pane = new stdClass();
    $pane->pid = 'new-d59734fe-4c31-4b3c-af53-5c2bad02f9cf';
    $pane->panel = 'footer';
    $pane->type = 'block';
    $pane->subtype = 'menu-menu-footer-menu-4';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'attachment-fourth',
    );
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = '';
    $pane->uuid = 'd59734fe-4c31-4b3c-af53-5c2bad02f9cf';
    $display->content['new-d59734fe-4c31-4b3c-af53-5c2bad02f9cf'] = $pane;
    $display->panels['footer'][3] = 'new-d59734fe-4c31-4b3c-af53-5c2bad02f9cf';
    $pane = new stdClass();
    $pane->pid = 'new-f06a4c37-1ed2-4a64-8502-7b8d4d0619b0';
    $pane->panel = 'header';
    $pane->type = 'block';
    $pane->subtype = 'search-form';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'default',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'f06a4c37-1ed2-4a64-8502-7b8d4d0619b0';
    $display->content['new-f06a4c37-1ed2-4a64-8502-7b8d4d0619b0'] = $pane;
    $display->panels['header'][0] = 'new-f06a4c37-1ed2-4a64-8502-7b8d4d0619b0';
    $pane = new stdClass();
    $pane->pid = 'new-51d74d8b-0aeb-4c73-8c20-b5d4fdd40a39';
    $pane->panel = 'header';
    $pane->type = 'block';
    $pane->subtype = 'user-login';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'default',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '51d74d8b-0aeb-4c73-8c20-b5d4fdd40a39';
    $display->content['new-51d74d8b-0aeb-4c73-8c20-b5d4fdd40a39'] = $pane;
    $display->panels['header'][1] = 'new-51d74d8b-0aeb-4c73-8c20-b5d4fdd40a39';
    $pane = new stdClass();
    $pane->pid = 'new-d9c1432b-77cc-432c-987a-eb64569a0b88';
    $pane->panel = 'header';
    $pane->type = 'user_menu';
    $pane->subtype = 'user_menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'path' => 'user/[user:uid]',
      'context' => 'logged-in-user',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'js-mobile-user-menu',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'd9c1432b-77cc-432c-987a-eb64569a0b88';
    $display->content['new-d9c1432b-77cc-432c-987a-eb64569a0b88'] = $pane;
    $display->panels['header'][2] = 'new-d9c1432b-77cc-432c-987a-eb64569a0b88';
    $pane = new stdClass();
    $pane->pid = 'new-889a855f-046c-4c3c-ba14-3e19231a6d4a';
    $pane->panel = 'header';
    $pane->type = 'block';
    $pane->subtype = 'ding_gatewayf-login';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
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
    $pane->uuid = '889a855f-046c-4c3c-ba14-3e19231a6d4a';
    $display->content['new-889a855f-046c-4c3c-ba14-3e19231a6d4a'] = $pane;
    $display->panels['header'][3] = 'new-889a855f-046c-4c3c-ba14-3e19231a6d4a';
    $pane = new stdClass();
    $pane->pid = 'new-cbaa0816-bd36-4c61-a038-5b49d0d434bd';
    $pane->panel = 'header';
    $pane->type = 'block';
    $pane->subtype = 'ding_gatewayf_registration-registration';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
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
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = 'cbaa0816-bd36-4c61-a038-5b49d0d434bd';
    $display->content['new-cbaa0816-bd36-4c61-a038-5b49d0d434bd'] = $pane;
    $display->panels['header'][4] = 'new-cbaa0816-bd36-4c61-a038-5b49d0d434bd';
    $pane = new stdClass();
    $pane->pid = 'new-94a239e5-00e0-4807-917f-df52c53405e7';
    $pane->panel = 'navigation';
    $pane->type = 'block';
    $pane->subtype = 'menu_block-1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'default',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '94a239e5-00e0-4807-917f-df52c53405e7';
    $display->content['new-94a239e5-00e0-4807-917f-df52c53405e7'] = $pane;
    $display->panels['navigation'][0] = 'new-94a239e5-00e0-4807-917f-df52c53405e7';
    $pane = new stdClass();
    $pane->pid = 'new-3202a330-fa71-44f2-be0a-265ed734b321';
    $pane->panel = 'navigation';
    $pane->type = 'block';
    $pane->subtype = 'menu_block-2';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'default',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '3202a330-fa71-44f2-be0a-265ed734b321';
    $display->content['new-3202a330-fa71-44f2-be0a-265ed734b321'] = $pane;
    $display->panels['navigation'][1] = 'new-3202a330-fa71-44f2-be0a-265ed734b321';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;

  $handlers['site_template_panel_context_1'] = $handler;
  
  // Provider profile
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'user_view_panel_context_5';
  $handler->task = 'user_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -30;
  $handler->conf = array(
    'title' => 'Provider profile P2',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(
      0 => array(
        'identifier' => 'Indlogget bruger',
        'keyword' => 'logged_in_user',
        'name' => 'user',
        'type' => 'current',
        'uid' => '',
        'id' => 1,
      ),
    ),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'external_user',
          'settings' => NULL,
          'context' => array(
            0 => 'logged-in-user',
          ),
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'compare_users',
          'settings' => array(
            'equality' => '1',
          ),
          'context' => array(
            0 => 'argument_entity_id:user_1',
            1 => 'logged-in-user',
          ),
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
      'middle' => NULL,
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
  $display->title = 'Account';
  $display->uuid = 'b4301b96-c745-4fea-8ae9-41cc346cb2cf';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-c73e6fbd-2403-4298-8cdb-00ed617c8e5d';
    $pane->panel = 'main_content';
    $pane->type = 'user_menu';
    $pane->subtype = 'user_menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_entity_id:user_1',
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
    $pane->uuid = 'c73e6fbd-2403-4298-8cdb-00ed617c8e5d';
    $display->content['new-c73e6fbd-2403-4298-8cdb-00ed617c8e5d'] = $pane;
    $display->panels['main_content'][0] = 'new-c73e6fbd-2403-4298-8cdb-00ed617c8e5d';
    $pane = new stdClass();
    $pane->pid = 'new-d8e66878-81ac-4da6-9c30-eb876b25af49';
    $pane->panel = 'main_content';
    $pane->type = 'block';
    $pane->subtype = 'ding_user_frontend-ding-user-loan-number';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => 'sdfsdf',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'user-loan-status-wrapper',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'd8e66878-81ac-4da6-9c30-eb876b25af49';
    $display->content['new-d8e66878-81ac-4da6-9c30-eb876b25af49'] = $pane;
    $display->panels['main_content'][1] = 'new-d8e66878-81ac-4da6-9c30-eb876b25af49';
    $pane = new stdClass();
    $pane->pid = 'new-96284cb3-0776-42ec-808d-fbd0707cd346';
    $pane->panel = 'main_content';
    $pane->type = 'profile2';
    $pane->subtype = 'profile2';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '96284cb3-0776-42ec-808d-fbd0707cd346';
    $display->content['new-96284cb3-0776-42ec-808d-fbd0707cd346'] = $pane;
    $display->panels['main_content'][2] = 'new-96284cb3-0776-42ec-808d-fbd0707cd346';
    $pane = new stdClass();
    $pane->pid = 'new-19996eea-aa45-473a-b367-59aa7d1f1ed1';
    $pane->panel = 'main_content';
    $pane->type = 'lists';
    $pane->subtype = 'lists';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '19996eea-aa45-473a-b367-59aa7d1f1ed1';
    $display->content['new-19996eea-aa45-473a-b367-59aa7d1f1ed1'] = $pane;
    $display->panels['main_content'][3] = 'new-19996eea-aa45-473a-b367-59aa7d1f1ed1';
    $pane = new stdClass();
    $pane->pid = 'new-8998a4b6-cfa0-4314-b510-4e8ed81cdd26';
    $pane->panel = 'main_content';
    $pane->type = 'add_user';
    $pane->subtype = 'add_user';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '8998a4b6-cfa0-4314-b510-4e8ed81cdd26';
    $display->content['new-8998a4b6-cfa0-4314-b510-4e8ed81cdd26'] = $pane;
    $display->panels['main_content'][4] = 'new-8998a4b6-cfa0-4314-b510-4e8ed81cdd26';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  
  $handlers['user_view_panel_context_5'] = $handler;
  
  // User profile
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'user_view_panel_context_4';
  $handler->task = 'user_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -29;
  $handler->conf = array(
    'title' => 'User profile P2',
    'no_blocks' => 0,
    'pipeline' => 'standard',
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
      'left' => NULL,
      'right' => NULL,
      'middle' => NULL,
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
  $display->title = 'Account';
  $display->uuid = '2bee1e6c-8cb9-489a-9b3e-9e80b6417074';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-cf25769d-7de8-4ef1-8d55-ae6c8a338ee3';
    $pane->panel = 'left_sidebar';
    $pane->type = 'block';
    $pane->subtype = 'system-user-menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
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
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'cf25769d-7de8-4ef1-8d55-ae6c8a338ee3';
    $display->content['new-cf25769d-7de8-4ef1-8d55-ae6c8a338ee3'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-cf25769d-7de8-4ef1-8d55-ae6c8a338ee3';
    $pane = new stdClass();
    $pane->pid = 'new-e5289475-70d1-4e3e-b26a-ffa09036a687';
    $pane->panel = 'main_content';
    $pane->type = 'lists';
    $pane->subtype = 'lists';
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
    $pane->uuid = 'e5289475-70d1-4e3e-b26a-ffa09036a687';
    $display->content['new-e5289475-70d1-4e3e-b26a-ffa09036a687'] = $pane;
    $display->panels['main_content'][0] = 'new-e5289475-70d1-4e3e-b26a-ffa09036a687';
    $pane = new stdClass();
    $pane->pid = 'new-dc4b2f5e-f42e-48bd-9f01-f81841042dbf';
    $pane->panel = 'main_content';
    $pane->type = 'user_profile';
    $pane->subtype = 'user_profile';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_entity_id:user_1',
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
    $pane->locks = '';
    $pane->uuid = 'dc4b2f5e-f42e-48bd-9f01-f81841042dbf';
    $display->content['new-dc4b2f5e-f42e-48bd-9f01-f81841042dbf'] = $pane;
    $display->panels['main_content'][1] = 'new-dc4b2f5e-f42e-48bd-9f01-f81841042dbf';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;

  $handlers['user_view_panel_context_4'] = $handler;
  
  // Search page:
  $handler = new stdClass();
  $handler->disabled = FALSE;
  $handler->api_version = 1;
  $handler->name = 'search_ting_search_panel_context_1';
  $handler->task = 'search';
  $handler->subtask = 'ting_search';
  $handler->handler = 'panel_context';
  $handler->weight = -1;
  $handler->conf = array(
    'title' => 'Ting Search P2',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'panels_breadcrumbs_state' => 1,
    'panels_breadcrumbs_titles' => 'Search
  Well
  %keywords:html_safe',
    'panels_breadcrumbs_paths' => 'search
  search/ting
  <none>
  ',
  );
  $display = new panels_display();
  $display->layout = '25_50_25';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
      'left' => NULL,
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
  $display->uuid = 'caa15777-4cfc-4926-8c39-6af276f23582';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-5929c0c7-25f7-4d61-8829-81a740e6f77e';
    $pane->panel = 'left_sidebar';
    $pane->type = 'search_backends';
    $pane->subtype = 'search_backends';
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
    $pane->uuid = '5929c0c7-25f7-4d61-8829-81a740e6f77e';
    $display->content['new-5929c0c7-25f7-4d61-8829-81a740e6f77e'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-5929c0c7-25f7-4d61-8829-81a740e6f77e';
    $pane = new stdClass();
    $pane->pid = 'new-f5097d22-b99c-49be-a0df-6b45a7d0d83c';
    $pane->panel = 'left_sidebar';
    $pane->type = 'ding_facetbrowser';
    $pane->subtype = 'ding_facetbrowser';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Filtrér din søgning',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = '';
    $pane->uuid = 'f5097d22-b99c-49be-a0df-6b45a7d0d83c';
    $display->content['new-f5097d22-b99c-49be-a0df-6b45a7d0d83c'] = $pane;
    $display->panels['left_sidebar'][1] = 'new-f5097d22-b99c-49be-a0df-6b45a7d0d83c';
    $pane = new stdClass();
    $pane->pid = 'new-07d2c562-f846-4241-b93f-7c1d723ff29d';
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
        2 => 'argument_string_1',
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
    $pane->locks = '';
    $pane->uuid = '07d2c562-f846-4241-b93f-7c1d723ff29d';
    $display->content['new-07d2c562-f846-4241-b93f-7c1d723ff29d'] = $pane;
    $display->panels['left_sidebar'][2] = 'new-07d2c562-f846-4241-b93f-7c1d723ff29d';
    $pane = new stdClass();
    $pane->pid = 'new-d6bca0c2-099c-4659-8fcd-69da98dbc7c9';
    $pane->panel = 'main_content';
    $pane->type = 'search_backends';
    $pane->subtype = 'search_backends';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'js-mobile-facets',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'd6bca0c2-099c-4659-8fcd-69da98dbc7c9';
    $display->content['new-d6bca0c2-099c-4659-8fcd-69da98dbc7c9'] = $pane;
    $display->panels['main_content'][0] = 'new-d6bca0c2-099c-4659-8fcd-69da98dbc7c9';
    $pane = new stdClass();
    $pane->pid = 'new-41aa51eb-47c2-41e5-b0e5-2606d863b66d';
    $pane->panel = 'main_content';
    $pane->type = 'ding_facetbrowser';
    $pane->subtype = 'ding_facetbrowser';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Filtrér din søgning',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'js-mobile-facets',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '41aa51eb-47c2-41e5-b0e5-2606d863b66d';
    $display->content['new-41aa51eb-47c2-41e5-b0e5-2606d863b66d'] = $pane;
    $display->panels['main_content'][1] = 'new-41aa51eb-47c2-41e5-b0e5-2606d863b66d';
    $pane = new stdClass();
    $pane->pid = 'new-f3a42372-e2fb-45e6-a62b-79c707f0a35d';
    $pane->panel = 'main_content';
    $pane->type = 'search_result_count';
    $pane->subtype = 'search_result_count';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_string_1',
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
    $pane->uuid = 'f3a42372-e2fb-45e6-a62b-79c707f0a35d';
    $display->content['new-f3a42372-e2fb-45e6-a62b-79c707f0a35d'] = $pane;
    $display->panels['main_content'][2] = 'new-f3a42372-e2fb-45e6-a62b-79c707f0a35d';
    $pane = new stdClass();
    $pane->pid = 'new-4fd48a77-4b9a-437f-8504-9c52ae3170e2';
    $pane->panel = 'main_content';
    $pane->type = 'search_query';
    $pane->subtype = 'search_query';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '4fd48a77-4b9a-437f-8504-9c52ae3170e2';
    $display->content['new-4fd48a77-4b9a-437f-8504-9c52ae3170e2'] = $pane;
    $display->panels['main_content'][3] = 'new-4fd48a77-4b9a-437f-8504-9c52ae3170e2';
    $pane = new stdClass();
    $pane->pid = 'new-dd50ebf9-a0f1-499b-b389-49f178f5e242';
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
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = '';
    $pane->uuid = 'dd50ebf9-a0f1-499b-b389-49f178f5e242';
    $display->content['new-dd50ebf9-a0f1-499b-b389-49f178f5e242'] = $pane;
    $display->panels['main_content'][4] = 'new-dd50ebf9-a0f1-499b-b389-49f178f5e242';
    $pane = new stdClass();
    $pane->pid = 'new-47206bf0-1031-456c-9aab-96b659e54d89';
    $pane->panel = 'main_content';
    $pane->type = 'search_per_page';
    $pane->subtype = 'search_per_page';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'select_type' => 'dropdown',
      'context' => 'argument_string_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 5;
    $pane->locks = array();
    $pane->uuid = '47206bf0-1031-456c-9aab-96b659e54d89';
    $display->content['new-47206bf0-1031-456c-9aab-96b659e54d89'] = $pane;
    $display->panels['main_content'][5] = 'new-47206bf0-1031-456c-9aab-96b659e54d89';
    $pane = new stdClass();
    $pane->pid = 'new-7c02f708-c47f-4eb5-8958-d6279de6ade4';
    $pane->panel = 'main_content';
    $pane->type = 'search_result';
    $pane->subtype = 'search_result';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'type' => 'ting_search',
      'log' => 0,
      'override_empty' => 0,
      'empty_title' => '',
      'empty' => '',
      'empty_format' => 'plain_text',
      'override_no_key' => 0,
      'no_key_title' => '',
      'no_key' => '',
      'no_key_format' => 'plain_text',
      'context' => 'argument_string_1',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 6;
    $pane->locks = '';
    $pane->uuid = '7c02f708-c47f-4eb5-8958-d6279de6ade4';
    $display->content['new-7c02f708-c47f-4eb5-8958-d6279de6ade4'] = $pane;
    $display->panels['main_content'][6] = 'new-7c02f708-c47f-4eb5-8958-d6279de6ade4';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  
  $handlers['search_ting_search_panel_context_1'] = $handler;
  
  // Ting Object
  $handler = new stdClass();
  $handler->disabled = FALSE;
  $handler->api_version = 1;
  $handler->name = 'ting_object_panel_context_1';
  $handler->task = 'ting_object';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -1;
  $handler->conf = array(
    'title' => 'Ting object P2',
    'no_blocks' => 0,
    'pipeline' => 'standard',
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
  $display->uuid = '7da7c33f-8425-44e8-a02d-0f497e4945e0';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-df83b6f7-4452-4d90-8566-5efb41b2cfbf';
    $pane->panel = 'left_sidebar';
    $pane->type = 'block';
    $pane->subtype = 'ting-ting_collection_types';
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
    $pane->uuid = 'df83b6f7-4452-4d90-8566-5efb41b2cfbf';
    $display->content['new-df83b6f7-4452-4d90-8566-5efb41b2cfbf'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-df83b6f7-4452-4d90-8566-5efb41b2cfbf';
    $pane = new stdClass();
    $pane->pid = 'new-1ec262e6-838d-429a-a83c-34fcb532f547';
    $pane->panel = 'left_sidebar';
    $pane->type = 'block';
    $pane->subtype = 'ting-ting_object_types';
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
    $pane->locks = '';
    $pane->uuid = '1ec262e6-838d-429a-a83c-34fcb532f547';
    $display->content['new-1ec262e6-838d-429a-a83c-34fcb532f547'] = $pane;
    $display->panels['left_sidebar'][1] = 'new-1ec262e6-838d-429a-a83c-34fcb532f547';
    $pane = new stdClass();
    $pane->pid = 'new-8fe5bb7f-41a6-4f5a-b6d1-eed5cc759f92';
    $pane->panel = 'left_sidebar';
    $pane->type = 'block';
    $pane->subtype = 'ting-ting_relation_anchors';
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
    $pane->position = 2;
    $pane->locks = '';
    $pane->uuid = '8fe5bb7f-41a6-4f5a-b6d1-eed5cc759f92';
    $display->content['new-8fe5bb7f-41a6-4f5a-b6d1-eed5cc759f92'] = $pane;
    $display->panels['left_sidebar'][2] = 'new-8fe5bb7f-41a6-4f5a-b6d1-eed5cc759f92';
    $pane = new stdClass();
    $pane->pid = 'new-2c6af9c6-63ae-4100-9b56-e3b1bee1ce9a';
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
    $pane->locks = '';
    $pane->uuid = '2c6af9c6-63ae-4100-9b56-e3b1bee1ce9a';
    $display->content['new-2c6af9c6-63ae-4100-9b56-e3b1bee1ce9a'] = $pane;
    $display->panels['left_sidebar'][3] = 'new-2c6af9c6-63ae-4100-9b56-e3b1bee1ce9a';
    $pane = new stdClass();
    $pane->pid = 'new-eda37090-d344-4baa-8c21-78573268da3d';
    $pane->panel = 'main_content';
    $pane->type = 'ting_object';
    $pane->subtype = 'ting_object';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_ting_object_id_17',
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
    $pane->uuid = 'eda37090-d344-4baa-8c21-78573268da3d';
    $display->content['new-eda37090-d344-4baa-8c21-78573268da3d'] = $pane;
    $display->panels['main_content'][0] = 'new-eda37090-d344-4baa-8c21-78573268da3d';
    $pane = new stdClass();
    $pane->pid = 'new-89ddd448-37a1-477a-bb5b-23b75fa07b5b';
    $pane->panel = 'main_content';
    $pane->type = 'serendipity_ting_object';
    $pane->subtype = 'serendipity_ting_object';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'compact',
      'sort_weight' => FALSE,
      'max' => '8',
      'min' => '4',
      'random' => FALSE,
      'selected_keys' => array(
        'ting_object_id' => 'ting_object_id',
      ),
      'context' => array(
        0 => 'empty',
        1 => 'empty',
        2 => 'empty',
        3 => 'argument_ting_object_id_17',
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '89ddd448-37a1-477a-bb5b-23b75fa07b5b';
    $display->content['new-89ddd448-37a1-477a-bb5b-23b75fa07b5b'] = $pane;
    $display->panels['main_content'][1] = 'new-89ddd448-37a1-477a-bb5b-23b75fa07b5b';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  
  $handlers['ting_object_panel_context_1'] = $handler;
  
  return $handlers;
}