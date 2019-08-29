<?php

/**
 * @file
 * Trait to check if jQuery ajax request have finished loading.
 */
trait AjaxCompleteTrait
{
    /**
     * Wait until all jQuery ajax calls have completed.
     *
     * Uses the 'jQuery.active' property to test if there are outstanding
     * ajax requests.
     *
     * @param int $seconds
     *    The amount of seconds to wait
     */
    public function waitForAjaxCalls($seconds = 5)
    {
        $this->getSession()->getPage()->waitFor($seconds, function () {
            // jQuery.active holds the number of outstanding ajax requests
            return $this->getSession()->getDriver()->evaluateScript('jQuery.active === 0');
        });
    }
}
