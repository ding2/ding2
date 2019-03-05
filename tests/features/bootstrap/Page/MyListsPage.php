<?php

namespace Page;

class MyListsPage extends PageBase
{
    /**
     * @var string $path
     */
    protected $path = '/user';

    public function getLists()
    {
        return $this->getElement('MyLists');
    }

    public function getListIdOf($title)
    {
        return $this->getLists()->getListIdOf($title);
    }
}
