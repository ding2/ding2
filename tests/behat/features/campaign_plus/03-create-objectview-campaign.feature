Feature: Creation of object view campaigns
  In order to create object view campaigns in DDB CMS
  As an editor
  I want to create campaigns and verify that they are triggered correctly when users
  browse and search the site

  Background:
    Given I am logged in as a cms user with the administrators role

  @api @campaign_plus @regression @cci
  Scenario: Create a 'object view' campaign and show it on a page
    Given I go to the create campaign plus page
    And I fill a campaign with the following:
      | Title | Behatman & Robin       |
      | Type  | Text only              |
      | Text  | Bats 4ever             |
      | Link  | <front>                |
      | Style | Bånd                   |
      | Tags  | campaign, super heroes |
    And I set the object view trigger with the search query Batman
    And I save the campaign
    And I have searched for "Batman"
    And I click "Batman"
    Then "Behatman & Robin" should appear within 2 seconds
    And I have searched for "Robin"
    And I click "Robin"
    Then "Behatman & Robin" should not appear within 2 seconds
