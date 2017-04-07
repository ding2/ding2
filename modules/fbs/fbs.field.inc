<?php

/**
 * @file
 * Field functions for FBS profiles.
 */

/**
 * Implements hook_field_info().
 *
 * Define our virtual fields.
 */
function fbs_field_info() {
  return array(
    'fbs_name' => array(
      'label' => t('Name from FBS'),
      'description' => t('The user name from the FBS provider'),
      'default_widget' => 'hidden',
      'default_formatter' => 'fbs_default',
      'virtual_field' => array(
        'entity_types' => array('profile2'),
        'add_widget' => TRUE,
      ),
      'property_type' => 'text',
      'property_callbacks' => array('fbs_field_property_callback'),
    ),

    'fbs_phone' => array(
      'label' => t('Phone number from FBS'),
      'description' => t('The user phone number from the FBS provider'),
      // These two keys are for compatibility with the text_textfield widget.
      'settings' => array('max_length' => 255),
      'instance_settings' => array('text_processing' => 0),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'fbs_default',
      'virtual_field' => array(
        'entity_types' => array('profile2'),
      ),
      'property_type' => 'text',
      'property_callbacks' => array('fbs_field_property_callback'),
    ),

    'fbs_mail' => array(
      'label' => t('E-mail address from FBS'),
      'description' => t('The user e-mail address from the FBS provider'),
      // These two keys are for compatibility with the text_textfield widget.
      'settings' => array('max_length' => 255),
      'instance_settings' => array('text_processing' => 0),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'fbs_default',
      'virtual_field' => array(
        'entity_types' => array('profile2'),
      ),
      'property_type' => 'text',
      'property_callbacks' => array('fbs_field_property_callback'),
    ),

    'fbs_phone_notification' => array(
      'label' => t('Phone notification setting from FBS'),
      'description' => t('The user phone notification setting from the FBS provider'),
      // These two keys are for compatibility with the text_textfield widget.
      'settings' => array(),
      'instance_settings' => array(),
      'default_widget' => 'fbs_options_onoff',
      'default_formatter' => 'fbs_default',
      'virtual_field' => array(
        'entity_types' => array('profile2'),
      ),
      'property_type' => 'text',
      'property_callbacks' => array('fbs_field_property_callback'),
    ),

    'fbs_mail_notification' => array(
      'label' => t('E-mail notification setting from FBS'),
      'description' => t('The user e-mail notification setting from the FBS provider'),
      // These two keys are for compatibility with the text_textfield widget.
      'settings' => array(),
      'instance_settings' => array(),
      'default_widget' => 'fbs_options_onoff',
      'default_formatter' => 'fbs_default',
      'virtual_field' => array(
        'entity_types' => array('profile2'),
      ),
      'property_type' => 'text',
      'property_callbacks' => array('fbs_field_property_callback'),
    ),

    'fbs_preferred_branch' => array(
      'label' => t('Preferred branch from FBS'),
      'description' => t('The users preferred branch from the FBS provider'),
      'default_widget' => 'fbs_options_select',
      'default_formatter' => 'fbs_preferred_branch',
      'virtual_field' => array(
        'entity_types' => array('profile2'),
        'add_widget' => TRUE,
      ),
      'property_type' => 'text',
      'property_callbacks' => array('fbs_field_property_callback'),
    ),

    'fbs_on_hold' => array(
      'label' => t('On hold period from FBS'),
      'description' => t('Period where user should not get any reservations'),
      'default_widget' => 'fbs_period',
      'default_formatter' => 'fbs_period_default',
      'virtual_field' => array(
        'entity_types' => array('profile2'),
        'add_widget' => TRUE,
      ),
      'property_type' => 'struct',
      'property_callbacks' => array('fbs_field_property_callback'),
    ),

    'fbs_address' => array(
      'label' => t('User address from FBS'),
      'description' => t('The address of the user.'),
      'default_widget' => 'hidden',
      'default_formatter' => 'fbs_address_default',
      'virtual_field' => array(
        'entity_types' => array('profile2'),
        'add_widget' => TRUE,
      ),
      'property_type' => 'struct',
      'property_callbacks' => array('fbs_field_property_callback'),
    ),
);
}

/**
 * Implements hook_field_widget_info().
 */
function fbs_field_widget_info() {
  $return['fbs_period'] = array(
    'label' => t('Period'),
    'field types' => array('fbs_on_hold'),
    'behaviors' => array(
      'multiple values' => FIELD_BEHAVIOR_DEFAULT,
    ),
  );

  if (module_exists('options')) {
    // The standard options widgets doesn't like our virtual fields as they use
    // the fields "columns" to figure out the field array structure. So we wrap
    // them thinly.
    $return['fbs_options_select'] = array(
      'label' => t('Select list (FBS)'),
      'field types' => array('fbs_preferred_branch'),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_CUSTOM,
      ),
    );
    $return['fbs_options_onoff'] = array(
      'label' => t('Single on/off checkbox (FBS)'),
      'field types' => array('fbs_phone_notification', 'fbs_mail_notification'),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_CUSTOM,
      ),
      'settings' => array('display_label' => 0),
    );
  }

  return $return;
}

/**
 * Implements hook_field_widget_form().
 */
function fbs_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {

  switch ($instance['widget']['type']) {
    case 'fbs_period':
      $element['#type'] = 'fieldset';
      $fields = array(
        'from' => t('Start date'),
        'to' => t('End date'),
      );

      foreach ($fields as $key => $title) {
        $default_value = '';
        if (!empty($items[$delta][$key])) {
          $date = new DateObject("@" + $items[$delta][$key]);
          $default_value = $date->format(DATE_FORMAT_DATETIME);
        }
        $element[$key] = array(
          '#type' => 'date_popup',
          '#title' => $title,
          '#date_format' => 'd-m-Y',
          '#date_label_position' => 'invisible',
          '#default_value' => $default_value,
        );
      }

      return $element;

    case 'fbs_options_onoff':
    case 'fbs_options_select':
      // Fixes columns and lets options_field_widget_form() do the work.
      $field['columns'] = array('value' => 'mumble');
      $instance['widget']['type'] = preg_replace('/^fbs_/', '', $instance['widget']['type']);
      return options_field_widget_form($form, $form_state, $field, $instance, $langcode, $items, $delta, $element);
  }
}

/**
 * Implements hook_field_widget_settings_form().
 */
function fbs_field_widget_settings_form($field, $instance) {

  switch ($instance['widget']['type']) {
    case 'fbs_period':
      return;

    case 'fbs_options_onoff':
    case 'fbs_options_select':
      // Thin wrapping.
      return options_field_widget_settings_form($field, $instance);
  }
}

/**
 * Entity API wrapper property callback.
 *
 * Tells entity_metadata_wrapper how to get the data out of our fields.
 */
function fbs_field_property_callback(&$info, $entity_type, $field, $instance, $field_type) {
  $name = $field['field_name'];
  $property = &$info[$entity_type]['bundles'][$instance['bundle']]['properties'][$name];
  if ($field['type'] == 'fbs_on_hold') {
    $property['getter callback'] = 'entity_metadata_field_verbatim_get';
  }
  else {
    $property['getter callback'] = 'fbs_field_metadata_get';
  }
  unset($property['setter callback']);
  unset($property['query callback']);
}

/**
 * Callback to get the value of a field.
 */
function fbs_field_metadata_get($entity, array $options, $name, $entity_type, &$context) {
  // Get the raw field value.
  $val = entity_metadata_field_verbatim_get($entity, $options, $name, $entity_type, $context);
  if (isset($val['value'])) {
    return $val['value'];
  }
  return NULL;
}

/**
 * Callback to get the value of a field.
 */
function fbs_field_metadata_period_get($entity, array $options, $name, $entity_type, &$context) {
  // Get the raw field value.
  $val = entity_metadata_field_verbatim_get($entity, $options, $name, $entity_type, $context);
  if (isset($val['from']) || isset($val['to'])) {
    return $val;
  }
  return NULL;
}

/**
 * Implements hook_widget_info_alter().
 *
 * Alter existing widgets to support our fields.
 */
function fbs_field_widget_info_alter(&$info) {
  if (isset($info['text_textfield'])) {
    $info['text_textfield']['field types'][] = 'fbs_phone';
    $info['text_textfield']['field types'][] = 'fbs_mail';
  }
}

/**
 * Implements hook_field_load().
 */
function fbs_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  global $user;

  $field_types = array(
    'fbs_name',
    'fbs_phone',
    'fbs_mail',
    'fbs_phone_notification',
    'fbs_mail_notification',
    'fbs_preferred_branch',
    'fbs_on_hold',
    'fbs_address',
  );
  if (in_array($field['type'], $field_types)) {
    try {
      $patron = ding_user_get_creds($user);
    }
    catch (Exception $e) {
      // No creds, don't return anything.
      return;
    }
    foreach ($entities as $id => $entity) {
      // Only populate when the profile is for the current user.
      if ($entity->uid == $user->uid) {
        switch ($field['type']) {
          case 'fbs_name':
            $items[$id][0] = array('value' => $patron['name']);
            break;

          case 'fbs_phone':
            $items[$id][0] = array('value' => $patron['phone']);
            break;

          case 'fbs_mail':
            $items[$id][0] = array('value' => $patron['mail']);
            break;

          case 'fbs_preferred_branch':
            $items[$id][0] = array('value' => $patron['preferred_branch']);
            break;

          case 'fbs_phone_notification':
            $items[$id][0] = array('value' => $patron['phone_notification'] ? 1 : 0);
            break;

          case 'fbs_mail_notification':
            $items[$id][0] = array('value' => $patron['mail_notification'] ? 1 : 0);
            break;

          case 'fbs_on_hold':
            $value = array(
              'from' => '',
              'to' => '',
            );

            if ($patron['on_hold']) {
              if ($patron['on_hold']['from']) {
                $value['from'] = strtotime($patron['on_hold']['from']);
              }
              if ($patron['on_hold']['to']) {
                $value['to'] = strtotime($patron['on_hold']['to']);
              }
            }

            $items[$id][0] = $value;
            break;

          case 'fbs_address':
            $items[$id][0] = array('value' => $patron['address']);
            break;
        }
      }
    }
  }
}

/**
 * Implements hook_options_list().
 */
function fbs_options_list($field, $instance, $entity_type, $entity) {
  if (in_array($field['type'], array('fbs_phone_notification', 'fbs_mail_notification'))) {
    return array(
      0 => t('No'),
      1 => t('Yes'),
    );
  }
  elseif ($field['type'] == 'fbs_preferred_branch') {
    return fbs_branches();
  }
}

/**
 * Implements hook_field_is_empty().
 */
function fbs_field_is_empty($item, $field) {
  if ($field['type'] == 'fbs_on_hold') {
    if (empty($item['from']) && empty($item['to'])) {
      return TRUE;
    }
  }
  else {
    if (empty($item['value']) && (string) $item['value'] !== '0') {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Implements hook_field_formatter_info().
 */
function fbs_field_formatter_info() {
  return array(
    'fbs_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'fbs_name',
        'fbs_phone',
        'fbs_mail',
      ),
    ),

    'fbs_notification' => array(
      'label' => t('Default'),
      'field types' => array(
        'fbs_phone_notification',
        'fbs_mail_notification',
      ),
    ),

    'fbs_preferred_branch' => array(
      'label' => t('Default'),
      'field types' => array(
        'fbs_preferred_branch',
      ),
    ),

    'fbs_period_default'  => array(
      'label' => t('Default'),
      'field types' => array(
        'fbs_on_hold',
      ),
    ),

    'fbs_address_default'  => array(
      'label' => t('Default'),
      'field types' => array(
        'fbs_address',
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function fbs_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  foreach ($items as $delta => $item) {
    switch ($display['type']) {
      case 'fbs_default':
        $element[$delta] = array(
          '#markup' => check_plain($item['value']),
        );
        break;

      case 'fbs_notification':
        $element[$delta] = array(
          '#markup' => $item['value'] ? t('Yes') : t('No'),
        );
        break;

      case 'fbs_preferred_branch':
        $branches = fbs_branches();
        if (isset($branches[$item['value']])) {
          $title = $branches[$item['value']];
        }
        else {
          $title = t('Unknown');
        }
        $element[$delta] = array(
          '#markup' => check_plain($title),
        );
        break;

      case 'fbs_period_default':
        if (empty($item['from']) && empty($item['to'])) {
          return;
        }
        elseif (empty($item['from'])) {
          $markup = t('To !end-date', array(
                      '!end-date' => format_date($item['to'],
                                   'ding_material_lists_date'),
          ));
        }
        elseif (empty($item['to'])) {
          $markup = t('From !start-date', array(
                      '!start-date' => format_date($item['from'],
                                     'ding_material_lists_date'),
                    ));
        }
        else {
          $markup = t('From !start-date to !end-date', array(
                      '!start-date' => format_date($item['from'],
                                     'ding_material_lists_date'),
                      '!end-date' => format_date($item['to'],
                                   'ding_material_lists_date'),
                    ));
        }

        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;

      case 'fbs_address_default':
        if ($item['value']) {
          $element[$delta] = array(
            '#markup' => $item['value']['street'] . '<br />' .
            $item['value']['postal'] . ' ' . $item['value']['city'] . '<br />' .
            $item['value']['country'],
          );
        }
        break;
    }
  }

  return $element;
}
