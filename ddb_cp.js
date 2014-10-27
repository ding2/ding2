/**
 * 
 */

(function($) {
  Drupal.behaviors.myBehavior = {
    attach: function (context, settings) {
      function disableButton(button) {
        button.addClass('form-button-disabled').attr('disabled', 'disabled');
      }
      
      function enableButton(button) {
        button.removeClass('form-button-disabled').removeAttr('disabled');
      }
    
      var devStatus = function() {
        $.getJSON('/ajax/ddb_cp/status', function(data) {
          $.each(data, function(key, val) {
            $(key).replaceWith(val);
          });
        });
      
        if ($('#dev-test-status').hasClass('test-ready') && $('#stg-site-status').length == 0) {
          enableButton($('#edit-go-delete-dev'));
        } else if ($('#dev-test-status').hasClass('test-ready') && $('#stg-test-status').hasClass('test-ready')) {
          enableButton($('#edit-go-delete-dev'));
        } else {
          disableButton($('#edit-go-delete-dev'));
        }

        if ($('#dev-test-status').hasClass('test-ready')) {
          enableButton($('#edit-go-test-dev'));
        } else {
          disableButton($('#edit-go-test-dev'));
        }

        if ($('#dev-test-status').hasClass('test-ready') && $('#dev-test-status').hasClass('test-status-ok')) {
          enableButton($('#edit-go-create-stg'));
        } else {
          disableButton($('#edit-go-create-stg'));
        }

        if ($('#stg-site-status').hasClass('site-status-running') && $('#stg-test-status').hasClass('test-ready')) {
          enableButton($('#edit-go-update-stg'));
        } else {
          disableButton($('#edit-go-update-stg'));
        }

        if ($('#stg-test-status').hasClass('test-ready')) {
          enableButton($('#edit-go-test-stg'));
        } else {
          disableButton($('#edit-go-test-stg'));
        }

        if ($('#stg-test-status').hasClass('test-ready') && $('#stg-test-status').hasClass('test-status-ok')) {
          enableButton($('#edit-go-update-prod'));
        } else {
          disableButton($('#edit-go-update-prod'));
        }  
      }
  
      setInterval(devStatus, 2000);
      
      function loadTestReport(site) {
        sitediv = '#' + site + '-test-report';
        $(sitediv).html(' ');      
        $(sitediv).addClass('loading');      
      
        $.ajax({
          method:'get',
          url:'/ajax/ddb_cp/test/result/' + site,
          success:function(data){
            $(sitediv).removeClass('loading');
  
            $(sitediv).html(data);
  
            $('.' + site + '-stdout').hide();
            $('.' + site + '-test-case').hide();
            $('.' + site + '-test-step').hide();
  
            $('div.' + site + '-test-case > a').click(function() {
              if ($(this).parent().hasClass('collapsed')) {
                $(this).parent().css('background-image', "url('/misc/menu-expanded.png')");
                $(this).parent().removeClass('collapsed');
              } else {
                $(this).parent().css('background-image', "url('/misc/menu-collapsed.png')");
                $(this).parent().addClass('collapsed');
              }
        
              $(this).siblings('.' + site + '-test-step').toggle();
        
              return true;
            })
            
            $('div.' + site + '-test-suite > a').click(function() {
              if ($(this).parent().hasClass('collapsed')) {
                $(this).parent().css('background-image', "url('/misc/menu-expanded.png')");
                $(this).parent().removeClass('collapsed');
              } else {
                $(this).parent().css('background-image', "url('/misc/menu-collapsed.png')");
                $(this).parent().addClass('collapsed');
              }
        
              $(this).siblings('.' + site + '-test-case').toggle();
        
              return true;
            })
            
            $('div.' + site + '-test-step > a').click(function() {
              if ($(this).parent().hasClass('collapsed')) {
                $(this).parent().css('background-image', "url('/misc/menu-expanded.png')");
                $(this).parent().removeClass('collapsed');
              } else {
                $(this).parent().css('background-image', "url('/misc/menu-collapsed.png')");
                $(this).parent().addClass('collapsed');
              }
        
              $(this).siblings('.' + site + '-stdout').toggle();
        
              return true;
            })
        
            $(sitediv).addClass('loaded');      
            $('#reload-' + site + '-test-report').click(function() { loadTestReport(site); });
          }
        })
      }
      
      var checkTestReport = function () {
        if (document.getElementById('edit-dev-status') && !$('#dev-test-report').hasClass('loading') && !$('#dev-test-report').hasClass('loaded') && !$('#edit-dev-result').hasClass('collapsed')) {
          loadTestReport('dev');
        }

        if (document.getElementById('edit-stg-status') && !$('#stg-test-report').hasClass('loading') && !$('#stg-test-report').hasClass('loaded') && !$('#edit-stg-result').hasClass('collapsed')) {
          loadTestReport('stg');
        }
      }
      
      setInterval(checkTestReport, 500);
      
      $('#edit-go-delete-dev').click(function() {
        $.get('/ajax/ddb_cp/recreate/dev');
      })
      
      $('#edit-go-update-stg').click(function() {
        $.get('/ajax/ddb_cp/recreate/stg');
      })
      
      $('#edit-go-test-dev').click(function() {
        $.get('/ajax/ddb_cp/test/execute/dev');
      })
      
      $('#edit-go-test-stg').click(function() {
        $.get('/ajax/ddb_cp/test/execute/stg');
      })      
    }
  };
})(jQuery);
