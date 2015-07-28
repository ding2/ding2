api = 2
core = 7.x

; Contrib

projects[varnish][subdir] = "contrib"
projects[varnish][version] = "1.0-beta3"
projects[varnish][patch][0] = "http://drupal.org/files/issues/notification_level_settings-2169271-3.patch"

projects[expire][subdir] = "contrib"
projects[expire][version] = "1.0-beta1"
projects[expire][patch][0] = "https://drupal.org/files/issues/expire-2183995-1.patch"
