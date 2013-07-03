<div class="date-display-header <?php if ($today) {print('today');} ?>">
  <div class="ding-event-date">
    <p class="ding-event-weekday"><?php print($weekday); ?></p>
    <p class="ding-event-day"><?php print($day); ?></p>
    <p class="ding-event-month"><?php print($month); ?></p>
  </div>
  <span class="ding-event-fulldate"><?php print($weekday); ?> <?php print($day); ?>. <?php print($month); ?> <?php print($year); ?></span>
</div>
