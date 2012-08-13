api = 2
core = 7.x

; Ding 2 modules

projects[blackhole][type] = "module"
projects[blackhole][download][type] = "git"
projects[blackhole][download][url] = "git@github.com:xendk/blackhole.git"

projects[ting][type] = "module"
projects[ting][download][type] = "git"
projects[ting][download][url] = "git@github.com:ding2/ting.git"
projects[ting][download][tag] = "7.x-0.22"

; Contrib modules

projects[features][subdir] = contrib
projects[features][version] = "1.0"

projects[field_group][subdir] = contrib
projects[field_group][version] = "1.1"
