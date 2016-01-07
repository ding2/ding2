Feature: Follow search
  In order to be notified when there is new content for a search
  As a library user
  I want to be able to follow a search and unfollow a followed search

  Background:
    Given I am logged in as a library user
    Then The list "user searches" exists

  @api
  Scenario: Follow search "harry potter"
    Given I am logged in as a library user
    When I have searched for "harry potter"
    And I add the search to followed searches
    Then I should get a confirmation for followed searches
    And I should see "harry potter" on followed searches

  @api @wip
  Scenario: Unfollow search
    Given I am logged in as a library user
    When I have followed the search "harry potter"
    And I remove the search from followed searches
    Then I should not see "harry potter" on followed searches
