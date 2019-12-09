# Scenario: Seek026

Tests if
1. online access button is shown,
2. reservation buttons, and
3. prompting to login by reservation
distributed on 4 scenarios.

## Method
See also seek040.

By using known data from pre-created data files to display a random object from file.
Then it checks based on css-class identifiers if the information is available.

For checking prompting to login, if not already logged in, by clicking Reservér, it is checked if the login fields are being shown. It is also documented by a screenshot. Login is not actually attempted.


## Notes
The login prompt scenario is currently excluded from the CCI suite, because the built site on CircleCI seems to use a different opensearch agency and/or service, despite attempts to reconfigure it.

Also tests for reservations are not on CCI because its
currently not possible to determine the exact dataset used there.
