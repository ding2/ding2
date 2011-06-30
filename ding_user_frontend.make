api = 2
core = 7.x

; Contrib
projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.x-dev"
projects[ctools][patch][] = "http://drupal.org/files/issues/0001-No-need-for-hook_search_execute-to-be-executed-twice.patch"

projects[panels][subdir] = contrib
projects[panels][version] = 3.0-alpha3

projects[ding_loan][type] = "module"
projects[ding_loan][download][type] = "git"
projects[ding_loan][download][url] = "git@github.com:ding2/ding_loan.git"

projects[ding_reservation][type] = "module"
projects[ding_reservation][download][type] = "git"
projects[ding_reservation][download][url] = "git@github.com:ding2/ding_reservation.git"
