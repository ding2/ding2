<?php

require_once 'includes/classes/FBS.php';

use Phly\Http\Response;
use Phly\Http\Stream;
use Prophecy\Argument;
use Reload\Prancer\HttpClient;
use Reload\Prancer\Serializer\JsonMapperSerializer;

class ExternalAuthenticationApiTest extends \PHPUnit_Framework_TestCase
{

    /**
     * Test that we get a proper result when using FBS class.
     *
     * Basically a re-implementation of ExternalAuthenticationApiTest.
     */
    public function testAuthentication()
    {
        $httpclient = $this->prophesize('Reload\Prancer\HttpClient');

        // Invalid login.
        $httpclient->request(Argument::that(function ($request) {
            $this->assertEquals('/banana/external/v1/1234/authentication/login', $request->getUri());
            return strpos((string) $request->getBody(), 'badpass') !== false;
        }))->will(function ($args) {
            return new Response('php://memory', 403);
        });

        $httpclient = $httpclient->reveal();
        $jsonMapper = new JsonMapperSerializer(new JsonMapper);
        $fbs = new FBS('123', 'banana/', $httpclient, $jsonMapper);

        $login = new \FBS\Model\Login();
        $login->username = 'banan';
        $login->password = 'badpass';
        try {
            $fbs->Authentication->login('1234', $login);
        } catch (\RuntimeException $e) {
            $this->assertEquals(403, $e->getCode());
            $this->assertEquals('invalid client credentials', $e->getMessage());
        }

        $httpclient = $this->prophesize('Reload\Prancer\HttpClient');

        // Valid login.
        $httpclient->request(Argument::that(function ($request) {
          return strpos((string) $request->getBody(), 'goodpass') !== false;
        }))->will(function ($args) {
          $userInfo = array(
            'sessionKey' => md5('randomness'),
          );
          $res = new Response(new Stream('php://memory', 'w'), 200);
          $res->getBody()->write(json_encode($userInfo));
          return $res;
        });

        $httpclient = $httpclient->reveal();
        $jsonMapper = new JsonMapperSerializer(new JsonMapper);
        $fbs = new FBS('123', 'banana/', $httpclient, $jsonMapper);

        $login->password = 'goodpass';
        $res = $fbs->Authentication->login('1234', $login);
        $this->assertInstanceOf('FBS\Model\ExternalAPIUserInfo', $res);
        $this->assertNotEmpty($res->sessionKey);


    }
}
