'use strict';

(function ($) {
  Drupal.behaviors.ting_ding_entity_buttons = {
    buttons: {
      '.ding-entity-button-see-online': 'see-online',
      '.ding-entity-button-other-formats': 'other-formats'
    },

    attach: function (context) {
      // Check the context, since behaviors can be attached several times.
      if (context !== document) {
        return;
      }

      let identifiers = {};
      let identifier = null;
      for (let i in this.buttons) {
        identifiers[this.buttons[i]] = [];

        // For event button type fetch it's parent ting entity id.
        $(i, context).each((index, element) => {
          identifier = $(element)
            .parents('div[ting-object-id]')
            .attr('ting-object-id');

          if (identifiers[this.buttons[i]].indexOf(identifier) === -1) {
            identifiers[this.buttons[i]].push(identifier);
          }
        });
      }

      // Identifiers object is keyed with button types, therefore loop
      // the types and send ajax request for each.
      for (let i in identifiers) {
        if (identifiers[i].length === 0) {
          continue;
        }

        this.renderDingEntityButtons(identifiers[i], i);
      }
    },

    renderDingEntityButtons: function (identifiers, type) {
      let element_settings = {
        url: '/ting/ding_entity_buttons/nojs/' + type,
        submit: {
          'js': true,
          'identifiers[]': identifiers
        }
      };

      let ajax = new Drupal.ajax(null, document.body, element_settings);
      ajax.eventResponse(ajax, {});
    }
  };
}(jQuery));
