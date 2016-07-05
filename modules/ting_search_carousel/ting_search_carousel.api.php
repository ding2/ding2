<?php

/**
 * @file
 * Hooks provided by the ting_search_carousel module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Implements hook_ting_search_carousel_transitions().
 */
function hook_ting_search_carousel_transitions() {
  return array(
    'none' => array(
      'name' => t('No transition'),
    ),
    'fade' => array(
      'name' => t('Fade out-in'),
    ),
    'fireworks' => array(
      'name' => t('The most insane transition'),
      'file' => drupal_get_path('module', 'mymodule') . '/js/mymodule.js',
    ),
  );
}


/**
 * @} End of "addtogroup hooks".
 */
