<?php
/**
 * @file
 * Provides form functionality to request a job after creation.
 */

/**
 * Implements hook_form().
 * Provides functionality to request a job.
 */
function models_forms_request_form($form, &$form_state){
  global $user;
  $nw = entity_metadata_wrapper('node', arg(1));
  $uw = entity_metadata_wrapper('user', $user);

  $form_state['nid'] = arg(1);
  foreach ($nw->field_hb_users->getIterator() as $k => $v) {
    if($v->getIdentifier() == $user->uid){
      $requested = true;
      break;
    }
  }

  $desc = !isset($requested) ? t('Hey !name, to show you\'re interested in this job, leave a message for the job owner below and hit <strong>sign me up</strong>!', array('!name' => $uw->field_first_name->value())) : t('To remove your request select <strong>remove request</strong> below - we\'ll let the job owner know.', array('!name' => $uw->field_first_name->value()));
  $form['form_description'] = array(
    '#markup' => '<p>'.$desc.'</p>',
  );

  if(!isset($requested)){
    $form['msg'] = array(
      '#type' => 'textarea',
      // '#title' => t('Message'),
      '#description' => t('... send a private message to !author.', array('!author' => $nw->author->field_first_name->value())),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => !isset($requested) ? t('sign me up') : t('remove request'),
    '#attributes' => array(
      'class' => !isset($requested) ? array('btn-success') : array('btn-danger'),
      'data-loading-text' => array("Sending request.."),
      'data-complete-text' => array('Sent!'),
    ),
  );
  return $form;
}

function models_forms_request_form_submit($form, &$form_state){
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
