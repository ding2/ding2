Feature: Material lists
  In order to keep track of materials
  As a library user
  I want to organize materials in lists

  Background:
    Given I am logged in as a library user

  @api
  Scenario: "Create a new list" link should be available on user page
    Given I am on my user page
    Then I should see a link to the create list page

  @api
  Scenario: Create a new list
    Given I am on my create list page
    When I create a new list "My list of astronomy books" with description "I like astronomy"
    Then I should be on the "My list of astronomy books" list page

  @api @regression
  Scenario: List titles should not be tranlated
    Given I am on my create list page
    When I create a new list "Action" with description "Description"
    Then I should be on the "Action" list page
    And I should not see "Handling"

  @api @javascript
  Scenario: Add material to list
    Given I have created a list "My fantasy book list"
    When I add material "Harry Potter" to the list "My fantasy book list"
    Then I should get a confirmation that I added the material to "My fantasy book list" list
    And I should see the material "Harry Potter" on the list "My fantasy book list"

  @api @javascript
  Scenario: Remove material from list
    Given I have created a list "My list of magic books"
    And I have added the material "Harry Potter" to the list "My list of magic books"
    And I am on the "My list of magic books" list page
    When I remove the material "Harry Potter" from the list
    Then I should not see the material "Harry potter" on the list "My list of magic books"

  @api @javascript
  Scenario: Add material to new list
    Given I am on the material "The hitchhiker's guide to the galaxy"
    When I add it to a new list
    And fill in "The best books" as list title
    Then I should see the material "The hitchhiker's guide to the galaxy" on the list "The best books"

