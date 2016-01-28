Feature: Follow search
  In order to be notified when there is new content for a search
  As a library user
  I want to be able to follow a search and unfollow a followed search

  Background:
    Given I am logged in as a library user
    Then the list for followed searches exists

  @api @javascript
  Scenario: Follow search "harry potter"
    Given I have searched for "harry potter"
    When I add the search to followed searches
    Then I should see "harry potter" on followed searches

  @api @javascript
  Scenario: Unfollow search
    Given I have followed the search "harry potter"
    When I remove the search "harry potter" from followed searches
    Then I should not see "harry potter" on followed searches
