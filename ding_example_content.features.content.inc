<?php
/**
 * @file
 * ding_example_content.features.content.inc
 */

/**
 * Implements hook_content_defaults().
 */
function ding_example_content_content_defaults() {
$content = array();
$content['andeby'] = (object)array(
  'exported_path' => 'biblioteker/andeby',
  'title' => 'Andeby bibliotek',
  'status' => '1',
  'promote' => '0',
  'sticky' => '0',
  'type' => 'ding_library',
  'language' => 'und',
  'created' => '1318841965',
  'comment' => '0',
  'translate' => '0',
  'machine_name' => 'andeby',
  'body' => array(
    'und' => array(
      0 => array(
        'value' => '<p>&nbsp;</p><p style="background-image: initial; background-attachment: initial; background-origin: initial; background-clip: initial; background-color: transparent; border-top-width: 0px; border-right-width: 0px; border-bottom-width: 0px; border-left-width: 0px; border-style: initial; border-color: initial; margin-top: 0px; margin-right: 0px; margin-bottom: 24px; margin-left: 0px; padding-top: 0px; padding-right: 0px; padding-bottom: 0px; padding-left: 0px; vertical-align: baseline; background-position: initial initial; background-repeat: initial initial; ">Bacon ipsum dolor sit amet ad do dolor in venison. Salami sint pancetta tail sunt pork chop, jerky turkey aliqua corned beef pork officia in beef ham. Andouille tenderloin nisi laborum, aliqua ullamco magna anim dolor ham hock short loin. Sint ribeye filet mignon est esse. Officia pork chop irure, short ribs magna bacon short loin ut id tongue dolor shankle strip steak spare ribs beef ribs. Reprehenderit salami irure ribeye. Sed cow in tenderloin.</p><p style="background-image: initial; background-attachment: initial; background-origin: initial; background-clip: initial; background-color: transparent; border-top-width: 0px; border-right-width: 0px; border-bottom-width: 0px; border-left-width: 0px; border-style: initial; border-color: initial; margin-top: 0px; margin-right: 0px; margin-bottom: 24px; margin-left: 0px; padding-top: 0px; padding-right: 0px; padding-bottom: 0px; padding-left: 0px; vertical-align: baseline; background-position: initial initial; background-repeat: initial initial; ">Tenderloin occaecat bacon in labore. Bacon flank leberkäse, bresaola voluptate hamburger tongue filet mignon pork chop aute labore jowl. Prosciutto qui short ribs, consectetur kielbasa cupidatat sed nisi ea ground round pastrami. Tri-tip prosciutto excepteur fugiat ribeye leberkäse. Hamburger capicola minim spare ribs, in excepteur ullamco occaecat kielbasa enim turducken voluptate. Pork chop quis shankle, reprehenderit beef adipisicing nostrud. Labore spare ribs swine beef ribs, consequat magna sirloin tri-tip.</p><p style="background-image: initial; background-attachment: initial; background-origin: initial; background-clip: initial; background-color: transparent; border-top-width: 0px; border-right-width: 0px; border-bottom-width: 0px; border-left-width: 0px; border-style: initial; border-color: initial; margin-top: 0px; margin-right: 0px; margin-bottom: 24px; margin-left: 0px; padding-top: 0px; padding-right: 0px; padding-bottom: 0px; padding-left: 0px; vertical-align: baseline; background-position: initial initial; background-repeat: initial initial; ">Commodo laborum jerky labore sirloin cow. Commodo short ribs shank, minim eu culpa dolore adipisicing boudin tail pork. Fugiat shoulder shankle ribeye, turducken rump bacon strip steak. Turducken incididunt boudin salami sausage. Do duis boudin, velit salami bresaola nisi. Sausage jerky turducken, brisket fatback ball tip irure ut swine nisi non pig sunt magna. Aute commodo pork loin ut shank, dolore enim elit meatloaf jowl ut aliqua consequat swine jerky.</p><div>&nbsp;</div>',
        'summary' => '',
        'format' => 'ding_wysiwyg',
        'safe_value' => ' <p> </p><p style="background-image: initial; background-attachment: initial; background-origin: initial; background-clip: initial; background-color: transparent; border-top-width: 0px; border-right-width: 0px; border-bottom-width: 0px; border-left-width: 0px; border-style: initial; border-color: initial; margin-top: 0px; margin-right: 0px; margin-bottom: 24px; margin-left: 0px; padding-top: 0px; padding-right: 0px; padding-bottom: 0px; padding-left: 0px; vertical-align: baseline; background-position: initial initial; background-repeat: initial initial; ">Bacon ipsum dolor sit amet ad do dolor in venison. Salami sint pancetta tail sunt pork chop, jerky turkey aliqua corned beef pork officia in beef ham. Andouille tenderloin nisi laborum, aliqua ullamco magna anim dolor ham hock short loin. Sint ribeye filet mignon est esse. Officia pork chop irure, short ribs magna bacon short loin ut id tongue dolor shankle strip steak spare ribs beef ribs. Reprehenderit salami irure ribeye. Sed cow in tenderloin.</p><p style="background-image: initial; background-attachment: initial; background-origin: initial; background-clip: initial; background-color: transparent; border-top-width: 0px; border-right-width: 0px; border-bottom-width: 0px; border-left-width: 0px; border-style: initial; border-color: initial; margin-top: 0px; margin-right: 0px; margin-bottom: 24px; margin-left: 0px; padding-top: 0px; padding-right: 0px; padding-bottom: 0px; padding-left: 0px; vertical-align: baseline; background-position: initial initial; background-repeat: initial initial; ">Tenderloin occaecat bacon in labore. Bacon flank leberkäse, bresaola voluptate hamburger tongue filet mignon pork chop aute labore jowl. Prosciutto qui short ribs, consectetur kielbasa cupidatat sed nisi ea ground round pastrami. Tri-tip prosciutto excepteur fugiat ribeye leberkäse. Hamburger capicola minim spare ribs, in excepteur ullamco occaecat kielbasa enim turducken voluptate. Pork chop quis shankle, reprehenderit beef adipisicing nostrud. Labore spare ribs swine beef ribs, consequat magna sirloin tri-tip.</p><p style="background-image: initial; background-attachment: initial; background-origin: initial; background-clip: initial; background-color: transparent; border-top-width: 0px; border-right-width: 0px; border-bottom-width: 0px; border-left-width: 0px; border-style: initial; border-color: initial; margin-top: 0px; margin-right: 0px; margin-bottom: 24px; margin-left: 0px; padding-top: 0px; padding-right: 0px; padding-bottom: 0px; padding-left: 0px; vertical-align: baseline; background-position: initial initial; background-repeat: initial initial; ">Commodo laborum jerky labore sirloin cow. Commodo short ribs shank, minim eu culpa dolore adipisicing boudin tail pork. Fugiat shoulder shankle ribeye, turducken rump bacon strip steak. Turducken incididunt boudin salami sausage. Do duis boudin, velit salami bresaola nisi. Sausage jerky turducken, brisket fatback ball tip irure ut swine nisi non pig sunt magna. Aute commodo pork loin ut shank, dolore enim elit meatloaf jowl ut aliqua consequat swine jerky.</p><div> </div> ',
        'safe_summary' => '  ',
      ),
    ),
  ),
);
$content['event-hoejben'] = (object)array(
  'exported_path' => 'content/foredrag-med-h-højben',
  'title' => 'Foredrag med H. Højben',
  'status' => '1',
  'promote' => '1',
  'sticky' => '0',
  'type' => 'ding_event',
  'language' => 'en',
  'created' => '1318843092',
  'comment' => '0',
  'translate' => '0',
  'machine_name' => 'event-hoejben',
);
$content['gaaseroed'] = (object)array(
  'exported_path' => 'content/gåserød-bibliotek',
  'title' => 'Gåserød Bibliotek',
  'status' => '1',
  'promote' => '0',
  'sticky' => '0',
  'type' => 'ding_library',
  'language' => 'und',
  'created' => '1318842111',
  'comment' => '0',
  'translate' => '0',
  'machine_name' => 'gaaseroed',
  'body' => array(
    'und' => array(
      0 => array(
        'value' => '<p>&nbsp;</p><p style="background-image: initial; background-attachment: initial; background-origin: initial; background-clip: initial; background-color: transparent; border-top-width: 0px; border-right-width: 0px; border-bottom-width: 0px; border-left-width: 0px; border-style: initial; border-color: initial; margin-top: 0px; margin-right: 0px; margin-bottom: 24px; margin-left: 0px; padding-top: 0px; padding-right: 0px; padding-bottom: 0px; padding-left: 0px; vertical-align: baseline; background-position: initial initial; background-repeat: initial initial; ">Aute tongue pancetta sirloin. Aliquip esse bacon laborum, incididunt commodo pork turkey strip steak boudin ham nisi shank turducken meatloaf. Jerky pig shankle id frankfurter, ea boudin ut flank veniam. Brisket tail ex quis, duis sirloin dolor shank ham hock strip steak id. Venison anim enim id jerky, shank labore. Capicola dolore id, esse flank pork belly shoulder t-bone officia sirloin nulla non duis ex. Ut swine turducken, ullamco duis sirloin incididunt tenderloin shoulder ham hock capicola consectetur bacon kielbasa rump.</p><p style="background-image: initial; background-attachment: initial; background-origin: initial; background-clip: initial; background-color: transparent; border-top-width: 0px; border-right-width: 0px; border-bottom-width: 0px; border-left-width: 0px; border-style: initial; border-color: initial; margin-top: 0px; margin-right: 0px; margin-bottom: 24px; margin-left: 0px; padding-top: 0px; padding-right: 0px; padding-bottom: 0px; padding-left: 0px; vertical-align: baseline; background-position: initial initial; background-repeat: initial initial; ">Minim deserunt incididunt irure tongue anim chicken. Sint nostrud consectetur ham hock, flank tenderloin pancetta prosciutto dolor duis enim salami eu reprehenderit. Beef leberkäse swine, et proident ham hock short ribs sunt tempor ut brisket drumstick pork chop. Ball tip ullamco mollit, pastrami cillum ham hock pig chicken non brisket. Short ribs tenderloin prosciutto ut, bacon cupidatat magna in consectetur ham hock. Frankfurter in incididunt do jowl t-bone. Sed biltong excepteur, sunt tail anim corned beef.</p>',
        'summary' => '',
        'format' => 'ding_wysiwyg',
        'safe_value' => ' <p> </p><p style="background-image: initial; background-attachment: initial; background-origin: initial; background-clip: initial; background-color: transparent; border-top-width: 0px; border-right-width: 0px; border-bottom-width: 0px; border-left-width: 0px; border-style: initial; border-color: initial; margin-top: 0px; margin-right: 0px; margin-bottom: 24px; margin-left: 0px; padding-top: 0px; padding-right: 0px; padding-bottom: 0px; padding-left: 0px; vertical-align: baseline; background-position: initial initial; background-repeat: initial initial; ">Aute tongue pancetta sirloin. Aliquip esse bacon laborum, incididunt commodo pork turkey strip steak boudin ham nisi shank turducken meatloaf. Jerky pig shankle id frankfurter, ea boudin ut flank veniam. Brisket tail ex quis, duis sirloin dolor shank ham hock strip steak id. Venison anim enim id jerky, shank labore. Capicola dolore id, esse flank pork belly shoulder t-bone officia sirloin nulla non duis ex. Ut swine turducken, ullamco duis sirloin incididunt tenderloin shoulder ham hock capicola consectetur bacon kielbasa rump.</p><p style="background-image: initial; background-attachment: initial; background-origin: initial; background-clip: initial; background-color: transparent; border-top-width: 0px; border-right-width: 0px; border-bottom-width: 0px; border-left-width: 0px; border-style: initial; border-color: initial; margin-top: 0px; margin-right: 0px; margin-bottom: 24px; margin-left: 0px; padding-top: 0px; padding-right: 0px; padding-bottom: 0px; padding-left: 0px; vertical-align: baseline; background-position: initial initial; background-repeat: initial initial; ">Minim deserunt incididunt irure tongue anim chicken. Sint nostrud consectetur ham hock, flank tenderloin pancetta prosciutto dolor duis enim salami eu reprehenderit. Beef leberkäse swine, et proident ham hock short ribs sunt tempor ut brisket drumstick pork chop. Ball tip ullamco mollit, pastrami cillum ham hock pig chicken non brisket. Short ribs tenderloin prosciutto ut, bacon cupidatat magna in consectetur ham hock. Frankfurter in incididunt do jowl t-bone. Sed biltong excepteur, sunt tail anim corned beef.</p> ',
        'safe_summary' => '  ',
      ),
    ),
  ),
);
$content['news-andeby-udvider'] = (object)array(
  'exported_path' => 'content/andeby-bibliotek-udvider',
  'title' => 'Andeby bibliotek udvider',
  'status' => '1',
  'promote' => '1',
  'sticky' => '0',
  'type' => 'ding_news',
  'language' => 'en',
  'created' => '1318843212',
  'comment' => '0',
  'translate' => '0',
  'machine_name' => 'news-andeby-udvider',
);
$content['oevre-gasefjeld'] = (object)array(
  'exported_path' => 'bibliotek/oevre-gasefjeld',
  'title' => 'Øvre Gasefjeld bibliotek',
  'status' => '1',
  'promote' => '0',
  'sticky' => '0',
  'type' => 'ding_library',
  'language' => 'und',
  'created' => '1318842248',
  'comment' => '0',
  'translate' => '0',
  'machine_name' => 'oevre-gasefjeld',
  'body' => array(
    'und' => array(
      0 => array(
        'value' => '<p>Sausage ribeye shoulder, biltong in pig short loin leberkäse. Ham velit consequat short loin, leberkäse rump do cupidatat. Meatball salami ribeye, in tongue ball tip capicola adipisicing sint pastrami jowl aliqua sausage fatback consequat. Esse cow chicken, excepteur brisket occaecat voluptate aliquip duis ham hock sausage turducken consectetur. Sed pork belly irure, exercitation jowl velit occaecat pork loin chicken in. Ut ground round exercitation, capicola venison bacon shoulder cillum deserunt in anim eu. Proident exercitation spare ribs, chicken strip steak pastrami salami dolor shoulder chuck.</p>',
        'summary' => '',
        'format' => 'ding_wysiwyg',
        'safe_value' => ' <p>Sausage ribeye shoulder, biltong in pig short loin leberkäse. Ham velit consequat short loin, leberkäse rump do cupidatat. Meatball salami ribeye, in tongue ball tip capicola adipisicing sint pastrami jowl aliqua sausage fatback consequat. Esse cow chicken, excepteur brisket occaecat voluptate aliquip duis ham hock sausage turducken consectetur. Sed pork belly irure, exercitation jowl velit occaecat pork loin chicken in. Ut ground round exercitation, capicola venison bacon shoulder cillum deserunt in anim eu. Proident exercitation spare ribs, chicken strip steak pastrami salami dolor shoulder chuck.</p> ',
        'safe_summary' => '  ',
      ),
    ),
  ),
);
return $content;
}
