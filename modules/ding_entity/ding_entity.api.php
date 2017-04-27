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
