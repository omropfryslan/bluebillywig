<?php

/**
 * @file
 */

/**
 *
 */
function bluebillywig_admin_settings($form, &$form_state) {
  // VMS-publication Account.
  $form['account'] = array(
    '#type' => 'fieldset',
    '#title' => t('VMS publication settings'),
    '#collapsible' => TRUE,
    '#collapsed' => (variable_get('bluebillywig_shared_secret', '') != '' ? TRUE : FALSE),
  );
  $form['account']['bluebillywig_publication_hostname'] = array(
    '#type' => 'textfield',
    '#title' => t('Publication Hostname'),
    '#maxlength' => 128,
    '#required' => TRUE,
    '#default_value' => variable_get('bluebillywig_publication_hostname', ''),
    '#description' => t('The hostname of your Blue Billywig VMS publication. The name of your publication can be found in the hostname you\'re using to acces the VMS, so: http://[publication_name].bbvms.com (for example: example.bbvms.com).'),
  );
  $form['account']['bluebillywig_shared_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Blue Billywig Shared Secret'),
    '#maxlength' => 255,
    '#required' => TRUE,
    '#default_value' => variable_get('bluebillywig_shared_secret', ''),
    '#description' => t('Fill in the Shared Secret as received from Blue Billywig. If you haven\'t received an Shared Secret, please contact !link.', array('!link' => l(t('Blue Billywig'), 'http://bluebillywig.com/nl/contact'))),
  );

  $form['player'] = array(
    '#type' => 'fieldset',
    '#title' => t('VMS Playout default settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['player']['bluebillywig_default_playout'] = array(
    '#type' => 'select',
    '#title' => t('The default playout'),
    '#maxlength' => 255,
    '#required' => FALSE,
    '#disabled' => (variable_get('bluebillywig_shared_secret', '') == '' ? TRUE : FALSE),
    '#options' => bluebillywig_get_cached_playouts(),
    '#default_value' => variable_get('bluebillywig_default_playout', 'default'),
    '#description' => t('Select a default playout. This playout will be selected by default when embedding a video.'),
  );

  $form['player']['bluebillywig_default_keywords'] = array(
    '#type' => 'textfield',
    '#title' => t('The default keywords'),
    '#required' => FALSE,
    '#default_value' => variable_get('bluebillywig_default_keywords', ''),
    '#description' => t('Add keywords for filtering, delimit by ",". Leave empty for none.'),
  );

  $form['#validate'][] = 'bluebillywig_admin_settings_validate';
  $form['#submit'][] = 'bluebillywig_admin_settings_submit';

  return system_settings_form($form);
}

/**
 * Validate handler for bluebillywig_admin_settings.
 */
function bluebillywig_admin_settings_validate($form, &$form_state) {
  // Check the VMS-credentials before saving.
  if (!_bluebillywig_checkVmsCredentials($form_state['values']['bluebillywig_publication_hostname'], $form_state['values']['bluebillywig_shared_secret'])) {
    form_set_error('bluebillywig_credentails_incorrect', t('Couldn\'t connect with the VMS publication.'));
    form_set_error('bluebillywig_publication_hostname', 'The publication hostname may be invalid.');
    form_set_error('bluebillywig_shared_secret', 'The Shared Secret may be invalid');
  }
}

/**
 * Submit handler for bluebillywig_admin_settings.
 */
function bluebillywig_admin_settings_submit($form, &$form_state) {
    cache_clear_all('bluebillywig_playouts_list', 'cache');
}
