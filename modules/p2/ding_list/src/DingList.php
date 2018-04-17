<?php

/**
 * @file
 * The DingList object.
 */

namespace DingList;

/**
 * DingList object.
 *
 * @package DingList
 */
class DingList implements DingListInterface {

  public $id = 0;
  public $type = '';
  public $title = '';
  public $modified = 0;
  public $owner = '';
  public $data = array();
  public $elements = array();

  /**
   * Map keys in the data array to properties in the object.
   *
   * @var array
   */
  protected $propertyMap = array(
    'list_id' => 'id',
    'type' => 'type',
    'title' => 'title',
    'modified' => 'modified',
    'owner' => 'owner',
    'data' => 'data',
  );

  /**
   * DingList constructor.
   *
   * @param array|false $data
   *   If an array is provided, it will be parsed into the object.
   */
  public function __construct($data = FALSE) {
    if (is_array($data)) {
      $this->parseDataArray($data);
    }
  }

  /**
   * Parse an array into the object properties.
   *
   * @param array $data
   *   The data array.
   */
  public function parseDataArray(array $data) {
    foreach ($this->propertyMap as $from => $to) {
      if (isset($data[$from])) {
        $this->{$to} = $data[$from];
      }
    }

    $this->elements = array();
    if (isset($data['elements']) && is_array($data['elements'])) {
      foreach ($data['elements'] as $element_id => $element_data) {
        $this->elements[$element_id] = new DingListElement($element_data);
      }
    }
  }

  /**
   * Build a data array from the current properties.
   *
   * @return array
   *   The data array.
   */
  public function buildDataArray() {
    $data = array();

    foreach ($this->propertyMap as $from => $to) {
      $data[$from] = $this->{$to};
    }

    return $data;
  }

  /**
   * Save the list.
   */
  public function save() {
    if (!empty($this->id)) {
      if (ding_provider_implements('openlist', 'edit_list')) {
        ding_provider_invoke('openlist', 'v2_edit_list', $this->buildDataArray());
      }
    }
    else {
      if (ding_provider_implements('openlist', 'create_list')) {
        $this->id = ding_provider_invoke('openlist', 'v2_create_list', $this->buildDataArray());
      }
    }
  }

  /**
   * Delete the list.
   *
   * @return bool
   *   TRUE if the list is deleted.
   */
  public function delete() {
    if (ding_provider_implements('openlist', 'v2_delete_list')) {
      try {
        ding_provider_invoke('openlist', 'v2_delete_list', $this->buildDataArray());
      }
      catch (Exception $e) {
        drupal_set_message(t("An error occurred while deleting your list. Please contact the administrator if this problem persists."), 'error');
        return FALSE;
      }
    }

    return TRUE;
  }

  /**
   * Add an element to the list.
   *
   * @param DingListElement|array $element_data
   *   The element or a data array.
   */
  public function attachElement($element_data) {
    if ($element_data instanceof DingListElement) {
      $element_data = $element_data->buildDataArray();
    }

    if (ding_provider_implements('openlist', 'create_element')) {
      try {
        $result = ding_provider_invoke(
          'openlist',
          'v2_create_element',
          $this->buildDataArray(),
          $element_data,
          TRUE
        );

        if ($result !== FALSE) {
          $element = new DingListElement($result);
          $this->elements[$element->id] = $element;

          return $element;
        }
      }
      catch (Exception $e) {
        watchdog_exception('ding_list', $e);
        return FALSE;
      }
    }

    return FALSE;
  }

  /**
   * Check to see if a specific element exists.
   *
   * @param string $value
   *   The value to look for.
   *
   * @return mixed
   *   If the list has the element, return that element entity, if not return
   *   FALSE
   */
  public function hasElement($value) {
    foreach ($this->elements as $element) {
      if ($element->value == $value) {
        return $element;
      }
    }

    return FALSE;
  }

  /**
   * Get count of followers for a list.
   *
   * @return int
   *   The followers count.
   */
  public function getFollowersCount() {
    return count(ding_provider_invoke('openlist', 'call_module', 'Query', 'getLists', array(
      $this->id,
      array(DING_LIST_TYPE_LISTS),
    )));
  }

  /**
   * Get owner name of the list.
   *
   * @return string
   *   The username.
   */
  public function getOwnerName() {
    $owner = ding_list_local_user($this->owner);

    $result = t('Another loaner');
    if (!empty($owner->data) && isset($owner->data['display_name'])) {
      $result = $owner->data['display_name'];
    }
    elseif (!empty($owner->realname)) {
      $result = $owner->realname;
    }

    return check_plain($result);
  }

}
