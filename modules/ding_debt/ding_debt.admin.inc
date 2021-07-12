<?php

/**
 * @file
 * Administration for ding_debts.
 */

/**
 * Settings form.
 */
function ding_debt_settings_form($form, $form_state) {
  $form['introtext'] = [
    '#type' => 'fieldset',
    '#title' => t('Introtext'),
    '#tree' => FALSE,
    '#description' => t('Text displayed at the top of the page, useful for explaining the move to a new system.'),
  ];

  $form['introtext']['ding_debt_show_introtext'] = [
    '#type' => 'checkbox',
    '#title' => t('Show introtext'),
    '#default_value' => variable_get('ding_debt_show_introtext', FALSE),
  ];

  $ding_debt_introtext = variable_get('ding_debt_introtext', _ding_debt_introtext_default());

  // We have to apply states to a wrapper, else it will only apply it to the
  // text field and not the text format selector. As suggested here:
  // https://www.drupal.org/project/drupal/issues/997826#comment-9119483
  $form['introtext']['wrapper'] = [
    '#type' => 'container',
    '#states' => [
      'visible' => [
        ':input[name="ding_debt_show_introtext"]' => ['checked' => TRUE],
      ],
    ],
  ];

  $form['introtext']['wrapper']['ding_debt_introtext'] = [
    '#type' => 'text_format',
    '#title' => t('Introtext'),
    '#default_value' => $ding_debt_introtext['value'],
    '#format' => $ding_debt_introtext['format'],
    '#states' => [
      'visible' => [
        ':input[name="ding_debt_show_introtext"]' => ['checked' => TRUE],
      ],
    ],
  ];

  $form['internal'] = [
    '#type' => 'fieldset',
    '#title' => t('Payable on site'),
    '#description' => t('Settings for debts that can be payed on site using DIBS.'),
    '#tree' => FALSE,
  ];

  $form['internal']['ding_debt_enable_internal'] = [
    '#type' => 'checkbox',
    '#title' => t('Show list'),
    '#description' => t('Shows list of debts payable on site.'),
    '#default_value' => variable_get('ding_debt_enable_internal', TRUE),
  ];

  $form['internal']['ding_debt_internal_title'] = [
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('Title for section, only shown if off-site debts is also shown.'),
    '#default_value' => variable_get('ding_debt_internal_title', ''),
    '#states' => [
      'enabled' => [
        ':input[name="ding_debt_enable_internal"]' => ['checked' => TRUE],
        ':input[name="ding_debt_enable_external"]' => ['checked' => TRUE],
      ],
    ],
  ];

  $form['internal']['ding_debt_enable_internal_button'] = [
    '#type' => 'checkbox',
    '#title' => t('Show payment button'),
    '#description' => t('Shows payment button for debts payable on site.'),
    '#default_value' => variable_get('ding_debt_enable_internal_button', TRUE),
    '#states' => [
      'enabled' => [
        ':input[name="ding_debt_enable_internal"]' => ['checked' => TRUE],
      ],
    ],
  ];

  $form['external'] = [
    '#type' => 'fieldset',
    '#title' => t('Payable off-site'),
    '#description' => t('Settings for debts that can be payed on an external site.'),
    '#tree' => FALSE,
  ];

  $form['external']['ding_debt_enable_external'] = [
    '#type' => 'checkbox',
    '#title' => t('Show list'),
    '#description' => t('Shows list of debts payable off-site.'),
    '#default_value' => variable_get('ding_debt_enable_external', FALSE),
  ];

  $form['external']['ding_debt_external_title'] = [
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('Title for section, only shown if on site debts is also shown.'),
    '#default_value' => variable_get('ding_debt_external_title', ''),
    '#states' => [
      'enabled' => [
        ':input[name="ding_debt_enable_external"]' => ['checked' => TRUE],
        ':input[name="ding_debt_enable_internal"]' => ['checked' => TRUE],
      ],
    ],
  ];

  $form['external']['ding_debt_enable_external_button'] = [
    '#type' => 'checkbox',
    '#title' => t('Show payment button'),
    '#description' => t('Shows payment button for debts payable off-site.'),
    '#default_value' => variable_get('ding_debt_enable_external_button', FALSE),
    '#states' => [
      'enabled' => [
        ':input[name="ding_debt_enable_external"]' => ['checked' => TRUE],
      ],
    ],
  ];

  $form['external']['button'] = [
    '#type' => 'fieldset',
    '#title' => t('Payment button'),
    '#tree' => FALSE,
    '#states' => [
      'visible' => [
        ':input[name="ding_debt_enable_external_button"]' => ['checked' => TRUE],
      ],
    ],
  ];

  $form['external']['button']['ding_debt_external_button_text'] = [
    '#type' => 'textfield',
    '#title' => t('Payment button text'),
    '#description' => t('Label for the payment button.'),
    '#default_value' => variable_get('ding_debt_external_button_text', ''),
  ];

  $form['external']['button']['ding_debt_external_button_url'] = [
    '#type' => 'textfield',
    '#title' => t('Payment button url'),
    '#description' => t('URL for the payment button.'),
    '#default_value' => variable_get('ding_debt_external_button_url', ''),
  ];

  $form['external']['extra_information'] = [
    '#type' => 'fieldset',
    '#title' => t('Extra information'),
    '#description' => t('Extra information displayed after the list. Useful for terms, information about delays in processing, etc.'),
    '#tree' => FALSE,
    '#states' => [
      'visible' => [
        ':input[name="ding_debt_enable_external"]' => ['checked' => TRUE],
      ],
    ],
  ];

  $form['external']['extra_information']['ding_debt_external_show_extra_information'] = [
    '#type' => 'checkbox',
    '#title' => t('Show extra information'),
    '#default_value' => variable_get('ding_debt_external_show_extra_information', FALSE),
  ];

  $ding_debt_external_extra_information = variable_get('ding_debt_external_extra_information', _ding_debt_external_extra_information_default());

  $form['external']['extra_information']['wrapper'] = [
    '#type' => 'container',
    '#states' => [
      'visible' => [
        ':input[name="ding_debt_external_show_extra_information"]' => ['checked' => TRUE],
      ],
    ],
  ];

  $form['external']['extra_information']['wrapper']['ding_debt_external_extra_information'] = [
    '#type' => 'text_format',
    '#title' => t('Extra information'),
    '#default_value' => $ding_debt_external_extra_information['value'],
    '#format' => $ding_debt_external_extra_information['format'],
    '#states' => [
      'visible' => [
        ':input[name="ding_debt_external_show_extra_information"]' => ['checked' => TRUE],
      ],
    ],
  ];

  return system_settings_form($form);
}

/**
 * Form validate function.
 */
function ding_debt_settings_form_validate($form, $form_state) {
  if ($form_state['values']['ding_debt_enable_external_button']) {
    if (empty($form_state['values']['ding_debt_external_button_text'])) {
      form_error($form['external']['button']['ding_debt_external_button_text'], t('Button text is required.'));
    }

    if (empty($form_state['values']['ding_debt_external_button_url'])) {
      form_error($form['external']['button']['ding_debt_external_button_url'], t('Button link is required.'));
    }
  }

  if (empty($form_state['values']['ding_debt_enable_internal_button'])
    && empty($form_state['values']['ding_debt_enable_external_button'])) {
    form_error($form, t('Please enable either internal or external payment'));
  }
}
