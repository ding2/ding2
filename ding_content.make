core = 7.x
api = 2

; Projects
projects[ding_page][type] = "module"
projects[ding_page][download][type] = "git"
projects[ding_page][download][url] = "git@github.com:ding2tal/ding_page.git"
projects[ding_page][download][branch] = "development"

projects[ding_path_alias][type] = "module"
projects[ding_path_alias][download][type] = "git"
projects[ding_path_alias][download][url] = "git@github.com:ding2tal/ding_path_alias.git"
projects[ding_path_alias][download][branch] = "development"

projects[cache_actions][subdir] = "contrib"
projects[cache_actions][version] = "2.0-alpha5"

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.3"
projects[ctools][patch][0] = "http://drupal.org/files/ctools-n1925018-12.patch"

projects[entity][subdir] = "contrib"
projects[entity][version] = "1.1"

projects[features][subdir] = "contrib"
projects[features][version] = "2.0-beta2"

projects[features_extra][subdir] = "contrib"
projects[features_extra][version] = "1.0-beta1"

projects[media][type] = "module"
projects[media][download][type] = "git"
projects[media][download][url] = "http://git.drupal.org/project/media.git"
projects[media][download][revision] = "e7be30f"

projects[file_entity][subdir] = "contrib"
projects[file_entity][version] = "2.0-alpha2"

projects[panels][subdir] = "contrib"
projects[panels][version] = "3.3"
projects[panels][patch][0] = "http://drupal.org/files/1649046-form-wrapper-is-where-form-is-now.patch"

projects[rules][subdir] = "contrib"
projects[rules][version] = "2.3"

projects[similarterms][subdir] = "contrib"
projects[similarterms][version] = "2.3"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0"

projects[views][subdir] = "contrib"
projects[views][version] = "3.7"

projects[workbench][subdir] = "contrib"
projects[workbench][version] = "1.2"

projects[wysiwyg][subdir] = "contrib"
projects[wysiwyg][version] = "2.2"

projects[media_vimeo][subdir] = "contrib"
projects[media_vimeo][version] = "2.0-rc1"

projects[media_youtube][subdir] = "contrib"
projects[media_youtube][version] = "2.0-rc3"

; Libraries
libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.6.2/ckeditor_3.6.2.zip"
libraries[ckeditor][directory_name] = "ckeditor"
libraries[ckeditor][destination] = "libraries"
