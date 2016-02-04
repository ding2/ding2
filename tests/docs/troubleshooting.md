# Troubleshooting

## JavaScript not available in Goutte

The Goutte driver doesn't support JavaScript, so if you need to use
JavaScript you should either use Phantomjs or Selenium with Chrome or
Firefox. Use the tag `@javascript` in the Behat test to indicate, that
you need JavaScript for this test. If you use Selenium this doesn't
matter, but if you use Goutte and Phantomjs the test will
automatically use either Goutte (without JavaScript) or Phantomjs
(with JavaScript) depending on the tag.

Example of a Behat test with javascript:
```cucumber
@api @javascript
Scenario: Add material to list
  Given I have created a list "My list"
  When I add material "Harry Potter" to the list "My list"
  Then I should get a confirmation that I added the material to "My list" list
  And I should see the material "Harry Potter" on the list "My list"
```

The `@api` tag is needed, because the test generates a random username
when logging in, and for unfathomable reasons the Behat Drupal
extension insists on bootstraping Drupal to try and get the Drupal 8
Random generator, before falling back on it's build-in and this only
happens when using the `@api` tag. Hence this tag is needed for most
tests, as we are logging in for most of the tests, but we hope to fix
this soon.

## Selenium issues with Chrome or Firefox

Testing in a browser (e.g. Chrome or Firefox) via Selenium sometimes
cause problems, because the tests in the browsers are more strict. For
instance, a test fails if you try to click a checkbox on an area which
isn't visible in the browser. And some selectors are not accepted in
the browser, when it's accepted in Phantomjs.

This section describes some solutions, hacks, and problems.

### scrollTo

If an element isn't visible and it has to be visible to click on it,
then you can inject JavaScript on the page, which will scroll to the
element. It's not necessary for all types of elements, as e.g. links
are normally accessible even if it's on the bottom of the page and
you're on the top.

There's currently at least three different ways to do this. The
recommended way is using page objects and `ElementBase::scrollTo()`:

```php
$button = $this->findButton('edit-add-list');
$this->scrollTo($button);
$button->press();
```

The `scrollTo()` method takes a mink Element and is thus easy to use.

Alternatively, if the test has not been converted to page objects yet,
`Ding2Context::scrollTo()` is basically the same function.

Thirdly, the one can inject the needed JavaScript, this is not
recommended for new code:

```php
$this->ding2Context->minkContext->getSession()
    ->evaluateScript('jQuery(document).scrollTo(".ding-list-add-button a");');
```

### Timing issues

Sometimes there are problems finding an element, because the page has
been loaded, but the element hasn't yet. Depending on what you're
waiting for, there's a few options.

Waiting for the page being loaded can be done with
`PageBase::waitForPage()` (for page objects) or
`Ding2Context::waitForPage()` (for older tests).

Waiting for the standard Ding2 popup: `PageBase::waitForPopup()` (page
objects only).

And lastly, waiting for pretty much anything can be accomplished by
using the Mink `Element::waitFor()` method.

Example (pre-page objects):
```php
$page = $this->ding2Context->minkContext->getSession()->getPage();
$page->waitFor(10, function ($page) {
    return $page->find('css', '.ding-list-add-button a');
});
```

This will wait for the element `.ding-list-add-button a` to be present
before continuing the test - with a timeout of 10 seconds.
