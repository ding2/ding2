Feature: Follow author
  In order to be notified when there is new content from an author
  As a library user
  I want to be able to follow an author

  Background:
    Given I am logged in as a library user
    Then The list "follow author" exists

  @api
  Scenario: Follow author
    Given I have searched for "George Orwell 1984"
    When I add the author to authors I follow
    Then I should see "George Orwell" on the list of followed authors

  @api
  Scenario: Unfollow author
    Given I have followed the author "George Orwell"
    When I remove the author "George Orwell" from followed authors
    Then I should not see "George Orwell" on followed authors
