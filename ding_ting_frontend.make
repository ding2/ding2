api = 2
core = 7.x

; CONTRIB MODULES
projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.x-dev"
projects[ctools][patch][] = "http://drupal.org/files/issues/0001-No-need-for-hook_search_execute-to-be-executed-twice.patch"

projects[panels][subdir] = "contrib"
projects[panels][version] = "3.0-alpha3"

projects[features][subdir] = "contrib"
projects[features][version] = "1.0-beta2"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0-beta2"

; CUSTOM MODULES
projects[ding_facetbrowser][type] = "module"
projects[ding_facetbrowser][download][type] = "git"
projects[ding_facetbrowser][download][url] = "git@github.com:ding2/ding_facetbrowser.git"

projects[ting_search][type] = "module"
projects[ting_search][download][type] = "git"
projects[ting_search][download][url] = "git@github.com:ding2/ting_search.git"

projects[ting_search_autocomplete][type] = "module"
projects[ting_search_autocomplete][download][type] = "git"
projects[ting_search_autocomplete][download][url] = "git@github.com:ding2/ting_search_autocomplete.git"

projects[ding_availability][type] = "module"
projects[ding_availability][download][type] = "git"
projects[ding_availability][download][url] = "git@github.com:ding2/ding_availability.git"

projects[ting_relation][type] = "module"
projects[ting_relation][download][type] = "git"
projects[ting_relation][download][url] = "git@github.com:ding2/ting_relation.git"

projects[ting_search_autocomplete][type] = "module"
projects[ting_search_autocomplete][download][type] = "git"
projects[ting_search_autocomplete][download][url] = "git@github.com:ding2/ting_search_autocomplete.git"

projects[ding_availability][type] = "module"
projects[ding_availability][download][type] = "git"
projects[ding_availability][download][url] = "git@github.com:ding2/ding_availability.git"

projects[ding_toggle_format][type] = "module"
projects[ding_toggle_format][download][type] = "git"
projects[ding_toggle_format][download][url] = "git@github.com:ding2/ding_toggle_format.git"

projects[ting_covers][type] = "module"
projects[ting_covers][download][type] = "git"
projects[ting_covers][download][url] = "git@github.com:ding2/ting_covers.git"
