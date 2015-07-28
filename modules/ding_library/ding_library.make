core = 7.x
api = 2

; Projects
projects[addressfield][subdir] = "contrib"
projects[addressfield][version] = "1.0-beta5"

projects[cache_actions][subdir] = "contrib"
projects[cache_actions][version] = "2.0-alpha5"

projects[cs_adaptive_image][subdir] = "contrib"
projects[cs_adaptive_image][version] = "1.0"

projects[email][subdir] = "contrib"
projects[email][version] = "1.3"

projects[features][subdir] = "contrib"
projects[features][version] = "2.0"

projects[features_extra][subdir] = "contrib"
projects[features_extra][version] = "1.0-beta1"

projects[field_group][subdir] = "contrib"
projects[field_group][version] = "1.1"

projects[geocoder][subdir] = "contrib"
projects[geocoder][version] = "1.2"

projects[geophp][subdir] = "contrib"
projects[geophp][version] = "1.7"

projects[geofield][subdir] = "contrib"
projects[geofield][version] = "1.2"

projects[nodequeue][subdir] = "contrib"
projects[nodequeue][version] = "2.0-beta1"

projects[proj4js][subdir] = "contrib"
projects[proj4js][version] = "1.2"

projects[leaflet][subdir] = "contrib"
projects[leaflet][version] = "1.1"
; OSM Mapnik is hard-coded to be accessed via http, but some sites may need maps to render under https. 
; The patch change code to use headless urls ("//" instead of "http://") for map access..
; Patch from https://www.drupal.org/node/2341015
projects[leaflet][patch][] = https://www.drupal.org/files/issues/leaflet-https_7x_11-2341015-3.patch

projects[libraries][subdir] = "contrib"
projects[libraries][version] = "2.2"

projects[link][subdir] = "contrib"
projects[link][version] = "1.2"

; This version of media is tested to work with both images and videos.
projects[media][type] = "module"
projects[media][subdir] = "contrib"
projects[media][download][type] = "git"
projects[media][download][url] = "http://git.drupal.org/project/media.git"
projects[media][download][revision] = "c3cda2b"
; Fixed issue where "insert" fails, see https://www.drupal.org/node/2184475.
projects[media][patch][] = "https://www.drupal.org/files/issues/media_popup_trigger_some_js-2184475-6.patch"

projects[file_entity][subdir] = "contrib"
projects[file_entity][version] = "2.0-alpha3"

projects[og][subdir] = "contrib"
projects[og][version] = "2.7"
projects[og][patch][] = "https://www.drupal.org/files/issues/entityreference_fields_do_not_validate-2249261-10.patch"
; Fix using organic groups for relationships in views
; https://www.drupal.org/node/1890370
projects[og][patch][] = "https://www.drupal.org/files/issues/add-gid-to-relationship-field-1890370-34.patch"

projects[og_menu][subdir] = "contrib"
projects[og_menu][version] = "3.0-rc5"
; Fixes JavaScript menu selection in edit node forms.
projects[og_menu][patch][0] = "http://drupal.org/files/issues/selector_not_found-2276951-2.patch"

; This version is patch to make the next/prev links work.
projects[opening_hours][type] = "module"
projects[opening_hours][subdir] = "contrib"
projects[opening_hours][download][type] = "git"
projects[opening_hours][download][url] = "http://git.drupal.org/project/opening_hours.git"
projects[opening_hours][download][revision] = "81146d1e8ab63ca70976596d928e4ec46dfdfd57"
projects[opening_hours][patch][] = "http://drupal.org/files/issues/is-string-check-2260505-2.patch"
projects[opening_hours][patch][] = "http://drupal.org/files/issues/change-path-2270935-2.patch"
projects[opening_hours][patch][] = "http://www.drupal.org/files/issues/Issue620-single-minute-opening-hours.patch"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0"

projects[tipsy][subdir] = "contrib"
projects[tipsy][version] = "1.0-rc1"

projects[views][subdir] = "contrib"
projects[views][version] = "3.8"

projects[views_bulk_operations][subdir] = "contrib"
projects[views_bulk_operations][version] = "3.2"

libraries[leaflet][download][type] = "get"
libraries[leaflet][download][url] = "http://leaflet-cdn.s3.amazonaws.com/build/leaflet-0.7.2.zip"
libraries[leaflet][directory_name] = "leaflet"
libraries[leaflet][destination] = "libraries"
