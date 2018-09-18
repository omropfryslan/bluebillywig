<?php

/**
 * @file Bluebillywig_media/includes/bluebillywig_media.formatters.
 *
 * Formatters for Blue Billywig Media module.
 *
 * @todo Add more playout options.
 */

/**
 * Implements hook_file_formatter_info().
 */
function bluebillywig_media_file_formatter_info() {
  $formatters['bluebillywig_media_video'] = array(
    'label' => t('Blue Billywig Video'),
    'file types' => array('video'),
    'default settings' => array(),
    'view callback' => 'bluebillywig_media_file_formatter_video_view',
    'settings callback' => 'bluebillywig_media_file_formatter_video_settings',
    'mime types' => array('video/bluebillywig'),
  );

  $formatters['bluebillywig_media_video']['default settings'] = array(
    'width' => NULL,
    'height' => NULL,
    'autoplay' => NULL,
    'microdata' => TRUE,
  );

  $formatters['bluebillywig_media_audio'] = array(
    'label' => t('Blue Billywig Audio'),
    'file types' => array('audio'),
    'default settings' => array(),
    'view callback' => 'bluebillywig_media_file_formatter_audio_view',
    'settings callback' => 'bluebillywig_media_file_formatter_audio_settings',
    'mime types' => array('audio/bluebillywig'),
  );

  $formatters['bluebillywig_media_audio']['default settings'] = array(
    'width' => NULL,
    'height' => NULL,
    'autoplay' => NULL,
    'microdata' => TRUE,
  );

  $formatters['bluebillywig_media_video_iframe'] = array(
    'label' => t('Blue Billywig Video Iframe'),
    'file types' => array('video'),
    'default settings' => array(),
    'view callback' => 'bluebillywig_media_file_formatter_video_iframe_view',
    'settings callback' => 'bluebillywig_media_file_formatter_video_settings',
    'mime types' => array('video/bluebillywig'),
  );

  $formatters['bluebillywig_media_video_iframe']['default settings'] = array(
    'width' => NULL,
    'height' => NULL,
    'autoplay' => NULL,
    'microdata' => TRUE,
  );

  $formatters['bluebillywig_media_audio_iframe'] = array(
    'label' => t('Blue Billywig Audio Iframe'),
    'file types' => array('audio'),
    'default settings' => array(),
    'view callback' => 'bluebillywig_media_file_formatter_audio_iframe_view',
    'settings callback' => 'bluebillywig_media_file_formatter_audio_settings',
    'mime types' => array('audio/bluebillywig'),
  );

  $formatters['bluebillywig_media_audio_iframe']['default settings'] = array(
    'width' => NULL,
    'height' => NULL,
    'autoplay' => NULL,
    'microdata' => TRUE,
  );

  $formatters['bluebillywig_media_image'] = array(
    'label' => t('Blue Billywig Preview Image'),
    'file types' => array('video', 'audio'),
    'default settings' => array(
      'image_style' => '',
    ),
    'view callback' => 'bluebillywig_media_file_formatter_image_view',
    'settings callback' => 'bluebillywig_media_file_formatter_image_settings',
    'mime types' => array('video/bluebillywig', 'audio/bluebillywig'),
  );

  return $formatters;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function bluebillywig_media_file_formatter_video_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);
  // WYSIWYG does not yet support video inside a running editor instance.
  if ($scheme == 'bluebillywig' && empty($file->override['wysiwyg'])) {
    $element = array(
      '#theme' => 'bluebillywig_media_video',
      '#uri' => $file->uri,
      '#options' => array(),
    );

    // Fake a default for attributes so the ternary doesn't choke.
    $display['settings']['attributes'] = array();

    foreach (array('width', 'height', 'autoplay', 'microdata') as $setting) {
      if (isset($display['settings']) && isset($display['settings'][$setting])) {
        $element['#options'][$setting] = isset($file->override[$setting]) ? $file->override[$setting] : $display['settings'][$setting];
      }
    }
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function bluebillywig_media_file_formatter_video_iframe_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);
  // WYSIWYG does not yet support video inside a running editor instance.
  if ($scheme == 'bluebillywig' && empty($file->override['wysiwyg'])) {
    $element = array(
      '#theme' => 'bluebillywig_media_video_iframe',
      '#uri' => $file->uri,
      '#options' => array(),
    );

    // Fake a default for attributes so the ternary doesn't choke.
    $display['settings']['attributes'] = array();

    foreach (array('width', 'height', 'autoplay', 'microdata') as $setting) {
      if (isset($display['settings']) && isset($display['settings'][$setting])) {
        $element['#options'][$setting] = isset($file->override[$setting]) ? $file->override[$setting] : $display['settings'][$setting];
      }
    }
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function bluebillywig_media_file_formatter_audio_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);
  // WYSIWYG does not yet support video inside a running editor instance.
  if ($scheme == 'bluebillywig' && empty($file->override['wysiwyg'])) {
    $element = array(
      '#theme' => 'bluebillywig_media_audio',
      '#uri' => $file->uri,
      '#options' => array(),
    );

    // Fake a default for attributes so the ternary doesn't choke.
    $display['settings']['attributes'] = array();

    foreach (array('width', 'height', 'autoplay', 'microdata') as $setting) {
      if (isset($display['settings']) && isset($display['settings'][$setting])) {
        $element['#options'][$setting] = isset($file->override[$setting]) ? $file->override[$setting] : $display['settings'][$setting];
      }
    }
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function bluebillywig_media_file_formatter_audio_iframe_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);
  // WYSIWYG does not yet support video inside a running editor instance.
  if ($scheme == 'bluebillywig' && empty($file->override['wysiwyg'])) {
    $element = array(
      '#theme' => 'bluebillywig_media_audio_iframe',
      '#uri' => $file->uri,
      '#options' => array(),
    );

    // Fake a default for attributes so the ternary doesn't choke.
    $display['settings']['attributes'] = array();

    foreach (array('width', 'height', 'autoplay', 'microdata') as $setting) {
      if (isset($display['settings']) && isset($display['settings'][$setting])) {
        $element['#options'][$setting] = isset($file->override[$setting]) ? $file->override[$setting] : $display['settings'][$setting];
      }
    }
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 *
 * Blue Billywig thumbnails aren't locally stored, so always gathered from the VMS.
 */
function bluebillywig_media_file_formatter_image_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);
  if ($scheme == 'bluebillywig') {
    $wrapper = file_stream_wrapper_get_instance_by_uri($file->uri);

    $image_style = $display['settings']['image_style'];
    $valid_image_styles = image_style_options(FALSE);

    if (empty($image_style) || !isset($valid_image_styles[$image_style])) {
      $element = array(
        '#theme' => 'image',
        '#path' => $wrapper->getOriginalThumbnailPath(100, 100),
        '#alt' => isset($file->override['attributes']['alt']) ? $file->override['attributes']['alt'] : $file->filename,
      );
    }
    else {
      $element = array(
        '#theme' => 'bluebillywig_vce_image_style',
        '#style_name' => $image_style,
        '#path' => $wrapper->getLocalThumbnailPath(),
        '#alt' => isset($file->override['attributes']['alt']) ? $file->override['attributes']['alt'] : $file->filename,
        '#timestamp' => $file->timestamp,
      );
    }
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function bluebillywig_media_file_formatter_video_settings($form, &$form_state, $settings) {
  $element = array();

  $element['width'] = array(
    '#title' => t('Width'),
    '#type' => 'textfield',
    '#default_value' => $settings['width'],
    '#element_validate' => array('_bluebillywig_media_validate_video_width_and_height'),
  );
  $element['height'] = array(
    '#title' => t('Height'),
    '#type' => 'textfield',
    '#default_value' => $settings['height'],
    '#element_validate' => array('_bluebillywig_media_validate_video_width_and_height'),
  );
  $element['autoplay'] = array(
    '#title' => t('Autoplay video on load'),
    '#type' => 'checkbox',
    '#default_value' => $settings['autoplay'],
  );
  $element['microdata'] = array(
    '#title' => t('Microdata'),
    '#type' => 'checkbox',
    '#default_value' => (isset($settings['microdata']) ? $settings['microdata'] : TRUE),
    '#description' => t('Add microdata for Search Engines/Web Crawlers, besides the standard player embed.'),
  );

  return $element;
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function bluebillywig_media_file_formatter_audio_settings($form, &$form_state, $settings) {
  $element = array();

  $element['width'] = array(
    '#title' => t('Width'),
    '#type' => 'textfield',
    '#default_value' => $settings['width'],
    '#element_validate' => array('_bluebillywig_media_validate_video_width_and_height'),
  );
  $element['height'] = array(
    '#title' => t('Height'),
    '#type' => 'textfield',
    '#default_value' => $settings['height'],
    '#element_validate' => array('_bluebillywig_media_validate_video_width_and_height'),
  );
  $element['autoplay'] = array(
    '#title' => t('Autoplay audio on load'),
    '#type' => 'checkbox',
    '#default_value' => $settings['autoplay'],
  );
  $element['microdata'] = array(
    '#title' => t('Microdata'),
    '#type' => 'checkbox',
    '#default_value' => (isset($settings['microdata']) ? $settings['microdata'] : TRUE),
    '#description' => t('Add microdata for Search Engines/Web Crawlers, besides the standard player embed.'),
  );

  return $element;
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function bluebillywig_media_file_formatter_image_settings($form, &$form_state, $settings) {
  $element = array();
  $element['image_style'] = array(
    '#title' => t('Image style'),
    '#type' => 'select',
    '#options' => image_style_options(FALSE),
    '#default_value' => $settings['image_style'],
    '#empty_option' => t('None (original image)'),
  );
  return $element;
}

/**
 * Validation for width and height.
 */
function _bluebillywig_media_validate_video_width_and_height($element, &$form_state, $form) {

  // Check if the value is a number with an optional decimal or percentage sign, or "auto".
  if (!empty($element['#value']) && !preg_match('/^(auto|([0-9]*(\.[0-9]+)?%?))$/', $element['#value'])) {
    form_error($element, t('The value entered for @dimension is invalid. Please insert a unitless integer for pixels, a percent, or "auto". Note that percent and auto may not function correctly depending on the browser and doctype.', array('@dimension' => $element['#title'])));
  }
}

/**
 * Implements hook_file_default_displays().
 */
function bluebillywig_media_file_default_displays() {
  $file_displays = array();

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__default__bluebillywig_media_video';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'width' => NULL,
    'height' => NULL,
  );
  $file_displays['video__default__bluebillywig_media_video'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__default__bluebillywig_media_video_iframe';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'width' => NULL,
    'height' => NULL,
  );
  $file_displays['video__default__bluebillywig_media_video_iframe'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__preview__bluebillywig_media_image';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'media_thumbnail',
  );
  $file_displays['video__preview__bluebillywig_media_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__teaser__bluebillywig_media_video';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'width' => '320',
    'height' => '180',
  );
  $file_displays['video__teaser__bluebillywig_media_video'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__teaser__bluebillywig_media_video_iframe';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'width' => '320',
    'height' => '180',
  );
  $file_displays['video__teaser__bluebillywig_media_video_iframe'] = $file_display;

  return $file_displays;
}
