<?php

namespace Reload\Prancer;

use Psr\Http\Message\RequestInterface;
use Psr\Http\Message\ResponseInterface;

interface HttpClient
{
    /**
     * Make a request to a service.
     *
     * @param Psr\Http\Message\RequestInterface $request
     *   Request to perform.
     *
     * @return Psr\Http\Message\ResponseInterface
     */
    public function request(RequestInterface $request);
}
