Feature: Rate materials
  In order to rate materials
  As a library user
  I want to be able to rate materials with stars

  Background:
    Given I am logged in as a library user
    And The list "ratings" exists

  @api @javascript
  Scenario: Rate material
    Given I have searched for "Nostradamus och hans märkliga förutsägelser om vår tid : en studie över den ryktbare franske läkaren och hans profetior" with the material name "870970-basis%3A01334042"
    When I rate the material "870970-basis%3A01334042" with "2" stars
    And I go to the list of rated materials
    Then I should see that the material "870970-basis%3A01334042" is marked with "2" stars

  @api @javascript
  Scenario: See materials I have rated
    Given I have rated the material "870970-basis%3A01860410" with "3" stars
    When I go to the list of rated materials
    Then I should see that the material "870970-basis%3A01860410" is marked with "3" stars

  @api @javascript
  Scenario: Change rating of material
    Given I have rated the material "870970-basis%3A25893271" with "4" stars
    When I go to the list of rated materials
    And I change the rating of material "870970-basis%3A25893271" to "1" stars
    Then I should see that the material "870970-basis%3A25893271" is marked with "1" stars