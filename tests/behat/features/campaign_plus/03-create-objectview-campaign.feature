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
    # View "Batman - Af Tim Burton (2013)"
    And I am on "ting/object/870970-basis%3A50711161"
    Then the campaign "Behatman & Robin" should appear on the page
    # View "Superman IV - Af Sidney J. Furie (2014)"
    And I am on "ting/object/870970-basis%3A51191331"
    Then the campaign "Behatman & Robin" should not appear on the page
