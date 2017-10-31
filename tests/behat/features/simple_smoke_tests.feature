Feature: Smoke tests
  Simple test scenarios to test installation of behat, and basic activities


  // this scenario simply opens up the front page and reports if it can
  // see the text Kontakt, which is presumed to be present on all libraries.
  // Even if it isn't and this will fail, we will have access to a
  // screenshot, to document that we have opened a browser, and navigated
  // on it. In other words, if we succeed then we can run behat tests.
  @simplesmoke @api
  Scenario: See front page
    Given I am on "/"
      And I accept cookies
     Then I save screenshot
     Then I should see "Kontakt"
