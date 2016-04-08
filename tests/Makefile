
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
	# Use Inlead dummy-alma.
	drush vset --exact alma_base_url 'http://dummy-alma.inlead.dk/web/alma/'
	# Too complex for oneliners, use a script.
	drush php-script setup-config-phpunit.php
