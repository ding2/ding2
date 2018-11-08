# Ding Mobilesearch
This module allows export of content to remote storage.
By default uses connectivity to a REST API, but can be expanded with custom plugins
to support other connectors. (see `hook_mobilesearch_plugin_info()`).

## Installation
No special installation steps are required, simply enable the module and set
export configuration (see `Configuration` section of this file).
Also supports (and provides a necessary features) workflow and workbench modules
in the case if they exist and enabled in the system.

## Dependencies
* None

## Configuration.
- Go to `admin/config/ding/mobilesearch/content-export` and specify the node types and menus which should be exported.
- Then go to `admin/config/ding/mobilesearch/content-export/plugin` and set the configs for all known plugins. Notice that "Agency ID" setting is the same as "Library code" (`admin/config/ting/settings`).


## Workbench integration
Standard implementation of Workbench works through Views module. Therefore integration with Workbench
is made through VBO (views_bulk_operations).
Ding Mobilesearch module implements a hook_action_info()
which defines "Push to Mongo" action for VBO. You are free to add new field
"Bulk operations: Content" in the respective view and enable "Push to Mongo" action in
"SELECTED BULK OPERATIONS" section (when the field is configured).
I.e. Workbench integration doesn't work "out of the box" and should be configured.
