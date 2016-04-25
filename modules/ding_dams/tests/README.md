Selenium tests for DDB CMS
==========================

Latest changes viable for ding2 tag: `7.x-2.3.1`
All tests are grouped in files, by area of testing.
Method name denotes the tested feature.

Dependencies
------------
* PHPUnit with Selenium testing package
* Firefox browser
* Selenium server
* JRE (for Selenium server)
* Xvfb (for server machines, headless Firefox launch)
* Composer

Installation
------------
1. Run `composer install` inside the cloned repository. This will download the phpUnit dependency.

2. Setup following environmental variables:

   `DDBTEST_BROWSER` - '*firefox' as default
   `DDBTEST_URL` - target url where the test should run
   `DDBTEST_LOCALE` - language code, set to 'en'
   `DDBTEST_USER` - test user, see dummy_alma repo.
   `DDBTEST_PASS` - test user pass, see dummy_alma repo.
   `DDBTEST_LMS` - Dummy alma LMS url.
   
3. Install Firefox browser:

   `apt-get install firefox`

4. Download Selenium2 server:

   [http://selenium-release.storage.googleapis.com/2.48/selenium-server-standalone-2.48.2.jar]
   
   `wget http://selenium-release.storage.googleapis.com/2.48/selenium-server-standalone-2.48.2.jar`
   
   _----- (Server only from here) -----_

5. Install Xvfb (X virtual frame buffer):

   `apt-get install xvfb`
   OR
   `yum install Xvfb`

Usage
-----
### Desktop
1. Launch Selenium2 server (JRE should be installed):

   `java -jar PATH_TO_DOWNLOADED_SELENIUM_SERVER.jar -interactive`
   
2. Move to this repo root and in Terminal type:

   `vendor/bin/phpunit`

   This will read the configuration from `phpunit.xml` and launch all tests sequentially.

### Server, headless Firefox
1. Launch Xvfb by executing the following commands in terminal:

   `export DISPLAY=:99`
   
   `/usr/bin/Xvfb ${DISPLAY} -ac -screen 0 1920x1080x24 &`
   
   This launches a virtual diplay with a number of 99, FullHD resolution and 24 bit depth.
   
2. Launch Selenium2 server:

   `java -jar PATH_TO_SELENIUM.jar -interactive &`

3. Move to this repo root and in terminal type:

   `./vendor/bin/phpunit`
   
   There should be an output like this:
   ```
   PHPUnit 4.5.0 by Sebastian Bergmann and contributors.
   
   Configuration read from C:\www\work\ding2tal-selenium\phpunit.xml
   
   ................
   
   Time: 5.9 minutes, Memory: 3.50Mb
   
   OK (16 tests, 436 assertions)
   ```

Prerequisites
-------------
Any settings different from these, can lead to some assertions fail.
Some of the assertions might fail as well, due to changed responses from various servies (e.g.: OpenSearch).

### Webservices
The tests cover the ding2 `7.x-2.3.1` clean installation with the following settings:
- `/admin/config/ting/settings`
- TING OpenSearch agencyId:   **775100**
- TING OpenSearch Profile:    **ding2taltest**
- TING OpenSearch URL:        **http://opensearch.addi.dk/4.0.1/**
- `/admin/config/ding/provider/alma`
- Provider:                   ***ALMA***
- Provider URL:               ***http://dummy-alma.inlead.dk/web/alma/***
- Enable reservation deletion: ***On***
- `/admin/config/ting/covers/addi`
- ADDI Service:               **http://moreinfo.addi.dk/2.1/**
- Addi Group:                 ***(Anyone)***
- Addi User:                  ***(Anyone)***
- Addi Pass:                  ***(Anyone)***
- `/admin/config/ting/autocomplete`
- Autocomplete URL:           **http://opensuggestion.addi.dk/b3.0_2.0/**
- Autocomplete method:        **facets**
- Match index:                **scanterm.default**
- Facet Index:                **scanphrase.default**
- Agency and profile:         ***(similar to TING OpenSearch settings)***

A test provider, separated from real one, can be found @ https://github.com/easyddb/dummy_alma/.
This project emulates alma provider with most of the calls real ALMA provides.
Usage of such dummy provider allows to have a fixed, yet responsive, set of data returned from the service.

### Other
Enable English locale and make sure it's set by default.
Also set the language detection to use URL prefix at: `/admin/config/regional/language/configure`
