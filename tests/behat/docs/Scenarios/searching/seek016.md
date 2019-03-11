# Scenario: Seek016

Check forsidebillede is shown on search result.

Performs search and checks that at least one record in the result has a cover image.

## Method
This is tested much as in Seek010 - see that for further detail.

Notice that cover pages are only present if configured, and configuration requires credentials.
Also, the search string used currently seems to be best for finding cover pages.
This may change over time.

__"term.type=Bog and term.date='2014' and holdingsitem.accessionDate>='NOW-300DAYS'"__ works well in December 2017.



## Notes

Because of the need for credentials to configure the cover page addi service, this scenario is not part of the CCI suite (it would require credentials to be in the github source code).

