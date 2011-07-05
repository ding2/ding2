api = 2
core = 7.x

projects[nanosoap][subdir] = contrib
projects[nanosoap][version] = 1.x-dev

libraries[ting-client][download][type] = "git"
libraries[ting-client][download][url] = "https://github.com/dingproject/ting-client.git"
libraries[ting-client][destination] = "modules/ting/lib"

projects[ding_entity][type] = "module"
projects[ding_entity][download][type] = "git"
projects[ding_entity][download][url] = "git@github.com:ding2/ding_entity.git"
