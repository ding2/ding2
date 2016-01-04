Feature: Smoke test
  Simple test to check if test site is running.

  Scenario: See front page
    Given I am on "/"
    Then I should see "Gadenavn 1"
    
