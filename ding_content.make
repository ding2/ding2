api = 2
core = 7.x

; Ting modules

projects[ting_reference][type] = module
projects[ting_reference][download][type] = git
projects[ting_reference][download][url] = git@github.com:ding2/ting_reference.git

; CONTRIB MODULES
projects[cache_actions][type] = module
projects[cache_actions][subdir] = contrib
projects[cache_actions][version] = 2.0-alpha3

projects[ctools][type] = module
projects[ctools][subdir] = contrib
projects[ctools][version] = 1.0-rc1

projects[entity][type] = module
projects[entity][subdir] = contrib
projects[entity][version] = 1.0-beta10

projects[media][type] = module
projects[media][subdir] = contrib
projects[media][version] = 1.0-rc1

projects[panels][type] = module
projects[panels][subdir] = contrib
projects[panels][version] = 3.0-alpha3

projects[pathauto][type] = module
projects[pathauto][subdir] = contrib
projects[pathauto][version] = 1.0-rc2
projects[pathauto][patch][] = http://drupal.org/files/1299460.patch

projects[rules][type] = module
projects[rules][subdir] = contrib
projects[rules][version] = 2.0-rc2

projects[transliteration][type] = module
projects[transliteration][subdir] = contrib
projects[transliteration][version] = 3.0-alpha1

projects[token][type] = module
projects[token][subdir] = contrib
projects[token][version] = 1.0-beta5

projects[views][type] = module
projects[views][subdir] = contrib
projects[views][version] = 3.0-rc1

projects[workbench][type] = module
projects[workbench][subdir] = contrib
projects[workbench][version] = 1.0

projects[wysiwyg][type] = module
projects[wysiwyg][subdir] = contrib
projects[wysiwyg][version] = 2.1

;Libraries
libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.6.2/ckeditor_3.6.2.zip"
libraries[ckeditor][directory_name] = "ckeditor"
libraries[ckeditor][destination] = "libraries"