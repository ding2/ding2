<?php
  /*
   * Markup documentation for Latto framework theme.
   */
?>
<html>
<head>
    <title>Ding2tal markup demo</title>

    <link rel="stylesheet" href="src/tdcss.css" type="text/css" media="screen">

    <!-- Project CSS -->
    <link rel="stylesheet" href="../../css/latto.bootstrap.css" type="text/css" media="screen">
    <link rel="stylesheet" href="../../css/latto.styles.css" type="text/css" media="screen">
    <link rel="stylesheet" href="/modules/system/system.base.css" type="text/css" media="screen">
    <link rel="stylesheet" href="demo/style.css" type="text/css" media="screen">
    
    <script type="text/javascript" src="src/vendors/jquery.js"></script>
    <script type="text/javascript" src="src/tdcss.js"></script>

</head>
<body data-spy="scroll" data-target=".docs-sidebar" onload="prettyPrint()">
  
  <ul class="docs-menu">
    <li class="title"><a href='/profiles/ding2/themes/latto/tools/tdcss/index.php'>Latto Documentation</a></li>
    <?php
    if (!empty($_SERVER['QUERY_STRING'])) {
      $query_string = explode('=', $_SERVER['QUERY_STRING']);
      $current_page = $query_string[1];
    }
    else {
      $current_page = 'markup.php';
    }

    foreach (scandir('sites') as $page) {
      if(strpos($page, '.') > 0) {
        $page_content = file_get_contents('sites/' . $page);
        $found_title = preg_match("/<title>(.*)<\/title>/i", $page_content, $title);

        $class = $page == $current_page ? 'active' : '';

        print '<li class=' . $class . '><a href=?page=' . $page . '>' . ($found_title ? (empty($title[1]) ? $page : $title[1]) : $page) . '</a></li>';
      }
    }
    ?>
  </ul>
  <div id="content">
    <?php 
    

    include_once('sites/' . $current_page);
    ?>
  </div>
</body>
</html>