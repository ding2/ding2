<?php

namespace Page\Element;

class Popup extends ElementBase
{
    /**
     * @var array|string $selector
     */
    protected $selector = '.ui-dialog';

    public function getTitle()
    {
        $titleElement = $this->find('css', '.ui-dialog-title');
        if (!$titleElement) {
            throw new \Exception('Could not find popup title');
        }
        return $titleElement->getText();
    }

    public function getContentText()
    {
        $contentElement = $this->find('css', '.ui-dialog-content');
        if (!$contentElement) {
            throw new \Exception('Could not find popup content');
        }
        return $contentElement->getText();
    }

}
