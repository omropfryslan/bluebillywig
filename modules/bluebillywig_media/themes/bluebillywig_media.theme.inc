<?php

/**
 * @file Bluebillywig_media/themes/bluebillywig_media.theme.inc.
 *
 * Theme and preprocess functions for Media: bluebillywig.
 */

/**
 * Preprocess function for theme('bluebillywig_media_audio').
 * Call video pre-processing function. No need to separate here.
 */
function bluebillywig_media_preprocess_bluebillywig_media_audio(&$variables) {
  return bluebillywig_media_preprocess_bluebillywig_media_video($variables);
}

/**
 *
 */
function bluebillywig_media_preprocess_bluebillywig_media_video_iframe(&$variables) {
  return bluebillywig_media_preprocess_bluebillywig_media_video($variables);
}

/**
 *
 */
function bluebillywig_media_preprocess_bluebillywig_media_audio_iframe(&$variables) {
  return bluebillywig_media_preprocess_bluebillywig_media_audio($variables);
}

/**
 * Preprocess function for theme('bluebillywig_media_video').
 */
function bluebillywig_media_preprocess_bluebillywig_media_video(&$variables) {
  // Build the URI.
  $wrapper = file_stream_wrapper_get_instance_by_uri($variables['uri']);
  $parts = $wrapper->get_parameters();
  if (!empty($parts)) {
    $variables['playout'] = $parts['playout'];
    $variables['contentIdentifier'] = $parts['contentIdentifier'];
    $variables['video_id'] = $variables['clip_id'] = $parts['id'];
  }
  // Make the file object available.
  $file_object = file_uri_to_object($variables['uri']);

  // Parse options and build the query string. Only add the option to the query
  // array if the option value is not default. Be careful, depending on the
  // wording in media_vimeo.formatters.inc, TRUE may be query=0.
  // @see http://developer.vimeo.com/player/embedding
  $query = array();

  // Strings.
  if (isset($variables['options']['color'])) {
    $query['color'] = str_replace('#', '', $variables['options']['color']);
  }

  // Get microdata for the current mediaclip
  // Add some options as their own template variables.
  foreach (array('width', 'height', 'autoplay', 'microdata') as $themevar) {
    if (isset($variables['options'][$themevar])) {

      if ($themevar == 'microdata') {
        $variables[$themevar] = NULL;
        if ($variables['options'][$themevar] == 1 && $microdata = bluebillywig_media_get_microdata($variables['video_id'], $variables['playout'])) {
          $variables[$themevar] = $microdata;
        }
      }
      else {
        $variables[$themevar] = $variables['options'][$themevar];
      }
    }
    else {
      $variables[$themevar] = NULL;
    }
  }

  // Do something useful with the overridden attributes from the file
  // object. We ignore alt and style for now.
  if (isset($variables['options']['attributes']['class'])) {
    if (is_array($variables['options']['attributes']['class'])) {
      $variables['classes_array'] = array_merge($variables['classes_array'], $variables['options']['attributes']['class']);
    }
    else {
      // Provide nominal support for Media 1.x.
      $variables['classes_array'][] = $variables['options']['attributes']['class'];
    }
  }

  // Add template variables for accessibility.
  $variables['title'] = check_plain($file_object->filename);
  // @TODO: Find an easy/ not too expensive way to get the Vimeo description
  // to use for the alternative content.
  $variables['alternative_content'] = t('Video of @title', array('@title' => $variables['title']));

  // Build the iframe URL with options query string.
  if (!isset($protocol)) {
    $protocol = '//';
  }

  // TODO: less "hacky" url concatenation.
  $variables['url'] = url($protocol . preg_replace('@bluebillywig://@', '', $variables['uri']), array('query' => $query, 'external' => TRUE));
  // Make iframe (html version) of url.
  $variables['iframeUrl'] = preg_replace('@\.js@', '.html', $variables['url']);
}
