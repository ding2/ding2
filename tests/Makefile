
test-setup: setup-modules setup-config

test-setup-phpunit: setup-modules setup-config-phpunit

# Install a test site.
install-site:
	drush site-install ding2

# Setup test modules on site.
setup-modules:
	# Nothing to be done yet.

setup-config:
	# Configure ting.module
	drush vset --exact ting_agency 100200
	drush vset --exact ting_search_url 'http://oss-services.dbc.dk/opensearch/4.3/'
	drush vset --exact ting_search_profile test

setup-config-phpunit: setup-config
	# bookmark module: Is not enabled by default.
	# drush en ding_bookmark -y
	# ting.module.
  # Note: agency 775100 has no reservable items in the test database
	drush vset --exact ting_agency 100200
	drush vset --exact ting_search_profile test
	drush vset --exact ting_search_url 'http://oss-services.dbc.dk/opensearch/4.3/'
	# alma.module
	drush vset --exact alma_base_url 'http://dummy-alma.inlead.dk/web/alma/'
	drush vset --exact alma_enable_reservation_deletion 1
	# ting_covers.module
	drush vset --exact addi_wsdl_url 'http://oss-services.dbc.dk/moreinfo/trunk/'
	# ting_search_autocomplete
	drush vset --exact ting_search_autocomplete_suggestion_url 'http://oss-services.dbc.dk/suggest/'
	drush vset --exact ting_search_autocomplete_method 'facets'
	# The rest is set in setup-config-phpunit.php
	# Too complex for oneliners, use a script.
	drush php-script setup-config-phpunit.php
	# clear cache
	drush cc all
