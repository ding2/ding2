api = 2
core = 7.x

projects[dibs][subdir] = "contrib"
projects[dibs][version] = "1.0-beta1"

; Ding! modules

projects[ding_base][type] = "module"
projects[ding_base][download][type] = "git"
projects[ding_base][download][url] = "git@github.com:ding2/ding_base.git"
projects[ding_base][download][tag] = "v0.1"

projects[ding_provider][type] = "module"
projects[ding_provider][download][type] = "git"
projects[ding_provider][download][url] = "git@github.com:ding2/ding_provider.git"
projects[ding_provider][download][tag] = "7.x-0.7"
