Feature: Follow author
  In order to be notified when there is new content from an author
  As a library user
  I want to be able to follow an author

  Background:
    Given I am logged in as a library user
    And the list of followed authors exists

  @api @javascript
  Scenario: Follow author
    Given I am on a material of "George Orwell"
    When I add the author "George Orwell" to authors I follow
    Then I should see "George Orwell" on the list of followed authors

  @api @javascript
  Scenario: Unfollow author
    Given I have followed the author "George Orwell"
    When I remove the author "George Orwell" from followed authors
    Then I should not see "George Orwell" on followed authors

  @api @javascript
  Scenario: There are new materials for author
    Given I have followed the author "Rune T. Kidde"
    When there are "2" new materials for the author "Rune T. Kidde"
    Then I should see that there are "2" new materials on the notifications list on the notifications top menu
    And I should see that there are "2" new materials on the list of authors I follow
