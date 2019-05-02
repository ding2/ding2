Feature: Automatic creation of campaigns
  In order to create automatic campaigns in DDB CMS
  As an administrator
  I want to create news and verify that they trigger automatic creation of facet campaigns

  Background:
    Given I am logged in as a cms user with the administrators role

  @api @campaign_plus @regression @cci
  Scenario: Create a news page with automatic campaign and show it on search results
    Given a "News Category" term with the name superhelte
    And I go to the create news page
    And I fill a news page with the following:
      | Title    | Behatman is back  |
      | Lead     | Superhero returns |
      | Body     | Go Behatman!      |
      | Category | superhelte        |
    And I set the campaign keywords to "superhelte, usa"
    And I save the news page
    And I have searched for "term.subject=superhelte"
    Then the campaign "Behatman is back" should appear on the page
    And I have searched for "term.subject=usa"
    Then the campaign "Behatman is back" should appear on the page
    Given I have searched for "term.subject=biler"
    Then the campaign "Behatman is back" should not appear on the page
