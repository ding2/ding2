core = 7.x
api = 2

; Core
projects[drupal][type] = core
projects[drupal][version] = 7.75
projects[drupal][patch][] = "https://drupal.org/files/issues/menu-get-item-rebuild-1232346-45.patch"
projects[drupal][patch][] = "https://www.drupal.org/files/issues/1232416-autocomplete-for-drupal7x53.patch"
projects[drupal][patch][] = "https://drupal.org/files/issues/translate_role_names-2205581-1.patch"
projects[drupal][patch][] = "https://raw.githubusercontent.com/ding2/ding2/master/patches/drupal_core.robots.txt.ding2.patch"
projects[drupal][patch][] = "https://www.drupal.org/files/issues/programatically_added-1079628-29-d7.patch"
; Make it possible to set SameSite attribute for Drupal session cookie.
; IMPORTANT: this patch is only compatible with PHP versions < 7.3. If using PHP
; versions >= 7.3 SameSite attribute will not be set. At the time of writing
; there's no working patch for these versions. There's an ongoing discussion
; about how to handle this.
; See: https://www.drupal.org/project/drupal/issues/3170525#comment-13834908.
projects[drupal][patch][] = "https://www.drupal.org/files/issues/2020-09-23/drupal-3170525-8-samesite_cookie_attribute_support_for_legacy_php_versions.patch"

; Get the profile, which will contain the next makefile.
projects[ding2][type] = "profile"
projects[ding2][download][type] = "git"
projects[ding2][download][url] = "https://github.com/ding2/ding2.git"
projects[ding2][download][tag] = "7.x-6.2.1-rc1"
