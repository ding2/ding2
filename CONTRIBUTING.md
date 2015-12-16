# Contribution guidelines

Thank you for your interest in contributing. It is greatly appreciated.

# Pull requests

Code contributions to this project follow this process and set of requirements:

1. As a contributor you SHOULD create an issue describing the suggested change on [the Redmine installation platform.dandigbib.org](http://platform.dandigbib.org/) in Danish. This allows the business side of the project to evaluate your suggestion. If it accepted for inclusion it will be marked for review. The only exception from this rule is if the change does not affect end users in any way. This could be documentation changes, technical tests or changes to tools.
2. All communication on GitHub in English SHOULD be in English.
3. The title of your pull request MUST refer to the Redmine issue number if applicable e.g. `#[issue number]: [summary of change]`. The description of your pull request SHOULD include a link to the issue.
4. The body of the pull request SHOULD provide a short description of the suggested change and the reasoning behind the approach you have chosen.
5. If your change affects the user interface you SHOULD include a screenshot of the result with the pull request.
6. Your commit message MUST follow the [Drupal commit message format](https://www.drupal.org/node/52287): `Issue #[issue number] by [comma-separated usernames]: [Short summary of the change]`.
7. Your code MUST comply with [our coding guidelines](http://ting.dk/wiki/ding-code-guidelines).
8. If your change relates to fronted assets such as SCSS or JavaScript your pull request MUST provide [recompiled versions of the resulting files](https://github.com/ding2/ding2#theme-development). 
9. Your code will be run through a set of static analysis tools and continuous integration builds to ensure compliance and project integrity. Your code SHOULD pass these tests without raising new issues or breaking the build.
10. If your code does not pass these tests then you MUST provide a comment in the pull request explaining why this change should be exempt from the coding standards and process. If you have suggestions for changes to our coding standards going forward please send a mail to [dingcore@ting.dk](mailto:dingcore@ting.dk) or submit a pull request to the static analysis tool configuration ([Scrutinizer](https://github.com/ding2/ding2/blob/master/.scrutinizer.yml), [jshint](https://github.com/ding2/ding2/blob/master/.jshintrc)). Do not expect changes to be accepted before accepting your current pull request.
11. Core members will review your proposed change and provide questions, comments and suggestions for changes. Please follow up as quickly as possible. Changes will not be merged before passing through this review.

# Issues

This project does not use GitHub issues. If you have questions or experience problems using this issue please go to [our Redmine installation](http://platform.dandigbib.org/) in Danish.