# Scenario: Seek020

Search and use facets repeatedly three times.

Extension of Seek019 - performs repeatedly decreasing of search result using facets and
returns to the original result again by deselecting the facets in turn.

## Method
See Seek019 for explanation of how this is done.

The differences are:

1. This will reduce the search result 3 times instead of just one.
2. The result reduction will be checked each time, but for deselecting and increasing the search result again only the final result will be checked for size. This is because we cannot control the way it will choose the facets to deselect, and so cannot predict completely how the result will grow.


## Notes

