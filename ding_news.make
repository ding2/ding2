api = 2
core = 7.x

; Views and CTools are required by ding_content.

projects[similarterms][type] = module
projects[similarterms][subdir] = contrib
projects[similarterms][download][type] = git
projects[similarterms][download][url] = http://git.drupal.org/project/similarterms.git
projects[similarterms][download][revision] = d0f10f5fdcb3a16855cff93094c4139a32e585f6
projects[similarterms][patch][] = http://drupal.org/files/issues/1292650.patch
projects[similarterms][patch][] = http://drupal.org/files/issues/1292676.patch
