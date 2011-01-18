  <div class="object-information clearfix">
    <?php print render($content); ?>
    <?php
    //we printed the first part up above so remove that
    unset($object->record['dcterms:abstract'][''][0]);
    ?>
    <div class="abstract"><?php print implode(' ; ', ting_format_abstract((array)$object->record['dcterms:abstract'][''])) ?></div>

    <?php print theme('item_list', array($object->type), t('Type'), 'span', array('class' => 'type')); ?>
    <?php if (!empty($object->record['dc:format'][''])) { ?>
      <?php print theme('item_list', $object->record['dc:format'][''], t('Format'), 'span', array('class' => 'format'));?>
    <?php } ?>
    <?php if (!empty($object->record['dcterms:isPartOf'][''])) { ?>
      <?php print theme('item_list', $object->record['dcterms:isPartOf'][''], t('Available in'), 'span', array('class' => 'is-part-of'));?>
    <?php } ?>


    <?php if (!empty($object->language)) { ?>
      <?php print theme('item_list', array($object->language), t('Language'), 'span', array('class' => 'language'));?>
    <?php } ?>
    <?php if (!empty($object->record['dc:language']['oss:spoken'])) { ?>
      <?php print theme('item_list', $object->record['dc:language']['oss:spoken'], t('Speech'), 'span', array('class' => 'language'));?>
    <?php } ?>
    <?php if (!empty($object->record['dc:language']['oss:subtitles'])) { ?>
      <?php print theme('item_list', $object->record['dc:language']['oss:subtitles'], t('Subtitles'), 'span', array('class' => 'language'));?>
    <?php } ?>

    <?php if (!empty($object->record['dc:subject']['oss:genre'])) { ?>
      <?php print theme('item_list', $object->record['dc:subject']['oss:genre'], t('Genre'), 'span', array('class' => 'subject'));?>
    <?php } ?>
    <?php if (!empty($object->subjects)) { ?>
      <?php print theme('item_list', $object->subjects, t('Subjects'), 'span', array('class' => 'subject'));?>
    <?php } ?>
    <?php if (!empty($object->record['dc:subject']['dkdcplus:DK5'])) { ?>
      <?php print theme('item_list', $object->record['dc:subject']['dkdcplus:DK5'], t('Classification'), 'span', array('class' => 'subject'));?>
    <?php } ?>
    <?php if (!empty($object->record['dcterms:spatial'][''])) { ?>
      <?php print theme('item_list', $object->record['dcterms:spatial'][''], NULL, 'span', array('class' => 'spatial')); ?>
    <?php } ?>

    <?php if (!empty($object->record['dc:contributor']['oss:dkind'])) { ?>
      <?php print theme('item_list', $object->record['dc:contributor']['oss:dkind'], t('Reader'), 'span', array('class' => 'contributor'));?>
    <?php } ?>
    <?php if (!empty($object->record['dc:contributor']['oss:act'])) { ?>
      <?php print theme('item_list', $object->record['dc:contributor']['oss:act'], t('Actor'), 'span', array('class' => 'contributor'));?>
    <?php } ?>
    <?php if (!empty($object->record['dc:contributor']['oss:mus'])) { ?>
      <?php print theme('item_list', $object->record['dc:contributor']['oss:mus'], t('Musician'), 'span', array('class' => 'contributor'));?>
    <?php } ?>

    <?php if (!empty($object->record['dcterms:hasPart']['oss:track'])) { ?>
      <?php print theme('item_list', $object->record['dcterms:hasPart']['oss:track'], t('Contains'), 'span', array('class' => 'contains'));?>
    <?php } ?>

    <?php if (!empty($object->record['dcterms:isReferencedBy'][''])) { ?>
      <?php print theme('item_list', $object->record['dcterms:isReferencedBy'][''], t('Referenced by'), 'span', array('class' => 'referenced-by'));?>
    <?php } ?>


    <?php if (!empty($object->record['dc:description'])) { ?>
      <?php foreach ($object->record['dc:description'] as $type => $dc_description) { ?>
        <?php print theme('item_list', $dc_description, t('Description'), 'span', array('class' => 'description'));?>
      <?php } ?>
    <?php } ?>

    <?php if (!empty($object->record['dc:source'][''])) { ?>
      <?php print theme('item_list', $object->record['dc:source'][''], t('Original title'), 'span', array('class' => 'titles'));?>
    <?php } ?>
    <?php if (!empty($object->record['dcterms:replaces'][''])) { ?>
      <?php print theme('item_list', $object->record['dcterms:replaces'][''], t('Previous title'), 'span', array('class' => 'titles'));?>
    <?php } ?>
    <?php if (!empty($object->record['dcterms:isReplacedBy'][''])) { ?>
      <?php print theme('item_list', $object->record['dcterms:isReplacedBy'][''], t('Later title'), 'span', array('class' => 'titles'));?>
    <?php } ?>

    <?php if (!empty($object->record['dc:identifier']['dkdcplus:ISBN'])) { ?>
      <?php print theme('item_list', $object->record['dc:identifier']['dkdcplus:ISBN'], t('ISBN no.'), 'span', array('class' => 'identifier'));?>
    <?php } ?>

    <?php
    if (!empty($object->record['dc:identifier']['dcterms:URI'])) {
      $uris = array();
      foreach ($object->record['dc:identifier']['dcterms:URI'] as $uri) {
        $uris[] = l($uri, $uri);
      }
      print theme('item_list', $uris, t('Host publication'), 'span', array('class' => 'identifier'));
    }
    ?>

    <?php if (!empty($object->record['dkdcplus:version'][''])) { ?>
      <?php print theme('item_list', $object->record['dkdcplus:version'][''], t('Version'), 'span', array('class' => 'version'));?>
    <?php } ?>

    <?php if (!empty($object->record['dcterms:extent'][''])) { ?>
      <?php print theme('item_list', $object->record['dcterms:extent'][''], t('Extent'), 'span', array('class' => 'version'));?>
    <?php } ?>
    <?php if (!empty($object->record['dc:publisher'][''])) { ?>
      <?php print theme('item_list', $object->record['dc:publisher'][''], t('Publisher'), 'span', array('class' => 'publisher'));?>
    <?php } ?>
    <?php if (!empty($object->record['dc:rights'][''])) { ?>
      <?php print theme('item_list', $object->record['dc:rights'][''], t('Rights'), 'span', array('class' => 'rights'));?>
    <?php } ?>
  </div>
