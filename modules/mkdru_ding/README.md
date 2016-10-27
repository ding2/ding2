DEPLOYMENT STEPS FOR MKDRU AND MKDRU_DING
-----------------------------------------

1. Checkout the core 'mkdru' module, for ding2 use the '7.x-1.x' branch, 
and for ding1 the '6.x-1.x' one (what follows assumes you run againts ding2):

 - read-only

  ```
  git clone --branch 7.x-1.x http://git.drupal.org/project/mkdru.git

  ```

 - read-write

  ```
  git clone --branch 7.x-1.x 'username'@git.drupal.org:project/mkdru.git

  ```

 More info: <http://drupal.org/project/mkdru/git-instructions>. Module tarballs 
can be downloaded from the project page in case you don't want to use Git.


2. Checkout the mkdru_ding integration module from GitHub:

 - read-only

  ```
  git clone --branch 7.x-1.x http://git://github.com/indexdata/mkdru_ding.git

  ```

 - read-write

  ```
  git clone --branch 7.x-1.x git@github.com:indexdata/mkdru_ding.git

  ```

3. Symlink both modules under your/drupal/sites/all/modules


4. Enable the modules and configure the ding integration one:

  - enable the pazpar2 search tab under admin/config/search/settings

  - add gateway settings to admin/config/search/mkdru_ding (see below)


5. Configure Apache proxy for the Universal Search gateway

 Mkdru uses Ajax to request data from the metasearch gateway and as such is 
subject to the JS same-domain policy. We need to proxy the gateway requests
using an Apache mod_proxy

 - on Debian make sure mod_proxy is enabled with `a2enmod proxy_http`

 - edit your Drupal vhost config (usually under `/etc/apache2/site-available/`)
 with the following settings:

  ```
  <Proxy *>
    Order deny,allow
    Allow from all
  </Proxy>

  ProxyPass /service-proxy/ http://pz2.dbc.dk/service-proxy/
  ProxyPassReverse /service-proxy/ http://pz2.dbc.dk/service-proxy/
  
  ProxyPreserveHost Off
  ````

 - make sure that under `admin/config/search/mkdru_ding` settings the 
 Service-Proxy path is set to `/service-proxy/` (or whatever else was 
 configured above) and the "session handling" checkbox is unchecked

 - provide username/password for the US gateway


6. Download and install external JS libraries

 Drupal policies forbid to re-distribute third party libraries within the
modules so you will need to fetch them on your own:

 - [get](http://benalman.com/projects/jquery-bbq-plugin/) jQuery-BBQ and place
 it in the `mkdru` module directory

 - get `pz2.js` library, on Debian `apt-get install pazpar2-js` (assuming Index
 Data sources are [enabled](http://ftp.indexdata.dk/debian/README)) on other 
 systems, get the library from [here](http://mk2.indexdata.com/pazpar2/js/pz2.js)
 and make available within your Apache vhost using the following directive:

  ```
  Alias /pazpar2/js/pz2.js /path/to/pz2.js
  ```
