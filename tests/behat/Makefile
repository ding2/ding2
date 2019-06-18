# Allow for overriding the drush command. Handy if running drush in a
# container.
DRUSH ?= drush

test-setup: setup-modules setup-config

# Setup test modules on site.
setup-modules:
	# We use the connie test provider for testing. Enable it and
	# disable the default fbs.
	$(DRUSH) en -y connie
	$(DRUSH) dis -y fbs

	# Enable mocking openlist provider.
	# Currently disabled as the API has changed and Connie haven't been updated.
	# $(DRUSH) en -y connie_openlist

setup-config:
	# Configure ting.module
	$(DRUSH) vset -y ting_agency 100200
	$(DRUSH) vset -y opensearch_url 'https://oss-services.dbc.dk/opensearch/5.0/'
	$(DRUSH) vset -y opensearch_search_profile test

	# Configure recommendation service
	$(DRUSH) vset -y opensearch_recommendation_url 'http://openadhl.addi.dk/1.1/'
	$(DRUSH) vset -y ting_infomedia_url 'http://useraccessinfomedia.addi.dk/1.3/'

	# Configure autocomplete
	$(DRUSH) vset -y opensearch_search_autocomplete_suggestion_url 'http://opensuggestion.addi.dk/b3.5_2.0/'
	$(DRUSH) vset -y opensearch_search_autocomplete_method 'facets'

	# Configure openlist.
	$(DRUSH) vset -y ting_openlist_prefix test
	$(DRUSH) vset -y ting_openlist_wsdl 'https://test.openlist.ddbcms.dk/?wsdl'
	$(DRUSH) vset -y ting_library_code 100200

	# Activate consent and set config.
	$(DRUSH) vset -y user_consent_activate true
	$(DRUSH) php-eval 'variable_set("loan_history_store_title", array("value" => ""));'
	$(DRUSH) php-eval 'variable_set("loan_history_store_title_first_time", array("value" => ""));'
	$(DRUSH) php-eval 'variable_set("loan_history_store_description_first_time", array("value" => ""));'
	$(DRUSH) php-eval 'variable_set("loan_history_store_description", array("value" => ""));'
