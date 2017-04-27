<?php

namespace Reload\Prancer;

/**
 * Exception thrown on request errors where a model is available.
 */
class SwaggerApiExtendedError extends SwaggerApiError
{
    public function __construct($payload, $message = "", $code = 0, Throwable $previous = null)
    {
        parent::__construct($message, $code, $previous);
        $this->payload = $payload;
    }

    /**
     * Get the model from the reply.
     */
    public function getPayload()
    {
        return $this->payload;
    }
}
