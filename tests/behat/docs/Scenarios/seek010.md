# Scenario: Seek010

Check serie-angivelse is shown on search result.

Performs a search and runs through the result trying to 
find a result that is a 'series'.
If only one series is found in the search result, it passes.

## Method
It searches for "phrase.titleSeries=B*", which is cryptic,
but this should ensure we find series. As B is quite common as a starting 
letter for some word in the title, this should actually work on most agencies.

After that it uses **Then paging allows to get all the results** (see Seek007),
to scrape off the result and finally it goes through
**Then there are posts with "serie" in the search results**.

This procedure runs through the scraped off results array, and
searches for various things. In this case 'series', but that is actually 
a parameter. The same method is used in the subsequent scenarios.
It is happy to find only one series, and a series is marked by
showing "Serie: <name of serie>" on the post in the result.
A CSS search string is used to identify this.

## Notes
