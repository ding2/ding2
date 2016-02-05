
circle-setup:
	# Build profile using drush make
	drush make ding2.make --no-core --contrib-destination=. -y
	# Install theme dependencies
	cd themes/ddbasic && npm install
	# Process theme files.
	# If there are any changes then fail the build. The result of processing
	# should be committed along with the source changes.
	cd themes/ddbasic && node_modules/.bin/gulp uglify sass
	git diff --exit-code
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
	cd $(DRUPAL_SITE_PATH)/profiles/ding2/tests && make test-setup
	# Make the files directory writable for the web server user.
	cd $(DRUPAL_SITE_PATH)/sites/default && sudo chown www-data. files

circle-run-tests:
	# Run Behat tests.
	cd $(DRUPAL_SITE_PATH)/profiles/ding2/tests && \
	eval `phpenv sh-shell $(BEHAT_PHP_VERSION)` && \
	./bin/behat --tags '~wip' --tags '~regression' \
	$(if $(subst 0,,$(CIRCLE_NODE_INDEX)),--tags '~no_circle_selenium') \
	--format=junit --format=pretty \
	$(if $(subst 0,,$(CIRCLE_NODE_INDEX)),-p chrome)
