Drupal install profile for Ding2 aka Artesis Web
================================================

Ding2 is a continuation of [ding.TING][] [Drupal][] distribution for
libraries as part of the [TING concept][].

Dependencies
------------
* [Drupal 7.10](http://drupal.org/node/1361968) (This is the latest stable version of Drupal Core working with ding2)
* [Drush 4.6](http://drupal.org/project/drush) (This is the latest stable version of Drush working with ding2)
* [Drush Make 2.3](http://drupal.org/project/drush_make)

Build instructions
------------------

Go into your Drupal installation path

    cd DRUPAL/profiles

Clone the ding2 profile repository from github.

    git clone git@github.com:ding2/ding2.git

Place the install profile inside your Drupal installation, and run this
command inside the profiles/ding2 folder:

    drush make --no-core --contrib-destination=. ding2.make

If you want a developer version with Git working copies, run this
command instead:

    drush make --no-core --contrib-destination=. --working-copy ding2.make

If you want to have some dummy content added and a pre-filled main menu, you can install the 'artesis demo content' module from our git repository.

[artesis_demo_content]: https://github.com/DBCDK/artesis_demo_content

[ding.TING]: http://ting.dk/groups/dingting
[Drupal]: http://drupal.org/
[TING concept]: http://ting.dk/