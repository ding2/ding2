core = 7.x
api = 2

; Core
projects[drupal][type] = core
projects[drupal][version] = 7.54
projects[drupal][patch][] = http://drupal.org/files/issues/menu-get-item-rebuild-1232346-45.patch
projects[drupal][patch][] = http://drupal.org/files/ssl-socket-transports-1879970-13.patch
projects[drupal][patch][] = http://drupal.org/files/issues/translate_role_names-2205581-1.patch

; Get the profile, which will contain the next makefile.
projects[ding2][type] = "profile"
projects[ding2][download][type] = "git"
projects[ding2][download][url] = "git@github.com:ding2/ding2.git"
projects[ding2][download][tag] = "7.x-4.0.0-beta1"
