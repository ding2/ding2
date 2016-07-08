<?php
/**
 * @file
 * ding_dams1.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function ding_dams_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_instance
  $overrides["field_instance.node-ding_event-field_ding_event_files.settings|file_extensions"] = 'txt pdf doc docx ppt pptx xsl xslx odt ods mp3 wav wma';
  $overrides["field_instance.node-ding_event-field_ding_event_files.widget|settings|allowed_schemes|vimeo"] = 0;
  $overrides["field_instance.node-ding_event-field_ding_event_files.widget|settings|allowed_schemes|youtube"] = 0;
  $overrides["field_instance.node-ding_event-field_ding_event_files.widget|settings|allowed_types|default"]["DELETED"] = TRUE;
  $overrides["field_instance.node-ding_event-field_ding_event_files.widget|settings|allowed_types|document"] = 0;
  $overrides["field_instance.node-ding_event-field_ding_event_files.widget|settings|browser_plugins|dams_media_browser--media_browser_2"] = 1;
  $overrides["field_instance.node-ding_event-field_ding_event_files.widget|settings|browser_plugins|dams_media_browser--media_browser_3"] = 1;
  $overrides["field_instance.node-ding_event-field_ding_event_files.widget|settings|browser_plugins|dams_media_browser--media_browser_4"] = 1;
  $overrides["field_instance.node-ding_event-field_ding_event_files.widget|settings|browser_plugins|dams_media_browser--media_browser_5"] = 1;
  $overrides["field_instance.node-ding_event-field_ding_event_files.widget|settings|browser_plugins|library"]["DELETED"] = TRUE;
  $overrides["field_instance.node-ding_event-field_ding_event_files.widget|settings|browser_plugins|media_default--media_browser_1"]["DELETED"] = TRUE;
  $overrides["field_instance.node-ding_event-field_ding_event_files.widget|settings|browser_plugins|media_default--media_browser_my_files"]["DELETED"] = TRUE;
  $overrides["field_instance.node-ding_event-field_ding_event_files.widget|settings|browser_plugins|media_internet"] = 0;
  $overrides["field_instance.node-ding_event-field_ding_event_files.widget|settings|browser_plugins|youtube"] = 0;
  $overrides["field_instance.node-ding_event-field_ding_event_files.widget|settings|progress_indicator"]["DELETED"] = TRUE;
  $overrides["field_instance.node-ding_news-field_ding_news_files.settings|file_extensions"] = 'txt pdf mp3 wav wma';
  $overrides["field_instance.node-ding_news-field_ding_news_files.widget|settings|allowed_schemes|vimeo"] = 0;
  $overrides["field_instance.node-ding_news-field_ding_news_files.widget|settings|allowed_schemes|youtube"] = 0;
  $overrides["field_instance.node-ding_news-field_ding_news_files.widget|settings|allowed_types|0"]["DELETED"] = TRUE;
  $overrides["field_instance.node-ding_news-field_ding_news_files.widget|settings|allowed_types|default"]["DELETED"] = TRUE;
  $overrides["field_instance.node-ding_news-field_ding_news_files.widget|settings|allowed_types|document"] = 0;
  $overrides["field_instance.node-ding_news-field_ding_news_files.widget|settings|browser_plugins|dams_media_browser--media_browser_2"] = 1;
  $overrides["field_instance.node-ding_news-field_ding_news_files.widget|settings|browser_plugins|dams_media_browser--media_browser_3"] = 1;
  $overrides["field_instance.node-ding_news-field_ding_news_files.widget|settings|browser_plugins|dams_media_browser--media_browser_4"] = 1;
  $overrides["field_instance.node-ding_news-field_ding_news_files.widget|settings|browser_plugins|dams_media_browser--media_browser_5"] = 1;
  $overrides["field_instance.node-ding_news-field_ding_news_files.widget|settings|browser_plugins|library"]["DELETED"] = TRUE;
  $overrides["field_instance.node-ding_news-field_ding_news_files.widget|settings|browser_plugins|media_default--media_browser_1"]["DELETED"] = TRUE;
  $overrides["field_instance.node-ding_news-field_ding_news_files.widget|settings|browser_plugins|media_default--media_browser_my_files"]["DELETED"] = TRUE;
  $overrides["field_instance.node-ding_news-field_ding_news_files.widget|settings|browser_plugins|media_internet"] = 0;
  $overrides["field_instance.node-ding_news-field_ding_news_files.widget|settings|browser_plugins|youtube"] = 0;
  $overrides["field_instance.node-ding_news-field_ding_news_files.widget|settings|progress_indicator"]["DELETED"] = TRUE;

  // Exported overrides for: file_display
  $overrides["file_display.video__default__media_vimeo_image.status"] = TRUE;
  $overrides["file_display.video__teaser__media_vimeo_image.status"] = TRUE;

 return $overrides;
}
