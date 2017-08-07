<?php

/**
 * @file
 * Ding list pages.
 */

/**
 * Page for managing the lists.
 */
function ding_list_manage_page($account) {
  $lists = ding_list_get_lists(NULL, $account);
  $view = array();
  if (!empty($lists)) {
    $view = entity_view('ding_type', $lists, 'teaser');
  }

  $create_form = array(
    '#markup' => l(t('Add new list'), 'list/create', array('query' => drupal_get_destination(), 'attributes' => array('class' => array('button')))),
  );

  return array($create_form) + $view;
}
