<?php

namespace Page;

class ListPage extends PageBase
{
    /**
     * @var string $path
     */
    protected $path = '/list/{listId}';

    public function isListPageFor($title)
    {
        // @todo check URL.
        $header = $this->find('css', '.primary-content h2.pane-title');
        return $header ? $header->getText() == $title : false;
    }

    protected function getList()
    {
        $list = $this->find('css', '#ding-list');
        if (!$list) {
            throw new \Exception('No list on page');
        }

        return $list;
    }

    public function getListId()
    {
        if (preg_match('{/list/(\d+)$}', $this->getDriver()->getCurrentUrl(), $matches)) {
            return $matches[1];
        }
        throw new \Exception('Not on a list page.');
    }

    public function hasMaterial($title)
    {
        $list = $this->getList();

        $materials = $list->findAll('css', '.ting-object');
        foreach ($materials as $material) {
            $material_title = $this->find('css', '.field-type-ting-title h2');
            if (!$material_title) {
                throw new \Exception("Can't find material title on page");
            }

            if (strpos($material_title->getText(), $title) !== false) {
                return true;
            }
        }

        return false;
    }

    public function removeMaterial($title)
    {
        $list = $this->getList();

        $items = $list->findAll('css', '.ding-type-ding-list-element');
        $removed = false;
        foreach ($items as $item) {
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
}
