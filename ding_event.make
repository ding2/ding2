api = 2
core = 7.x

; Ding 2 modules

projects[ding_page][type] = "module"
projects[ding_page][download][type] = "git"
projects[ding_page][download][url] = "git@github.com:ding2tal/ding_page.git"
projects[ding_page][download][branch] = "development"

projects[ding_base][type] = "module"
projects[ding_base][download][type] = "git"
projects[ding_base][download][url] = "git@github.com:ding2tal/ding_base.git"
projects[ding_base][download][branch] = "development"

projects[ding_content][type] = module
projects[ding_content][download][type] = git
projects[ding_content][download][url] = git@github.com:ding2tal/ding_content.git
projects[ding_content][download][branch] = "development"

projects[ding_frontend][type] = "module"
projects[ding_frontend][download][type] = "git"
projects[ding_frontend][download][url] = "git@github.com:ding2tal/ding_frontend.git"
projects[ding_frontend][download][branch] = "development"

projects[ding_user_roles][type] = "module"
projects[ding_user_roles][download][type] = "git"
projects[ding_user_roles][download][url] = "git@github.com:ding2tal/ding_user_roles.git"
projects[ding_user_roles][download][branch] = "development"

projects[ting_reference][type] = module
projects[ting_reference][download][type] = git
projects[ting_reference][download][url] = git@github.com:ding2tal/ting_reference.git
projects[ting_reference][download][branch] = "development"

projects[ding_place2book][type] = module
projects[ding_place2book][download][type] = "git"
projects[ding_place2book][download][url] = "git@github.com:vejlebib/ding_place2book.git"
projects[ding_place2book][download][branch] = "ding2tal_compatibility"


; Contrib modules

projects[addressfield][subdir] = contrib
projects[addressfield][version] = "1.0-beta3"

projects[cache_actions][subdir] = contrib
projects[cache_actions][version] = "2.0-alpha5"

projects[cs_adaptive_image][subdir] = contrib
projects[cs_adaptive_image][version] = "1.0"

projects[ctools][subdir] = contrib
projects[ctools][version] = "1.1"

projects[date][subdir] = contrib
projects[date][version] = "2.6"

projects[features][subdir] = contrib
projects[features][version] = "2.0-beta2"

projects[field_group][subdir] = contrib
projects[field_group][version] = "1.1"

projects[media][subdir] = contrib
projects[media][version] = "2.0-unstable7"

projects[file_entity][subdir] = contrib
projects[file_entity][version] = "2.0-unstable7"

; Changed to download as git repository due to failing when applying
; patch when version of git is lower than 1.7.5.4 and option working-copy
; is enabled
projects[og][type] = module
projects[og][subdir] = contrib
projects[og][download][type] = git
projects[og][download][url] = http://git.drupal.org/project/og.git
projects[og][download][tag] = 7.x-1.3
projects[og][patch][] = http://drupal.org/files/1320778.patch

projects[strongarm][subdir] = contrib
projects[strongarm][version] = "2.0"

projects[views][subdir] = contrib
projects[views][version] = "3.3"
