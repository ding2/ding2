Feature: Login for library users
  As a user
  In order to interact with the library system
  I want to be able to log in

  @api
  Scenario: Login
    Given I am on "/"
    When I log in as a library user
    Then I should see "Mine sider"
