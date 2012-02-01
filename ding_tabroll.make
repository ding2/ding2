api = 2
core = 6.x

projects[nodequeue][subdir] = "contrib"
projects[nodequeue][version] = "2.11"
; Patch required to add events for nodequeue saving which can then clear views caches.
projects[nodequeue][patch][] = "http://drupal.org/files/rules_event_support-952448-21.patch"

projects[smartqueue_nodetypes][subdir] = "contrib"
projects[smartqueue_nodetypes][version] = "1.2-beta2"
; Patch to automatically update subqueues when creating, updating or deleting library nodes
projects[smartqueue_nodetypes][patch][] = http://drupal.org/files/smartqueue_subqueues_nodeapi-1116406-3.patch

projects[nodequeue_export][type] = "module"
projects[nodequeue_export][download][type] = "git"
projects[nodequeue_export][download][url] = "https://github.com/blakehall/nodequeue_export.git"
; There is currently no tags for nodequeue_export so use a SHA.
projects[nodequeue_export][download][revision] = "4837a1ad5a537063e3d4d7aa8cb8c5d8264c35d3"
projects[nodequeue_export][patch][]= "https://github.com/blakehall/nodequeue_export/pull/4.diff"
