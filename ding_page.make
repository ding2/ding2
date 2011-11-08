api = 2
core = 7.x

; Ding! 2 modules

projects[ding_base][type] = "module"
projects[ding_base][download][type] = "git"
projects[ding_base][download][url] = "git@github.com:ding2/ding_base.git"
projects[ding_base][download][tag] = "7.x-0.3"

projects[ting_reference][type] = module
projects[ting_reference][download][type] = git
projects[ting_reference][download][url] = git@github.com:ding2/ting_reference.git
projects[ting_reference][download][tag] = "7.x-0.7"

; Contrib modules

projects[features][type] = module
projects[features][subdir] = contrib
projects[features][version] = 1.0-beta4

projects[og][type] = module
projects[og][subdir] = contrib
projects[og][version] = 1.3
projects[og][patch][] = http://drupal.org/files/1320778.patch

projects[strongarm][type] = module
projects[strongarm][subdir] = contrib
projects[strongarm][version] = 2.0-beta4

