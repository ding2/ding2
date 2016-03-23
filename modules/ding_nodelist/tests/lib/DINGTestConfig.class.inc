<?php
/**
 * @file
 * Config class implementation.
 *
 * Uses environment variables as a default setting.
 */
class DINGTestConfig
{
    private $browser;
    private $url;
    private $user;
    private $pass;
    private $lms;

    public function __construct()
    {
        $this->browser = isset($_SERVER['DINGTEST_BROWSER']) ? $_SERVER['DINGTEST_BROWSER'] : 'firefox';
        $this->url = isset($_SERVER['DINGTEST_URL']) ? $_SERVER['DINGTEST_URL'] : 'http://md.ding2.dev.inlead.dk';
        $this->user = isset($_SERVER['DINGTEST_USER']) ? $_SERVER['DINGTEST_USER'] : 'admin';
        $this->pass = isset($_SERVER['DINGTEST_PASS']) ? $_SERVER['DINGTEST_PASS'] : '1234';
        $this->lms = isset($_SERVER['DINGTEST_LMS']) ? $_SERVER['DINGTEST_LMS'] : '';
    }


    /**
     * Get the browser that will hold the tests.
     *
     * @return string
     *   Tested browser.
     */
    public function getBrowser() {
        return $this->browser;
    }

    /**
     * Get the target URL, where tests are to run.
     *
     * @return string
     *   Tests target URL.
     */
    public function getUrl() {
        return $this->url;
    }

    /**
     * Get the user login, used for authenticated tests.
     *
     * @return string
     *   User login.
     */
    public function getUser() {
        return $this->user;
    }

    /**
     * Get the user password, used for authenticated tests.
     *
     * @return string
     *   User password.
     */
    public function getPass() {
        return $this->pass;
    }



    public function getLms() {
        return $this->lms;
    }
}