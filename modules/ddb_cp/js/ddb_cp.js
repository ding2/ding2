/**
 * @file
 * Javascript file for the DDB CMS Control Panel.
 */

(function($) {
  "use strict";

  Drupal.behaviors.myBehavior = {
    attach: function (context, settings) {

      /**
       * Disables a button.
       *
       *  @param button
       *    The button to disable.
       */
      function disableButton(button) {
        button.addClass('form-button-disabled').attr('disabled', 'disabled');
      }

      /**
       * Enables a button.
       *
       *  @param button
       *    The button to enable.
       */
      function enableButton(button) {
        button.removeClass('form-button-disabled').removeAttr('disabled');
      }

      /**
       * Toggles visibility of branches in the test report tree.
       * 
       * @param branch
       *   The branch to toggle.
       */
      function toggleBranch(branch) {
        if (branch.parent().hasClass('collapsed')) {
          branch.parent().css('background-image', "url('/misc/menu-expanded.png')");
          branch.parent().removeClass('collapsed');
        }
        else {
          branch.parent().css('background-image', "url('/misc/menu-collapsed.png')");
          branch.parent().addClass('collapsed');
        }
      }

      /**
       * Updates status information in the control panel.
       */
      var updateStatus = function() {
        $.getJSON('/ajax/ddb_cp/status', function(data) {
          $.each(data, function(key, val) {
            $(key).replaceWith(val);
          });
        });
      
        // Find the elements to check.
        var dev_test_status = $('#dev-test-status');
        var stg_site_status = $('#stg-site-status');
        var stg_test_status = $('#stg-test-status');

        // Enables and disables buttons according to current system status
        if (dev_test_status.hasClass('test-ready') && stg_site_status.length === 0) {
          enableButton($('#edit-go-delete-dev'));
        }
        else if (dev_test_status.hasClass('test-ready') && stg_test_status.hasClass('test-ready')) {
          enableButton($('#edit-go-delete-dev'));
        }
        else {
          disableButton($('#edit-go-delete-dev'));
        }

        if (dev_test_status.hasClass('test-ready')) {
          enableButton($('#edit-go-test-dev'));
        }
        else {
          disableButton($('#edit-go-test-dev'));
        }

        if (dev_test_status.hasClass('test-ready') && dev_test_status.hasClass('test-status-ok')) {
          enableButton($('#edit-go-create-stg'));
        }
        else {
          disableButton($('#edit-go-create-stg'));
        }

        if (stg_site_status.hasClass('site-status-running') && stg_test_status.hasClass('test-ready')) {
          enableButton($('#edit-go-update-stg'));
        }
        else {
          disableButton($('#edit-go-update-stg'));
        }

        if (stg_test_status.hasClass('test-ready')) {
          enableButton($('#edit-go-test-stg'));
        }
        else {
          disableButton($('#edit-go-test-stg'));
        }

        if (stg_test_status.hasClass('test-ready') && stg_test_status.hasClass('test-status-ok')) {
          enableButton($('#edit-go-update-prod'));
        }
        else {
          disableButton($('#edit-go-update-prod'));
        }  
      };

      // Update status every 2 seconds.
      setInterval(updateStatus, 2000);

      /**
       * Load a full test report from the Jenkins server. 
       *
       * @param site
       *   'dev' or 'stg' site to load report for.
       */
      function loadTestReport(site) {
        var sitediv = $('#' + site + '-test-report');
        sitediv.html(' ');
        sitediv.addClass('loading');

        // Load the test report.
        $.ajax({
          method:'get',
          url:'/ajax/ddb_cp/test/result/' + site,
          success:function(data){
            sitediv.removeClass('loading');
            sitediv.html(data);

            // All children should be collapsed after loading.
            $('.' + site + '-stdout').hide();
            $('.' + site + '-test-case').hide();
            $('.' + site + '-test-step').hide();

            // Add click() functions to all but the leaf children.
            $('div.' + site + '-test-case > a').click(function() {
              toggleBranch($(this));
              $(this).siblings('.' + site + '-test-step').toggle();
              return true;
            });

            $('div.' + site + '-test-suite > a').click(function() {
              toggleBranch($(this));
              $(this).siblings('.' + site + '-test-case').toggle();
              return true;
            });

            $('div.' + site + '-test-step > a').click(function() {
              toggleBranch($(this));
              $(this).siblings('.' + site + '-stdout').toggle();
              return true;
            });
        
            sitediv.addClass('loaded');
            $('#reload-' + site + '-test-report').click(function() { loadTestReport(site); });
          }
        });
      }

      /**
       * Check if test report needs to be loaded
       */
      var checkTestReport = function () {
        var element = $('#dev-test-report');
        if (document.getElementById('edit-dev-status') && !element.hasClass('loading') && !element.hasClass('loaded') && !$('#edit-dev-result').hasClass('collapsed')) {
          loadTestReport('dev');
        }

        element = $('#stg-test-report');
        if (document.getElementById('edit-stg-status') && !element.hasClass('loading') && !element.hasClass('loaded') && !$('#edit-stg-result').hasClass('collapsed')) {
          loadTestReport('stg');
        }
      };

      /*
       * As Drupal's Form API doesn't allow attaching events to fieldsets,
       * we need to check regularly if the test report fieldset is open
       * or collapsed.
       */
      setInterval(checkTestReport, 500);

      // Triggers a recreation of the developer site.
      $('#edit-go-delete-dev').click(function() {
        $.get('/ajax/ddb_cp/recreate/dev');
      });

      // Triggers a recreation of the staging site.
      $('#edit-go-update-stg').click(function() {
        $.get('/ajax/ddb_cp/recreate/stg');
      });

      // Triggers an execution of the developer site test.
      $('#edit-go-test-dev').click(function() {
        $.get('/ajax/ddb_cp/test/execute/dev');
      });

      // Triggers an execution of the staging site test.
      $('#edit-go-test-stg').click(function() {
        $.get('/ajax/ddb_cp/test/execute/stg');
      });
    }
  };
})(jQuery);
