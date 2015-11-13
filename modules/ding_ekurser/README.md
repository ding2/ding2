# Ding eKurser - ding_ekurser

This module implements the page /ekurser, from where a user can browse all e-courses in the well, optionally limited to popular subjects.

## Technical considerations

We want to reuse the functionality from the ding search result page, but with a few adjustments, so it makes sense in regards to only listing e-courses.

The e-courses are queried from the well with the string "ekurser.nu", as we currently can't uniquely identify them all by source or publisher.

We want to offer the user a way to limit the results via the facet "subject", but we're not interested in other facets, and since there's only one facet, we want to display it as a submenu, instead of the usual folding facetbrowser. So we remove all facets from the facetbrowser and build our own list of terms.

The subject terms are currently defined by dbc, and may include terms that cover e-courses in general, like "Vejledninger". To get rid of these from our submenu, we remove terms that cover more than 80% of the total result set.

Some of the fields in the search results posts seem redundant when only listing e-courses, like availability and year (year is misleading, as many e-courses are updated regularly, which the wells posts currently don't reflect). So we hide these fields via css.

We add our own sort options to the search result, as ordering by something like author doesn't make sense, while ordering by acquisition date does.

## Facet Browser
We chose not to make our own facet browser, so we can reuse the existing one and modify this instead.

That means we remove the existing facets, because we don't want to use all of them, e.g. it's not relevant to use date as a facet, because all e-courses are current - old courses are removed from ekurser.nu. Facets are removed explicitly, but maybe this has to be changed. If a site has added more facets, these will be shown and not removed automatically. It's currently undefined how to deal with this situation, so the default is to not remove them which is probably reasonably sane.

Most of the code in the form alter hook for the facet browser (ding_facetbrowser_form) is to change the handling of facets. The intention of the existing facet browser is to make several AND filters. This is not what ekurser.nu handling is supposed to do. They want OR filters, i.e. when you have chosen one facet the facet browser should still show the "top" facets instead of filtering down. This might not be the cleanest way to do it, but instead of making a completely new facet browser we can reuse the existing and modify it.

## Subject facets cache
### Short description
This module modifies the behavior of how facets are filtered in the facet browser. When the user chooses a facet, we don't want to change the set of facets (including the count of each facet) which is the normal behavior of the facet browser.

To do this we use a cache for the facets which will be used instead of the filtered down facet list. This way the facet browser will contain the same facets, when we have chosen a specific facet from the list. The default behavior is to change the facets so you can choose sub-facets, sub-sub-facets, etc., but the facets for e-courses should always be the same.

### Longer description
The reason for the implementation of a cache of the subject facets is that we modify the facet browser and modify the behavior of filtering of facets. If you go to the search (when you haven't chosen any facet), a search will be performed which will - among search results - return facets. These facets are cached. When you choose a facet, instead of filtering the facets too, we show the cached facets so we are able to choose from the main set again.

The facets are cached permanently, and this will only be a problem if you go directly to a search for a specific facet and the top facets have changed. Every time you go to the main ekurser page, it will make a search as it normally would, so the cached facets will not be older than the last time ekurser was visited. If you go to a search with a specific facet and the cache is empty, it will redirect to the main ekurser page to make a new search to get the facets.

In practice this should only be a problem if either ekurser is almost never visited, or the facets change more frequently than ekurser is visited, and users tend to go directly to a facet term instead of the main ekurser search page.
