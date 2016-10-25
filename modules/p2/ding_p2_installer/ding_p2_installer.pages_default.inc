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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '19996eea-aa45-473a-b367-59aa7d1f1ed1';
    $display->content['new-19996eea-aa45-473a-b367-59aa7d1f1ed1'] = $pane;
    $display->panels['main_content'][1] = 'new-19996eea-aa45-473a-b367-59aa7d1f1ed1';
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '8998a4b6-cfa0-4314-b510-4e8ed81cdd26';
    $display->content['new-8998a4b6-cfa0-4314-b510-4e8ed81cdd26'] = $pane;
    $display->panels['main_content'][2] = 'new-8998a4b6-cfa0-4314-b510-4e8ed81cdd26';
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
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = 'dc4b2f5e-f42e-48bd-9f01-f81841042dbf';
    $display->content['new-dc4b2f5e-f42e-48bd-9f01-f81841042dbf'] = $pane;
    $display->panels['main_content'][0] = 'new-dc4b2f5e-f42e-48bd-9f01-f81841042dbf';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;


  $handlers['user_view_panel_context_4'] = $handler;

  // Search page:
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
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
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'role',
          'settings' => array(
            'rids' => array(
              0 => 8,
            ),
          ),
          'context' => 'logged-in-user',
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
