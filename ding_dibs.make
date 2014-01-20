api = 2
core = 7.x

projects[dibs][subdir] = "contrib"
projects[dibs][version] = "1.0"
projects[dibs][patch][] = "http://drupal.org/files/dibs-2107389-2.patch"

; Ding! modules

projects[ding_base][type] = "module"
projects[ding_base][download][type] = "git"
projects[ding_base][download][url] = "git@github.com:ding2tal/ding_base.git"
projects[ding_base][download][tag] = "7.x-1.0-rc3"

projects[ding_provider][type] = "module"
projects[ding_provider][download][type] = "git"
projects[ding_provider][download][url] = "git@github.com:ding2tal/ding_provider.git"
projects[ding_provider][download][tag] = "7.x-1.0-rc3"
