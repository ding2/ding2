api = 2
core = 7.x

projects[nanosoap][subdir] = contrib
projects[nanosoap][version] = 1.0-beta3

libraries[ting-client][download][type] = "git"
libraries[ting-client][download][url] = "git@github.com:ding2/ting-client.git"
libraries[ting-client][destination] = "modules/ting/lib"

projects[ding_entity][type] = "module"
projects[ding_entity][download][type] = "git"
projects[ding_entity][download][url] = "git@github.com:ding2/ding_entity.git"
projects[ding_entity][download][tag] = "7.x-0.7"

projects[blackhole][type] = "module"
projects[blackhole][download][type] = "git"
projects[blackhole][download][url] = "git@github.com:xendk/blackhole.git"
