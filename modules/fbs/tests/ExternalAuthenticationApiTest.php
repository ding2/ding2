<?php

namespace FBS;

require_once 'vendor/autoload.php';

use Reload\Prancer;
use Reload\Prancer\Serializer\JsonMapperSerializer;
use Reload\Prancer\HttpClient;
use JsonMapper;
use Phly\Http\Response;
use Phly\Http\Request;
use Phly\Http\Stream;

use Prophecy\Argument;

class ExternalAuthenticationApiTest extends \PHPUnit_Framework_TestCase
{

    public function testLogin()
    {
        $prophecy = $this->prophesize('Reload\Prancer\HttpClient');

        // Invalid login.
        $prophecy->request(Argument::that(function ($request) {
            $this->assertEquals('/banana/external/v1/1234/authentication/login', $request->getUri()->getPath());
            return strpos((string) $request->getBody(), 'badpass') !== false;
        }))->will(function ($args) {
            return new Response('php://memory', 403);
        });


        $httpclient = $prophecy->reveal();
        $jsonMapper = new JsonMapperSerializer(new JsonMapper());
        $authApi = new ExternalAuthenticationApi('banana/', $httpclient, $jsonMapper);

        $login = new Model\Login();
        $login->username = 'banan';
        $login->password = 'badpass';
        try {
            $authApi->login('1234', $login);
        } catch (\RuntimeException $e) {
            $this->assertEquals(403, $e->getCode());
            $this->assertEquals('invalid client credentials', $e->getMessage());
        }

        // Valid login.
        $prophecy = $this->prophesize('Reload\Prancer\HttpClient');
        $prophecy->request(Argument::that(function ($request) {
            return strpos((string) $request->getBody(), 'goodpass') !== false;
        }))->will(function ($args) {
            $userInfo = array(
                'sessionKey' => md5('randomness'),
            );
            $res = new Response(new Stream('php://memory', 'w'), 200);
            $res->getBody()->write(json_encode($userInfo));
            return $res;
        });

        $httpclient = $prophecy->reveal();
        $jsonMapper = new JsonMapperSerializer(new JsonMapper());
        $authApi = new ExternalAuthenticationApi('banana/', $httpclient, $jsonMapper);

        $login->password = 'goodpass';
        $res = $authApi->login('1234', $login);
        $this->assertInstanceOf('FBS\Model\ExternalAPIUserInfo', $res);
        $this->assertNotEmpty($res->sessionKey);
    }
}
