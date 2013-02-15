api = 2
core = 7.x

; Ting modules

projects[ding_page][type] = "module"
projects[ding_page][download][type] = "git"
projects[ding_page][download][url] = "git@github.com:ding2tal/ding_page.git"
projects[ding_page][download][branch] = "development"

projects[ding_path_alias][type] = module
projects[ding_path_alias][download][type] = git
projects[ding_path_alias][download][url] = git@github.com:ding2tal/ding_path_alias.git
projects[ding_path_alias][download][branch] = "development"

projects[ting_reference][type] = module
projects[ting_reference][download][type] = git
projects[ting_reference][download][url] = git@github.com:ding2tal/ting_reference.git
projects[ting_reference][download][branch] = "development"

; Contrib modules

projects[cache_actions][type] = module
projects[cache_actions][subdir] = contrib
projects[cache_actions][version] = "2.0-alpha5"

projects[ctools][type] = module
projects[ctools][subdir] = contrib
projects[ctools][version] = "1.1"

projects[entity][type] = module
projects[entity][subdir] = contrib
projects[entity][version] = "1.0-rc3"

projects[features][type] = module
projects[features][subdir] = contrib
projects[features][version] = "1.0"

projects[media][type] = module
projects[media][subdir] = contrib
projects[media][version] = "2.0-unstable6"

projects[panels][type] = module
projects[panels][subdir] = contrib
projects[panels][version] = "3.2"
projects[panels][patch][] =  http://drupal.org/files/1649046-form-wrapper-is-where-form-is-now.patch

projects[rules][type] = module
projects[rules][subdir] = contrib
projects[rules][version] = "2.2"

projects[similarterms][type] = module
projects[similarterms][subdir] = contrib
projects[similarterms][download][type] = git
projects[similarterms][download][url] = http://git.drupal.org/project/similarterms.git
projects[similarterms][download][revision] = d0f10f5fdcb3a16855cff93094c4139a32e585f6
projects[similarterms][patch][] = https://raw.github.com/ding2/patches/master/similarterms-combined-patches.patch

projects[strongarm][subdir] = contrib
projects[strongarm][version] = "2.0"

projects[views][type] = module
projects[views][subdir] = contrib
projects[views][version] = "3.3"

projects[workbench][type] = module
projects[workbench][subdir] = contrib
projects[workbench][version] = "1.1"

projects[wysiwyg][type] = module
projects[wysiwyg][subdir] = contrib
projects[wysiwyg][version] = "2.1"

; Libraries

libraries[ckeditor][download][type] = get
libraries[ckeditor][download][url] = http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.6.2/ckeditor_3.6.2.zip
libraries[ckeditor][directory_name] = ckeditor
libraries[ckeditor][destination] = libraries

