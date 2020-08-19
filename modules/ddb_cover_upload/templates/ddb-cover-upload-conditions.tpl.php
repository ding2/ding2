<?php

/**
 * @file
 * Template for showing upload conditions.
 *
 * Note: The danish text here have been decided by the steering committee to be
 *       hardcoded and should not be changeable in the CMS.
 *
 * Available variables:
 *   - $uri: to more information about service.
 */
?>
<div class="ddb-cover-upload__conditions">
  <h1><?php print t('Usage of cover upload service')?></h1>
  <p>Læs hvordan du skal forholde dig omkring upload af forsidebilleder til Cover servicen, herunder billedernes størrelser, opløsning og kvalitet, samt hvilke billeder der er klareret rettigheder til at uploade og bruge på bibliotekernes brugergrænseflader.</p>
  <p><?php print l('Læs mere om aftalerne og rettighederne til at benytte forsider.', $uri, array('external' => TRUE, 'attributes' => array('target' => '_blank'))) ?></p>
</div>
