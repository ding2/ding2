<?php

/**
 * @file
 * Expose event's ticket sales status.
 */

/**
 * Class ding_app_content_rss_handler_sales_status.
 */
class ding_app_content_rss_handler_sales_status extends views_handler_field {
  /**
   * {@inheritdoc}
   */
  function query() {}

  /**
   * {@inheritdoc}
   */
  function render($values) {
    if (!module_exists('ding_place2book')) {
      return;
    }

    if (empty($values->field_field_place2book)) {
      return;
    }

    $p2b_field = $values->field_field_place2book[0]['raw'];
    $event_id = $p2b_field['event_id'];
    $event_maker_id = $p2b_field['event_maker_id'];

    if (empty($event_id) || empty($event_maker_id)) {
      return;
    }

    /** @var \P2b\P2b $p2b */
    $p2b = ding_place2book_instance();

    return ding_place2book_ticket_status($event_maker_id, $event_id, $p2b);
  }

}
