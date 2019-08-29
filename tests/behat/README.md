# Behat regression suite checks

Suite for automated checking of DDB CMS.

#### Docs
Guidelines: `profiles/ding2/tests/behat/docs/Guidelines.md`  
Maintenance: `profiles/ding2/tests/behat/docs/Maintenance.md`

## Preparation

Check out the code. Install Behat. Install browser-support.

#### Installing Behat

From a working Ding2 environment:

1. Make sure that [Composer is installed](https://getcomposer.org/download/)
2. Go to the `profiles/ding2/tests/behat` directory
3. Run `path/to/composer install`

#### Behat Version Notes
Behat version is currently locked at `3.3.1` and Gherkin at `4.4.5`. There is and open bug 
([#1085](https://github.com/Behat/Behat/issues/1085)) in later versions that result in a 
"No specifications found at path" error when using the Drupal API driver.

#### Install browser-support

Ensure that you have a recent version of the Chrome browser available 
(version 60+).

## Structure

The entire suite is under `profiles/ding2/tests/behat`. Here you will find 
config-files, most importantly `behat.yml`. In the directory features you will 
find the `.feature-files, which contains the scenarios, written in Gherkin. 
Under `features/bootstrap` you will find the `.php` files, which contains all 
the code that will run, and which is mapped to the Gherkin methods/steps 
(given/when/then).

## How to run

1. Launch Chrome with Developer Tools listening on port 9222: 
    - Linux: `google-chrome-stable --remote-debugging-address=0.0.0.0 --remote-debugging-port=9222`
    - OSX: `/Applications/Google\ Chrome.app/Contents/MacOS/Google\ Chrome --remote-debugging-address=0.0.0.0 --remote-debugging-port=9222`
    - Windows: `start chrome --remote-debugging-address=0.0.0.0 --remote-debugging-port=9222`
2. Set up an environment variable `BEHAT_PARAMS` containing the URL of the 
website you want to test
3. Select the tags (`@xyz) from the scenarios you want to run in the 
`.feature-files`
4. Run `behat` by giving the tags and the browser config you want to use as
parameters

#### Example

```sh
% export BEHAT_PARAMS='{"extensions" : {"Behat\\MinkExtension" : {"base_url" : "http://localhost/"}}}'
% behat --tags=@simplesmoke,@anothertag -p chrome
```

#### Tips

PHPStorm users: You can run tests from a run configuration but you have to 
insert this env variable with a sensible value in your run configuration.
If you want to avoid this you can temporarily insert the `base_url` parameter in 
the `behat.yml`-file:

```yaml
    Behat\MinkExtension:
      browser_name: chrome    
      base_url: http://localhost/
```

Another hint is to create a file, f.ex. ".vanilla", containing the BEHAT_PARAMS
export, and then source it. By having a series of files like that it is easy
to switch between test sites:

```sh
% cat .vanilla
export BEHAT_PARAMS='{"extensions" : {"Behat\\MinkExtension" : {"base_url" : "https://vanilla-fbs.ddbcms.dk/"}}}'
% source .vanilla
```
