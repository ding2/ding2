<?php
/**
 * @file
 * ding_list_installer.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function ding_list_installer_default_page_manager_pages() {
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
        'name' => 'external_user',
        'settings' => NULL,
        'context' => array(
          0 => 'logged-in-user',
        ),
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
    $pane->pid = 'new-7d5c6e1f-16a0-4dde-9218-cb2663da215f';
    $pane->panel = 'left_sidebar';
    $pane->type = 'block';
    $pane->subtype = 'system-user-menu';
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
    $pane->uuid = '7d5c6e1f-16a0-4dde-9218-cb2663da215f';
    $display->content['new-7d5c6e1f-16a0-4dde-9218-cb2663da215f'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-7d5c6e1f-16a0-4dde-9218-cb2663da215f';
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
  $page->path = 'list/%ding_type/edit';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'user_list',
        'settings' => array(
          'visibility_settings' => 'edit',
        ),
        'context' => array(
          0 => 'logged-in-user',
          1 => 'argument_entity_id:ding_type_1',
        ),
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array();
  $page->arguments = array(
    'ding_type' => array(
      'id' => 1,
      'identifier' => 'ding_type: ID',
      'name' => 'entity_id:ding_type',
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
      'plugins' => array(
        0 => array(
          'name' => 'user_list',
          'settings' => array(
            'visibility_settings' => 'edit',
          ),
          'context' => array(
            0 => 'logged-in-user',
            1 => 'argument_entity_id:ding_type_1',
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
  $display->title = '%ding_type:title';
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
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
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
  $page->path = 'list/%ding_type/share';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'user_list',
        'settings' => array(
          'visibility_settings' => 'view',
        ),
        'context' => array(
          0 => 'logged-in-user',
          1 => 'argument_entity_id:ding_type_1',
        ),
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array();
  $page->arguments = array(
    'ding_type' => array(
      'id' => 1,
      'identifier' => 'ding_type: ID',
      'name' => 'entity_id:ding_type',
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
  $display->title = '%ding_type:title';
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
  $page->path = 'list/%ding_type';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'user_list',
        'settings' => array(
          'visibility_settings' => 'view',
          'list_argument' => '2',
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array();
  $page->arguments = array(
    'ding_type' => array(
      'id' => 1,
      'identifier' => 'ding_type: ID',
      'name' => 'entity_id:ding_type',
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
  $handler->name = 'page_page_ding_list_view_panel_context_2';
  $handler->task = 'page';
  $handler->subtask = 'page_ding_list_view';
  $handler->handler = 'panel_context';
  $handler->weight = -30;
  $handler->conf = array(
    'title' => 'Interest list panel',
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
          'name' => 'entity_field_value:ding_type:ding_list:field_list_type',
          'settings' => array(
            'field_list_type' => array(
              'und' => array(
                0 => array(
                  'value' => 'interests',
                ),
              ),
            ),
            'field_list_type_value' => array(
              0 => array(
                'value' => 'interests',
              ),
            ),
            'field_list_type_format' => array(
              0 => array(
                'value' => 'interests',
              ),
            ),
          ),
          'context' => 'argument_entity_id:ding_type_1',
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
      'branding' => NULL,
      'header' => NULL,
      'navigation' => NULL,
      'content' => NULL,
      'footer' => NULL,
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
  $display->title = '%ding_type:title';
  $display->uuid = '1838d05d-2ad7-4f6f-8176-17d51c8fd5b1';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-f3c44a50-69be-447d-b3b3-e406d7f8cb3d';
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
    $pane->uuid = 'f3c44a50-69be-447d-b3b3-e406d7f8cb3d';
    $display->content['new-f3c44a50-69be-447d-b3b3-e406d7f8cb3d'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-f3c44a50-69be-447d-b3b3-e406d7f8cb3d';
    $pane = new stdClass();
    $pane->pid = 'new-08fdcb78-1289-4d46-8b95-5592fd14eb9d';
    $pane->panel = 'main_content';
    $pane->type = 'list_followers';
    $pane->subtype = 'list_followers';
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
    $pane->uuid = '08fdcb78-1289-4d46-8b95-5592fd14eb9d';
    $display->content['new-08fdcb78-1289-4d46-8b95-5592fd14eb9d'] = $pane;
    $display->panels['main_content'][0] = 'new-08fdcb78-1289-4d46-8b95-5592fd14eb9d';
    $pane = new stdClass();
    $pane->pid = 'new-6522f0cd-55b6-410c-9bae-3b3f8f08f00f';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_list_elements-panel_pane_2';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'use_pager' => 0,
      'pager_id' => '0',
      'items_per_page' => '10',
      'offset' => '0',
      'override_title' => 1,
      'override_title_text' => '<none>',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '6522f0cd-55b6-410c-9bae-3b3f8f08f00f';
    $display->content['new-6522f0cd-55b6-410c-9bae-3b3f8f08f00f'] = $pane;
    $display->panels['main_content'][1] = 'new-6522f0cd-55b6-410c-9bae-3b3f8f08f00f';
    $pane = new stdClass();
    $pane->pid = 'new-0357577e-2618-45d0-9290-c453913e0043';
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '0357577e-2618-45d0-9290-c453913e0043';
    $display->content['new-0357577e-2618-45d0-9290-c453913e0043'] = $pane;
    $display->panels['main_content'][2] = 'new-0357577e-2618-45d0-9290-c453913e0043';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-08fdcb78-1289-4d46-8b95-5592fd14eb9d';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_page_ding_list_view_panel_context_3';
  $handler->task = 'page';
  $handler->subtask = 'page_ding_list_view';
  $handler->handler = 'panel_context';
  $handler->weight = -29;
  $handler->conf = array(
    'title' => 'Ratings list panel',
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
          'name' => 'entity_field_value:ding_type:ding_list:field_list_type',
          'settings' => array(
            'field_list_type' => array(
              'und' => array(
                0 => array(
                  'value' => 'ratings',
                ),
              ),
            ),
            'field_list_type_value' => array(
              0 => array(
                'value' => 'ratings',
              ),
            ),
            'field_list_type_format' => array(
              0 => array(
                'value' => 'ratings',
              ),
            ),
          ),
          'context' => 'argument_entity_id:ding_type_1',
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
      'branding' => NULL,
      'header' => NULL,
      'navigation' => NULL,
      'content' => NULL,
      'footer' => NULL,
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
  $display->uuid = 'ad6764cb-72bf-47ec-930a-732f48dc0cb3';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-e2582186-d894-4d24-b4de-0fd01537ec3f';
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
    $pane->uuid = 'e2582186-d894-4d24-b4de-0fd01537ec3f';
    $display->content['new-e2582186-d894-4d24-b4de-0fd01537ec3f'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-e2582186-d894-4d24-b4de-0fd01537ec3f';
    $pane = new stdClass();
    $pane->pid = 'new-2a35405a-6396-48c9-a3e8-f1182af32625';
    $pane->panel = 'main_content';
    $pane->type = 'list_followers';
    $pane->subtype = 'list_followers';
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
    $pane->uuid = '2a35405a-6396-48c9-a3e8-f1182af32625';
    $display->content['new-2a35405a-6396-48c9-a3e8-f1182af32625'] = $pane;
    $display->panels['main_content'][0] = 'new-2a35405a-6396-48c9-a3e8-f1182af32625';
    $pane = new stdClass();
    $pane->pid = 'new-027999f9-cb20-4a51-b97f-fadace305a3d';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_list_elements-panel_pane_3';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'use_pager' => 0,
      'pager_id' => '0',
      'items_per_page' => '10',
      'offset' => '0',
      'override_title' => 1,
      'override_title_text' => '<none>',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '027999f9-cb20-4a51-b97f-fadace305a3d';
    $display->content['new-027999f9-cb20-4a51-b97f-fadace305a3d'] = $pane;
    $display->panels['main_content'][1] = 'new-027999f9-cb20-4a51-b97f-fadace305a3d';
    $pane = new stdClass();
    $pane->pid = 'new-edb024c0-742d-4f80-8a33-1e0d14f22d04';
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'edb024c0-742d-4f80-8a33-1e0d14f22d04';
    $display->content['new-edb024c0-742d-4f80-8a33-1e0d14f22d04'] = $pane;
    $display->panels['main_content'][2] = 'new-edb024c0-742d-4f80-8a33-1e0d14f22d04';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-2a35405a-6396-48c9-a3e8-f1182af32625';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
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
  $display->title = '%ding_type:title';
  $display->uuid = '8128a3a2-3296-46f4-bd3f-0f34e86bcb73';
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
    $pane->pid = 'new-aea07c96-ad88-4e14-80a7-23264747e203';
    $pane->panel = 'main_content';
    $pane->type = 'list_followers';
    $pane->subtype = 'list_followers';
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
    $pane->uuid = 'aea07c96-ad88-4e14-80a7-23264747e203';
    $display->content['new-aea07c96-ad88-4e14-80a7-23264747e203'] = $pane;
    $display->panels['main_content'][0] = 'new-aea07c96-ad88-4e14-80a7-23264747e203';
    $pane = new stdClass();
    $pane->pid = 'new-e1195ffb-63fb-4b67-9ee9-6d20d0c0ead0';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_list_elements-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'use_pager' => 0,
      'pager_id' => '0',
      'items_per_page' => '10',
      'offset' => '0',
      'override_title' => 1,
      'override_title_text' => '<none>',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'e1195ffb-63fb-4b67-9ee9-6d20d0c0ead0';
    $display->content['new-e1195ffb-63fb-4b67-9ee9-6d20d0c0ead0'] = $pane;
    $display->panels['main_content'][1] = 'new-e1195ffb-63fb-4b67-9ee9-6d20d0c0ead0';
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'f0e76ffa-abea-407f-a468-692229c54e81';
    $display->content['new-f0e76ffa-abea-407f-a468-692229c54e81'] = $pane;
    $display->panels['main_content'][2] = 'new-f0e76ffa-abea-407f-a468-692229c54e81';
    $pane = new stdClass();
    $pane->pid = 'new-be8eb5bc-a163-4123-97a3-7df269deff17';
    $pane->panel = 'main_content';
    $pane->type = 'sharer_pane';
    $pane->subtype = 'sharer_pane';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'entity_field_value:ding_type:ding_list:field_ding_list_status',
          'settings' => array(
            'field_ding_list_status' => array(
              'und' => array(
                0 => array(
                  'value' => 'public',
                ),
              ),
            ),
            'field_ding_list_status_value' => array(
              0 => 'public',
            ),
          ),
          'context' => 'argument_entity_id:ding_type_1',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'count' => '5',
      'override_title' => 0,
      'override_title_text' => '',
      'communities' => array(
        'facebook' => 'facebook',
        'twitter' => 'twitter',
      ),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = 'be8eb5bc-a163-4123-97a3-7df269deff17';
    $display->content['new-be8eb5bc-a163-4123-97a3-7df269deff17'] = $pane;
    $display->panels['main_content'][3] = 'new-be8eb5bc-a163-4123-97a3-7df269deff17';
    $pane = new stdClass();
    $pane->pid = 'new-b8ce1ce7-690b-426b-9331-363e945cd3c4';
    $pane->panel = 'main_content';
    $pane->type = 'private_share';
    $pane->subtype = 'private_share';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'entity_field_value:ding_type:ding_list:field_ding_list_status',
          'settings' => array(
            'field_ding_list_status' => array(
              'und' => array(
                0 => array(
                  'value' => 'public',
                ),
              ),
            ),
            'field_ding_list_status_value' => array(
              0 => 'public',
            ),
          ),
          'context' => 'argument_entity_id:ding_type_1',
          'not' => TRUE,
        ),
      ),
    );
    $pane->configuration = array(
      'communities' => array(
        'facebook' => 'facebook',
        'twitter' => 'twitter',
      ),
      'context' => 'argument_entity_id:ding_type_1',
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
    $pane->uuid = 'b8ce1ce7-690b-426b-9331-363e945cd3c4';
    $display->content['new-b8ce1ce7-690b-426b-9331-363e945cd3c4'] = $pane;
    $display->panels['main_content'][4] = 'new-b8ce1ce7-690b-426b-9331-363e945cd3c4';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-aea07c96-ad88-4e14-80a7-23264747e203';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['page_ding_list_view'] = $page;

  return $pages;

}
