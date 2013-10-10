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

  // Set initial values required by the template.
  $variables['classes'] = array(
    'ting-cover',
    'ting-cover-object-id-' . $object->localId,
    'ting-cover-style-' . $variables['image_style'],
    'ting-cover-owner-id-' . $object->ownerId,
  );
  $variables['image'] = '';

  // If we already have the image available locally then just use it.
  $path = ting_covers_object_path($object->localId);
  if (file_exists($path)) {
    // Generate an alt tag.
    $alt = implode(', ', $object->creators) . ': ' . $object->title;

    $variables['image'] = theme('image_style', array(
      'style_name' => $variables['image_style'],
      'path' => $path,
      'alt' => $alt,
    ));

    // Avoid further javascript processing.
    $variables['classes'][] = 'ting-cover-processed';
  }
  elseif (cache_get('ting_covers:' . $object->localId)) {
    // We know that there is no cover available for this object so avoid
    // further javascript processing.
    $variables['classes'][] = 'ting-cover-processed';
  }
}

/**
 * Implements theme_ting_object_cover().
 *
 * Default theme function implementation.
 */
function theme_ting_object_cover($variables) {
  return '<div class="' . implode(' ', $variables['classes']) . '">' . $variables['image'] . '</div>';
}
