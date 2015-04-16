Selenium tests for DDB CMS
==========================

Edit the `config.inc` file to set specific testing settings.
Latest changes viable for ding2tal branch: ddb-rc8.
All test are grouped in files, by area of testing.
Method name denotes the tested feature.

Dependencies
------------
* PHPUnit with Selenium testing package
* Firefox browser
* Selenium server
* JRE (for Selenium server)
* Xvfb (for server machines, headless Firefox launch)

Installation
------------
1. Run `composer install` inside the cloned repository.

2. Setup following environmental variables:

   `DDBTEST_BROWSER` - '*firefox' as default
   `DDBTEST_URL` - target url where the test should run
   `DDBTEST_LOCALE` - language code, set to 'en'
   `DDBTEST_USER` - test user, see dummy_alma repo.
   `DDBTEST_PASS` - test user pass, see dummy_alma repo.
   `DDBTEST_LMS` - Dummy alma LMS url.
   
3. Install Firefox browser

4. Download Selenium2 server

   [http://selenium-release.storage.googleapis.com/2.42/selenium-server-standalone-2.42.2.jar]
   
   _----- (Server only from here) -----_

5. Install Xvfb (X virtual frame buffer)

   `apt-get install xvfb`

Usage
-----
### Desktop
1. Launch Selenium2 server (JRE should be installed)

   `java -jar PATH_TO_SELENIUM.jar -interactive`
   
2. In Terminal, type: `vendor/bin/phpunit`

   (ex.: `phpunit SearchResult SearchResultTestSuite.php`)

### Server, headless Firefox
1. Launch Xvfb

   `export DISPLAY=:99`
   
   `/usr/bin/Xvfb ${DISPLAY} -ac -screen 0 1920x1080x24 &`
   
2. Launch Selenium2 server

   `java -jar PATH_TO_SELENIUM.jar -interactive &`

3. Launch PHPUnit Selenium tests in terminal by running

   `vendor/bin/phpunit`
   
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
Any settings different from these, can lead to some assertions will fail.
Some of the assertions might fail as well due to changed data response (OpenSearch).

### Webservices
The tests cover the ding2tal ddb-rc8 clean installation with the following settings:
- TING OpenSearch agencyId:   **100200**
- TING OpenSearch Profile:    **test**
- TING OpenSearch URL:        **http://opensearch.addi.dk/4.0/**
- Provider:                   ***ALMA***
- Provider URL:               ***http://dummy-alma.inlead.dk/web/alma/***
- ADDI Service:               **http://moreinfo.addi.dk/2.1/**
- Addi Group:                 ***Anyone***
- Addi User:                  ***Anyone***
- Addi Pass:                  ***Anyone***

A test provider, separated from real one, can be found @ https://github.com/easyddb/dummy_alma/tree/DDBTEST-77
This project emulates alma provider with most of the calls real one provides.
Usage of such dummy provider allows to have a fixed, yet responsive set of data returned from the service.

### Other
Enable english locale and make sure it's set by default. Also set the language
detection to use URL prefix: `admin/config/regional/language/configure`
