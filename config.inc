<?php
// Target browser. By default, tests were created under firefox.
define('TARGET_BROWSER', isset($_SERVER['DDBTEST_BROWSER']) ? $_SERVER['DDBTEST_BROWSER'] : '*firefox');
// Target URL. Which site to run tests on.
define('TARGET_URL', isset($_SERVER['DDBTEST_URL']) ? $_SERVER['DDBTEST_URL'] : 'http://ding2tal.easyting.dk');
// Site locale. By default, tests were created under EN language.
define('TARGET_URL_LANG', isset($_SERVER['DDBTEST_LOCALE']) ? $_SERVER['DDBTEST_LOCALE'] : 'en');
// Test user credentials.
define('TARGET_URL_USER', isset($_SERVER['DDBTEST_USER']) ? $_SERVER['DDBTEST_USER'] : '1111110022');
define('TARGET_URL_USER_PASS', isset($_SERVER['DDBTEST_PASS']) ? $_SERVER['DDBTEST_PASS'] : '5555');
