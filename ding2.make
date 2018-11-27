core = 7.x
api = 2

defaults[projects][subdir] = "contrib"

; Contrib modules
projects[addressfield][subdir] = "contrib"
projects[addressfield][version] = "1.0-beta5"

projects[admin_menu][subdir] = "contrib"
projects[admin_menu][version] = "3.0-rc5"

projects[admin_views][subdir] = "contrib"
projects[admin_views][version] = "1.6"

projects[apc][subdir] = "contrib"
projects[apc][version] = "1.0-beta4"

projects[autologout][subdir] = "contrib"
projects[autologout][version] = "4.5"

projects[autosave][subdir] = "contrib"
projects[autosave][version] = "2.2"

projects[better_exposed_filters][subdir] = "contrib"
projects[better_exposed_filters][version] = "3.4"

projects[block_access][subdir] = "contrib"
projects[block_access][version] = "1.5"

projects[cache_actions][subdir] = "contrib"
projects[cache_actions][version] = "2.0-alpha5"

projects[conditional_styles][subdir] = "contrib"
projects[conditional_styles][version] = "2.2"

projects[cs_adaptive_image][subdir] = "contrib"
projects[cs_adaptive_image][version] = "1.0"

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.9"
; Fix regression. See https://www.drupal.org/node/2209775
projects[ctools][patch][] = "https://www.drupal.org/files/issues/ctools-readd_access_callback_params-2209775-24.patch"
; Fix PHP7 errors - PHP 4 style constructors - https://www.drupal.org/node/2528736
projects[ctools][patch][] = "https://www.drupal.org/files/issues/deprecating_php4_style-2528736-23.patch"
; PHP7 - Uniform Variable Syntax updates are causing exported pages to not have names.
projects[ctools][patch][] = "https://www.drupal.org/files/issues/ctools-uniform-variable-syntax-2635876-6.patch"

projects[customerror][subdir] = "contrib"
projects[customerror][version] = "1.4"
projects[customerror][patch][] = "https://www.drupal.org/files/issues/customerror-2836107-switch_between_text_formats.patch"
projects[customerror][patch][] = "patches/customerror-disable_auto_redirect.ding2.patch"

projects[date][subdir] = "contrib"
projects[date][version] = "2.8"

projects[dibs][subdir] = "contrib"
projects[dibs][version] = "1.0"
; Patch to fix empty order_id. See https://drupal.org/node/2107389
projects[dibs][patch][] = "http://drupal.org/files/dibs-2107389-2.patch"
; Patch make dibs_split_payments payment_transaction_id a NOT NULL database field.
; https://www.drupal.org/node/2812891
projects[dibs][patch][] = "https://www.drupal.org/files/issues/mysql_5.7_compatibility-2812891-2.patch"

projects[diff][subdir] = "contrib"
projects[diff][version] = "3.3"

; The patch ensures that file upload patch is created on file upload. It normally
; created on settings form save, but as we use feature this do not work.
; See https://www.drupal.org/node/2410241
projects[dynamic_background][subdir] = "contrib"
projects[dynamic_background][version] = "2.0-rc4"
projects[dynamic_background][patch][] = "https://www.drupal.org/files/issues/create_file_path-2410241-1.patch"

projects[eck][subdir] = "contrib"
projects[eck][version] = "2.0-rc9"

projects[email][subdir] = "contrib"
projects[email][version] = "1.3"

projects[entity][subdir] = "contrib"
projects[entity][version] = "1.8"

projects[entitycache][subdir] = "contrib"
projects[entitycache][version] = "1.2"
; https://drupal.org/node/2146543, profile 2 blank fields.
projects[entitycache][patch][0] = "http://drupal.org/files/issues/2146543-ensure-entity-inserts-clears-caches.1.patch"

projects[entityreference][subdir] = "contrib"
projects[entityreference][version] = "1.1"

projects[entityreference_filter][subdir] = "contrib"
projects[entityreference_filter][version] = "1.7"

projects[eu_cookie_compliance][subdir] = "contrib"
projects[eu_cookie_compliance][version] = "1.14"

projects[environment_indicator][subdir] = "contrib"
projects[environment_indicator][version] = "2.8"

projects[expire][subdir] = "contrib"
projects[expire][version] = "2.0-rc4"

projects[features][subdir] = "contrib"
projects[features][version] = "2.10"

projects[features_extra][subdir] = "contrib"
projects[features_extra][version] = "1.0-beta1"

projects[feeds][subdir] = "contrib"
projects[feeds][version] = "2.0-alpha8"

projects[fences][type] = "module"
projects[fences][subdir] = "contrib"
projects[fences][version] = "1.0"
projects[fences][patch][0] = "http://drupal.org/files/field_for_wrapper_css_class-1679684-3.patch"

projects[field_group][subdir] = "contrib"
projects[field_group][version] = "1.5"
; PHP7 - Uniform Variable Syntax updates are causing exported field_groups to not have names.
projects[field_group][patch][] = "https://www.drupal.org/files/issues/php7_uniform_variable-2649648-5.patch"

projects[file_entity][subdir] = "contrib"
projects[file_entity][version] = "2.0-beta3"

projects[flag][subdir] = "contrib"
projects[flag][version] = "2.2"

projects[fontyourface][subdir] = "contrib"
projects[fontyourface][version] = "2.7"

projects[formblock][type] = "module"
projects[formblock][subdir] = "contrib"
projects[formblock][download][type] = "git"
projects[formblock][download][url] = "http://git.drupal.org/project/formblock.git"
projects[formblock][download][revision] = "2d94c83"

projects[geocoder][subdir] = "contrib"
projects[geocoder][version] = "1.2"

projects[geofield][subdir] = "contrib"
projects[geofield][version] = "1.2"

projects[geophp][subdir] = "contrib"
projects[geophp][version] = "1.7"

projects[globalredirect][subdir] = "contrib"
projects[globalredirect][version] = "1.5"
projects[globalredirect][patch][] = "http://drupal.org/files/language_redirect_view_node-1399506-2.patch"

projects[google_analytics][subdir] = "contrib"
projects[google_analytics][version] = "1.3"

projects[htmlmail][subdir] = "contrib"
projects[htmlmail][version] = "2.65"

projects[honeypot][subdir] = "contrib"
projects[honeypot][version] = "1.21"

projects[image_resize_filter][subdir] = "contrib"
projects[image_resize_filter][version] = "1.14"

projects[job_scheduler][subdir] = "contrib"
projects[job_scheduler][version] = "2.0-alpha3"

projects[jquery_update][subdir] = "contrib"
projects[jquery_update][version] = "2.7"

projects[languageicons][subdir] = "contrib"
projects[languageicons][version] = "1.0"

projects[lazy_pane][subdir] = "contrib"
projects[lazy_pane][version] = "1.2"

projects[leaflet][subdir] = "contrib"
projects[leaflet][version] = "1.1"
; OSM Mapnik is hard-coded to be accessed via http, but some sites may need maps to render under https.
; The patch change code to use headless urls ("//" instead of "http://") for map access..
; Patch from https://www.drupal.org/node/2341015
projects[leaflet][patch][] = https://www.drupal.org/files/issues/leaflet-https_7x_11-2341015-3.patch

projects[libraries][subdir] = "contrib"
projects[libraries][version] = "2.2"

projects[link][subdir] = "contrib"
projects[link][version] = "1.4"
; Link sanitizes external URLs too much, rendering some external links broken.
; Patch changes external URL handling to pass it through unmolested.
; Patch from https://www.drupal.org/files/issues/link-external-1914072-22.patch
projects[link][patch][] = "https://www.drupal.org/files/issues/link_module_displays-1914072-28.patch"

projects[l10n_update][type] = "module"
projects[l10n_update][subdir] = "contrib"
projects[l10n_update][version] = "1.0"

projects[l10n_client][type] = "module"
projects[l10n_client][subdir] = "contrib"
projects[l10n_client][version] = "1.3"

projects[i18n][subdir] = "contrib"
projects[i18n][version] = "1.11"

projects[manualcrop][subdir] = "contrib"
projects[manualcrop][version] = "1.6"
; Fix loading of updated JavaScript library.
; https://www.drupal.org/node/2836970
projects[manualcrop][patch][] = "https://www.drupal.org/files/issues/manualcrop-imgareaselect_library_version_arguments-2836970-14-d7.patch"
; Fix crop display when the same file is used in multiple fields
; https://www.drupal.org/node/2503175
projects[manualcrop][patch][] = "https://www.drupal.org/files/issues/manualcrop-duplicatepreview-2503175-41.patch"
; Fix horizontal alignment of preview and buttons.
; https://www.drupal.org/node/2874825
projects[manualcrop][patch][] = "https://www.drupal.org/files/issues/manualcrop_media-widget-alignment-2874825-2.patch"

projects[mailsystem][subdir] = "contrib"
projects[mailsystem][version] = "2.34"

projects[maintenance_mode_api][subdir] = "contrib"
projects[maintenance_mode_api][version] = "1.0-beta1"

projects[media][subdir] = "contrib"
projects[media][version] = "2.0"
; Patch against SA-CONTRIB-2018-020
projects[media][patch][] = "https://cgit.drupalcode.org/media/patch/?id=1cd77ffa9c2cf96d80b76d47318179a8a82f0d46"

projects[media_vimeo][subdir] = "contrib"
projects[media_vimeo][version] = "2.1"

projects[media_youtube][subdir] = "contrib"
projects[media_youtube][version] = "3.0"

projects[memcache][subdir] = "contrib"
projects[memcache][version] = "1.6"

projects[menu_block][subdir] = "contrib"
projects[menu_block][version] = "2.7"
; Add support for features export of blocks
; https://www.drupal.org/node/693302
; The patch here add a database table, which is already created in a previous hook_update (from a previous patch).
; We have to modify it for our use.
projects[menu_block][patch][0] = "patches/menu_block-2x-ctools_exportables-693302-163.ding2.patch"

projects[menu_breadcrumb][subdir] = "contrib"
projects[menu_breadcrumb][version] = "1.5"

projects[menu_position][subdir] = "contrib"
projects[menu_position][version] = "1.1"

projects[message][subdir] = "contrib"
projects[message][version] = "1.12"

projects[metatag][subdir] = "contrib"
projects[metatag][version] = "1.21"

projects[mmeu][subdir] = "contrib"
projects[mmeu][version] = "1.0"

projects[module_filter][subdir] = "contrib"
projects[module_filter][version] = "2.0"

; NanoSOAP is currently not placed in contrib at this was not the case
; when using recursive make files.
projects[nanosoap][subdir] = "contrib"
projects[nanosoap][version] = "1.0"
projects[nanosoap][patch][] = "http://drupal.org/files/nanosoap-curloptions-1943732.patch"

projects[nodequeue][subdir] = "contrib"
projects[nodequeue][version] = "2.1"

projects[node_clone][subdir] = "contrib"
projects[node_clone][version] = "1.0-rc2"

projects[node_export][subdir] = "contrib"
projects[node_export][version] = "3.0"
projects[node_export][patch][] = "http://drupal.org/files/suppress-feature-install-profile-import.patch"
projects[node_export][patch][] = "http://drupal.org/files/check-field.patch"

projects[oembed][subdir] = "contrib"
projects[oembed][version] = "1.0-rc2"
; Remove hook_system_info_alter() to allow installing modules depending on oembed, after oembed is installed.
projects[oembed][patch][] = "http://www.drupal.org/files/issues/oembed-remove_hook_sytem_info_alter-2502817-1.patch"
; Added a check to ensure that a menu item exists before trying to alter it in order to fix a PHP error.
projects[oembed][patch][] = "https://www.drupal.org/files/oembed-2021015-1.patch"

projects[og][subdir] = "contrib"
projects[og][version] = "2.9"

projects[og_menu][subdir] = "contrib"
projects[og_menu][version] = "3.0"

projects[opening_hours][subdir] = "contrib"
projects[opening_hours][version] = "1.6"
; Adjust granularity to one minte.
; https://www.drupal.org/node/2381127
projects[opening_hours][patch][] = "http://www.drupal.org/files/issues/Issue620-single-minute-opening-hours.patch"
; Support series longer than a year.
; https://www.drupal.org/node/2194867
projects[opening_hours][patch][] = "https://www.drupal.org/files/issues/opening_hours-2194867-D7.patch"
; Add "hide if empty" option to field settings.
; https://www.drupal.org/node/2820005
projects[opening_hours][patch][] = "https://www.drupal.org/files/issues/opening-hours-2820005-hide-field-if-empty.patch"

projects[override_node_options][subdir] = "contrib"
projects[override_node_options][version] = "1.13"

projects[pagepreview][subdir] = "contrib"
projects[pagepreview][version] = "1.0-alpha1"

projects[panels][subdir] = "contrib"
projects[panels][version] = "3.4"
; Fix PHP7 errors - PHP 4 style constructors - (https://www.drupal.org/node/2557061)
projects[panels][patch][] = "https://www.drupal.org/files/issues/deprecated-constructor-in-php-7-2557061-3.patch"


projects[panels_breadcrumbs][subdir] = "contrib"
projects[panels_breadcrumbs][version] = "2.1"

projects[panels_everywhere][subdir] = "contrib"
projects[panels_everywhere][version] = "1.0-rc1"
projects[panels_everywhere][type] = "module"

projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.2"

projects[pm_existing_pages][subdir] = "contrib"
projects[pm_existing_pages][version] = "1.4"

projects[proj4js][subdir] = "contrib"
projects[proj4js][version] = "1.2"

projects[profile2][subdir] = "contrib"
projects[profile2][version] = "1.3"

projects[realname][subdir] = "contrib"
projects[realname][version] = "1.2"

projects[redirect][subdir] = "contrib"
projects[redirect][version] = "1.0-rc3"

projects[relation][subdir] = "contrib"
projects[relation][version] = "1.0"

projects[role_delegation][subdir] = "contrib"
projects[role_delegation][version] = "1.1"

projects[rules][subdir] = "contrib"
projects[rules][version] = "2.7"

projects[scheduler][subdir] = "contrib"
projects[scheduler][version] = "1.5"

; Patched with "Secure Permissions fails with features and multilingual"
projects[secure_permissions][type] = "module"
projects[secure_permissions][subdir] = "contrib"
projects[secure_permissions][download][type] = "git"
projects[secure_permissions][download][url] = "http://git.drupal.org/project/secure_permissions.git"
projects[secure_permissions][download][revision] = "ef5eec5"
projects[secure_permissions][patch][] = "http://drupal.org/files/issues/2188491-features-multilingual-2.patch"
projects[secure_permissions][patch][] = "http://drupal.org/files/issues/secure_permissions-dont_disable_all_permissions-2499607-3.patch"

projects[services][subdir] = "contrib"
projects[services][version] = "3.14"

projects[services_views][subdir] = "contrib"
projects[services_views][version] = "1.1"

projects[search_api][subdir] = "contrib"
projects[search_api][version] = "1.18"

projects[search_api_multi][subdir] = "contrib"
projects[search_api_multi][version] = "1.3"
; Fix incompatibility with Multiple types indexes
; https://www.drupal.org/node/2580975
projects[search_api_multi][patch][] = "https://www.drupal.org/files/issues/2580975-2--fix_multi_type_index_incompatibilities.patch"

projects[search_api_db][subdir] = "contrib"
projects[search_api_db][version] = "1.5"

projects[similarterms][subdir] = "contrib"
projects[similarterms][version] = "2.3"

projects[sslproxy][subdir] = "contrib"
projects[sslproxy][version] = "1.0"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0"

projects[tipsy][subdir] = "contrib"
projects[tipsy][version] = "1.0-rc1"

projects[token][subdir] = "contrib"
projects[token][version] = "1.6"

projects[transliteration][subdir] = "contrib"
projects[transliteration][version] = "3.2"

; Using dev release, as the "stable" version is making errors in the install profile.
projects[uuid][subdir] = "contrib"
projects[uuid][download][type] = "git"
projects[uuid][download][url] = "http://git.drupal.org/project/uuid.git"
projects[uuid][download][revision] = "3f4d9fb"

projects[variable][subdir] = "contrib"
projects[variable][version] = "2.5"

projects[varnish][subdir] = "contrib"
projects[varnish][version] = "1.0-beta3"
projects[varnish][patch][0] = "http://drupal.org/files/issues/notification_level_settings-2169271-3.patch"
; Fixes "Connection reset by peer" on large purge list by batching paths, https://www.drupal.org/node/1481136
projects[varnish][patch][] = "https://www.drupal.org/files/issues/varnish_purge_limit-1481136-11_1.patch"
; Fixes missing leading slash from ban URLs, https://www.drupal.org/node/2340829
projects[varnish][patch][] = "https://www.drupal.org/files/issues/varnish-leave_base_path_in_urls-2340829-26.patch"

projects[virtual_field][subdir] = "contrib"
projects[virtual_field][version] = "1.2"

projects[views][subdir] = "contrib"
projects[views][version] = "3.17"

projects[views_bulk_operations][subdir] = "contrib"
projects[views_bulk_operations][version] = "3.3"

projects[views_responsive_grid][subdir] = "contrib"
projects[views_responsive_grid][version] = "1.3"

projects[views_rss][subdir] = "contrib"
projects[views_rss][version] = "2.0-rc4"

; This specific checkout is only because of the module is dev branch only.
projects[views_rss_media][type] = "module"
projects[views_rss_media][subdir] = "contrib"
projects[views_rss_media][download][type] = "git"
projects[views_rss_media][download][url] = "http://git.drupal.org/project/views_rss_media.git"
projects[views_rss_media][download][revision] = "14f7cc90d41c0186d2356ff528ac316a16eba3fd"
; Prevents yielding strict warning about variables that should be passed by reference in views_rss_media_requirements().
projects[views_rss_media][patch][] = "https://www.drupal.org/files/issues/strict-warning-2149287-1.patch"
; Changing REQUIREMENT_ERROR to REQUIREMENT_WARNING so the installation of module will pass.
projects[views_rss_media][patch][] = "https://www.drupal.org/files/issues/views_rss_media-2550589-1.patch"

; Development version where the "unpublished" status have been fixed on the content edit page.
projects[view_unpublished][subdir] = "contrib"
projects[view_unpublished][download][type] = "git"
projects[view_unpublished][download][url] = "http://git.drupal.org/project/view_unpublished.git"
projects[view_unpublished][download][revision] = "e9df1d3"

projects[watchdog_filtering][subdir] = "contrib"
projects[watchdog_filtering][version] = "1.3"

projects[webform][subdir] = "contrib"
projects[webform][version] = "4.10"

projects[workbench][subdir] = "contrib"
projects[workbench][version] = "1.2"

projects[workflow][subdir] = "contrib"
projects[workflow][version] = "2.5"
projects[workflow][patch][] = "http://www.drupal.org/files/issues/features_import-2484297-10.patch"
; Prevent fatal errors on cron when using Scheduler, https://www.drupal.org/node/2499193.
projects[workflow][patch][] = "https://www.drupal.org/files/issues/workflow-php_fatal_error_call-2499193-7-2.5.patch"

projects[wysiwyg][subdir] = "contrib"
projects[wysiwyg][version] = "2.5"

projects[ask_vopros][type] = "module"
projects[ask_vopros][subdir] = "contrib"
projects[ask_vopros][download][type] = "git"
projects[ask_vopros][download][url] = "https://github.com/vopros-dk/ask_vopros.git"
projects[ask_vopros][download][tag] = "1.5"

projects[xautoload][subdir] = "contrib"
projects[xautoload][version] = "5.7"

; Libraries
; For ding_libs.
libraries[bpi-client][destination] = "modules/bpi/lib"
libraries[bpi-client][download][type] = "git"
libraries[bpi-client][download][url] = "http://github.com/ding2/bpi-client.git"
libraries[bpi-client][download][branch] = "master"

; For wysiwyg.
libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = https://download.cksource.com/CKEditor/CKEditor/CKEditor%204.9.2/ckeditor_4.9.2_standard.zip
libraries[ckeditor][directory_name] = "ckeditor"
libraries[ckeditor][destination] = "libraries"

; For ding_libs.
libraries[chosen][download][type] = "get"
libraries[chosen][download][url] = "https://github.com/harvesthq/chosen/releases/download/1.4.2/chosen_v1.4.2.zip"
libraries[chosen][destination] = "libraries"

; For ding_libs.
libraries[guzzle][download][type] = "git"
libraries[guzzle][download][url] = "https://github.com/guzzle/guzzle.git"
libraries[guzzle][download][tag] = "6.2.2"
libraries[guzzle][destination] = "libraries"

; For ding_libs.
libraries[http-message][download][type] = "git"
libraries[http-message][download][url] = "https://github.com/php-fig/http-message.git"
libraries[http-message][download][tag] = "1.0.1"
libraries[http-message][destination] = "libraries"

; For ding_libs.
libraries[jsonmapper][download][type] = "git"
libraries[jsonmapper][download][url] = "https://github.com/cweiske/jsonmapper"
libraries[jsonmapper][download][tag] = "v0.4.4"
libraries[jsonmapper][destination] = "libraries"

; For leaflet.
libraries[leaflet][download][type] = "get"
libraries[leaflet][download][url] = "http://cdn.leafletjs.com/downloads/leaflet-0.7.3.zip"
libraries[leaflet][directory_name] = "leaflet"
libraries[leaflet][destination] = "libraries"

; For ding_libs.
libraries[phly-http][download][type] = "git"
libraries[phly-http][download][url] = "https://github.com/phly/http"
libraries[phly-http][download][tag] = "0.14.1"
libraries[phly-http][destination] = "libraries"

libraries[profiler][download][type] = "git"
libraries[profiler][download][url] = "http://git.drupal.org/project/profiler.git"
libraries[profiler][download][branch] = "7.x-2.0-beta1"
; https://drupal.org/node/1328796, keep dependency order of base profile.
libraries[profiler][patch][0] = "http://drupal.org/files/profiler-reverse.patch"

; For ding_libs.
libraries[promises][download][type] = "git"
libraries[promises][download][url] = "https://github.com/guzzle/promises.git"
libraries[promises][download][tag] = "1.2.0"
libraries[promises][destination] = "libraries"

; For ding_libs.
libraries[psr7][download][type] = "git"
libraries[psr7][download][url] = "https://github.com/guzzle/psr7.git"
libraries[psr7][download][tag] = "1.3.1"
libraries[psr7][destination] = "libraries"

; For ting.
libraries[ting-client][download][type] = "git"
libraries[ting-client][download][url] = "http://github.com/ding2/ting-client.git"
libraries[ting-client][download][branch] = "master"
libraries[ting-client][destination] = "modules/opensearch/lib"

; Obsoleted. Only reference is in ding_frontend.
libraries[zen-grids][download][type] = "git"
libraries[zen-grids][download][url] = "https://github.com/JohnAlbin/zen-grids.git"
libraries[zen-grids][download][tag] = "1.4"
libraries[zen-grids][destination] = "libraries"

; For manualcrop.
libraries[jquery.imgareaselect][download][type] = "get"
libraries[jquery.imgareaselect][download][url] =  https://github.com/odyniec/imgareaselect/archive/v0.9.11-rc.1.tar.gz
libraries[jquery.imgareaselect][directory_name] = "jquery.imgareaselect"
libraries[jquery.imgareaselect][destination] = "libraries"

; For manualcrop and ddbasic.
libraries[jquery.imagesloaded][download][type] = "get"
libraries[jquery.imagesloaded][download][url] = https://github.com/desandro/imagesloaded/archive/v2.1.2.tar.gz
libraries[jquery.imagesloaded][directory_name] = "jquery.imagesloaded"
libraries[jquery.imagesloaded][destination] = "libraries"

; For ding_libs.
libraries[js.cookie][download][type] = "get"
libraries[js.cookie][download][url] =  "https://github.com/js-cookie/js-cookie/releases/download/v2.1.4/js.cookie-2.1.4.min.js"
libraries[js.cookie][directory_name] = "js.cookie"
libraries[js.cookie][destination] = "libraries"

; For ding_libs.
libraries[slick][download][type] = "get"
libraries[slick][download][url] = https://github.com/kenwheeler/slick/archive/1.8.0.tar.gz
libraries[slick][directory_name] = "slick"
libraries[slick][destination] = "libraries"
; Fix variableWitdh and white space/empty slides at the end.
; See https://github.com/kenwheeler/slick/pull/2635
libraries[slick][patch][] = "https://patch-diff.githubusercontent.com/raw/kenwheeler/slick/pull/2635.diff"

; For ding_libs.
libraries[html5shiv][download][type] = "get"
libraries[html5shiv][download][url] = https://github.com/aFarkas/html5shiv/archive/3.7.3.zip
libraries[html5shiv][directory_name] = "html5shiv"
libraries[html5shiv][destination] = "libraries"

; For ding_libs.
libraries[masonry][download][type] = "get"
libraries[masonry][download][url] = https://github.com/desandro/masonry/archive/v4.1.1.zip
libraries[masonry][directory_name] = "masonry"
libraries[masonry][destination] = "libraries"

libraries[smart-app-banner][download][type] = "get"
libraries[smart-app-banner][download][url] = https://github.com/kudago/smart-app-banner/archive/v1.3.0.zip
libraries[smart-app-banner][directory_name] = "smart-app-banner"
libraries[smart-app-banner][destination] = "libraries"
