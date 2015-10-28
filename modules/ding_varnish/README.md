# Ding Varnish
This module makes it possible to cache pages for logged in users in Varnish by
using to X headers, namely "X-Drupal-Roles" and "X-Drupal-Varnish-Cache". The
first is used in the "Vary" to ensure that the cache is divide into different
bins/hashs based on roles in Drupal.

## Requirements
This requires that the pages that you want to cache are the same for all users
with a given combination of roles, which is the cache in the DDBasic theme.

This module requires changes to the vcl used by varnish, which can be found in
http://raw.github.com/ding2/ding2/development/ding2.vcl.

## Security
To ensure that users not simply sets the X-Drupal-Roles header and get a logged
in version of af page the vcl creates an extra call to get roles. This call is
cached in Varnish as well for 3 minutes and is hashed based on cookies
(session) and user agent string.

# Installation/configuration
Simply enable the module and goto admin/config/development/varnish/ding to
configure the user roles, paths and node types that should trigger the cacheing
of a page.
