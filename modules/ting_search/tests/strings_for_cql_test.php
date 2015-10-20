<?php
function ting_search_test_valid_cql() {
  // @see http://platform.dandigbib.org/issues/1324
  return array(
    '(term.acquisitionDate=201528* OR dkcclterm.kk=bkm201528*
  OR term.acquisitionDate=201529* OR dkcclterm.kk=bkm201529*
  OR term.acquisitionDate=20153* OR dkcclterm.kk=bkm20153*)
  AND facet.date=2015 AND dkcclterm.dk=77.7 AND dkcclterm.ma=th'
    =>
      '(term.acquisitionDate=201528* OR dkcclterm.kk=bkm201528*
  OR term.acquisitionDate=201529* OR dkcclterm.kk=bkm201529*
  OR term.acquisitionDate=20153* OR dkcclterm.kk=bkm20153*)
  AND facet.date=2015 AND dkcclterm.dk=77.7 AND dkcclterm.ma=th',

    '(term.acquisitionDate=20153* OR dkcclterm.kk=bkm20153*)
  AND facet.date=2015 AND dkcclterm.dk=sk AND (dkcclterm.ma=ro
  OR dkcclterm.ma=no) AND dkcclterm.ma=xx NOT (dkcclterm.em=krimi
  OR dkcclterm.ma=ss OR facet.category=børnematerialer)'
    =>
      '(term.acquisitionDate=20153* OR dkcclterm.kk=bkm20153*)
  AND facet.date=2015 AND dkcclterm.dk=sk AND (dkcclterm.ma=ro
  OR dkcclterm.ma=no) AND dkcclterm.ma=xx NOT (dkcclterm.em=krimi
  OR dkcclterm.ma=ss OR facet.category=børnematerialer)',

    '(term.acquisitionDate=20153* OR dkcclterm.kk=bkm20153*)
    AND facet.date=2015 AND dkcclterm.ma=xx NOT (dkcclterm.em=krimi
    OR dkcclterm.ma=ss OR facet.category=børnematerialer
    OR dkcclterm.dk=sk OR dkcclterm.ma=ro OR dkcclterm.ma=no OR facet.dk5=79.41)'
    =>
      '(term.acquisitionDate=20153* OR dkcclterm.kk=bkm20153*)
    AND facet.date=2015 AND dkcclterm.ma=xx NOT (dkcclterm.em=krimi
    OR dkcclterm.ma=ss OR facet.category=børnematerialer
    OR dkcclterm.dk=sk OR dkcclterm.ma=ro OR dkcclterm.ma=no OR facet.dk5=79.41)',

    '(term.subject=fantasy OR term.subject="science fiction")
    and (facet.type=dvd OR facet.type=blu*)'
    =>
      '(term.subject=fantasy OR term.subject="science fiction")
    and (facet.type=dvd OR facet.type=blu*)',

    'facet.category="voksenmaterialer" AND term.type="bog"
    AND term.subject=("gys" OR "overnaturlige evner")'
    =>
      'facet.category="voksenmaterialer" AND term.type="bog"
    AND term.subject=("gys" OR "overnaturlige evner")',

    'term.type="bog" AND facet.category="voksenmaterialer"
    NOT dkcclterm.dk=(82* OR 83* OR 84* OR 85* OR 86* OR 87* OR 88*)'
    =>
      'term.type="bog" AND facet.category="voksenmaterialer"
    NOT dkcclterm.dk=(82* OR 83* OR 84* OR 85* OR 86* OR 87* OR 88*)',

    'rec.id = 870970-basis:05203120 OR rec.id=870970-basis:05203120'
    =>
      'rec.id = 870970-basis:05203120 OR rec.id=870970-basis:05203120',

    'em any "delebørn skilsmissebørn"' => 'em any "delebørn skilsmissebørn"',

    'blue-ray' => 'blue-ray',
  );
}

function ting_search_test_invalid_cql() {
  return array(
    'anders and' => 'anders and and',

    'anders AND' => 'anders and AND',

    '"anders and"  phrase.title=ander*'
    =>
      '"anders and" and phrase.title=ander*',

    'anders AND (dc.title=historie)'
    =>
      'anders AND (dc.title=historie)',

    'hest fisk hund' => 'hest and fisk and hund',
    'hest fisk and hund' => 'hest and fisk and and and hund',
    'blue/ray' => 'blue and "/" and ray',
  );
}