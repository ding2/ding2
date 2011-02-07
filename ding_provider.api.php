<?php

/**
 * @file
 * Documentation for ding_provider API.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Implement this hook to tell ding_provider that this module
 * implements a/some given provider.
 *
 * @return
 *
 *   An array of information about the module's providers. The array
 *   contains a sub-array of providers with the key being the provider
 *   name. The sub-array may have these attributes:
 *   - "title": The human-readable name for this provider. Required.
 *   - "prefix": An optional prefix for the methods in this provider.
 *      For instance, if the prefix for this provider is 'user', and the
 *      provider function to be called is 'is_logged_in', then
 *      ding_provider will attempt to call the
 *      <module name>_user_is_logged_in function.
 *   - "file": File to be included before calling this function. Optional.
 */
function hook_ding_provider() {
  return array(
    'availability' => array(
      'title' => 'Ding provider test availability provider',
      'prefix' => 'availability',
    ),
  );
}

/**
 * @} End of "addtogroup hooks".
 */
