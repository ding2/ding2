Feature: Creation of basic campaigns
  In order to create basic campaigns in DDB CMS
  As an editor
  I want to create campaigns and verify that they are triggered correctly when users
  browse and search the site

  Background:
    Given I am logged in as a cms user with the administrators role

  @api @campaign_plus @regression @cci
  Scenario: Create a 'basic' campaign and show it on a page
    Given "Side" content:
      | title         | field_ding_page_body     |
      | Campaign Page | Some content for testing |
      | Other Page    | Some content for testing |
    When I go to the create campaign plus page
    And I fill a campaign with the following:
      | Title | Behatman & Robin         |
      | Type  | Text only              |
      | Text  | Bats 4ever             |
      | Link  | <front>                |
      | Style | Boks                   |
      | Tags  | campaign, super heroes |
    And I add a basic trigger with the following:
      | Rule type  | Side     |
      | Rule value | Campaign |
    And I save the campaign
    When I go to "admin/content"
    And I click "Campaign Page"
    Then the campaign "Behatman & Robin" should appear on the page within 2 seconds
    Then the campaign "Behatman & Robin" should appear on the page
    When I go to "admin/content"
    And I click "Page without campaign"
    Then the campaign "Behatman & Robin" should not appear on the page
    And I am on "published-page"
