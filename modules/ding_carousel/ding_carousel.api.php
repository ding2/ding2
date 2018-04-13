<?php

/**
 * @file
 * Hooks provided by the ding_carousel module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Allows modules to provide extra transitions for the carousel.
 *
 * See ding_carousel.js for some examples implementations.
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
    ),
  );
}

/**
 * @} End of "addtogroup hooks".
 */
