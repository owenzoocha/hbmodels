<?php
/**
 * @file models.personal_information.inc
 *
 * @author: Owen Williams http://drupal.org/user/??
 *
 */

function models_forms_personal_info() {
  global $user;
  $user = user_load($user->uid);
  module_load_include('inc', 'user', 'user.pages');
  $user_form = drupal_get_form('user_profile_form', $user);
  unset($user_form['account']);
  unset($user_form['field_my_name']);
  unset($user_form['privatemsg']);
  unset($user_form['timezone']);
  unset($user_form['picture']['picture_delete']);
  unset($user_form['field_hb_type']);
  unset($user_form['field_hb_ht']);
  unset($user_form['field_hb_bt']);
  return drupal_render($user_form);
}

function models_forms_email_settings() {
  global $user;

  $user = user_load($user->uid);
  module_load_include('inc', 'user', 'user.pages');
  $user_form = drupal_get_form('user_profile_form', $user);

  unset($user_form['account']);
  unset($user_form['field_my_name']);
  unset($user_form['field_first_name']);
  unset($user_form['field_surname']);
  unset($user_form['field_phone']);
  unset($user_form['field_gender']);
  unset($user_form['field_my_web']);
  unset($user_form['field_my_address']);
  unset($user_form['field_my_bio']);
  unset($user_form['field_my_latlong']);
  unset($user_form['timezone']);
  unset($user_form['picture']);
  unset($user_form['field_hb_type']);
  unset($user_form['field_hb_ht']);
  unset($user_form['field_hb_bt']);
  // unset($user_form['privatemsg']['pm_email_only_user']);
  $user_form['privatemsg']['pm_enable']['#value'] = TRUE;
  $user_form['privatemsg']['pm_enable']['#default_value'] = TRUE;
  $user_form['privatemsg']['pm_enable']['#checked'] = TRUE;
  return drupal_render($user_form);
}

function models_forms_interests() {
  global $user;

  $user = user_load($user->uid);
  module_load_include('inc', 'user', 'user.pages');
  $user_form = drupal_get_form('user_profile_form', $user);

  $user_form['interest_types'] = array(
    '#markup' => '<p>' . t('Let us know what you\'re interested in - we can use this to tailor your search results and keep you updated with offers.') . '</p>',
    '#weight' => 1,
  );
  unset($user_form['account']);
  unset($user_form['field_my_name']);
  unset($user_form['field_first_name']);
  unset($user_form['field_surname']);
  unset($user_form['field_phone']);
  unset($user_form['field_gender']);
  unset($user_form['field_my_web']);
  unset($user_form['field_my_address']);
  unset($user_form['field_my_bio']);
  unset($user_form['field_my_latlong']);
  unset($user_form['privatemsg']);
  unset($user_form['timezone']);
  unset($user_form['picture']);
  unset($user_form['field_hb_type']);
  // $user_form['field_my_tcs']['und']['#required'] = FALSE;
  // unset($user_form['field_my_tcs']);
  return drupal_render($user_form);
}

function models_forms_account_settings() {
  global $user;

  module_load_include('inc', 'hybridauth', 'hybridauth.pages');
  if(!empty(_hybridauth_identity_load_by_uid($user->uid))) {
    $identity = hybridauth_user_identity($user);
    $identity_table = drupal_render($identity);
  }

  $user = user_load($user->uid);
  module_load_include('inc', 'user', 'user.pages');
  $user_form = drupal_get_form('user_profile_form', $user);

  unset($user_form['field_my_name']);
  unset($user_form['field_first_name']);
  unset($user_form['field_surname']);
  unset($user_form['field_phone']);
  unset($user_form['field_gender']);
  unset($user_form['field_my_web']);
  unset($user_form['field_my_address']);
  unset($user_form['field_my_bio']);
  unset($user_form['field_my_latlong']);
  unset($user_form['privatemsg']);
  unset($user_form['timezone']);
  unset($user_form['picture']);
  unset($user_form['field_hb_type']);
  unset($user_form['field_hb_ht']);
  unset($user_form['field_hb_bt']);

  if (isset($identity_table)) {
    return drupal_render($user_form) . $identity_table;
  }
  else {
    return drupal_render($user_form);
  }
}

/**
 * Implements hook_form().
 * Provides functionality to update users personal information.
 */

function models_forms_personal_information_form($form, &$form_state){
  global $user;
  $uw = entity_metadata_wrapper('user', $user);

  $desc = t('blabla');
  $form['form_description'] = array(
    '#markup' => '<p>'.$desc.'</p>',
  );

  // $form['pass_fields'] = array(
  //   '#type' => 'password_confirm',
  //   '#description' => t('Enter the same password in both fields'),
  //   '#size' => 32,
  //   '#required' => TRUE,
  // );


  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('save'),
    '#attributes' => array(
      'class' => array('btn-success'),
      'data-loading-text' => array("Sending request.."),
      'data-complete-text' => array('Sent!'),
    ),
  );
  return $form;

}

function models_forms_personal_information_form_submit($form, &$form_state){
  global $user;
  $nw = entity_metadata_wrapper('node', $form_state['nid']);
  $uw = entity_metadata_wrapper('user', $user->uid);
  $msg = isset($form_state['values']['msg']) ? $form_state['values']['msg'] : false;
  $removed = 1;
  if(sizeof($nw->field_hb_users->value()) > 0){
    $flag = 0;
    foreach ($nw->field_hb_users->getIterator() as $k => $u) {
      if($u->getIdentifier() == $user->uid){
        $nw->field_hb_users[$k] = NULL;
        $flag = 1;
        break;
      }
    }
    if($flag == 0){
      $nw->field_hb_users->offsetSet(sizeof($nw->field_hb_users->value()), $user->uid);
      rules_invoke_component('rules_pm_job_request', $msg, $user, $nw->author->value(), $nw->value());
      $removed = 0;
    }
  } else {
    $nw->field_hb_users->offsetSet(0, $user->uid);
    rules_invoke_component('rules_pm_job_request', $msg, $user, $nw->author->value(), $nw->value());
    $removed = 0;
  }

  $nw->save();

  if($removed == 1){
    drupal_set_message(t('Hey !name, your job request has now been removed - we\'ve let the job owner know! Check out the <strong>job board</strong> for more hair and beauty options.', array('!name' => $uw->field_first_name->value())), 'info', FALSE);
  } else {
    drupal_set_message(t('Hey !name, good news - your request has been sent! Keep an eye on your <strong>job requests</strong> for updates - you will be contacted soon.', array('!name' => $uw->field_first_name->value())), 'info', FALSE);
  }
}
