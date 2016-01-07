Feature: Material lists
  As a library user
  In order to keep track of materials
  I want to organize materials in lists

  Background:
    Given I am logged in as a library user

  @wip @api
  Scenario: List listing page should be available from user page
    Given I am on my user page
    Then I should see a link to the lists page

  @wip
  Scenario: Create a new list link
    Given I am on the lists page
    Then I should see a link to the "create list" page

  @wip
  Scenario: Create a new list
    Given I am on the "create list" page
    When I create a new list "Title" with description "Description"
    Then I am returned to the lists page
    And I should see the list I created

  @wip
  Scenario: Add material to list
    Given I have a list "My list"
    And I am on the material "Harry Potter"
    When I add the material "Harry Potter" to "My list" list
    Then I should get a confirmation that I added the material to "My list" list
    And I should see the material "Harry Potter" on the "My list" listing page

  @wip
  Scenario: Remove material from list
    Given I have a material on a list named "My list"
    And I am on the "My list" listing page
    When I remove the material
    Then I should not see the material on the "My list" listing page

