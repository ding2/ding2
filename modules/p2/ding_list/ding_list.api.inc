<?php

/**
 * @file
 * API documentation.
 */

/**
 * Add new list types with allowed operations to the current list types.
 *
 * The returned array is mapped by the list type name, and then a list of
 * operations allowed.
 * There's the default DING_LIST_OPERATION constants, but the module including
 * this hook, can create custom operations, that wont affect the default logic.
 *
 * @return array
 *   The mapped array of new list types.
 */
function hook_ding_list_operations() {
  return array(
    // Create the new list type.
    'my_list_type' => array(
      // The list is deleteable.
      DING_LIST_OPERATION_DELETE => TRUE,

      // The ding list elements type allowed to attach to this list.
      DING_LIST_OPERATION_ATTACH => array('some_type', 'another_type'),

      // And it's allowed to detach elements again.
      DING_LIST_OPERATION_DETACH => TRUE,

      // A custom operation, that needs logic in the custom module.
      'my_list_operation_change_owner' => TRUE,

      // The _data can contain some default information, but it can also hold
      // information used specifically by my_list_type.
      '_data' => array(
        'description' => t('Describe the list type'),
      ),
    ),
  );
}
