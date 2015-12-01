<?php
/**
 * @file
 * ding_frontend.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_frontend_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "menu_block" && $api == "menu_block") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "pm_existing_pages" && $api == "pm_existing_pages") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ding_frontend_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ding_frontend_image_default_styles() {
  $styles = array();

  // Exported image style: ding_attachment_large.
  $styles['ding_attachment_large'] = array(
    'name' => 'ding_attachment_large',
    'effects' => array(
      6 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 500,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_attachment_large',
  );

  // Exported image style: ding_attachment_medium.
  $styles['ding_attachment_medium'] = array(
    'name' => 'ding_attachment_medium',
    'effects' => array(
      7 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 500,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_attachment_medium',
  );

  // Exported image style: ding_attachment_small.
  $styles['ding_attachment_small'] = array(
    'name' => 'ding_attachment_small',
    'effects' => array(
      8 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 500,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_attachment_small',
  );

  // Exported image style: ding_list_large.
  $styles['ding_list_large'] = array(
    'name' => 'ding_list_large',
    'effects' => array(
      3 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 300,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_list_large',
  );

  // Exported image style: ding_list_medium.
  $styles['ding_list_medium'] = array(
    'name' => 'ding_list_medium',
    'effects' => array(
      4 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 300,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_list_medium',
  );

  // Exported image style: ding_list_small.
  $styles['ding_list_small'] = array(
    'name' => 'ding_list_small',
    'effects' => array(
      5 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 200,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_list_small',
  );

  // Exported image style: ding_panorama_attachment_large.
  $styles['ding_panorama_attachment_large'] = array(
    'name' => 'ding_panorama_attachment_large',
    'effects' => array(
      11 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 500,
          'height' => 125,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_panorama_attachment_large',
  );

  // Exported image style: ding_panorama_attachment_medium.
  $styles['ding_panorama_attachment_medium'] = array(
    'name' => 'ding_panorama_attachment_medium',
    'effects' => array(
      12 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 500,
          'height' => 125,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_panorama_attachment_medium',
  );

  // Exported image style: ding_panorama_attachment_small.
  $styles['ding_panorama_attachment_small'] = array(
    'name' => 'ding_panorama_attachment_small',
    'effects' => array(
      13 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 500,
          'height' => 125,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_panorama_attachment_small',
  );

  // Exported image style: ding_panorama_list_large.
  $styles['ding_panorama_list_large'] = array(
    'name' => 'ding_panorama_list_large',
    'effects' => array(
      14 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 300,
          'height' => 75,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_panorama_list_large',
  );

  // Exported image style: ding_panorama_list_medium.
  $styles['ding_panorama_list_medium'] = array(
    'name' => 'ding_panorama_list_medium',
    'effects' => array(
      15 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 300,
          'height' => 75,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_panorama_list_medium',
  );

  // Exported image style: ding_panorama_list_small.
  $styles['ding_panorama_list_small'] = array(
    'name' => 'ding_panorama_list_small',
    'effects' => array(
      16 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 200,
          'height' => 50,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_panorama_list_small',
  );

  // Exported image style: ding_panorama_primary_large.
  $styles['ding_panorama_primary_large'] = array(
    'name' => 'ding_panorama_primary_large',
    'effects' => array(
      2 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1200,
          'height' => 300,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_panorama_primary_large',
  );

  // Exported image style: ding_panorama_primary_medium.
  $styles['ding_panorama_primary_medium'] = array(
    'name' => 'ding_panorama_primary_medium',
    'effects' => array(
      3 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1000,
          'height' => 250,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_panorama_primary_medium',
  );

  // Exported image style: ding_panorama_primary_small.
  $styles['ding_panorama_primary_small'] = array(
    'name' => 'ding_panorama_primary_small',
    'effects' => array(
      4 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 500,
          'height' => 125,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_panorama_primary_small',
  );

  // Exported image style: ding_panorama_secondary_large.
  $styles['ding_panorama_secondary_large'] = array(
    'name' => 'ding_panorama_secondary_large',
    'effects' => array(
      5 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 900,
          'height' => 225,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_panorama_secondary_large',
  );

  // Exported image style: ding_panorama_secondary_medium.
  $styles['ding_panorama_secondary_medium'] = array(
    'name' => 'ding_panorama_secondary_medium',
    'effects' => array(
      6 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 900,
          'height' => 225,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_panorama_secondary_medium',
  );

  // Exported image style: ding_panorama_secondary_small.
  $styles['ding_panorama_secondary_small'] = array(
    'name' => 'ding_panorama_secondary_small',
    'effects' => array(
      7 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 500,
          'height' => 125,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_panorama_secondary_small',
  );

  // Exported image style: ding_panorama_tetiary_large.
  $styles['ding_panorama_tetiary_large'] = array(
    'name' => 'ding_panorama_tetiary_large',
    'effects' => array(
      8 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 600,
          'height' => 150,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_panorama_tetiary_large',
  );

  // Exported image style: ding_panorama_tetiary_medium.
  $styles['ding_panorama_tetiary_medium'] = array(
    'name' => 'ding_panorama_tetiary_medium',
    'effects' => array(
      9 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 600,
          'height' => 150,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_panorama_tetiary_medium',
  );

  // Exported image style: ding_panorama_tetiary_small.
  $styles['ding_panorama_tetiary_small'] = array(
    'name' => 'ding_panorama_tetiary_small',
    'effects' => array(
      10 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 500,
          'height' => 125,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_panorama_tetiary_small',
  );

  // Exported image style: ding_primary_large.
  $styles['ding_primary_large'] = array(
    'name' => 'ding_primary_large',
    'effects' => array(
      15 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 1200,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_primary_large',
  );

  // Exported image style: ding_primary_medium.
  $styles['ding_primary_medium'] = array(
    'name' => 'ding_primary_medium',
    'effects' => array(
      16 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 1000,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_primary_medium',
  );

  // Exported image style: ding_primary_small.
  $styles['ding_primary_small'] = array(
    'name' => 'ding_primary_small',
    'effects' => array(
      17 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 500,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_primary_small',
  );

  // Exported image style: ding_secondary_large.
  $styles['ding_secondary_large'] = array(
    'name' => 'ding_secondary_large',
    'effects' => array(
      12 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 900,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_secondary_large',
  );

  // Exported image style: ding_secondary_medium.
  $styles['ding_secondary_medium'] = array(
    'name' => 'ding_secondary_medium',
    'effects' => array(
      13 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 900,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_secondary_medium',
  );

  // Exported image style: ding_secondary_small.
  $styles['ding_secondary_small'] = array(
    'name' => 'ding_secondary_small',
    'effects' => array(
      14 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 500,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_secondary_small',
  );

  // Exported image style: ding_tetiary_large.
  $styles['ding_tetiary_large'] = array(
    'name' => 'ding_tetiary_large',
    'effects' => array(
      9 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 600,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_tetiary_large',
  );

  // Exported image style: ding_tetiary_medium.
  $styles['ding_tetiary_medium'] = array(
    'name' => 'ding_tetiary_medium',
    'effects' => array(
      10 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 600,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_tetiary_medium',
  );

  // Exported image style: ding_tetiary_small.
  $styles['ding_tetiary_small'] = array(
    'name' => 'ding_tetiary_small',
    'effects' => array(
      11 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 500,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_tetiary_small',
  );

  return $styles;
}

/**
 * Implements hook_default_search_api_index().
 */
function ding_frontend_default_search_api_index() {
  $items = array();
  $items['default_multiple_index'] = entity_import('search_api_index', '{
    "name" : "Default multiple index",
    "machine_name" : "default_multiple_index",
    "description" : null,
    "server" : "localhost",
    "item_type" : "multiple",
    "options" : {
      "datasource" : { "types" : [ "node", "user" ] },
      "index_directly" : 0,
      "cron_limit" : "50",
      "fields" : {
        "item_bundle" : { "type" : "string" },
        "item_entity_id" : { "type" : "string" },
        "item_id" : { "type" : "string" },
        "item_label" : { "type" : "text" },
        "item_type" : { "type" : "string" },
        "node" : { "type" : "integer", "entity_type" : "node" },
        "node:author" : { "type" : "integer", "entity_type" : "user" },
        "node:changed" : { "type" : "date" },
        "node:comment" : { "type" : "integer" },
        "node:created" : { "type" : "date" },
        "node:ding_news_groups_ref" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "node:field_bpi_workflow" : { "type" : "string" },
        "node:field_ding_event_category" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "node:field_ding_event_lead" : { "type" : "text" },
        "node:field_ding_event_price" : { "type" : "integer" },
        "node:field_ding_event_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "node:field_ding_event_target" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "node:field_ding_group_lead" : { "type" : "text" },
        "node:field_ding_library_fax_number" : { "type" : "text" },
        "node:field_ding_library_lead" : { "type" : "text" },
        "node:field_ding_library_mail" : { "type" : "text" },
        "node:field_ding_library_phone_number" : { "type" : "text" },
        "node:field_ding_library_slug" : { "type" : "text" },
        "node:field_ding_news_category" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "node:field_ding_news_lead" : { "type" : "text" },
        "node:field_ding_news_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "node:field_ding_page_lead" : { "type" : "text" },
        "node:field_ding_page_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "node:field_ding_tabroll_lead" : { "type" : "text" },
        "node:group_group" : { "type" : "boolean" },
        "node:language" : { "type" : "string" },
        "node:nid" : { "type" : "integer" },
        "node:og_group_ref" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "node:og_membership" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "og_membership" },
        "node:promote" : { "type" : "boolean" },
        "node:revision" : { "type" : "boolean" },
        "node:source" : { "type" : "integer", "entity_type" : "node" },
        "node:status" : { "type" : "integer" },
        "node:title" : { "type" : "text" },
        "node:type" : { "type" : "string" },
        "node:vid" : { "type" : "integer" },
        "search_api_language" : { "type" : "string" },
        "user" : { "type" : "integer", "entity_type" : "user" },
        "user:created" : { "type" : "date" },
        "user:language" : { "type" : "string" },
        "user:mail" : { "type" : "text" },
        "user:name" : { "type" : "text" },
        "user:og_membership" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "og_membership" },
        "user:og_membership__1" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "og_membership" },
        "user:og_membership__2" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "og_membership" },
        "user:og_membership__3" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "og_membership" },
        "user:og_user_node" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "user:profile_ding_staff_profile" : { "type" : "integer", "entity_type" : "profile2" },
        "user:profile_provider_alma" : { "type" : "integer", "entity_type" : "profile2" },
        "user:relation_ting_reference_ting_object" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "ting_object" },
        "user:roles" : { "type" : "list\\u003Cinteger\\u003E" },
        "user:status" : { "type" : "integer" },
        "user:uid" : { "type" : "integer" }
      }
    },
    "enabled" : "1",
    "read_only" : "0"
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function ding_frontend_default_search_api_server() {
  $items = array();
  $items['localhost'] = entity_import('search_api_server', '{
    "name" : "Localhost",
    "machine_name" : "localhost",
    "description" : "",
    "class" : "search_api_solr_service",
    "options" : {
      "clean_ids" : true,
      "site_hash" : true,
      "scheme" : "http",
      "host" : "localhost",
      "port" : "8983",
      "path" : "\\/solr\\/ding2",
      "http_user" : "",
      "http_pass" : "",
      "excerpt" : 0,
      "retrieve_data" : 0,
      "highlight_data" : 0,
      "skip_schema_check" : 0,
      "solr_version" : "",
      "http_method" : "AUTO"
    },
    "enabled" : "1"
  }');
  return $items;
}
