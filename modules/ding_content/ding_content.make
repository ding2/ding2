core = 7.x
api = 2

; Projects

projects[cache_actions][subdir] = "contrib"
projects[cache_actions][version] = "2.0-alpha5"

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.5"

projects[entity][subdir] = "contrib"
projects[entity][version] = "1.5"

projects[features][subdir] = "contrib"
projects[features][version] = "2.0"

projects[features_extra][subdir] = "contrib"
projects[features_extra][version] = "1.0-beta1"

; This version of media is tested to work with both images and videos.
projects[media][type] = "module"
projects[media][subdir] = "contrib"
projects[media][download][type] = "git"
projects[media][download][url] = "http://git.drupal.org/project/media.git"
projects[media][download][revision] = "c3cda2b"
; Fixed issue where "insert" fails, see https://www.drupal.org/node/2184475.
projects[media][patch][] = "https://www.drupal.org/files/issues/media_popup_trigger_some_js-2184475-6.patch"

projects[file_entity][subdir] = "contrib"
projects[file_entity][version] = "2.0-alpha3"

projects[panels][subdir] = "contrib"
projects[panels][version] = "3.4"

projects[rules][subdir] = "contrib"
projects[rules][version] = "2.7"

projects[similarterms][subdir] = "contrib"
projects[similarterms][version] = "2.3"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0"

projects[views][subdir] = "contrib"
projects[views][version] = "3.8"

projects[workbench][subdir] = "contrib"
projects[workbench][version] = "1.2"

; This revision support the CKEditor 4.x, and can be used until a new version is tagged.
projects[wysiwyg][type] = "module"
projects[wysiwyg][subdir] = "contrib"
projects[wysiwyg][download][type] = "git"
projects[wysiwyg][download][url] = "http://git.drupal.org/project/wysiwyg.git"
projects[wysiwyg][download][revision] = "7981731f4f3db2f932419499d2ec13a073e9b88f"

projects[media_vimeo][subdir] = "contrib"
projects[media_vimeo][version] = "2.0-rc1"

projects[media_youtube][type] = "module"
projects[media_youtube][subdir] = "contrib"
projects[media_youtube][download][type] = "git"
projects[media_youtube][download][url] = "http://git.drupal.org/project/media_youtube.git"
projects[media_youtube][download][revision] = "ca46aba"
projects[media_youtube][patch][] = "http://drupal.org/files/issues/provide-access-wrapper-1823376-6.patch"

projects[node_clone][subdir] = "contrib"
projects[node_clone][version] = "1.0-rc2"

projects[image_resize_filter][subdir] = "contrib"
projects[image_resize_filter][version] = "1.14"

; Libraries
libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = http://download.cksource.com/CKEditor/CKEditor/CKEditor%204.4.7/ckeditor_4.4.7_full.zip
libraries[ckeditor][directory_name] = "ckeditor"
libraries[ckeditor][destination] = "libraries"

; ding2

projects[ding_page][type] = "module"
projects[ding_page][download][type] = "git"
projects[ding_page][download][url] = "git@github.com:ding2/ding_page.git"
projects[ding_page][download][branch] = "master"

