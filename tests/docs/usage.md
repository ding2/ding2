# Running Behat

Running Behat with default settings using Goutte/Phantomjs:

```
# cd to profiles/ding2/tests
./bin/behat --tags "~wip"
```

The tag @wip is used to indicate "work in progress" which means, that
it's not finished and might fail. We don't want to run tests that we
know are going to fail. If you want to run the tests without the
regression tests, you can use `./bin/behat --tags "~wip" --tags
"~regression"`.

## Profiles

If you want to run the tests in e.g. Firefox via Selenium, you can use
a different profile than the default:

```
./bin/behat -p firefox --tags "~wip"
```
