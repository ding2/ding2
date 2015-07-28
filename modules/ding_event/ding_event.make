core = 7.x
api = 2

; Projects
projects[ding_page][type] = "module"
projects[ding_page][download][type] = "git"
projects[ding_page][download][url] = "git@github.com:ding2/ding_page.git"
projects[ding_page][download][branch] = "master"

projects[ding_base][type] = "module"
projects[ding_base][download][type] = "git"
projects[ding_base][download][url] = "git@github.com:ding2/ding_base.git"
projects[ding_base][download][branch] = "master"

projects[ding_content][type] = "module"
projects[ding_content][download][type] = "git"
projects[ding_content][download][url] = "git@github.com:ding2/ding_content.git"
projects[ding_content][download][branch] = "master"

projects[ding_frontend][type] = "module"
projects[ding_frontend][download][type] = "git"
projects[ding_frontend][download][url] = "git@github.com:ding2/ding_frontend.git"
projects[ding_frontend][download][branch] = "master"

projects[ting_reference][type] = "module"
projects[ting_reference][download][type] = "git"
projects[ting_reference][download][url] = "git@github.com:ding2/ting_reference.git"
projects[ting_reference][download][branch] = "master"

projects[ding_place2book][type] = "module"
projects[ding_place2book][download][type] = "git"
projects[ding_place2book][download][url] = "git@github.com:ding2/ding_place2book.git"
projects[ding_place2book][download][branch] = "master"

projects[addressfield][subdir] = "contrib"
projects[addressfield][version] = "1.0-beta5"

projects[cache_actions][subdir] = "contrib"
projects[cache_actions][version] = "2.0-alpha5"

projects[cs_adaptive_image][subdir] = "contrib"
projects[cs_adaptive_image][version] = "1.0"

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.5"

projects[date][subdir] = "contrib"
projects[date][version] = "2.8"

projects[features][subdir] = "contrib"
projects[features][version] = "2.0"

projects[features_extra][subdir] = "contrib"
projects[features_extra][version] = "1.0-beta1"

projects[field_group][subdir] = "contrib"
projects[field_group][version] = "1.1"

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

projects[og][subdir] = "contrib"
projects[og][version] = "2.5"
projects[og][patch][] = "https://www.drupal.org/files/issues/entityreference_fields_do_not_validate-2249261-10.patch"
; Fix using organic groups for relationships in views
; https://www.drupal.org/node/1890370
projects[og][patch][] = "https://www.drupal.org/files/issues/add-gid-to-relationship-field-1890370-34.patch"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0"

projects[views][subdir] = "contrib"
projects[views][version] = "3.8"

projects[scheduler][subdir] = "contrib"
projects[scheduler][version] = "1.2"

projects[autosave][subdir] = "contrib"
projects[autosave][version] = "2.2"

projects[views_bulk_operations][subdir] = "contrib"
projects[views_bulk_operations][version] = "3.2"
