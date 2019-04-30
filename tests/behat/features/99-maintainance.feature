Feature: Maintainance
  Not really tests, but scenarios that updates test files.

  @maintenanceonly @no_ci
  Scenario: Update files after well is refreshed
    Given I create files 'aim' from opensearch on relation 'accessInfoMedia'
    Given I create files 'credesc' from opensearch on relation 'hasCreatorDescription'
    Given I create files 'onlacc' from opensearch on relation 'hasOnlineAccess'
    Given I create files 'hasrev' from opensearch on relation 'hasReview'

  @specialtests @no_ci
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



