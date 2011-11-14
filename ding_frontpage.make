api = 2
core = 7.x

; Contrib modules

projects[cache_actions][type] = module
projects[cache_actions][subdir] = contrib
projects[cache_actions][version] = 2.0-alpha3

projects[ctools][type] = "module"
projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.0-rc1"
projects[ctools][patch][] = "http://drupal.org/files/issues/user_edit_form-p0-format-1184168.patch"

projects[ting_search_carousel][type] = "module"
projects[ting_search_carousel][download][type] = "git"
projects[ting_search_carousel][download][url] = "git@github.com:ding2/ting_search_carousel.git"
