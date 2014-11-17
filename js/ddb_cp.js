/**
 * @file
 * Javascript file for the DDB CMS Control Panel.
 */

(function($) {
  "use strict";

  Drupal.behaviors.myBehavior = {
    attach: function (context, settings) {

      /**
       * @todo: Missing function description.
       *
       *  @param button
       *    @todo: missing description.
       */
      function disableButton(button) {
        button.addClass('form-button-disabled').attr('disabled', 'disabled');
      }

      /**
       * @todo: Missing function description.
       *
       *  @param button
       *    @todo: missing description.
       */
      function enableButton(button) {
        button.removeClass('form-button-disabled').removeAttr('disabled');
      }

      /**
       * @todo: Missing function description.
       */
      var devStatus = function() {
        $.getJSON('/ajax/ddb_cp/status', function(data) {
          $.each(data, function(key, val) {
            $(key).replaceWith(val);
          });
        });
      
        // Find the elements to check.
        var dev_test_status = $('#dev-test-status');
        var stg_site_status = $('#stg-site-status');
        var stg_test_status = $('#stg-test-status');

        // @todo: Would be nice with a comment here about all this if
        //        statements.
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

      // @todo; Why this timeout?
      setInterval(devStatus, 2000);

      /**
       * @todo: Missing function description.
       *
       * @todo: The click event handlers in this function, do a lot of the same
       *        could it be move to a helper function?
       *
       * @param site
       *   @todo: Missing description.
       */
      function loadTestReport(site) {
        var sitediv = $('#' + site + '-test-report');
        sitediv.html(' ');
        sitediv.addClass('loading');

        // @todo: Would be nice with a comment here.
        $.ajax({
          method:'get',
          url:'/ajax/ddb_cp/test/result/' + site,
          success:function(data){
            sitediv.removeClass('loading');
            sitediv.html(data);

            // @todo: Would be nice with a comment here.
            $('.' + site + '-stdout').hide();
            $('.' + site + '-test-case').hide();
            $('.' + site + '-test-step').hide();

            // @todo: Would be nice with a comment here.
            $('div.' + site + '-test-case > a').click(function() {
              var self = $(this);
              if (self.parent().hasClass('collapsed')) {
                self.parent().css('background-image', "url('/misc/menu-expanded.png')");
                self.parent().removeClass('collapsed');
              }
              else {
                self.parent().css('background-image', "url('/misc/menu-collapsed.png')");
                self.parent().addClass('collapsed');
              }
        
              $(this).siblings('.' + site + '-test-step').toggle();

              return true;
            });

            // @todo: Would be nice with a comment here.
            $('div.' + site + '-test-suite > a').click(function() {
              var self = $(this);
              if (self.parent().hasClass('collapsed')) {
                self.parent().css('background-image', "url('/misc/menu-expanded.png')");
                self.parent().removeClass('collapsed');
              }
              else {
                self.parent().css('background-image', "url('/misc/menu-collapsed.png')");
                self.parent().addClass('collapsed');
              }
        
              $(this).siblings('.' + site + '-test-case').toggle();
        
              return true;
            });

            // @todo: Would be nice with a comment here.
            $('div.' + site + '-test-step > a').click(function() {
              var self = $(this);
              if (self.parent().hasClass('collapsed')) {
                self.parent().css('background-image', "url('/misc/menu-expanded.png')");
                self.parent().removeClass('collapsed');
              }
              else {
                self.parent().css('background-image', "url('/misc/menu-collapsed.png')");
                self.parent().addClass('collapsed');
              }
        
              $(this).siblings('.' + site + '-stdout').toggle();
        
              return true;
            });
        
            sitediv.addClass('loaded');
            $('#reload-' + site + '-test-report').click(function() { loadTestReport(site); });
          }
        });
      }

      /**
       * @todo: Missing function description.
       */
      var checkTestReport = function () {
        var element = $('#dev-test-report');
        if (document.getElementById('edit-dev-status') && !element.hasClass('loading') && !element.hasClass('loaded') && !$('#edit-dev-result').hasClass('collapsed')) {
          loadTestReport('dev');
        }

        if (document.getElementById('edit-stg-status') && !element.hasClass('loading') && !element.hasClass('loaded') && !$('#edit-stg-result').hasClass('collapsed')) {
          loadTestReport('stg');
        }
      };

      // @todo: Why is this interval here?
      setInterval(checkTestReport, 500);

      // @todo: Would be nice with a comment here.
      $('#edit-go-delete-dev').click(function() {
        $.get('/ajax/ddb_cp/recreate/dev');
      });

      // @todo: Would be nice with a comment here.
      $('#edit-go-update-stg').click(function() {
        $.get('/ajax/ddb_cp/recreate/stg');
      });

      // @todo: Would be nice with a comment here.
      $('#edit-go-test-dev').click(function() {
        $.get('/ajax/ddb_cp/test/execute/dev');
      });

      // @todo: Would be nice with a comment here.
      $('#edit-go-test-stg').click(function() {
        $.get('/ajax/ddb_cp/test/execute/stg');
      });
    }
  };
})(jQuery);
