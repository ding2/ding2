<?php
/**
 * @file
 * Theme function default implementation for the module.
 */

/**
 * Implements hook_preprocess_ting_object_cover().
 *
 * Default template preprocess for ting_object_cover theme function. It adds the
 * right class to the HTML element to ensure that the image is load now or
 * loaded by ajax if it has not been downloaded yet from moreinfo services.
 */
function template_preprocess_ting_object_cover(&$variables) {
  $object = $variables['object'] = $variables['elements']['#object'];
  $variables['image_style'] = $variables['elements']['#image_style'];
  $variables['link'] = !empty($variables['elements']['#link']) ? $variables['elements']['#link'] : FALSE;

  // Set initial values required by the template.
  $variables['classes'] = array(
    'ting-cover',
  );
  $variables['data'] = array(
    'ting-cover-object-id' => $object->id,
    'ting-cover-style' => $variables['image_style'],
  );
  $variables['image'] = '';

  if (cache_get('ting_covers:' . $object->id)) {
    // We know that there is no cover available for this object so avoid
    // further javascript processing.
    $variables['classes'][] = 'ting-cover-processed';
  }
  else {
    $path = ting_covers_object_path($object->id);
    if (file_exists($path)) {
      // Generate an alt tag.
      $alt = implode(', ', $object->creators) . ': ' . $object->title;

      // Render the img element.
      $variables['image'] = theme('image_style', array(
                              'style_name' => $variables['image_style'],
                              'path' => $path,
                              'alt' => $alt,
                            ));

      // Avoid further javascript processing. Just load the image.
      $variables['classes'][] = 'ting-cover-processed';
    }
  }
}

/**
 * Implements theme_ting_object_cover().
 *
 * Default theme function implementation.
 */
function theme_ting_object_cover($variables) {
  $data = "";
  foreach ($variables['data'] as $name => $value) {
    $data .= 'data-' . $name . '="' . htmlentities($value) . '" ';
  }

  if ($variables['link'] === FALSE) {
    return '<div class="' . implode(' ', $variables['classes']) . '" ' . trim($data) . '>' . $variables['image'] . '</div>';
  }

  return '<a href="' . url($variables['link']) . '" class="' . implode(' ', $variables['classes']) . '" ' . trim($data) . '>' . $variables['image'] . '</a>';
}
