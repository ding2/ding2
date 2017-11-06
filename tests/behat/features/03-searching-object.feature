Feature: test object displays after search
  In order to check searches and showing of materials on the DDB CMS
  As a user
  I want to do searches and examine the search result for
  - if creatorDescriptions are being shown if present
  - if accessInfomedia relations are being shown if present

  @api @seek040 @seekNologin
    Scenario: Show creatorDescriptions
    Given filename "creator.mat" is used
      And I only want reservables
    When I display random object from file
    Then a 'hasCreatorDescription' entry is shown

  @api @seek040 @seekNologin
  Scenario: Do not show creatorDescriptions
    Given filename "accessMedia.mat" is used
    When I display random object from file
    Then a 'hasCreatorDescription' entry is not shown

  @api @seek037 @seekNologin
  Scenario: Show accessInfomedia
    Given filename "accessMedia.mat" is used
    When I display random object from file
    Then a 'hasReview' entry is shown

  @api @seek037 @seekNologin
  Scenario: Do not show accessInfomedia
    Given filename "creator.mat" is used
    When I display random object from file
    Then a 'hasReview' entry is not shown

