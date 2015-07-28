api = 2
core = 7.x

; Contrib

projects[date][subdir] = "contrib"
projects[date][version] = "2.8"

; Ding 2 modules

projects[ding_base][type] = "module"
projects[ding_base][download][type] = "git"
projects[ding_base][download][url] = "git@github.com:ding2/ding_base.git"
projects[ding_base][download][branch] = "master"

projects[ding_popup][type] = "module"
projects[ding_popup][download][type] = "git"
projects[ding_popup][download][url] = "git@github.com:ding2/ding_popup.git"
projects[ding_popup][download][branch] = "master"

projects[ding_user][type] = "module"
projects[ding_user][download][type] = "git"
projects[ding_user][download][url] = "git@github.com:ding2/ding_user.git"
projects[ding_user][download][branch] = "master"

projects[ding_provider][type] = "module"
projects[ding_provider][download][type] = "git"
projects[ding_provider][download][url] = "git@github.com:ding2/ding_provider.git"
projects[ding_provider][download][branch] = "master"
