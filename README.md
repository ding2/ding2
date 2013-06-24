# Drupal install profile for Ding2
Ding2 is a continuation of [ding.TING](http://ting.dk/content/om-dingting) [Drupal](http://drupal.org/project/drupal) distribution for libraries as part of the [TING concept](http://ting.dk).

## Dependencies

* [Drupal 7.22](https://drupal.org/drupal-7.22-release-notes) The latest stable version of Drupal Core that ding2 have been tested on and the last stable release when this was written.

* [Drush 5.8](http://drupal.org/project/drush) Which has build in drush make API version 2 and was the latest release when this was written.

If you are running an Aegir 1.9 stack you can download the required version of drush and drush make at these URLs.

* [Drush 4.6](http://drupal.org/project/drush)

* [Drush Make 2.3](http://drupal.org/project/drush_make)

## Build instructions

Install the dependencies and start by downloading a fresh copy of drupal and make sure that it's ready to begin the installation process (e.g. LAMP stack configured).

Go into your web-root and execute this command to download drupal

	~$ drush dl drupal-7.16
	~$ mv drupal-7.16/* .
	~$ mv drupal-7.16/.* .
	~$ rm -r drupal-7.16

To use the ding2 installation profile you need to patch drupal-7 core as of this writing. The patch can be download from drupal.org here http://drupal.org/files/menu-get-item-rebuild-1232346-22_0.patch from issue [#1232346](http://drupal.org/node/1232346)

To apply the patch go into your Drupal installation path.

	~$ cd DRUPAL
	~$ wget -qO- http://drupal.org/files/menu-get-item-rebuild-1232346-22_0.patch | patch -p1

You also need to patch core with this [patch](https://drupal.org/node/1879970) to ensure that communication with servers runing openssl v1.0.0 works

	~$ cd DRUPAL
	~$ wget -qO- http://drupal.org/files/ssl-socket-transports-1879970-13.patch | patch -p1

Download installation profile. Go into your Drupal installation path and into the profiles folder.

    ~$ cd DRUPAL/profiles

Clone the ding2 profile repository from github.

    ~$ git clone git@github.com:ding2/ding2.git

Place the install profile inside your Drupal installation, and run this command inside the profiles/ding2 folder:

	~$ drush make --concurrency=1 --no-core --contrib-destination=. ding2.make

You should note that the _--concurrency=1_ only apply to drush make that comes with drush-5.x.

If you want a developer version with Git working copies, run this command instead:

    ~$ drush make --concurrency=1 --no-core --working-copy --contrib-destination=. ding2.make

Next go to your sites URL and run the ding2 installation profile.

### Faster build process (~6 min)

The ding2 makefiles utilizes recursive makefiles, which results in the projects
and libraries being download more than once. You can work around this by cloning
the http://github.com/ding2/drush-ding2-utils into your .drush folder.

    ~$ cd ~/.drush
    ~$ git clone https://github.com/ding2/drush-ding2-utils drush-ding2-utils

Next go back to the profile folder.

    ~$ cd DRUPAL/profiles/ding2

Use the command below and you will only download resources once during the build
process and only the first defined version.

    ~$ drush --ding2-only-once --strict=0 make --concurrency=1 --no-core --contrib-destination=. ding2.make

This trick uses the drush cache and to build once more within 10 min you will
need to clear the cache. This also applies if the build fails and you need to
rebuild.

    ~$ drush cc drush