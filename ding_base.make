core = 7.x
api = 2

; Projects
projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.3"
projects[ctools][patch][0] = "http://drupal.org/files/ctools-n1925018-12.patch"

projects[features][subdir] = "contrib"
projects[features][version] = "2.0-beta2"

projects[globalredirect][subdir] = "contrib"
projects[globalredirect][version] = "1.5"
projects[globalredirect][patch][] = "http://drupal.org/files/language_redirect_view_node-1399506-2.patch"

projects[jquery_update][subdir] = "contrib"
projects[jquery_update][version] = "2.3"

projects[og][subdir] = "contrib"
projects[og][version] = "2.3"

# This version of og menu contains patches from ding2tal.
projects[og_menu][type] = "module"
projects[og_menu][subdir] = "contrib"
projects[og_menu][download][type] = "git"
projects[og_menu][download][url] = "http://git.drupal.org/project/og_menu.git"
projects[og_menu][download][revision] = "4c1d8dd4c18dc25df12f5e7fabd4dde52dd286f0"
projects[og_menu][patch][0] = "http://drupal.org/files/issues/option_to_hide_create_menu-2139819-2.patch"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0"

projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.2"

projects[transliteration][subdir] = "contrib"
projects[transliteration][version] = "3.1"

projects[token][subdir] = "contrib"
projects[token][version] = "1.5"

projects[diff][subdir] = "contrib"
projects[diff][version] = "3.2"
