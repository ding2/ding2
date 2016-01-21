
test-setup: setup-modules setup-config

# Install a test site.
install-site:
	drush site-install ding2

# Setup test modules on site.
setup-modules:
	# Enable P2.
	drush en -y ding_p2_installer

	# We use the connie test provider for testing. Enable it an
	# disable the default alma.
	drush en -y connie
	drush dis -y alma

	# Enable mocking openlist provider.
	drush en -y connie_openlist

setup-config:
	# Configure ting.module
	drush vset -y ting_agency 100200
	drush vset -y ting_search_url 'http://oss-services.dbc.dk/opensearch/4.0.1/'
	drush vset -y ting_search_profile test

	# Configure openlist.
	drush vset -y ting_search_profileting_openlist_prefix test
	drush vset -y ting_openlist_wsdl 'http://v2_test.openlist.server003.b14cms.dk/?wsdl'

	# Activate consent and set config.
	drush vset -y user_consent_activate true
	drush vset -y loan_history_store_title_first_time ''
	drush vset -y loan_history_store_title ''
	drush php-eval 'variable_set("loan_history_store_description_first_time", array("value" => ""));'
	drush php-eval 'variable_set("loan_history_store_description", array("value" => ""));'

