api = 2
core = 7.x

projects[addressfield][type] = module
projects[addressfield][subdir] = contrib
projects[addressfield][version] = 1.0-beta2

projects[cache_actions][type] = module
projects[cache_actions][subdir] = contrib
projects[cache_actions][version] = 2.0-alpha3

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.0-rc1"
projects[ctools][patch][] = "http://drupal.org/files/issues/user_edit_form-p0-format-1184168.patch"

projects[email][type] = module
projects[email][subdir] = contrib
projects[email][version] = 1.0

projects[features][type] = module
projects[features][subdir] = contrib
projects[features][version] = 1.0-beta4

projects[geocoder][type] = module
projects[geocoder][subdir] = contrib
projects[geocoder][download][type] = git
projects[geocoder][download][url] = http://git.drupal.org/project/geocoder.git
projects[geocoder][download][revision] = 4c6801e6f824adbe4d2a5919d09bce454f2c7f2b

projects[geofield][type] = module
projects[geofield][subdir] = contrib
projects[geofield][version] = 1.0-alpha5

projects[libraries][type] = module
projects[libraries][subdir] = contrib
projects[libraries][version] = 1.0

projects[link][type] = module
projects[link][subdir] = contrib
projects[link][version] = 1.0

; Changed to download as git repository due to failing when applying
; patch when version of git is lower than 1.7.5.4 and option working-copy
; is enabled
projects[og][type] = module
projects[og][subdir] = contrib
projects[og][download][type] = git
projects[og][download][url] = http://drupalcode.org/project/og.git
projects[og][download][tag] = 7.x-1.3
projects[og][patch][] = http://drupal.org/files/1320778.patch

projects[openlayers][type] = module
projects[openlayers][subdir] = contrib
projects[openlayers][version] = 2.0-beta1

projects[strongarm][type] = module
projects[strongarm][subdir] = contrib
projects[strongarm][version] = 2.0-beta4

projects[views][type] = module
projects[views][subdir] = contrib
projects[views][version] = 3.0

libraries[openlayers][download][type] = get
libraries[openlayers][download][url] = http://openlayers.org/download/OpenLayers-2.11.tar.gz

libraries[openlayers_themes][download][type] = git
libraries[openlayers_themes][download][url] = git://github.com/developmentseed/openlayers_themes.git

