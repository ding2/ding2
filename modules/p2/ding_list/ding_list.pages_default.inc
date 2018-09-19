<?php
/**
 * @file
 * ding_list.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function ding_list_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'ding_list_public_lists';
  $page->task = 'page';
  $page->admin_title = 'Ding List Public Lists';
  $page->admin_description = '';
  $page->path = 'public-lists';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_ding_list_public_lists__panel';
  $handler->task = 'page';
  $handler->subtask = 'ding_list_public_lists';
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
    'name' => 'panel',
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
  $display->uuid = '4893be64-f7b2-4f4f-86ae-0268af15671e';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-676cad11-d7c4-4084-bdf1-3df32af899df';
    $pane->panel = 'attachment_1_1';
    $pane->type = 'public_lists';
    $pane->subtype = 'public_lists';
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
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '676cad11-d7c4-4084-bdf1-3df32af899df';
    $display->content['new-676cad11-d7c4-4084-bdf1-3df32af899df'] = $pane;
    $display->panels['attachment_1_1'][0] = 'new-676cad11-d7c4-4084-bdf1-3df32af899df';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-676cad11-d7c4-4084-bdf1-3df32af899df';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['ding_list_public_lists'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'page_ding_list_create';
  $page->task = 'page';
  $page->admin_title = 'Page Ding List Create';
  $page->admin_description = '';
  $page->path = 'list/create';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'perm',
        'settings' => array(
          'perm' => 'use personalisation',
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array(
    'type' => 'action',
    'title' => 'asf',
    'name' => 'user-menu',
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
  $handler->name = 'page_page_ding_list_create_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'page_ding_list_create';
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
  $display->uuid = '2ea80930-b247-40e9-b11d-6a77d17baf76';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-85cb79c6-27e1-4665-82a8-d133684d0a20';
    $pane->panel = 'left_sidebar';
    $pane->type = 'list_menu';
    $pane->subtype = 'list_menu';
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
    $pane->uuid = '85cb79c6-27e1-4665-82a8-d133684d0a20';
    $display->content['new-85cb79c6-27e1-4665-82a8-d133684d0a20'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-85cb79c6-27e1-4665-82a8-d133684d0a20';
    $pane = new stdClass();
    $pane->pid = 'new-030a1967-3309-4d13-8d4b-b1d1a8928b35';
    $pane->panel = 'left_sidebar';
    $pane->type = 'campaign';
    $pane->subtype = 'campaign';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'ding_campaign_count' => 3,
      'ding_campaign_offset' => 0,
      'ding_campaign_style' => 'ding_campaign_full_width',
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
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '030a1967-3309-4d13-8d4b-b1d1a8928b35';
    $display->content['new-030a1967-3309-4d13-8d4b-b1d1a8928b35'] = $pane;
    $display->panels['left_sidebar'][1] = 'new-030a1967-3309-4d13-8d4b-b1d1a8928b35';
    $pane = new stdClass();
    $pane->pid = 'new-b44b6f0a-c530-4dfb-b949-53cf6af6a8c6';
    $pane->panel = 'main_content';
    $pane->type = 'list_create';
    $pane->subtype = 'list_create';
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
    $pane->uuid = 'b44b6f0a-c530-4dfb-b949-53cf6af6a8c6';
    $display->content['new-b44b6f0a-c530-4dfb-b949-53cf6af6a8c6'] = $pane;
    $display->panels['main_content'][0] = 'new-b44b6f0a-c530-4dfb-b949-53cf6af6a8c6';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['page_ding_list_create'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'page_ding_list_edit';
  $page->task = 'page';
  $page->admin_title = 'Page Ding List Edit';
  $page->admin_description = '';
  $page->path = 'list/%ding_list_list/edit';
  $page->access = array(
    'plugins' => array(
      1 => array(
        'name' => 'user_list',
        'settings' => array(
          'visibility_settings' => 'edit',
        ),
        'context' => array(
          0 => 'logged-in-user',
          1 => 'argument_list_id_1',
        ),
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array();
  $page->arguments = array(
    'ding_list_list' => array(
      'id' => 1,
      'identifier' => 'Ding list: List ID',
      'name' => 'list_id',
      'settings' => array(),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_page_ding_list_edit_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'page_ding_list_edit';
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
    'access' => array(
      'plugins' => array(),
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
  $display->title = '%ding_list_list:title';
  $display->uuid = '9779b00e-e5e0-422e-9334-73968d52571b';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-20f9d50f-c373-42f3-9206-b4040600b98b';
    $pane->panel = 'left_sidebar';
    $pane->type = 'list_menu';
    $pane->subtype = 'list_menu';
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
    $pane->uuid = '20f9d50f-c373-42f3-9206-b4040600b98b';
    $display->content['new-20f9d50f-c373-42f3-9206-b4040600b98b'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-20f9d50f-c373-42f3-9206-b4040600b98b';
    $pane = new stdClass();
    $pane->pid = 'new-0fa8b7e4-f8c5-4257-acd3-e625cf9d6b8a';
    $pane->panel = 'left_sidebar';
    $pane->type = 'campaign';
    $pane->subtype = 'campaign';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'ding_campaign_count' => 3,
      'ding_campaign_offset' => 0,
      'ding_campaign_style' => 'ding_campaign_full_width',
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
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '0fa8b7e4-f8c5-4257-acd3-e625cf9d6b8a';
    $display->content['new-0fa8b7e4-f8c5-4257-acd3-e625cf9d6b8a'] = $pane;
    $display->panels['left_sidebar'][1] = 'new-0fa8b7e4-f8c5-4257-acd3-e625cf9d6b8a';
    $pane = new stdClass();
    $pane->pid = 'new-57afe885-c847-4468-b003-e4c593c74c6b';
    $pane->panel = 'main_content';
    $pane->type = 'edit_list';
    $pane->subtype = 'edit_list';
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
    $pane->uuid = '57afe885-c847-4468-b003-e4c593c74c6b';
    $display->content['new-57afe885-c847-4468-b003-e4c593c74c6b'] = $pane;
    $display->panels['main_content'][0] = 'new-57afe885-c847-4468-b003-e4c593c74c6b';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-57afe885-c847-4468-b003-e4c593c74c6b';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['page_ding_list_edit'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'page_ding_list_share';
  $page->task = 'page';
  $page->admin_title = 'Page Ding List Share';
  $page->admin_description = '';
  $page->path = 'list/%ding_list_list/share';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'user_list',
        'settings' => array(
          'visibility_settings' => 'view',
        ),
        'context' => array(
          0 => 'logged-in-user',
          1 => 'argument_list_id_1',
        ),
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array();
  $page->arguments = array(
    'ding_list_list' => array(
      'id' => 1,
      'identifier' => 'Ding list: List ID',
      'name' => 'list_id',
      'settings' => array(),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_page_ding_list_share_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'page_ding_list_share';
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
    'access' => array(
      'plugins' => array(),
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
  $display->title = '%ding_list_list:title';
  $display->uuid = 'd8a80332-bb30-4fc8-8027-477a80bedc6c';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-b5400e30-65c7-4c2e-a52c-c2b610c46af2';
    $pane->panel = 'left_sidebar';
    $pane->type = 'list_menu';
    $pane->subtype = 'list_menu';
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
    $pane->uuid = 'b5400e30-65c7-4c2e-a52c-c2b610c46af2';
    $display->content['new-b5400e30-65c7-4c2e-a52c-c2b610c46af2'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-b5400e30-65c7-4c2e-a52c-c2b610c46af2';
    $pane = new stdClass();
    $pane->pid = 'new-8bb85cae-e461-4101-967d-0a0cb7f45f44';
    $pane->panel = 'left_sidebar';
    $pane->type = 'campaign';
    $pane->subtype = 'campaign';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'ding_campaign_count' => 3,
      'ding_campaign_offset' => 0,
      'ding_campaign_style' => 'ding_campaign_full_width',
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
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '8bb85cae-e461-4101-967d-0a0cb7f45f44';
    $display->content['new-8bb85cae-e461-4101-967d-0a0cb7f45f44'] = $pane;
    $display->panels['left_sidebar'][1] = 'new-8bb85cae-e461-4101-967d-0a0cb7f45f44';
    $pane = new stdClass();
    $pane->pid = 'new-0bd01468-7972-47f2-bf9b-83af83c72a01';
    $pane->panel = 'main_content';
    $pane->type = 'share_list';
    $pane->subtype = 'share_list';
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
    $pane->uuid = '0bd01468-7972-47f2-bf9b-83af83c72a01';
    $display->content['new-0bd01468-7972-47f2-bf9b-83af83c72a01'] = $pane;
    $display->panels['main_content'][0] = 'new-0bd01468-7972-47f2-bf9b-83af83c72a01';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['page_ding_list_share'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'page_ding_list_view';
  $page->task = 'page';
  $page->admin_title = 'Page Ding List View';
  $page->admin_description = '';
  $page->path = 'list/%ding_list_list';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'user_list',
        'settings' => array(
          'visibility_settings' => 'view',
        ),
        'context' => array(
          0 => 'logged-in-user',
          1 => 'argument_list_id_1',
        ),
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array();
  $page->arguments = array(
    'ding_list_list' => array(
      'id' => 1,
      'identifier' => 'Ding list: List ID',
      'name' => 'list_id',
      'settings' => array(),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_page_ding_list_view_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'page_ding_list_view';
  $handler->handler = 'panel_context';
  $handler->weight = -28;
  $handler->conf = array(
    'title' => 'Default panel',
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
  $display->title = '%ding_list_list:title';
  $display->uuid = '8128a3a2-3296-46f4-bd3f-0f34e86bcb73';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'page_page_ding_list_view_panel_context';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-c21a508d-ee0c-449a-8550-ca8b60812664';
    $pane->panel = 'left_sidebar';
    $pane->type = 'list_menu';
    $pane->subtype = 'list_menu';
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
    $pane->uuid = 'c21a508d-ee0c-449a-8550-ca8b60812664';
    $display->content['new-c21a508d-ee0c-449a-8550-ca8b60812664'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-c21a508d-ee0c-449a-8550-ca8b60812664';
    $pane = new stdClass();
    $pane->pid = 'new-82abe182-e133-48a4-aa74-c60be3792de3';
    $pane->panel = 'main_content';
    $pane->type = 'list';
    $pane->subtype = 'list';
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
    $pane->uuid = '82abe182-e133-48a4-aa74-c60be3792de3';
    $display->content['new-82abe182-e133-48a4-aa74-c60be3792de3'] = $pane;
    $display->panels['main_content'][0] = 'new-82abe182-e133-48a4-aa74-c60be3792de3';
    $pane = new stdClass();
    $pane->pid = 'new-f0e76ffa-abea-407f-a468-692229c54e81';
    $pane->panel = 'main_content';
    $pane->type = 'add_list';
    $pane->subtype = 'add_list';
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
    $pane->uuid = 'f0e76ffa-abea-407f-a468-692229c54e81';
    $display->content['new-f0e76ffa-abea-407f-a468-692229c54e81'] = $pane;
    $display->panels['main_content'][1] = 'new-f0e76ffa-abea-407f-a468-692229c54e81';
    $pane = new stdClass();
    $pane->pid = 'new-b8ce1ce7-690b-426b-9331-363e945cd3c4';
    $pane->panel = 'main_content';
    $pane->type = 'private_share';
    $pane->subtype = 'private_share';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(),
    );
    $pane->configuration = array(
      'communities' => array(
        'facebook' => 'facebook',
        'twitter' => 'twitter',
      ),
      'context' => 'argument_list_id_1',
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
    $pane->uuid = 'b8ce1ce7-690b-426b-9331-363e945cd3c4';
    $display->content['new-b8ce1ce7-690b-426b-9331-363e945cd3c4'] = $pane;
    $display->panels['main_content'][2] = 'new-b8ce1ce7-690b-426b-9331-363e945cd3c4';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['page_ding_list_view'] = $page;

  return $pages;

}
