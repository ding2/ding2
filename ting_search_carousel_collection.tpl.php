<li>
	<a href="<?php echo $collection->url ?>" title="<?php print check_plain($collection->creators_string); ?>: <?php print check_plain($collection->title); ?>">
		<img src="<?php echo ting_covers_collection_url($collection->objects[0], 'ting_search_carousel') ?>" alt=""/>
		<div class="info">
			<span class="creator"><?php print check_plain($collection->creators_string); ?></span>
			<span class="title"><?php print check_plain($collection->title); ?></span>
	  </div>
	</a>
</li>
