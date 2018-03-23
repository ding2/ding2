/**
 *  @file
 *  Attach Media WYSIWYG behaviors.
 */

(function ($) {
  "use strict";

  Drupal.media = Drupal.media || {};
  var InsertMediaDamsDocument = function (instance_id) {
    this.instanceId = instance_id;
    return this;
  };

  InsertMediaDamsDocument.prototype = {
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
      var html = jQuery(formatted_media.html).children('a');
      formatted_media.options.dams_type = 'document';
      var element = Drupal.media.filter.create_element(html, {
        fid: this.mediaFile.fid,
        view_mode: formatted_media.type,
        attributes: formatted_media.options,
        fields: formatted_media.options,
        dams_type: 'document'
      });

      var markup = '';
      var macro = Drupal.media.filter.create_macro(element);
      switch (formatted_media.type) {
        case 'ding_dams_download_link':
          markup = Drupal.media.filter.getWysiwygHTML(element);
          break;

        case 'ding_dams_download_icon':
          var doc_extension = element[0].text.split('.').pop();
          var doctype_icon = 'doc_txt.png';

          switch (doc_extension) {
            case 'doc':
            case 'docx':
              doctype_icon = 'doc_doc.png';
              break;

            case 'xls':
            case 'xlsx':
              doctype_icon = 'doc_xls.png';
              break;

            case 'ppt':
            case 'pptx':
              doctype_icon = 'doc_ppt.png';
              break;

            case 'pdf':
              doctype_icon = 'doc_pdf.png';
              break;

            default:
              doctype_icon = 'doc_txt.png';
          }

          var a = document.createElement('a');
          a.href = element[0].href;
          a.target = '_blank';
          a.className = element[0].className;
          a.setAttribute('data-file_info', element.attr('data-file_info'));

          var image = document.createElement('img');
          image.src = Drupal.settings.ding_dams.icon_path + doctype_icon;
          a.appendChild(image);
          markup = a.outerHTML;
          break;
      }
      Drupal.settings.tagmap[macro] = markup;
      // Insert placeholder markup into wysiwyg.
      Drupal.wysiwyg.instances[this.instanceId].insert(markup);
    }
  };

  Drupal.wysiwyg.plugins.dams_document = {

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
        var insert = new InsertMediaDamsDocument(instanceId);
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
      if (!content.match(/dams_type"\:"document/g)) {
        return content;
      }

      return Drupal.wysiwyg.plugins.media.attach(content, settings, instanceId);
    },

    /**
     * Detach function, called when a rich text editor detaches
     */
    detach: function (content, settings, instanceId) {
      if (!content.match(/dams_type"\:"document/g)) {
        return content;
      }

      return Drupal.wysiwyg.plugins.media.detach(content, settings, instanceId);
    }

  };
})(jQuery);
