<?php

/**
 * @file
 * Defines contact message entity controller.
 */

/**
 * Class CRMMessageController
 */
class CRMMessageTemplateController extends EntityAPIController {

  /**
   * Overrides EntityAPIController::buildQuery().
   */
  public function buildQuery($ids, $conditions = array(), $revision_id = FALSE) {
    // Add an alias to this query to ensure that we can tell if this is
    // the current revision or not.
    $query = parent::buildQuery($ids, $conditions, $revision_id);
    $query->addField('base', $this->revisionKey, 'current_revision_id');
    return $query;
  }

  /**
   * Overrides EntityAPIController::access().
   */
  public function access($op, $entity = NULL, $account = NULL) {
    if ($op !== 'create' && !$entity) {
      return FALSE;
    }
    if ($op === 'delete' && $entity->locked) {
      return FALSE;
    }
    // The administer permission is a blanket override.
    if (user_access('crm bypass access')) {
      return TRUE;
    }
    switch ($op) {
      case 'create':
        return user_access('crm message template create');
      case 'view':
        return user_access('crm message template view');
      case 'update':
        return user_access('crm message template update');
      case 'delete':
        return user_access('crm message template delete');
    }
    return FALSE;
  }

  /**
   * Overrides EntityAPIController::create().
   */
  public function create(array $values = array()) {
    $values += array(
      'language' => LANGUAGE_NONE,
      'locked' => FALSE,
    );
    return parent::create($values);
  }

  /**
   * Overrides EntityAPIController::save().
   */
  public function save($entity) {

    // If we are going to save new message data needs to be validated against
    // uniqueness.
    if (isset($entity->is_new) && $entity->is_new == TRUE && !isset($entity->template_id)) {
      $entity->created = REQUEST_TIME;
    }
    // Set changed time arbitrary.
    $entity->changed = REQUEST_TIME;

    // Create new revision by default.
    if (!isset($entity->revision)) {
      $entity->revision = TRUE;
    }

    // Save message.
    return parent::save($entity);
  }

  /**
   * Overrides DrupalDefaultEntityController::saveRevision().
   */
  protected function saveRevision($entity) {
    $entity->revision_timestamp = REQUEST_TIME;
    $entity->revision_uid = $GLOBALS['user']->uid;
    return parent::saveRevision($entity);
  }

}