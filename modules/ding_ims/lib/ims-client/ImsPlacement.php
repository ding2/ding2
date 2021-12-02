<?php
/**
 * @file
 * ImsPlacement class.
 */

class ImsPlacement {

  public $materialId;
  public $placement;

  /**
   * ImsPlacement constructor.
   */
  public function __construct($material_id, array $placement) {
    $this->materialId = $material_id;
    $this->placement = $placement;
  }
}
