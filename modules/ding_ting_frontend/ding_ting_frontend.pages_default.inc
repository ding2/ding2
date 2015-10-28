<?php
/**
 * @file
 * ding_ting_frontend.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function ding_ting_frontend_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'pm_existing_pages_fulltext_panel_context';
  $handler->task = 'pm_existing_pages';
  $handler->subtask = 'fulltext';
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
  $display->title = '';
  $display->uuid = '193e6dd3-abf4-4007-a730-afcc858727ce';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-7366f4b5-1c46-4994-a822-c1e205933342';
    $pane->panel = 'main_content';
    $pane->type = 'fulltext';
    $pane->subtype = 'fulltext';
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
    $pane->uuid = '7366f4b5-1c46-4994-a822-c1e205933342';
    $display->content['new-7366f4b5-1c46-4994-a822-c1e205933342'] = $pane;
    $display->panels['main_content'][0] = 'new-7366f4b5-1c46-4994-a822-c1e205933342';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['pm_existing_pages_fulltext_panel_context'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'pm_existing_pages_infomedia__panel_context_1538f85e-2f80-4ed9-bd22-3c38f8caefee';
  $handler->task = 'pm_existing_pages';
  $handler->subtask = 'infomedia';
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
    'name' => '',
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
  $display->uuid = '187f6693-111c-4782-83b3-8a3e38b588cb';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-598ca7ff-43a4-4c49-9ab8-92df3e53c6b9';
    $pane->panel = 'main_content';
    $pane->type = 'pm_existing_pages';
    $pane->subtype = 'pm_existing_pages';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      0 => 'task_id',
      'task_id' => 'infomedia',
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
    $pane->uuid = '598ca7ff-43a4-4c49-9ab8-92df3e53c6b9';
    $display->content['new-598ca7ff-43a4-4c49-9ab8-92df3e53c6b9'] = $pane;
    $display->panels['main_content'][0] = 'new-598ca7ff-43a4-4c49-9ab8-92df3e53c6b9';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-598ca7ff-43a4-4c49-9ab8-92df3e53c6b9';
  $handler->conf['display'] = $display;
  $export['pm_existing_pages_infomedia__panel_context_1538f85e-2f80-4ed9-bd22-3c38f8caefee'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'search_ting_search_panel_context';
  $handler->task = 'search';
  $handler->subtask = 'ting_search';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'ting search',
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
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '47206bf0-1031-456c-9aab-96b659e54d89';
    $display->content['new-47206bf0-1031-456c-9aab-96b659e54d89'] = $pane;
    $display->panels['main_content'][3] = 'new-47206bf0-1031-456c-9aab-96b659e54d89';
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
    $pane->position = 5;
    $pane->locks = '';
    $pane->uuid = '7c02f708-c47f-4eb5-8958-d6279de6ade4';
    $display->content['new-7c02f708-c47f-4eb5-8958-d6279de6ade4'] = $pane;
    $display->panels['main_content'][5] = 'new-7c02f708-c47f-4eb5-8958-d6279de6ade4';
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
  $export['search_ting_search_panel_context'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'ting_collection_panel_context';
  $handler->task = 'ting_collection';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
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
  $display->uuid = 'accd93cd-f443-4d6e-9be8-d91300f9b07a';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-4c54cd38-001a-424c-a467-1fd89a6d1c11';
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
    $pane->uuid = '4c54cd38-001a-424c-a467-1fd89a6d1c11';
    $display->content['new-4c54cd38-001a-424c-a467-1fd89a6d1c11'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-4c54cd38-001a-424c-a467-1fd89a6d1c11';
    $pane = new stdClass();
    $pane->pid = 'new-68662b45-8a6a-442f-89b4-4d76417bd855';
    $pane->panel = 'left_sidebar';
    $pane->type = 'block';
    $pane->subtype = 'ting-ting_object_types';
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
    $pane->position = 1;
    $pane->locks = '';
    $pane->uuid = '68662b45-8a6a-442f-89b4-4d76417bd855';
    $display->content['new-68662b45-8a6a-442f-89b4-4d76417bd855'] = $pane;
    $display->panels['left_sidebar'][1] = 'new-68662b45-8a6a-442f-89b4-4d76417bd855';
    $pane = new stdClass();
    $pane->pid = 'new-55cc4d0d-d8cd-46ae-96f7-18bb4fc809c8';
    $pane->panel = 'main_content';
    $pane->type = 'ting_collection';
    $pane->subtype = 'ting_collection';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_ting_collection_id_17',
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
    $pane->uuid = '55cc4d0d-d8cd-46ae-96f7-18bb4fc809c8';
    $display->content['new-55cc4d0d-d8cd-46ae-96f7-18bb4fc809c8'] = $pane;
    $display->panels['main_content'][0] = 'new-55cc4d0d-d8cd-46ae-96f7-18bb4fc809c8';
    $pane = new stdClass();
    $pane->pid = 'new-26a27e6c-f934-4169-a06e-04db0f61ebf6';
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
    $pane->locks = '';
    $pane->uuid = '26a27e6c-f934-4169-a06e-04db0f61ebf6';
    $display->content['new-26a27e6c-f934-4169-a06e-04db0f61ebf6'] = $pane;
    $display->panels['right_sidebar'][0] = 'new-26a27e6c-f934-4169-a06e-04db0f61ebf6';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['ting_collection_panel_context'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'ting_object_panel_context';
  $handler->task = 'ting_object';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Ting object',
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
    $pane->pid = 'new-2c6af9c6-63ae-4100-9b56-e3b1bee1ce9a';
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
    $pane->locks = '';
    $pane->uuid = '2c6af9c6-63ae-4100-9b56-e3b1bee1ce9a';
    $display->content['new-2c6af9c6-63ae-4100-9b56-e3b1bee1ce9a'] = $pane;
    $display->panels['right_sidebar'][0] = 'new-2c6af9c6-63ae-4100-9b56-e3b1bee1ce9a';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['ting_object_panel_context'] = $handler;

  return $export;
}
