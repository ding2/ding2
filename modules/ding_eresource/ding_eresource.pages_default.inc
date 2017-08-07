<?php
/**
 * @file
 * ding_eresource.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function ding_eresource_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view_panel_context_ding_eresource';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -22;
  $handler->conf = array(
    'title' => 'Ding E-resource',
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
        'identifier' => 'Category term',
        'keyword' => 'taxonomy_term',
        'name' => 'entity_from_field:field_ding_eresource_category-node-taxonomy_term',
        'delta' => '0',
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
              'ding_eresource' => 'ding_eresource',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
    'panels_breadcrumbs_state' => 1,
    'panels_breadcrumbs_titles' => 'FAQ
%node:title',
    'panels_breadcrumbs_paths' => 'faq
<none>',
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
  $display->uuid = 'd82976d5-f78c-46b3-8d9a-c2ba458d539c';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-203b68b0-35f7-4be2-bac3-b300a7e5f01c';
    $pane->panel = 'content';
    $pane->type = 'taxonomy_menu';
    $pane->subtype = 'taxonomy_menu';
    $pane->shown = FALSE;
    $pane->access = array();
    $pane->configuration = array(
      'slug' => 'e-materialer',
      'default_link_text' => 'All categories',
      'dropdown' => 0,
      'vocabulary' => 'e_resource_category',
      'base' => '',
      'context' => array(
        0 => 'relationship_entity_from_field:field_ding_eresource_category-node-taxonomy_term_1',
        1 => 'empty',
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
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '203b68b0-35f7-4be2-bac3-b300a7e5f01c';
    $display->content['new-203b68b0-35f7-4be2-bac3-b300a7e5f01c'] = $pane;
    $display->panels['content'][0] = 'new-203b68b0-35f7-4be2-bac3-b300a7e5f01c';
    $pane = new stdClass();
    $pane->pid = 'new-9585f181-cf01-4270-a7fd-b981246d6e2c';
    $pane->panel = 'content';
    $pane->type = 'node_content';
    $pane->subtype = 'node_content';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'links' => 0,
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
    $pane->uuid = '9585f181-cf01-4270-a7fd-b981246d6e2c';
    $display->content['new-9585f181-cf01-4270-a7fd-b981246d6e2c'] = $pane;
    $display->panels['content'][1] = 'new-9585f181-cf01-4270-a7fd-b981246d6e2c';
    $pane = new stdClass();
    $pane->pid = 'new-fb3893c4-f99a-47a1-989f-46b5483382fd';
    $pane->panel = 'content';
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
    $pane->position = 2;
    $pane->locks = '';
    $pane->uuid = 'fb3893c4-f99a-47a1-989f-46b5483382fd';
    $display->content['new-fb3893c4-f99a-47a1-989f-46b5483382fd'] = $pane;
    $display->panels['content'][2] = 'new-fb3893c4-f99a-47a1-989f-46b5483382fd';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-9585f181-cf01-4270-a7fd-b981246d6e2c';
  $handler->conf['display'] = $display;
  $export['node_view_panel_context_ding_eresource'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'term_view_ding_eresource_category';
  $handler->task = 'term_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 5;
  $handler->conf = array(
    'title' => 'Ding e-resource',
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
              'e_resource_category' => 'e_resource_category',
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
  $display->title = 'E-resurser';
  $display->uuid = 'd44ae923-a33f-4fc1-8d4c-2de4afe70ce0';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-7fce740e-cd45-46f9-bd91-712f24b7a0f9';
    $pane->panel = 'left_sidebar';
    $pane->type = 'menu_title';
    $pane->subtype = 'menu_title';
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
    $pane->uuid = '7fce740e-cd45-46f9-bd91-712f24b7a0f9';
    $display->content['new-7fce740e-cd45-46f9-bd91-712f24b7a0f9'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-7fce740e-cd45-46f9-bd91-712f24b7a0f9';
    $pane = new stdClass();
    $pane->pid = 'new-5972e678-414e-4ef5-8802-35010f0f84aa';
    $pane->panel = 'left_sidebar';
    $pane->type = 'taxonomy_menu';
    $pane->subtype = 'taxonomy_menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'slug' => 'e-materialer',
      'default_link_text' => 'All categories',
      'dropdown' => 0,
      'vocabulary' => 'e_resource_category',
      'base' => '',
      'context' => array(
        0 => 'argument_term_1',
        1 => 'empty',
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '5972e678-414e-4ef5-8802-35010f0f84aa';
    $display->content['new-5972e678-414e-4ef5-8802-35010f0f84aa'] = $pane;
    $display->panels['left_sidebar'][1] = 'new-5972e678-414e-4ef5-8802-35010f0f84aa';
    $pane = new stdClass();
    $pane->pid = 'new-67fac3c4-5600-4994-b091-8d680e22ac66';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_eresource-ding_eresource_category';
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
    $pane->uuid = '67fac3c4-5600-4994-b091-8d680e22ac66';
    $display->content['new-67fac3c4-5600-4994-b091-8d680e22ac66'] = $pane;
    $display->panels['main_content'][0] = 'new-67fac3c4-5600-4994-b091-8d680e22ac66';
    $pane = new stdClass();
    $pane->pid = 'new-4c3eca62-ff45-4c17-bd19-03d7d91dab2e';
    $pane->panel = 'main_content';
    $pane->type = 'ding_eresource_index';
    $pane->subtype = 'ding_eresource_index';
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
    $pane->locks = array();
    $pane->uuid = '4c3eca62-ff45-4c17-bd19-03d7d91dab2e';
    $display->content['new-4c3eca62-ff45-4c17-bd19-03d7d91dab2e'] = $pane;
    $display->panels['main_content'][1] = 'new-4c3eca62-ff45-4c17-bd19-03d7d91dab2e';
    $pane = new stdClass();
    $pane->pid = 'new-6083a62a-5e1f-49e8-b9b9-ef1fd6d8a8ec';
    $pane->panel = 'main_content';
    $pane->type = 'block';
    $pane->subtype = 'views-98880b6fbff6f74deeae473932e04e0b';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'inherit_path' => 1,
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
    $pane->uuid = '6083a62a-5e1f-49e8-b9b9-ef1fd6d8a8ec';
    $display->content['new-6083a62a-5e1f-49e8-b9b9-ef1fd6d8a8ec'] = $pane;
    $display->panels['main_content'][2] = 'new-6083a62a-5e1f-49e8-b9b9-ef1fd6d8a8ec';
    $pane = new stdClass();
    $pane->pid = 'new-d6286c13-2986-46ef-bb83-a85ff00275fc';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_eresource-ding_eresource_list';
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
    $pane->uuid = 'd6286c13-2986-46ef-bb83-a85ff00275fc';
    $display->content['new-d6286c13-2986-46ef-bb83-a85ff00275fc'] = $pane;
    $display->panels['main_content'][3] = 'new-d6286c13-2986-46ef-bb83-a85ff00275fc';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-4c3eca62-ff45-4c17-bd19-03d7d91dab2e';
  $handler->conf['display'] = $display;
  $export['term_view_ding_eresource_category'] = $handler;

  return $export;
}

/**
 * Implements hook_default_page_manager_pages().
 */
function ding_eresource_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'ding_eresources';
  $page->task = 'page';
  $page->admin_title = 'Ding E-resources';
  $page->admin_description = '';
  $page->path = 'e-materialer';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_ding_eresources_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'ding_eresources';
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
  $display->title = 'E-resurser';
  $display->uuid = 'd44ae923-a33f-4fc1-8d4c-2de4afe70ce0';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-0089f8fc-d009-4d6d-91b9-1df49dfa4d3b';
    $pane->panel = 'left_sidebar';
    $pane->type = 'menu_title';
    $pane->subtype = 'menu_title';
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
    $pane->uuid = '0089f8fc-d009-4d6d-91b9-1df49dfa4d3b';
    $display->content['new-0089f8fc-d009-4d6d-91b9-1df49dfa4d3b'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-0089f8fc-d009-4d6d-91b9-1df49dfa4d3b';
    $pane = new stdClass();
    $pane->pid = 'new-dde3b04f-c23f-4232-8881-46714c01690a';
    $pane->panel = 'left_sidebar';
    $pane->type = 'taxonomy_menu';
    $pane->subtype = 'taxonomy_menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'slug' => 'e-materialer',
      'default_link_text' => 'All categories',
      'dropdown' => 0,
      'vocabulary' => 'e_resource_category',
      'base' => '',
      'context' => array(
        0 => 'argument_term_1',
        1 => 'empty',
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
    $pane->uuid = 'dde3b04f-c23f-4232-8881-46714c01690a';
    $display->content['new-dde3b04f-c23f-4232-8881-46714c01690a'] = $pane;
    $display->panels['left_sidebar'][1] = 'new-dde3b04f-c23f-4232-8881-46714c01690a';
    $pane = new stdClass();
    $pane->pid = 'new-67fac3c4-5600-4994-b091-8d680e22ac66';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_eresource-ding_eresource_category';
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
    $pane->uuid = '67fac3c4-5600-4994-b091-8d680e22ac66';
    $display->content['new-67fac3c4-5600-4994-b091-8d680e22ac66'] = $pane;
    $display->panels['main_content'][0] = 'new-67fac3c4-5600-4994-b091-8d680e22ac66';
    $pane = new stdClass();
    $pane->pid = 'new-4c3eca62-ff45-4c17-bd19-03d7d91dab2e';
    $pane->panel = 'main_content';
    $pane->type = 'ding_eresource_index';
    $pane->subtype = 'ding_eresource_index';
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
    $pane->locks = array();
    $pane->uuid = '4c3eca62-ff45-4c17-bd19-03d7d91dab2e';
    $display->content['new-4c3eca62-ff45-4c17-bd19-03d7d91dab2e'] = $pane;
    $display->panels['main_content'][1] = 'new-4c3eca62-ff45-4c17-bd19-03d7d91dab2e';
    $pane = new stdClass();
    $pane->pid = 'new-6083a62a-5e1f-49e8-b9b9-ef1fd6d8a8ec';
    $pane->panel = 'main_content';
    $pane->type = 'block';
    $pane->subtype = 'views-98880b6fbff6f74deeae473932e04e0b';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'inherit_path' => 1,
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
    $pane->uuid = '6083a62a-5e1f-49e8-b9b9-ef1fd6d8a8ec';
    $display->content['new-6083a62a-5e1f-49e8-b9b9-ef1fd6d8a8ec'] = $pane;
    $display->panels['main_content'][2] = 'new-6083a62a-5e1f-49e8-b9b9-ef1fd6d8a8ec';
    $pane = new stdClass();
    $pane->pid = 'new-d6286c13-2986-46ef-bb83-a85ff00275fc';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_eresource-ding_eresource_list';
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
    $pane->uuid = 'd6286c13-2986-46ef-bb83-a85ff00275fc';
    $display->content['new-d6286c13-2986-46ef-bb83-a85ff00275fc'] = $pane;
    $display->panels['main_content'][3] = 'new-d6286c13-2986-46ef-bb83-a85ff00275fc';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-4c3eca62-ff45-4c17-bd19-03d7d91dab2e';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['ding_eresources'] = $page;

  return $pages;

}
