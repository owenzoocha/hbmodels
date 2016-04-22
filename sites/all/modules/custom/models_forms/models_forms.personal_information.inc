<?php
/**
 * @file models.personal_information.inc
 *
 * @author: Owen Williams http://drupal.org/user/??
 *
 */

function eek() {
global $user;

if (module_load_include('inc', 'hybridauth', 'hybridauth.pages')) {
  dpm('included');
}
// dpm( _hybridauth_identity_load_by_uid($user->uid));
dpm( _hybridauth_identity_load_by_uid($user->uid));
$bla = hybridauth_user_identity($user);
return drupal_render($bla);

// $user=user_load($user->uid);
// module_load_include('inc', 'user', 'user.pages');
// $user_form = drupal_get_form('user_profile_form', $user);
// dpm($user_form);
// return drupal_render($user_form);
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
