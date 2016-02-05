# Initial setup #

In order to have a consistent test site to run tests on, it needs to
be set up in a specific way. There's a standard Unix Makefile in the
test directory that'll do just that:

```
cd profiles/ding2/tests
make test-setup
```

## Running Behat ##

Running Behat with default settings using Goutte/Phantomjs:

```
cd profiles/ding2/tests
./bin/behat --tags "~wip"
```

The tag @wip is used to indicate "work in progress" which means, that
it's not finished and might fail. We don't want to run tests that we
know are going to fail. If you want to run the tests without the
regression tests, you can use `./bin/behat --tags "~wip" --tags
"~regression"`.

### Tags ###

In addition to using tags to select features/scenarios from the
command line, some tags modify the behavior of some Behat extensions.
List of currently used tags:

 * `@api` Causes the Drupal extension to bootstrap it's driver, which
   most importantly makes it possible to log in.

 * `@wip` Work In Progress. Not run on Circle CI.

 * `@regression` Regression test. Tests for an existing bug. Ensures
   it doesn't reappear. Also, writing a regression test before fixing
   a bug and coding until it turns green is an excellent way to work.

 * `@javascript` Scenario needs a browser that supports JavaScript.
   Makes Mink use phantomjs rather than goutte in the default profile.

 * `@no_messages_check` The default setup tests for unexpected
   warnings and errors (from `drupal_set_message()`) and fails the
   scenario if any occur. This tag suppresses that test.

 * `@no_circle_selenium` Don't run test on Selenium on Circle CI.
   Temporary workaround. FontAwesome does not work on the test site
   Circle builds, for some reason, which makes some tests fail as
   Selenium can't click on an empty element. This tag is used on
   the rating tests (the stars are from FontAwesome).

### Profiles ###

Behat is configured with three profiles, which can be selected with
the -p switch.

The `default` profile runs test using goutte and phantomjs for tests
that require JavaScript. You need to manually start phantomjs.

The `chrome` and `firefox` profiles runs in the named browser using
Selenium. You need to manually start the Selenium server.

See [Installation](./install.md) on how to run phantomjs and Selenium.
