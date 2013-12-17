api = 2
core = 7.x

projects[node_export][subdir] = "contrib"
projects[node_export][version] = "3.0"
projects[node_export][patch][] = "http://drupal.org/files/suppress-feature-install-profile-import.patch"
projects[node_export][patch][] = "http://drupal.org/files/check-field.patch"

# Using dev release, as the "stable" version is making errors on install profile.
projects[uuid][subdir] = "contrib"
projects[uuid][download][type] = "git"
projects[uuid][download][url] = "http://git.drupal.org/project/uuid.git"
projects[uuid][download][revision] = "3f4d9fb"

projects[ding_library][type] = "module"
projects[ding_library][download][type] = "git"
projects[ding_library][download][url] = "git@github.com:ding2tal/ding_library.git"
projects[ding_library][download][branch] = "development"

projects[ding_groups][type] = "module"
projects[ding_groups][download][type] = "git"
projects[ding_groups][download][url] = "git@github.com:ding2tal/ding_groups.git"
projects[ding_groups][download][branch] = "development"
