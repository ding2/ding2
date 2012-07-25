<?php //dsm($fields); 

// Prepare variable.
$libString = $fields['field_library_ref_nid']->content;
$libString = strtolower( str_replace(" Bibliotek", "", $libString) );
// Translating danish characters, avoiding character set issues when styling with CSS afterwards
$trans = array("æ" => "ae", "Æ" => "AE", "ø" => "o", "Ø" => "O", "å" => "aa", "Å" => "AA");
$libString = strtr($libString, $trans);

?>

<div class="image <?php print $libString; ?>">
  <?php print $fields['field_image_fid']->content; ?>
</div>


<div class="info <?php print $libString; ?>">
  <h3><?php print l($fields['title']->content, $fields['field_link_url']->raw); ?></h3>
  <p><?php print $fields['field_teaser_value']->content; ?></p>
</div>



