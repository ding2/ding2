Feature: SEEK redroute 01
  In order to check searches on the DDB CMS
  As a user
  I want to do searches and examine the search result for the followingw
  which refers to the lines in the redroute spreadsheet for testing searching (seek001 is line 1)
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
  Scenario Outline: Search for special letters
    Given I have searched for "<title>"
    Then I can see "<letter>" somewhere in the search result

    Examples:
      | title                                                      | letter |
      | term.language=dansk AND term.type=bog  AND term.title=Æ*   | Æ      |
      | term.language=dansk AND term.type=bog  AND term.title=Ø*   | Ø      |
      | term.language=dansk AND term.type=bog  AND term.title=Åer* | Å      |
      | term.language=dansk AND term.type=bog  AND term.title=?æ*  | æ      |
      | term.language=dansk AND term.type=bog  AND term.title=?ø*  | ø      |
      | term.language=dansk AND term.type=bog  AND term.title=?å*  | å      |

  @api @seek004 @seekNologin @regression
  Scenario: Show openscan suggestions in search field
    Given I am on "/"
    When I enter "her" in field "Søg"
    Then I get suggestions from openscan

  @api @seek005 @seekNologin @regression
  Scenario: Search using typing of enter
    Given I am on "/"
    When I enter "larsen\n" in field "Søg"
    Then pageing allows to get all the results

  @api @seek005 @seekNologin @regression
  Scenario: Search using click search button
    Given I am on "/"
    When I enter "hansen" in field "Søg"
    When I press "Søg"
    Then pageing allows to get all the results

  @api @seek007 @seekNologin @regression
  Scenario: Check pagination
    Given I set control mode for "searchMaxPages" to be "100"
    Given I want a search result between "81-110" using "term.type=bog and term.creator=Hansen and term.publisher=Gyldendal" published between "2000-2017"
    When pageing allows to get all the results
    Then I check pagination on all pages

  @api @seek010  @seekNologin @regression
  Scenario: Check serie-angivelse is shown on search result
    Given I have searched for "phrase.titleSeries=B*"
    When pageing allows to get all the results
    Then there are posts with "serie" in the search results

  @api @seek011 @seekNologin @regression
  Scenario: Check materialetype is shown on search result
    Given I have searched for "phrase.titleSeries=A*"
    When pageing allows to get all the results
    Then all posts have "materialetype" in the search results

  @api @seek012 @seekNologin @regression
  Scenario: Check internal searchfield
    Given I am on "/"
    And I have searched for "$random:nyhed"
    When I search on hjemmesiden
    Then I can see "$get:lastSearchString" in the search results first page

  @api @seek013 @seekNologin @regression
  Scenario: Check sorting for title
    Given I have searched for "phrase.titleSeries=B* and term.language=dansk"
    When I sort the search result on "title_ascending"
    Then the search result is sorted on "title_ascending"
    When I sort the search result on "title_descending"
    Then the search result is sorted on "title_descending"

  @api @seek013 @seekNologin @regression
  Scenario: Check sorting for creator by listing the results in the log
    Given I have searched for "term.language=dansk and phrase.titleSeries=B*"
    And I set verbose mode for "search-Results" to be "on"
    When I sort the search result on "creator_descending"
    Then pageing allows to get all the results
    When I sort the search result on "creator_ascending"
    Then pageing allows to get all the results

  @api @seek013 @seekNologin @regression
  Scenario: Check sorting for published date
    Given I have searched for "phrase.titleSeries=B*"
    When I sort the search result on "date_descending"
    Then the search result is sorted on "date_descending"
    When I sort the search result on "date_ascending"
    Then the search result is sorted on "date_ascending"

  @api @seek014 @seekNologin @regression
  Scenario: Check tilgængelighed is shown on search result
    Given I have searched for "phrase.titleSeries=All*"
    When pageing allows to get all the results
    Then all posts have "tilgængelighed" in the search results

  @api @seek015 @seekNologin @regression
  Scenario: Check samlinger is shown on search result
    Given I have searched for "phrase.titleSeries=Harry*"
    When pageing allows to get all the results
    Then there are posts with "materialesamling" in the search results

  @api @seek016 @seekNologin @regression
  Scenario: Check forsidebillede is shown on search result
    Given I have searched for "term.type=bog and holdingsitem.accessionDate>='NOW-300DAYS'"
    When pageing allows to get all the results
    Then there are posts with "forside" in the search results
