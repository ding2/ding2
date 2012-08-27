api = 2
core = 7.x

; Contrib modules

projects[defaultcontent][subdir] = contrib
projects[defaultcontent][version] = "1.0-alpha6"

; Ting! modules

projects[ding_library][type] = module
projects[ding_library][download][type] = git
projects[ding_library][download][url] = git@github.com:ding2tal/ding_library.git
projects[ding_library][download][branch] = "development"

projects[ding_event][type] = module
projects[ding_event][download][type] = git
projects[ding_event][download][url] = git@github.com:ding2tal/ding_event.git
projects[ding_event][download][branch] = "development"

projects[ding_news][type] = module
projects[ding_news][download][type] = git
projects[ding_news][download][url] = git@github.com:ding2tal/ding_news.git
projects[ding_news][download][branch] = "development"
