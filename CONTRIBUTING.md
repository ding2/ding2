# Contribution guidelines

Thank you for your interest in contributing. It is greatly appreciated.

# Pull requests

Code contributions to this project follow this process and set of requirements:

1. As a contributor you should [create an issue](http://platform.dandigbib.org/projects/ddb-cms/issues/new) describing the suggested change on [our Redmine installation platform.dandigbib.org](http://platform.dandigbib.org/projects/ddb-cms/) in Danish. This allows the business side of the project to evaluate your suggestion. If it accepted for inclusion it will be marked for review. To create an issue you must [have an account on the site](http://platform.dandigbib.org/account/register). The only exception from this rule is if the change does not affect end users in any way. This could be developer documentation changes or changes to tools.
2. All communication on GitHub should be in English.
3. The title of your pull request must refer to the Redmine issue number if applicable e.g. *[issue number]: [short summary of change]*.
4. The description of your pull request should include a link to the issue.
5. The body of the pull request should provide a short description of the suggested change and the reasoning behind the approach you have chosen.
6. If your change affects the user interface you should include a screenshot of the result with the pull request.
7. The first line of your commit message (the subject) must follow this format: `[issue number]: [short summary of change]`. The subject should be kept around 50 characters long. The subject must not be more than 69 characters long. Strive for about 50 characters.
8. Your code must comply with [our coding guidelines](docs/code_guidelines.md).
9. If your change relates to fronted assets such as SCSS or JavaScript your pull request must provide [recompiled versions of the resulting files](README.md#theme-development). 
10. Your code will be run through a set of static analysis tools and continuous integration builds to ensure compliance and project integrity. Your code should pass these tests without raising new issues or breaking the build. [The status of the tests will be reported within the pull request](https://github.com/blog/1935-see-results-from-all-pull-request-status-checks). If you want to be notified through other means you must follow the projects/subscribe to updates on the individual test platforms ([Scrutinizer](https://scrutinizer-ci.com/g/ding2/ding2/), [Circle](https://circleci.com/gh/ding2/ding2)).
11. If your code does not pass these tests then you must provide a comment in the pull request explaining why this change should be exempt from the code standards and process. If you have suggestions for changes to our code standards going forward please send a mail to [dingcore@ting.dk](mailto:dingcore@ting.dk) or submit a pull request to the static analysis tool configuration ([Scrutinizer](https://github.com/ding2/ding2/blob/master/.scrutinizer.yml), [jshint](https://github.com/ding2/ding2/blob/master/.jshintrc)). Do not expect changes to be accepted before accepting your current pull request.
12. Core members will review your proposed change and provide questions, comments and suggestions for changes. Please follow up as quickly as possible. Changes will not be merged before passing through this review.

# Issues

This project does not use GitHub issues. If you have questions or experience problems using the project please go to [our Redmine installation](http://platform.dandigbib.org/) (in Danish).
