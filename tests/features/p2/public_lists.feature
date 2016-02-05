Feature: Public lists
  In order to share lists with other library users
  As a library user
  I want to be able to make my lists public
  
  - Users should be able to share lists
  - Users should be able to follow shared lists
  - Users should be able to add material to shared lists, if they have proper permissions

  Background:
    Given I am logged in as a library user

  @api @javascript
  Scenario: Make list public
    Given I have created a list "My Harry Potter books"
    When I make the list "My Harry Potter books" public
    Then I should see that the list "My Harry Potter books" is marked as public

  @api @javascript
  Scenario: See public list on public-lists
    Given I have created a list "My Sci Fi novels"
    And I have made the list "My Sci Fi novels" public
    When I go to the public lists page
    Then I should see the public list "My Sci Fi novels"

  @api @javascript
  Scenario: Follow public list
    Given I have a link to a public list with the title "My George Orwell books"
    When I follow the list "My George Orwell books"
    Then I should see the list "My George Orwell books" on lists I follow

  @api @javascript
  Scenario: Unfollow a public list
    Given I am following a public list with the title "Books about flowers"
    When I unfollow the list with the title "Books about flowers"
    Then I should not see the list "Books about flowers" on lists I follow

  @api @javascript
  Scenario: Add content to a public list
    Given I have created a public list "My action movies"
    When I add material "Die hard 4.0" to the list "My action movies"
    Then I should see the material "Die hard 4.0" on the public list "My action movies"

  @api @javascript
  Scenario: Other users can't add content to a public list
    Given I have created a public list "My fruit books"
    When I log in as a different user
    Then I should not be able to add material "Essential guide to back garden self-sufficiency" to the list "My fruit books"

  @api @javascript @regression
  Scenario: Make list shared for other users to read
    Given I have created a list "My family's vacation books"
    When I make the list "My family's vacation books" read shared
    And I log in as a different user
    Then I should be able to see the list "My family's vacation books" with the "read" link
    And I should not be able to add material "The raven" to the list "My family's vacation books"

  @api @javascript @regression
  Scenario: Make list shared for other users to add material
    Given I have created a list "My special books for my friends"
    When I make the list "My special books for my friends" write shared
    And I log in as a different user
    Then I should be able to see the list "My special books for my friends" with the "write" link
    And I should be able to add material "The price" to the list "My special books for my friends" as a different user
