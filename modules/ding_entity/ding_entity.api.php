<?php

/**
 * @file
 * Hooks provided by the Ding Entity module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Add local menu tasks to ding_entities.
 *
 * This hook allows modules to add local tasks to ding_entities,
 * regardless of which module provides the entity implementation.
 *
 * @param &$items
 *   The menu items already defined. The place to add items.
 * @param $type
 *   Type of the objects to add menus for (ding_entity or
 *   ding_entity_collection).
 * @param $path
 *   Base path of the object type.
 * @param $index
 *   Index of the object loader in the path.
 */
function hook_ding_entity_menu(&$items, $type, $path, $index) {
  if ($type == 'ding_entity') {
    $items[$path . '/reserve'] = array(
      'title' => t('Reserve'),
      'page callback' => 'ding_provider_get_form',
      'page arguments' => array('ding_reservation_reserve_form', $index),
      'access callback' => TRUE,
    );
  }
}

/**
 *
 */
function hook_ding_entity_view(&$object, $view_mode) {

}

/**
 *
 */
function hook_ding_entity_collection_view(&$object, $view_mode) {

}

/**
 * Tell ding_entity about ding_entity fields, so it can create the
 * proper fields and instances.
 *
 * @return
 *   An array whose keys are the names of the field, and the value is
 *   an array with the following key value pairs:
 *   - field: An array of field settings, as accepted by
 *     field_create_field. field_name and type defaults to the same as
 *     the name of the field.
 *   - instance: Instance settings, as accepted by
 *     field_create_instance, with the difference that entity_type and
 *     bundle will be set automatically depending on ding_entity_type,
 *     and ding_entity_type itself that defaults to 'ding_entity'.
 */
function hook_ding_entity_fields() {
  return array(
    'ding_availability_item' => array(
      'field' => array(
        'type' => 'ding_availability_item',
        'locked' => TRUE,
        'storage' => array(
          'type' => 'virtual_field',
        ),
      ),
      'instance' => array(
        'label' => t('Availability information'),
      ),
    ),
    'ding_availability_holdings' => array(
      'field' => array(
        'type' => 'ding_availability_holdings',
        'locked' => TRUE,
        'storage' => array(
          'type' => 'virtual_field',
        ),
      ),
      'instance' => array(
        'label' => t('Holdings information'),
      ),
    ),
  );
}

/**
 * Add buttons to an ding entity.
 *
 * Return an array of buttons to add.
 */
function hook_ding_entity_buttons($type, $entity) {
  if ($type == 'ding_entity' && $entity->is('reservable')) {
    return array(ding_provider_get_form('ding_reservation_reserve_form', new DingReservationReservableEntity($entity), TRUE));
  }
}

/**
 * @} End of "addtogroup hooks".
 */
