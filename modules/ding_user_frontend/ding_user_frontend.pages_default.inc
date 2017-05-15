<?php
/**
 * @file
 * ding_user_frontend.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function ding_user_frontend_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'user_edit_panel_context';
  $handler->task = 'user_edit';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -29;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(
      0 => array(
        'identifier' => 'Profile2 type',
        'keyword' => 'user_2',
        'name' => 'profile2',
        'type' => 'select',
        'uid' => '',
        'default_type' => 'provider_alma',
        'id' => 1,
      ),
    ),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(),
      'logic' => 'and',
    ),
    'metatag_panels' => array(
      'enabled' => 1,
      'metatags' => array(
        'title' => array(
          'value' => 'Edit profile | [current-page:pager][site:name]',
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
  $display->title = '';
  $display->uuid = '554649f4-0529-4783-9b86-51026c768269';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-8bf84cda-201b-4d35-8df9-54edaf360565';
    $pane->panel = 'main_content';
    $pane->type = 'profile2_form';
    $pane->subtype = 'profile2_form';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_user_edit_1',
        1 => 'context_profile2_1',
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
    $pane->uuid = '8bf84cda-201b-4d35-8df9-54edaf360565';
    $display->content['new-8bf84cda-201b-4d35-8df9-54edaf360565'] = $pane;
    $display->panels['main_content'][0] = 'new-8bf84cda-201b-4d35-8df9-54edaf360565';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['user_edit_panel_context'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'user_edit_panel_context_2';
  $handler->task = 'user_edit';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -30;
  $handler->conf = array(
    'title' => 'Provider profile',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(
      0 => array(
        'identifier' => 'Profile2 type',
        'keyword' => 'user_2',
        'name' => 'profile2',
        'type' => 'select',
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
            0 => 'argument_user_edit_1',
          ),
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
    'metatag_panels' => array(
      'enabled' => 1,
      'metatags' => array(
        'title' => array(
          'value' => 'Edit profile | [current-page:pager][site:name]',
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
  $display->uuid = '87c1ede8-382a-4c1e-aed4-19f750af7522';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-121673e4-ec13-4123-88da-a3851e600028';
    $pane->panel = 'left_sidebar';
    $pane->type = 'user_menu';
    $pane->subtype = 'user_menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_user_edit_1',
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
    $pane->uuid = '121673e4-ec13-4123-88da-a3851e600028';
    $display->content['new-121673e4-ec13-4123-88da-a3851e600028'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-121673e4-ec13-4123-88da-a3851e600028';
    $pane = new stdClass();
    $pane->pid = 'new-6122fec0-74e0-458d-94d1-581fd43434df';
    $pane->panel = 'main_content';
    $pane->type = 'profile2';
    $pane->subtype = 'profile2';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_user_edit_1',
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
    $pane->uuid = '6122fec0-74e0-458d-94d1-581fd43434df';
    $display->content['new-6122fec0-74e0-458d-94d1-581fd43434df'] = $pane;
    $display->panels['main_content'][0] = 'new-6122fec0-74e0-458d-94d1-581fd43434df';
    $pane = new stdClass();
    $pane->pid = 'new-7a8a1910-8380-44a6-9b6e-6e1fe10cbc2d';
    $pane->panel = 'main_content';
    $pane->type = 'profile2_form';
    $pane->subtype = 'profile2_form';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_user_edit_1',
        1 => 'context_profile2_1',
      ),
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '7a8a1910-8380-44a6-9b6e-6e1fe10cbc2d';
    $display->content['new-7a8a1910-8380-44a6-9b6e-6e1fe10cbc2d'] = $pane;
    $display->panels['main_content'][1] = 'new-7a8a1910-8380-44a6-9b6e-6e1fe10cbc2d';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['user_edit_panel_context_2'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'user_view_panel_context';
  $handler->task = 'user_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -28;
  $handler->conf = array(
    'title' => 'User profile',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'metatag_panels' => array(
      'enabled' => 1,
      'metatags' => array(
        'title' => array(
          'value' => 'User profile | [current-page:pager][site:name]',
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
  $display->title = '';
  $display->uuid = '2bee1e6c-8cb9-489a-9b3e-9e80b6417074';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-d9b7b379-4c92-4e2e-9d80-4c0ec07bdb83';
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
    $pane->uuid = 'd9b7b379-4c92-4e2e-9d80-4c0ec07bdb83';
    $display->content['new-d9b7b379-4c92-4e2e-9d80-4c0ec07bdb83'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-d9b7b379-4c92-4e2e-9d80-4c0ec07bdb83';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = 'dc4b2f5e-f42e-48bd-9f01-f81841042dbf';
    $display->content['new-dc4b2f5e-f42e-48bd-9f01-f81841042dbf'] = $pane;
    $display->panels['main_content'][0] = 'new-dc4b2f5e-f42e-48bd-9f01-f81841042dbf';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['user_view_panel_context'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'user_view_panel_context_2';
  $handler->task = 'user_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -29;
  $handler->conf = array(
    'title' => 'Provider profile',
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
    'metatag_panels' => array(
      'enabled' => 1,
      'metatags' => array(
        'title' => array(
          'value' => 'User profile | [current-page:pager][site:name]',
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
    $pane->panel = 'left_sidebar';
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
    $display->panels['left_sidebar'][0] = 'new-c73e6fbd-2403-4298-8cdb-00ed617c8e5d';
    $pane = new stdClass();
    $pane->pid = 'new-d081acdc-515e-4069-b395-8c7bc7e6e3c7';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'pane-userlists-and-specials',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'd081acdc-515e-4069-b395-8c7bc7e6e3c7';
    $display->content['new-d081acdc-515e-4069-b395-8c7bc7e6e3c7'] = $pane;
    $display->panels['main_content'][0] = 'new-d081acdc-515e-4069-b395-8c7bc7e6e3c7';
    $pane = new stdClass();
    $pane->pid = 'new-d8e66878-81ac-4da6-9c30-eb876b25af49';
    $pane->panel = 'main_content';
    $pane->type = 'block';
    $pane->subtype = 'ding_user_frontend-ding-user-loan-number';
    $pane->shown = FALSE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => 'sdfsdf',
      'override_title_heading' => 'h2',
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
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['user_view_panel_context_2'] = $handler;

  return $export;
}

/**
 * Implements hook_default_page_manager_pages().
 */
function ding_user_frontend_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'user_debts';
  $page->task = 'page';
  $page->admin_title = 'User debts';
  $page->admin_description = '';
  $page->path = 'user/%user/status-debts';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'external_user',
        'settings' => NULL,
        'context' => array(
          0 => 'argument_entity_id:user_1',
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
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array(
    'type' => 'tab',
    'title' => 'Mine bøder',
    'name' => 'navigation',
    'weight' => '5',
    'parent' => array(
      'type' => 'tab',
      'title' => 'Min side',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array(
    'user' => array(
      'id' => 1,
      'identifier' => 'User: ID',
      'name' => 'entity_id:user',
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
  $handler->name = 'page_user_debts_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'user_debts';
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
    'access' => array(
      'plugins' => array(),
      'logic' => 'and',
    ),
    'metatag_panels' => array(
      'enabled' => 1,
      'metatags' => array(
        'title' => array(
          'value' => 'Debts | [current-page:pager][site:name]',
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
  $display->uuid = '7df426ee-6800-4124-b929-4391f02d19bd';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-bc35a6a8-ac4b-4d43-a9ce-5530d19e355f';
    $pane->panel = 'left_sidebar';
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
    $pane->uuid = 'bc35a6a8-ac4b-4d43-a9ce-5530d19e355f';
    $display->content['new-bc35a6a8-ac4b-4d43-a9ce-5530d19e355f'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-bc35a6a8-ac4b-4d43-a9ce-5530d19e355f';
    $pane = new stdClass();
    $pane->pid = 'new-e2022ee9-76c6-459f-a099-31e801455557';
    $pane->panel = 'main_content';
    $pane->type = 'debts';
    $pane->subtype = 'debts';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'default-account-panel-layout',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = 'e2022ee9-76c6-459f-a099-31e801455557';
    $display->content['new-e2022ee9-76c6-459f-a099-31e801455557'] = $pane;
    $display->panels['main_content'][0] = 'new-e2022ee9-76c6-459f-a099-31e801455557';
    $pane = new stdClass();
    $pane->pid = 'new-a02ec119-af14-4c5c-bdf3-f742b32486a7';
    $pane->panel = 'main_content';
    $pane->type = 'block';
    $pane->subtype = 'ding_dibs-dibs-terms-of-sale';
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
    $pane->uuid = 'a02ec119-af14-4c5c-bdf3-f742b32486a7';
    $display->content['new-a02ec119-af14-4c5c-bdf3-f742b32486a7'] = $pane;
    $display->panels['main_content'][1] = 'new-a02ec119-af14-4c5c-bdf3-f742b32486a7';
    $pane = new stdClass();
    $pane->pid = 'new-6de0581e-da74-4598-8800-395eee76efdd';
    $pane->panel = 'main_content';
    $pane->type = 'block';
    $pane->subtype = 'ding_dibs-dibs-cards-supported';
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
    $pane->uuid = '6de0581e-da74-4598-8800-395eee76efdd';
    $display->content['new-6de0581e-da74-4598-8800-395eee76efdd'] = $pane;
    $display->panels['main_content'][2] = 'new-6de0581e-da74-4598-8800-395eee76efdd';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-e2022ee9-76c6-459f-a099-31e801455557';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['user_debts'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'user_loans';
  $page->task = 'page';
  $page->admin_title = 'User loans';
  $page->admin_description = '';
  $page->path = 'user/%user/status-loans';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'external_user',
        'settings' => NULL,
        'context' => array(
          0 => 'argument_entity_id:user_1',
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
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array(
    'type' => 'tab',
    'title' => 'Mine hjemlån',
    'name' => 'navigation',
    'weight' => '3',
    'parent' => array(
      'type' => 'tab',
      'title' => 'Min side',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array(
    'user' => array(
      'id' => 1,
      'identifier' => 'User: ID',
      'name' => 'entity_id:user',
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
  $handler->name = 'page_user_loans_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'user_loans';
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
    'access' => array(
      'plugins' => array(),
      'logic' => 'and',
    ),
    'metatag_panels' => array(
      'enabled' => 1,
      'metatags' => array(
        'title' => array(
          'value' => 'Loans | [current-page:pager][site:name]',
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
  $display->uuid = '846ee609-1e6e-4c1e-ada9-7009f8684530';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-95c59944-f02d-4a0c-95c4-a7a854e6a5f3';
    $pane->panel = 'left_sidebar';
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
    $pane->uuid = '95c59944-f02d-4a0c-95c4-a7a854e6a5f3';
    $display->content['new-95c59944-f02d-4a0c-95c4-a7a854e6a5f3'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-95c59944-f02d-4a0c-95c4-a7a854e6a5f3';
    $pane = new stdClass();
    $pane->pid = 'new-375a2a68-afd4-4852-8e12-0b6af310c47a';
    $pane->panel = 'main_content';
    $pane->type = 'loans';
    $pane->subtype = 'loans';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'default-account-panel-layout',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = '375a2a68-afd4-4852-8e12-0b6af310c47a';
    $display->content['new-375a2a68-afd4-4852-8e12-0b6af310c47a'] = $pane;
    $display->panels['main_content'][0] = 'new-375a2a68-afd4-4852-8e12-0b6af310c47a';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['user_loans'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'user_reservations';
  $page->task = 'page';
  $page->admin_title = 'User reservations';
  $page->admin_description = '';
  $page->path = 'user/%user/status-reservations';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'external_user',
        'settings' => NULL,
        'context' => array(
          0 => 'argument_entity_id:user_1',
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
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array(
    'type' => 'tab',
    'title' => 'Mine reserveringer',
    'name' => 'navigation',
    'weight' => '4',
    'parent' => array(
      'type' => 'tab',
      'title' => 'Min side',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array(
    'user' => array(
      'id' => 1,
      'identifier' => 'User: ID',
      'name' => 'entity_id:user',
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
  $handler->name = 'page_user_reservations_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'user_reservations';
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
    'access' => array(
      'plugins' => array(),
      'logic' => 'and',
    ),
    'metatag_panels' => array(
      'enabled' => 1,
      'metatags' => array(
        'title' => array(
          'value' => 'Reservations | [current-page:pager][site:name]',
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
  $display->uuid = 'ccd85251-4afb-4bd6-b41a-da31a734086c';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-c142c84d-4448-41f1-b980-bf06bf2e0d38';
    $pane->panel = 'left_sidebar';
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
    $pane->uuid = 'c142c84d-4448-41f1-b980-bf06bf2e0d38';
    $display->content['new-c142c84d-4448-41f1-b980-bf06bf2e0d38'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-c142c84d-4448-41f1-b980-bf06bf2e0d38';
    $pane = new stdClass();
    $pane->pid = 'new-422dddfe-35fd-4a5b-824a-cbcc7c68a86e';
    $pane->panel = 'main_content';
    $pane->type = 'reservations';
    $pane->subtype = 'reservations';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_entity_id:user_1',
      'reservation_type_list' => array(
        'ready_for_pickup' => 'ready_for_pickup',
        'not_ready_for_pickup' => 0,
        'interlibrary_loans' => 0,
      ),
      'form_build_id' => 'form-QX87y88WafYChoueSImY7P2AU2StCbd-HxeA0_Eb3RQ',
      'form_token' => '58yM0Lyy1WXessO9Qx3vSM6g4JQYaG8E8ITfEpyCkEM',
      'form_id' => 'ding_reservation_reservations_content_type_edit_form',
      'override_title' => 1,
      'override_title_text' => 'Reservations ready for pickup',
      'reservation_title' => 'Select all',
      'reservation_empty_text' => 'There are no reservations ready for pickup.',
      'reservation_form_id' => 'ding_reservation_reservations_ready_form',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'default-account-panel-layout',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = '422dddfe-35fd-4a5b-824a-cbcc7c68a86e';
    $display->content['new-422dddfe-35fd-4a5b-824a-cbcc7c68a86e'] = $pane;
    $display->panels['main_content'][0] = 'new-422dddfe-35fd-4a5b-824a-cbcc7c68a86e';
    $pane = new stdClass();
    $pane->pid = 'new-8947b7ce-b3b4-4a9a-8068-9eac82ea9dd3';
    $pane->panel = 'main_content';
    $pane->type = 'reservations';
    $pane->subtype = 'reservations';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_entity_id:user_1',
      'reservation_type_list' => array(
        'not_ready_for_pickup' => 'not_ready_for_pickup',
        'interlibrary_loans' => 'interlibrary_loans',
        'ready_for_pickup' => 0,
      ),
      'form_build_id' => 'form-YjzqJCj7L0VlsFICUhBPU4plnz6GmBW4_ygeTOAg23o',
      'form_token' => '58yM0Lyy1WXessO9Qx3vSM6g4JQYaG8E8ITfEpyCkEM',
      'form_id' => 'ding_reservation_reservations_content_type_edit_form',
      'override_title' => 1,
      'override_title_text' => 'Reservations',
      'reservation_title' => 'Select all',
      'reservation_empty_text' => 'There are no reservations.',
      'reservation_form_id' => 'ding_reservation_reservations_notready_form',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'default-account-panel-layout',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = '';
    $pane->uuid = '8947b7ce-b3b4-4a9a-8068-9eac82ea9dd3';
    $display->content['new-8947b7ce-b3b4-4a9a-8068-9eac82ea9dd3'] = $pane;
    $display->panels['main_content'][1] = 'new-8947b7ce-b3b4-4a9a-8068-9eac82ea9dd3';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-422dddfe-35fd-4a5b-824a-cbcc7c68a86e';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['user_reservations'] = $page;

  return $pages;

}
