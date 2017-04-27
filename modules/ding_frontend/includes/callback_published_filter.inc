<?php
/**
 * @file
 * This filter excludes unpublished users and content.
 */

/**
 * Class DingFrontendPublishedStateFilter
 */
class DingFrontendPublishedStateFilter extends SearchApiAbstractAlterCallback {
  /**
   * Overrides SearchApiAbstractAlterCallback::supportsIndex().
   */
  public function supportsIndex(SearchApiIndex $index) {
    return TRUE;
  }

  /**
   * Implements SearchApiAlterCallbackInterface::alterItems().
   */
  public function alterItems(array &$items) {
    foreach ($items as $nid => &$item) {
      if (empty($item->{$item->item_type}->status)) {
        unset($items[$nid]);
      }
    }
  }
}
