<?php
/**
 * @file
 * Views related items definition.
 */

/**
 * Class DingDashboardEditorialReject.
 */
class DingDashboardEditorialReject extends views_handler_field_node_link {

  /**
   * Renders the link.
   *
   * @param object $node
   *   Node object.
   *
   * @return string
   *   Returns action text.
   */
  public function renderLink($node, $values) {
    global $user;

    if (!ding_dashboard_access_callback($node, EDITORIAL_ACTION_REJECT) || !isset($node->field_editorial_status[LANGUAGE_NONE][0]['value'])) {
      return FALSE;
    }

    // @todo
    // Correct action path.
    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "node/$node->nid/editorial/reject";
    $this->options['alter']['query'] = drupal_get_destination();

    $status = $node->field_editorial_status[LANGUAGE_NONE][0]['value'];
    $actions = ding_dashboard_workflow($status);
    $text = '';
    if (in_array(EDITORIAL_ACTION_REJECT, $actions)) {
      $text = !empty($this->options['text']) ? $this->options['text'] : t('reject');
    }

    return $text;
  }

}
