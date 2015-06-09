<?php


/**
 * The main classes for the multichoice question type.
 *
 * These inherit or implement code found in quiz_question.classes.inc.
 * Code: LogicMedia
 *
 * Based on:
 * Other question types in the quiz framework.
 *
 *
 *
 * @file
 * Question type, enabling the creation of multiple choice and multiple answer questions.
 */

/**
 * Extension of QuizQuestion.
 */
class QuizfileuploadQuestion extends QuizQuestion {

  /**
   * Implementation of save
   *
   * Stores the question in the database.
   *
   * @param is_new if - if the node is a new node...
   * (non-PHPdoc)
   * @see sites/all/modules/quiz-HEAD/question_types/quiz_question/QuizQuestion#save()
   */

  public function saveNodeProperties($is_new = FALSE) {
    $is_new = $is_new || $this->node->revision == 1;
    if ($is_new) {
      db_insert('quiz_fileupload_node_properties')
        ->fields(array(
          'nid' => $this->node->nid,
          'vid' => $this->node->vid,
          'filetypes' => $this->node->filetypes,
          'type' => $this->node->quizfileupload_scoring[LANGUAGE_NONE][0]['value'],
        ))
        ->execute();
    }
    else {
      db_update('quiz_fileupload_node_properties')
        ->fields(array(
          'filetypes' => $this->node->filetypes,
          'type' => $this->node->quizfileupload_scoring[LANGUAGE_NONE][0]['value']
        ))
        ->condition('nid', $this->node->nid)
        ->condition('vid', $this->node->vid)
        ->execute();
    }
  }

  /**
   * Implementation of validate
   *
   * QuizQuestion#validate()
   */
  public function validateNode(array &$form) {
    //no validation required
  }

  /**
   * Implementation of delete
   *
   * @see QuizQuestion#delete()
   */
  public function delete($only_this_version = FALSE) {
    if ($only_this_version) {
      db_delete('quiz_fileupload_node_properties')
        ->condition('question_nid', $this->node->nid)
        ->condition('question_vid', $this->node->vid)
        ->execute();
      db_delete('quiz_fileupload_user_answers')
        ->condition('nid', $this->node->nid)
        ->condition('vid', $this->node->vid)
        ->execute();
    }
    else {
      db_delete('quiz_fileupload_node_properties')
        ->condition('nid', $this->node->nid)
        ->execute();
      db_delete('quiz_fileupload_user_answers')
        ->condition('question_nid', $this->node->nid)
        ->execute();
    }
    parent::delete($only_this_version);
  }

  /**
   * Implementation of getNodeProperties
   *
   * @see QuizQuestion#getNodeProperties()
   */
  public function getNodeProperties() {
    if (isset($this->nodeProperties)) {
      return $this->nodeProperties;
    }
    $props = parent::getNodeProperties();

    // Load the properties
    $res_a = db_query('SELECT filetypes FROM {quiz_fileupload_node_properties} WHERE nid = :nid AND vid = :vid',
      array(
        ':nid' => $this->node->nid,
        ':vid' => $this->node->vid
      ))->fetchAssoc();

    if (is_array($res_a)) {
      $props = array_merge($props, $res_a);
    }
    $this->nodeProperties = $props;
    return $props;
  }

  /**
   * Implementation of getNodeView
   *
   * @see QuizQuestion#getNodeView()
   */
  public function getNodeView() {
    $content = parent::getNodeView();
    $content['filetypes'] = array(
      '#type' => 'markup',
      '#value' => '<pre>' . check_plain($this->node->filetypes) . '</pre>',
    );
    return $content;
  }

  /**
   * Generates the question form.
   *
   * This is called whenever a question is rendered, either
   * to an administrator or to a quiz taker.
   */
  public function getAnsweringForm(array $form_state = NULL, $rid) {
    $form = parent::getAnsweringForm($form_state, $rid);
    $fid = db_query('SELECT qf.fid
      FROM {quiz_fileupload_user_answers} qf
      WHERE question_nid = :nid AND question_vid = :vid AND result_id = :result_id',
      array(':nid' => $this->node->nid, ':vid' => $this->node->vid, ':result_id' => $rid))
      ->fetchField();

    if (is_numeric($fid)) {
      $form['previous_upload'] = array(
        '#title' => t('Previous upload'),
        '#type' => 'item',
        '#markup' => quiz_file_markup($fid),
        '#description' => t('<strong>Upload a new file to replace previous upload.</strong>')
      );
    }
    $form['tries'] = array(
      '#type' => 'file',
      '#title' => t('Upload'),
      '#description' => t('Allowed extensions !ext', array('!ext' => $this->node->filetypes)),
    );
    return $form;
  }

  /**
   * Implementation of getCreationForm
   *
   * @see QuizQuestion#getCreationForm()
   */
  public function getCreationForm(array &$form_state = NULL) {
    $allowed = variable_get('quizfileupload_default_extensions', QUIZFILEUPLOAD_DEFAULT_EXTENSIONS);
    $form['filetypes'] = array(
      '#type' => 'textfield',
      '#title' => t('Allowed extension'),
      '#description' => t('Enter the allowed file extensions one per line.'),
      '#default_value' => isset($this->node->filetypes) ? $this->node->filetypes : $allowed,
      '#required' => TRUE,
    );
    return $form;
  }

  /**
   * Implementation of getMaximumScore
   *
   * @see QuizQuestion#getMaximumScore()
   */
  public function getMaximumScore() {
    return variable_get('quizfileupload_default_score', 5);
  }

}

/**
 * Extension of QuizQuestionResponse
 */
class QuizfileuploadResponse extends QuizQuestionResponse {
  /**
   * ID of the answer.
   */
  protected $answer_id = 0;
  protected $file=null;

  /**
   * Constructor
   */
  public function __construct($result_id, stdClass $question_node, $tries = NULL) {
    parent::__construct($result_id, $question_node, $tries);
    $tries = $_FILES;
    $this->answer = $tries;
    $this->answer_feedback="";
    if (!isset($result) || !is_object($result)) {
      $result = new stdClass;
    }
    $result->is_correct = TRUE;
    $this->evaluated = 0;
    $response = $this->getResponse();
    if (isset($question_node->quizfileupload_scoring[LANGUAGE_NONE][0]['value'])) {
      if ($question_node->quizfileupload_scoring[LANGUAGE_NONE][0]['value'] == 0) {
        $this->evaluated = 1;
      }
    }
    $this->result_id = $result_id;
    // Question has been answered allready. We fetch the answer data from the database.
    $r = db_query('SELECT * FROM {quiz_fileupload_user_answers}
    WHERE question_nid = :question_nid AND question_vid = :question_vid AND result_id = :result_id',
      array(
        ':question_nid' => $question_node->nid,
        ':question_vid' => $question_node->vid,
        ':result_id' => $result_id
      ))->fetchAssoc();
    if (is_array($r)) {
      $this->score = $r['score'];
      $this->answer_id = $r['answer_id'];
      $this->evaluated = $r['is_evaluated'];
      $this->answer_feedback=$r['answer_feedback'];
    }
  }

  /**
   * Implementation of isValid
   *
   * @see QuizQuestionResponse#isValid()
   */
  public function isValid() {
    if (isset($this->file->fid)) {
      return TRUE;
    }
    else {
      return "";
    }
  }

  /**
   * Implementation of save
   *
   * @see QuizQuestionResponse#save()
   */
  public function save() {
    $validator = array(
      'file_validate_extensions' => array($this->question->filetypes),
    );
    $this->file = file_save_upload('tries', $validator, 'public://');
    if (isset($this->file->fid)) {
      $this->answer_id = db_insert('quiz_fileupload_user_answers')
        ->fields(array(
          'result_id' => $this->rid,
          'question_vid' => $this->question->vid,
          'question_nid' => $this->question->nid,
          'fid' => $this->file->fid,
          'score' => $this->getScore(FALSE),
          'is_evaluated' => $this->evaluated,
          'answer_feedback' => $this->answer_feedback,
        ))
        ->execute();
    }
  }

  /**
   * Implementation of delete
   *
   * @see QuizQuestionResponse#delete()
   */
  public function delete() {
    db_delete('quiz_fileupload_user_answers')
      ->condition('question_nid', $this->question->nid)
      ->condition('question_vid', $this->question->vid)
      ->condition('result_id', $this->rid)
      ->execute();
  }

  /**
   * Implementation of score
   *
   * @return uint
   *
   * @see QuizQuestionResponse#score()
   */
  public function score() {
    if ($this->question->quizfileupload_scoring[LANGUAGE_NONE][0]['value'] == 1) {
      $score = db_query('SELECT score FROM {quiz_fileupload_user_answers} WHERE result_id = :result_id AND question_vid = :question_vid', array(
        ':result_id' => $this->rid,
        ':question_vid' => $this->question->vid
      ))->fetchField();
      if (!$score) {
        $score = 0;
      }
    }
    else {
      $shortAnswer = new QuizfileuploadQuestion($this->question);
      $score = $shortAnswer->getMaximumScore();
    }
    return $score;
  }

  /**
   * Implementation of getResponse
   *
   * @return answer
   *
   * @see QuizQuestionResponse#getResponse()
   */
  public function getResponse() {
    return $this->answer;
  }

  /**
   * Implementation of getReportFormResponse
   *
   * @see getReportFormResponse($showpoints, $showfeedback, $allow_scoring)
   */
  public function getReportFormResponse($showpoints = TRUE, $showfeedback = TRUE, $allow_scoring = FALSE) {
    $result_id = $this->question->answers[0]['result_id'];
    $fid = db_query('SELECT f.fid
      FROM {file_managed} f
      INNER JOIN {quiz_fileupload_user_answers} qf ON (f.fid = qf.fid)
      WHERE result_id = :result_id AND question_nid = :question_nid AND question_vid = :question_vid',
      array(
        ':result_id' => $result_id,
        ':question_nid' => $this->question->nid,
        ':question_vid' => $this->question->vid
      ))
      ->fetchField();
    $markup = quiz_file_markup($fid);
    if ($this->question && !empty($this->question->answers)) {
      $answer = (object) current($this->question->answers);
    }

    $form['fileupload'] = array('#markup' => $markup);
    if ($answer->is_evaluated == 1) {
      // Show feedback, if any.
      $form['answer_feedback'] = array(
        '#title' => t('Feedback'),
        '#type' => 'item',
        '#markup' => '<span class="quiz_answer_feedback">' . $this->answer_feedback . '</span>',
      );
    }
    else {
      $feedback = t('This answer has not yet been scored.') .
        '<br/>' .
        t('Until the answer is scored, the total score will not be correct.');
    }
    return $form;
  }


  public function getReportFormScore($showfeedback = TRUE, $showpoints = TRUE, $allow_scoring = FALSE) {
    $node = node_load($this->question->nid);
    $score = ($this->isEvaluated()) ? $this->getScore() : '?';
    if (quiz_access_to_score() && $allow_scoring && ($node->quizfileupload_scoring[LANGUAGE_NONE][0]['value'] == 1)) {
      return array(
        '#type' => 'textfield',
        '#default_value' => $score,
        '#size' => 3,
        '#maxlength' => 3,
        '#attributes' => array('class' => array('quiz-report-score')),
      );
    }
    else {
      return array(
        '#markup' => $score,
      );
    }
  }


  public function getReportFormAnswerFeedback($showpoints = TRUE, $showfeedback = TRUE, $allow_scoring = FALSE) {
    if (quiz_access_to_score() && $allow_scoring) {
      return array(
        '#title' => t('Enter feedback'),
        '#type' => 'textarea',
        '#default_value' => $this->answer_feedback,
        '#attributes' => array('class' => array('quiz-report-score')),
      );
    }
    return FALSE;
  }

  /**
   * Implementation of getReportFormSubmit
   *
   * @see QuizQuestionResponse#getReportFormSubmit($showfeedback, $showpoints, $allow_scoring)
   */
  public function getReportFormSubmit($showfeedback = TRUE, $showpoints = TRUE, $allow_scoring = FALSE) {
    $node = node_load($this->question->nid);
    if (isset($node->quizfileupload_scoring[LANGUAGE_NONE][0]['value'])) {
      if (quiz_access_to_score() && $allow_scoring && ($node->quizfileupload_scoring[LANGUAGE_NONE][0]['value'] == 1)) {
        return $allow_scoring ? 'quizfileupload_report_submit' : FALSE;
      }
    }
    return FALSE;
  }

  /**
   * Implementation of getReportFormValidate
   *
   * @see QuizQuestionResponse#getReportFormValidate($showfeedback, $showpoints, $allow_scoring)
   */
  public function getReportFormValidate($showfeedback = TRUE, $showpoints = TRUE, $allow_scoring = FALSE) {
    $node = node_load($this->question->nid);
    if (isset($node->quizfileupload_scoring[LANGUAGE_NONE][0]['value'])) {
      if (quiz_access_to_score() && $allow_scoring && ($node->quizfileupload_scoring[LANGUAGE_NONE][0]['value'] == 1)) {
        return $allow_scoring ? 'quizfileupload_report_validate' : FALSE;
      }
    }
    return FALSE;
  }
}

function quiz_file_markup($fid) {

  if (is_numeric($fid)) {
    // image check
    $file = file_load($fid);
    $errors = file_validate_is_image($file);

    // not image
    if (count($errors)) {
      return l($file->filename, file_create_url($file->uri));
    }
    // image, we use thumbnail
    else {
      $variables['item'] = array(
        'uri' => $file->uri,
        'alt' => '',
        'title' => $file->filename
      );
      $variables['path'] = array(
        'path' => file_create_url($file->uri),
        'options' => array(
          'html' => TRUE
        )
      );
      $variables['image_style'] = 'large';
      return theme('image_formatter', $variables);
    }
  }
  // no file
  else {
    return t('n/a');
  }
}
