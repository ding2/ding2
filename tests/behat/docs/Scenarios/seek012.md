# Scenario: Seek012

Check internal searchfield.

Performs search, switches to internal search and checks that a result is found.

## Method
This scenario utilizes the variable-substitution functionality in

**Given I have search for "$random.news"**

The $ is the variable-indicator, which means the method will attempt to translate the value.
The actual variable consists of a modifier and a variable name.
The modifier is in the example above __random__ and the variable is __news__.
The modifier could be random, first, last, but would be defined for each variable because each variable that will ever be defined would have its own context.

The effect of finding a first, last or random 'news' is that it will search for news displayed on the page. An unfortunate side effect of this is, that it presumes the browser currently is on the front page, and that news are present in the system. The error message issued if no news are found will indicate this.

Another variable currently defined is __lastsearchstring__. The modifier for this is any string, so in this scenario we use "$get.lastsearchstring" as it seems most natural.

The method "When I search internally on the homepage" does what it says - search on the library site itself.
 
## Notes
This is currently not part of CCI tests because for some reason default news are not loaded into the site when built. It gives an error. The test does not require specific news to be loaded - it will look at news on the the front page, and pick one of those.

