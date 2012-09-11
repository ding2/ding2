api = 2
core = 7.x

; Ding! 2 modules

projects[ding_base][type] = "module"
projects[ding_base][download][type] = "git"
projects[ding_base][download][url] = "git@github.com:ding2/ding_base.git"
projects[ding_base][download][tag] = "7.x-0.4"

projects[ting_reference][type] = module
projects[ting_reference][download][type] = git
projects[ting_reference][download][url] = git@github.com:ding2/ting_reference.git
projects[ting_reference][download][tag] = "7.x-0.18"

; Contrib modules

projects[cache_actions][type] = module
projects[cache_actions][subdir] = contrib
projects[cache_actions][version] = "2.0-alpha5"

projects[ctools][subdir] = contrib
projects[ctools][version] = "1.1"

projects[features][type] = module
projects[features][subdir] = contrib
projects[features][version] = "1.0"


; Changed to download as git repository due to failing when applying
; patch when version of git is lower than 1.7.5.4 and option working-copy
; is enabled
projects[og][type] = module
projects[og][subdir] = contrib
projects[og][download][type] = git
projects[og][download][url] = http://git.drupal.org/project/og.git
projects[og][download][tag] = 7.x-1.3
projects[og][patch][] = http://drupal.org/files/1320778.patch

projects[strongarm][type] = module
projects[strongarm][subdir] = contrib
projects[strongarm][version] = "2.0"

