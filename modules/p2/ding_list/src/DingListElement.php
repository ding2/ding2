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

  /**
   * ID of the list this element it attached to.
   *
   * @var int
   */
  protected $listId = 0;

  /**
   * Element ID.
   *
   * @var int
   */
  protected $id = 0;

  /**
   * Element value.
   *
   * @var string
   */
  protected $value = '';

  /**
   * Element type.
   *
   * @var string
   */
  protected $type = '';

  /**
   * Extra data.
   *
   * @var array
   */
  protected $data = array();

  /**
   * Map keys to the getter/setter functions.
   *
   * Without the get/set prefix.
   *
   * @var array
   */
  protected static $propertyMap = array(
    'list_id' => 'ListId',
    'element_id' => 'Id',
    'value' => 'Value',
    'type' => 'Type',
    'data' => 'Data',
  );

  /**
   * Parse an array into the object properties.
   *
   * @param array $data
   *   The data array.
   *
   * @return DingListElement
   *   The newly created object.
   */
  public static function fromDataArray(array $data) {
    $element = new DingListElement();

    foreach (self::$propertyMap as $from => $fn) {
      if (isset($data[$from])) {
        call_user_func(array($element, 'set' . $fn), $data[$from]);
      }
    }

    return $element;
  }

  /**
   * Save the element.
   *
   * @return DingListElement|false
   *   This object, or FALSE if the element wasn't saved.
   */
  public function save() {
    try {
      if (!empty($this->id)) {
        ding_provider_invoke('openlist', 'edit_element', $this);
      }
      elseif (!empty($this->listId)) {
        ding_provider_invoke('openlist', 'create_element', $this);
      }
      else {
        watchdog('ding_list', 'Trying to save element without listId', array(), WATCHDOG_ERROR);
        return FALSE;
      }
    }
    catch (Exception $e) {
      watchdog_exception('ding_list', $e);
      return FALSE;
    }

    return $this;
  }

  /**
   * Delete the element.
   *
   * @return bool
   *   If the elements where deleted or not.
   */
  public function delete() {
    try {
      ding_provider_invoke('openlist', 'delete_element', $this);
    }
    catch (Exception $e) {
      watchdog_exception('ding_list', $e);
      return FALSE;
    }

    return TRUE;
  }

  /**
   * Getter for listId.
   *
   * @return int
   *   The value.
   */
  public function getListId() {
    return $this->listId;
  }

  /**
   * Setter for listId.
   *
   * @param int $value
   *   The new value.
   *
   * @return DingListElement
   *   Chainable.
   */
  public function setListId($value) {
    $this->listId = $value;

    return $this;
  }

  /**
   * Getter for id.
   *
   * @return int
   *   The value.
   */
  public function getId() {
    return $this->id;
  }

  /**
   * Setter for id.
   *
   * @param int $value
   *   The new value.
   *
   * @return DingListElement
   *   Chainable.
   */
  public function setId($value) {
    $this->id = $value;

    return $this;
  }

  /**
   * Getter for value.
   *
   * @return string
   *   The value.
   */
  public function getValue() {
    return $this->value;
  }

  /**
   * Setter for value.
   *
   * @param string $value
   *   The new value.
   *
   * @return DingListElement
   *   Chainable.
   */
  public function setValue($value) {
    $this->value = $value;

    return $this;
  }

  /**
   * Getter for type.
   *
   * @return string
   *   The value.
   */
  public function getType() {
    return $this->type;
  }

  /**
   * Setter for type.
   *
   * @param string $value
   *   The new value.
   *
   * @return DingListElement
   *   Chainable.
   */
  public function setType($value) {
    $this->type = $value;

    return $this;
  }

  /**
   * Getter for data.
   *
   * @param string|null $key
   *   The specifc data key to get. Leave NULL to get the complete array.
   * @param mixed $default
   *   The default value, if the data doesn't contain the given key.
   *
   * @return string
   *   The value.
   */
  public function getData($key = NULL, $default = NULL) {
    if ($key === NULL) {
      return $this->data;
    }

    if (isset($this->data[$key])) {
      return $this->data[$key];
    }

    return $default;
  }

  /**
   * Setter for data.
   *
   * @param array|string $key
   *   The key to set. If an array is given the entire data array is replaced.
   * @param mixed $value
   *   The new value.
   *
   * @return DingListElement
   *   Chainable.
   */
  public function setData($key, $value = NULL) {
    if (is_array($key)) {
      $this->data = $key;
    }
    else {
      $this->data[$key] = $value;
    }

    return $this;
  }

}
