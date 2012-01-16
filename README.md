# Ding! Tabroll
`ding_tabroll` is a module for displaying content in a carousel - typically used on frontpages of the site.

![Ding! Tabroll carousel](https://github.com/downloads/kdb/ding_tabroll/ding_tabroll_carousel.png)

Editors can manage the content of each queue at `/admin/content/nodequeue`. There is a queue, *Frontpage tabroll*, for the frontpage carousel.

A tabroll-carousel will not repeat its cycle unless at least 5 itemsa have been added to the queue.

The imagecache preset used by tabroll `460_240_crop` includes the action to make the image greyscale. This can be modified - it is greyscale because of the use of images on vejlebibs Ding!

Every rolltab can reference a library on the Ding!-site. This is entirely optional, and the only thing provided by this is the name of the library printed out as a CSS class on the image and info elements. We use this on vejlebibs Ding! to show the tabs with colored overlays.

## Ding! Library Tabroll
The submodule `ding_library_tabroll` adds support for per-library carousels. The nodequeue, *Library tabroll*, contains subqueues for each library. Content added to these nodequeues are shown on the librarys frontpage. If no nodes are added to a nodequeue the carousel is not shown.

Note that a rolltab is *not* automatically added to a librarys nodequeue if it references the library.

## Requirements

The module requires that some additional modules are added to the ding.make file:

<pre><code>projects[nodequeue][subdir] = "contrib"
projects[nodequeue][version] = "2.11"
; Patch required to add events for nodequeue saving which can then clear views caches.
projects[nodequeue][patch][] = "http://drupal.org/files/rules_event_support-952448-21.patch"

projects[smartqueue_nodetypes][subdir] = "contrib"
projects[smartqueue_nodetypes][version] = "1.2-beta2"
; Patch to update subqueues when a library node is created, updated or deleted
projects[smartqueue_nodetypes][patch][] = "http://drupal.org/files/smartqueue_subqueues_nodeapi-1116406-3.patch"

projects[nodequeue_export][type] = "module"
projects[nodequeue_export][download][type] = "git"
projects[nodequeue_export][download][url] = "https://github.com/blakehall/nodequeue_export.git"
; There is currently no tags for nodequeue_export so use a SHA.
projects[nodequeue_export][download][revision] = "4837a1ad5a537063e3d4d7aa8cb8c5d8264c35d3"
projects[nodequeue_export][patch][]= "https://github.com/blakehall/nodequeue_export/pull/4.diff"</pre></code>

## Update
The latest version of Ding! Tabroll uses nodequeues for managing tabroll carousels.


When updating the module administators must clear caches and run `update.php` or use `drush cc all` and `drush updb`.

