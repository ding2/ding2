api = 2
core = 7.x

; Ding! 2 modules

projects[ding_content][type] = module
projects[ding_content][download][type] = git
projects[ding_content][download][url] = git@github.com:ding2/ding_content.git
projects[ding_content][download][tag] = "7.x-0.15"

projects[ding_page][type] = "module"
projects[ding_page][download][type] = "git"
projects[ding_page][download][url] = "git@github.com:ding2/ding_page.git"
projects[ding_page][download][tag] = "7.x-0.12"

projects[ting_reference][type] = module
projects[ting_reference][download][type] = git
projects[ting_reference][download][url] = git@github.com:ding2/ting_reference.git
projects[ting_reference][download][tag] = "7.x-0.18"

; Contrib modules

projects[cache_actions][type] = module
projects[cache_actions][subdir] = contrib
projects[cache_actions][version] = 2.0-alpha3

projects[ctools][type] = "module"
projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.0-rc1"
projects[ctools][patch][] = "http://drupal.org/files/issues/user_edit_form-p0-format-1184168.patch"

projects[features][type] = module
projects[features][subdir] = contrib
projects[features][version] = 1.0-beta4

; Changed to download as git repository due to failing when applying
; patch when version of git is lower than 1.7.5.4 and option working-copy
; is enabled
projects[og][type] = module
projects[og][subdir] = contrib
projects[og][download][type] = git
projects[og][download][url] = http://git.drupal.org/project/og.git
projects[og][download][tag] = 7.x-1.3
projects[og][patch][] = http://drupal.org/files/1320778.patch

projects[similarterms][type] = module
projects[similarterms][subdir] = contrib
projects[similarterms][download][type] = git
projects[similarterms][download][url] = http://git.drupal.org/project/similarterms.git
projects[similarterms][download][revision] = d0f10f5fdcb3a16855cff93094c4139a32e585f6
projects[similarterms][patch][] = https://raw.github.com/ding2/patches/master/similarterms-combined-patches.patch

projects[strongarm][type] = module
projects[strongarm][subdir] = contrib
projects[strongarm][version] = 2.0-beta4

projects[views][type] = module
projects[views][subdir] = contrib
projects[views][version] = 3.0
