
/**
 *  @file
 *  Attach Media WYSIWYG behaviors.
 */

(function ($) {

  Drupal.media = Drupal.media || {};

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
      if (data.format == 'html') {
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
      return Drupal.wysiwyg.plugins.media.attach(content, settings, instanceId);
    },

    /**
     * Detach function, called when a rich text editor detaches
     */
    detach: function (content, settings, instanceId) {
      return Drupal.wysiwyg.plugins.media.detach(content, settings, instanceId);
    },
  };

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
      var element = Drupal.media.filter.create_element(html, {
        fid: this.mediaFile.fid,
        view_mode: formatted_media.type,
        attributes: formatted_media.options,
        fields: formatted_media.options
      });

      var markup = '';
      var macro = Drupal.media.filter.create_macro(element);
      Drupal.media.filter.ensure_tagmap();
      var i = 1;
      for (var key in Drupal.settings.tagmap) {
        i++;
      }
      switch (formatted_media.type) {
        case 'ding_dams_download_link':
          markup = Drupal.media.filter.getWysiwygHTML(element);
          break;
        case 'ding_dams_download_icon':
          var doc_extension = element[0].text.split('.').pop();
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
          }

          markup = '<a href="' + element[0].src + '" ' +
              'target="_blank" ' +
              'data-file_info="' + element.attr('data-file_info') +  '" ' +
              'class="' + element[0].className + '">' +
              '<img src="' + Drupal.settings.ding_dams.icon_path + doctype_icon + '"/>' +
              '</a>';
          break;
      }
      Drupal.settings.tagmap[macro] = markup;
      // Insert placeholder markup into wysiwyg.
      Drupal.wysiwyg.instances[this.instanceId].insert(markup);
    }
  };

})(jQuery);
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
// /**
//  *  @file
//  *  Attach Media WYSIWYG behaviors.
//  */
//
// (function ($) {
//
// Drupal.media = Drupal.media || {};
//
// // Define the behavior.
// Drupal.wysiwyg.plugins.dams_document = {
//
//
//   /**
//    * Respond to the mediaBrowser's onSelect event.
//    * @TODO: Debug calls from this are never called. What's its function?
//    */
//   mediaBrowserOnSelect: function (mediaFiles, instanceId) {
//     var mediaFile = mediaFiles[0];
//     var options = {};
//
//     Drupal.media.popups.mediaStyleSelector(mediaFile, function (formattedMedia) {
//       var formattedMediaType = '';
//       var formattedMediaHtml = '';
//
//       var doctype_icon = 'doc_txt.png';
//       var doc_extension = mediaFile.filename.split('.').pop();
//       switch (doc_extension) {
//         case 'doc':
//         case 'docx':
//           doctype_icon = 'doc_doc.png';
//           break;
//         case 'xls':
//         case 'xlsx':
//           doctype_icon = 'doc_xls.png';
//           break;
//         case 'ppt':
//         case 'pptx':
//           doctype_icon = 'doc_ppt.png';
//           break;
//         case 'pdf':
//           doctype_icon = 'doc_pdf.png';
//           break;
//       }
//       options['icon_file'] = doctype_icon;
//
//       if (formattedMedia.type === 'ding_dams_download_icon') {
//         formattedMediaType = 'ding_dams_download_icon';
//         formattedMediaHtml = '<img src="' + Drupal.settings.ding_dams.icon_path + doctype_icon + '"/>';
//       }
//       else {
//         formattedMediaType = formattedMedia.type;
//         formattedMediaHtml = formattedMedia.html;
//       }
//
//       Drupal.wysiwyg.plugins.dams_document.insertMediaFile(mediaFile, formattedMediaType, formattedMediaHtml, formattedMedia.options, Drupal.wysiwyg.instances[instanceId]);
//     }, options);
//
//     return;
//   },
//
//   insertMediaFile: function (mediaFile, viewMode, formattedMedia, options, wysiwygInstance) {
//     this.initializeTagMap();
//     // @TODO: the folks @ ckeditor have told us that there is no way
//     // to reliably add wrapper divs via normal HTML.
//     // There is some method of adding a "fake element"
//     // But until then, we're just going to embed to img.
//     // This is pretty hacked for now.
//     //
//     var imgElement = $(this.stripDivs(formattedMedia));
//
//     if (viewMode === 'ding_dams_download_link') {
//       imgElement = $('<a href="' + mediaFile.url + '" alt="" title="">' + mediaFile.filename + '</a>');
//     }
//
//     this.addImageAttributes(imgElement, mediaFile.fid, viewMode, options);
//
//     var toInsert = this.outerHTML(imgElement);
//     // Create an inline tag
//     var inlineTag = Drupal.wysiwyg.plugins.dams_document.createTag(imgElement);
//     // Add it to the tag map in case the user switches input formats
//     Drupal.settings.tagmap[inlineTag] = toInsert;
//     wysiwygInstance.insert(toInsert);
//   },
//
//
//   /**
//    * Attach function, called when a rich text editor loads.
//    * This finds all [[tags]] and replaces them with the html
//    * that needs to show in the editor.
//    *
//    */
//   attach: function (content, settings, instanceId) {
//     var matches = content.match(/\[\[.*?\]\]/g);
//     this.initializeTagMap();
//     var tagmap = Drupal.settings.tagmap;
//     if (matches) {
//       var inlineTag = "";
//       for (i = 0; i < matches.length; i++) {
//         inlineTag = matches[i];
//         if (tagmap[inlineTag]) {
//           var _tag = inlineTag;
//           _tag = _tag.replace('[[','');
//           _tag = _tag.replace(']]','');
//           try {
//             mediaObj = JSON.parse(_tag);
//           }
//           catch(err) {
//             mediaObj = null;
//           }
//           if (mediaObj.view_mode == 'ding_dams_download_icon') {
//             var imgElement = $('<img src="' + mediaObj.attributes.icon_file + '"/>');
//             var extra_attributes = {};
//             extra_attributes['icon_file'] = mediaObj.attributes.icon_file;
//             this.addImageAttributes(imgElement, mediaObj.fid, mediaObj.view_mode, extra_attributes);
//             var toInsert = this.outerHTML(imgElement);
//             content = content.replace(inlineTag, toInsert);
//           }
//         }
//         else {
//           debug.debug("Could not find content for " + inlineTag);
//         }
//       }
//     }
//     return content;
//   },
//
//   /**
//    * Detach function, called when a rich text editor detaches
//    */
//   detach: function (content, settings, instanceId) {
//     // Replace all Media placeholder images with the appropriate inline json
//     // string. Using a regular expression instead of jQuery manipulation to
//     // prevent <script> tags from being displaced.
//     // @see http://drupal.org/node/1280758.
//     if (matches = content.match(/<img[^>]+class=([\'"])ding-dams-doc[^>]*>/gi)) {
//       for (var i = 0; i < matches.length; i++) {
//         var imageTag = matches[i];
//         var inlineTag = Drupal.wysiwyg.plugins.dams_document.createTag($(imageTag));
//         Drupal.settings.tagmap[inlineTag] = imageTag;
//         content = content.replace(imageTag, inlineTag);
//       }
//     }
//     return content;
//   },
//
//
// })(jQuery);
