# Scenario: Seek007

Check pagination.

Performs a search and checks that pagination works.
It looks both to use of ellipsis (...) and by changing pages via the url 
(parameter ?page=xx), as well as using the pagination links at the bottom of the page.


## Method
This test is the origin for two generally used methods.

**Given I want a search result between "81-110" using "term.type=bog" published between "2000-2017"**

performs searches until the search result has a size between
the first parameter - above 81-110 - by reiterating over the 
'using' parameter - above 'term.type=bog' - by changing the year
of publishing within the given interval (last parameter).

This method is highly advanced, as it attempts semi-binary search to quickly
arrive at the search result of the wanted size.
Notice, that the wanted size must be possible using the criteria
given. 
By using this method we can be certain we get a big enough search result to
walk through.

**When paging allows to get all the results**
is a very used method. It scrapes off all the results of the 
search, page by page, and places the result in an internal array.

**Then I check pagination on all pages** is a complex method, that 
goes through all the pages, and for each checks if the shown pagination
is correct. It checks if the number of ellipsises shown is reasonable
for the page, as well as if links to the beginning should be shown
along with the link to the previous page.
It also checks if there is a link to the next page on the last page.



## Notes
Depending on the library system (agency) and version of opensearch the
criteria may need to be adjusted. It is attempted to be as general 
as possible, but nothing can be guaranteed.
