'use strict';

(function ($) {
  Drupal.behaviors.ting_ding_entity_buttons = {
    buttons: {
      '.ding-entity-button-see-online': 'see-online',
      '.ding-entity-button-other-formats': 'other-formats',
      '.ding-entity-button-infomedia': 'infomedia',
    },

    attach: function (context) {
      // Check the context, since behaviors can be attached several times.
      if (context !== document) {
        return;
      }

      var identifiers = {};
      var identifier = null;
      var $this = this;
      for (var i in $this.buttons) {
        identifiers[$this.buttons[i]] = [];

        // For event button type fetch it's parent ting entity id.
        $(i, context).each(function (index, element) {
          identifier = $(element)
            .parents('div[ting-object-id]')
            .attr('ting-object-id');

          if (identifiers[$this.buttons[i]].indexOf(identifier) === -1) {
            identifiers[$this.buttons[i]].push(identifier);
          }
        });
      }

      // Identifiers object is keyed with button types, therefore loop
      // the types and send ajax request for each.
      for (let i in identifiers) {
        if (identifiers[i].length === 0) {
          delete identifiers[i];
        }
      }

      $this.renderDingEntityButtons(identifiers);
    },

    renderDingEntityButtons: async function (identifiers) {
      for (let i in identifiers) {
        await this.sendButtonAjaxRequest(identifiers[i], i).then(() => {});
      }
    },

    sendButtonAjaxRequest: function (identifier, type) {
      return new Promise(resolve => {
        var element_settings = {
          url: '/ting/ding_entity_buttons/nojs/' + type,
          submit: {
            'js': true,
            'identifiers[]': identifier
          },
          success: function (response, status) {
            resolve();
            Drupal.ajax.prototype.success.apply(this, arguments);
          }
        };

        var ajax = new Drupal.ajax(null, document.body, element_settings);
        ajax.eventResponse(ajax, {});
      });
    }
  };
}(jQuery));
