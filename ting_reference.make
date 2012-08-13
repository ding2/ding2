api = 2
core = 7.x

; Contrib

projects[ctools][subdir] = contrib
projects[ctools][version] = "1.1"

projects[relation][subdir] = contrib
projects[relation][version] = "1.0-rc3"

; Ding!
projects[ding_entity][type] = "module"
projects[ding_entity][download][type] = "git"
projects[ding_entity][download][url] = "git@github.com:ding2/ding_entity.git"
projects[ding_entity][download][tag] = "7.x-0.7"

projects[ting][type] = "module"
projects[ting][download][type] = "git"
projects[ting][download][url] = "git@github.com:ding2/ting.git"
projects[ting][download][tag] = "7.x-0.22"
