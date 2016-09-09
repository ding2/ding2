core = 7.x
api = 2

; Projects
projects[flag][subdir] = "contrib"
projects[flag][version] = "2.0"

projects[views_rss][subdir] = "contrib"
projects[views_rss][version] = "2.0-rc3"

; This specific checkout is only because of the module is dev branch only.
projects[views_rss_media][type] = "module"
projects[views_rss_media][subdir] = "contrib"
projects[views_rss_media][download][type] = "git"
projects[views_rss_media][download][url] = "http://git.drupal.org/project/views_rss_media.git"
projects[views_rss_media][download][revision] = "adb84a10e839c8ec8ed5d193a9d69d16d3393a1e"