<?php
/**
 * @file
 * Question type, enabling the creation of drag drop type of questions.
 * 
 * The main classes for the quiz_drag_drop question type.
 *
 * These inherit or implement code found in quiz_question.classes.inc.
 *
 * Based on:
 * Other question types in the quiz framework.
 */

/**
 * Extension of QuizQuestion.
 */
class DragDropQuestion extends QuizQuestion {

  /**
   * Run check_markup() on the field of the specified choice alternative.
   * 
   * @param int $alternativeIndex
   *   The index of the alternative in the alternatives array.
   * @param varchar $field
   *   The name of the field we want to check markup on.
   * @param Boolean $check_user_access
   *   Whether or not to check for user access to the filter we're trying to 
   * apply.
   * 
   * @return HTML
   *   HTML markup.
   */
  private function checkMarkup($alternativeIndex, $field, $check_user_access = FALSE) {
    $alternative = $this->node->alternatives[$alternativeIndex];
    return check_markup($alternative[$field]['value'], $alternative[$field]['format']);
  }

  /**
   * Implementation of save.
   *
   * Stores the question in the database.
   *
   * @param Boolean $is_new 
   *   if - if the node is a new node...
   * (non-PHPdoc)
   * 
   * @see sites/all/modules/quiz-HEAD/question_types/quiz_question/QuizQuestion#save()
   */
  public function saveNodeProperties($is_new = FALSE) {
    // TODO.
  }
  /**
   * Implementation of validate.
   *
   * QuizQuestion#validate()
   */
  public function validateNode(array &$form) {
    // For node level validation.
    $title_error = FALSE;
    $file_upload_delta = $form['field_dragdrop_image'][LANGUAGE_NONE]['#file_upload_delta'];

    if ($file_upload_delta > 0) {
      for ($i = 0; $i < $file_upload_delta; $i++) {
        if ($form['field_dragdrop_image'][LANGUAGE_NONE][$i]['#value']['title'] == '') {
          $title_error = TRUE;
        }
      }
    }

    if ($title_error === TRUE) {
      form_set_error(t('image_uploaded_title'), t('Please provide title for all the images uploaded. All the titles will become placeholders.'));
    }
  }

  /**
   * Implementation of delete.
   *
   * @see QuizQuestion#delete()
   */
  public function delete($only_this_version = FALSE) {
    if ($only_this_version) {
      db_delete('quiz_drag_drop_user_answers')
        ->condition('question_nid', $this->node->nid)
        ->condition('question_vid', $this->node->vid)
        ->execute();
    }
    // Delete all versions of this question.
    else {
      db_delete('quiz_drag_drop_user_answers')
        ->condition('question_nid', $this->node->nid)
        ->execute();
    }
    parent::delete($only_this_version);
  }

  /**
   * Implementation of getNodeProperties.
   *
   * @see QuizQuestion#getNodeProperties()
   */
  public function getNodeProperties() {
    if (isset($this->nodeProperties) && !empty($this->nodeProperties)) {
      return $this->nodeProperties;
    }
    $props = parent::getNodeProperties();

    return $props;
  }

  /**
   * Implementation of getNodeView.
   *
   * @see QuizQuestion#getNodeView()
   */
  public function getNodeView() {
    $content = parent::getNodeView();

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
    list($matches, $images) = $this->getSubquestions();

    $matches = $this->customShuffle($matches);
    $images = $this->customShuffle($images);

    $data = array('placeholder' => $matches, 'images' => $images);
    $form['drag_drop_answer'] = array('#markup' => theme('quiz_drag_drop_answer_form', array('data' => $data)));
    $form['answerCount'] = array(
      '#type' => 'hidden',
      '#value' => '',
      '#name' => 'answerCount',
      '#attributes' => array('id' => 'answerCount'));
    $form['dropCount'] = array(
      '#type' => 'hidden',
      '#value' => '',
      '#name' => 'dropCount',
      '#attributes' => array('id' => 'dropCount'));
    $form['tries'] = array(
      '#type' => 'hidden',
      '#value' => 0,
    );
    $form['reset'] = array(
      '#type' => 'button',
      '#value' => t('Reset'),
      '#attributes' => array('class' => array('reset_btn')),
      '#id' => 'btnReset',
    );
    return $form;
  }

  /**
   * Helper function to generate question images.
   * 
   * @param array $variables
   *   Holds image related settings.
   *
   * @return HTML
   *   HTML of image.
   */
  private function imageStyle($variables) {
    // Determine the dimensions of the styled image.
    $dimensions = array(
      //'width' => '',
      'height' => 70,
    );

    image_style_transform_dimensions($variables['style_name'], $dimensions);

    //$variables['width'] = $dimensions['width'];
    $variables['height'] = $dimensions['height'];

    $variables['attributes'] = array(
      'class' => 'draggable',
      'id' => 'image_' . $variables['fid'],
    );

    // Determine the url for the styled image.
    $variables['path'] = image_style_url($variables['style_name'], $variables['path']);
    return theme('image', $variables);
  }

  /**
   * Helper function to fetch subquestions.
   *
   * @return array
   *   Array with two arrays, matches and selected options
   */
  private function getSubquestions() {
    $title = $image = array();
    $node_detail = node_load($this->node->nid);
    foreach ($node_detail->field_dragdrop_image[LANGUAGE_NONE] as $key => $val) {
      $style = 'thumbnail';
      $path = $val['uri'];
      $fid = $val['fid'];

      $data = array('style_name' => $style, 'path' => $path, 'fid' => $fid);

      $title[] = array(
        'fid' => $val['fid'],
        'title' => $val['title'],
        'uri' => $this->imageStyle($data),
      );

      $image[] = array(
        'fid' => $val['fid'],
        'title' => $val['title'],
        'uri' => $this->imageStyle($data),
      );
    }
    return array($title, $image);
  }

  /**
   * Shuffles an array and makes sure the first element is the default element.
   *
   * @param array $array
   *   Array to be shuffled
   * 
   * @return array
   *   A shuffled version of the array with $array['def'] = '' as the first 
   * element.
   */
  private function customShuffle(array $array = array()) {
    $new_array = array();

    while (count($array)) {
      $element = array_rand($array);
      $new_array[$element] = $array[$element];
      unset($array[$element]);
    }
    return $new_array;
  }

  /**
   * Implementation of getCreationForm.
   *
   * @see QuizQuestion#getCreationForm()
   */
  public function getCreationForm(array &$form_state = NULL) {
    $form = array();

    return $form;
  }

  /**
   * Implementation of getMaximumScore.
   *
   * @see QuizQuestion#getMaximumScore()
   */
  public function getMaximumScore() {
    return 1;
  }
}

/**
 * Extension of QuizQuestionResponse
 */
class DragDropResponse extends QuizQuestionResponse {
  /**
   * Constructor.
   */
  public function __construct($result_id, stdClass $question_node, $tries = NULL) {
    parent::__construct($result_id, $question_node, $tries);
  }

  /**
   * Implementation of isValid.
   *
   * @see QuizQuestionResponse#isValid()
   */
  public function isValid() {

    $drop_count = $_POST['dropCount'];
    if ($drop_count != count($this->question->field_dragdrop_image[LANGUAGE_NONE])) {
      return t('You must drop all the image into placeholders.');
    }
    return TRUE;
  }

  /**
   * Implementation of save.
   *
   * @see QuizQuestionResponse#save()
   */
  public function save() {

    if (isset($_POST['dropCount']) && !empty($_POST['dropCount'])) {
      $drop_count = $_POST['dropCount'];
    }
    if (isset($drop_count) && $drop_count == count($this->question->field_dragdrop_image[LANGUAGE_NONE])) {
      $this->answer_id = db_insert('quiz_drag_drop_user_answers')
        ->fields(array(
          'question_nid' => $this->question->nid,
          'question_vid' => $this->question->vid,
          'result_id' => $this->rid,
          'score' => (int) $this->getScore(),
        ))
        ->execute();
    }
  }

  /**
   * Implementation of delete.
   *
   * @see QuizQuestionResponse#delete()
   */
  public function delete() {
	db_delete('quiz_drag_drop_user_answers')
			->condition('result_id', $this->rid)
			->condition('question_nid', $this->question->nid)
			->condition('question_vid', $this->question->vid)
			->execute();
  }

  /**
   * Implementation of score.
   *
   * @return int
   *   Calculates score for the user.
   *
   * @see QuizQuestionResponse#score()
   */
  public function score() {
    $score = 0;
    if (isset($_POST['answerCount']) && !empty($_POST['answerCount'])) {
      $answer_count = $_POST['answerCount'];

      $score = 0;

      if ($answer_count == count($this->question->field_dragdrop_image[LANGUAGE_NONE])) {
        $score = 1;
      }
    }
    else {
      $result = db_query('SELECT score FROM {quiz_drag_drop_user_answers} 
                          WHERE result_id = :result_id AND 
                                question_nid = :question_nid AND
                                question_vid = :question_vid',
                array(
                  ':result_id' => $this->rid,
                  ':question_nid' => $this->question->nid,
                  ':question_vid' => $this->question->vid))->fetchField();

      if (!$result) {
        return;
      }

      $score = $result;
    }

    return $score;
  }

  /**
   * If all answers in a question is wrong.
   *
   * @return Boolean
   *   TRUE if all answers are wrong. False otherwise.
   */
  public function isAllWrong() {
    return TRUE;
  }

  /**
   * Implementation of getResponse.
   *
   * @see QuizQuestionResponse#getResponse()
   */
  public function getResponse() {
    // TODO.
  }

  /**
   * Implementation of getReportFormResponse.
   *
   * @see getReportFormResponse()
   */
  public function getReportFormResponse($showpoints = TRUE, $showfeedback = TRUE, $allow_scoring = FALSE) {
    $score = (int) $this->getScore();
    $data = array('score' => $score, 'is_skipped' => $this->is_skipped);
    // Return themed report.
    return array('#markup' => theme('quiz_drag_drop_response', array('data' => $data)));
  }

  /**
   * Run check_markup() on the field of the specified choice alternative.
   *
   * @param String $alternative
   *   String to be checked
   * @param String $format
   *   The input format to be used
   * @param Boolean $check_user_access
   *   Whether or not we are to check the users access to the chosen format
   * 
   * @return HTML
   *   HTML markup
   */
  private function checkMarkup($alternative, $format, $check_user_access = FALSE) {
    // If the string is empty we don't run it through input
    // filters(They might add empty tags).
    if (drupal_strlen($alternative) == 0) {
      return '';
    }
    return check_markup($alternative, $format, $langcode = '' /* TODO Set this variable. */, $check_user_access);
  }
}
