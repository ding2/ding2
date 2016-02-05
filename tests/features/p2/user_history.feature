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
  Scenario: Check that my loan history exists
    Given I have checked the personalisation consent box
    When I am on my user page
    Then I should see the list of previous loans

  @api
  Scenario: Disallow my loan history to be saved
    Given I am on my user consent page
    When I uncheck the consent box
    Then I should see that the consent box is not checked

  @api
  Scenario: Check that my loan history doesn't exist
    Given I have unchecked the personalisation consent box
    When I am on my user page
    Then I should not see the list of previous loans
