This modules helps store information about the currently logged in user in a 
secure way. It should boost performance on the user pages (loans and 
reservations) especially for those users with many loans.

To use the module enable it and head over to the performance page at
admin/config/development/performance to setup cache time or disable the 
different caches.

The module uses the users session id to store information and removes the data
when the user logs out. So the cache will not have any effect between logins.

Modules that which to use this module have to implement the 
hook_ding_user_cache_defaults.

function hook_ding_user_cache_defaults() {
  return array(
    'titel' => 'My module',
    'enabled' => TRUE,
    'expire' => 0,
  );
}

The the cache set and get functions can be used.

// Try to get data from the cache.
$data = FALSE;
if (module_exists('ding_user_cache')) {
  $data = ding_user_cache_get('my_module', 'list');
}


// Store data in the cache.
if (module_exists('ding_user_cache')) {
  ding_user_cache_set('my_module', 'list', $data);
}
