<?php

namespace Reload\Prancer\Serializer;

use ArrayObject;
use JsonMapper;
use Reload\Prancer\Serializer;

class JsonMapperSerializer implements Serializer
{
    /**
     * @var JsonMapper
     */
    protected $jsonMapper;

    public function __construct(JsonMapper $jsonMapper)
    {
        $this->jsonMapper = $jsonMapper;
    }

    public function serialize($object)
    {
        return json_encode($object);
    }

    public function unserialize($string, $type)
    {
        $object = json_decode($string);
        if ($object === null) {
            throw new \RuntimeException('Unable to decode string as JSON: ' . $string);
        }

        if (is_array($type) || $type instanceof ArrayAccess) {
            return $this->jsonMapper->mapArray($object, new ArrayObject(), $type[0]);
            
        } else {
            return $this->jsonMapper->map($object, new $type());
        }
    }
}
