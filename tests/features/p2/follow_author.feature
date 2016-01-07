@wip
Feature: Follow author
  In order to be notified when there is new content from an author
  As a library user
  I want to be able to follow an author

  @api
  Scenario: Follow author
    Given I am logged in as a library user
    When I have searched for "george orwell"
    And I add the author to authors I follow
    Then I should see "george orwell" on the list of followed authors

  @api
  Scenario: Unfollow author
    Given I am logged in as a library user
    When I have followed the author "george orwell"
    And I remove the author "george orwell" from followed authors
    Then I should not see "george orwell" on followed authors
