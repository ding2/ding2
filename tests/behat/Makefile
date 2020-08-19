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
