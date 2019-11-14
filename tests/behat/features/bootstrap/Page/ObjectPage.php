<?php
/**
 * @file
 * Implements page showing an object.
 */

namespace Page;

/**
 * Class ObjectPage
 *
 * @package Page
 */
class ObjectPage extends PageBase
{
    /**
     * Path.
     *
     * @var string $path
     */
    protected $path = '/ting/object/{id}';

    /**
     * EntryIsShown.
     *
     * @param string $relType
     *    Popular name for a relationtype to be found.
     *
     * @return string
     *    Nonempty if it cannot be found.
     */
    public function entryIsShown($relType)
    {
        $relationType = $this->convertRelationTypeToTechnicalTerm($relType);
        $found = $this->find('css', '.ting-object ' . $relationType);
        if ($found === null) {
            return "Could not find entry: " . $relationType;
        }
        return "";
    }

    /**
     * Entry Is Not Shown.
     *
     * @param string $relType
     *    Relationtype that must not be shown.
     *
     * @return string
     *    Nonempty if it is shown.
     */
    public function entryIsNotShown($relType)
    {
        $relationType = $this->convertRelationTypeToTechnicalTerm($relType);

        $found = $this->find('css', '.ting-object ' . $relationType);
        if ($found !== null) {
            return "Found a " . $relationType . " unexpectedly. Is your file updated?";
        }
        return "";
    }

    /**
     * Convert Relation to Technical Term.
     *
     * @param string $relType
     *    Relationtype to be converted.
     *
     * @return string
     *    Technical term for relation.
     */
    private function convertRelationTypeToTechnicalTerm($relType)
    {
        $relationType = "";
        switch (strtolower($relType)) {
            case 'hasreview':
                $relationType = 'div[id="dbcaddi:hasReview"]';
                break;

            case 'hascreatordescription':
                $relationType = 'div[id="dbcaddi:hasCreatorDescription"]';
                break;

            case 'hasplacement':
                $relationType = 'div.group-holdings-available a';
                break;

            case 'hasdetails':
            case 'hasobjectdetails':
                $relationType = 'div.group-material-details a';
                break;
        }
        if ($relationType == "") {
            return "Error: Could not decipher the relationtype " . $relType .
                "\n(Knowns are 'hasReview', 'hasCreatorDescription', 'hasDetails', 'hasPlacement').";
        }
        return $relationType;
    }

    /**
     * Has Cover Page.
     *
     * @return string
     *    Nonempty if coverpage is not found.
     */
    public function hasCoverPage()
    {
        $coverimg = $this->find('xpath', '//div[contains(@class,"ting-cover")]/img');
        $txt_cover = "";
        if ($coverimg) {
            $txt_cover = $coverimg->getAttribute('src');
        }
        if (strlen($txt_cover) > 0) {
            return "";
        } else {
            return "Did not find a cover page.";
        }
    }

    /**
     * Has Availability Options.
     *
     * @return string
     *    Nonempty if availability is not shown.
     */
    public function hasAvailabiltyOptions()
    {
        // Simply try to grab the img object.
        $found = $this->find('css', '.ting-object .field-group-format li.availability');
        if ($found === null) {
            return "Could not find availability informations";
        }
        return "";
    }

    /**
     * Has Online Access Options.
     *
     * @return string
     *    Nonempty if online access is not shown.
     */
    public function hasOnlineAccessButton()
    {
        $button = $this->find('css', "a.button-see-online");

        if (!$button) {
            return "Online Access button is not shown";
        }
        return "";
    }

    /**
     * Has Reservation Options.
     *
     * @return string
     *    Nonempty if reservation button is not shown.
     */
    public function hasReservationButton()
    {
        $button = $this->find('css', '.ting-object-inner-wrapper a.reserve-button');
        if (!$button) {
            return "Reservation button was not found";
        }

        $classAttr = $button->getAttribute('class');
        // It takes a bit to add these classes. Wait until they are there.
        // This also covers not-reservable and unavailable, of course. A 5
        // second pause is a tad long, but it caters for slower environments,
        // like upgrade-fbs.
        $max = 3000;
        while (--$max > 0 && (strpos($classAttr, 'reservable') === false ||
                              strpos($classAttr, 'available') === false)) {
            sleep(5);
            $classAttr = $button->getAttribute('class');
        }

        $classes = explode(' ', $classAttr);
        foreach ($classes as $class) {
            if ($class == 'not-reservable') {
                return "Reservation-button is prevented on this object";
            }
        }
        return "";
    }

    /**
     * Attempt to make a reservation.
     *
     * @return string
     *    The status of whether the reservation click could be done.
     *
     * @throws Exception
     *    In case of error.
     */
    public function makeReservation()
    {
        $button = $this->find('xpath', '//a[contains(@class,"reserve-button")]');
        $this->scrollTo($button);
        $button->click();
        return "";
    }
}
