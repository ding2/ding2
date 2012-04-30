Drupal install profile for Ding2 aka Artesis Web
================================================

Ding2 is a continuation of [ding.TING][] [Drupal][] distribution for
libraries as part of the [TING concept][].

Dependencies
------------
Drush v. 4.5 http://drupal.org/project/drush
Drush_make v. 2.3 http://drupal.org/project/drush_make
Drupal v. 7.10 (latest stable version of core working with ding2)

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

