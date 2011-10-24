<?php
/**
 * @file
 * ding_wishlist.flag_ting.inc
 */

/**
 * Implements a ting flag.
 */
class flag_ting extends flag_flag {
  function options() {
    $options = parent::options();
    $options += array(
      'show_on_ting_types' => array(),
      'flagged_already_message' => '',
    );
    return $options;
  }

  function options_form(&$form) {
    parent::options_form($form);
    $form['messages']['flagged_already_message'] = array(
        '#type' => 'textfield',
        '#title' => t('Flagged already message'),
        '#default_value' => $this->flagged_already_message,
    );
    $form['messages']['flag_short']['#weight'] = 1;
    $form['messages']['flag_long']['#weight'] = 2;
    $form['messages']['flag_message']['#weight'] = 3;
    $form['messages']['flagged_already_message']['#weight'] = 4;
    $form['messages']['unflag_short']['#weight'] = 5;
    $form['messages']['unflag_long']['#weight'] = 6;
    $form['messages']['unflag_message']['#weight'] = 7;

    $form['display']['show_on_ting_types'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Wishlist allowed ting types'),
        '#options' => array('ting_object' => t('Ting object')),
        '#default_value' => $this->show_on_ting_types,
        '#access' => empty($this->locked['show_on_ting_types']),
    );

    unset($form['messages']['tokens_help']);
  }

  function _load_content($content_id) {
    return (object) array('ting_id' => $content_id);
  }

  function applies_to_content_object($ting_object) {
    return TRUE;
  }

  function get_content_id($ting_object) {
    return $ting_object->ting_id;
  }

  function get_relevant_action_objects($content_id) {
    return array(
      'ting_object' => $this->fetch_content($content_id),
    );
  }

  function applies_to_content_id_array($content_ids) {
    $passed = array();
    foreach ($content_ids as $ting_id) {
      if ($this->applies_to_content_id($ting_id)) {
        $passed[$ting_id] = TRUE;
      }
    }
    return $passed;
  }

  function get_user_count_number($uid, $sid = NULL) {
    return parent::get_user_count($uid, $sid)->fetchField();
  }

  /**
   * Returns array of items' ids a user has flagged.
   */
  function get_user_content_ids($uid, $sid = NULL) {
    if (!isset($sid)) {
      $sid = flag_get_sid($uid);
    }
    return db_select('flag_content', 'fc')
            ->fields('fc', array('content_id'))
            ->condition('fid', $this->fid)
            ->condition('uid', $uid)
            ->condition('sid', $sid)
            ->execute()
            ->fetchAllAssoc('content_id');
  }
}
