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
    return "";
  }

  public function entryIsNotShown($relType) {
    $relationType = $this->convertRelationTypeToTechnicalTerm($relType);

    $found = $this->find('css', '.ting-object div[id="' . $relationType . '"]' );
    if ($found !== null) {
      return "Found a " . $relationType . " unexpectedly. Is your file updated?";
    }
    return "";
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
      return "Could not dechiper the relationtype " . $relType . "\n Use either 'hasReview' or 'hasCreatorDescription'.";
    }
    return $relationType;
  }

  public function hasAddToList() {

    $button = $this->find('xpath', "//div[contains(@class,'ding-list-add-button')]/a[contains(@class,'trigger')]");
    if (!$button) {
      return "Add to list-button is not shown";
    }
    return "";
  }

  public function hasNotAddToList() {
    $button = $this->find('xpath', "//div[contains(@class,'ding-list-add-button')]/a[contains(@class,'trigger')]");
    if ($button) {
      if ($button->isVisible() ) {
        return "Add To List button is visible, and it shouldn't be";
      }
    }
    return "";
  }

  public function hasCoverPage() {

    $coverimg = $this->find('xpath', '//div[contains(@class,"ting-cover")]/img');
    $txt_cover = "";
    if ($coverimg) {
      $txt_cover = $coverimg->getAttribute('src');
    }
    if (strlen($txt_cover)>0) {
      return "";
    } else {
      return "Did not find a cover page.";
    }
  }

  public function hasAvailabiltyOptions() {
    // simply try to grab the img object
    $found = $this->find('css', '.ting-object .field-group-format li.availability');
    if ($found === null) {
      return "Could not find availability informations";
    }
    return "";
  }

  public function hasOnlineAccessButton() {

    $button = $this->find('css', "a.button-see-online");

    if (!$button) {
      return "Online Access button is not shown";
    }
    return "";
  }

  public function hasReservationButton() {

    $button = $this->find('css', '.ting-object-inner-wrapper a.reserve-button');
    if (!$button) {
      return "Reservation button was not found";
    }

    $classAttr = $button->getAttribute('class');
    // it takes a bit to add these classes. Wait until they are there. This also covers not-reservable and unavailable, of course
    $max=3000;
    while (--$max>0 && (strpos($classAttr, 'reservable')===false || strpos($classAttr, 'available')===false)) {
      usleep(10);
      $classAttr = $button->getAttribute('class');
    }

    $classes = explode(' ', $classAttr);
    foreach($classes as $class){
      if ($class == 'not-reservable' ) {
        return "Reservation-button is prevented on this object";
      }
    }
    return "";
  }

  public function makeReservation() {

    $button = $this->find('xpath', '//a[contains(@class,"reserve-button")]');

    $this->scrollTo($button);
    $button->click();
  }
}