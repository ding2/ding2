Feature: Creation of facet campaigns
  In order to create facet campaigns in DDB CMS
  As an administrator
  I want to create campaigns and verify that they are triggered correctly when users
  search the site

  Background:
    Given I am logged in as a cms user with the administrators role
    When I go to the create campaign plus page
    And I fill a campaign with the following:
      | Title | Behatman & Robin       |
      | Type  | Text only              |
      | Text  | Bats 4ever             |
      | Link  | <front>                |
      | Style | Boks                   |

  @api @campaign_plus @regression @cci
  Scenario: Subject search - Create a 'facet' campaign that only shows on search for "subject=børn"
    When I add a facet trigger with the following:
      | Facet type   | Emne |
      | Facet value  | Børn |
      | Common value | 7    |
    And I save the campaign
    And I have searched for "term.subject=børn"
    Then the campaign "Behatman & Robin" should appear on the page
    Given I have searched for "term.subject=biler"
    Then the campaign "Behatman & Robin" should not appear on the page

  @api @campaign_plus @regression @cci
  Scenario: Material type search - Create a 'facet' campaign that only shows on search for "type=bog"
    When I add a facet trigger with the following:
      | Facet type   | Materialetype |
      | Facet value  | bog           |
      | Common value | 1             |
    And I save the campaign
    And I have searched for "facet.type=bog"
    Then the campaign "Behatman & Robin" should appear on the page
    And I have searched for "facet.type=film"
    Then the campaign "Behatman & Robin" should not appear on the page

  @api @campaign_plus @regression @cci
  Scenario: Publisher search - Create a 'facet' campaign that only shows on search for "publisher=gyldendal"
    When I add a facet trigger with the following:
      | Facet type   | Forlag    |
      | Facet value  | gyldendal |
      | Common value | 1         |
    And I save the campaign
    And I have searched for "facet.publisher=gyldendal"
    Then the campaign "Behatman & Robin" should appear on the page
    And I have searched for "facet.publisher=systime"
    Then the campaign "Behatman & Robin" should not appear on the page
