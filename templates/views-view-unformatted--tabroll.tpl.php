<?php
// $Id$

// We need jQuery UI tabs for this.
jquery_ui_add('ui.tabs');
?>
 <div id="featured">
  <ul class="ui-tabs-nav">
    <?php
      for ($i=0; $i < 5 ; $i++) { 
        if($i == 0){
          print '<li class="ui-tabs-nav-item  ui-tabs-selected"><a href="#fragment-'.$i.' ">' .$view->result[$i]->node_title .'</a></li>';
        }else{
          print '<li class="ui-tabs-nav-item count-'.$i.'"><a href="#fragment-'.$i.' ">' .$view->result[$i]->node_title .'</a></li>';
        }
      }
    ?>
  </ul>

  <?php foreach ($rows as $id => $row): ?>
    <div id="fragment-<?php print $id ?>" class="ui-tabs-panel <?php if($id >= "1"){print "ui-tabs-hide"; }  ?>">
      <?php print $row; ?>
    </div>
  <?php endforeach; ?>

</div>

