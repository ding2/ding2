<?php
/**
 * @file
 * Defines the reservation entities.
 * 
 * @todo: Create "real" entities based on the entity module from drupal core.
 */

/**
 * Interface for reservable items.
 */
interface DingReservationReservable {
  public function getProviderId();
  // @todo, this should be optional.
  public function getEntity();

  /**
   * Returns the title of the reservable entity.
   *
   * @return string
   *   Title or empty string if it cannot be determined.
   */
  public function getTitle();
}

/**
 * A reservable entity.
 *
 * @todo: what type of entity is used here ding_entity or ting_entity?
 */
class DingReservationReservableEntity implements DingReservationReservable {
  public function __construct($entity) {
    $this->entity = $entity;
  }

  public function getProviderId() {
    return isset($this->entity->provider_id) ? $this->entity->provider_id : NULL;
  }

  public function getEntity() {
    return $this->entity;
  }

  /**
   * {@inheritdoc}
   */
  public function getTitle() {
    return empty($this->entity->getTitle()) ? '' : $this->entity->getTitle();
  }
}
