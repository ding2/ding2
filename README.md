# Ding2
Ding2 is a continuation of [ding.TING](http://ting.dk/content/om-dingting)
[Drupal](http://drupal.org/project/drupal) distribution for libraries as part
of the [TING concept](http://ting.dk).

[![Circle CI](https://img.shields.io/circleci/project/ding2/ding2.svg)](https://circleci.com/gh/ding2/ding2)
[![Latest release](https://img.shields.io/github/release/ding2/ding2.svg)](https://github.com/ding2/ding2/releases/latest)


# Installation
This README assumes that you have install a configured your server with a
working Apache/Nginx, APC, Memcached, PHP 5.4 and Varnish 3.x (optional). The
stack should be optimized to run a Drupal site.

If you want to try out Ding2 you can download [the latest release](https://github.com/ding2/ding2/releases/latest). The `ding2-7.x-[version].tar.gz` file contain a full Drupal installation including Drupal Core, third party modules and Ding2 code needed to run the site.

# Build instructions
The reset of this document explains how to download Drupal and patch the core
to run a Ding2 based site.

## Dependencies
* [Drupal 7.43](https://drupal.org/drupal-7.43-release-notes) - latest stable
  version of Drupal Core that ding2 have been tested on and the last stable
  release when this was written.
* [Drush 6.1.0](https://github.com/drush-ops/drush) - latest release when this
  was written. See its README for installation instructions.

## Drupal
Go into your web-root (from now on named DRUPAL) and execute this drush command
to download a fresh copy of Drupal version 7.43. If you omit the version number
the newest version of Drupal will be downloaded.
```sh
  ~$ drush dl drupal-7.43
  ~$ mv drupal-7.43/* .
  ~$ mv drupal-7.43/.* .
  ~$ rm -r drupal-7.43
```

### Patches
You need to apply a set of patches to Drupal core to run the installation and
the site after the installation. To apply the patch go into your Drupal
root path and execute the commands below.

This [patch](https://drupal.org/node/1232346) fixes a problem with recursive menu rebuilds.
```sh
  ~$ wget -qO- http://drupal.org/files/menu-get-item-rebuild-1232346-22_0.patch | patch -p1
```

This [patch](https://drupal.org/node/2205581) fixes issue with permissions and
translation of role names.
```sh
  ~$ wget -qO- http://drupal.org/files/issues/translate_role_names-2205581-1.patch | patch -p1
```

This [patch](https://drupal.org/node/1879970) ensure that communication with
web-services that runs OpenSSL v1.0.x or newer works.
```sh
  ~$ wget -qO- http://drupal.org/files/ssl-socket-transports-1879970-13.patch | patch -p1
```

__Optional__,but recommended patch that ensures that Ajax errors only are
displayed when not in readystate 4. So when the user presses enter to perform a
search before auto-complete Ajax is call is completed an error will not be
displayed.
```sh
  ~$ wget -qO- https://drupal.org/files/issues/autocomplete-1232416-17-7x.patch | patch -p1
```

## Build Ding2 installation profile
Ding2 comes in the form of a Drupal installation profile and the first step is
to build that profile. So go into your Drupal installations _profiles_ folder.
```sh
  ~$ cd DRUPAL/profiles
```

Clone the ding2 repository from http://github.com/ding2/ding2.
```sh
  ~$ git clone git@github.com:ding2/ding2.git ding2
```

### Production
Now that you have cloned the installation profile you need to run the build
process using drush make. It will download all the modules and the theme from
the different repositories at http://github.com/ding2
```sh
  ~$ cd DRUPAL/profiles/ding2
  ~$ drush make --no-core --contrib-destination=. ding2.make
```

### Development
If you want a developer version with _working copies_ of the Git repositories,
run this command instead. It is because drush automatically deletes _.git_
folders after it has cloned the repositories and by adding _--working-copy_, it
will not delete these.
```sh
  ~$ drush make --no-core --working-copy --contrib-destination=. ding2.make
```

Next goto your sites URL and run the ding2 installation profile and fill out
all the questions.

## Alternative installation method
If you are using an deployment system you may not want to patch Drupal core
manually in a production environment.
```sh
  ~$ wget https://raw.github.com/ding2/ding2/release/drupal.make
  ~$ drush make --working-copy --contrib-destination=profiles/ding2/ drupal.make htdocs
```

# Post installation
After you have finished the installation there are some performance optimization
that you should put into your settings.php file.

## Drupal cache
This ensures that caching is enforced and that it can not be disabled in the
administration interface.

```php
  $conf['cache'] = 1;
  $conf['block_cache'] = 1;
  $conf['preprocess_css'] = 1;
  $conf['preprocess_js'] = 1;

  // Ensures that form data is not moved out of the database. It's important to
  // keep this in non-volatile memory (e.g. the database).
  $conf['cache_class_cache_form'] = 'DrupalDatabaseCache';

  // Ensure fast tracks for files not found.
  drupal_fast_404();
```

## Theme development

The base theme for the installation is DDBasic and is located within `themes/ddbasic`.

The JavaScript and stylesheet files for the files are processed orchestracted by [Gulp](http://gulpjs.com/). To work with these aspects of the installation you must have Node.js, Gulp and a number of packages installed.

### Install gulp

Install [Node.js](https://github.com/joyent/node/wiki/Installing-Node.js-via-package-manager) if it is not already available on your platform.

Install Gulp and other packages:

```sh
  ~$ cd DRUPAL/profiles/ding2/themes/ddbasic
  ~$ npm install
```

### Process files

Gulp can watch your source files so they are processed on every change:

```sh
  ~$ cd DRUPAL/profiles/ding2/themes/ddbasic
  ~$ gulp watch
```

Note that developers changing the source JavaScript and SCSS files are also responsible for changing the processed files in their commits.

## Varnish
This project assumes that you are using Varnish as a revers proxy and the
project comes with a specially design VCL file, so that authenticated library
users can be served cached pages (ding_varnish). It also allows Varnish to have
paths purged when content is edited (varnish and expire modules).

The other varnish configurations (not listed here) are added by ding_base
feature with the strong arm module.
```php
  // Tell Drupal it's behind a proxy.
  $conf['reverse_proxy'] = TRUE;

  // Tell Drupal what addresses the proxy server(s) use.
  $conf['reverse_proxy_addresses'] = array('127.0.0.1');

  // Bypass Drupal bootstrap for anonymous users so that Drupal sets max-age < 0.
  $conf['page_cache_invoke_hooks'] = FALSE;

  // Set varnish configuration.
  $conf['varnish_control_key'] = 'THE KEY';
  $conf['varnish_socket_timeout'] = 500;

  // Set varnish server IP's sperated by spaces
  $conf['varnish-control-terminal'] = 'IP:6082 IP:6082';
```

If you do not use varnish, you should disable varnish, exipre and ding_varnish
modules as they may give you problems.

## APC
This optimization assumes that you have APC installed on your server.

__More information on the way__

## Memcache
This optimization assumes that you have memcached installed on your server.
Alternatively you can use redis as a key/value store, but it will not give you
advantages as the more advanced stuff that redis as is not used by Drupal. So
from a performance point it's more what you are use to setup.

```php
  $conf += array(
    'memcache_extension' => 'Memcache',
    'show_memcache_statistics' => 0,
    'memcache_persistent' => TRUE,
    'memcache_stampede_protection' => TRUE,
    'memcache_stampede_semaphore' => 15,
    'memcache_stampede_wait_time' => 5,
    'memcache_stampede_wait_limit' => 3,
    'memcache_key_prefix' => YOUR_SITE_NAME,
  );

  $conf['cache_backends'][] = 'profiles/ding2/modules/contrib/memcache/memcache.inc';
  $conf['cache_default_class'] = 'MemCacheDrupal';

  // Configure cache servers.
  $conf['memcache_servers'] = array(
    '127.0.0.1:11211' => 'default',
  );
  $conf['memcache_bins'] = array(
    'cache' => 'default',
  );
```

## WAYF - NemID
The ding_wayf module that is used to connect to WAYF services through
SimpleSAMLphp requires that the providers (alma and openruth) set a special
hash value as default password togehter with the social security number from
WAYF.

This is done in settings.php by setting.
```php
  $conf['wayf_hash'] = "HASH_VALUE";
```

# SSL Proxy
It is recommended that you run the site behind an https end-point proxy and with varnish.

<pre>
  Client -> Nginx -> Varnish -> Apache
</pre>

## Nginx
The installation profile contains an example configuration (_example-nginx.conf_) for nginx that works as an SSL Proxy.

## Varnish
The installation profile also contains a Vanish configuration file (_ding2.vcl_), which is created to match the ding_varnish module's communication with varnish about which pages to cache for users (even logged in users).

The configuration file also limits which server are authenticated/allowed to be upstream proxy for Varnish. This is to ensure that sensitive information is not forwarded to an un-secure proxy as until the SSL proxy the information is not encrypted.

## Apache 
Apache do not have the SSL module enabled, so it will not set the "_X-Forwarded-Proto_" header from the SSL proxy and Drupal will not be able to detect that it's behind a SSL Proxy. So you have to set the HTTPS flag in your vhost configuration file as shown below.

<pre>
 SetEnvIf X-Forwarded-Proto https HTTPS=on
</pre>
