Drupal install profile for Ding2 aka Artesis Web
================================================

Ding2 is a continuation of [ding.TING][] [Drupal][] distribution for
libraries as part of the [TING concept][].

Build instructions
------------------

Place the install profile inside your Drupal installation, and run this
command inside the profiles/ding2 folder:

    drush make --no-core --contrib-destination=. ding2.make

If you want a developer version with Git working copies, run this
command instead:

    drush make --no-core --contrib-destination=. --working-copy ding2.make

[ding.TING]: http://ting.dk/groups/dingting
[Drupal]: http://drupal.org/
[TING concept]: http://ting.dk/

