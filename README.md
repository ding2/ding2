# Ding2
Ding2 is a continuation of [ding.TING](http://ting.dk/content/om-dingting) [Drupal](http://drupal.org/project/drupal) distribution for libraries as part of the [TING concept](http://ting.dk).

# Installation
This read me assumes that you have installed a working web-server with Apache/Nginx, APC, Memcached, PHP 5.4 (_optional_ varnish) and that you have tested your setup.

## Dependencies
* [Drupal 7.23](https://drupal.org/drupal-7.23-release-notes) The latest stable version of Drupal Core that ding2 have been tested on and the last stable release when this was written.
* [Drush 6.1.0](https://github.com/drush-ops/drush) Which has build in drush make API version 2 and was the latest release when this was written. See it's readme for installation instructions.

# Build instructions
Download a fresh copy of Drupal and make sure that it's ready to begin the installation process (e.g. your LAMP stack is configured).

## Drush utils
The ding2 makefiles uses nested makefiles (each module have its own dependencies), which results in projects and libraries being download more than once. You can work around this by cloning the [drush-ding2-utils](http://github.com/ding2tal/drush-ding2-utils) into your .drush folder.
```sh
  ~$ cd ~/.drush
  ~$ git clone http://github.com/ding2tal/drush-ding2-utils.git drush-ding2-utils
```

## Drupal
Go into your web-root and execute this drush command to download Drupal version 7.23, you omit the version number the newest version will be downloaded.
```sh
  ~$ drush dl drupal-7.23
  ~$ mv drupal-7.23/* .
  ~$ mv drupal-7.23/.* .
  ~$ rm -r drupal-7.23
```

### Patches
You need to apply a set of patches to Drupal core to run the installation and the site after the installation. To apply the patch go into your Drupal installation path and execute the commands below.

This [patch](https://drupal.org/node/1232346) fixes a problem with recursive menu rebuilds.
```sh
  ~$ cd DRUPAL
  ~$ wget -qO- http://drupal.org/files/menu-get-item-rebuild-1232346-22_0.patch | patch -p1
```

This [patch](https://drupal.org/node/1879970) ensure that communication with web-services that runs OpenSSL v1.0.x or newer works.
```sh
  ~$ cd DRUPAL
  ~$ wget -qO- http://drupal.org/files/ssl-socket-transports-1879970-13.patch | patch -p1
```

Ding2 sites uses the [CacheTags](http://drupal.org/project/cachetags) 2.x module, which require core to be patched.
```sh
  ~$ cd DRUPAL
  ~$ wget -qO- http://drupalcode.org/project/cachetags.git/blob_plain/refs/heads/7.x-2.x:/cachetags.patch | patch -p1
```

## Ding2 installation profile
Go into your Drupal installation path and into the profiles folder.
```sh
  ~$ cd DRUPAL/profiles
```

Clone the ding2 profile repository from http://github.com/ding2tal.
```sh
  ~$ git clone git@github.com:ding2tal/ding2.git ding2
```

Now that you have cloned the installation profile you need to run the build process using drush make. It will download all the modules and the theme from http://github.com/ding2tal
```sh
  ~$ cd DRUPAL/profiles/ding2
  ~$ ~$ drush --ding2-only-once --strict=0 make --concurrency=1 --no-core --contrib-destination=. ding2.make
```

If you want a developer version with Git working copies, run this command instead. This is because drush automatically deletes _.git_ after it has cloned the repositories and by adding _--working-copy_ it will not delete these.
```sh
  ~$ drush --ding2-only-once --strict=0 make --concurrency=1 --no-core --working-copy --contrib-destination=. ding2.make
```

Next goto your sites URL and run the ding2 installation profile.


### Note
The fix in [drush-ding2-utils](http://github.com/ding2tal/drush-ding2-utils) uses drush cache and to build the site more than once within 10 min of each other you will need to clear the cache. This also applies if the build fails and you need to rebuild.
```sh
  ~$ drush cc drush
```

# Post installation
After you have finished the installation there are some performance optimization that you should put into your settings.php file.

## Drupal cache

```php
  $conf['cache'] = 1;
  $conf['block_cache'] = 1;
  $conf['preprocess_css'] = 1;
  $conf['preprocess_js'] = 1;

  // Ensures that form data is not moved out of the database.
  $conf['cache_class_cache_form'] = 'DrupalDatabaseCache';
```

## APC

```php
  $conf['cache_backends'][] = 'profiles/ding2/modules/contrib/apc/drupal_apc_cache.inc');
  $conf['cache_class_cache'] = 'DrupalAPCCache';
  $conf['cache_class_cache_bootstrap'] = 'DrupalAPCCache';
```

## Memcache
This optimization assumes that you have memcached installed on your server.

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

### CacheTags
Cache tags extendes Drupals default caching with tags, so the cache can be divided into logic parts.

```php
  $conf['cache_backends'] = array('profiles/ding2/modules/contrib/cachetags/cache-memcache.inc');
  $conf['cache_class_???'] = 'DrupalMemcacheCacheTagsPlugin';
  $conf['cache_tags_class'] = 'DrupalMemcacheCacheTags';
```
