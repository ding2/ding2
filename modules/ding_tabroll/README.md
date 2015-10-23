# Ding! Tabroll
`ding_tabroll` is a module for displaying content in a carousel - typically used on frontpages of the site.

![Ding! Tabroll carousel](https://github.com/downloads/kdb/ding_tabroll/ding_tabroll_carousel.png)

Editors can manage the content of each queue at `/admin/content/nodequeue`. There is a queue, *Frontpage tabroll*, for the frontpage carousel.

A tabroll-carousel will not repeat its cycle unless at least 5 itemsa have been added to the queue.

Tabroll supports reponsive web design. The whole box will expand to its bounding container, and will maintain its width:height aspect ratio.

The navigation is by default placed on the left. When theming, the navigation tabs can be switched to the right by providing a class of "nav-right" to the Tabroll DIV wrapper (the element with ID "ding-tabroll").

The imagecache preset used by tabroll `460_240_crop` includes the action to make the image greyscale. This can be modified - it is greyscale because of the use of images on vejlebibs Ding!

Every rolltab can reference a library on the Ding!-site. This is entirely optional, and the only thing provided by this is the name of the library printed out as a CSS class on the image and info elements. We use this on vejlebibs Ding! to show the tabs with colored overlays.

## Ding! Library Tabroll
The submodule `ding_library_tabroll` adds support for per-library carousels. The nodequeue, *Library tabroll*, contains subqueues for each library. Content added to these nodequeues are shown on the librarys frontpage. If no nodes are added to a nodequeue the carousel is not shown.

Note that a rolltab is *not* automatically added to a librarys nodequeue if it references the library.

## Update
The latest version of Ding! Tabroll uses nodequeues for managing tabroll carousels.

When updating the module administators must clear caches and run `update.php` or use `drush cc all` and `drush updb`.

