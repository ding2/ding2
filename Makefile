circle-setup:
	# Build profile using drush make
	drush make ding2.make --no-core --contrib-destination=. -y
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
	cd $(DRUPAL_SITE_PATH) && drush site-install ding2 --db-url=mysql://ubuntu@127.0.0.1/circle_test -y
	# Set up test site.
	cd $(DRUPAL_SITE_PATH)/profiles/ding2/tests/behat && make test-setup
	# Make the files directory writable for the web server user.
	cd $(DRUPAL_SITE_PATH)/sites/default && sudo chown www-data. files

circle-static-analysis:
	# Run PHP7 Compatibility Checker - using tee to get non-rezero exit code (see https://github.com/sstalle/php7cc/issues/102)
	- 'php7cc --except=vendor --level=error --extensions=php,inc,module,install $DRUPAL_SITE_PATH | tee /dev/tty | grep -vq ''File: '''

circle-run-tests:
	# Run Behat tests.
	export BEHAT_PARAMS='{"extensions" : {"Behat\\MinkExtension" : {"base_url" : "http://127.0.0.1:80/" }}}' && \
	cd $(DRUPAL_SITE_PATH)/profiles/ding2/tests/behat && \
	./bin/behat --tags 'seekNologin' --format=html --out=results -p chrome
