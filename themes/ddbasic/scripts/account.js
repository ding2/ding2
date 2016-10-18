(function($) {

  Drupal.behaviors.account = {
    attach: function(context, settings) {

      //We inject a select all button here, since the basic theme dont provide one for loans, only for reservations and bookmarks. To enhance the user experience, and to streamline the design it is added js-time.
      //In future please add a select all select to the form.

      //
      //Add select all on loans
      //

      var loan_form_action_buttons = $('#ding-loan-loans-form > div > .action-buttons', context),
          all_select_all_checkboxes = $('#ding-loan-loans-form > div > .select-all .form-item:not(.form-disabled) label', context),
          all_material_items_checkboxes = $('#ding-loan-loans-form > div > .material-item .form-item:not(.form-disabled) label');

      //Cache new renew-all
      var renew_all = $('.renew-all', context);

      //Wrap action form, so it behaves as reservations and bookmarks
      loan_form_action_buttons.wrap('<div class="actions-container"></div>');

      //Add the checkbox with same markup as reservations/bookmarks to keep styling consistent
      loan_form_action_buttons.parent().prepend('<div class="select-all"><div class="form-item"><input type="checkbox" id="js-select-all" name="js-title" value="1" class="form-checkbox"><label class="option" for="js-title">Vælg alle</label></div></div>');

      //cache the newly added checkbox
      var select_all_new = $('#ding-loan-loans-form > div > .actions-container label', context);

      //Renew all handler
      renew_all.on('click', function(event){
        //Select all
        if(select_all_new.siblings('input').prop('checked') == false) {
          select_all_new.click();
        }
        //Submit form
        $('#ding-loan-loans-form', context).submit();
      })

      select_all_new.on('click', function(){
        var $this = $(this).siblings('input');

        if($this.prop('checked') == true) { //deselect all
          all_select_all_checkboxes.each(function(){
            var $this = $(this);
            if($this.siblings('input').prop('checked') == true) {
              $this.click();
            }
          });
          $this.prop('checked', false);
          all_material_items_checkboxes.each(function(){
            var $this = $(this);
            if($this.siblings('input').prop('checked') == true) {
              $this.click();
            }
          });

        }
        else { //select all
          all_material_items_checkboxes.each(function(){
            var $this = $(this);
            if($this.siblings('input').prop('checked') == false) {
              $this.click();
            }
          });
          all_select_all_checkboxes.each(function(){
            var $this = $(this);
            if($this.siblings('input').prop('checked') == false) {
              $this.click();
            }
          });
          $this.prop('checked', true);
        }
      });

      all_material_items_checkboxes.on('click', function(){ //reset select all btn
        select_all_new.siblings('input').prop('checked', false);

      });

      all_select_all_checkboxes.on('click', function(){ //reset select all btn
        select_all_new.siblings('input').prop('checked', false);
      });


      // Reservations - delete all
      var delete_all = $('.delete-all', context),
          form,
          checkbox;

      delete_all.on('click', function(event){
        event.preventDefault();
        form = $(this).closest('form');
        checkbox = form.find('input[type="checkbox"]');

        checkbox.each(function( index ) {
          if($(this).prop('checked') == false) {
            $(this).prop("checked", true);
          }
        });
        //Submit form
        form.find('.action-buttons .delete-reservations input').removeAttr('disabled');
        // On
        form.find('.action-buttons .delete-reservations input').trigger('mousedown');
        form.find('.action-buttons .delete-reservations input').trigger('click');
      });
    }
  };

  $(function() {

    // Make actions-container sticky when it hits header
    var current,
        is_mobile,
        form_width,
        header_height,
        title_container_height,
        title_container_offset;

    $(window).bind('resize.account_form', function (evt) {

      if(ddbasic.breakpoint.is('mobile', 'mobile_out_account') == ddbasic.breakpoint.OUT) {
        is_mobile = false;
      }
      if(ddbasic.breakpoint.is('mobile', 'mobile_in_account') == ddbasic.breakpoint.IN) {
        is_mobile = true;
      }

      header_height = $('.site-header .topbar').height() + $('.site-header > .navigation-wrapper').height();

      $('.default-account-panel-layout').each(function( index ) {
        current = $(this);
        form_width = current.find('.pane-content > form').width();
        title_container_height = current.find('.title-container').height();
        title_container_offset = current.find('.title-container').offset();
        if (is_mobile == false) {
          current.find('.actions-container').css({
            "position": "absolute",
            "top": title_container_height,
            "width": form_width
          });
        } else {
          current.find('.actions-container').css({
            "position": "relative",
            "top": 0,
            "width": form_width
          });
        }
      });

    }).triggerHandler('resize.account_form');

    // Scroll event
    $(window).bind('scroll.actions_container', function (evt) {

      if (title_container_offset) {
        $('.default-account-panel-layout').each(function( index ) {
          current = $(this);
          form_width = current.find('.pane-content > form').width();
          title_container_height = current.find('.title-container').height();
          title_container_offset = current.find('.title-container').offset();

          var scroll = $(window).scrollTop(),
              action_container_position = title_container_offset.top + title_container_height - scroll;

          if (is_mobile == false) {

            if (action_container_position < header_height) {
              current.find('.actions-container').css({
                "position": "fixed",
                "top": header_height,
              });

            } else {
              current.find('.actions-container').css({
                "position": "absolute",
                "top": title_container_height,
              });
            }

            var current_offset = current.find('.actions-container').offset(),
                current_height = current.find('.actions-container').outerHeight() + 20,
                footer_offset = $('footer').offset(),
                footer_position = footer_offset.top - scroll;

            if(current_offset) {
              var current_position = current_offset.top + current_height - scroll;
            }

            // If next sibling has action container
            if (current.next('.default-account-panel-layout').find('.actions-container').length) {
              var next_offset = current.next().find('.actions-container').offset();

              if(current_offset && next_offset) {
                var next_position = next_offset.top - scroll,
                    current_top = next_position - current_height;
                console.log(current_position);
                console.log(next_position);
                if(current_position >= next_position) {
                  current.find('.actions-container').css({
                    "top": current_top,
                  });
                }
              }
            }

            // If scrolled to footer
            if (current_position >= footer_position) {
              var current_top = footer_position - current_height;
              current.find('.actions-container').css({
                "top": current_top,
              });
            }

          }
        });
      }

    });

  });

})(jQuery);