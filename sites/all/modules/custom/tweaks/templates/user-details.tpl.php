<div class="row">
  <div class="hbm-user-details col-sm-4">
    <div class="hbm-user-details-wrapper">
      <?php
        print $name;
        print $username;
        print $add;
        print $web;
      ?>
  </div>
  </div>
  <div class="hbm-user-details col-sm-8">
    <div class="hbm-user-details-wrapper">
      <?php

        $fb_block = block_load('views', 'user_feedback-block_1');
        $block = _block_get_renderable_array(_block_render_blocks(array($fb_block)));
        print drupal_render($block);
      ?>
  </div>
  </div>
</div>
