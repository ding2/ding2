# Troubleshooting

## JavaScript not available in Goutte
The Goutte driver doesn't support JavaScript, so if you need to use JavaScript you should either use Phantomjs or
Selenium with Chrome or Firefox. Use the tag `@javascript` in the Behat test to indicate, that you need JavaScript for
this test. If you use Selenium this doesn't matter, but if you use Goutte and Phantomjs the test will automatically
use either Goutte (without JavaScript) or Phantomjs (with JavaScript) depending on the tag.

Example of a Behat test with javascript:
```
@api @javascript
Scenario: Add material to list
  Given I have created a list "My list"
  When I add material "Harry Potter" to the list "My list"
  Then I should get a confirmation that I added the material to "My list" list
  And I should see the material "Harry Potter" on the list "My list"
```

The `@api` tag is needed, because the test generates a random username when logging in, and for some reason it's
necessary to use this tag to be able to use that particular code. Hence this tag is needed for most tests, as we are
logging in for most of the tests.

## Selenium issues with Chrome or Firefox
Testing in a browser (e.g. Chrome or Firefox) via Selenium sometimes cause problems, because the tests in the browsers
are more strict. For instance, a test fails if you try to click a checkbox on an area which isn't visible in the
browser. And some selectors are not accepted in the browser, when it's accepted in Phantomjs.

This section describes some solutions, hacks, and problems.

### scrollTo
If an element isn't visible and it has to be visible to click on it, then you can inject JavaScript on the page, which
will scroll to the element. It's not necessary for all types of elements, as e.g. links are normally accessible even
if it's on the bottom of the page and you're on the top.

The following is an example of scrolling to the link element `.ding-list-add-button a`.

```
$this->ding2Context->minkContext->getSession()
    ->evaluateScript('jQuery(document).scrollTo(".ding-list-add-button a");');
```

### Timing issues
Sometimes there are problems finding an element, because the page has been loaded, but the element hasn't yet. Then you
can wait for the element with `waitFor()` function in Mink context.

Example:
```
$page = $this->ding2Context->minkContext->getSession()->getPage();
$page->waitFor(10, function ($page) {
    return $page->find('css', '.ding-list-add-button a');
});
```

This will wait for the element `.ding-list-add-button a` to be present before continuing the test - with a timeout of
10 seconds.
