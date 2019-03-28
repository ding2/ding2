<?php

namespace Page;

use Exception;

class ListPage extends PageBase
{
    /**
     * @var string $path
     */
    protected $path = '/list/{listId}';

    public function isListPageFor($title)
    {
        // @todo check URL.
        $header = $this->find('css', '.ding-list-list__title');
        return $header ? $header->getText() == $title : false;
    }

    protected function getList()
    {
        $list = $this->find('css', '#ding-list-list-elements');
        if (!$list) {
            throw new Exception('No list on page');
        }

        return $list;
    }

    public function getListId()
    {
        if (preg_match('{/list/(\d+)$}', $this->getDriver()->getCurrentUrl(), $matches)) {
            return $matches[1];
        }
        throw new Exception('Not on a list page.');
    }

    public function getMaterial($title) {
        foreach ($this->getItems() as $material) {
            $material_title = $material->find('css', '.field-type-ting-title h2');
            if (!$material_title) {
                throw new Exception("Can't find material title on item");
            }

            if (strpos($material_title->getText(), $title) !== false) {
                return $material;
            }
        }

        throw new Exception("Can't find material \"" . $title . "\" on list");
    }

    public function hasMaterial($title)
    {
        try {
            $this->getMaterial($title);
            return true;
        }
        catch (Exception $e) {
            return false;
        }
    }

    public function removeMaterial($title)
    {
        $removed = false;
        foreach ($this->getItems() as $item) {
            $itemTitle = $item->find('css', '.field-type-ting-title');
            if ($title && (strpos($itemTitle->getText(), $title) !== false)) {
                // The remove button has no usable classes, hope it's the
                // right one.
                $button = $item->find('css', 'form #edit-submit');
                if ($button) {
                    $button->click();
                    $removed = true;
                }
            }
        }
        if (!$removed) {
            throw new Exception('Could not find remove button');
        }
    }

    /**
     * Check if list has an item with specified title.
     */
    public function hasItem(string $title)
    {
        foreach ($this->getItems() as $item) {
            $itemTitle = $this->find('css', '.ding-list-element__title');
            if (!$itemTitle) {
                throw new Exception("Can't find item title on page");
            }

            if (strpos($itemTitle->getText(), $title) !== false) {
                return true;
            }
        }

        return false;
    }

    /**
     * Remove an item by title.
     */
    public function removeItem(string $title)
    {
        $removed = false;
        foreach ($this->getItems() as $item) {
            $itemTitle = $item->find('css', '.ding-list-element__title');
            if (!$itemTitle) {
                throw new Exception("Can't find item title on page");
            }

            if ((strpos($itemTitle->getText(), $title) !== false)) {
                // The remove button has no usable classes, hope it's the
                // right one.
                $button = $item->find('css', 'input[type=submit]');
                if ($button) {
                    $button->click();
                    $removed = true;
                }
            }
        }
        if (!$removed) {
            throw new Exception('Could not find remove button');
        }
    }

    public function getItems() {
        $list = $this->getList();

        return $list->findAll('css', 'tr');
    }
}
