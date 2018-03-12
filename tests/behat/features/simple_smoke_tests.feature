Feature: Smoke tests
  Simple test scenarios to test installation of behat, and basic activities


  // this scenario simply opens up the front page and reports if it can
  // see the text Kontakt, which is presumed to be present on all libraries.
  // Even if it isn't and this will fail, we will have access to a
  // screenshot, to document that we have opened a browser, and navigated
  // on it. In other words, if we succeed then we can run behat tests.
  @simplesmoke @api @cci
  Scenario: See front page
    Given I am on "/"
      And I accept cookies
     Then I save screenshot
     Then I should see "Kontakt"

  @simplelogin @api
  Scenario: Attempt to login
    Given I am on "/"
    And I accept cookies
    And I am logged in as a library user

  @maintenanceonly 
  Scenario: Update files after well is refreshed
    Given I create files 'aim' from opensearch on relation 'accessInfoMedia'
    Given I create files 'credesc' from opensearch on relation 'hasCreatorDescription'
    Given I create files 'onlacc' from opensearch on relation 'hasOnlineAccess'
    Given I create files 'hasrev' from opensearch on relation 'hasReview'

  @specialtests
  Scenario: Test entries in datafiles
    Given filename "creator.dat" is used
    When I display all objects from file
    Given filename "creatorNot.dat" is used
    When I display all objects from file
    Given filename "accessMedia.dat" is used
    When I display all objects from file
    Given filename "accessMediaNot.dat" is used
    When I display all objects from file
    Given filename "onlineAccess.dat" is used
    When I display all objects from file



