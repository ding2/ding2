
test-setup: setup-modules setup-config

install-site:
	drush site-install ding2

setup-modules:
	# Enable P2.
	drush en -y ding_p2_installer

	# We use the connie test provider for testing. Enable it an
	# disable the default alma.
	drush en -y connie
	drush dis -y alma

setup-config:
	# Activate consent and set config.
	drush vset -y user_consent_activate true
	drush vset -y loan_history_store_title_first_time ''
	drush vset -y loan_history_store_title ''
	drush php-eval 'variable_set("loan_history_store_description_first_time", array("value" => ""));'
	drush php-eval 'variable_set("loan_history_store_description", array("value" => ""));'
