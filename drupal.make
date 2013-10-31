core = 7.x
api = 2

; Core
projects[drupal][version] = "7.22"
projects[drupal][patch][] = http://drupal.org/files/menu-get-item-rebuild-1232346-22_0.patch
projects[drupal][patch][] = http://drupal.org/files/ssl-socket-transports-1879970-13.patch
projects[drupal][patch][] = https://drupal.org/files/issues/autocomplete-1232416-17-7x.patch

; Get the profile, which will contain the next makefile.
projects[ding2][type] = "profile"
projects[ding2][download][type] = "git"
projects[ding2][download][url] = "git@github.com:ding2tal/ding2.git"
;projects[ding2][download][revision] = "e7be30f"
