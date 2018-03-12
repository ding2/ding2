# Scenario: Seek013

Test of sorting of search results.
This one is divided into 5 scenarios, covering sorting on title, creator and date of publishing.


## Method
After searching for a reasonable search criteria the sort option is selected, and the search result is checked to see if the sorting is done correctly.

**When I sort the search result on "xx"**

only selects the sort option from the drop down. It does do a check on whether xx is a valid option. The valid values are unfortunately hard coded.

**Then the search result is sorted on "xx"**

Again xx is validated, and if okay, the search result is checked from the top down on the page.
The check respects the searchMaxPage-setting, if any, and thus only looks through that many pages.

**NB:** Creators and titles are difficult to check, because they are sorted according to a sort-order value, which is only available in the opensearch results. This sorting respects "Aa" as "Å" for instance, and that makes checking this incredible difficult, because it is also not simple to look up the actual book (because searching does show collections as well) in the opensearch interface. For this reason the scenario that tests sorting for creator never fails, but uses the verbose mode and **Then paging allows to get all the results** to display the results for the user instead. 
 


## Notes
Sorting on title descending is not part of CCI because there seems to be a bug in the opensearch sorting.
Also sorting on date ascending is not part of CCI because it doesn't handle (1???) entries well. This should actually be fixed (and that value ignored).

