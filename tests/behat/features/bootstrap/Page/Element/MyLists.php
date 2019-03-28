<?php

namespace Page\Element;

class MyLists extends ElementBase
{
    /**
     * @var array|string $selector
     */
    protected $selector = '.list-links.userlists';

    public function getListIdOf($title)
    {
        $lists = [];
        $liElements = $this->findAll('css', 'ul li');
        foreach ($liElements as $liElement) {
            $a = $liElement->find('css', 'a.signature-label');
            if ($a && preg_match('{/list/(\d+)}', $a->getAttribute('href'), $matches)) {
                $text = trim($a->getText());
                $lists[$text] = $matches[1];
            }
        }
        return isset($lists[$title]) ? $lists[$title] : false;
    }
}
