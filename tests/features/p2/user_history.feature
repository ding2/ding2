Feature: Consent to save loan history
  In order to see my loan history
  As a library user
  I want to be able to allow that my loan history is saved

  Background:
    Given I am logged in as a library user

  @api
  Scenario: Allow my loan history to be saved
    Given I am on my user consent page
    When I check the consent box
    Then I should see that the consent box is checked

  @api
  Scenario: Disallow my loan history to be saved
    Given I am on my user consent page
    When I uncheck the consent box
    Then I should see that the consent box is not checked