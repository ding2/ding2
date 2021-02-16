Feature: SEEK redroute 01
  In order to check searches on the DDB CMS
  As a user
  I want to do searches and examine the search result for the following
  which refers to the lines in the redroute spreadsheet for testing searching (seek004 is line 4)
  - correct use of æ, ø and å (danish letters) (seek001)
  - check openscan suggestions (seek004)
  - check testing using enter and by clicking search button (seek005)
  - pagination on search result pages (seek007)

  Background:
    Given I am on "/"
    And I set verbose mode for "search-Results" to be "off"
    And I set verbose mode for "cookies" to be "off"
    And I set control mode for "searchMaxPages" to be "1"
    And I accept cookies


  @api @seek001 @seekNologin @regression
  Scenario Outline: S001 Search for special letters
    Given I have searched for "<title>"
    Then I can see "<letter>" somewhere in the search result

    Examples:
      | title                                                      | letter |
      | term.language=dansk AND term.type=bog  AND term.title=Æ*   | [Ææ]  |
      | term.language=dansk AND term.type=bog  AND term.title=Ø*   | [Øø]  |
      | term.language=dansk AND term.type=bog  AND term.title=?æ*  | æ      |
      | term.language=dansk AND term.type=bog  AND term.title=?ø*  | ø      |
      | term.language=dansk AND term.type=bog  AND term.title=?å*  | å      |

  @api @seek001 @seekNologin @regression @no_ci
  Scenario Outline: S001 Search for special letters
    Given I have searched for "<title>"
    Then I can see "<letter>" somewhere in the search result

    Examples:
      | title                                                      | letter |
      | term.language=dansk AND term.type=bog  AND term.title=Å* | Å      |

  @api @seek004 @seekNologin @regression @no_ci
  Scenario: S004 Show openscan suggestions in search field
    Given I am on "/"
    When I enter "her" in field "Search"
    Then I get suggestions from openscan

  @api @seek005 @seekNologin @regression
  Scenario: S005 Search using click search button
    Given I am on "/"
    When I enter "hansen" in field "Search"
    When I press "Søg"
    Then paging allows to get all the results

  @api @seek007 @seekNologin @regression
  Scenario: S007 Check pagination
    Given I set control mode for "searchMaxPages" to be "100"
    Given I want a search result between "81-110" using "term.type=bog and term.creator=Hansen and term.publisher=Gyldendal" published between "2000-2017"
    When paging allows to get all the results
    Then I check pagination on all pages

  @api @seek010  @seekNologin @regression
  Scenario: S010 Check serie-angivelse is shown on search result
    Given I have searched for "phrase.titleSeries=B*"
    When paging allows to get all the results
    Then there are posts with "series" in the search results

  @api @seek011 @seekNologin @regression
  Scenario: S011 Check materialetype is shown on search result
    Given I have searched for "phrase.titleSeries=A*"
    When paging allows to get all the results
    Then all posts have "objecttype" in the search results

  @api @seek012 @seekNologin @regression @no_ci
  Scenario: S012 Check internal searchfield
    Given I am on "/"
    And I have searched for "$random:news"
    When I search internally on the home page
    Then I can see "$get:lastSearchString" in the search results first page

  @api @seek013 @seekNologin @regression @no_ci
  Scenario: S013 Check sorting for title ascending
    Given I have searched for "phrase.titleSeries=B* and term.language=dansk"
    When I sort the search result on "title_ascending"
    Then paging allows to get all the results

  @api @seek013 @seekNologin @regression @no_ci
  Scenario: S013 Check sorting for title descending
    Given I have searched for "phrase.titleSeries=B* and term.language=dansk"
    When I sort the search result on "title_descending"
    Then paging allows to get all the results

  @api @seek013 @seekNologin @regression @no_ci
  Scenario: S013 Check sorting for published date descending
    Given I have searched for "phrase.titleSeries=B*"
    And I set control mode for "searchMaxPages" to be "2"
    When I sort the search result on "date_descending"
    Then the search result is sorted on "date_descending"

  @api @seek013 @seekNologin @regression @no_ci
  Scenario: S013 Check sorting for published date ascending
    Given I have searched for "phrase.titleSeries=B*"
    When I sort the search result on "date_ascending"
    Then the search result is sorted on "date_ascending"

  @api @seek014 @seekNologin @regression
  Scenario: S014 Check tilgængelighed is shown on search result
    Given I have searched for "phrase.titleSeries=All*"
    When paging allows to get all the results
    Then all posts have "availability" in the search results

  @api @seek015 @seekNologin @regression
  Scenario: S015 Check samlinger is shown on search result
    Given I have searched for "phrase.titleSeries=Harry*"
    When paging allows to get all the results
    Then there are posts with "collection" in the search results

  @api @seek016 @seekNologin @regression
  Scenario: S016 Check forsidebillede is shown on search result
    Given I have searched for "term.type=Bog and term.date='2014'"
    When paging allows to get all the results
    Then there are posts with "cover" in the search results
