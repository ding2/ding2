<?php
/**
 * @file
 * ding_tabroll.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function ding_tabroll_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-ding_rolltab-field_ding_tabroll_ext'
  $field_instances['node-ding_rolltab-field_ding_tabroll_ext'] = array(
    'bundle' => 'ding_rolltab',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'If you rather want an external link or a link to a menu, use this field. It will only be used if the previous link is empty.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser_highlight' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ding_tabroll_ext',
    'label' => 'Menu or external',
    'required' => 0,
    'settings' => array(
      'attributes' => array(
        'class' => '',
        'configurable_title' => 0,
        'rel' => '',
        'target' => 'default',
        'title' => '',
      ),
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 1,
      'rel_remove' => 'default',
      'title' => 'none',
      'title_maxlength' => 128,
      'title_value' => '',
      'url' => 0,
      'user_register_form' => FALSE,
      'validate_url' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'link',
      'settings' => array(),
      'type' => 'link_field',
      'weight' => 35,
    ),
  );

  // Exported field_instance: 'node-ding_rolltab-field_ding_tabroll_image'
  $field_instances['node-ding_rolltab-field_ding_tabroll_image'] = array(
    'bundle' => 'ding_rolltab',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'content_glider' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'hidden',
        'module' => 'cs_adaptive_image',
        'settings' => array(
          'image_link' => '',
          'styles' => array(
            'breakpoint_1' => 768,
            'breakpoint_2' => 500,
            'fallback_style' => 'ding_tabroll_large',
            'max_style' => 'ding_tabroll_large',
            'style_1' => 'ding_tabroll_medium',
            'style_2' => 'ding_tabroll_small',
          ),
        ),
        'type' => 'cs_adaptive_image',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser_highlight' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ding_tabroll_image',
    'label' => 'Image',
    'required' => 1,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => 'rolltab',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'media',
      'settings' => array(
        'allowed_schemes' => array(
          'private' => 0,
          'public' => 'public',
        ),
        'allowed_types' => array(
          'audio' => 0,
          0 => 0,
          'document' => 0,
          'image' => 'image',
          'video' => 0,
        ),
        'browser_plugins' => array(
          'ding_content' => 0,
          'media_default--media_browser_1' => 0,
          'media_default--media_browser_my_files' => 0,
          'upload' => 0,
        ),
        'manualcrop_crop_info' => 1,
        'manualcrop_default_crop_area' => 1,
        'manualcrop_enable' => 1,
        'manualcrop_inline_crop' => 0,
        'manualcrop_instant_crop' => FALSE,
        'manualcrop_instant_preview' => 1,
        'manualcrop_keyboard' => 1,
        'manualcrop_maximize_default_crop_area' => 0,
        'manualcrop_require_cropping' => array(),
        'manualcrop_styles_list' => array(
          'ding_tabroll_large' => 'ding_tabroll_large',
        ),
        'manualcrop_styles_mode' => 'include',
        'manualcrop_thumblist' => 0,
        'progress_indicator' => 'throbber',
      ),
      'type' => 'media_generic',
      'weight' => 32,
    ),
  );

  // Exported field_instance: 'node-ding_rolltab-field_ding_tabroll_lead'
  $field_instances['node-ding_rolltab-field_ding_tabroll_lead'] = array(
    'bundle' => 'ding_rolltab',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Short description displayed inside the tab in a overlay.',
    'display' => array(
      'content_glider' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser_highlight' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ding_tabroll_lead',
    'label' => 'Lead',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 33,
    ),
  );

  // Exported field_instance: 'node-ding_rolltab-field_ding_tabroll_link'
  $field_instances['node-ding_rolltab-field_ding_tabroll_link'] = array(
    'bundle' => 'ding_rolltab',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Link to content that the tab should go to when clicked.',
    'display' => array(
      'content_glider' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'inline',
        'module' => 'entityreference',
        'settings' => array(
          'link' => 1,
        ),
        'type' => 'entityreference_label',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser_highlight' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ding_tabroll_link',
    'label' => 'Link',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 34,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('If you rather want an external link or a link to a menu, use this field. It will only be used if the previous link is empty.');
  t('Image');
  t('Lead');
  t('Link');
  t('Link to content that the tab should go to when clicked.');
  t('Menu or external');
  t('Short description displayed inside the tab in a overlay.');

  return $field_instances;
}
