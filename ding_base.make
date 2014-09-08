core = 7.x
api = 2

; Projects
projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.4"

projects[features][subdir] = "contrib"
projects[features][version] = "2.0"

projects[globalredirect][subdir] = "contrib"
projects[globalredirect][version] = "1.5"
projects[globalredirect][patch][] = "http://drupal.org/files/language_redirect_view_node-1399506-2.patch"

projects[jquery_update][subdir] = "contrib"
projects[jquery_update][version] = "2.4"

projects[og][subdir] = "contrib"
projects[og][version] = "2.7"

projects[og_menu][subdir] = "contrib"
projects[og_menu][version] = "3.0-rc5"
; Fixes JavaScript menu selection in edit node forms.
projects[og_menu][patch][0] = "http://drupal.org/files/issues/selector_not_found-2276951-2.patch"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0"

projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.2"

projects[transliteration][subdir] = "contrib"
projects[transliteration][version] = "3.2"

projects[token][subdir] = "contrib"
projects[token][version] = "1.5"

projects[diff][subdir] = "contrib"
projects[diff][version] = "3.2"
