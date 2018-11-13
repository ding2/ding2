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
   `DDBTEST_USER` - test user, see dummy_alma repo.
   `DDBTEST_PASS` - test user pass, see dummy_alma repo.
   
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

