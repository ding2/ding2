<?php

namespace Reload\Prancer;

use Reload\Prancer\Serializer;
use Reload\Prancer\SwaggerApiRequest;
use Phly\Http\Request;
use Psr\Http\Message\ResponseInterface;

class SwaggerApi
{
    /**
     * @var string
     */
    protected $endpoint;

    /**
     * @var HttpClient
     */
    protected $client;

    /**
     * @var Serializer
     */
    protected $serializer;

    public function __construct($endpoint, HttpClient $client, Serializer $serializer)
    {
        $this->endpoint = $endpoint;
        $this->client = $client;
        $this->serializer = $serializer;
    }

    protected function newRequest($method, $path)
    {
        return new SwaggerApiRequest($this->endpoint, $this->client, $this->serializer, $method, $path);
    }
}
