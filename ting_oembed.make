api = 2
core = 7.x

; Projects
projects[oembed][subdir] = "contrib"
projects[oembed][version] = "1.0-rc2"
; Remove hook_system_info_alter() to allow installing modules depending on oembed, after oembed is installed.
projects[oembed][patch] = "http://www.drupal.org/files/issues/oembed-remove_hook_sytem_info_alter-2502817-1.patch"

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.5"

projects[features][subdir] = "contrib"
projects[features][version] = "2.0"

projects[field_group][subdir] = "contrib"
projects[field_group][version] = "1.1"

projects[virtual_field][subdir] = "contrib"
projects[virtual_field][version] = "1.2"
