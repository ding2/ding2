<?php

/**
 * @file
 * The DingList object.
 */

namespace DingList;

/**
 * DingList object.
 *
 * To create a new instance use the DingList::fromDataArray(array $data), read
 * about the data structure in that function.
 *
 * @package DingList
 */
class DingList {

  /**
   * Number of preloaded elements.
   *
   * @var integer
   */
  const PRELOADED_ELEMENTS = 25;

  /**
   * List ID.
   *
   * @var int
   */
  protected $id = 0;

  /**
   * List type.
   *
   * @var string
   */
  protected $type = '';

  /**
   * List title.
   *
   * @var string
   */
  protected $title = '';

  /**
   * The openlist owner id.
   *
   * @var string
   */
  protected $owner = '';

  /**
   * Extra data.
   *
   * @var array
   */
  protected $data = array();

  /**
   * List of elements.
   *
   * @var DingListElemnt[]
   */
  protected $elements = array();

  /**
   * List note.
   *
   * @var string
   */
  protected $note = '';

  /**
   * The permissions to the list.
   *
   * These are filled when getPermission is called.
   *
   * @var array
   */
  protected $permissions = array();

  /**
   * If there's more elements available.
   *
   * @var bool
   */
  protected $elementCount = FALSE;

  /**
   * Map keys to the getter/setter functions.
   *
   * Without the get/set prefix.
   *
   * @var array
   */
  protected static $propertyMap = array(
    'list_id' => 'Id',
    'type' => 'Type',
    'title' => 'Title',
    'owner' => 'Owner',
    'data' => 'Data',
    'element_count' => 'ElementCount',
  );

  /**
   * Create an instance out of a data array.
   *
   * The structure of this data array, is the same as the one returned by the
   * openlist service. Which looks as the following:
   *
   * - list_id: List id, parsed to the id property.
   * - type: Type.
   * - title: Title.
   * - owner: The openlist user id.
   * - data: A custom data array. If the custom data array holds the note, it's
   *   passed along to the note property.
   *
   * @param array $data
   *   The data array.
   *
   * @return DingList
   *   The newly created object.
   */
  public static function fromDataArray(array $data) {
    $list = new DingList();

    foreach (self::$propertyMap as $from => $fn) {
      if (isset($data[$from])) {
        call_user_func(array($list, 'set' . $fn), $data[$from]);
      }
    }

    $list->elements = array();
    if (isset($data['elements']) && is_array($data['elements'])) {
      foreach ($data['elements'] as $element_id => $element_data) {
        $list->attachElement(DingListElement::fromDataArray($element_data), TRUE);
      }
    }

    if (isset($data['data']['note'])) {
      $list->setNote($data['data']['note']);
    }

    return $list;
  }

  /**
   * Save the list.
   *
   * @return DingList
   *   The object.
   */
  public function save() {
    if (!empty($this->id)) {
      ding_provider_invoke('openlist', 'edit_list', $this);
    }
    else {
      ding_provider_invoke('openlist', 'create_list', $this);
    }

    return $this;
  }

  /**
   * Delete the list.
   *
   * @return bool
   *   TRUE if the list is deleted.
   */
  public function delete() {
    try {
      ding_provider_invoke('openlist', 'delete_list', $this);
    }
    catch (Exception $e) {
      watchdog_exception('ding_list', $e);
      return FALSE;
    }

    return TRUE;
  }

  /**
   * Check to see if a specific element exists.
   *
   * @param string $value
   *   The value to look for.
   *
   * @return DingListElement|false
   *   If the list has the element, return that element entity, if not return
   *   FALSE
   */
  public function hasElement($value) {
    foreach ($this->elements as $element) {
      if ($element->getValue() == $value) {
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
    $owner = ding_provider_invoke('openlist', 'drupal_user', $this->owner);

    $result = t('Another loaner');
    if (!empty($owner->data) && isset($owner->data['display_name'])) {
      $result = $owner->data['display_name'];
    }
    elseif (!empty($owner->realname)) {
      $result = $owner->realname;
    }

    return check_plain($result);
  }

  /**
   * Make sure you're allowed to perform a certain action on a list.
   *
   * @param string $operation
   *   The operation you wish to perform.
   *
   * @return bool
   *   TRUE if the list has the operation, and FALSE if it doesn't.
   */
  public function allowed($operation) {
    $list_operations = ding_list_list_operations();
    return isset($list_operations[$this->getType()][$operation]);
  }

  /**
   * Move an element in a list down below another element.
   *
   * @param int $element_id
   *   ID of the element ot move.
   * @param int $previous
   *   ID of the element to position the $element after.
   *   If this is 0 the $element is positioned as the first element.
   *
   * @return bool
   *   If the move is successful or not.
   */
  public function setElementPosition($element_id, $previous = 0) {
    try {
      ding_provider_invoke('openlist', 'set_element_after', $this, $element_id, $previous);
    }
    catch (Exception $e) {
      watchdog_exception('ding_list', $e);
      return FALSE;
    }

    return TRUE;
  }

  /**
   * Add permissions to a list and user.
   *
   * @param string $permission
   *   The permission to add.
   * @param object $account
   *   The user to give the permissions.
   */
  public function setPermission($permission, $account = NULL) {
    if ($account === NULL) {
      global $user;
      $account = $user;
    }

    $openlist_uid = ding_provider_invoke('openlist', 'user_identifier', $account);
    ding_provider_invoke('openlist', 'call_module', 'ListPermission', 'setPermission', array(
      $openlist_uid,
      $this->getId(),
      $permission,
    ), array('use_cache' => FALSE));

    ding_provider_invoke('openlist', 'clear_cache', 'lp' . $this->getId());
    $this->permissions[$account->uid] = $permission;
  }

  /**
   * Remove permissions.
   *
   * @param object $account
   *   User to remove permissions from.
   */
  public function removePermission($account = NULL) {
    if ($account === NULL) {
      global $user;
      $account = $user;
    }

    $openlist_uid = ding_provider_invoke('openlist', 'user_identifier', $account);
    ding_provider_invoke('openlist', 'call_module', 'ListPermission', 'removePermission', array(
      $openlist_uid,
      $this->getId(),
    ), array('use_cache' => FALSE));

    ding_provider_invoke('openlist', 'clear_cache', 'lp' . $this->getId());
    $this->permissions[$account->uid] = FALSE;
  }

  /**
   * Get the users permissions to a list.
   *
   * @param object $account
   *   The user.
   *
   * @return bool|object
   *   The permissions entity for the user, or FALSE if there's no permission.
   */
  public function getPermission($account = NULL) {
    if ($account === NULL) {
      global $user;
      $account = $user;
    }

    if (!isset($this->permissions[$account->uid])) {
      $openlist_uid = ding_provider_invoke('openlist', 'user_identifier', $account);
      $this->permissions[$account->uid] = ding_provider_invoke('openlist', 'call_module', 'ListPermission', 'getPermission', array(
        $openlist_uid,
        $this->getId(),
      ), array('cache_prefix' => 'lp' . $this->getId()));

      if ($this->permissions[$account->uid] !== FALSE) {
        // Flatten the array.
        $this->permissions[$account->uid] = $this->permissions[$account->uid]['permission'];
      }
    }

    return $this->permissions[$account->uid];
  }

  /**
   * Check if the user has list permissions.
   *
   * @param string $permission
   *   The permission.
   * @param object $account
   *   The user.
   *
   * @return bool
   *   TRUE or FALSE depending on the permission exists.
   */
  public function hasPermission($permission, $account = NULL) {
    $user_permission = $this->getPermission($account);

    if (!$user_permission) {
      return FALSE;
    }

    return in_array($permission, ding_list_get_permission_permissions($user_permission));
  }

  /**
   * Check if a user is the owner of the list.
   *
   * @param object $account
   *   User object.
   *
   * @return bool
   *   TRUE if the user is the owner.
   */
  public function isOwner($account = NULL) {
    if ($account === NULL) {
      global $user;
      $account = $user;
    }

    $account_openlist_id = ding_provider_invoke('openlist', 'user_identifier', $account);

    return $account_openlist_id == $this->getOwner();
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
   * @return DingList
   *   Chainable.
   */
  public function setId($value) {
    $this->id = $value;

    return $this;
  }

  /**
   * Getter for title.
   *
   * @return string
   *   The value.
   */
  public function getTitle() {
    return $this->title;
  }

  /**
   * Setter for title.
   *
   * @param string $value
   *   The new value.
   *
   * @return DingList
   *   Chainable.
   */
  public function setTitle($value) {
    $this->title = $value;

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
   * @return DingList
   *   Chainable.
   */
  public function setType($value) {
    $this->type = $value;

    return $this;
  }

  /**
   * Getter for owner.
   *
   * @return string
   *   The value.
   */
  public function getOwner() {
    return $this->owner;
  }

  /**
   * Setter for owner.
   *
   * @param string $value
   *   The new value.
   *
   * @return DingList
   *   Chainable.
   */
  public function setOwner($value) {
    $this->owner = $value;

    return $this;
  }

  /**
   * Getter for note.
   *
   * @return string
   *   The value.
   */
  public function getNote() {
    return $this->note;
  }

  /**
   * Setter for note.
   *
   * @param string $value
   *   The new value.
   *
   * @return DingList
   *   Chainable.
   */
  public function setNote($value) {
    $this->note = $value;
    $this->data['note'] = $value;

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
   * @return DingList
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

  /**
   * Check if the list has a specific data key.
   *
   * @param string $key
   *   Key to look for.
   *
   * @return bool
   *   TRUE if the data key exists.
   */
  public function hasData($key) {
    return isset($this->data[$key]);
  }

  /**
   * Getter for elements.
   *
   * @param int $offset
   *   Start of the sequence.
   * @param int|null $count
   *   Number of elements to get.
   *   Set this to NULL to get the rest elements.
   *
   * @return DingListElement[]
   *   The elements. Element ids are used as keys.
   */
  public function getElements($offset = 0, $count = NULL) {
    if ($count === NULL || $count + $offset > $this->elementCount) {
      $count = $this->elementCount - $offset;
    }

    if (count($this->elements) < $offset + $count) {
      $service_offset = count($this->elements);
      $service_count = ($offset + $count) - $service_offset;

      $elements = ding_provider_invoke('openlist', 'get_list_elements', $this, $service_offset, $service_count);
      foreach ($elements as $element) {
        $this->attachElement($element, TRUE);
      }
    }
    $result = array_slice($this->elements, $offset, $count, TRUE);

    return $result;
  }

  /**
   * Getter for elementCount.
   */
  public function getElementCount() {
    return $this->elementCount;
  }

  /**
   * Setter for elementCount.
   */
  public function setElementCount($value) {
    $this->elementCount = $value;
    return $this;
  }

  /**
   * Remove a specific element from the element list.
   *
   * @param DingListElement $element
   *   The element.
   *
   * @return DingList
   *   Chainable.
   */
  public function removeElement(DingListElement $element) {
    unset($this->elements[$element->id]);
    return $this;
  }

  /**
   * Add an element to the list.
   *
   * @param DingListElement $element
   *   Elemen to add.
   * @param bool $existing
   *   If the element already exists at the provider set the to TRUE. This will
   *   make sure the elementCount is correct.
   *
   * @return DingListElement
   *   Returns the same element given.
   */
  public function attachElement(DingListElement $element, $existing = FALSE) {
    $element->setListId($this->id);
    $this->elements[$element->getId()] = $element;
    if ($existing === FALSE) {
      $this->elementCount += 1;
    }
    return $element;
  }

}
