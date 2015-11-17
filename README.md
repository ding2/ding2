ting_search_context
======================

Description
-----------
This is module which puts content from the rest of the site on search result
pages. The module evaluates the search query and results to provide the best match to a defined search context.
A search context can be one of 3 variants. A search string context which matches the actual (or part of) search query. A system
context which is a broad predefined search context which comes default with the module. E.g. adult fiction books. And subject contexts
which are a extention and narrowing of one of the predefined system contexts. Subject context can be added at will by defining one
or more subject terms when creating a context.

Content one the site is matches with a context here: /admin/content/ting-search-context. You can match following kind of content to
a search context: Ding page, Ding event, Ding news and Search context link. Search context link is a special node type which comes with
the module and gives you the possibility of creating a link to any kind of content, search queries and external resources. When context is
matched it receives a rating from 1 - 10. Rating of 10 means this is a required content while rating of 1 - 9 is a measure of probability of the
content being shown on a relevant search result page. A rating of 4 has twice the chance of being shown then a rating of 2.

Installation
-----------


Configuration
-------------


