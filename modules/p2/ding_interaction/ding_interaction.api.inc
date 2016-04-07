<?php

/**
 * @file
 * This file contains the api functions which developers can use to
 * influence the interaction panes.
 *
 * The hooks can be used to define and provide new interaction content panes,
 * and to alter or implement new output.
 */

/**
 * Hook which defines ding interaction content.
 *
 * @return array
 *   The returned array should contain the following values.
 *   - "title": The title to display when the interaction pane is display.
 *   - "active": Status of this interaction content.
 *     TRUE if this pane should be displayed, FALSE if not.
 */
function hook_ding_interaction_info() {
  return array(
    'title' => t('Title to display'),
    'active' => TRUE,
  );
}

/**
 * Hook which provides ding interaction content.
 *
 * @return string
 *   Return content which is ready to be displayed by the interaction pane.
 */
function hook_ding_interaction_view() {
  return $output;
}
