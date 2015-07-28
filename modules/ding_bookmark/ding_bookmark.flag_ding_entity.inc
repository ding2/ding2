<?php
/**
 * @file
 * ding_bookmark.flag_ding_entity.inc
 */

/**
 * Implements a ding_entity_flag.
 */
class flag_ding_entity extends flag_flag {

  function options() {
    $options = parent::options();
    $options += array(
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
  }

  function _load_content($content_id) {
    $type_info = ding_entity_info('ding_entity');
    $entities = entity_load($type_info['entity_type'], array($content_id));
    return !empty($entities[$content_id]) ? $entities[$content_id] : array();
  }

  function applies_to_content_object($ding_entity) {
    return TRUE;
  }

  function get_content_id($ding_entity) {
    $entity_info = entity_get_info($entity_type);
    return $ding_entity->{$entity_info['entity keys']['id']};
  }

  function get_relevant_action_objects($content_id) {
    return array(
      'ding_entity' => $this->fetch_content($content_id),
    );
  }

  // @todo: what's the meaning of this?
  function applies_to_content_id_array($content_ids) {
    $passed = array();
    foreach ($content_ids as $entity_ids) {
      if ($this->applies_to_content_id($entity_ids)) {
        $passed[$entity_ids] = TRUE;
      }
    }
    return $passed;
  }

  function get_user_count_number($uid, $sid = NULL) {
    return parent::get_user_count($uid, $sid);
  }

  /**
   * Returns array of items' ids a user has flagged.
   */
  function get_user_content_ids($uid, $sid = NULL) {
    if (!isset($sid)) {
      $sid = flag_get_sid($uid);
    }
    return db_select('flag_content', 'fc')
      ->fields('fc', array('content_id', 'content_type'))
      ->condition('fid', $this->fid)
      ->condition('uid', $uid)
      ->condition('sid', $sid)
      ->orderBy('fcid', 'DESC')
      ->execute()
      ->fetchAllKeyed();
  }
}
