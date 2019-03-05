<?php

namespace Page\Element;

class CreateListForm extends ElementBase
{
    /**
     * @var array|string $selector
     */
    protected $selector = '#ding-list-create-list-form';

    /**
     * @param string $keywords
     *
     * @return Page
     */
    public function createList($title, $description = '')
    {
        $this->fillField('edit-title', $title);
        $this->fillField('edit-notes', $description);

        $button = $this->findButton('edit-add-list');
        $this->scrollTo($button);
        $button->press();

        return $this->getPage('List page');
    }
}
