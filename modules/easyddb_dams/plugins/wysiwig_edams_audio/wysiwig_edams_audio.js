/**
 *  @file
 *  Attach Media WYSIWYG behaviors.
 */

(function ($) {

Drupal.wysiwig_edams_audio = Drupal.wysiwig_edams_audio || {};

    /**
 * Register the plugin with WYSIWYG.
 */
Drupal.wysiwig_edams_audio = {

  /**
   * Determine whether a DOM element belongs to this plugin.
   *
   * @param node
   *   A DOM element
   */
  isNode: function(node) {
    return $(node).is('html.media-element');
  },

/**
 * Gets the HTML content of an element.
 *
 * @param element (jQuery object)
 *
 * @deprecated
 */
function outerHTML (element) {
  return Drupal.media.filter.outerHTML(element);
}
})(jQuery);
