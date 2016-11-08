<?php

/**
 * Implements hook_ctools_plugin_pre_alter().
 */
function ddbasic_ctools_plugin_pre_alter(&$plugin, &$info) {
  switch ($plugin['module'] . ' ' . $plugin['name']) {
    case 'ting_search search_result_count':
      $plugin['render callback'] = 'ddbasic_ctools_plugin__ting_search_result_count_content_type_render';
      break;
    case 'ding_library contact':
      $plugin['render callback'] = 'ddbasic_ctools_plugin__ding_library_contact_content_type_render';
      break;
  }
}

/**
 * Render callback for the ting_search search_result_count pane.
 */
function ddbasic_ctools_plugin__ting_search_result_count_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $search_result = drupal_static('ting_search_results');
  if (isset($search_result)) {
    $results = isset($search_result->numTotalObjects) ? (int) $search_result->numTotalObjects : 0;
    $string = format_plural($results > 1 ? $results : 1, 'Result', 'Results');
    $block->content = array(
      'title' => array(
        '#theme' => 'html_tag',
        '#tag' => 'h1',
        '#attributes' => array('class' => array('page-title')),
        '#value' => t('Search result')
      ),
      'string' => array(
        '#theme' => 'html_tag',
        '#tag' => 'span',
        '#attributes' => array('class' => array('search-string')),
        '#value' => '"' . $search_result->search_key . '"'
      ),
      'count' => array(
        '#theme' => 'html_tag',
        '#tag' => 'span',
        '#attributes' => array('class' => array('count')),
        '#value' => '(' . format_plural($results, '1 Result', '@count Results') . ')'
      )
    );
  }

  return $block;
}

function ddbasic_ctools_plugin__ding_library_contact_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();
  if (empty($context->data)) {
    return $block;
  }
  $node = $context->data;

  $content = ' <div class="library-contact">';
  if (!empty($node->field_ding_library_phone_number['und'])) {
    $content .= '
      <div class="library-contact-phone">
        <span class="library-contact-phone-label">' . t('Phone:') . '</span>
        <span class="library-contact-phone">' . $node->field_ding_library_phone_number['und'][0]['value'] . '</span>
      </div>';
  }
  if (!empty($node->field_ding_library_fax_number['und'])) {
    $content .= '
        <div class="library-contact-fax">
          <span class="library-contact-fax-label">' . t('Fax:') . '</span>
          <span class="library-contact-fax">' . $node->field_ding_library_fax_number['und'][0]['value'] . '</span>
        </div>
    ';
  }
  if (!empty($node->field_ding_library_mail['und'])) {
    $content .= '
        <div class="library-contact-email">
          <span class="library-contact-email-label">' . t('Email:') . '</span>
          <span class="library-contact-email">' . l($node->field_ding_library_mail['und'][0]['email'], 'mailto:' . $node->field_ding_library_mail['und'][0]['email']) . '</span>
        </div>
    ';
  }
  $content .= '</div>';

  $block->title = t('Contact');
  $block->content = $content;

  return $block;
}