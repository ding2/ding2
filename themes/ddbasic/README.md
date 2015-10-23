# DDBasic theme for Ding2

## Maintenance pages

The theme provides maintenance page templates:
- *maintenance-page-tpl.php*: This page template is used when the site has been set offline by the administrator. 
- *maintenance-page--offline.tpl.php*: This page template is used when the site cannot get in contact with the database.

It is common for ding2 sites to have the DDBasic theme reside in the folder /profiles/ding2/themes/ddbasic.
In this case, you will need to add the following lines to your settings.php file in order for both template 
files to be displayed properly:

    $conf['install_profile'] = 'ding2';
    $conf['maintenance_theme'] = 'ddbasic';

    