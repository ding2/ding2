<?php

/**
 * @file
 * Payment provider implementation for Ding!
 */

/**
 * Generate the payment URL to redirect the user to.
 */
function ding_debt_easy_payment_get_url($amount, $params, $callback) {
  return 'payment/dibs/redirect/';
}

/**
 * Generate support cards form element for the payment page.
 */
function ding_debt_easy_payment_cards_supported() {
  drupal_add_css(drupal_get_path('module', 'ding_debt_easy') . '/css/ding_debt_easy.css');
  $cards = ding_debt_easy_get_payment_types();

  $form = [];
  $form['ding_debt_easy_cards'] = [
    '#theme' => 'ding_debt_easy_cards_supported',
    '#cards' => $cards,
  ];

  return $form;
}

/**
 * Generate terms form element for the payment page.
 */
function ding_debt_easy_payment_terms() {
  $terms =  variable_get('ding_debt_easy_terms', []);

  $form = [];
  $form['ding_debt_easy_terms'] = [
    '#theme' => 'ding_debt_easy_terms',
    '#terms' => $terms['text']['value'],
    '#url' => $terms['url'],
  ];

  return $form;
}
