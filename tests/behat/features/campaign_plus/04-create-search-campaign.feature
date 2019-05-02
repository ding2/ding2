Feature: Creation of search campaigns
  In order to create search campaigns in DDB CMS
  As an administrator
  I want to create campaigns and verify that they are triggered correctly when users
  search the site

  Background:
    Given I am logged in as a cms user with the administrators role

  @api @campaign_plus @regression @cci
  Scenario: Create a search campaign and verify it is only shown on results for the correct search term
    Given I go to the create campaign plus page
    And I fill a campaign with the following:
      | Title | Behatman & Robin       |
      | Type  | Text only              |
      | Text  | Bats 4ever             |
      | Link  | <front>                |
      | Style | Bånd                   |
      | Tags  | campaign, super heroes |
    And I set the search trigger with the search query "Batman"
    And I save the campaign
    And I have searched for "Batman"
    Then the campaign "Behatman & Robin" should appear on the page
    And I have searched for "Robin"
    Then the campaign "Behatman & Robin" should not appear on the page
