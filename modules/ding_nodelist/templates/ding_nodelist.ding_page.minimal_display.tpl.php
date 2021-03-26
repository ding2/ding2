<?php

/**
 * @file
 * Minimal display page display template.
 */
?>
<table>
  <tr class="minimal-item <?php print $class; ?>">
    <td class="minimal-title"><?php print l($item->title, 'node/' . $item->nid); ?></td>
    <td class="minimal-date">
      <?php print format_date($item->created, 'custom', 'd/m'); ?>
    </td>
  </tr>
</table>
