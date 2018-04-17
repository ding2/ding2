<?php

/**
 * @file
 * DingList object interface.
 */

namespace DingList;

/**
 * Interface.
 */
interface DingListInterface {

  /**
   * Save the list.
   *
   * @return string
   *   Title of the list.
   */
  public function save();

}
