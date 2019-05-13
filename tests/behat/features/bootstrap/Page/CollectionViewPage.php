<?php

namespace Page;

class CollectionViewPage extends PageBase
{
    /**
     * @var string $path
     */
    protected $path = '/ting/collection/{id}';

    /**
     * Goto the first material in the collection.
     */
    public function gotoFirstMateriol()
    {
        $link = $this->find('css', '.ting-collection-wrapper .ting-object .field-name-ting-title a');
        $link->click();
        return $this->getPage('Material view page')->verifyCurrentPage();
    }
}
