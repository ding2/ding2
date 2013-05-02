<?php
/**
 * @file
 * Class definition of ag reservable periodical used when making reservations of
 * a given issue.
 */

/**
 * Implements DingPeriodicalReservable class.
 */
class DingPeriodicalReservable extends DingReservationReservableEntity {
  /**
   * Default constructor.
   * 
   * @param type $id
   *  Id for the periodical issue from the provider.
   * @param type $volume
   *  The volume the issue is belonging to.
   * @param type $issue
   *  The issue from the provider
   * @param type $entity
   *  The ding entity that repesents the periodical.
   */
  public function __construct($id, $volume, $issue, $entity) {
    $this->id = $id;
    $this->volume = $volume;
    $this->issue = $issue;
    $this->entity = $entity;
  }

  /**
   * Gets the provider id based on the provider.
   * 
   * @return string
   *  The id for the issue. 
   */
  public function getProviderId() {
    $type = ding_provider_get_provider_module_name('reservation');
    switch ($type) {
      case 'openruth':
        return array($this->entity->provider_id, $this->id);
      default:
        return $this->id;
    }
  }

  /**
   * Returns the entity that repesents this issue.
   * 
   * @return DingEntity
   */
  public function getEntity() {
    return $this->entity;
  }

  /**
   * The periodical title with volume and issue information.
   * 
   * @return string 
   */
  public function getTitle() {
    $title = '@title, vol @volume';
    $title .= !empty($this->issue) ? ', issue @issue' : '';

    return t($title, array('@title' => $this->entity->title, '@volume' => $this->volume, '@issue' => $this->issue));
  }
}
