# Prepare a site-installation for testing
circle-setup:
	# Build profile using drush make
	drush make project.make --no-core --contrib-destination=. -y
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
	# just build. This way we do not have to update project.make
	# for each build.
	drush make project.make --projects=drupal -y $(DRUPAL_SITE_PATH)
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
	# Run PHP7 Compatibility Checker - using tee to get non-rezero exit code (see https://github.com/sstalle/php7cc/issues/102)
	php7cc --except=vendor --level=error --extensions=php,inc,module,install $(DRUPAL_SITE_PATH) | tee /dev/tty | grep -vq 'File: '

circle-run-behat-tests:
	mkdir -p $(CIRCLE_TEST_REPORTS)/cucumber
	# Set up test site.
	cd $(DRUPAL_SITE_PATH)/profiles/ding2/tests/behat && make test-setup
	# Make the files directory writable for the web server user.
	cd $(DRUPAL_SITE_PATH)/sites/default && sudo chown www-data. files
	# Run Behat tests.
	export BEHAT_PARAMS='{"extensions" : {"Behat\\MinkExtension" : {"base_url" : "http://ding2.dev/" }}}' && \
	cd $(DRUPAL_SITE_PATH)/profiles/ding2/tests/behat && \
	export SCREENSHOT_DIR=$(CIRCLE_ARTIFACTS)/ && \
	./bin/behat --tags 'cci' --tags '~wip' --format=junit --out=$(CIRCLE_TEST_REPORTS)/cucumber/junit.xml --format=pretty --out=std -p chrome

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
	  "Opensearch"
	cd $(DRUPAL_SITE_PATH) && php scripts/run-tests.sh --php /opt/circleci/.phpenv/shims/php --xml $(CIRCLE_TEST_REPORTS)/phpunit \
	  --class ConnieSearchSearchProviderImplementationTestCase
