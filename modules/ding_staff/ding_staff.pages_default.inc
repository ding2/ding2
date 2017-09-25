<?php
/**
 * @file
 * ding_staff.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function ding_staff_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'user_view_panel_context_3';
  $handler->task = 'user_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -30;
  $handler->conf = array(
    'title' => 'Staff profile',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'has_staff_role',
          'settings' => NULL,
          'context' => array(
            0 => 'argument_entity_id:user_1',
          ),
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'ding2_site_template';
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
      'branding' => NULL,
      'header' => NULL,
      'navigation' => NULL,
      'content' => NULL,
      'footer' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Account';
  $display->uuid = '7724df15-c005-4221-8048-5fc88fead69b';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-c4b06a7e-01a0-4551-803f-1b654ae9ffbb';
    $pane->panel = 'content';
    $pane->type = 'staff_profile';
    $pane->subtype = 'staff_profile';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_entity_id:user_1',
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
    $pane->uuid = 'c4b06a7e-01a0-4551-803f-1b654ae9ffbb';
    $display->content['new-c4b06a7e-01a0-4551-803f-1b654ae9ffbb'] = $pane;
    $display->panels['content'][0] = 'new-c4b06a7e-01a0-4551-803f-1b654ae9ffbb';
    $pane = new stdClass();
    $pane->pid = 'new-8de0095e-70ec-425c-ba76-a07a2a7dbd58';
    $pane->panel = 'content';
    $pane->type = 'lists';
    $pane->subtype = 'lists';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
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
    );
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '8de0095e-70ec-425c-ba76-a07a2a7dbd58';
    $display->content['new-8de0095e-70ec-425c-ba76-a07a2a7dbd58'] = $pane;
    $display->panels['content'][1] = 'new-8de0095e-70ec-425c-ba76-a07a2a7dbd58';
    $pane = new stdClass();
    $pane->pid = 'new-8de3be43-6942-4dca-a179-edf434dc63d9';
    $pane->panel = 'content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_news-ding_news_list_user';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:user_1',
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '8de3be43-6942-4dca-a179-edf434dc63d9';
    $display->content['new-8de3be43-6942-4dca-a179-edf434dc63d9'] = $pane;
    $display->panels['content'][2] = 'new-8de3be43-6942-4dca-a179-edf434dc63d9';
    $pane = new stdClass();
    $pane->pid = 'new-cf6940f2-a95b-493c-9ed3-37c212957a98';
    $pane->panel = 'content';
    $pane->type = 'views_panes';
    $pane->subtype = 'public_lists-user';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:user_1',
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
    $pane->uuid = 'cf6940f2-a95b-493c-9ed3-37c212957a98';
    $display->content['new-cf6940f2-a95b-493c-9ed3-37c212957a98'] = $pane;
    $display->panels['content'][3] = 'new-cf6940f2-a95b-493c-9ed3-37c212957a98';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-c4b06a7e-01a0-4551-803f-1b654ae9ffbb';
  $handler->conf['display'] = $display;
  $export['user_view_panel_context_3'] = $handler;

  return $export;
}

/**
 * Implements hook_default_page_manager_pages().
 */
function ding_staff_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'ding_staff_library';
  $page->task = 'page';
  $page->admin_title = 'Ding staff library';
  $page->admin_description = '';
  $page->path = 'bibliotek/%slug/personale';
  $page->access = array(
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
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_ding_staff_library_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'ding_staff_library';
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
    'metatag_panels' => array(
      'enabled' => 1,
      'metatags' => array(
        'title' => array(
          'value' => '%slug:title | Departments and Staff | [current-page:pager][site:name]',
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
  $display->title = 'Staff at: %node:title';
  $display->uuid = 'd250e77c-be00-4883-b131-50c8668105cb';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-c33cb008-3da8-49dc-a14e-e02e9c612e72';
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
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'c33cb008-3da8-49dc-a14e-e02e9c612e72';
    $display->content['new-c33cb008-3da8-49dc-a14e-e02e9c612e72'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-c33cb008-3da8-49dc-a14e-e02e9c612e72';
    $pane = new stdClass();
    $pane->pid = 'new-3443002f-f33c-470f-a71f-060df3d51f32';
    $pane->panel = 'left_sidebar';
    $pane->type = 'library_list';
    $pane->subtype = 'library_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'slug' => 'personale',
      'context' => array(
        0 => 'empty',
        1 => 'argument_slug_1',
      ),
      'override_title' => 0,
      'override_title_text' => '',
      'hide_default' => 1,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '3443002f-f33c-470f-a71f-060df3d51f32';
    $display->content['new-3443002f-f33c-470f-a71f-060df3d51f32'] = $pane;
    $display->panels['left_sidebar'][1] = 'new-3443002f-f33c-470f-a71f-060df3d51f32';
    $pane = new stdClass();
    $pane->pid = 'new-6171a17a-4789-4aac-86de-eb9c76dee003';
    $pane->panel = 'main_content';
    $pane->type = 'views_panes';
    $pane->subtype = 'ding_staff-ding_staff_library_departments';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '%slug:title : departments & staff',
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
    $pane->uuid = '6171a17a-4789-4aac-86de-eb9c76dee003';
    $display->content['new-6171a17a-4789-4aac-86de-eb9c76dee003'] = $pane;
    $display->panels['main_content'][0] = 'new-6171a17a-4789-4aac-86de-eb9c76dee003';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-6171a17a-4789-4aac-86de-eb9c76dee003';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['ding_staff_library'] = $page;

  return $pages;

}
