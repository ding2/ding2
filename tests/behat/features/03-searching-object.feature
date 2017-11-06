Feature: test object displays after search
  In order to check searches and showing of materials on the DDB CMS
  As a user
  I want to do searches and examine the search result for
  - if creatorDescriptions are being shown if present
  - if accessInfomedia relations are being shown if present

  @api @seek040 @seekNologin @regression
    Scenario: Show creatorDescriptions
    Given filename "creator.mat" is used
      And I only want reservables
    When I display random object from file
    Then a 'hasCreatorDescription' entry is shown

  @api @seek040 @seekNologin @regression
  Scenario: Do not show creatorDescriptions
    Given filename "accessMedia.mat" is used
    When I display random object from file
    Then a 'hasCreatorDescription' entry is not shown

  @api @seek037 @seekNologin @regression
  Scenario: Show accessInfomedia
    Given filename "accessMedia.mat" is used
    When I display random object from file
    Then a 'hasReview' entry is shown

  @api @seek037 @seekNologin @regression
  Scenario: Do not show accessInfomedia
    Given filename "creator.mat" is used
    When I display random object from file
    Then a 'hasReview' entry is not shown

  @api @seek025 @seekNologin @regression
  Scenario: Search and display material see availability
    Given filename 'onlineAccess.mat' is used
    When I display random object from file
    Then I should see availability options

  @api @seek026 @seekNologin @regression
  Scenario: Search and display material see online button shows
    Given filename 'onlineAccess.mat' is used
    When I display random object from file
    Then online access button is shown


  @api @seek026a @seekNologin @regression
  Scenario: Search and display material reservation button shows
    Given filename 'creator.mat' is used
      And I only want reservables
    When I display random object from file
    Then it is possible to click to reserve the material

  @api @seek026 @seekLogin @regression
  Scenario: Search and display material husk or add to list button shows
    Given I am logged in as a library user
    Given filename 'creator.mat' is used
    When I display random object from file
    Then it is possible to add to a list


  @api @seek026 @seekNologin @regression
  Scenario: Search and display material while not logged in should not show all buttons
    Given filename 'creator.mat' is used
    When I display random object from file
    Then it is not possible to add to a list

  @api @seek026 @seekNologin @regression
  Scenario: Search and reserve material while not logged in to prompt login
    Given filename 'creator.mat' is used
      And I only want reservables
    When I display random object from file
    Then it is possible to click to reserve the material
    When I try to reserve the material
    Then I am prompted to login
    Then I save screenshot

  @api @seek027 @seekNologin @regression
  Scenario: Search and display material should show cover page
    Given I have searched for "term.type=bog and holdingsitem.accessionDate>='NOW-300DAYS'"
    When I open a random search result with a cover page to show the post
    Then I should see a cover page