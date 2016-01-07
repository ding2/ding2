Feature: Follow search
  In order to be notified when there is new content for a search
  As a library user
  I want to be able to follow a search

  Scenario: Follow search "harry potter"
    Given I am logged in as a library user
    When I have searched for "harry potter"
    And I add the search to followed searches
    Then I should get a confirmation for followed searches
    And I should see "harry potter" on followed searches