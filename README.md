Selenium tests for Ding2Tal.

Edit the config.inc file to set specific testing settings.
Latest changes viable for ding2tal ddb-rc8 branch.
All test grouped in file by area of testing.
Method name denotes the tested feature.

Prerequisites:
PHPUnit with Selenium testing package.
Firefox browser.
Selenium server.
JRE (for selenium server)
Xvfb (for server machines, headless firefox launch)

Installation:
1. Install phpunit via pear or composer.
   If installing with "pear" make sure --alldeps flag is used.
   pear channel-discover pear.phpunit.de
   pear install --alldeps phpunit
2. Install Selenium phpunit library.
   pear install phpunit/PHPUnit_Selenium
3. Install firefox browser
4. Download Selenium2 server
   http://selenium-release.storage.googleapis.com/2.42/selenium-server-standalone-2.42.2.jar
----- (Server only) -----
5. Install X virtual frame buffer (Xvfb)
   apt-get install xvfb

Usage (desktop):
1. Launch Selenium2 server (JRE should be installed)
  java -jar PATH_TO_SELENIUM.jar -interactive
2. In terminal, type: phpunit ClassName filename.php
  ex.: phpunit SearchResult SearchResultTestSuite.php

Usage (server, headless firefox)
1. Launch Xvfb
  export DISPLAY=:99
  /usr/bin/Xvfb ${DISPLAY} -ac -screen 0 1920x1080x24 &
2. Launch Selenium2 server
  java -jar PATH_TO_SELENIUM.jar -interactive &
3. Launch phpunit selenium tests.

Note:
The tests cover the ding2tal ddb-rc8 clean installation with the following settings:
- Ting agency: 100200
- Ting profile: test
- Provider: alma
- Provider url: https://hjobib.axielldrift.dk:8040/alma/
- Addi service: http://moreinfo.addi.dk/2.1/
- Addi group: 786000
- Addi user: netpunkt
- Addi pass: YOUR_PASSWORD

Enable english locale and make sure it's set by default. Also set the language
detection to use URL prefix.
admin/config/regional/language/configure

Any settings different from those can lead that some assertions will fail.
Some of the assertions might fail as well due to probable ting service data response
changes.
