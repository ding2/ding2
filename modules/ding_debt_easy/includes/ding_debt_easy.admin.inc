<?php

/**
 * @file
 * Handler for the administrative settings form for the module.
 */

/**
 * Implements hook_form().
 *
 * Administrative form used to configure the module.
 */
function ding_debt_easy_admin_settings_form($form, &$form_state) {
  $form['ding_debt_easy'] = [];
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'ding_debt_easy') . '/css/ding_debt_easy.admin.css',
  );

  $default_keys = variable_get('ding_debt_easy_keys', [
    'secret' => '',
    'checkout' => '',
  ]);
  $form['ding_debt_easy']['ding_debt_easy_keys'] = [
    '#type' => 'fieldset',
    '#title' => t('Nets payment keys'),
    '#description' => t('These values can be found at <a href="@url">https://portal.dibspayment.eu/integration</a> which requires that you have an easy payment account', ['@url' => 'https://portal.dibspayment.eu/integration']),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,
  ];

  $form['ding_debt_easy']['ding_debt_easy_keys']['secret'] = [
    '#type' => 'textfield',
    '#title' => t('Secret key'),
    '#default_value' => $default_keys['secret'],
    '#required' => TRUE,
  ];

  $form['ding_debt_easy']['ding_debt_easy_keys']['checkout'] = [
    '#type' => 'textfield',
    '#title' => t('Checkout key'),
    '#default_value' => $default_keys['checkout'],
    '#required' => TRUE,
  ];

  $form['ding_debt_easy']['endpoints'] = [
    '#type' => 'fieldset',
    '#title' => t('End point configuration'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#tree' => FALSE,
  ];

  $default_api = variable_get('ding_debt_easy_api_endpoints', [
    'type' => FALSE,
    'prod' => 'https://api.dibspayment.eu/v1/payments',
    'test' => 'https://test.api.dibspayment.eu/v1/payments',
  ]);

  $form['ding_debt_easy']['endpoints']['ding_debt_easy_api_endpoints'] = [
    '#type' => 'fieldset',
    '#title' => t('Nets payments API'),
    '#descriptions' => t('These end-point should not change, but if required they can be overridden in settings.php.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,
  ];

  $form['ding_debt_easy']['endpoints']['ding_debt_easy_api_endpoints']['type'] = [
    '#type' => 'checkbox',
    '#title' => t('Use testing end-point'),
    '#default_value' => $default_api['type'],
  ];

  $form['ding_debt_easy']['endpoints']['ding_debt_easy_api_endpoints']['prod'] = [
    '#type' => 'textfield',
    '#title' => t('Production payments end-point'),
    '#description' => '',
    '#default_value' => $default_api['prod'],
    '#disabled' => TRUE,
    '#required' => TRUE,
  ];

  $form['ding_debt_easy']['endpoints']['ding_debt_easy_api_endpoints']['test'] = [
    '#type' => 'textfield',
    '#title' => t('Test payments end-point'),
    '#default_value' => $default_api['test'],
    '#disabled' => TRUE,
    '#required' => TRUE,
  ];

  $default_endpoints = variable_get('ding_debt_easy_endpoints', [
    'callback' => DING_DEBT_EASY_CALLBACK_URL,
    'cancel' => DING_DEBT_EASY_CANCEL_URL,
  ]);
  $form['ding_debt_easy']['endpoints']['ding_debt_easy_endpoints'] = [
    '#type' => 'fieldset',
    '#title' => t('Return/callback URL'),
    '#description' => t('You should not change these URLs as it will/may break payment (mostly here for debug and you real need to  known what you are doing to change them.)'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,
  ];

  $form['ding_debt_easy']['endpoints']['ding_debt_easy_endpoints']['callback'] = [
    '#type' => 'textfield',
    '#title' => t('Return for completed payment'),
    '#default_value' => $default_endpoints['callback'],
    '#required' => TRUE,
  ];

  $form['ding_debt_easy']['endpoints']['ding_debt_easy_endpoints']['cancel'] = [
    '#type' => 'textfield',
    '#title' => t('Cancel payment callback'),
    '#default_value' => $default_endpoints['cancel'],
    '#required' => TRUE,
  ];

  $form['ding_debt_easy']['ding_debt_easy_config'] = [
    '#type' => 'fieldset',
    '#title' => t('Basic configuration'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  ];

  $form['ding_debt_easy']['ding_debt_easy_config']['currency'] = [
    '#type' => 'select',
    '#title' => t('Currency'),
    '#options' => _ding_debt_easy_get_currency_options(),
    '#default_value' => ding_debt_easy_get_currency(),
  ];

  $form['ding_debt_easy']['ding_debt_easy_config']['lang'] = [
    '#type' => 'select',
    '#title' => t('Language'),
    '#options' => _ding_debt_easy_get_localization_options(),
    '#default_value' => ding_debt_easy_get_localization(),
  ];

  $cards_options = _ding_debt_easy_get_payment_types_options();
  array_walk($cards_options, function (&$value, $key) {
    $value = '<div class="card-logo"><img src="' . $value . '" alt="' . $key . '" /><div class="name">' . $key . '</div></div>';
  });
  $form['ding_debt_easy']['ding_debt_easy_config']['cards'] = [
    '#type' => 'checkboxes',
    '#title' => t('Payment types (Cards etc.)'),
    '#options' => $cards_options,
    '#default_value' => ding_debt_easy_get_payment_types(FALSE),
    '#required' => TRUE,
  ];

  $form['ding_debt_easy']['ding_debt_easy_config']['integrationType'] = [
    '#type' => 'select',
    '#title' => t('Integration Type'),
    '#options' => _ding_debt_easy_get_integration_type_options(),
  ];

  $default_terms = variable_get('ding_debt_easy_terms', [
    'text' => [
      'value' => '',
      'format' => 'ding_wysiwyg',
    ],
    'url' => '',
  ]);

  $form['ding_debt_easy']['ding_debt_easy_terms'] = [
    '#type' => 'fieldset',
    '#title' => t('Terms and privacy'),
    '#description' => t('If these are <strong>not</strong> filled in the defaults text/url used by Nets easy payments will be used. See <a href=@url>Legal & Compliance</a> at Nets.', [
      '@url' => 'https://www.nets.eu/dk/payments/customerservice/legal-compliance/easy/',
    ]),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  ];

  $form['ding_debt_easy']['ding_debt_easy_terms']['url'] = [
    '#type' => 'textfield',
    '#title' => t('Link to existing "Terms and usage" page'),
    '#description' => t('Alternative to using the text field below, you can link to existing page.'),
    '#default_value' => '',
  ];

  $form['ding_debt_easy']['ding_debt_easy_terms']['text'] = [
    '#type' => 'text_format',
    '#title' => t('Terms declaration (<a href="@url" target="_blank">link to page</a>)', [
      '@url' => DING_DEBT_EASY_DEFAULT_TERMS_URL,
    ]),
    '#default_value' => $default_terms['text']['value'],
    '#format' => $default_terms['text']['format'],
    '#rows' => 15,
  ];

  $default_privacy = variable_get('ding_debt_easy_privacy', [
    'text' => [
      'value' => '',
      'format' => 'ding_wysiwyg',
    ],
    'url' => '',
  ]);

  $form['ding_debt_easy']['ding_debt_easy_privacy'] = [
    '#type' => 'fieldset',
    '#title' => t('Privacy and cookies'),
    '#description' => t('If these are <strong>not</strong> filled in the defaults text/url used by Nets easy payments will be used. See <a href=@url>Legal & Compliance</a> at Nets.', [
      '@url' => 'https://www.nets.eu/dk/payments/customerservice/legal-compliance/easy/',
    ]),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  ];

  $form['ding_debt_easy']['ding_debt_easy_privacy']['url'] = [
    '#type' => 'textfield',
    '#title' => t('Link to existing "Privacy and cookies" page'),
    '#description' => t('Alternative to using the text field below, you can link to existing page.'),
    '#default_value' => $default_privacy['url'],
  ];

  $form['ding_debt_easy']['ding_debt_easy_privacy']['text'] = [
    '#type' => 'text_format',
    '#title' => t('Privacy and cookies declaration (<a href="@url" target="_blank">link to page</a>)', [
      '@url' => DING_DEBT_EASY_DEFAULT_PRIVACY_URL,
    ]),
    '#default_value' => $default_privacy['text']['value'],
    '#format' => $default_privacy['text']['format'],
    '#rows' => 15,
  ];

  return system_settings_form($form);
}

/**
 * Implements hook_form().
 *
 * The reports mail settings.
 */
function ding_debt_easy_admin_mails_settings_form($form, &$form_state) {

  $default = variable_get('ding_debt_easy_mail', [
    'to' => '',
    'cc' => '',
    'title' => 'EASY betaling: %count afventende',
    'header' => [
      'value' => '',
      'format' => 'ding_wysiwyg',
    ],
    'footer' => [
      'value' => '',
      'format' => 'ding_wysiwyg',
    ],
  ]);

  $form['ding_debt_easy_mail'] = [
    '#type' => 'fieldset',
    '#title' => t('Mail report settings'),
    '#tree' => TRUE,
  ];

  $form['ding_debt_easy_mail']['to'] = [
    '#type' => 'textfield',
    '#title' => t('To'),
    '#description' => t('Comma separated list of mail addresses'),
    '#default_value' => $default['to'],
    '#required' => TRUE,
  ];

  $form['ding_debt_easy_mail']['cc'] = [
    '#type' => 'textfield',
    '#title' => t('Cc'),
    '#description' => t('Comma separated list of mail addresses'),
    '#default_value' => $default['cc'],
    '#required' => TRUE,
  ];

  $form['ding_debt_easy_mail']['title'] = [
    '#type' => 'textfield',
    '#title' => t('Mail title'),
    '#description' => t('Note: the "%count" in the title is substituted with the number payments awaiting action'),
    '#default_value' => $default['title'],
    '#required' => TRUE,
  ];

  $form['ding_debt_easy_mail']['header'] = [
    '#type' => 'text_format',
    '#title' => t('Mail header', [
      '@url' => DING_DEBT_EASY_DEFAULT_PRIVACY_URL,
    ]),
    '#default_value' => $default['header']['value'],
    '#format' => $default['header']['format'],
    '#rows' => 15,
    '#required' => TRUE,
  ];

  $form['ding_debt_easy_mail']['footer'] = [
    '#type' => 'text_format',
    '#title' => t('Mail footer', [
      '@url' => DING_DEBT_EASY_DEFAULT_PRIVACY_URL,
    ]),
    '#default_value' => $default['footer']['value'],
    '#format' => $default['footer']['format'],
    '#rows' => 15,
    '#required' => TRUE,
  ];

  return system_settings_form($form);
}

/**
 * Implements hook_form_validate().
 *
 * Validate that the mail-addresses enter is mail addresses.
 */
function ding_debt_easy_admin_mails_settings_form_validate(&$form, &$form_state) {
  $values = $form_state['values'];
  $fields = ['to', 'cc'];
  foreach ($fields as $field) {
    $mails = explode(',', $values['ding_debt_easy_mail'][$field]);
    foreach ($mails as $mail) {
      if (!filter_var(trim($mail), FILTER_VALIDATE_EMAIL)) {
        form_error($form['ding_debt_easy_mail'][$field], t('Invalid email format: %mail', ['%mail' => $mail]));
      }
    }
  }
}
