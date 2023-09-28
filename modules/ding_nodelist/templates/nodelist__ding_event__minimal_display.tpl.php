<?php

/**
 * @file
 * Minimal display event display template.
 */
?>
<table<?php print $attributes; ?>>
  <tr class="minimal-item <?php print $class; ?>">
    <td class="minimal-title"><?php print l($item->title, 'node/' . $item->nid); ?></td>
    <td class="minimal-date"><?php print format_date($item->timestamp, 'custom', 'd/m', $item->timezone); ?></td>
  </tr>
</table>
