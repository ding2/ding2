<?php
/**
 * @file
 * Implements content page.
 */

namespace Page\Common;

use SensioLabs\Behat\PageObjectExtension\PageObject\Page;

/**
 * Class ContentPage
 *
 * Simple page object to represent any generic page that doesn't have a custom URL-alias.
 * Used to test if
 */
class ContentPage extends Page {
  protected $path = '/content/{title}';
}
