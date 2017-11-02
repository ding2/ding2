Feature: SEEK redroute 01
  In order to check searches on the DDB CMS
  As a user
  I want to do searches and examine the search result for
  - correct use of æ, ø and å (danish letters)

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
    When I enter "her" in field "input#edit-search-block-form--2"
    Then I get suggestions from openscan

  @api @seek005 @seekNologin @regression
  Scenario: Search using typing of enter
    Given I am on "/"
    When I enter "harry\n" in field "input#edit-search-block-form--2"
    Then pageing allows to get all the results

  @api @seek005 @seekNologin @regression
  Scenario: Search using click search button
    Given I am on "/"
    When I enter "harry" in field "input#edit-search-block-form--2"
    When I press "Søg"
    Then pageing allows to get all the results

