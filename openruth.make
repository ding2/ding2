api = 2
core = 7.x

projects[date][subdir] = contrib
projects[date][version] = "2.6"

projects[features][subdir] = contrib
projects[features][version] = "1.0"

projects[profile2][subdir] = contrib
projects[profile2][version] = "1.2"

; Ding! modules

projects[ding_provider][type] = "module"
projects[ding_provider][download][type] = "git"
projects[ding_provider][download][url] = "git@github.com:ding2tal/ding_provider.git"
projects[ding_provider][download][branch] = "development"
