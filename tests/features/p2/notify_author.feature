Feature: Notify author

  Background:
    Given I am logged in as a library user
    And the list "Forfattere jeg følger" exists

  @api @javascript
  Scenario: There are new materials for author
    Given I have followed the author "Rune T. Kidde"
    When there are "2" new materials for the author "Rune T. Kidde"
    Then I should see that there are "2" new materials on the notifications list on the notifications top menu
    And I should see that there are "2" new materials on the list of authors I follow