Feature: Unfollow search
  As a library user
  I want to be able to unfollow a followed search

  Scenario: Unfollow search
    Given I am logged in as a library user
    When I have followed the search "harry potter"
    And I remove the search from followed searches
    Then I should not see "harry potter" on followed searches
