core = 7.x
api = 2

; Projects
projects[alma][type] = "module"
projects[alma][download][type] = "git"
projects[alma][download][url] = "git@github.com:ding2tal/alma.git"
projects[alma][download][branch] = "development"

projects[ding_devel][type] = "module"
projects[ding_devel][download][type] = "git"
projects[ding_devel][download][url] = "git@github.com:ding2tal/ding_devel.git"
projects[ding_devel][download][branch] = "development"

projects[openruth][type] = "module"
projects[openruth][download][type] = "git"
projects[openruth][download][url] = "git@github.com:ding2tal/openruth.git"
projects[openruth][download][branch] = "development"

projects[ding_frontend][type] = "module"
projects[ding_frontend][download][type] = "git"
projects[ding_frontend][download][url] = "git@github.com:ding2tal/ding_frontend.git"
projects[ding_frontend][download][branch] = "development"

projects[ding_groups][type] = "module"
projects[ding_groups][download][type] = "git"
projects[ding_groups][download][url] = "git@github.com:ding2tal/ding_groups.git"
projects[ding_groups][download][branch] = "development"

projects[ding_user_frontend][type] = "module"
projects[ding_user_frontend][download][type] = "git"
projects[ding_user_frontend][download][url] = "git@github.com:ding2tal/ding_user_frontend.git"
projects[ding_user_frontend][download][branch] = "development"

projects[ding_ting_frontend][type] = "module"
projects[ding_ting_frontend][download][type] = "git"
projects[ding_ting_frontend][download][url] = "git@github.com:ding2tal/ding_ting_frontend.git"
projects[ding_ting_frontend][download][branch] = "development"

#projects[mkdru_ding_frontend][type] = "module"
#projects[mkdru_ding_frontend][download][type] = "git"
#projects[mkdru_ding_frontend][download][url] = "git@github.com:ding2tal/mkdru_ding_frontend.git"
#projects[mkdru_ding_frontend][download][branch] = "development"

projects[ding_content][type] = "module"
projects[ding_content][download][type] = "git"
projects[ding_content][download][url] = "git@github.com:ding2tal/ding_content.git"
projects[ding_content][download][branch] = "development"

projects[ding_example_content][type] = "module"
projects[ding_example_content][download][type] = "git"
projects[ding_example_content][download][url] = "git@github.com:ding2tal/ding_example_content.git"
projects[ding_example_content][download][branch] = "development"

projects[ding_frontpage][type] = "module"
projects[ding_frontpage][download][type] = "git"
projects[ding_frontpage][download][url] = "git@github.com:ding2tal/ding_frontpage.git"
projects[ding_frontpage][download][branch] = "development"

projects[ding_library][type] = "module"
projects[ding_library][download][type] = "git"
projects[ding_library][download][url] = "git@github.com:ding2tal/ding_library.git"
projects[ding_library][download][branch] = "development"

projects[ding_news][type] = "module"
projects[ding_news][download][type] = "git"
projects[ding_news][download][url] = "git@github.com:ding2tal/ding_news.git"
projects[ding_news][download][branch] = "development"

projects[ding_event][type] = "module"
projects[ding_event][download][type] = "git"
projects[ding_event][download][url] = "git@github.com:ding2tal/ding_event.git"
projects[ding_event][download][branch] = "development"

projects[ding_permissions][type] = "module"
projects[ding_permissions][download][type] = "git"
projects[ding_permissions][download][url] = "git@github.com:ding2tal/ding_permissions.git"
projects[ding_permissions][download][branch] = "development"

projects[ding_webtrends][type] = "module"
projects[ding_webtrends][download][type] = "git"
projects[ding_webtrends][download][url] = "git@github.com:ding2tal/ding_webtrends.git"
projects[ding_webtrends][download][branch] = "development"

projects[ding_session_cache][type] = "module"
projects[ding_session_cache][download][type] = "git"
projects[ding_session_cache][download][url] = "git@github.com:ding2tal/ding_session_cache.git"
projects[ding_session_cache][download][branch] = "development"

projects[ding_staff][type] = "module"
projects[ding_staff][download][type] = "git"
projects[ding_staff][download][url] = "git@github.com:ding2tal/ding_staff.git"
projects[ding_staff][download][branch] = "development"

projects[ding_varnish][type] = "module"
projects[ding_varnish][download][type] = "git"
projects[ding_varnish][download][url] = "git@github.com:ding2tal/ding_varnish.git"
projects[ding_varnish][download][branch] = "development"

projects[ding_contact][type] = "module"
projects[ding_contact][download][type] = "git"
projects[ding_contact][download][url] = "git@github.com:ding2tal/ding_contact.git"
projects[ding_contact][download][branch] = "development"

projects[bpi][type] = "module"
projects[bpi][download][type] = "git"
projects[bpi][download][url] = "git@github.com:ding2tal/bpi.git"
projects[bpi][download][branch] = "development"

; Base theme
projects[ddbasic][type] = "theme"
projects[ddbasic][download][type] = "git"
projects[ddbasic][download][url] = "git@github.com:ding2tal/ddbasic.git"
projects[ddbasic][download][branch] = "development"

; Libraries
libraries[profiler][download][type] = "git"
libraries[profiler][download][url] = "http://git.drupal.org/project/profiler.git"
libraries[profiler][download][branch] = "7.x-2.0-beta1"
# https://drupal.org/node/1328796, keep dependency order of base profile.
libraries[profiler][patch][0] = "http://drupal.org/files/profiler-reverse.patch"

; Contrib modules
projects[apc][subdir] = "contrib"
projects[apc][version] = "1.0-beta4"

projects[entitycache][subdir] = "contrib"
projects[entitycache][version] = "1.2"
# https://drupal.org/node/2146543, profile 2 blank fields.
projects[entitycache][patch][0] = "http://drupal.org/files/issues/2146543-ensure-entity-inserts-clears-caches.1.patch"

projects[fontyourface][subdir] = "contrib"
projects[fontyourface][version] = "2.7"

projects[module_filter][subdir] = "contrib"
projects[module_filter][version] = "1.8"

projects[memcache][subdir] = "contrib"
projects[memcache][version] = "1.0"

projects[sslproxy][subdir] = "contrib"
projects[sslproxy][version] = "1.0"

projects[cookiecontrol][subdir] = "contrib"
projects[cookiecontrol][version] = "1.6"
# https://drupal.org/node/2174955, fix translatable link.
projects[cookiecontrol][patch][0] = "http://drupal.org/files/issues/translatable_link_title-2174955-1.patch"

# Using dev release, as the "stable" version is making errors in the install profile.
projects[uuid][subdir] = "contrib"
projects[uuid][download][type] = "git"
projects[uuid][download][url] = "http://git.drupal.org/project/uuid.git"
projects[uuid][download][revision] = "3f4d9fb"

projects[view_unpublished][subdir] = "contrib"
projects[view_unpublished][version] = "1.1"
