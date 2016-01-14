Feature: Public lists
  As a library user
  I want to be able to make lists public or shared lists with a token
  I want to (un)follow public lists and shared lists
  I want to add material to public lists I created and to shared lists I have edit access to

  Background:
    Given I am logged in as a library user

  @api @no_messages_check @javascript
  Scenario: Make list public
    Given I have created a list "My Harry Potter books"
    When I make the list "My Harry Potter books" public
    Then I should see that the list "My Harry Potter books" is public

  @api @no_messages_check @javascript
  Scenario: See public list on public-lists
    Given I have created a list "My Sci Fi novels"
    And I have made the list "My Sci Fi novels" public
    When I go to the public lists page
    Then I should see the public list "My Sci Fi novels"

  @api @no_messages_check @javascript
  Scenario: Follow public list
    Given I have a link to a public list with the title "My George Orwell books"
    When I follow the list "My George Orwell books"
    Then I should see the list "My George Orwell books" on lists I follow

  @api @no_messages_check @javascript
  Scenario: Unfollow a public list
    Given I am following a public list with the title "Books about flowers"
    When I unfollow the list with the title "Books about flowers"
    Then I should not see the list "Books about flowers" on lists I follow

  @api @no_messages_check @javascript
  Scenario: Add content to a public list
    Given I have created a public list "My action movies"
    When I add material "Die hard 4.0" to the list "My action movies"
    Then I should see the material "Die hard 4.0" on the public list "My action movies"
