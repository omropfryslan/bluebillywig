<?php

/**
 * @file Bluebillywig_media/includes/MediaBluebillywigBrowser.inc.
 *
 * Definition of MediaBluebillywigBrowser.
 */

/**
 * Media browser plugin for displaying a specific view and display.
 */
class MediaBlueBillywigBrowser extends MediaBrowserPlugin {

  /**
   * Implements MediaBrowserPluginInterface::access().
   */
  public function access($account = NULL) {
    return file_entity_access('create', NULL, $account);
  }

  /**
   * Implements MediaBrowserPlugin::view().
   */
  public function view() {
    // Check if the user is able to add remote media.
    if (user_access('add media from remote sources')) {
      $build['form'] = drupal_get_form('media_bluebillywig_add', $this->params['types'], $this->params['multiselect']);
      return $build;
    }
  }

}
