<?php

namespace Reload\Prancer;

interface Serializer
{

    public function serialize($object);

    public function unserialize($string, $type);
}
