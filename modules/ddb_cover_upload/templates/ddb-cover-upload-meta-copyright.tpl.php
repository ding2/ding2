<?php

/**
 * @file
 * Template for showing meta copyright information.
 *
 * Note: The danish text here have been decided by the steering committee to be
 *       hardcoded and should not be changeable in the CMS.
 *
 * Available variables:
 *   - $uri: to more information about service.
 */
?>
<div>
  <h3><?php print t('Copyright information');?></h3>
  <p>FDDF har på vegne af bibliotekerne forhandlet med rettighedshaverne om klarering af rettigheder for mange forskellige materialer herunder bøger, musik, film og e-ressourcer, men der kan også være materialer bibliotekerne endnu ikke må benytte.</p>
  <p>Det er udelukkende tilladt at uploade billeder, som FDDF har klareret rettighederne til.</p>
  <p><?php print l('Læs mere om aftalerne og rettighederne til at benytte forsider', $uri, array('external' => TRUE, 'attributes' => array('target' => '_blank'))) ?></p>
</div>
