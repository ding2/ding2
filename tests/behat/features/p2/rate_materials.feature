Feature: Rate materials
  In order to rate materials
  As a library user
  I want to be able to rate materials with stars

  Background:
    Given I am logged in as a library user
    And the list of rated materials exists

  @api @javascript
  Scenario: Rate material
    Given I have rated the material "The riddle of Nostradamus" with "2" stars
    When I go to the list of rated materials
    Then I should see that the material "The riddle of Nostradamus" is marked with "2" stars

  @api @javascript
  Scenario: See materials I have rated
    Given I have rated the material "Asimov on physics" with "3" stars
    When I go to the list of rated materials
    Then I should see that the material "Asimov on physics" is marked with "3" stars

  @api @javascript @disabled
  # Currently the rating widget doesn't work on list pages.
  Scenario: Change rating of material
    Given I have rated the material "Debrett's etiquette and modern manners" with "4" stars
    When I go to the list of rated materials
    And I change the rating of material "Debrett's etiquette and modern manners" to "1" stars
    Then I should see that the material "Debrett's etiquette and modern manners" is marked with "1" stars
