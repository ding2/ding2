# How to write tests #

Writing tests should start from a high level of abstraction and
written in a way that can be used for documentation. The tests should
be divided in scenarios, each of which tests a single functionality.

An example could be that a user logs in, creates a list, and adds some
library material to the list.

The tests should be written in a documentation-wise manner, which
excludes details about the implementation and how the user
specifically interacts with the user interface. Ideally it should be
written, so that if another interface is designed and implemented it
should still make sense. E.g. instead of a web-based interface for
desktop browsers, it's decided to make an old school console
application for black/green Unix terminals with only a keyboard, the
test should not be rewritten for this.

This means that specific details such as "click the login button",
"press the add button", "insert text in this form field" must be
avoided.

Bad example:

``` 
I go to the login page
I click the login button
I insert username "bernhard" in the username field
I insert password "secret" in the password field
...
```

Better example:
```
I log in as "bernhard" using password "secret"
```

Or, in our case, even better:

``` 
I log in to the system as a library user
```

The bad example has way too many details which are directly related to
the actual interface.

The better example abstracts all specific user interface details, as
they are not relevant for the test. If it's decided that in order to
log in you should be able to use a smartcard or a similar device,
which is equivalent of performing a user/password login, this should
not be written in every single test.

The "better example" is appropriate if using a user name and password
combination is part of the specification. In our case, the important
part is that it's a library user, so we leave out the unneeded detail,
which means that the testing code can generate a new user for every
test.

## Behat features ##

Behat features use the Gherkin language [gherkin][gherkin].

[gherkin]: http://docs.behat.org/en/v3.0/guides/1.gherkin.html

A Behat Feature is just one file describing one site feature. A
feature consists of multiple Scenarios that describe different aspects
of how this feature functions. Each scenario consists of preconditions
("Given"), actions ("When") and outcomes ("Then"), all of which are
step definitions.

### Feature organization ###

Behat features is located in `features`, while tests for major
(possibly optional) components should be located in a sub-folder. For
instance, the tests for the personalization modules are located in
`features/p2`.

Currently there's only one suite defined (`default`), but as more
sub-systems become covered by tests, suites will be created.

## Step definitions ##

The step definitions contain the actual test code, which performs the
action described in the Behat features. The step definitions should
use page objects (see next section), that perform the low level
steps. Page objects are not strictly necessary for Behat tests, but it
adds an extra level of abstraction and it makes it easier to make
structured tests, partly because test code can be shared among
different tests, and because it makes the tests easier to read.

When step definitions follow these rules, you can basically write
tests like "go to the front page", "login", "go to the page of lists",
"create a new list". The page objects abstract the actual steps
necessary to perform the tests, and the step definitions perform the
code that tests whether the application performs what it's supposed
to.

## Tags ##

Behat features/scenarios may be tagged, see [Usage](./usage.md) for a
list.

## Page objects ##

[Page objects][page objects] is a way to make interaction with pages
on a website object-oriented. You make a page object by defining what
paths it covers (e.g. /user/{uid}/list/{list_id}) and define the
functions on the page (e.g. create new list, go to specific list, read
number of notifications on a list).

Page objects make it easier to share code across scenarios, makes the
tests easier to read, and the tests will be structured more nicely.

As of this writing, only part of the tests has been refactored to use
page object. For an example, look at
`features/p2/material_lists.feature` and it's related step definitons.

[page objects]: http://martinfowler.com/bliki/PageObject.html
