<?php
/**
 * @file
 * Provides form functionality to cancel jobs / PM node author.
 */

/**
 * Implements hook_form().
 * Provides functionality to cancel a job.
 */
function models_forms_cancel_form($form, &$form_state){
  global $user;
  $nw = entity_metadata_wrapper('node', arg(1));
  $uw = entity_metadata_wrapper('user', $user);

  $form_state['nid'] = arg(1);

  $desc = t('To remove this current job - please make sure you have no job requests.');

  $form['form_description'] = array(
    '#markup' => '<p>'.$desc.'</p>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Remove Job'),
    '#attributes' => array(
      'class' => array('btn-success'),
      'data-loading-text' => array("removing.."),
      'data-complete-text' => array('remove!'),
    ),
  );
  return $form;
}

function models_forms_publish_form_submit($form, &$form_state){
  global $user;
  $nw = entity_metadata_wrapper('node', $form_state['nid']);
  $nw->status->set(1);
  $nw->save();
  drupal_set_message(t($nw->label() . ' is now published, keep an eye on your <strong>job requests</strong> to see who\'s interested.'), 'info', FALSE);
}
