Feature: Consent to save loan history
  I want to choose whether my loan history is saved or not
  As a library user
  I want to check or uncheck the personalification box

  Background:
    Given I am logged in as a library user

  @api
  Scenario: Check the personalification box
    Given I am on my user consent page
    When I check the consent box
    Then I should see that the consent box is checked

  @api
  Scenario: Uncheck the personalification box
    Given I am on my user consent page
    When I uncheck the consent box
    Then I should see that the consent box is not checked