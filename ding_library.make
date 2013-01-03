api = 2
core = 7.x

projects[addressfield][type] = module
projects[addressfield][subdir] = contrib
projects[addressfield][version] = "1.0-beta3"

projects[cache_actions][type] = module
projects[cache_actions][subdir] = contrib
projects[cache_actions][version] = "2.0-alpha5"

projects[ctools][subdir] = contrib
projects[ctools][version] = "1.1"

projects[email][type] = module
projects[email][subdir] = contrib
projects[email][version] = "1.2"

projects[features][type] = module
projects[features][subdir] = contrib
projects[features][version] = "1.0"

projects[geocoder][type] = module
projects[geocoder][subdir] = contrib
projects[geocoder][version] = "1.2"

projects[geophp][type] = module
projects[geophp][subdir] = contrib
projects[geophp][version] = "1.6"

projects[geofield][type] = module
projects[geofield][subdir] = contrib
projects[geofield][version] = "1.1"

projects[libraries][type] = module
projects[libraries][subdir] = contrib
projects[libraries][version] = "1.0"
;projects[libraries][version] = "2.0"

projects[link][type] = module
projects[link][subdir] = contrib
projects[link][version] = "1.0"

projects[menu_block][type] = module
projects[menu_block][subdir] = contrib
projects[menu_block][version] = 2.3

; Changed to download as git repository due to failing when applying
; patch when version of git is lower than 1.7.5.4 and option working-copy
; is enabled
projects[og][type] = module
projects[og][subdir] = contrib
projects[og][download][type] = git
projects[og][download][url] = http://git.drupal.org/project/og.git
projects[og][download][tag] = 7.x-1.3
projects[og][patch][] = http://drupal.org/files/1320778.patch

projects[openlayers][type] = module
projects[openlayers][subdir] = contrib
projects[openlayers][version] = "2.0-beta1"

projects[strongarm][type] = module
projects[strongarm][subdir] = contrib
projects[strongarm][version] = "2.0"

projects[views][type] = module
projects[views][subdir] = contrib
projects[views][version] = "3.3"

libraries[openlayers][download][type] = get
libraries[openlayers][download][url] = http://openlayers.org/download/OpenLayers-2.12.tar.gz

libraries[openlayers_themes][download][type] = git
libraries[openlayers_themes][download][url] = git@github.com:developmentseed/openlayers_themes.git

