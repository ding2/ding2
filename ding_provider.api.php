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
 * implements one or more providers.
 *
 * See the dp_example module for how to implement different providers.
 *
 * @return
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
 *
 * @see dp_example.module
 */
function hook_ding_provider() {
  return array(
    'availability' => array(
      'title' => 'My availability provider',
      'prefix' => 'availability',
      'file' => drupal_get_path('module', 'my_module') .  '/mymodule.availability.inc',
    ),
  );
}

/**
 * @} End of "addtogroup hooks".
 */
