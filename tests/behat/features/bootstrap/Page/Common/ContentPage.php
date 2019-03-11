<?php
/**
 * @file
 * Implements content page.
 */

namespace Page\Common;

use SensioLabs\Behat\PageObjectExtension\PageObject\Page;

class ContentPage extends Page
{
  protected $path = '/content/{title}';
}
