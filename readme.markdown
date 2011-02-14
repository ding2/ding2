# Ding Facetbrowser

## Usage 

All search modules in this installation is implemented by hook_search_info(), hook_search_execute(), and hook_ding_facetbrowser() to implement the facetbrowser.

Check the test_facetbrowser_search module for how to implement your search module into the facetbrowser

Remember to enable the test_facetbrowser_search module and enable the module as a search tab in 'Admin -> Search settings' or via the hook_install in test_facetbrowser_search.install

The only custom part is hook_ding_facetbrowser() where you have to use this precise format for the facets.

## Installation

`git clone git@github.com:ding2/ding_facetbrowser.git`

From your drupal installation go to

1. Admin -> Modules And enable "Ding Facet browser"
2. Admin -> Structure -> Blocks and enable "Search form" and "Facetbrowser"

