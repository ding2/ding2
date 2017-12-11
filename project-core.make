core = 7.x
api = 2

; Core
projects[drupal][type] = core
projects[drupal][version] = 7.81
projects[drupal][patch][] = "https://drupal.org/files/issues/menu-get-item-rebuild-1232346-45.patch"
projects[drupal][patch][] = "https://www.drupal.org/files/issues/1232416-autocomplete-for-drupal7x53.patch"
projects[drupal][patch][] = "https://drupal.org/files/issues/translate_role_names-2205581-1.patch"
projects[drupal][patch][] = "https://raw.githubusercontent.com/ding2/ding2/master/patches/drupal_core.robots.txt.ding2.patch"
projects[drupal][patch][] = "https://www.drupal.org/files/issues/programatically_added-1079628-29-d7.patch"

; Get the profile, which will contain the next makefile.
projects[ding2][type] = "profile"
projects[ding2][download][type] = "git"
projects[ding2][download][url] = "https://github.com/ding2/ding2.git"
projects[ding2][download][tag] = "7.x-6.4.0-beta1"
