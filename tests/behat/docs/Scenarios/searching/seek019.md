# Scenario: Seek019

Search and use facets to find a lesser result.

Searches broadly and reduce and increase the search result using facets.

## Method
This command uses **Given I accept cookies** which is done to click the cookie acceptance banner away. Otherwise it could potentially cover for some of the clicks necessary to unpack the facet lists.

Also it sets the number of records per page to 50, which seems to be the maximum it can be set to over several agencies. Notice, that some agencies may configure this differently.
The parameter given must match the value the user can see in the dropdown, so just change accordingly if the options change at some point.

**When I use facets to reduce the search results to the highest possible**

unpacks the facet structure (it's a list, where only a few are shown) by repeatedly clicking the links to show more. Then it scrapes off the promised reductions the various facets promise, and chooses the largest value a facet can reduce to, and clicks that facet. 
The result should be a list of that amount of results in. 

Notice, that if a search result shows say 25 records, and a facet, say 'H.C. Andersen' will give you 25 records, this will never reduce the result set. However, this is a special case that hasn't occurred during testing.

After the reduction, the number of shown records are tested against the promised amount. This number is based on the number of results shown on the top of the page of search results (it's not counted, because what is shown is not always the same, given some objects are shown as collections).

This scenario ends by actually deselecting the facet. Again, it will seek out the largest result promised by an enabled facet, and finally check that we're back at the first result we found.

 

## Notes

