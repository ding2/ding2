# What to test #

When we write Behat tests, we don't test everything.

## Business logic ##

Focus should be on business logic. We want to test essential flows,
including what users and roles are allowed to perform actions.

## What not to test ##

Basically we don't use Behat testing for functionality, where testing
should be done with unit tests or integration tests. I.e. we don't use
Behat tests for low level code, web services, APIs, as they are not
directly relevant for the business logic.

We don't want to test:
 - Low level code (e.g. database functions, hooks)
 - Every single edge case
 - External services
 - Drupal

Testing all edges in the code, that the database functions are
correct, that external web services are working properly, that Drupal
is working as it's supposed are all something that should be tested in
other ways, e.g. with unit tests. Behat tests are tests on a higher
level.
