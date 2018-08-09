<?php

/**
 * @file Bluebillywig_media/includes/MediaInterenetBlueBillywigHandler.inc.
 *
 * Contains MediaInternetBlueBillywigHandler.
 */

/**
 * Implementation of MediaInternetBaseHandler.
 *
 * @see hook_media_internet_providers().
 */
class MediaInternetBlueBillywigHandler extends MediaInternetBaseHandler {

  /**
   * Check if a BlueBillywig video id is valid.
   *
   * @return
   *   Boolean.
   */
  public static function validId($id) {
    $publicationHost = variable_get('bluebillywig_publication_hostname', NULL);
    if (empty($publicationHost)) {
      return FALSE;
    }
    $response = bluebillywig_executeActionVms('mediaclip', array("id" => $id));
    // Check if the response is valid.
    if ($response['id'] != $id) {
      throw new MediaInternetValidationException("The BlueBillywig media-clip ID is invalid, not published or the media-clip was deleted.");
    }
    return TRUE;
  }

  /**
   *
   */
  public function parse($embedCode) {

    $publicationHost = variable_get('bluebillywig_publication_hostname', NULL);
    if (empty($publicationHost)) {
      return FALSE;
    }

    // Default VMS domain.
    $domainPattern = 'bbvms\.com';
    if (!strpos($publicationHost, 'bbvms.com')) {
      $parts = explode('.', $publicationHost);
      $l = count($parts);
      $domainPattern = $parts[$l - 2] . '\.' . $parts[$l - 1];
    }

    $patterns = array(
      '@' . $domainPattern . '/p/(.*?)\/c\/(\d+)@',
    );
    foreach ($patterns as $pattern) {
      preg_match($pattern, $embedCode, $matches);
      if (isset($matches[2])) {
        $fsWrapperUriNorm = file_stream_wrapper_uri_normalize('bluebillywig://' . $publicationHost . '/p/' . $matches[1] . '/c/' . $matches[2] . '.js');
        return $fsWrapperUriNorm;
      }
    }
  }

  /**
   *
   */
  public function claim($embedCode) {
    if ($this->parse($embedCode)) {
      return TRUE;
    }
  }

  /**
   *
   */
  public function getFileObject() {
    $uri = $this->parse($this->embedCode);
    $file = file_uri_to_object($uri, TRUE);
    return $file;
  }

}
