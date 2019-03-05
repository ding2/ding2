<?php
/**
 * @file
 * Base for unittests in ding.
 *
 * The base-class ensures that eg. prophecy is available during tests.
 */

namespace Drupal\ding_test;

use Drupal\xautoload\ClassLoader\ClassLoaderInterface;
use DrupalUnitTestCase;

/**
 * Base class for unit tests which rely on XAutoload for class loading.
 */
class DingUnitTestBase extends DrupalUnitTestCase {

  /**
   * @var \Prophecy\Prophet
   */
  protected $prophet;

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    // We depend on xautoload, so it has already been loaded by core as we have
    // a dependency on it.
    // It is not registered as the first classloader though, so we have to go
    // in, remove it, and re-register a new instance.
    foreach (spl_autoload_functions() as $callback) {
      if (is_array($callback)
        && ($loader = $callback[0])
        && $loader instanceof ClassLoaderInterface
      ) {
        $loader->unregister();
      }
    }
    xautoload()->finder->register(TRUE);

    // We call parent late to make sure we have our autoloader in place.
    parent::setUp();

    $this->prophet = new \Prophecy\Prophet();
  }
}
