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
function hook_ding_entity_buttons($type, $entity, $view_mode, $widget) {
  if ($type == 'ding_entity' && $entity->is('reservable')) {
    return array(ding_provider_get_form('ding_reservation_reserve_form', new DingReservationReservableEntity($entity), TRUE));
  }
}

/**
 * Help determine whether entities belongs to given pseudo-classes.
 *
 * Note that there's also a single entity version of this hook named
 * hook_ding_entity_is(), which is invoked from within a ding entity object and
 * therefore only support one entity at a time. This hook is therefore better to
 * implement if acting on multiple entities and the implementation can achieve
 * better performance by recieving all entities at once.
 *
 * @param array $entities
 *   The entities that needs to be checked against the pseudo-class.
 * @param string $class
 *   The pseudo class to check for.
 *
 * @return array
 *   The implementation must return an array with an entry for each of the
 *   passed entities keyed by their ding_entity_id. If the implementation
 *   doesn't have a say for a particular entity and/or pseudo-class it must set
 *   NULL to return something for that entity and signal that it is neutral.
 */
function hook_ding_entity_entities_is(array $entities, $class) {
  $return = [];
  // Loop through each passed entity and check if it belongs to $class.
  foreach ($entities as $entity) {
    // Here we check if the entities belong to a pseudo class called 'book' to
    // give an example, but it could be anything. This way the implementation
    // can "invent" and add new pseudo-classes just by implementing this hook.
    if ($class == 'book') {
      // If we are certain this entity belongs to the pseudo class set TRUE:
      if ($entity->getType() == 'book') {
        $return[$entity->ding_entity_id] = TRUE;
      }
      // If we are absolutely certain this entity does not belong to the class and
      // wanna overwrite any module who says so, we set FALSE for this entity:
      elseif (strpos($entity->getType(), 'book') === FALSE) {
        $return[$entity->ding_entity_id] = FALSE;
      }
    }
    if (!isset($return[$entity->ding_entity_id])) {
      // If we don't know about the pseudo class or don't have sufficient
      // information about the entity to have a say, we can set a neutral response
      // by setting NULL for this entity. This way we don't interfere with the
      // final outcome and leaves more flexibility to other modules.
      $return[$entity->ding_entity_id] = NULL;
    }
  }
  return $return;
}

/**
 * @} End of "addtogroup hooks".
 */
