Feature: Follow tags
  In order to be notified when there is new content for specific subjects
  As a library user
  I want to be able to follow and unfollow subjects

  Background:
    Given I am logged in as a library user
    And the list of my interests exists

  @api @javascript
  Scenario: Search for a subject
    Given I am on a material page that has the subject science fiction
    Then I should see the subject "science fiction" on the material

  @api @javascript
  Scenario: Follow a subject
    Given I am on a material page that has the subject science fiction
    When I follow the subject "science fiction"
    Then I should see the subject "science fiction" on the list of my interests

  @api @javascript
  Scenario: Unfollow a subject
    Given I am following the subject "orkideer"
    When I unfollow the subject "orkideer"
    Then I should not see the subject "orkideer" on the list of my interests
