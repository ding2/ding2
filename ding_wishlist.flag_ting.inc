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
      'show_on_ting_types' => array('ting_object'),
    );
    return $options;
  }

  function options_form(&$form) {
    parent::options_form($form);

    $form['display']['show_on_ting_types'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Wishlist allowed ting types'),
        '#options' => array('ting_object' => t('Ting object')),
        '#default_value' => $this->show_on_ting_types,
        '#access' => empty($this->locked['show_on_ting_types']),
    );
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
}
