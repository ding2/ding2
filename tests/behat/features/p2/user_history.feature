Feature: Consent to save loan history
  In order to see my loan history
  As a library user
  I want to be able to allow that my loan history is saved

  Background:
    Given I am logged in as a library user

  @api @disabled
  # Setting consent causes fatal error on subsequent requests.
  Scenario: Check that my loan history exists
    Given I have given consent to save my loan history
    When I am on my user page
    Then I should see the list of previous loans

  @api @disabled
  # Setting consent causes fatal error on subsequent requests.
  Scenario: Check that my loan history list is deleted when consent is withdrawn
    Given I have withdrawn consent to save loan history
    When I am on my user page
    Then I should not see the list of previous loans
