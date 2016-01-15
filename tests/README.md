# Ding Behat tests #

## Usage ##

composer install
make setup
./bin/behat --tags '~wip'

### Profiles ###

todo

### Tags ###

todo @wip, @regression, @no_messages_check

## Development ##

### Tags ###

todo @wip, @regression, @no_messages_check

### Test layout ###

todo

### Service mocking ###

todo make targets, MOCK_HOST

#### Services ####

Ding depends on multiple external services, each which is handled in
one of two ways:

Provider based services is mocked by creating a mocking
implementation. Most of these is in Connie, the testing provider
module included in ding_provider.

Others are mocked by recording and playing back service communication
using mock-http-server. Recording is preferably done against a test
installation of the service.  These are currently: 

##### Opensearch #####

https://opensource.dbc.dk/services/open-search-web-service

Using http://oss-services.dbc.dk/opensearch/4.0.1/

#### Playback ####

todo

#### Recording ####

todo

