<?php
function ding_dibs_admin_settings($form, &$form_state) {

  drupal_add_css(drupal_get_path('module', 'ding_dibs') . '/css/ding_dibs.css');

  $cards = ding_dibs_cards();

  foreach ($cards as $key=>$card) {
    $cards[$key] = '<img src="' . base_path() . drupal_get_path('module', 'ding_dibs') . '/img/card_logos/' . $card . '" alt="' . $key . '" class="card-logo"> <b>' . $key . '</b>';
  }

  $form['terms_of_sale']=array(
    '#type' => 'textarea',
    '#title' => t('Terms of sale'),
    '#description' => '<p>' .
      t('
        DIBS require that the following information must be visible to the customer before payment takes place:<br/><br/>

        The shop\'s contact info (name, address, e-mail and/or telephone number including the shop\'s CVR number).<br/>
        A complete description of the services/products offered. In other words, the customer must never doubt what he/she is paying for.<br/>
        A clear itemization of the total amount charged to the credit card, including freight, value added tax, etc.<br/>
        Specification of the currency used for the transaction (e.g. DKK, SEK, NOK or EUR).<br/>
        Terms of sale and delivery, including the right to terminate the purchase agreement.<br/>
        A clear statement of shipping policies (when will the customer receive the merchandise).
      ') . '</p><p>' .
      t('
        For instance:<br/>
        The debt is paid in full to: [name] library, [adress], [email], CVR no. [number].<br/>
        Once the fee is paid, it is not possible to cancel the payment.<br/>
        The amount is not withdrawn from the account, until it is confirmed that the amount owed is paid in local system.<br/>
        Please note: PBS charges a transaction fee to handle your payment. The amount is 1.45 kr. + 0.1% of the fee.<br/>
        For example: A fee of 15.00 kr. rises for PBS to 16.47 Kr.') . '</p>',
    '#default_value' => variable_get('terms_of_sale'),
    '#required' => TRUE
  );

  $form['cards_supported'] = array(
    '#type' => 'checkboxes',
    '#options' => $cards,
    '#title' => t('Supported card types:'),
    '#default_value' => variable_get('cards_supported'),
  );

  return system_settings_form($form);
}
