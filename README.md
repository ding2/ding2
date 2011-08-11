Drupal install profile for Artesis Web based on Ding2
================================================

Ding2 is a continuation of [ding.TING][] [Drupal][] distribution for
libraries as part of the [TING concept][].

Dependencies
------------
Drush http://drupal.org/project/drush
Drush_make http://drupal.org/project/drush_make

Build instructions
------------------

Go into your Drupal installation path

    cd DRUPAL/profiles

Clone the ding2 profile repository from github.

    git clone git@github.com:DBCDK/ding2.git

Place the install profile inside your Drupal installation, and run this
command inside the profiles/ding2 folder:

    drush make --no-core --contrib-destination=. ding2.make

Ding relies on recursive make files that might have the same projects defined in multiple places. If your drush make bombs on this, apply the latest patch from this issue: http://drupal.org/node/947158

    cd DRUSH_MAKE_FOLDER
    wget http://drupal.org/files/issues/947158-recursive_2.patch
    patch -p1 < 947158-recursive_2.patch

If you want a developer version with Git working copies, run this
command instead:

    drush make --no-core --contrib-destination=. --working-copy ding2.make

If you want to have some dummy content added and a pre-filled main menu, you can install the 'artesis demo content' module from our git repository.

[artesis_demo_content]: https://github.com/DBCDK/artesis_demo_content

[ding.TING]: http://ting.dk/groups/dingting
[Drupal]: http://drupal.org/
[TING concept]: http://ting.dk/

