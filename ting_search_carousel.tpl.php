<div class="ting-search-carousel">
  <ul class="search-results">
    <?php foreach ($searches as $i => $search) :?>
      <li class="<?php echo ($i == 0) ? 'active' : ''; ?>">
        <div class="subtitle">
          <?php echo $search['subtitle']; ?>
        </div>
        <ul class="jcarousel-skin-ting-search-carousel">
        </ul>
      </li>
    <?php endforeach; ?>
  </ul>

  <ul class="search-controller">
    <?php foreach ($searches as $i => $search) : ?>
      <li class="<?php echo ($i == 0) ? 'active' : ''; ?>">
        <a href="#"><?php echo $search['title'] ?></a>
      </li>
    <?php endforeach; ?>
  </ul>
</div>
