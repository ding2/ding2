
/**
 *  @file
 *  Attach Media WYSIWYG behaviors.
 */

(function ($) {
  "use strict";

  Drupal.media = Drupal.media || {};

  var InsertMediaDamsImage = function (instance_id) {
    this.instanceId = instance_id;
    return this;
  };

  InsertMediaDamsImage.prototype = {
    /**
     * Prompt user to select a media item with the media browser.
     *
     * @param settings
     *    Settings object to pass on to the media browser.
     */
    prompt: function (settings) {
      Drupal.media.popups.mediaBrowser($.proxy(this, 'onSelect'), settings);
    },

    /**
     * On selection of a media item, display item's display configuration form.
     */
    onSelect: function (media_files) {
      this.mediaFile = media_files[0];
      Drupal.media.popups.mediaStyleSelector(this.mediaFile, $.proxy(this, 'insert'), {});
    },

    /**
     * When display config has been set, insert the placeholder markup into the
     * wysiwyg and generate its corresponding json macro pair to be added to the
     * tagmap.
     */
    insert: function (formatted_media) {
      formatted_media.options.dams_type = 'image';
      var element = Drupal.media.filter.create_element(formatted_media.html, {
        fid: this.mediaFile.fid,
        view_mode: formatted_media.type,
        attributes: formatted_media.options,
        fields: formatted_media.options,
        dams_type: 'image'
      });

      var markup = '';
      var macro = Drupal.media.filter.create_macro(element);
      if (formatted_media.type === 'ding_dams_download_link') {
        var data = JSON.parse(decodeURI(element.attr('data-file_info')));
        var name = '';
        if (data.fields['field_file_image_alt_text[und][0][value]'].length > 0) {
          name = data.fields['field_file_image_alt_text[und][0][value]'];
        }
        else {
          name = element[0].src.split('/').pop().split('.')[0];
        }
        var a = document.createElement('a');
        a.href = element[0].src;
        a.target = '_blank';
        a.title = element.attr('title');
        a.className = element[0].className;
        a.setAttribute('data-file_info', element.attr('data-file_info'));
        a.innerHTML = typeof element.attr('title') !== 'undefined' ? element.attr('title') : name;
        markup = a.outerHTML;
      }
      else {
        // Get the markup and register it for the macro / placeholder handling.
        markup = Drupal.media.filter.getWysiwygHTML(element);
      }

      Drupal.settings.tagmap[macro] = markup;
      // Insert placeholder markup into wysiwyg.
      Drupal.wysiwyg.instances[this.instanceId].insert(markup);
    }
  };

  Drupal.wysiwyg.plugins.dams_image = {

  /**
   * Determine whether a DOM element belongs to this plugin.
   *
   * @param node
   *   A DOM element
   */
  isNode: function(node) {
    return Drupal.wysiwyg.plugins.media.isNode(node);
  },

  /**
   * Execute the button.
   */
  invoke: function (data, settings, instanceId) {
    if (data.format === 'html') {
      var insert = new InsertMediaDamsImage(instanceId);
      if (this.isNode(data.node)) {
        // Change the view mode for already-inserted media.
        var media_file = Drupal.media.filter.extract_file_info($(data.node));
        insert.onSelect([media_file]);
      }
      else {
        // Insert new media.
        insert.prompt(settings.global);
      }
    }
  },

  /**
   * Attach function, called when a rich text editor loads.
   * This finds all [[tags]] and replaces them with the html
   * that needs to show in the editor.
   *
   */
  attach: function (content, settings, instanceId) {
    if (!content.match(/dams_type"\:"image/g)) {
      return content;
    }

    return Drupal.wysiwyg.plugins.media.attach(content, settings, instanceId);
  },

  /**
   * Detach function, called when a rich text editor detaches
   */
  detach: function (content, settings, instanceId) {
    if (!content.match(/dams_type"\:"image/g)) {
      return content;
    }

    return Drupal.wysiwyg.plugins.media.detach(content, settings, instanceId);
  }
};

})(jQuery);
