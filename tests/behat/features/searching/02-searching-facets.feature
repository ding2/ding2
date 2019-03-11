Feature: Searching with facets
  In order to check searches and showing of materials on the DDB CMS
  As a user
  I want to do searches and examine the search result for
  - if the number of shown results are actually shown
  - if we can use facets to end up with just one book.
  Numbering refers to the lines in the redroute spreadsheet for testing searching (seek004 is line 4)


  @api @seek019 @seekNologin @regression @cci
  Scenario: S019 Search and use facets to find a lesser result
    Given I have searched for "term.type=bog and term.publisher=Gyldendal"
    And I accept cookies
    When I use facets to reduce the search results to the highest possible
    Then I check if the right number of search results are shown
    When I deselect a facet to increase the search results
    Then I check if the right number of search results are shown



    # notice that we will not check facet results while deselecting because we cannot control
    # the sequence it will deselect in.
  @api @seek020 @seekNologin @regression @cci
  Scenario: S020 Search and use facets repeatedly three times
    Given I have searched for "term.type=bog and term.publisher=Gyldendal"
    And I accept cookies
    When I use facets to reduce the search results to the highest possible
    Then I check if the right number of search results are shown
    When I use facets to reduce the search results to the highest possible
    Then I check if the right number of search results are shown
    When I use facets to reduce the search results to the highest possible
    Then I check if the right number of search results are shown
    When I deselect a facet to increase the search results
    When I deselect a facet to increase the search results
    When I deselect a facet to increase the search results
    Then I check if the right number of search results are shown
