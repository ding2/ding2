<?php
/**
 * @file
 * ding_redia_rss.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ding_redia_rss_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ding_redia_event_rss';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Ding Redia Event RSS';
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
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
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
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Event - Start Date */
  $handler->display->display_options['fields']['field_ding_event_date']['id'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['ui_name'] = 'Event - Start Date';
  $handler->display->display_options['fields']['field_ding_event_date']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date']['type'] = 'ding_redia_rss_date_time';
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
  $handler->display->display_options['fields']['field_ding_event_date_1']['type'] = 'ding_redia_rss_date_time';
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
  $handler->display->display_options['fields']['field_ding_event_location']['type'] = 'ding_redia_rss_location';
  $handler->display->display_options['fields']['field_ding_event_location']['settings'] = array(
    'use_widget_handlers' => 0,
    'format_handlers' => array(),
  );
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_ding_event_body']['id'] = 'field_ding_event_body';
  $handler->display->display_options['fields']['field_ding_event_body']['table'] = 'field_data_field_ding_event_body';
  $handler->display->display_options['fields']['field_ding_event_body']['field'] = 'field_ding_event_body';
  $handler->display->display_options['fields']['field_ding_event_body']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_body']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_ding_event_body']['alter']['preserve_tags'] = '<a><b><em><u><i><li><ul><ol><h2><h3><strong><p><br/>';
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
  /* Field: Scheduler: Publish on */
  $handler->display->display_options['fields']['publish_on']['id'] = 'publish_on';
  $handler->display->display_options['fields']['publish_on']['table'] = 'scheduler';
  $handler->display->display_options['fields']['publish_on']['field'] = 'publish_on';
  $handler->display->display_options['fields']['publish_on']['label'] = '';
  $handler->display->display_options['fields']['publish_on']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['publish_on']['date_format'] = 'custom';
  $handler->display->display_options['fields']['publish_on']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['publish_on']['timezone'] = 'UTC';
  /* Field: Scheduler: Unpublish on */
  $handler->display->display_options['fields']['unpublish_on']['id'] = 'unpublish_on';
  $handler->display->display_options['fields']['unpublish_on']['table'] = 'scheduler';
  $handler->display->display_options['fields']['unpublish_on']['field'] = 'unpublish_on';
  $handler->display->display_options['fields']['unpublish_on']['label'] = '';
  $handler->display->display_options['fields']['unpublish_on']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['unpublish_on']['date_format'] = 'custom';
  $handler->display->display_options['fields']['unpublish_on']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['unpublish_on']['timezone'] = 'UTC';
  /* Sort criterion: Content: Updated date */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'node';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
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
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 2;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Scheduler: Publish on */
  $handler->display->display_options['filters']['publish_on']['id'] = 'publish_on';
  $handler->display->display_options['filters']['publish_on']['table'] = 'scheduler';
  $handler->display->display_options['filters']['publish_on']['field'] = 'publish_on';
  $handler->display->display_options['filters']['publish_on']['operator'] = 'not empty';
  $handler->display->display_options['filters']['publish_on']['group'] = 2;

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
    'redia-rss' => array(
      'ding_redia_rss' => array(
        'subheadline' => 'field_ding_event_lead',
        'arrangement-starttime' => 'field_ding_event_date',
        'arrangement-endtime' => 'field_ding_event_date_1',
        'display-starttime' => 'publish_on',
        'display-endtime' => 'unpublish_on',
        'arrangement-location' => 'field_ding_event_location',
        'arrangement-price' => 'field_ding_event_price',
        'resources' => 'nid',
      ),
    ),
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
  );
  $handler->display->display_options['style_options']['feed_settings'] = array(
    'absolute_paths' => 1,
    'feed_in_links' => 0,
  );
  $handler->display->display_options['path'] = 'ding-redia-rss/event';

  /* Display: App Feed */
  $handler = $view->new_display('feed', 'App Feed', 'feed_app');
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
    'redia-rss' => array(
      'ding_redia_rss' => array(
        'subheadline' => 'field_ding_event_lead',
        'arrangement-starttime' => 'field_ding_event_date',
        'arrangement-endtime' => 'field_ding_event_date_1',
        'display-starttime' => 'publish_on',
        'display-endtime' => 'unpublish_on',
        'arrangement-location' => 'field_ding_event_location',
        'arrangement-price' => 'field_ding_event_price',
        'resources' => 'nid',
      ),
    ),
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
  );
  $handler->display->display_options['style_options']['feed_settings'] = array(
    'absolute_paths' => 1,
    'feed_in_links' => 0,
  );
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Author */
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
  $handler->display->display_options['path'] = 'ding-redia-rss/event/app';
  $translatables['ding_redia_event_rss'] = array(
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
    t('[field_ding_event_list_image]'),
    t('Feed'),
    t('App Feed'),
    t('flag'),
  );
  $export['ding_redia_event_rss'] = $view;

  $view = new view();
  $view->name = 'ding_redia_news_rss';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Ding Redia News RSS';
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
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
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
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_ding_news_body']['id'] = 'field_ding_news_body';
  $handler->display->display_options['fields']['field_ding_news_body']['table'] = 'field_data_field_ding_news_body';
  $handler->display->display_options['fields']['field_ding_news_body']['field'] = 'field_ding_news_body';
  $handler->display->display_options['fields']['field_ding_news_body']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_body']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_ding_news_body']['alter']['preserve_tags'] = '<a><b><em><u><i><li><ul><ol><h2><h3><strong><p><br/>';
  $handler->display->display_options['fields']['field_ding_news_body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_body']['element_default_classes'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = FALSE;
  /* Field: Content: Lead */
  $handler->display->display_options['fields']['field_ding_news_lead']['id'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['table'] = 'field_data_field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['field'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_lead']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_lead']['type'] = 'text_plain';
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
  /* Field: Scheduler: Publish on */
  $handler->display->display_options['fields']['publish_on']['id'] = 'publish_on';
  $handler->display->display_options['fields']['publish_on']['table'] = 'scheduler';
  $handler->display->display_options['fields']['publish_on']['field'] = 'publish_on';
  $handler->display->display_options['fields']['publish_on']['label'] = '';
  $handler->display->display_options['fields']['publish_on']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['publish_on']['date_format'] = 'custom';
  $handler->display->display_options['fields']['publish_on']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['publish_on']['timezone'] = 'UTC';
  /* Field: Scheduler: Unpublish on */
  $handler->display->display_options['fields']['unpublish_on']['id'] = 'unpublish_on';
  $handler->display->display_options['fields']['unpublish_on']['table'] = 'scheduler';
  $handler->display->display_options['fields']['unpublish_on']['field'] = 'unpublish_on';
  $handler->display->display_options['fields']['unpublish_on']['label'] = '';
  $handler->display->display_options['fields']['unpublish_on']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['unpublish_on']['date_format'] = 'custom';
  $handler->display->display_options['fields']['unpublish_on']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['unpublish_on']['timezone'] = 'UTC';
  /* Sort criterion: Content: Updated date */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'node';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
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
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 2;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Scheduler: Publish on */
  $handler->display->display_options['filters']['publish_on']['id'] = 'publish_on';
  $handler->display->display_options['filters']['publish_on']['table'] = 'scheduler';
  $handler->display->display_options['filters']['publish_on']['field'] = 'publish_on';
  $handler->display->display_options['filters']['publish_on']['operator'] = 'not empty';
  $handler->display->display_options['filters']['publish_on']['group'] = 2;

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
    'redia-rss' => array(
      'ding_redia_rss' => array(
        'subheadline' => 'field_ding_news_lead',
        'arrangement-starttime' => '',
        'arrangement-endtime' => '',
        'display-starttime' => 'publish_on',
        'display-endtime' => 'unpublish_on',
        'arrangement-location' => '',
        'arrangement-price' => '',
        'resources' => 'nid',
      ),
    ),
    'core' => array(
      'views_rss_core' => array(
        'title' => 'title',
        'link' => '',
        'description' => 'field_ding_news_body',
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
  );
  $handler->display->display_options['style_options']['feed_settings'] = array(
    'absolute_paths' => 1,
    'feed_in_links' => 0,
  );
  $handler->display->display_options['path'] = 'ding-redia-rss/news';

  /* Display: App Feed */
  $handler = $view->new_display('feed', 'App Feed', 'feed_app');
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
    'redia-rss' => array(
      'ding_redia_rss' => array(
        'subheadline' => 'field_ding_news_lead',
        'arrangement-starttime' => '',
        'arrangement-endtime' => '',
        'display-starttime' => 'publish_on',
        'display-endtime' => 'unpublish_on',
        'arrangement-location' => '',
        'arrangement-price' => '',
        'resources' => 'nid',
      ),
    ),
    'core' => array(
      'views_rss_core' => array(
        'title' => 'title',
        'link' => '',
        'description' => 'field_ding_news_body',
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
        'content' => '',
        'title' => '',
        'description' => '',
        'keywords' => '',
        'thumbnail' => 'field_ding_news_list_image',
        'category' => '',
      ),
    ),
  );
  $handler->display->display_options['style_options']['feed_settings'] = array(
    'absolute_paths' => 1,
    'feed_in_links' => 0,
  );
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Author */
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
  $handler->display->display_options['path'] = 'ding-redia-rss/news/app';
  $translatables['ding_redia_news_rss'] = array(
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
    t('[field_ding_news_list_image]'),
    t('Feed'),
    t('App Feed'),
    t('flag'),
  );
  $export['ding_redia_news_rss'] = $view;

  return $export;
}
