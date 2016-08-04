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
  $variables['classes_array'] = array();
  $variables['attributes_array'] = NULL;
  $variables['title_attributes_array'] = NULL;
  $variables['content_attributes_array'] = NULL;
  $image_style = $variables['elements']['#image_style'];
  $object = $variables['elements']['#object'];
  $local_ids[] = $object->provider_id;

  $variables['elements']['#id'] = drupal_html_id(md5(implode($local_ids), TRUE));
  $variables['elements']['#front_cover_large_image'] = array('#markup' => 'fubar');
  $variables['elements']['#back_cover_large_pdf'] = array('#markup' => 'fubar');
  $variables['elements']['#close_button'] = array(
    '#markup' => '<a class="reveal-cover close-reveal-modal">&#215;</a>',
  );
  // Set initial values required by the template, and check if there's an image available locally.
  $cover_file_path = FALSE;
  $backcoverpdf_file_path = $backcoverpdf_local_id = FALSE;
  $variables['elements']['#classes'] = array(
    'ting-cover',
    'ting-cover-style-' . $image_style,
  );
  foreach ($local_ids as $key => $lid) {
    // If there's a cover in the file system, we'll use it. Otherwise, we'll get it by AJAX.
    $file_path = ting_covers_object_path($lid, 'detail');
    if (file_exists($file_path)) {
      $cover_file_path = $file_path;
    }
    $file_path = ting_covers_object_path($lid, 'backpage');
    if (file_exists($file_path)) {
      $backcoverpdf_file_path = $file_path;
    }

    if (!empty($lid)) {
      $variables['elements']['#classes'][] = 'ting-cover-object-id-' . $lid;
    }
  }
  // Default link if there's no covers cached.
  $variables['elements']['#image'] = array(
    '#type' => 'link',
    '#title' => '',
    '#href' => '#',
    '#options' => array(
      'attributes' => array(
        'class' => array('reveal-cover'),
        'title' => t('See large image', array(), array('context' => 'ting_covers')),
        'aria-label' => t('See large image', array(), array('context' => 'ting_covers')),
        'data-reveal-id' => 'reveal-cover-large-' . $variables['elements']['#id'],
      ),
    ),
  );

  if ($cover_file_path) {
    $alt = '';
    if (isset($object->creators)) {
      $alt = implode(', ', $object->creators);
    }

    // Thumbnail image with link to full cover in modal window.
    $variables['elements']['#image'] = array(
      '#type' => 'link',
      '#title' => theme('image_style', array(
        'style_name' => $image_style,
        'path' => $cover_file_path,
        'alt' => $alt,
      )),
      '#href' => '#',
      '#options' => array(
        'html' => TRUE,
        'attributes' => array(
          'class' => array('reveal-cover'),
          'title' => t('See large image foo', array(), array('context' => 'ting_covers')),
          'aria-label' => t('See large image', array(), array('context' => 'ting_covers')),
          'data-reveal-id' => 'reveal-cover-large-' . $variables['elements']['#id'],
        ),
      ),
    );
    $variables['elements']['#no_image_style'] = '';
    // Front cover image (shown in modal window).
    $variables['elements']['#front_cover_large_image'] = array(
      '#theme' => 'image_style',
      '#path' => $cover_file_path,
      '#style_name' => 'large',
      '#attributes' => array(
        'alt' => $alt,
        'title' => t('large cover image', array(), array('context' => 'ting_covers')),
      ),
    );
    // Back cover pdf object (shown in modal window).
    if ($wrapper = file_stream_wrapper_get_instance_by_uri($backcoverpdf_file_path)) {
      $backcover_uri = $wrapper->getExternalUrl();
      $variables['elements']['#back_cover_large_pdf'] = array(
        '#markup' =>
          '<object data="' . $backcover_uri . '?page=1&amp;view=Fit" type="application/pdf" width="590" height="925">
              <p>It appears you don\'t have a PDF plugin for this browser.
                 No biggie... you can <a href="' . $backcover_uri . '">click here to download the PDF file.</a></p>
           </object>',
      );
    }
    // Avoid further javascript processing.
    $variables['elements']['#classes'][] = 'ting-cover-processed';
  }
  // Front cover modal link.
  $options = array(
    'html' => FALSE,
    'attributes' => array(
      'class' => array('cover-front', 'active', 'reveal-cover'),
      'title' => t('See large cover image', array(), array('context' => 'ting_covers')),
      'aria-label' => t('See large cover image', array(), array('context' => 'ting_covers')),
      'data-reveal-id' => 'reveal-cover-large-' . $variables['elements']['#id'],
    ),
  );
  if (!file_exists($backcoverpdf_file_path)) {
    $options['attributes']['style'] = 'display:none';
  }
  $variables['elements']['#front_cover_large_link'] = array(
    '#type' => 'link',
    '#title' => '',
    '#href' => '',
    '#options' => $options,
  );
  $options = array(
    'html' => FALSE,
    'attributes' => array(
      'class' => array('cover-back', 'reveal-cover'),
      'title' => t('See large back cover image', array(), array('context' => 'ting_covers')),
      'aria-label' => t('See large back cover image', array(), array('context' => 'ting_covers')),
      'data-reveal-id' => 'reveal-cover-back-' . $variables['elements']['#id'],
    ),
  );
  if (!file_exists($backcoverpdf_file_path)) {
    $options['attributes']['style'] = 'display:none';
  }
  $variables['elements']['#back_cover_large_link'] = array(
    '#type' => 'link',
    '#title' => '',
    '#href' => '',
    '#options' => $options,
  );
  if (!isset($variables['classes_array'])) {
    $variables['classes_array'] = array();
  }
  if (!isset($variables['attributes_array'])) {
    $variables['attributes_array'] = array();
  }
  if (!isset($variables['title_attributes_array'])) {
    $variables['title_attributes_array'] = array();
  }
  if (!isset($variables['content_attributes_array'])) {
    $variables['content_attributes_array'] = array();
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
