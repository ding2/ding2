api = 2
core = 7.x

projects[cs_adaptive_image][subdir] = "contrib"
projects[cs_adaptive_image][version] = "1.0"

projects[nodequeue][subdir] = "contrib"
projects[nodequeue][version] = "2.0-beta1"

projects[entityreference][subdir] = "contrib"
projects[entityreference][version] = "1.1"

projects[features][subdir] = "contrib"
projects[features][version] = "2.0"

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

projects[views][subdir] = "contrib"
projects[views][version] = "3.8"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0"

projects[ding_library][type] = "module"
projects[ding_library][download][type] = "git"
projects[ding_library][download][url] = "git@github.com:ding2/ding_library.git"
projects[ding_library][download][branch] = "master"
