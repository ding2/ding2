# Overview of the behat suite

The test suite has been automated to provide documentation of checks that DDB often perform on new versions of DDB CMS. 
The suite has been redesigned in 2017 to add robustness and setup a framework that can be used in future testing activities.

This documentation outlines the guiding principles and practices for maintaining and extending the suite.

## About the behat tool

Behat is a member of the cucumber family of automation tools and as such has roots in the BDD methodology. While BDD has many good things, cucumber remains a nice automation tool even if the BDD philosophy is not being used.

The automation is divided into layers that makes maintenance and extension easy as well as providing robustness towards changes.

The top layer is the Gherkin scripts. These are written in near-normal english, guided by Given, When, Then-keywords. Because these are readable by humans it provides good documentation of what the script and the check is about.

The underlying glue layer is in PHP. This means that the power of the entire programming language is at our disposal, so there is few limits on what the automation can do. 

By using classes to encapsulate functionality and interactions concerning the different parts of the DDB CMS site, it is possible to further add layers into the code, thus making it more maintainable and less-to-not redundant. 
Plus it adds the possibility to handle test data in an orderly way. 

When working with behat, please don't get hung up on BDD as philosophy. We can still use the tool with great benefits. 

## Principles in the current suite

The whole purpose of the suite is to provide easy and quick information to the testers about the state of DDB CMS in a certain version. This means that the following principles are put into use:

* The automation is to be as robust as possible
* Information about errors and deviances is to be logged whenever possible
* Failures should be trustworthy.

With robustness comes checks on the automation itself. One of the great things about behat is that it deals with any errors that occur in a civilised way. But here we want to inform the testers as good as possible about why the error occurs, and minimize the errors that stems from the automation itself.

As an example consider the following piece of code:
```sh
  $field = $this->find('css', '.ting-object a');
  return $field->getText();
```

The code looks for a hypertext link somewhere in the page structure, and seeks to return the link-text. 
If the css-locator '.ting-object a' cannot be found, then the variable $field will be null.
This is alright until the return-statement which will fail because we try to use a function on a null object. Behat will catch this automatically, fail the scenario on the corresponding step, and that's great. Except, we will only get an incomprehensible message in the log file, like "cannot invoke function on null object" and leave a screenshot in a .png-file.
This tells very little about where the code went wrong and even the screenshot is of little help, because - what to look for?

To inform better, consider the following code:
```sh
  $field = $this->find('css', '.ting-object a');
  if (!$field) {
    throw new Exception ("Did not find link to xxx on the page.");
  }
  return $field->getText();
```
This is more work to do automation, but it informs well about what went wrong and makes the automation more valuable that way. It's important to view the automation code with the perspective of a tester: don't anticipate that the site actually works. Be sceptical.

## Practises in use

Here is a list of the ways the current suite solves various problems.

### Structure of code

There are two context-files, LibContext and StepsContext. They are considered equally good to hold step definitions, with the emphasis on having more generally applicable or reused functions in LibContext rather than StepsContext. 
Classes are instantiated in LibContext, which in turns is referenced in StepsContext. The hierarchy is thus:
StepsContext->LibContext->Classes...

### Naming of scenarios
The scenarios are named seekXXX where XXX is
the number of the row in the spreadsheet
describing the redroutes. The sequence is not
necessarily sequential, ie. numbers will
be missing, because those checks are not
selected for implementation or not valid for
different reasons.

### Environment variables

The behaviour of the behat test suite can be influenced with certain
environment variables:

- `SCREENSHOT_DIR`: Directory to save screenshots to.
- `SCREENSHOT_FEATURE_FOLDER`: If `true`/`yes`, create a directory for
  each feature.

### Injecting classes into context-file

Read here: http://behat-page-object-extension.readthedocs.io/en/stable/guide/working_with_page_objects.html#injecting-page-objects-into-a-context-file

### Logging

Data and information can be put into the behat log file using the functions in the class LogMessages, which inherits Page and is incorporated in all classes that inherits PageBase.
```sh
$this->logMsg(__condition__, __text__);
```
will log text into a message list, if condition is true. 
```sh
$this->getMessages(); 
```
will print all the messages in the list into the behat logfile. This is particular useful when examining complex checks, like listing search results that are not sorted correctly, for instance. Instead of failing on the first wrongly sorted item, the full list is collected so the tester has a better chance of seeing the extend - and maybe even the cause - of the problem. 

### Class-functions returns string on failure

Classes do not throw exceptions. They provide a service, and functions in general returns a string value which indicates success if it's empty, and otherwise contains the error message.

LibContext contains the function "check(__resultstring__, __msg__)" which will check on whether the resultstring is empty. If not, the msg string will be added to the behat log and an exception containing the resultstring is thrown. 

Typical use:
```sh
   $this->check($this->searchPage->checkXXX(), $this->searchPage->getMessages);
```
Here we will print the messages that will be generated during the checkXXX() function and throw an exception if that function returns a non-empty string.

### DataManager

The DataManager class handles values from files and checks on PID being reservable according to Connie provider conventions. 
A number of files are to be provided for this, containing PIDs with certain characteristics. In this way we can search for particular objects, known to us. 
This needs to be extended at some point to incorporate data from known library codes - this far 100200 test library code is anticipated to be in use. 

The data is organised so that the filename reflects the characteristic, f.ex. "creatorDesc.mat" contains pids with creatorDescriptions. 

The corresponding gherkin commands that controls this are:
```sh
  Given filename 'creatorDesc.mat' is used
  Given I only want reservables
  When I display random object from file
```
This sequence will
* fetch pids from the file named 'creatorDesc.mat', located in the behat-root dir
* require pids to be reservable according to Connie conventions
* go to the /ting/object/pid page for a randomly selected pid from the file

Per default the randomly chosen pid from the file is not necessarily reservable. If "Given I only want reservables" is omitted the object will be either non-reservable or reservable. When it is stated in the script only reservable objects are found.

The files contain a limited amount of pids only.

### Verbose and Control modes

Classes may contain verbose and control settings, which are accessible through functions to set or unset them. They will have default settings that are resp. silent and unlimited.

Currently the following verbose settings are in searchPage:
```sh
  Given I set verbose mode for "search-Results" to be "on"  # default off
  Given I set control mode for "searchMaxPages" to be "1"   # default 0
```

The first will print the title, author and publishing date of the found search results, when they are handled, for instance with "When pagination allows to get all the results".

The second will make all subsequent (within the scenario) steps look only on 1 page, ie. the first page. Set it to 0 for no limit.

In PageBase we have the following:
```sh
  Given I set verbose mode for "cookies" to be "on"   # default off
```

This will display information about if cookie agree button is shown and clicked away using "Given I accept cookies".

### variable substitution

It is possible on certain gherkin steps to give a string value starting with $.
The syntax is $ modifier : source and this far the following can be used:

* source can be "news" - for which modifier can be random, first or last.
* source can be "lastsearchstring" - for which modifier can be get.

"news" are taken from the current page, ie. if used while not on a page with news elements, this will fail. Given I have searched for "$random.news" will pick a random news title from the page and insert as lastsearchstring.
Then I can see "$get:lastsearchstring" - will then use that news item.

More variables will be added over time, no doubt.

###  tags

Scenarios are tagged in gherkin, which makes it possible to select individual scenarios or groups.
The following conventions are used:

@regression - all scenarios which should run for normal regression testing. This will be pretty much all scenarios.

@no_ci - don't run these scenarios during the automatic test on circleCI. See paragraph on CircleCI.

@api - indicates that the chrome browser is to be used. This is put on all scenarios.

@seekNNN - refers to search-tests in the redroute spreadsheet, where NNN is the line. @seek007 refers to test of pagination, f.ex. Some lines have multiple tests, and thus multiple scenarios can be marked with the same number.

@seekNologin - refers to all @seekNNN scenarios where logging in is not performed. These can be run against any test-site.

@seekLogin - refers to all @seekNNN scenarios where logging in is attempted. To succeed the testsite must have Connie as provider. 

### Logging in

To login behat requires Connie as provider for the testsite. Currently 20 users are known, and a random will be used on every login. At login the chosen user will be written to the behat log for reference.
Connie requires the last 4 letters to be given as password.

### versioning

The behat code should always follow the cms code version. 

### CircleCI

A subset of the regression suite is designed to be run after each push of a branch.
The subset is defined based on the following limitations:
- not all configurations can be made to the testsite that is spun up.
- some tests may need human checkup, like sorting.
- some tests are not compatible with the local testsite.

Currently (January 2018) the following limitations exists:
- Openscan integration cannot be enabled using drush
- Cover pages cannot be shown, because that will require credentials to be put into source code for configuration
- data are expected to come from opensearch test, v4.5, agency 100200.
- sorting is not machine-deterministic and should not stop a build.
- default news are not loaded into a testsite, so internal search cannot be tested.






