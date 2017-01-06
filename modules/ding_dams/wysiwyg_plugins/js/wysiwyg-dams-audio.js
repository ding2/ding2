/**
 *  @file
 *  Attach Media WYSIWYG behaviors.
 */

(function ($) {
  "use strict";
  Drupal.media = Drupal.media || {};

  var InsertMediaDamsAudio = function (instance_id) {
    this.instanceId = instance_id;

    return this;
  };

  InsertMediaDamsAudio.prototype = {
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
        html = $(formatted_media.html).children('source');
      }

      formatted_media.options.dams_type = 'audio';
      var element = Drupal.media.filter.create_element(html, {
        fid: this.mediaFile.fid,
        view_mode: formatted_media.type,
        attributes: formatted_media.options,
        fields: formatted_media.options,
        dams_type: 'audio'
      });

      var markup = '';
      var macro = Drupal.media.filter.create_macro(element);
      switch (formatted_media.type) {
        case 'ding_dams_download_link':
          var a = document.createElement('a');
          a.href = element[0].src;
          a.target = '_blank';
          a.className = element[0].className;
          a.setAttribute('data-file_info', element.attr('data-file_info'));

          var name = element[0].src.split('/').pop().split('.')[0];
          a.innerHTML = name;
          markup = a.outerHTML;
          break;

        case 'ding_dams_inline':
          markup = Drupal.media.filter.getWysiwygHTML(element);
          break;

        case 'ding_dams_popup':
          var data = JSON.parse(decodeURI(element.attr('data-file_info')));
          var a = document.createElement('a');
          a.href = "ding-dams/nojs/popup/" + data.fid;
          a.target = '_blank';
          a.className = element[0].className + ' use-ajax';
          a.setAttribute('data-file_info', element.attr('data-file_info'));

          var image = document.createElement('img');
          image.src = Drupal.settings.ding_dams.icon_path + '/doc_mp3.png';
          a.appendChild(image);
          markup = a.outerHTML;
          break;

        case 'ding_dams_download_icon':
          var a = document.createElement('a');
          a.href = element[0].src;
          a.target = '_blank';
          a.className = element[0].className;
          a.setAttribute('data-file_info', element.attr('data-file_info'));

          var image = document.createElement('img');
          image.src = Drupal.settings.ding_dams.icon_path + '/doc_mp3.png';
          a.appendChild(image);
          markup = a.outerHTML;
          break;
      }
      Drupal.settings.tagmap[macro] = markup;
      // Insert placeholder markup into wysiwyg.
      Drupal.wysiwyg.instances[this.instanceId].insert(markup);
    }
  };

  Drupal.wysiwyg.plugins.dams_audio = {

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
        var insert = new InsertMediaDamsAudio(instanceId);
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
      if (!content.match(/dams_type"\:"audio/g)) {
        return content;
      }

      return Drupal.wysiwyg.plugins.media.attach(content, settings, instanceId);
    },

    /**
     * Detach function, called when a rich text editor detaches
     */
    detach: function (content, settings, instanceId) {
      if (!content.match(/dams_type"\:"audio/g)) {
        return content;
      }

      return Drupal.wysiwyg.plugins.media.detach(content, settings, instanceId);
    }
  };
})(jQuery);
