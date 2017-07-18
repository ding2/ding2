<?php

/**
 * @file
 * Represents field definitions and implementation of field hooks.
 */

/**
 * Implements hook_field_info().
 */
function ding_mkws_field_info() {
  return array(
    'ding_mkws_node' => array(
      'label' => t('Ding mkws node'),
      'description' => t('Field which represents a mkws widget for node.'),
      'default_widget' => 'ding_mkws_node_widget_default',
      'default_formatter' => 'ding_mkws_node_formatter_default',
    ),
  );
}

/**
 * Implements hook_field_widget_info().
 */
function ding_mkws_field_widget_info() {
  return array(
    'ding_mkws_node_widget_default' => array(
      'label' => t('Default'),
      'field types' => array('ding_mkws_node'),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_DEFAULT,
        'default value' => FIELD_BEHAVIOR_NONE,
      ),
    ),
  );
}


/**
 * Implements hook_field_is_empty().
 */
function ding_mkws_field_is_empty($item, $field) {
  switch ($field['type']) {
    case 'ding_mkws_node':
      return empty($item['wrapper']['term']) || empty($item['wrapper']['resources']);

    default:
      return FALSE;
  }
}

/**
 * Implements hook_field_widget_form().
 */
function ding_mkws_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  switch ($instance['widget']['type']) {
    case 'ding_mkws_node_widget_default':
      $element['wrapper'] = array(
        '#type' => 'fieldset',
        '#title' => t('LBR widget'),
        '#collapsible' => FALSE,
      );

      $item = !empty($items) ? reset($items) : array();
      $element['wrapper']['additional'] = array(
        '#markup' => '<p>' . t('This fieldgroup generates a widget on the node itself. Resources are searched based on the term with amount defined.') . '</p>',
      );

      $element['wrapper']['term'] = array(
        '#type' => 'textfield',
        '#title' => t('Term:'),
        '#default_value' => !empty($item['term']) ? $item['term'] : NULL,
        '#size' => 40,
        '#attributes' => array('placeholder' => t('Type in your term(s) here...')),
      );

      $options = _ding_mkws_get_processed_resources();
      $element['wrapper']['resources'] = array(
        '#type' => 'select',
        '#title' => t('Resources:'),
        '#default_value' => !empty($item['resources']) ? $item['resources'] : NULL,
        '#options' => $options,
        '#empty_option' => t('Choose LBRs'),
        '#multiple' => TRUE,
      );

      $element['wrapper']['amount'] = array(
        '#type' => 'textfield',
        '#title' => t('Amount:'),
        '#default_value' => !empty($item['amount']) ? $item['amount'] : 10,
        '#element_validate' => array('element_validate_integer_positive'),
        '#size' => 6,
        '#maxlength' => 4,
      );

      $element['wrapper']['maxrecs'] = array(
        '#type' => 'textfield',
        '#title' => t('Maxrecs'),
        '#default_value' => !empty($item['maxrecs']) ? $item['maxrecs'] : '',
        '#size' => 6,
        '#maxlength' => 4,
      );

      $element['wrapper']['toggle_title'] = array(
        '#prefix' => '<br>',
        '#type' => 'checkbox',
        '#title' => t('Change widget headline'),
        '#default_value' => !empty($item['toggle_title']) ? $item['toggle_title'] : 0,
      );

      $element['wrapper']['widget_headline'] = array(
        '#prefix' => '<br>',
        '#type' => 'textfield',
        '#title' => t('Widget headline'),
        '#default_value' => !empty($item['widget_headline']) ? $item['widget_headline'] : '',
        '#states' => array(
          'visible' => array(
            'input[name="field_mkws_node_widget[und][0][wrapper][toggle_title]"]' => array(
              'checked' => TRUE,
            ),
          ),
        ),
      );

      ding_mkws_include_all();
      $element['#attached'] = array(
        'css' => array(
          drupal_get_path('module', 'ding_mkws') . '/css/ding_mkws.fields.css',
        ),
      );
      break;
  }

  return $element;
}

/**
 * Implements hook_field_presave().
 */
function ding_mkws_field_presave($entity_type, $entity, $field, $instance, $langcode, &$items) {
  switch ($instance['widget']['type']) {
    case 'ding_mkws_node_widget_default':
      foreach ($items as $delta => &$item) {
        $item = (!empty($item['wrapper'])) ? $item['wrapper'] : $item;
        $item['resources'] = serialize($item['resources']);

        if (!empty($item['toggle_title'])) {
          $instance['label'] = $item['widget_headline'];
          field_update_instance($instance);
        }
        else {
          $instance['label'] = 'Content for LBR';
          field_update_instance($instance);
        }

        if (empty($item['maxrecs'])) {
          $item['maxrecs'] = 0;
        }
      }
      break;
  }
}

/**
 * Implements hook_field_load().
 */
function ding_mkws_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    foreach ($items[$id] as $delta => $item) {
      if ($field['type'] == 'ding_mkws_node') {
        $items[$id][$delta]['resources'] = unserialize($items[$id][$delta]['resources']);
      }
    }
  }
}

/**
 * Implements hook_field_formatter_info().
 */
function ding_mkws_field_formatter_info() {
  return array(
    'ding_mkws_node_formatter_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ding_mkws_node',
      ),
      'settings' => array(),
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function ding_mkws_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  if (!empty($items)) {
    switch ($display['type']) {
      case 'ding_mkws_node_formatter_default':
        $item = reset($items);
        if (empty($item['maxrecs'])) {
          unset($item['maxrecs']);
        }
        $imploded = array_map(function ($i) {
          return is_array($i) ? implode('', $i) : $i;
        }, $item);
        $hash = md5(implode('', $imploded));
        ding_mkws_include_all();
        $markup = array(
          '#type' => 'html_tag',
          '#tag' => 'div',
          '#attributes' => array(
            'data-hash' => $hash,
            'data-process' => 'ProcessDataForNodeWidget',
            'data-template' => 'dingMkwsNodeWidget',
            'class' => array(
              'ding-mkws-widget',
              'ding-mkws-node-widget',
            ),
          ),
        );

        $element[0] = array(
          '#markup' => drupal_render($markup),
          '#attached' => array(
            'css' => array(
              drupal_get_path('module', 'ding_mkws') . '/css/ding_mkws.css',
            ),
            'js' => array(
              drupal_get_path('module', 'ding_mkws') . '/js/ding_mkws.js',
              array(
                'type' => 'setting',
                'data' => array(
                  $hash => $item,
                ),
              ),
            ),
          ),
        );
        break;
    }
  }
  return $element;
}
