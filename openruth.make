api = 2
core = 7.x

projects[date][subdir] = "contrib"
projects[date][version] = "2.0-alpha4"
projects[date][patch][] = "http://drupal.org/files/issues/date-i18n-title-1188380-3.patch"

; Ding! modules

projects[ding_provider][type] = "module"
projects[ding_provider][download][type] = "git"
projects[ding_provider][download][url] = "git@github.com:ding2/ding_provider.git"
projects[ding_provider][download][tag] = "7.x-0.7"
