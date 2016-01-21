<?php
/**
 * @file
 * ting_search_context_feature.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function ting_search_context_feature_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'search_ting_search_panel_context_with_related_content';
  $handler->task = 'search';
  $handler->subtask = 'ting_search';
  $handler->handler = 'panel_context';
  $handler->weight = -1;
  $handler->conf = array(
    'title' => 'ting search with ting search context',
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
  $pane->pid = 'new-c300791e-5aa9-4dec-a802-d0ba6810eda4';
  $pane->panel = 'left_sidebar';
  $pane->type = 'search_context';
  $pane->subtype = 'search_context';
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
    'css_class' => 'js-below-facets',
  );
  $pane->extras = array();
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = 'c300791e-5aa9-4dec-a802-d0ba6810eda4';
  $display->content['new-c300791e-5aa9-4dec-a802-d0ba6810eda4'] = $pane;
  $display->panels['left_sidebar'][2] = 'new-c300791e-5aa9-4dec-a802-d0ba6810eda4';
  $pane = new stdClass();
  $pane->pid = 'new-09c27add-b62d-4dc6-978e-97c18900be43';
  $pane->panel = 'main_content';
  $pane->type = 'search_context';
  $pane->subtype = 'search_context';
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
    'css_class' => 'js-above-search-result',
  );
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '09c27add-b62d-4dc6-978e-97c18900be43';
  $display->content['new-09c27add-b62d-4dc6-978e-97c18900be43'] = $pane;
  $display->panels['main_content'][0] = 'new-09c27add-b62d-4dc6-978e-97c18900be43';
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = 'd6bca0c2-099c-4659-8fcd-69da98dbc7c9';
  $display->content['new-d6bca0c2-099c-4659-8fcd-69da98dbc7c9'] = $pane;
  $display->panels['main_content'][1] = 'new-d6bca0c2-099c-4659-8fcd-69da98dbc7c9';
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
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '41aa51eb-47c2-41e5-b0e5-2606d863b66d';
  $display->content['new-41aa51eb-47c2-41e5-b0e5-2606d863b66d'] = $pane;
  $display->panels['main_content'][2] = 'new-41aa51eb-47c2-41e5-b0e5-2606d863b66d';
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
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = 'f3a42372-e2fb-45e6-a62b-79c707f0a35d';
  $display->content['new-f3a42372-e2fb-45e6-a62b-79c707f0a35d'] = $pane;
  $display->panels['main_content'][3] = 'new-f3a42372-e2fb-45e6-a62b-79c707f0a35d';
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
  $pane = new stdClass();
  $pane->pid = 'new-05d87521-c6f0-4a56-aed9-e232f92f3194';
  $pane->panel = 'main_content';
  $pane->type = 'search_context';
  $pane->subtype = 'search_context';
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
    'css_class' => 'js-below-search-result js-mobile',
  );
  $pane->extras = array();
  $pane->position = 7;
  $pane->locks = array();
  $pane->uuid = '05d87521-c6f0-4a56-aed9-e232f92f3194';
  $display->content['new-05d87521-c6f0-4a56-aed9-e232f92f3194'] = $pane;
  $display->panels['main_content'][7] = 'new-05d87521-c6f0-4a56-aed9-e232f92f3194';
  $pane = new stdClass();
  $pane->pid = 'new-07d2c562-f846-4241-b93f-7c1d723ff29d';
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
  $pane->position = 0;
  $pane->locks = '';
  $pane->uuid = '07d2c562-f846-4241-b93f-7c1d723ff29d';
  $display->content['new-07d2c562-f846-4241-b93f-7c1d723ff29d'] = $pane;
  $display->panels['right_sidebar'][0] = 'new-07d2c562-f846-4241-b93f-7c1d723ff29d';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['search_ting_search_panel_context_with_related_content'] = $handler;

  return $export;
}
