<?php

/**
 * @file
 * Theme implementation for displaying place2book ticket info
 * (support for ding_place2book module)
 *
 * Variables:
 * $place2book_id: the ID for the event at place2book.com  (if it exists for the ding event)
 * $url: the full URL to the event at place2book.com (if it exists for the ding event)
 * $type: the type of information to display. 4 kinds exists:
 * - event-over
 * - closed-admission
 * - no-tickets-left
 * - order-link.
 *
 * Only the 'order-link' type should be and action - the rest is to be
 * displayed as information to the user
 */

switch ($type) {
  case 'event-over':
    print '<div class="place2book-tickets-label">'. t('Tickets') . '</div><div class="place2book-tickets-info">' . t('The event has already taken place') . '</div>';
    break;

  case 'closed-admission':
    print '<div class="place2book-tickets-label">'. t('Tickets') . '</div><div class="place2book-tickets-info">' . t('Not open for ticket sale') . '</div>';
    break;

  case 'no-tickets-left':
    print '<div class="place2book-tickets-label">'. t('Tickets') . '</div><div class="place2book-tickets-info">' . t('Sold out') . '</div>';
    break;

  case 'order-link':
    print l(t('Book a ticket'), $url, array('attributes' => array('class' => array('ticket-available', 'button'))));
    break;

  case 'sale-not-started':
    print '<div class="place2book-tickets-label">'. t('Tickets') . '</div><div class="place2book-tickets-info">' . t('Ticket sale has not yet started for this event') . '</div>';
    break;

  default:
    print '-nothing-';
    break;
}
