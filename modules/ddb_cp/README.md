ddb_cp
======

Control panel for the DDB CMS project.

When this module is installed, it will provide a top-level administrative menu item named 'DDB'.

The control panel is a tiny shim that cannot do much without an associated webservice.

When running without the webservice, the only submenu available is a configuration panel with a field to specify the address of the webservice.

If the webservice is running, the control panel will check the webservice to learn which subscription model the library holds: If the webservice returns 'webmaster', the control panel enables the development submenu. 
