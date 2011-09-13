api = 2
core = 7.x

; Modules
projects[alma][type] = module
projects[alma][download][type] = git
projects[alma][download][url] = git@github.com:ding2/alma.git
projects[alma][download][tag] = "v0.3"

projects[ding_devel][type] = "module"
projects[ding_devel][download][type] = "git"
projects[ding_devel][download][url] = "git@github.com:ding2/ding_devel.git"
projects[ding_devel][download][tag] = "v0.1"

projects[mkdru][subdir] = "contrib"
projects[mkdru][version] = "1.1"

projects[mkdru_ding][type] = "module"
projects[mkdru_ding][download][type] = "git"
projects[mkdru_ding][download][url] = "git://github.com/indexdata/mkdru_ding.git"
projects[mkdru_ding][download][branch] = "7.x-1.x"

projects[openruth][type] = "module"
projects[openruth][download][type] = "git"
projects[openruth][download][url] = "git@github.com:ding2/openruth.git"
projects[openruth][download][tag] = "v0.3"

projects[ting_fulltext][type] = module
projects[ting_fulltext][download][type] = git
projects[ting_fulltext][download][url] = git@github.com:ding2/ting_fulltext.git
projects[ting_fulltext][download][tag] = "v0.3"

; Frontend modules
projects[ding_frontend][type] = "module"
projects[ding_frontend][download][type] = "git"
projects[ding_frontend][download][url] = "git@github.com:ding2/ding_frontend.git"
projects[ding_frontend][download][tag] = "v0.2"

projects[ding_user_frontend][type] = "module"
projects[ding_user_frontend][download][type] = "git"
projects[ding_user_frontend][download][url] = "git@github.com:ding2/ding_user_frontend.git"
projects[ding_user_frontend][download][tag] = "v0.4"

projects[ding_ting_frontend][type] = "module"
projects[ding_ting_frontend][download][type] = "git"
projects[ding_ting_frontend][download][url] = "git@github.com:ding2/ding_ting_frontend.git"
projects[ding_ting_frontend][download][tag] = "v0.5"

projects[mkdru_ding_frontend][type] = "module"
projects[mkdru_ding_frontend][download][type] = "git"
projects[mkdru_ding_frontend][download][url] = "git@github.com:ding2/mkdru_ding_frontend.git"

; Libraries
projects[pazpar2][download][type] = "git"
projects[pazpar2][type] = "library"
projects[pazpar2][download][url] = "git://git.indexdata.com/pazpar2.git"

; Themes
projects[artois][type] = "theme"
projects[artois][download][type] = "git"
projects[artois][download][url] = "git@github.com:DBCDK/artois.git"
projects[artois][tag] = "v0.4"
