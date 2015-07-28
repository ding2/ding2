<?php

/**
 * @file
 * DDBasic's theme implementation to display event nodes.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct url of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $date (NOTE: modified for
 *   ddbasic during ddbasic_preprocess_node in templates.php)
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type, i.e., "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode, e.g. 'full', 'teaser'...
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined, e.g. $node->body becomes $body. When needing to access
 * a field's raw values, developers/themers are strongly encouraged to use these
 * variables. Otherwise they will have to explicitly specify the desired field
 * language, e.g. $node->body['en'], thus overriding any language negotiation
 * rule that was previously applied.
 *
 * ddbasic specific variables:
 * - $ddbasic_updated: Information about latest update on the node created from
 *   $date during
 *   ddbasic_preprocess_node().
 * - $ddbasic_event_date: Event date or period, printed as date(s) 
 * - $ddbasic_event_time: Event time, printed as time(s) 
 * - $ddbasic_ding_event_tags: Tags, as a comma-separated list of links with
 *   leading text "Tags: "
 * - $ddbasic_event_location: String containing adress info for either
 *   field_address or group_audience,
 *   as relevant for the event node
 * - $ddbasic_byline: outputs byline to be used before $name
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 */
?>
<article class="event">
  <h1 class="page-title"><?php print $title; ?></h1>

  <div class="event-lead">
    <?php print render($content['field_ding_event_lead']); ?>
  </div>
  <div class="event-info">
    <?php if (isset($ddbasic_event_date)) : ?>
      <p><i class="icon-calendar"></i> <?php print $ddbasic_event_date; ?></p>
    <?php endif; ?>
    <?php if (isset($ddbasic_event_date)) : ?>
      <p><i class="icon-time"></i> <?php print $ddbasic_event_time; ?></p>
    <?php endif; ?>

    <?php if (isset($ddbasic_event_location)): ?>
      <p><i class="icon-home"></i> <?php print render($ddbasic_event_location); ?></p>
    <?php endif; ?>

    <?php if (isset($content['field_ding_event_target'])): ?>
      <p><i class="icon-user"></i> <?php print render($content['field_ding_event_target']); ?></p>
    <?php endif; ?>

    <?php if (isset($content['field_ding_event_price'])): ?>
      <p><i class="icon-tag"></i> <?php print render($content['field_ding_event_price']); ?></p>
    <?php endif; ?>
  </div>  
  <div class="event-content">
    <?php if (isset($content['field_ding_event_title_image'])) : ?>
    <div class="event-image">
      <?php print render($content['field_ding_event_title_image']); ?>
    </div>
    <?php endif; ?>

    <?php
      // Hide fields we have already rendered.
      hide($content['field_ding_event_category']);
      hide($content['og_group_ref']);
      hide($content['ding_event_groups_ref']);

      hide($content['field_ding_event_date']);
      hide($content['field_ding_event_location']);
      hide($content['field_ding_event_target']);
      hide($content['field_ding_event_price']);

      // Hide fields that will be displayed as panel panes instead.
      hide($content['comments']);

      // Hide fields now so that we can render them later.
      hide($content['links']);
      hide($content['field_ding_event_tags']);

      print render($content);
    ?>
  </div>

  <footer class="event-footer">
    <section class="event-tags">
      <span class="event-category label"><?php print render($content['field_ding_event_category']); ?></span>
      <?php if (isset($content['field_ding_event_tags'])) : ?>
        <span class="event-tags label"><?php print render($content['field_ding_event_tags']); ?></span>
      <?php endif; ?>
      <?php if (isset($content['og_group_ref']['#items'])) : ?>
        <span class="library-ref label label-info"><?php print render($content['og_group_ref']); ?></span>
      <?php endif; ?>
      <?php if (isset($content['ding_event_groups_ref']['#items'])) : ?>
        <span class="groups-ref label"><?php print render($content['ding_event_groups_ref']); ?></span>
      <?php endif; ?>
    </section>

    <?php if ($display_submitted) : ?>
      <div class="signature">
        <div class="signature-image"><?php print $user_picture; ?></div>
        <div class="signature-info">
          <p><span class="signature-label"><?php print t("Posted by:"); ?></span><?php print $name; ?></p>
          <p><span class="signature-label"><?php print t("Posted at:"); ?></span><?php print $submitted ?></p>
          <p><span class="signature-label"><?php print t("Last updated:"); ?></span><?php print $ddbasic_updated ?></p>
        </div>
      </div>
    <?php endif; ?>
    
    <?php
      // Remove the "Add new comment" link on the teaser page or if the comment
      // form is being displayed on the same page.
      // @todo: this should be moved to field_preprocess.
      if ($teaser || !empty($content['comments']['comment_form'])) :
        unset($content['links']['comment']['#links']['comment-add']);
      endif;
    ?>

    <?php if (!empty($content['links']['#links'])) : ?>
      <div class="link-wrapper">
        <?php print render($links); ?>
      </div>
    <?php endif; ?>

  </footer>
</article>
