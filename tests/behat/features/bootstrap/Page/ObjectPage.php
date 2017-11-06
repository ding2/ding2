<?php
/**
 * Created by PhpStorm.
 * User: caf
 * Date: 11/6/17
 * Time: 12:25 AM
 */

namespace Page;


class ObjectPage extends PageBase
{
  /**
   * @var string $path
   */
  protected $path = '/ting/object/%7Bid%7B';

  public function entryIsShown($relType) {
    $relationType = $this->convertRelationTypeToTechnicalTerm($relType);
    $found = $this->find('css', '.ting-object div[id="' . $relationType . '"]' );
    if ($found === null) {
      return "Could not find entry: " . $relationType;
    }
  }

  public function entryIsNotShown($relType) {
    $relationType = $this->convertRelationTypeToTechnicalTerm($relType);

    $found = $this->find('css', '.ting-object div[id="' . $relationType . '"]' );
    if ($found !== null) {
      return "Found a " . $relationType . " unexpectedly. Is your file updated?";
    }
  }

  private function convertRelationTypeToTechnicalTerm($relType)
  {
    $relationType = "";
    switch(strtolower($relType))
    {
      case 'hasreview':
        $relationType = 'dbcaddi:hasReview';
        break;
      case 'hascreatordescription':
        $relationType = 'dbcaddi:hasCreatorDescription';
        break;

    }
    if ($relationType == "") {
      throw new Exception ("Could not dechipher the relationtype " . $relType . "\n Use either 'hasReview' or 'hasCreatorDescription'.");
    }
    return $relationType;
  }
}