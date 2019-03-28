<?php

namespace Page\Element;

class CreateListForm extends ElementBase
{
    /**
     * @var array|string $selector
     */
    protected $selector = '#ding-list-edit-list-form';

    /**
     * @param string $keywords
     *
     * @return Page
     */
    public function createList($title, $description = '')
    {
        $this->fillField('edit-title', $title);
        $this->fillField('edit-note', $description);

        $button = $this->findButton('edit-save');
        $button->press();

        return $this->getPage('List page');
    }
}
