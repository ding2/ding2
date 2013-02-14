<div class="event-list-date-wrapper <?php if ($today) {print 'today';} ?>">
  <span class="event-list-day"><?php print $weekday; ?></span>
  <div class="event-list-inner-wrapper">
    <span class="event-list-date"><?php print $day; ?></span>
    <span class="event-list-month"><?php print $month; ?></span>
  </div>
</div>
<span class="ding-event-fulldate"><?php print($weekday); ?> <?php print($day); ?>. <?php print($month); ?> <?php print($year); ?></span>
