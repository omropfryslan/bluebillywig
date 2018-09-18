<?php

/**
 * @file Media_bluebillywig/includes/MediaBlueBillywigStreamWrapper.inc.
 *
 *  Create a BlueBillywig Stream Wrapper class for the Media/Resource module.
 */

/**
 * Create an instance like this:
 *  $bluebillywig = new MediaBlueBillywigStreamWrapper('bluebillywig://v/[video-code]');.
 */
class MediaBlueBillywigStreamWrapper extends MediaReadOnlyStreamWrapper {

  /**
   * Overrides $base_url defined in MediaReadOnlyStreamWrapper.
   */
  protected $base_url = '';

  /**
   *
   */
  public function __construct() {
    $hostName = variable_get('bluebillywig_publication_hostname', '');
    $this->base_url = 'https://' . $hostName;
  }

  /**
   * Returns a url in the format "http://<title>.bbvms.com/params".
   *
   * Overrides interpolateUrl() defined in MediaReadOnlyStreamWrapper.
   * This is an exact copy of the function in MediaReadOnlyStreamWrapper,
   * here in case that example is redefined or removed.
   */
  public function interpolateUrl() {
    if ($parameters = $this->get_parameters()) {
      return $this->base_url . '/p/' . $parameters['playout'] . '/' . $parameters['contentIdentifier'] . '/' . $parameters['id'] . '.html';
    }
  }

  /**
   *
   */
  public static function getMimeType($uri, $mapping = NULL) {
    // Not the finest way to determine the exact type of a file entity, but for updates the hook_file_presave is invoked,
    // but doens't have any affect.
    $result = db_query('SELECT fm.* FROM {file_managed} fm WHERE fm.uri = :uri', array(':uri' => $uri));
    $record = $result->fetchAssoc();
    if ($record) {
      if (isset($record['type']) && $record['type'] == 'audio') {
        return 'audio/bluebillywig';
      }
    }
    return 'video/bluebillywig';
  }

  /**
   *
   */
  public function getTarget($f) {
    return FALSE;
  }

  /**
   *
   */
  public function getOriginalThumbnailPath($width = 'default', $height = 'default') {
    $parts = $this->get_parameters();
    return $this->base_url . '/mediaclip/' . check_plain($parts['id']) . '/pthumbnail/' . $width . '/' . $height . '.jpg?' . time();
  }

  /**
   *
   */
  public function getLocalThumbnailPath() {
    $parts = $this->get_parameters();
    $local_path = file_default_scheme() . '://media-bluebillywig/' . check_plain($parts['id']) . '.jpg';
    if (!file_exists($local_path)) {
      $dirname = drupal_dirname($local_path);
      file_prepare_directory($dirname, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
      $response = drupal_http_request($this->getOriginalThumbnailPath());

      if (!isset($response->error)) {
        file_unmanaged_save_data($response->data, $local_path, TRUE);
      }
      else {
        @copy($this->getOriginalThumbnailPath(), $local_path);
      }
    }
    return $local_path;
  }

  /**
   * Returns an array of any parameters stored in the URL's path.
   *
   *  Because the function _parse_url() in MediaReadOnlyStreamWrapper don't accepts an uneven number of parts
   *  and we're using another url formatting, so this function overrides the standard one.
   *
   * @param $url
   *   The URL to parse
   *
   * @return
   *   An associative array of all the parameters in the path,
   *    or FALSE if the $url is ill-formed.
   */
  protected function _parse_url($url) {

    $path = explode('://', $url);
    $parts = explode('/', $path[1]);
    $params = array();
    $count = 0;
    $total = count($parts);
    if (!$total) {
      // If we have no parts, it's malformed.
      return FALSE;
    }

    $params['host'] = $parts[0];
    $params['playout'] = $parts[2];
    $params['contentIdentifier'] = $parts[3];
    $arId = explode('.', $parts[4]);
    $params['id'] = $arId[0];

    return $params;
  }

}
