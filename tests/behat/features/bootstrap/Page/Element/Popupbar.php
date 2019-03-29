<?php

namespace Page\Element;

class Popupbar extends ElementBase
{
    /**
     * @var array|string $selector
     */
    protected $selector = '#popupbar';

    public function getText()
    {
        $contentElement = $this->find('css', '.popupbar-content');
        if (!$contentElement) {
            throw new \Exception('Could not find popupbar content');
        }
        return $contentElement->getText();
    }
}
