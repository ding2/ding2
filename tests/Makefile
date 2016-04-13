
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
	drush vset --exact ting_search_url 'http://oss-services.dbc.dk/opensearch/4.0.1/'
	drush vset --exact ting_search_profile test

setup-config-phpunit: setup-config
	# ting.module.
	drush vset --exact ting_agency '775100'
	drush vset --exact ting_search_profile 'ding2taltest'
	drush vset --exact ting_search_url 'http://opensearch.addi.dk/4.0.1/'
	# alma.module
	drush vset --exact alma_base_url 'http://dummy-alma.inlead.dk/web/alma/'
	drush vset --exact alma_enable_reservation_deletion 1
	# ting_covers.module
	drush vset --exact addi_wsdl_url 'http://moreinfo.addi.dk/2.1/'
	# ting_search_autocomplete
	drush vset --exact ting_search_autocomplete_suggestion_url 'http://opensuggestion.addi.dk/b3.0_2.0/'
	drush vset --exact ting_search_autocomplete_method 'facets'
	# The rest is set in setup-config-phpunit.php	
	# Too complex for oneliners, use a script.
	drush php-script setup-config-phpunit.php
