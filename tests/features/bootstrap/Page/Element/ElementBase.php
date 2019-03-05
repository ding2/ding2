<?php

namespace Page\Element;

use Behat\Mink\Element\ElementInterface;
use Behat\Mink\Exception\UnsupportedDriverActionException;
use SensioLabs\Behat\PageObjectExtension\PageObject\Element;

class ElementBase extends Element
{
    /**
     * Scroll to an element.
     *
     * @param ElementInterface $element
     *   Element to scroll to.
     *
     * @todo too generic for this class.
     */
    public function scrollTo(ElementInterface $element)
    {
        // Quote quotes and remove newlines.
        $xpath = strtr($element->getXpath(), ['"' => '\\"', "\n" => ' ']);
        $script = 'jQuery(document).scrollTo(document.evaluate("' . $xpath . '", document, null, XPathResult.FIRST_ORDERED_NODE_TYPE, null ).singleNodeValue);';
        try {
            $this->getSession()->evaluateScript($script);
        } catch (UnsupportedDriverActionException $e) {
            // Ignore.
        } catch (Exception $e) {
            throw new Exception('Could not scroll to element');
        }
    }
}
