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
 * See the Connie module for how to implement different providers.
 *
 * @return
 *   An array of information about what this module provides. The array may
 *   have these attributes:
 *   - "title": The human-readable name for this module. Required.
 *   - "settings": Form id for a form of settings common to all providers
 *      of this module. Optional.
 *   - "file": File to include for the global settings form. Optional.
 *   - "provides": An array of providers. The key is the name and the value
 *      is an array with the following attributes:
 *      - "prefix": An optional prefix for the methods in this provider.
 *         For instance, if the prefix for this provider is 'user', and the
 *         provider function to be called is 'is_logged_in', then
 *         ding_provider will attempt to call the
 *         <module name>_user_is_logged_in function.
 *      - "file": File to be included before calling this function. Optional.
 *
 * @see connie.module
 */
function hook_ding_provider() {
  return array(
    'title' => 'My module',
    'settings' => 'mymodule_global_settings_form',
    'provides' => array(
      'availability' => array(
        'prefix' => 'availability',
        'file' => drupal_get_path('module', 'my_module') . '/mymodule.availability.inc',
      ),
    ),
  );
}

/**
 * Inform ding_provider that a module uses a/some provider.
 *
 * Not required for provider usage, but highly recommended.
 *
 * @return
 *
 *  An array of providers used. The key is the provider name and the value is
 *  an array of information, which may have these attributes:
 *  - "required": Whether this provider is required for the functioning of
 *     this module.
 *  - "install time setup": Whether this providers settings (if any), should
 *     be requested at installation time (if possible).
 */
function hook_ding_provider_user() {
  return array(
    'availability' => array(
      'required' => TRUE,
      'install time setup' => TRUE,
    ),
  );
}

/**
 * @} End of "addtogroup hooks".
 */
