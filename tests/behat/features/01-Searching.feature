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
    Then I can see "<regex>" somewhere in the search result

    Examples:
      | title                                                     | regex |
      | term.language=dansk AND term.type=bog  AND term.title=Æ*  | Æ+    |
      | term.language=dansk AND term.type=bog  AND term.title=Ø*  | Ø+    |
      | term.language=dansk AND term.type=bog  AND term.title=Å*  | Å+    |
      | term.language=dansk AND term.type=bog  AND term.title=?æ* | æ+    |
      | term.language=dansk AND term.type=bog  AND term.title=?ø* | ø+    |
      | term.language=dansk AND term.type=bog  AND term.title=?å* | å+    |
