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
class DingListElement {

  public $listId = 0;
  public $id = 0;
  public $weight = 0;
  public $value = '';
  public $type = '';
  public $modified = 0;
  public $created = 0;
  public $extra = array();

  /**
   * Map keys in the data array to properties in the object.
   *
   * @var array
   */
  protected $propertyMap = array(
    'list_id' => 'listId',
    'element_id' => 'id',
    'weight' => 'weight',
    'modified' => 'modified',
    'created' => 'created',
  );

  protected $dataMap = array(
    'value' => 'value',
    'type' => 'type',
  );

  /**
   * DingListElement constructor.
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

    // foreach ($this->dataMap as $from => $to) {
    foreach ($data['data'] as $key => $value) {
      if (isset($this->dataMap[$key])) {
        $this->{$this->dataMap[$key]} = $value;
      }
      else {
        $this->extra[$key] = $value;
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
    $data = array('data' => array());

    foreach ($this->propertyMap as $from => $to) {
      $data[$from] = $this->{$to};
    }

    foreach ($this->dataMap as $from => $to) {
      if (!empty($this->{$to})) {
        $data['data'][$from] = $this->{$to};
      }
    }

    return $data;
  }

  /**
   * Save the element.
   *
   * @return DingListElement|false
   *   This object, or FALSE if the element wasn't saved.
   */
  public function save() {
    if (ding_provider_implements('openlist', 'v2_edit_element')) {
      try {
        ding_provider_invoke('openlist', 'v2_edit_element', $this->buildDataArray());
      }
      catch (Exception $e) {
        drupal_set_message(t("An error occurred while editing your element. Please contact the administrator if this problem persists."), 'error');
        return FALSE;
      }
    }

    return $element;
  }

  /**
   * Delete the list.
   *
   * @return bool
   *   If the elements where deleted or not.
   */
  public function delete() {
    if (ding_provider_implements('openlist', 'v2_delete_element')) {
      try {
        ding_provider_invoke('openlist', 'v2_delete_element', $this->buildDataArray());
      }
      catch (Exception $e) {
        drupal_set_message(t("An error occurred while deleting your element. Please contact the administrator if this problem persists."), 'error');
        return FALSE;
      }
    }

    return TRUE;
  }

}
