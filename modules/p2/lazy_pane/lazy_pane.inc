<?php

/**
 * @file
 * Miscellaneous functions for Lazy Pane.
 */

/**
 * Menu callback to load a lazy-pane through ajax.
 *
 * This callback is responsible for validating access, loading pane configuration
 * from cache, rendering the panes and handling it back to the user.
 *
 * @see lazy_pane_lazy_cache_get()
 */
function lazy_pane_ajax() {

  if (!isset($_REQUEST['lazy_pane_ids']) || !is_array($_REQUEST['lazy_pane_ids'])) {
    return;
  }

  if (!isset($_REQUEST['lazy_pane_current_path']) || !is_string($_REQUEST['lazy_pane_current_path'])) {
    return;
  }

  // Check if the host path exists and the user has access to it. Otherwise bail out.
  $path = $_REQUEST['lazy_pane_current_path'];

  if (!drupal_valid_path($path)) {
    return;
  }

  // Override the active path so that panes behave as if they are in the host path.
  menu_set_active_item($path);

  // Flag the current request as being a lazy request.
  lazy_pane_is_lazy_request(TRUE);

  // Store the request uri for later use.
  lazy_pane_get_request_path($path);

  // Some panes might use GET parameters present on the host page, such as a pager.
  // Given that Drupal AJAX Framework uses POST we merge the page params into the
  // super global $_GET so that modules such as views can use them for filters.
  $_GET += (!isset($_REQUEST['lazy_pane_get']) || !is_array($_REQUEST['lazy_pane_get'])) ? array() : $_REQUEST['lazy_pane_get'];

  // Empty the POST data before rendering the panes as it prevents displays
  // from using cache. See panels_set_cached_content() $_POST bailout.
  $stored_post = $_POST;
  $_POST = array();

  // Filter out non-lazy pane cache ids and load them from the database.
  $cache_ids = array();
  foreach ($_REQUEST['lazy_pane_ids'] as $id) {
    if (drupal_substr($id, 0, 9) == 'lazy_pane') {
      $cache_ids[] = $id;
    }
  }

  $caches = cache_get_multiple($cache_ids);

  // Finally, render the lazy panes.
  ctools_include('content');
  ctools_include('plugins', 'panels');

  $commands = array();
  foreach ($caches as $cache) {
    $pane = $cache->data['pane'];
    $display = $cache->data['display'];

    $output = lazy_pane_render($pane, $display);

    // $commands[] = ajax_command_replace('[data-lazy-pane-id="' . $cache->cid . '"]', $output);
    // $commands[] = ajax_command_invoke('[data-lazy-pane-id="' . $cache->cid . '"]', 'lazyPaneAjax', array($output));
    $commands[] = array(
      'command' => 'replacer',
      'selector' => '[data-lazy-pane-id="' . $cache->cid . '"]',
      'data' => $output,
    );
  }

  // Restore the POST data before handling it for delivery. The function responsible
  // for the delivery - ajax_render() - requires the POST data to be present or
  // it won't inject the rendered panes JS/CSS dependencies in the host page.
  $_POST = $stored_post;

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Render a pane or a display using its designated style.
 *
 * @param stdClass $pane
 *  A panels pane object.
 * @param panels_display $display
 *  The panels display object to be rendered.
 *
 * @return string
 *  Rendered panel pane markup.
 */
function lazy_pane_render($pane, $display) {
  $output = '';

  // If it's a display, render it now.
  if (empty($pane) && !empty($display)) {
    $display->cache = array();
    $output = $display->render();
  }
  // Otherwise, it's a pane.
  elseif (!empty($pane) && !empty($display)) {
    // Get type of renderer.
    $renderer_handler = $display->renderer_handler->plugin['renderer'];
    // Instantiate renderer.
    $renderer = new $renderer_handler();
    // Set the renderer display settings to those passed into this function.
    $renderer->display = $display;
    // The placeholder was cached for this display so we need to skip caching.
    $renderer->display->skip_cache = TRUE;
    $output = $renderer->render_pane($pane);
  }

  return $output;
}
