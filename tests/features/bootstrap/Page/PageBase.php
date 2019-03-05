<?php

namespace Page;

use SensioLabs\Behat\PageObjectExtension\PageObject\Page;
use SensioLabs\Behat\PageObjectExtension\PageObject\Exception\UnexpectedPageException;

class PageBase extends Page
{

    /**
     * Checks if the current Mink page matches this object.
     */
    public function verifyCurrentPage()
    {
        $currentUrl = $this->getDriver()->getCurrentUrl();
        // Replace placeholders with regexps. We have to match on quoted
        // placeholdes as preg_quote quotes them (naturally).
        $quotedPath = preg_replace('/\\\{.*?\\\}/', '[^/]+', preg_quote($this->path, '@'));
        $urlRegex = preg_quote(rtrim($this->getParameter('base_url'), '/'), '@') . $quotedPath;

        if (!preg_match('@' . $urlRegex . '@', $currentUrl)) {
            throw new UnexpectedPageException(sprintf('URL "%s" does not match path "%s"', $currentUrl, $this->path));
        }

        return $this;
    }

    public function waitForPopup()
    {
        $this->waitFor(10, function ($page) {
            return $page->find('css', '.ui-dialog');
        });
    }

    /**
     * Wait for page to load.
     */
    public function waitForPage()
    {
        try {
            // Strictly, this waits for jQuery to be loaded, but it seems
            // sufficient.
            $this->getSession()->wait(5000, 'typeof window.jQuery == "function"');
        } catch (UnsupportedDriverActionException $e) {
            // Ignore.
        } catch (Exception $e) {
            throw new Exception('Unknown error waiting for page');
        }
    }
}
