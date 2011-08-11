Drupal install profile for Ding2
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

    git clone git@github.com:ding2/ding2.git

Ding relies on recursive make files that might have the same projects defined in multiple places. If your drush make bombs on this, apply the latest patch from this issue: http://drupal.org/node/947158

    cd DRUSH_MAKE_FOLDER
    wget http://drupal.org/files/issues/947158-recursive_2.patch
    patch -p1 < 947158-recursive_2.patch

Place the install profile inside your Drupal installation, and run this
command inside the profiles/ding2 folder:

    drush make --no-core --contrib-destination=. ding2.make

If you want a developer version with Git working copies, run this
command instead:

    drush make --no-core --contrib-destination=. --working-copy ding2.make

[ding.TING]: http://ting.dk/groups/dingting
[Drupal]: http://drupal.org/
[TING concept]: http://ting.dk/

