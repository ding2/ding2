<?php
/**
 * @file
 * ding_app_content_rss.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ding_app_content_rss_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ding_app_content_event_rss';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Ding App Content Event RSS';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'rules';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Content author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Relationship: Flags: mobile_app */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'mobile_app';
  $handler->display->display_options['relationships']['flag_content_rel']['user_scope'] = 'any';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'r';
  /* Field: Content: Promoted to front page status */
  $handler->display->display_options['fields']['promote']['id'] = 'promote';
  $handler->display->display_options['fields']['promote']['table'] = 'node';
  $handler->display->display_options['fields']['promote']['field'] = 'promote';
  $handler->display->display_options['fields']['promote']['label'] = '';
  $handler->display->display_options['fields']['promote']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['promote']['type'] = 'true-false';
  $handler->display->display_options['fields']['promote']['not'] = 0;
  /* Field: Content: Sticky status */
  $handler->display->display_options['fields']['sticky']['id'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['table'] = 'node';
  $handler->display->display_options['fields']['sticky']['field'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['label'] = '';
  $handler->display->display_options['fields']['sticky']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['sticky']['type'] = 'true-false';
  $handler->display->display_options['fields']['sticky']['not'] = 0;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Field: Content: Lead */
  $handler->display->display_options['fields']['field_ding_event_lead']['id'] = 'field_ding_event_lead';
  $handler->display->display_options['fields']['field_ding_event_lead']['table'] = 'field_data_field_ding_event_lead';
  $handler->display->display_options['fields']['field_ding_event_lead']['field'] = 'field_ding_event_lead';
  $handler->display->display_options['fields']['field_ding_event_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_lead']['type'] = 'text_plain';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_ding_event_body']['id'] = 'field_ding_event_body';
  $handler->display->display_options['fields']['field_ding_event_body']['table'] = 'field_data_field_ding_event_body';
  $handler->display->display_options['fields']['field_ding_event_body']['field'] = 'field_ding_event_body';
  $handler->display->display_options['fields']['field_ding_event_body']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_body']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_ding_event_body']['alter']['preserve_tags'] = '<a><b><em><u><i><li><ul><ol><h2><h3><strong><p><br/><br><br />';
  $handler->display->display_options['fields']['field_ding_event_body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_body']['element_default_classes'] = FALSE;
  /* Field: Indhold: List image (content) */
  $handler->display->display_options['fields']['field_ding_event_list_image']['id'] = 'field_ding_event_list_image';
  $handler->display->display_options['fields']['field_ding_event_list_image']['table'] = 'field_data_field_ding_event_list_image';
  $handler->display->display_options['fields']['field_ding_event_list_image']['field'] = 'field_ding_event_list_image';
  $handler->display->display_options['fields']['field_ding_event_list_image']['ui_name'] = 'Indhold: List image (content)';
  $handler->display->display_options['fields']['field_ding_event_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_list_image']['alter']['text'] = '[field_ding_event_list_image]';
  $handler->display->display_options['fields']['field_ding_event_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_list_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_event_list_image']['type'] = 'media_content';
  $handler->display->display_options['fields']['field_ding_event_list_image']['settings'] = array(
    'image_style' => '',
    'group_multiple_values' => 0,
    'medium' => 'image',
    'expression' => '',
    'generate_hash' => 1,
    'hash_algo' => 'md5',
  );
  /* Field: Indhold: List image (thumbnail) */
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['id'] = 'field_ding_event_list_image_1';
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['table'] = 'field_data_field_ding_event_list_image';
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['field'] = 'field_ding_event_list_image';
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['ui_name'] = 'Indhold: List image (thumbnail)';
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['type'] = 'media_thumbnail';
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['settings'] = array(
    'image_style' => 'medium',
  );
  /* Field: Ding App Content RSS: Library ID */
  $handler->display->display_options['fields']['ding_app_content_rss_handler_library_id']['id'] = 'ding_app_content_rss_handler_library_id';
  $handler->display->display_options['fields']['ding_app_content_rss_handler_library_id']['table'] = 'ding_app_content_rss';
  $handler->display->display_options['fields']['ding_app_content_rss_handler_library_id']['field'] = 'ding_app_content_rss_handler_library_id';
  $handler->display->display_options['fields']['ding_app_content_rss_handler_library_id']['label'] = '';
  $handler->display->display_options['fields']['ding_app_content_rss_handler_library_id']['element_label_colon'] = FALSE;
  /* Field: Event - Start Date */
  $handler->display->display_options['fields']['field_ding_event_date']['id'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['ui_name'] = 'Event - Start Date';
  $handler->display->display_options['fields']['field_ding_event_date']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date']['type'] = 'ding_app_content_rss_date_time';
  $handler->display->display_options['fields']['field_ding_event_date']['settings'] = array(
    'fromto' => 'value',
  );
  /* Field: Event - End Date */
  $handler->display->display_options['fields']['field_ding_event_date_1']['id'] = 'field_ding_event_date_1';
  $handler->display->display_options['fields']['field_ding_event_date_1']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['ui_name'] = 'Event - End Date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_date_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date_1']['type'] = 'ding_app_content_rss_date_time';
  $handler->display->display_options['fields']['field_ding_event_date_1']['settings'] = array(
    'fromto' => 'value2',
  );
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_ding_event_location']['id'] = 'field_ding_event_location';
  $handler->display->display_options['fields']['field_ding_event_location']['table'] = 'field_data_field_ding_event_location';
  $handler->display->display_options['fields']['field_ding_event_location']['field'] = 'field_ding_event_location';
  $handler->display->display_options['fields']['field_ding_event_location']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_location']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_ding_event_location']['type'] = 'ding_app_content_rss_location';
  $handler->display->display_options['fields']['field_ding_event_location']['settings'] = array(
    'use_widget_handlers' => 0,
    'format_handlers' => array(),
  );
  /* Field: Content: Price */
  $handler->display->display_options['fields']['field_ding_event_price']['id'] = 'field_ding_event_price';
  $handler->display->display_options['fields']['field_ding_event_price']['table'] = 'field_data_field_ding_event_price';
  $handler->display->display_options['fields']['field_ding_event_price']['field'] = 'field_ding_event_price';
  $handler->display->display_options['fields']['field_ding_event_price']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_price']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_price']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 0,
  );
  /* Field: Content: Book ticket/Participate in event */
  $handler->display->display_options['fields']['field_ding_event_ticket_link']['id'] = 'field_ding_event_ticket_link';
  $handler->display->display_options['fields']['field_ding_event_ticket_link']['table'] = 'field_data_field_ding_event_ticket_link';
  $handler->display->display_options['fields']['field_ding_event_ticket_link']['field'] = 'field_ding_event_ticket_link';
  $handler->display->display_options['fields']['field_ding_event_ticket_link']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_ticket_link']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_event_ticket_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_ticket_link']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_ding_event_ticket_link']['type'] = 'link_plain';
  /* Sort criterion: Content: Date -  start date (field_ding_event_date) */
  $handler->display->display_options['sorts']['field_ding_event_date_value']['id'] = 'field_ding_event_date_value';
  $handler->display->display_options['sorts']['field_ding_event_date_value']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['sorts']['field_ding_event_date_value']['field'] = 'field_ding_event_date_value';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'OR',
  );
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_event' => 'ding_event',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Published status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 2;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Date -  start date (field_ding_event_date) */
  $handler->display->display_options['filters']['field_ding_event_date_value']['id'] = 'field_ding_event_date_value';
  $handler->display->display_options['filters']['field_ding_event_date_value']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['filters']['field_ding_event_date_value']['field'] = 'field_ding_event_date_value';
  $handler->display->display_options['filters']['field_ding_event_date_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_ding_event_date_value']['default_date'] = 'now';
  /* Filter criterion: Content: Date -  start date (field_ding_event_date) */
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['id'] = 'field_ding_event_date_value_1';
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['field'] = 'field_ding_event_date_value';
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['operator'] = '<=';
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['default_date'] = '+180 day';

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'feed');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'rss_fields';
  $handler->display->display_options['style_options']['channel'] = array(
    'core' => array(
      'views_rss_core' => array(
        'description' => '',
        'language' => 'da',
        'category' => '',
        'image' => '',
        'copyright' => '',
        'managingEditor' => '',
        'webMaster' => '',
        'generator' => '',
        'docs' => '',
        'cloud' => '',
        'ttl' => '',
        'skipHours' => '',
        'skipDays' => '',
      ),
    ),
  );
  $handler->display->display_options['style_options']['item'] = array(
    'core' => array(
      'views_rss_core' => array(
        'title' => 'title',
        'link' => '',
        'description' => 'field_ding_event_body',
        'author' => 'name',
        'category' => '',
        'comments' => '',
        'enclosure' => '',
        'guid' => 'nid',
        'pubDate' => 'created',
      ),
    ),
    'media' => array(
      'views_rss_media' => array(
        'content' => 'field_ding_event_list_image',
        'title' => '',
        'description' => '',
        'keywords' => '',
        'thumbnail' => 'field_ding_event_list_image_1',
        'category' => '',
      ),
    ),
    'content-rss' => array(
      'ding_app_content_rss' => array(
        'subheadline' => 'field_ding_event_lead',
        'arrangement-starttime' => 'field_ding_event_date',
        'arrangement-endtime' => 'field_ding_event_date_1',
        'display-starttime' => '',
        'display-endtime' => '',
        'arrangement-location' => 'field_ding_event_location',
        'arrangement-price' => 'field_ding_event_price',
        'resources' => 'nid',
        'library-id' => 'ding_app_content_rss_handler_library_id',
        'booking-url' => 'field_ding_event_ticket_link',
        'promoted' => 'promote',
        'sticky' => '',
        'place_room' => 'field_ding_event_place',
        'organizers' => 'field_ding_event_organizers',
      ),
    ),
  );
  $handler->display->display_options['style_options']['feed_settings'] = array(
    'absolute_paths' => 1,
    'feed_in_links' => 0,
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'r';
  /* Field: Content: Promoted to front page status */
  $handler->display->display_options['fields']['promote']['id'] = 'promote';
  $handler->display->display_options['fields']['promote']['table'] = 'node';
  $handler->display->display_options['fields']['promote']['field'] = 'promote';
  $handler->display->display_options['fields']['promote']['label'] = '';
  $handler->display->display_options['fields']['promote']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['promote']['type'] = 'true-false';
  $handler->display->display_options['fields']['promote']['not'] = 0;
  /* Field: Content: Sticky status */
  $handler->display->display_options['fields']['sticky']['id'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['table'] = 'node';
  $handler->display->display_options['fields']['sticky']['field'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['label'] = '';
  $handler->display->display_options['fields']['sticky']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['sticky']['type'] = 'true-false';
  $handler->display->display_options['fields']['sticky']['not'] = 0;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Field: Content: Lead */
  $handler->display->display_options['fields']['field_ding_event_lead']['id'] = 'field_ding_event_lead';
  $handler->display->display_options['fields']['field_ding_event_lead']['table'] = 'field_data_field_ding_event_lead';
  $handler->display->display_options['fields']['field_ding_event_lead']['field'] = 'field_ding_event_lead';
  $handler->display->display_options['fields']['field_ding_event_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_lead']['type'] = 'text_plain';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_ding_event_body']['id'] = 'field_ding_event_body';
  $handler->display->display_options['fields']['field_ding_event_body']['table'] = 'field_data_field_ding_event_body';
  $handler->display->display_options['fields']['field_ding_event_body']['field'] = 'field_ding_event_body';
  $handler->display->display_options['fields']['field_ding_event_body']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_body']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_ding_event_body']['alter']['preserve_tags'] = '<a><b><em><u><i><li><ul><ol><h2><h3><strong><p><br/><br><br />';
  $handler->display->display_options['fields']['field_ding_event_body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_body']['element_default_classes'] = FALSE;
  /* Field: Indhold: List image (content) */
  $handler->display->display_options['fields']['field_ding_event_list_image']['id'] = 'field_ding_event_list_image';
  $handler->display->display_options['fields']['field_ding_event_list_image']['table'] = 'field_data_field_ding_event_list_image';
  $handler->display->display_options['fields']['field_ding_event_list_image']['field'] = 'field_ding_event_list_image';
  $handler->display->display_options['fields']['field_ding_event_list_image']['ui_name'] = 'Indhold: List image (content)';
  $handler->display->display_options['fields']['field_ding_event_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_list_image']['alter']['text'] = '[field_ding_event_list_image]';
  $handler->display->display_options['fields']['field_ding_event_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_list_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_event_list_image']['type'] = 'media_content';
  $handler->display->display_options['fields']['field_ding_event_list_image']['settings'] = array(
    'image_style' => '',
    'group_multiple_values' => 0,
    'medium' => 'image',
    'expression' => '',
    'generate_hash' => 1,
    'hash_algo' => 'md5',
  );
  /* Field: Indhold: List image (thumbnail) */
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['id'] = 'field_ding_event_list_image_1';
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['table'] = 'field_data_field_ding_event_list_image';
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['field'] = 'field_ding_event_list_image';
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['ui_name'] = 'Indhold: List image (thumbnail)';
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['type'] = 'media_thumbnail';
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['settings'] = array(
    'image_style' => 'medium',
  );
  /* Field: Ding App Content RSS: Library ID */
  $handler->display->display_options['fields']['ding_app_content_rss_handler_library_id']['id'] = 'ding_app_content_rss_handler_library_id';
  $handler->display->display_options['fields']['ding_app_content_rss_handler_library_id']['table'] = 'ding_app_content_rss';
  $handler->display->display_options['fields']['ding_app_content_rss_handler_library_id']['field'] = 'ding_app_content_rss_handler_library_id';
  $handler->display->display_options['fields']['ding_app_content_rss_handler_library_id']['label'] = '';
  $handler->display->display_options['fields']['ding_app_content_rss_handler_library_id']['element_label_colon'] = FALSE;
  /* Field: Event - Start Date */
  $handler->display->display_options['fields']['field_ding_event_date']['id'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['ui_name'] = 'Event - Start Date';
  $handler->display->display_options['fields']['field_ding_event_date']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date']['type'] = 'ding_app_content_rss_date_time';
  $handler->display->display_options['fields']['field_ding_event_date']['settings'] = array(
    'fromto' => 'value',
  );
  /* Field: Event - End Date */
  $handler->display->display_options['fields']['field_ding_event_date_1']['id'] = 'field_ding_event_date_1';
  $handler->display->display_options['fields']['field_ding_event_date_1']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['ui_name'] = 'Event - End Date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_date_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date_1']['type'] = 'ding_app_content_rss_date_time';
  $handler->display->display_options['fields']['field_ding_event_date_1']['settings'] = array(
    'fromto' => 'value2',
  );
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_ding_event_location']['id'] = 'field_ding_event_location';
  $handler->display->display_options['fields']['field_ding_event_location']['table'] = 'field_data_field_ding_event_location';
  $handler->display->display_options['fields']['field_ding_event_location']['field'] = 'field_ding_event_location';
  $handler->display->display_options['fields']['field_ding_event_location']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_location']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_ding_event_location']['type'] = 'ding_app_content_rss_location';
  $handler->display->display_options['fields']['field_ding_event_location']['settings'] = array(
    'use_widget_handlers' => 0,
    'format_handlers' => array(),
  );
  /* Field: Content: Price */
  $handler->display->display_options['fields']['field_ding_event_price']['id'] = 'field_ding_event_price';
  $handler->display->display_options['fields']['field_ding_event_price']['table'] = 'field_data_field_ding_event_price';
  $handler->display->display_options['fields']['field_ding_event_price']['field'] = 'field_ding_event_price';
  $handler->display->display_options['fields']['field_ding_event_price']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_price']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_price']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 0,
  );
  /* Field: Content: Book ticket/Participate in event */
  $handler->display->display_options['fields']['field_ding_event_ticket_link']['id'] = 'field_ding_event_ticket_link';
  $handler->display->display_options['fields']['field_ding_event_ticket_link']['table'] = 'field_data_field_ding_event_ticket_link';
  $handler->display->display_options['fields']['field_ding_event_ticket_link']['field'] = 'field_ding_event_ticket_link';
  $handler->display->display_options['fields']['field_ding_event_ticket_link']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_ticket_link']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_event_ticket_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_ticket_link']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_ding_event_ticket_link']['type'] = 'link_plain';
  /* Field: Content: Place / Room */
  $handler->display->display_options['fields']['field_ding_event_place']['id'] = 'field_ding_event_place';
  $handler->display->display_options['fields']['field_ding_event_place']['table'] = 'field_data_field_ding_event_place';
  $handler->display->display_options['fields']['field_ding_event_place']['field'] = 'field_ding_event_place';
  $handler->display->display_options['fields']['field_ding_event_place']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_place']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_place']['type'] = 'text_plain';
  /* Field: Content: Organizer */
  $handler->display->display_options['fields']['field_ding_event_organizers']['id'] = 'field_ding_event_organizers';
  $handler->display->display_options['fields']['field_ding_event_organizers']['table'] = 'field_data_field_ding_event_organizers';
  $handler->display->display_options['fields']['field_ding_event_organizers']['field'] = 'field_ding_event_organizers';
  $handler->display->display_options['fields']['field_ding_event_organizers']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_organizers']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_organizers']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_ding_event_organizers']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Sticky status */
  $handler->display->display_options['sorts']['sticky']['id'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['table'] = 'node';
  $handler->display->display_options['sorts']['sticky']['field'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['order'] = 'DESC';
  /* Sort criterion: Content: Date -  start date (field_ding_event_date) */
  $handler->display->display_options['sorts']['field_ding_event_date_value']['id'] = 'field_ding_event_date_value';
  $handler->display->display_options['sorts']['field_ding_event_date_value']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['sorts']['field_ding_event_date_value']['field'] = 'field_ding_event_date_value';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['operator'] = 'OR';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'AND',
  );
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_event' => 'ding_event',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Date -  start date (field_ding_event_date) */
  $handler->display->display_options['filters']['field_ding_event_date_value']['id'] = 'field_ding_event_date_value';
  $handler->display->display_options['filters']['field_ding_event_date_value']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['filters']['field_ding_event_date_value']['field'] = 'field_ding_event_date_value';
  $handler->display->display_options['filters']['field_ding_event_date_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_ding_event_date_value']['group'] = 1;
  $handler->display->display_options['filters']['field_ding_event_date_value']['default_date'] = 'now';
  /* Filter criterion: Content: Date -  start date (field_ding_event_date) */
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['id'] = 'field_ding_event_date_value_1';
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['field'] = 'field_ding_event_date_value';
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['operator'] = '<=';
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['group'] = 1;
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['default_date'] = '+180 day';
  /* Filter criterion: Content: Published status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'ding_event' => 'ding_event',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 2;
  /* Filter criterion: Content: Event list filter (field_ding_event_list_filter) */
  $handler->display->display_options['filters']['field_ding_event_list_filter_value_1']['id'] = 'field_ding_event_list_filter_value_1';
  $handler->display->display_options['filters']['field_ding_event_list_filter_value_1']['table'] = 'field_data_field_ding_event_list_filter';
  $handler->display->display_options['filters']['field_ding_event_list_filter_value_1']['field'] = 'field_ding_event_list_filter_value';
  $handler->display->display_options['filters']['field_ding_event_list_filter_value_1']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_ding_event_list_filter_value_1']['group'] = 2;
  /* Filter criterion: Content: Event list filter (field_ding_event_list_filter) */
  $handler->display->display_options['filters']['field_ding_event_list_filter_value']['id'] = 'field_ding_event_list_filter_value';
  $handler->display->display_options['filters']['field_ding_event_list_filter_value']['table'] = 'field_data_field_ding_event_list_filter';
  $handler->display->display_options['filters']['field_ding_event_list_filter_value']['field'] = 'field_ding_event_list_filter_value';
  $handler->display->display_options['filters']['field_ding_event_list_filter_value']['value'] = array(
    'show_all' => 'show_all',
  );
  $handler->display->display_options['filters']['field_ding_event_list_filter_value']['group'] = 2;
  /* Filter criterion: Content: Date - end date (field_ding_event_date:value2) */
  $handler->display->display_options['filters']['field_ding_event_date_value2']['id'] = 'field_ding_event_date_value2';
  $handler->display->display_options['filters']['field_ding_event_date_value2']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['filters']['field_ding_event_date_value2']['field'] = 'field_ding_event_date_value2';
  $handler->display->display_options['filters']['field_ding_event_date_value2']['operator'] = '>=';
  $handler->display->display_options['filters']['field_ding_event_date_value2']['group'] = 2;
  $handler->display->display_options['filters']['field_ding_event_date_value2']['default_date'] = 'now';
  /* Filter criterion: Content: Date -  start date (field_ding_event_date) */
  $handler->display->display_options['filters']['field_ding_event_date_value_2']['id'] = 'field_ding_event_date_value_2';
  $handler->display->display_options['filters']['field_ding_event_date_value_2']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['filters']['field_ding_event_date_value_2']['field'] = 'field_ding_event_date_value';
  $handler->display->display_options['filters']['field_ding_event_date_value_2']['operator'] = '<=';
  $handler->display->display_options['filters']['field_ding_event_date_value_2']['group'] = 2;
  $handler->display->display_options['filters']['field_ding_event_date_value_2']['default_date'] = '+180 day';
  /* Filter criterion: Content: Published status */
  $handler->display->display_options['filters']['status_1']['id'] = 'status_1';
  $handler->display->display_options['filters']['status_1']['table'] = 'node';
  $handler->display->display_options['filters']['status_1']['field'] = 'status';
  $handler->display->display_options['filters']['status_1']['value'] = '1';
  $handler->display->display_options['filters']['status_1']['group'] = 2;
  $handler->display->display_options['path'] = 'ding-redia-rss/event';
  $translatables['ding_app_content_event_rss'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('author'),
    t('flag'),
    t('[field_ding_event_list_image]'),
    t('Feed'),
  );
  $export['ding_app_content_event_rss'] = $view;

  $view = new view();
  $view->name = 'ding_app_content_news_rss';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Ding App Content News RSS';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'rules';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Content author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Relationship: Flags: mobile_app */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'mobile_app';
  $handler->display->display_options['relationships']['flag_content_rel']['user_scope'] = 'any';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'r';
  /* Field: Content: Promoted to front page status */
  $handler->display->display_options['fields']['promote']['id'] = 'promote';
  $handler->display->display_options['fields']['promote']['table'] = 'node';
  $handler->display->display_options['fields']['promote']['field'] = 'promote';
  $handler->display->display_options['fields']['promote']['label'] = '';
  $handler->display->display_options['fields']['promote']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['promote']['type'] = 'true-false';
  $handler->display->display_options['fields']['promote']['not'] = 0;
  /* Field: Content: Sticky status */
  $handler->display->display_options['fields']['sticky']['id'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['table'] = 'node';
  $handler->display->display_options['fields']['sticky']['field'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['label'] = '';
  $handler->display->display_options['fields']['sticky']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['sticky']['type'] = 'true-false';
  $handler->display->display_options['fields']['sticky']['not'] = 0;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Field: Content: Lead */
  $handler->display->display_options['fields']['field_ding_news_lead']['id'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['table'] = 'field_data_field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['field'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_lead']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_lead']['type'] = 'text_plain';
  /* Field: Content: Paragraphs */
  $handler->display->display_options['fields']['field_ding_news_paragraphs']['id'] = 'field_ding_news_paragraphs';
  $handler->display->display_options['fields']['field_ding_news_paragraphs']['table'] = 'field_data_field_ding_news_paragraphs';
  $handler->display->display_options['fields']['field_ding_news_paragraphs']['field'] = 'field_ding_news_paragraphs';
  $handler->display->display_options['fields']['field_ding_news_paragraphs']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_paragraphs']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_paragraphs']['settings'] = array(
    'view_mode' => 'full',
  );
  $handler->display->display_options['fields']['field_ding_news_paragraphs']['delta_offset'] = '0';
  /* Field: Indhold: List image (content) */
  $handler->display->display_options['fields']['field_ding_news_list_image']['id'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['table'] = 'field_data_field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['field'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['ui_name'] = 'Indhold: List image (content)';
  $handler->display->display_options['fields']['field_ding_news_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['text'] = '[field_ding_news_list_image]';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_news_list_image']['type'] = 'media_content';
  $handler->display->display_options['fields']['field_ding_news_list_image']['settings'] = array(
    'image_style' => '',
    'group_multiple_values' => 0,
    'medium' => 'image',
    'expression' => '',
    'generate_hash' => 1,
    'hash_algo' => 'md5',
  );
  /* Field: Indhold: List image (thumbnail) */
  $handler->display->display_options['fields']['field_ding_news_list_image_1']['id'] = 'field_ding_news_list_image_1';
  $handler->display->display_options['fields']['field_ding_news_list_image_1']['table'] = 'field_data_field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image_1']['field'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image_1']['ui_name'] = 'Indhold: List image (thumbnail)';
  $handler->display->display_options['fields']['field_ding_news_list_image_1']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_list_image_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_news_list_image_1']['type'] = 'media_thumbnail';
  $handler->display->display_options['fields']['field_ding_news_list_image_1']['settings'] = array(
    'image_style' => 'medium',
  );
  /* Field: Ding App Content RSS: Library ID */
  $handler->display->display_options['fields']['ding_app_content_rss_handler_library_id']['id'] = 'ding_app_content_rss_handler_library_id';
  $handler->display->display_options['fields']['ding_app_content_rss_handler_library_id']['table'] = 'ding_app_content_rss';
  $handler->display->display_options['fields']['ding_app_content_rss_handler_library_id']['field'] = 'ding_app_content_rss_handler_library_id';
  $handler->display->display_options['fields']['ding_app_content_rss_handler_library_id']['label'] = '';
  $handler->display->display_options['fields']['ding_app_content_rss_handler_library_id']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'OR',
  );
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_news' => 'ding_news',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Published status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 2;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'feed');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'rss_fields';
  $handler->display->display_options['style_options']['channel'] = array(
    'core' => array(
      'views_rss_core' => array(
        'description' => '',
        'language' => 'da',
        'category' => '',
        'image' => '',
        'copyright' => '',
        'managingEditor' => '',
        'webMaster' => '',
        'generator' => '',
        'docs' => '',
        'cloud' => '',
        'ttl' => '',
        'skipHours' => '',
        'skipDays' => '',
      ),
    ),
  );
  $handler->display->display_options['style_options']['item'] = array(
    'core' => array(
      'views_rss_core' => array(
        'title' => 'title',
        'link' => '',
        'description' => 'field_ding_news_paragraphs',
        'author' => 'name',
        'category' => '',
        'comments' => '',
        'enclosure' => '',
        'guid' => 'nid',
        'pubDate' => 'created',
      ),
    ),
    'media' => array(
      'views_rss_media' => array(
        'content' => 'field_ding_news_list_image',
        'title' => '',
        'description' => '',
        'keywords' => '',
        'thumbnail' => 'field_ding_news_list_image_1',
        'category' => '',
      ),
    ),
    'content-rss' => array(
      'ding_app_content_rss' => array(
        'subheadline' => 'field_ding_news_lead',
        'arrangement-starttime' => '',
        'arrangement-endtime' => '',
        'display-starttime' => '',
        'display-endtime' => '',
        'arrangement-location' => '',
        'arrangement-price' => '',
        'resources' => 'nid',
        'library-id' => 'ding_app_content_rss_handler_library_id',
        'booking-url' => '',
        'promoted' => 'promote',
        'sticky' => '',
        'place_room' => '',
        'organizers' => '',
      ),
    ),
  );
  $handler->display->display_options['style_options']['feed_settings'] = array(
    'absolute_paths' => 1,
    'feed_in_links' => 0,
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Sticky status */
  $handler->display->display_options['sorts']['sticky']['id'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['table'] = 'node';
  $handler->display->display_options['sorts']['sticky']['field'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['order'] = 'DESC';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['path'] = 'ding-redia-rss/news';
  $translatables['ding_app_content_news_rss'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('author'),
    t('flag'),
    t('[field_ding_news_list_image]'),
    t('Feed'),
  );
  $export['ding_app_content_news_rss'] = $view;

  return $export;
}
