<?php
/**
 * @file
 * Define items list pane.
 */

/**
 * General ctools plugin settings.
 */
$plugin = array(
  'title' => t('Ding MKWS item list.'),
  'category' => t('Ding!'),
  'description' => t('Add MKWS items as a list.'),
  'single' => TRUE,
  'render callback' => 'ding_mkws_item_list_render',
);

/**
 * Plugin render.
 */
function ding_mkws_item_list_render($subtype, $conf, $panel_args, $context) {
  $pane = new stdClass();
  $global_options = variable_get('ding_mkws_global', array());
  $key = $subtype . '_' . $conf['scope'];
  $global_settings = (!empty($global_options['opac'])) ? $global_options['opac'][$key] : array();

  $params = array(
    'type' => $subtype,
    'amount' => (!empty($global_settings)) ? $global_settings['amount'] : '0',
    'maxrecs' => (!empty($global_settings)) ? $global_settings['maxrecs'] : '',
    'scope' => $conf['scope'],
    'title' => $global_settings['title'],
  );
  $hash = md5(implode('', $params));

  if (in_array($subtype, array('ting_object', 'ting_collection'))) {
    $entities = ding_entity_load_multiple($panel_args);
    foreach ($entities as $entity) {
      $record = $entity->reply->record;
      $query = $record['dc:title'][''][0];

      if (!empty($conf['scope'])) {
        $params['term']['type'] = $conf['scope'];

        switch ($conf['scope']) {
          case 'au':
            if (count($record['dc:creator']) > 0) {
              $result = reset($record['dc:creator']);
              if (isset($result[0])) {
                $author = $result[0];
                $query = drupal_strtolower($author);
              }
            }
            break;
        }

      }
      $params['term']['query'] = str_replace(array('.', '!', '?', '#', ','), ' ', $query);
    }
    if (!empty($global_settings['maxrecs'])) {
      $params['maxrecs'] = $global_settings['maxrecs'];
    }
  }
  else {
    $params['term']['query'] = reset($panel_args);
  }

  $params['resources'] = (!empty($global_settings)) ? array_values($global_settings['resources']) : NULL;

  $markup = array(
    '#type' => 'html_tag',
    '#tag' => 'div',
    '#attributes' => array(
      'data-hash' => $hash,
      'data-process' => 'ProcessDataForPaneWidget',
      'data-template' => 'dingMkwsPaneWidget',
      'class' => array(
        'ding-mkws-widget',
        'ding-mkws-pane-widget',
      ),
    ),
  );

  $pane->content['#markup'] = render($markup);
  ding_mkws_include_all();
  $pane->content['#attached'] = array(
    'css' => array(
      drupal_get_path('module', 'ding_mkws') . '/css/ding_mkws.css',
    ),
    'js' => array(
      drupal_get_path('module', 'ding_mkws') . '/js/ding_mkws.js',
      array(
        'type' => 'setting',
        'data' => array(
          $hash => $params,
        ),
      ),
    ),
  );

  return $pane;
}
