# DDBCMS Personalisering #

This is a collection of modules related to personal user experience in DDBCMS / Ding2

To install the complete package download the repo and

drush en ding_p2_installer

## Configuration of OpenList ##
The installation comes with a developer configuration for OpenList.
Change the configuration to production here:

/admin/config/ding/provider/ting_openlist

## Configuration of Consent / Loan History 30d+ ##

Library providers that does not support storage of the user consent and loan history synchronization can disable the features here:

/admin/config/ding/provider/alma

## Configuration of Ding Interaction ##

Ding Interaction will show all sorts of useful information and interaction in rotation in a panel usually placed on the frontpage.
Enable desired DI plugins here

/admin/config/ding/interaction

Create and edit manual interaction content here:

/admin/structure/entity-type/ding_type/ding_interaction

Check out the ding_interaction_example module to see how to create new DI plugins

## Configuration of Ding User Complete ##

Ding User Complete adds plugins for the DI based on features the user has not yet tried out.

Enable desired plugins here

/admin/config/ding/user-complete

## Configuration of Ding Serendipity ##

Ding Serendipity collectes personalized serendipity based on all sorts of vectors. 
Enable desired serendipity plugins here:

/admin/config/ding/serendipity/key_overview


