api = 2
core = 7.x

; Changed to download as git repository due to failing when applying
; patch when version of git is lower than 1.7.5.4 and option working-copy
; is enabled
projects[date][type] = module
projects[date][subdir] = contrib
projects[date][download][type] = git
projects[date][download][url] = http://drupalcode.org/project/date.git
projects[date][download][tag] = 7.x-2.0-alpha4
; Translation patch.
projects[date][patch][] = http://drupal.org/files/1188380.patch

projects[features][subdir] = contrib
projects[features][version] = 1.0-beta4

projects[profile2][version] = 1.2
projects[profile2][subdir] = contrib

; Ding! modules

projects[ding_provider][type] = "module"
projects[ding_provider][download][type] = "git"
projects[ding_provider][download][url] = "git@github.com:ding2/ding_provider.git"
projects[ding_provider][download][tag] = "7.x-0.11"
