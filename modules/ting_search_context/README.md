ting_search_context
======================

Description
-----------
This module puts content from the rest of the site on search result pages. The module evaluates the search query and search results to provide the best 
match to a defined search context.

A search context can be one of 3 variants. A search string context which matches the actual search query or part of it. A system
context which is a broad predefined search context that comes default with the module. E.g. adult fiction books. And a subject context
which is an extention and narrowing of one of the predefined system contexts. Subject contexts can be added by defining one
or more subject terms when creating a context.

Content on the site is matched with the contexts here: /admin/content/ting-search-context. You can match the following kind of content to
a search context: Ding page, Ding event, Ding news and Search context link. Search context link is a special node type which comes with
the module and gives you the possibility of creating a link to any kind of content, search queries and external resources. When content is
matched with a context it receives a rating from 1 - 10. Rating of 10 means this is a required content while rating of 1 - 9 is a measure of probability of the
content being shown on a relevant search result page. A rating of 4 has twice the chance of being shown then a rating of 2.

When the user performs a search the relevant search context is calculated. There is always a relevant system context. If the calculation of
context is inconclusive the search context defaults to at neutral context. The content shown is retrieved by ajax and shows up to 15 content items
on a carousel. The content can be shown in one of three location depending on configuration.

Installation
-----------
Enable the features Ting Search Context and Ting Search Context Feature. Go to facet configuration page /admin/config/ting/facets. Add the following facets:
facet.genreCategory, facet.fictionSubject, facet.nonFictionSubject. This is necessary in order to calculate the relevant search context.


Configuration
-------------
On /admin/config/ting/ting-search-context the placement of the content item shown can be configured. There are three possible placements:
Above search results, below search result and in left column shown vertically. On small screens the above search result view is moved under the
search results.

/admin/config/ting/ting-search-context lists all defined search contexts on the site and gives possibility of creating, editing and deleting search contexts.



Notes
--------------
The Ting Search Context module has been developed and tested with a well profile mostly consisting of physical items from the local library.
Including extra sources in the well profile like big article databases or digital music could eschew the calculation significantly.

The reason there is two features is because the code in ting_search_context_feature module should be and may eventually be part of ting_search module.


