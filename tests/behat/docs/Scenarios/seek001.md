# Scenario: seek001

Search for special letters.

Tests if danish characters æ, ø and å can be used in search.
Searches using these, and checks the result contains them as well.

## Method
The scenario is an outline, that loops through searching for each of the
characters in both lower- and uppercase.

It uses Given I have searched for <x> step, to search for a string
composed by terms. It narrows in on danish books, and assumes uppercase
will start a word in the title, and lowercase will be second letter in 
a word in the title.

The check happens in Then I can see <x> somewhere in the search result.
This step will look for titles on each page of the search result
and basically do a reg-ex search for x.

## Notes
It seems to be extra difficult to find Å, because opensearch equals this 
to Aa (old danish spelling). The search goes for Åer because that word
is apparently less likely to be spelled differently. However,
that depends on the opensearch version and agency. 

The scenario is usually good enough to run with limitation on search result 
pages (I set control mode for 'searchMaxPages' to be '1'). 
If it fails, try to increase or completely remove that limitation.
Its main purpose of being set to 1 is to make the test run faster.