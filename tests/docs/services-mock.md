# Services and mocking

Ding2 uses different services like Alma or OpenRuth, OpenSearch, etc.
Ideally we would use either a mock for the service (like Connie which
is a login mock that makes it simple to login) or a test service which
could be installed in e.g. a Docker container or a vagrant box to
avoid using services on the Internet. This way we can have a
predictable service with some static data that doesn't change often,
so the test can focus on what is tested instead of testing that the
Internet is working adequately stable. Especially when more tests are
running at the same time, it can be a problem using online services.

However, currently it's not possible to install test services for e.g.
OpenSearch, so instead we will be using either mocks when possible or
online test services

The problem using online services is that when they are updated, the
tests using the service might have to be updated too in order to
reflect the changes in the service. And when the service is updated,
we need to use the same version of the test service. I.e. there are
more dependencies when using online services, and we might get failed
tests because if these depencencies. When we're using a mock or a test
service, the test can focus on what is being tested.

## Connie - login

Connie is a Ding provider which doesn't use any external services and
makes it easy to log in. The password is the last 4 characters of the
username.

## Connie Openlist

The module connie_openlist provides a mock for Openlist. It has a
limited set of Openlist functions which focus on creating lists and
getting them.

## OpenSearch

https://opensource.dbc.dk/services/open-search-web-service

It's not possible to install a test instance of this service, and
mocking of this service is quite advanced, so we will be using a test
service available on oss-services.dbc.dk. The problem using this
service is that we have no way of knowing, when the service will be
restarted or updated or for other reasons be unavailable at certain
times.

Currently using http://oss-services.dbc.dk/opensearch/4.0.1/
