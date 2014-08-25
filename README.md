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
1. Install PHPUnit via PEAR (or composer):

   If installing with PEAR make sure `--alldeps` flag is used.
   
   `pear channel-discover pear.phpunit.de`
   
   `pear install --alldeps phpunit`
   
2. Install Selenium PHPUnit library:

   `pear install phpunit/PHPUnit_Selenium`
   
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
   
2. In Terminal, type: `phpunit ClassName filename.php`

   (ex.: `phpunit SearchResult SearchResultTestSuite.php`)

### Server, headless Firefox
1. Launch Xvfb

   `export DISPLAY=:99`
   
   `/usr/bin/Xvfb ${DISPLAY} -ac -screen 0 1920x1080x24 &`
   
2. Launch Selenium2 server

   `java -jar PATH_TO_SELENIUM.jar -interactive &`

3. Launch PHPUnit Selenium tests

Prerequisites
-------------
Any settings different from these, can lead to some assertions will fail.
Some of the assertions might fail as well due to changed data response (OpenSearch).

### Webservices
The tests cover the ding2tal ddb-rc8 clean installation with the following settings:
- TING OpenSearch agencyId:   **100200**
- TING OpenSearch Profile:    **test**
- TING OpenSearch URL:        **http://opensearch.addi.dk/3.0/**
- Provider:                   ***Anyone***
- Provider URL:               ***Anyone***
- ADDI Service:               **http://moreinfo.addi.dk/2.1/**
- Addi Group:                 ***Anyone***
- Addi User:                  ***Anyone***
- Addi Pass:                  ***Anyone***

### Other
Enable english locale and make sure it's set by default. Also set the language
detection to use URL prefix: `admin/config/regional/language/configure`



