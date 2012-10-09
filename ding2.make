api = 2
core = 7.x

; Profiler lib for profile
libraries[profiler][download][type] = "git"
libraries[profiler][download][url] = "http://git.drupal.org/project/profiler.git"
libraries[profiler][download][revision] = "d0137cb42bc7a4e9ce0a0431f875806285d09758"
; Patch from http://drupal.org/node/1328796
libraries[profiler][patch][] = http://drupal.org/files/profiler-reverse.patch

; Modules
projects[alma][type] = "module"
projects[alma][download][type] = "git"
projects[alma][download][url] = "https://github.com/ding2/alma.git"
projects[alma][download][tag] = "7.x-0.12"

projects[ding_devel][type] = "module"
projects[ding_devel][download][type] = "git"
projects[ding_devel][download][url] = "https://github.com/ding2/ding_devel.git"
projects[ding_devel][download][tag] = "7.x-0.3"

projects[openruth][type] = "module"
projects[openruth][download][type] = "git"
projects[openruth][download][url] = "https://github.com/ding2/openruth.git"
projects[openruth][download][tag] = "7.x-0.16"

; Frontend modules
projects[ding_frontend][type] = "module"
projects[ding_frontend][download][type] = "git"
projects[ding_frontend][download][url] = "https://github.com/ding2/ding_frontend.git"
projects[ding_frontend][download][tag] = "7.x-0.24"

projects[ding_user_frontend][type] = "module"
projects[ding_user_frontend][download][type] = "git"
projects[ding_user_frontend][download][url] = "https://github.com/ding2/ding_user_frontend.git"
projects[ding_user_frontend][download][tag] = "7.x-0.26"

projects[ding_ting_frontend][type] = "module"
projects[ding_ting_frontend][download][type] = "git"
projects[ding_ting_frontend][download][url] = "https://github.com/ding2/ding_ting_frontend.git"
projects[ding_ting_frontend][download][tag] = "7.x-0.42"

projects[mkdru_ding_frontend][type] = "module"
projects[mkdru_ding_frontend][download][type] = "git"
projects[mkdru_ding_frontend][download][url] = "https://github.com/ding2/mkdru_ding_frontend.git"
projects[mkdru_ding_frontend][download][tag] = "7.x-1.8"

; CMS modules (Curate)

projects[ding_content][type] = "module"
projects[ding_content][download][type] = "git"
projects[ding_content][download][url] = "https://github.com/ding2/ding_content.git"
projects[ding_content][download][tag] = "7.x-0.15"

projects[ding_example_content][type] = "module"
projects[ding_example_content][download][type] = "git"
projects[ding_example_content][download][url] = "https://github.com/ding2/ding_example_content.git"
projects[ding_example_content][download][tag] = "7.x-0.22"

projects[ding_frontpage][type] = "module"
projects[ding_frontpage][download][type] = "git"
projects[ding_frontpage][download][url] = "https://github.com/ding2/ding_frontpage.git"
projects[ding_frontpage][download][tag] = "7.x-0.7"

projects[ding_library][type] = "module"
projects[ding_library][download][type] = "git"
projects[ding_library][download][url] = "https://github.com/ding2/ding_library.git"
projects[ding_library][download][tag] = "7.x-0.17"

projects[ding_news][type] = "module"
projects[ding_news][download][type] = "git"
projects[ding_news][download][url] = "https://github.com/ding2/ding_news.git"
projects[ding_news][download][tag] = "7.x-0.22"

projects[ding_event][type] = "module"
projects[ding_event][download][type] = "git"
projects[ding_event][download][url] = "https://github.com/ding2/ding_event.git"
projects[ding_event][download][tag] = "7.x-0.20"
