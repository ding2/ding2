This modules helps store information about the currently logged in user in a 
secure way. It should boost performance on the user pages (loans and 
reservations) especially for those users with many loans.

To use the module enable it and head over to the performance page at
admin/config/development/performance to setup cache time or disable the 
different caches.

The module uses the users session id to store information and removes the data
when the user logs out. So the cache will not have any effect between logins.