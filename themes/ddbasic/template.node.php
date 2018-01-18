<?php

/**
 * @file
 * Node related preprocessors.
 */

/**
 * Implements hook_preprocess_node().
 *
 * Override or insert variables into the node templates.
 */
function ddbasic_preprocess_node(&$variables, $hook) {
  //
  // Add tpl suggestions for node view modes.
  if (isset($variables['view_mode'])) {
    $variables['theme_hook_suggestions'][] = 'node__view_mode__' . $variables['view_mode'];
    $variables['theme_hook_suggestions'][] = 'node__' . $variables['type'] . '__view_mode__' . $variables['view_mode'];
  }

  //
  // Call our own custom preprocess functions.
  $function = 'ddbasic_preprocess__node__' . $variables['type'];
  if (function_exists($function)) {
    call_user_func_array($function, array(&$variables));
  }

  // Opening hours on library list. but not on the search page.
  $path = drupal_get_path_alias();
  if (!(strpos($path, 'search', 0) === 0)) {
    $hooks = theme_get_registry(FALSE);
    if (isset($hooks['opening_hours_week']) && $variables['type'] == 'ding_library') {
      $variables['opening_hours'] = theme('ding_ddbasic_opening_hours_week', array('node' => $variables['node']));
    }
  }

  // Add updated to variables.
  $variables['ddbasic_updated'] = format_date($variables['node']->changed, 'long');

  // Modified submitted variable.
  if ($variables['display_submitted']) {
    $variables['submitted'] = format_date($variables['node']->changed, 'long');
  }
}

/**
 * Implememnts template_process_node().
 */
function ddbasic_process_node(&$variables, $hook) {
  // For search result view mode move title into left col. group.
  if (isset($variables['content']['group_right_col_search'])) {
    $variables['content']['group_right_col_search']['title'] = array(
      '#theme' => 'link',
      '#text' => decode_entities($variables['title']),
      '#path' => 'node/' . $variables['nid'],
      '#options' => array(
        'attributes' => array(
          'title' => $variables['title'],
        ),
        'html' => FALSE,
      ),
      '#prefix' => '<h2>',
      '#suffix' => '</h2>',
    );
  }
}

/**
 * Ding news.
 */
function ddbasic_preprocess__node__ding_news(&$variables) {

  $variables['news_submitted'] = format_date($variables['created'], 'ding_date_only_version2');

  switch ($variables['view_mode']) {
    case 'full':
      array_push($variables['classes_array'], 'node-full');

      // Make social-share button.
      $variables['content']['group_right']['share_button'] = array(
        '#theme' => 'ding_sharer',
        '#label' => t('Share this news'),
      );

      break;

    case 'alternative_layout_full':
      array_push($variables['classes_array'], 'node-full', 'alternative-layout-full');

      // Make social-share button.
      $variables['content']['group_left']['share_button'] = array(
        '#theme' => 'ding_sharer',
        '#label' => t('Share this news'),
      );

      break;

    case 'teaser':
      if (!empty($variables['field_ding_news_list_image'][0]['uri'])) {
        // Get image url to use as background image.
        $uri = $variables['field_ding_news_list_image'][0]['uri'];

        $image_title = $variables['field_ding_news_list_image'][0]['title'];

        // If in view with large first teaser and first in view.
        $current_view = $variables['view']->current_display;
        $views_with_large_first = array('ding_news_frontpage_list');
        if (in_array($current_view, $views_with_large_first) && $variables['view']->result[0]->nid == $variables['nid']) {
          $img_url = image_style_url('ding_panorama_list_large_wide', $uri);
          $variables['classes_array'][] = 'ding-news-highlighted';
        }
        else {
          $img_url = image_style_url('ding_panorama_list_large', $uri);
        }
        if (!empty($image_title)) {
          $variables['news_teaser_image'] = '<div class="ding-news-list-image background-image-styling-16-9" style="background-image:url(' . $img_url . ')" title="' . $image_title . '"></div>';
        }
        else {
          $variables['news_teaser_image'] = '<div class="ding-news-list-image background-image-styling-16-9" style="background-image:url(' . $img_url . ')"></div>';
        }
      }
      else {
        $variables['news_teaser_image'] = '<div class="ding-news-list-image background-image-styling-16-9"></div>';
      }
      break;

    case 'teaser_no_overlay':
      array_push($variables['classes_array'], 'node-teaser-no-overlay');

      if (!empty($variables['field_ding_news_list_image'][0]['uri'])) {
        // Get image url to use as background image.
        $uri = $variables['field_ding_news_list_image'][0]['uri'];

        $image_title = $variables['field_ding_news_list_image'][0]['title'];

        // If in view with large first teaser and first in view.
        $current_view = $variables['view']->current_display;
        $views_with_large_first = array('ding_news_frontpage_list');
        if (in_array($current_view, $views_with_large_first) && $variables['view']->result[0]->nid == $variables['nid']) {
          $img_url = image_style_url('ding_panorama_list_large_wide', $uri);
          $variables['classes_array'][] = 'ding-news-highlighted';
        }
        else {
          $img_url = image_style_url('ding_panorama_list_large', $uri);
        }
        if (!empty($image_title)) {
          $variables['news_teaser_image'] = '<div class="ding-news-list-image background-image-styling-16-9" style="background-image:url(' . $img_url . ')" title="' . $image_title . '"></div>';
        }
        else {
          $variables['news_teaser_image'] = '<div class="ding-news-list-image background-image-styling-16-9" style="background-image:url(' . $img_url . ')"></div>';
        }
      }
      else {
        $variables['news_teaser_image'] = '<div class="ding-news-list-image background-image-styling-16-9"></div>';
      }
      break;
  }
}

/**
 * Ding event.
 */
function ddbasic_preprocess__node__ding_event(&$variables) {

  $date = field_get_items('node', $variables['node'], 'field_ding_event_date');

  $price = field_get_items('node', $variables['node'], 'field_ding_event_price');
  if (!empty($price)) {
    $variables['event_price'] = $price[0]['value'] . ' ' . variable_get('ding_event_currency_type', 'Kr');
  }
  else {
    $variables['event_price'] = t('Free');
  }

  $location = field_get_items('node', $variables['node'], 'field_ding_event_location');
  $variables['alt_location_is_set'] = !empty($location[0]['name_line']) || !empty($location[0]['thoroughfare']);

  switch ($variables['view_mode']) {
    case 'teaser':
      // Add class if image.
      if (!empty($variables['field_ding_event_list_image'])) {
        $variables['classes_array'][] = 'has-image';
      }
      // Create image url.
      $uri = empty($variables['field_ding_event_list_image'][0]['uri']) ?
        "" : $variables['field_ding_event_list_image'][0]['uri'];

      if (!empty($uri)) {
        $variables['event_background_image'] = image_style_url('ding_panorama_list_large', $uri);
      }

      $variables['image_title'] = empty($variables['field_ding_event_list_image'][0]['title']) ?
        "" : 'title="' . $variables['field_ding_event_list_image'][0]['title'] . '"';

      // Date.
      if (!empty($date)) {
        // When the user saves the event time (e.g. danish time 2018-01-10 00:00),
        // the value is saved in the database in UTC time 
        // (e.g. UTC time 2018-01-09 23:00). To print out the date/time properly
        // We first need to create the dateObject with the UTC database time, and
        // afterwards we can convert the dateObject db-time to localtime.

        // Create a dateObject from startdate, set base timezone to UTC
        $date_start = new DateObject($date[0]['value'], new DateTimeZone($date[0]['timezone_db']));
        // Set timezone to local timezone
        $date_start->setTimezone(new DateTimeZone($date[0]['timezone']));

        // Create a dateObject from enddate, set base timezone to UTC
        $date_end = new DateObject($date[0]['value2'], new DateTimeZone($date[0]['timezone_db']));
        // Set timezone to local timezone
        $date_end->setTimezone(new DateTimeZone($date[0]['timezone']));

        $variables['event_date'] = date_format_date($date_start, 'ding_date_only_version2');
        $event_time_view_settings = array(
          'label' => 'hidden',
          'type' => 'date_default',
          'settings' => array(
            'format_type' => 'ding_time_only',
            'fromto' => 'value',
          ),
        );

        // If start and end date days are equal.
        if ($date_start->format('Ymd') !== $date_end->format('Ymd')) {
          $variables['event_date'] .= ' - ' . date_format_date($date_end, 'ding_date_only_version2');
        }
        // If start and end date days and time are not equal.
        if ($date_start->format('YmdHi') !== $date_end->format('YmdHi')) {
          $event_time_view_settings['settings']['fromto'] = 'both';
        }

        $event_time_ra = field_view_field('node', $variables['node'], 'field_ding_event_date', $event_time_view_settings);
        $variables['event_time'] = $event_time_ra[0]['#markup'];
      }

      break;

    case 'full':
      if (!empty($date)) {
        array_push($variables['classes_array'], 'node-full');

        // Add event time to variables. A render array is created based on the
        // date format "time_only".
        $event_time_ra = field_view_field('node', $variables['node'], 'field_ding_event_date', array(
          'label' => 'hidden',
          'type' => 'date_default',
          'settings' => array(
            'format_type' => 'ding_time_only',
            'fromto' => 'both',
          ),
        ));
        $variables['event_time'] = $event_time_ra[0]['#markup'];

        // Make social-share button.
        $variables['share_button'] = array(
          '#theme' => 'ding_sharer',
          '#label' => t('Share this event'),
        );

        // Make book/participate in event button.
        $price = ding_base_get_value('node', $variables['node'], 'field_ding_event_price');
        $participate = t('Participate in the event');
        $book = t('Book a ticket');

        if (empty($price)) {
          $text = $participate;
        }
        else {
          $text = $book;
        }

        $link_url = ding_base_get_value('node', $variables['node'], 'field_ding_event_ticket_link', 'url');

        if (!empty($link_url)) {
          $variables['book_button'] = l($text, $link_url, array(
            'attributes' => array(
              'class' => array('ticket', 'button'),
              'target' => '_blank',
            ),
          ));
        }

        if (!empty($location)) {
          $variables['content']['group_left']['og_group_ref']['#access'] = FALSE;
        }
      }
      break;
  }
}

/**
 * Ding Campaign.
 */
function ddbasic_preprocess__node__ding_campaign(&$variables) {
  $type = ding_base_get_value('node', $variables['node'], 'field_camp_settings', 'value');
  $image_uri = ding_base_get_value('node', $variables['node'], 'field_camp_image', 'uri');
  $image_style = "ding_full_width";
  $image_url = image_style_url($image_style, $image_uri);
  $variables['type'] = drupal_html_class($type);
  $variables['background'] = ($type == 'text_on_image' ? 'style="background-image: url(' . $image_url . ');"' : " ");
  $variables['link'] = ding_base_get_value('node', $variables['node'], 'field_camp_link', 'value');
  $variables['target'] = ding_base_get_value('node', $variables['node'], 'field_camp_new_window') ? '_blank' : '';
  $variables['panel_style'] = drupal_html_class($variables['elements']['#style']);

  if (isset($type)) {
    switch ($type) {
      case 'image_and_text':
        $variables['image'] = '<div class="ding-campaign-image" style="background-image: url(' . $image_url . '"></div>';
      break;
      case 'image':
        $variables['image'] = theme('image_style',array(
            'style_name' => "ding_full_width",
            'path' => $image_uri,
            'attributes' => array('class' => 'ding-campaign-image')
          )
        );
      break;
    }
  }
}

/**
 * Ding Library.
 */
function ddbasic_preprocess__node__ding_library(&$variables) {

  // Google maps addition to library list.
  $address = $variables['content']['group_ding_library_right_column']['field_ding_library_addresse'][0]['#address'];

  $street = $address['thoroughfare'];
  $street = preg_replace('/\s+/', '+', $street);
  $postal = $address['postal_code'];
  $city = $address['locality'];
  $country = $address['country'];
  $url = "http://www.google.com/maps/place/" . $street . "+" . $postal . "+" . $city . "+" . $country;
  $link = l(t("Show on map"), $url, array('attributes' => array('class' => 'maps-link', 'target' => '_blank')));

  $variables['content']['group_ding_library_right_column']['maps_link']['#markup'] = $link;
  $variables['content']['group_ding_library_right_column']['maps_link']['#weight'] = 10;
}

/**
 * Ding Group.
 */
function ddbasic_preprocess__node__ding_group(&$variables) {
  switch ($variables['view_mode']) {
    case 'teaser':
      $img_uri = $variables['field_ding_group_list_image'][0]['uri'];
      if (!empty($img_uri)) {
        $variables['background_image'] = image_style_url('ding_panorama_list_large_desaturate', $img_uri);
      }
      break;

    case 'teaser_no_overlay':
      array_push($variables['classes_array'], 'node-teaser-no-overlay');

      $img_field = field_get_items('node', $variables['node'], 'field_ding_group_list_image', 'uri');
      if (!empty($img_field)) {
        $variables['background_image'] = image_style_url('ding_panorama_list_large', $img_field[0]['uri']);
      }
      break;

    case 'full':
      array_push($variables['classes_array'], 'node-full');
      break;
  }
}

/**
 * Ding E-resource.
 */
function ddbasic_preprocess__node__ding_eresource(&$variables) {
  switch ($variables['view_mode']) {
    case 'teaser':
    case 'full':
      if (!empty($variables['field_ding_eresource_link'][0]['url'])) {
        $variables['link_url'] = $variables['field_ding_eresource_link'][0]['url'];
      }
      break;
  }
}
