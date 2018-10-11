test-setup: setup-modules setup-config

# Install a test site.
install-site:
	drush site-install ding2

# Setup test modules on site.
setup-modules:
	# We use the connie test provider for testing. Enable it and
	# disable the default fbs.
	drush en -y connie
	drush dis -y fbs

	# Enable mocking openlist provider.
	drush en -y connie_openlist

setup-config:
	# Configure ting.module
	drush vset -y ting_agency 100200
	drush vset -y opensearch_url 'https://oss-services.dbc.dk/opensearch/b3.5_5.0/'
	drush vset -y opensearch_search_profile test

	# Configure recommendation service
	drush vset -y opensearch_recommendation_url 'http://openadhl.addi.dk/1.1/'
	drush vset -y ting_infomedia_url 'http://useraccessinfomedia.addi.dk/1.3/'

	# Configure autocomplete
	drush vset -y opensearch_search_autocomplete_suggestion_url 'http://opensuggestion.addi.dk/b3.5_2.0/'
	drush vset -y opensearch_search_autocomplete_method 'facets'

	# Configure openlist.
	drush vset -y ting_openlist_prefix test
	drush vset -y ting_openlist_wsdl 'https://test.openlist.ddbcms.dk/?wsdl'

	# Activate consent and set config.
	drush vset -y user_consent_activate true
	drush vset -y loan_history_store_title ''
	drush vset -y loan_history_store_title_first_time ''
	drush php-eval 'variable_set("loan_history_store_description_first_time", array("value" => ""));'
	drush php-eval 'variable_set("loan_history_store_description", array("value" => ""));'
