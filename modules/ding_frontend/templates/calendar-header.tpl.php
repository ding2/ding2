<?php
/**
 * @file
 * Default implementation of calendar header template file.
 *
 * Available variables:
 * - $date: Array with date elements day, month, weekday and year as indexes.
 * - $today: Bool that's TRUE if the event is happening today else FALSE.
 * - $timezone: The current timezone.
 * - $timestamp: The date as a Unix timestamp.
 */
?>
<div class="event-list-date-wrapper <?php print ($today ? 'today' : ''); ?>">
  <span class="event-list-day"><?php print $date['weekday'] ?></span>
  <div class="event-list-inner-wrapper">
    <span class="event-list-date"><?php print $date['day']; ?></span>
    <span class="event-list-month"><?php print $date['month']; ?></span>
  </div>
</div>
<span class="event-list-fulldate">
  <?php print format_date($timestamp, 'ding_event_lists_date', '', $timezone); ?>
</span>
