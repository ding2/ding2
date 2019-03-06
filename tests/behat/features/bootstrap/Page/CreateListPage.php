<?php

namespace Page;

use SensioLabs\Behat\PageObjectExtension\PageObject\Exception\UnexpectedPageException;

class CreateListPage extends PageBase
{
    /**
     * @var string $path
     */
    protected $path = 'list/create';

    public function verifyCurrentPage()
    {
        // The create page has multiple URLs, try them both.
        try {
            parent::verifyCurrentPage();
        } catch (UnexpectedPageException $e) {
            $this->path = '/list/create';
            parent::verifyCurrentPage();
        }
    }
}
