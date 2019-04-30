<?php

namespace Page;

use SensioLabs\Behat\PageObjectExtension\PageObject\Exception\UnexpectedPageException;

class P2SearchPage extends PageBase
{
    /**
     * @var string $path
     */
    protected $path = '/search/ting/{string}';

    protected function verifyUrl(array $urlParameters = array())
    {
        try {
            parent::verifyUrl($urlParameters);
        } catch (UnexpectedPageException $e) {
            foreach ($urlParameters as $key => &$value) {
                $value = strtr($value, [' ' => '%20']);
            }
            parent::verifyUrl($urlParameters);
        }
    }

    public function search($string)
    {
        // You'd think we should URL encode this, but that makes it fail on
        // "The hitchhiker's guide to the galaxy".
        $this->open(['string' => $string]);
    }

    public function gotoFirstResultNamed($title)
    {
        $resultContainer = $this->find('css', '.search-results');
        if (!$resultContainer) {
            throw new \Exception('Could not find search result on page');
        }

        $results = $resultContainer->findAll('css', '.ting-object .field-type-ting-title h2 a');
        if (!$results) {
            throw new \Exception('Could not find first search result on page');
        }
        $path = null;
        foreach ($results as $result) {
            if (strpos($result->getText(), $title) !== false) {
                $path = $result->getAttribute('href');
                break;
            }
        }

        if (!$path) {
            throw new \Exception(sprintf('Could not find result named "%s"', $title));
        }

        $baseUrl = rtrim($this->getParameter('base_url'), '/').'/';

        $this->getDriver()->visit($baseUrl . $path);

        $url = $this->getDriver()->getCurrentUrl();
        if (preg_match('{ting/object/}', $url)) {
            return $this->getPage('Material view page');
        } elseif (preg_match('{ting/collection/}', $url)) {
            return $this->getPage('Collection view page');
        } else {
            throw new \Exception(sprintf('Unknown search result page "%s"', $url));
        }
    }
}
