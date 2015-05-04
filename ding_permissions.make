core = 7.x
api = 2

; Projects

; Patched with "Secure Permissions fails with features and multilingual"
projects[secure_permissions][type] = "module"
projects[secure_permissions][subdir] = "contrib"
projects[secure_permissions][download][type] = "git"
projects[secure_permissions][download][url] = "http://git.drupal.org/project/secure_permissions.git"
projects[secure_permissions][download][revision] = "ef5eec5"
projects[secure_permissions][patch][] = "http://drupal.org/files/issues/2188491-features-multilingual-2.patch"
projects[secure_permissions][patch][] = "http://drupal.org/files/issues/secure_permissions-filter_modules_permissions-2482565-1.patch"

projects[role_delegation][subdir] = "contrib"
projects[role_delegation][version] = "1.1"
