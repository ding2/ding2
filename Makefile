
# Prepare a site-installation for testing
circle-setup:
	# Build profile using drush make
	drush make ding2.make --no-core --contrib-destination=. -y
	# Build the root composer.json. It only references our deployment tool so we
	# mainly install it to verify that the depedency can still be resolved.
	composer install
	# Install theme dependencies
	cd themes/ddbasic && npm install
	# Process theme files.
	# If there are any changes then fail the build. The result of processing
	# should be committed along with the source changes.
	cd themes/ddbasic && node_modules/.bin/gulp uglify sass
	# Readable changes. Exclude minified CSS files compiled from SCSS. Changes
	# in verbose version will probably also apply here.
	git diff --exit-code -- . ':(exclude)themes/ddbasic/css/*.min.css'
	# Do a complete diff in short form as well for good measure. This will
	# catch changes in excluded files.
	git diff --stat --exit-code
	# Built an entire Drupal site with core, contrib and custom
	# code First we build Drupal core only. Instead of using the
	# profile specified in the make file we use the one we have
	# just build. This way we do not have to update drupal.make
	# for each build.
	drush make drupal.make --projects=drupal -y $(DRUPAL_SITE_PATH)
	# Copy the current profile which has just been built into Drupal core
	mkdir $(DRUPAL_SITE_PATH)/profiles/ding2
	cp -R ./* $(DRUPAL_SITE_PATH)/profiles/ding2/
	# Install the site using the ding2 profile
	cd $(DRUPAL_SITE_PATH) && drush site-install ding2 --db-url=mysql://ubuntu@127.0.0.1/circle_test -y ding2_module_selection_form.providers_selection=connie
	# Notices and warnings are seen as an error from simpletests point of view
	# and is added to the xml-output as such. Idealy we would not have any
	# notices or warnings, but in the current state of affairs we see quite a
	# few, so in order to focus on actually getting some tests up and running
	# we're disabling notices and warnings for now. In the future it would be a
	# good idéa to revisit running with E_ALL.
	echo "ini_set('error_reporting', E_ALL & ~E_NOTICE & ~E_STRICT & ~E_DEPRECATED & ~E_WARNING);" | sudo tee --append $(DRUPAL_SITE_PATH)/sites/default/settings.php

# Run ding2 unittests
circle-run-unit-tests:
	cd $(DRUPAL_SITE_PATH)/profiles/ding2/modules/ding_test && composer install
	cd $(DRUPAL_SITE_PATH) && drush pml
	cd $(DRUPAL_SITE_PATH) && drush dis fbs alma -y
	cd $(DRUPAL_SITE_PATH) && drush en connie ding_test -y
	# Run all ding unit-tests
	mkdir -p $(CIRCLE_TEST_REPORTS)/phpunit
	# Circleci has a proxy for the php-executable which confuses run-tests.sh,
	# so we have to specify the full path to the executable.
	# Tests to be run are referenced as a comma-seperated list of group-names.
	cd $(DRUPAL_SITE_PATH) && php scripts/run-tests.sh --php /opt/circleci/.phpenv/shims/php --xml $(CIRCLE_TEST_REPORTS)/phpunit \
	  "Ding! - Ting search unittest"
	cd $(DRUPAL_SITE_PATH) && php scripts/run-tests.sh --php /opt/circleci/.phpenv/shims/php --xml $(CIRCLE_TEST_REPORTS)/phpunit \
	  --class ConnieSearchSearchProviderImplementationTestCase

