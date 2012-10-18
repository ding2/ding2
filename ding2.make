api = 2
core = 7.x

; Profiler lib for profile
libraries[profiler][download][type] = "git"
libraries[profiler][download][url] = "http://git.drupal.org/project/profiler.git"
libraries[profiler][download][revision] = d0137cb42bc7a4e9ce0a0431f875806285d09758
; Patch from http://drupal.org/node/1328796
libraries[profiler][patch][] = http://drupal.org/files/profiler-reverse.patch

; Modules
projects[alma][type] = module
projects[alma][download][type] = git
projects[alma][download][url] = git@github.com:ding2tal/alma.git
projects[alma][download][branch] = "development"

projects[ding_devel][type] = "module"
projects[ding_devel][download][type] = "git"
projects[ding_devel][download][url] = "git@github.com:ding2tal/ding_devel.git"
projects[ding_devel][download][branch] = "development"

projects[openruth][type] = "module"
projects[openruth][download][type] = "git"
projects[openruth][download][url] = "git@github.com:ding2tal/openruth.git"
projects[openruth][download][branch] = "development"

; Frontend modules
projects[ding_frontend][type] = "module"
projects[ding_frontend][download][type] = "git"
projects[ding_frontend][download][url] = "git@github.com:ding2tal/ding_frontend.git"
projects[ding_frontend][download][branch] = "development"

projects[ding_user_frontend][type] = "module"
projects[ding_user_frontend][download][type] = "git"
projects[ding_user_frontend][download][url] = "git@github.com:ding2tal/ding_user_frontend.git"
projects[ding_user_frontend][download][branch] = "development"

projects[ding_ting_frontend][type] = "module"
projects[ding_ting_frontend][download][type] = "git"
projects[ding_ting_frontend][download][url] = "git@github.com:ding2tal/ding_ting_frontend.git"
projects[ding_ting_frontend][download][branch] = "development"

projects[mkdru_ding_frontend][type] = "module"
projects[mkdru_ding_frontend][download][type] = "git"
projects[mkdru_ding_frontend][download][url] = "git@github.com:ding2tal/mkdru_ding_frontend.git"
projects[mkdru_ding_frontend][download][branch] = "development"

; CMS modules (Curate)

projects[ding_content][type] = module
projects[ding_content][download][type] = git
projects[ding_content][download][url] = git@github.com:ding2tal/ding_content.git
projects[ding_content][download][branch] = "development"

projects[ding_example_content][type] = module
projects[ding_example_content][download][type] = git
projects[ding_example_content][download][url] = git@github.com:ding2tal/ding_example_content.git
projects[ding_example_content][download][branch] = "development"

projects[ding_frontpage][type] = module
projects[ding_frontpage][download][type] = git
projects[ding_frontpage][download][url] = git@github.com:ding2tal/ding_frontpage.git
projects[ding_frontpage][download][branch] = "development"

projects[ding_library][type] = module
projects[ding_library][download][type] = git
projects[ding_library][download][url] = git@github.com:ding2tal/ding_library.git
projects[ding_library][download][branch] = "development"

projects[ding_news][type] = module
projects[ding_news][download][type] = git
projects[ding_news][download][url] = git@github.com:ding2tal/ding_news.git
projects[ding_news][download][branch] = "development"

projects[ding_event][type] = module
projects[ding_event][download][type] = git
projects[ding_event][download][url] = git@github.com:ding2tal/ding_event.git
projects[ding_event][download][branch] = "development"
