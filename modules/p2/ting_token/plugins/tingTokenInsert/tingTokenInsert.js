/**
 * @file
 * Insert ting object plugin
 */
 
(function ($) {
 
Drupal.wysiwyg.plugins['tingTokenInsert'] = {
 
  /**
   * Return whether the passed node belongs to this plugin (note that "node" in this context is a JQuery node, not a Drupal node).
   *
   * We identify code managed by this FOO plugin by giving it the HTML class
   * 'wysiwyg_plugin_example-foo'.
   */
  isNode: function(node) {
    return ($(node).is('.tingTokenInsert'));
  },
 
  /**
   * Invoke is called when the toolbar button is clicked.
   */
  invoke: function(data, settings, instanceId) {
    // Typically, an icon might be added to the WYSIWYG, which HTML gets added
    // to the plain-text version.
    if (data.format == 'html') {
      var content = this._getIds(data.content);
      if (content !== '') {
        settings.tingIds = content;
      } else {
        settings.tingIds = '';
      }
    }
    else {
      var content = '<!--tingInsert-->';
    }
    if (typeof content !== 'undefined') {
      Drupal.wysiwyg.plugins.tingTokenInsert.insert_form(data, settings, instanceId);
    }
  },
  /**
   * Insert form and dialog.
   */
  insert_form: function (data, settings, instanceId) {
    // Location, where to fetch the dialog.
    var aurl = Drupal.settings.basePath + 'ting_token/insert/ajax';
    if(settings.tingIds) {
      aurl += '/' + settings.tingIds.join();
    }
    var dialogdiv = $('<div id="ting-token-insert-dialog"></div>');
    dialogdiv.load(aurl, function(){
      var dialogClose = function () {
        try {
          dialogdiv.dialog('destroy').remove();
        } catch (e) {};
      };
      var btns = {};
      btns[Drupal.t('Cancel')] = function () {
        $(this).dialog("close");
      };
      var $this = this;
      dialogdiv.find('.form-save-ids').click(function(evt) {
        evt.preventDefault();
        var ids = [],
          $items = dialogdiv.find('#ting-token-fieldset-wrapper .form-text');
        $items.each(function() {
          ids.push($(this).val());
        });
        settings.tingIds = ids;
        var content = Drupal.wysiwyg.plugins['tingTokenInsert']._getPlaceholder(settings);
        Drupal.wysiwyg.instances[instanceId].insert(content);
        dialogdiv.dialog("close");
      });
      dialogdiv.dialog({
        modal: true,
        autoOpen: false,
        closeOnEscape: true,
        resizable: true,
        draggable: true,
        autoresize: true,
        namespace: 'jquery_ui_dialog_default_ns',
        dialogClass: 'jquery_ui_dialog-dialog',
        title: Drupal.t('Insert'),
        buttons: btns,
        width: '70%',
        close: dialogClose
      });
      dialogdiv.dialog("open");
      Drupal.attachBehaviors();
    });
  },
  /**
   * Replace all <!--tingInsert--> tags with the icon.
   */
  attach: function(content, settings, instanceId) {
    content = content.replace(/<!--tingInsert-->/g, this._getPlaceholder(settings));
    return content;
  },
 
  /**
   * Replace the icons with <!--wysiwyg_example_plugin--> tags in content upon detaching editor.
   */
  detach: function(content, settings, instanceId) {
    var $content = $('<div>' + content + '</div>');
    $.each($('.mainTingInsert', $content), function (i, elem) {
      elem.parentNode.removeChild(elem);
    });
    return $content.html();
  },
 
  /**
   * Helper function to return a HTML placeholder.
   */
  _getPlaceholder: function (settings) {
    if(settings.tingIds) {
      var viewMode = Drupal.settings.ting_token.viewMode
      return '[ting:' + viewMode + ':' + settings.tingIds.join() + ']';
    }
    return '';
  },
  
  /**
   * Helper function to return ids from a placeholder.
   */
  _getIds: function (content) {
    var ids = ''
      viewMode = Drupal.settings.ting_token.viewMode;
    if(content.indexOf('[ting:' + viewMode + ':') === 0 && content.indexOf(']') === (content.length - 1)) {
      content = content.replace('[ting:' + viewMode + ':', '');
      content = content.replace(']', '');
      ids = content.split(',');
    }
    return ids;
  }
};
 
})(jQuery);
