Feature: Unfollow author
  As a library user
  I want to unfollow a followed author

  Scenario: Unfollow author
    Given I am logged in as a library user
    When I have followed the author "george orwell"
    And I remove the author "george orwell" from followed authors
    Then I should not see "george orwell" on followed authors