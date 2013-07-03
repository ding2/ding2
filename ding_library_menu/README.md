# Ding library menu
This module automatically creates menu items under the library's parent menu
item based on the hook_ding_library_menu_links() which provides a link and menu
item title (see example below).

This can be use to ensure that all libraries have links to news, events and
other stuff that should be the same on every library. The menu items path will
automatically be updated based on the library's menu item path.

The module that implements this hook is responsible for providing a valid menu
callback.

## Example

/**
 * Implements hook_ding_library_menu_links().
 */
function MODULENAME_menu_ding_library_menu_links() {
  return array(
    'example' => array(
      'title' => 'Example item',
      'weight' => 11,
    ),
  );
}
