api = 2
core = 7.x

projects[cs_adaptive_image][subdir] = "contrib"
projects[cs_adaptive_image][version] = "1.0"

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.3"
projects[ctools][patch][0] = "http://drupal.org/files/ctools-n1925018-12.patch"

projects[entity][subdir] = "contrib"
projects[entity][version] = "1.1"

projects[email][subdir] = "contrib"
projects[email][version] = "1.2"

projects[features][subdir] = "contrib"
projects[features][version] = "2.0-beta2"

projects[footable][subdir] = "contrib"
projects[footable][version] = "1.0-beta2"

projects[views_bulk_operations][subdir] = "contrib"
projects[views_bulk_operations][version] = "3.1"

projects[media][subdir] = "contrib"
projects[media][version] = "2.0-unstable7"

projects[file_entity][subdir] = "contrib"
projects[file_entity][version] = "2.0-unstable7"

projects[field_group][subdir] = "contrib"
projects[field_group][version] = "1.1"

projects[profile2][subdir] = "contrib"
projects[profile2][version] = "1.3"

projects[views][subdir] = "contrib"
projects[views][version] = "3.7"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0"

projects[role_delegation][subdir] = "contrib"
projects[role_delegation][version] = "1.1"

projects[jquery_update][subdir] = "contrib"
projects[jquery_update][version] = "2.3"

projects[og][type] = "module"
projects[og][subdir] = "contrib"
projects[og][download][type] = "git"
projects[og][download][url] = "http://git.drupal.org/project/og.git"
projects[og][download][tag] = "7.x-1.3"
projects[og][patch][0] = "http://drupal.org/files/1320778.patch"

projects[ding_content][type] = "module"
projects[ding_content][download][type] = "git"
projects[ding_content][download][url] = "git@github.com:ding2tal/ding_content.git"
projects[ding_content][download][branch] = "development"

projects[ding_news][type] = "module"
projects[ding_news][download][type] = "git"
projects[ding_news][download][url] = "git@github.com:ding2tal/ding_news.git"
projects[ding_news][download][branch] = "development"

libraries[FooTable][download][type] = "get"
libraries[FooTable][download][url] = "https://github.com/bradvin/FooTable/archive/0.5.0.zip"
