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
    if (empty($values->field_field_place2book)) {
      return;
    }

    $p2b_field = $values->field_field_place2book[0]['raw'];
    $event_id = $p2b_field['event_id'];
    $event_maker_id = $p2b_field['event_maker_id'];

    if (empty($event_id) || empty($event_maker_id)) {
      return;
    }

    $p2b = ding_place2book_instance();
    $event = $p2b->getEvent($event_maker_id, $event_id);
    $meta_data = $event->meta_data;
    $state = $event->state;
    $available_tickets = $meta_data->available_tickets;

    // Try to derive a status for the ticket link in frontend by looking at the
    // p2b event's state, ticket types and sale periods.
    // See: http://developer.place2book.com/v1/events/
    $ticket_link_status = '';
    if (in_array($state, ['held', 'completed'])) {
      $ticket_link_status = 'event-over';
    }
    elseif (!$event->active) {
      $ticket_link_status = 'closed';
    }
    elseif ($state === 'published') {
      // If event is published we first check to see if there's any available
      // tickets at all. If not the event is sold out and we can avoid fetching
      // ticket types and sale periods. There might be a waiting-list so we
      // check for that first before setting sold out.
      if (empty($available_tickets)) {
        if (!empty($event->waiting_list)) {
          $ticket_link_status = 'waiting-list';
        }
        else {
          $ticket_link_status = 'sold-out';
        }
      }
      else {
        // Else we have no other options than to fetch the tickets and look
        // for open or upcoming sale periods.
        $sale_periods = [];
        foreach ($p2b->getPrices($event_maker_id, $event_id) as $price) {
          $sale_periods[] = [
            'begin' => strtotime($price->sale_begin_at),
            'end' => strtotime($price->sale_end_at),
          ];
        }

        // Some events, for example those migrated from the old API, will have
        // sales period on the event and not on the individual tickets.
        if (isset($event->sale_open_at) && isset($event->sale_close_at)) {
          $sale_periods[] = [
            'begin' => strtotime($event->sale_open_at),
            'end' => strtotime($event->sale_close_at),
          ];
        }

        $now = time();

        // Filter out periods which are already over.
        $sale_periods = array_filter($sale_periods, function ($p) use ($now) {
          return $p['end'] >= $now;
        });

        // Check if we still have any active sale periods. If such are - go on!
        if (!empty($sale_periods)) {
          // Find the closest sale period.
          $begin_values = array_column($sale_periods, 'begin');
          // Get the closest sale period. In case when event has upcoming sales,
          // its start value will be used in button label.
          $min_period_begin = min($begin_values);
          $min_period = array_filter($sale_periods, function ($sale_period) use ($min_period_begin) {
            return ($sale_period['begin']) == $min_period_begin;
          });
          $min_period = array_shift($min_period);

          // We have found an open sales period.
          $ticket_link_status = 'open';

          // Check for 'upcoming' sale.
          if ($now < $min_period['begin']) {
            // We haven't found any open sales period yet, but at least there's
            // an upcoming, so set that status for now.
            $ticket_link_status = 'upcoming';
          }
        }

        // If no upcoming or open sales period was found for the published event
        // we consider the sales status to be closed.
        if (empty($ticket_link_status)) {
          $ticket_link_status = 'closed';
        }

      }
    }

    return $ticket_link_status;
  }

}
