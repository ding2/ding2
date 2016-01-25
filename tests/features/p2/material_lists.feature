Feature: Material lists
  As a library user
  In order to keep track of materials
  I want to organize materials in lists

  Background:
    Given I am logged in as a library user

  @api 
  Scenario: Create a new list link should be available on user page
    Given I am on my user page
    Then I should see a link to the create list page

  @api
  Scenario: Create a new list
    Given I am on my create list page
    When I create a new list "My special list" with description "Description"
    Then I should be on a list page
    And I should see "My special list"
  
  @api @regression
  Scenario: List titles should not be tranlated
    Given I am on my create list page
    When I create a new list "Action" with description "Description"
    Then I should be on a list page
    And I should see "Action"
    And I should not see "Handling"

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

