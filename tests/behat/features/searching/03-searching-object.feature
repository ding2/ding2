Feature: test object displays after search
  In order to check searches and showing of materials on the DDB CMS
  As a user
  I want to do searches and examine the search result for
  - if creatorDescriptions are being shown if present
  - if accessInfomedia relations are being shown if present
  Numbering refers to the lines in the redroute spreadsheet for testing searching (seek004 is line 4)

  @api @seek040 @seekNologin @regression @wip
    Scenario: S040 Show creatorDescriptions
    Given filename "creator.dat" is used
      And I only want reservables
    When I display random object from file
    Then a 'hasCreatorDescription' entry is shown

  @api @seek040 @seekNologin @regression @wip
  Scenario: S040 Do not show creatorDescriptions
    Given filename "creatorNot.dat" is used
    When I display random object from file
    Then a 'hasCreatorDescription' entry is not shown

    # Taken out as WIP because accessInfoMedia is not well understood at this time
  @api @seek037 @seekNologin @wip @regression
  Scenario: S037 Show accessInfomedia
    Given filename "accessMedia.dat" is used
    When I display random object from file
    Then a 'hasReview' entry is shown

    # Taken out as WIP because accessInfoMedia is not well understood at this time
  @api @seek037 @seekNologin @wip @regression
  Scenario: S037 Do not show accessInfomedia
    Given filename "accessMediaNot.dat" is used
    When I display random object from file
    Then a 'hasReview' entry is not shown

  @api @seek035 @seekNologin @regression
  Scenario: S035 Show Object Placement
    Given filename 'creator.dat' is used
    When I display random object from file
    Then a 'hasPlacement' entry is shown

  @api @seek034 @seekNologin @regression
  Scenario: S034 Show Object Details
    Given filename 'creator.dat' is used
    When I display random object from file
    Then a 'hasDetails' entry is shown

  @api @seek025 @seekNologin @regression
  Scenario: S025 Search and display material see availability
    Given filename 'onlineAccess.dat' is used
    When I display random object from file
    Then I should see availability options

  @api @seek026 @seekNologin @regression
  Scenario: S026 Search and display material see online button shows
    Given filename 'onlineAccess.dat' is used
    When I display random object from file
    Then online access button is shown


    # Excluded from CCI because it cannot currently find the material, so probably not configured to right opensource
  @api @seek026 @seekNologin @regression
  Scenario: S026 Search and display material reservation button shows
    Given filename 'creator.dat' is used
      And I only want reservables
    When I display random object from file
    Then it is possible to click to reserve the material

    # Excluded from CCI because it cannot currently log in.
  @api @seek026 @seekLogin @regression
  Scenario: S026 Search and display material husk or add to list button shows
    Given I am logged in as a library user
    Given filename 'creator.dat' is used
    When I display random object from file
    Then it is possible to add to a list

  @api @seek026 @seekNologin @regression @cci
  Scenario: S026 Search and display material while not logged in should not show all buttons
    Given filename 'creator.dat' is used
    When I display random object from file
    Then it is possible to add to a list

    # Excluded from CCI because it cannot currently find the material, so probably not configured to right opensource
  @api @seek026 @seekNologin @regression
  Scenario: S026 Search and reserve material while not logged in to prompt login
    Given filename 'creator.dat' is used
      And I only want reservables
    When I display random object from file
    Then it is possible to click to reserve the material
    When I try to reserve the material
    Then I am prompted to login
    Then I save screenshot

  @api @seek027 @seekNologin @regression
  Scenario: S027 Search and display material should show cover page
    Given I have searched for "term.type=Bog and term.date='2016' and term.language='dansk'"
    When I open a random search result with a cover page to show the post
    Then I should see a cover page