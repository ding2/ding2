# Installation

The tests folder (profiles/ding2/tests) contains a composer.json file,
so it's straightforward to install with composer.

Just `composer install` and you're set.

## Phantomjs

### Install

There are several ways to install Phantomjs. One way is to use a Phantomjs installer, e.g.
[phantomjs-installer](https://github.com/jakoch/phantomjs-installer).

Make a folder somewhere on your
disk and write the following in a composer.json file:
```
{
    "require": {
        "jakoch/phantomjs-installer": "1.9.8"
    },
    "scripts": {
        "post-install-cmd": [
            "PhantomInstaller\\Installer::installPhantomJS"
        ],
        "post-update-cmd": [
            "PhantomInstaller\\Installer::installPhantomJS"
        ]
    }
}
```

Then you can install the Phantomjs installer by using `composer install`.

### Run

Running the Phantomjs webdriver:
```
 # Change dir to your phantomjs folder.
 ./bin/phantomjs --webdriver=127.0.0.1:4444
```

Port 4444 is the default port. The default Behat configuration uses this port.

## Selenium

### Install

There are several ways you can run Selenium with Firefox or Chrome.
One way is to install a Selenium standalone server from
[Selenium HQ](http://www.seleniumhq.org/download/).

### Run

Run the Selenium standalone server with default settings:
```
java -jar selenium-server-standalone-2.48.2.jar
```

Selenium can also run phantomjs if installed.
