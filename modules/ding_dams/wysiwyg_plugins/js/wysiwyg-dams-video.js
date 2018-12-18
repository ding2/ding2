/**
 *  @file
 *  Attach Media WYSIWYG behaviors.
 */

(function ($) {
  "use strict";

  Drupal.media = Drupal.media || {};

  var InsertMediaDamsVideo = function (instance_id) {
    this.instanceId = instance_id;
    return this;
  };

  InsertMediaDamsVideo.prototype = {
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
      var html = formatted_media.html;
      if (formatted_media.type !== 'ding_dams_inline') {
        html = $(formatted_media.html).children('a');
      }

      formatted_media.options.dams_type = 'video';
      var element = Drupal.media.filter.create_element(html, {
        fid: this.mediaFile.fid,
        view_mode: formatted_media.type,
        attributes: formatted_media.options,
        fields: formatted_media.options
      });

      var markup = '';
      var macro = Drupal.media.filter.create_macro(element);
      var data = Drupal.media.filter.extract_file_info(element);

      switch (formatted_media.type) {
        case 'ding_dams_download_link':
          var name = $(formatted_media.html).children('a').html();

          var a = document.createElement('a');
          a.href = element[0].href;
          a.target = '_blank';
          a.className = element[0].className;
          a.innerHTML = name;
          markup = a.outerHTML;
          break;

        case 'ding_dams_inline':
          markup = Drupal.media.filter.getWysiwygHTML(element);

          // Open link in new tab.
          $(markup).find('a').attr('target', '_blank');
          break;

        case 'ding_dams_popup':
          var a = document.createElement('a');
          a.href = "/ding-dams/nojs/popup/" + data.fid;
          a.target = '_blank';
          a.className = element[0].className + ' ctools-use-modal ctools-modal-dams-modal';

          var image = document.createElement('img');
          image.src = Drupal.settings.ding_dams.icon_path + 'doc_flv.png';
          a.appendChild(image);

          markup = a.outerHTML;
          break;

        case 'ding_dams_download_icon':
          var a = document.createElement('a');
          a.href = element[0].href;
          a.target = '_blank';
          a.className = element[0].className;

          var image = document.createElement('img');
          image.src = Drupal.settings.ding_dams.icon_path + 'doc_flv.png';
          a.appendChild(image);

          markup = a.outerHTML;
          break;
      }

      Drupal.settings.tagmap[macro] = markup;

      // This hack is used because video ads empty tags, which makes webkit
      // browsers unable to place an editable selection inside.
      // @see https://bugs.webkit.org/show_bug.cgi?id=15256
      markup += '&zwnj;';

      // Insert placeholder markup into wysiwyg.
      Drupal.wysiwyg.instances[this.instanceId].insert(markup);
    }
  };

  Drupal.wysiwyg.plugins.dams_video = {

    /**
     * Determine whether a DOM element belongs to this plugin.
     *
     * @param node
     *   A DOM element
     */
    isNode: function (node) {
      return Drupal.wysiwyg.plugins.media.isNode(node);
    },

    /**
     * Execute the button.
     */
    invoke: function (data, settings, instanceId) {
      if (data.format === 'html') {
        var insert = new InsertMediaDamsVideo(instanceId);
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
      if (!content.match(/dams_type"\:"video/g)) {
        return content;
      }

      return Drupal.wysiwyg.plugins.media.attach(content, settings, instanceId);
    },

    /**
     * Detach function, called when a rich text editor detaches
     */
    detach: function (content, settings, instanceId) {
      if (!content.match(/dams_type"\:"video/g)) {
        return content;
      }

      return Drupal.wysiwyg.plugins.media.detach(content, settings, instanceId);
    }
  };

})(jQuery);
