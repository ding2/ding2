# Behat regression suite checks

Suite for automated checking of DDB CMS.


## Preparation

Install Behat.
Check out the code.
Install browser-support.

#### installing Behat

_Development machine:_
If you use PHPStorm open the project and add the composer dependency "behat/behat".
Version should be at least 3.4.
Add the other dependencies, as described in the server-installation, see below.
(notice, phpstorm requires you to have php.mbstring installed (sudo apt install php.mbstring))


_Server installation:_
Create a directory where you want the installation to be.
In this, create a composer.json file and run the composer on it.
```sh
% cat <<EOF > composer.json
{
    "require-dev": {
        "sensiolabs/behat-page-object-extension": "^2.1",
        "jarnaiz/behat-junit-formatter": "^1.3",
        "Drupal/Drupal-Extension": "^3.3",
        "emuse/behat-html-formatter": "^0.1.0"
    },
    "config": {
        "bin-dir": "bin/"
    },
    "require": {
        "behat/behat": "^3.4",
        "behat/mink": "^1.4@stable",
        "behat/mink-extension": "^2.2",
        "behat/mink-goutte-driver": "^1.2",
        "behat/mink-selenium2-driver": "^1.3",
        "michaelc/intdiv-compat": "^1.0",
        "paragonie/random_compat": "^2.0"
        "curl/curl": "^1.8"
    }
}
EOF
% composer update
```
(this requires of course that composer is already installed. That's beyond the scope of this 
instruction. You can find instructions on http://docs.behat.org/en/v2.5/quick_intro.html).

NB: the PHP modules you will need for this are:
* sudo apt install phpx.x-cli  (where x.x is the php version)
* sudo apt install php-xml


## Structure

The entire suite is under profiles/ding2/tests/behat.
Here you will find config-files, most importantly behat.yml.
In the directory features you will find the .feature-files, which
contains the scenarios, written in gherkin.
Under features/bootstrap you will find the .php files, which
contains all the code that will run, and which is mapped to
the gherkin methods/steps (given/when/then).

## How to run
* set up an environment variable BEHAT_PARAMS containing the URL of the website you want to test
* select the tags (@xxx) from the scenarios you want to run in the .feature-files
* run behat by giving the tags as parameter and the browser/browser config you want to use



```sh
% export BEHAT_PARAMS='{"extensions" : {"Behat\\MinkExtension" : {"base_url" : "http://localhost:32770/"}}}'
% behat --tags=@simplesmoketest,@anothertag -p chrome
```

PHPStorm: notice, you will need to insert this env variable with a sensible value in your run configuration.
If you want to avoid this you can
temporarily insert the base_url parameter in the behat.yml-file:

```sh
    Behat\MinkExtension:
      goutte: ~
      browser_name: 'chrome'
      base_url: http://localhost:32770
```

Another hint is to create a file, f.ex. ".vanilla", containing the BEHAT_PARAMS
export, and then source it. By having a series of files like that it is easy
to switch between test sites:
```sh
% cat .vanilla
export BEHAT_PARAMS='{"extensions" : {"Behat\\MinkExtension" : {"base_url" : "https://vanilla-fbs.ddbcms.dk/"}}}'
% source .vanilla
```
