<?php

/**
 * @file
 * Defines the different Guideme tours.
 */

/**
 * Implements hook_guideme_path().
 */
function opigno_lms_tour_guideme_path() {
  return array(
    'opigno_lms_intro' => array(
      'weight' => -100,
      'steps' => array(
        '<front>' => array(
          array(
            'title' => t("Welcome !"),
            'description' => t("Welcome to Opigno LMS! We will show you around and help you get started working with this amazing tool. If you want to start exploring by yourself and dismiss this guide, just click on the 'x' icon in the top right corner."),
			'button_label' => t("OK"),
          ),
          array(
            'title' => t("This is the dashboard"),
            'description' => t("Opigno provides a custom dashboard for each user. Here you can add or remove blocks, drag them around, etc. Give it a try."),
            'target' => '#homebox',
			'button_label' => t("OK"),
            'options' => array(
              'tooltip_location' => 'top',
            ),
          ),
          array(
            'title' => t("This is the main navigation"),
            'description' => t("Here you can quickly jump to the main parts of Opigno."),
            'target' => '#main-navigation-wrapper',
            'button_label' => t("OK"),
			'options' => array(
              'tooltip_location' => 'right',
            ),
          ),
		  array(
            'title' => t("Course catalogue"),
            'description' => t("In the course catalogue you can see and subscribe to all courses you are <strong>not</strong> already a part of."),
            'target' => '#main-navigation-item-training-catalogue',
            'button_label' => t("OK"),
          ),
		  array(
            'title' => t("My courses"),
            'description' => t("When clicking on 'My courses' button you will find all courses you are already member of, and, as an admin, you will be able to create new courses.<br />Let's click on this button to start creating your first course."),
            'target' => '#main-navigation-item-my-courses',
            'button_label' => t("Done"),
          ),	  
        ),
        'admin/opigno' => array(
          array(
            'title' => t("This is the Opigno administration"),
            'description' => t("This is where you can administer all aspects of Opigno."),
          ),
          array(
            'title' => t("Course administration"),
            'description' => t("Click here to go to the course administration."),
            'target' => 'a[href="' . base_path() . 'admin/opigno/content/course-administration"]',
            'button_label' => t("Done"),
            'options' => array(
              'tooltip_location' => 'left',
            ),
          ),
		  array(
            'title' => t("User management"),
            'description' => t("Click here to manage the users at platform level."),
            'target' => 'a[href="' . base_path() . 'admin/opigno/system/users"]',
            'button_label' => t("Done"),
            'options' => array(
              'tooltip_location' => 'right',
            ),
          ),
		  array(
            'title' => t("Display settings"),
            'description' => t("Click here to manage the display settings of the platform."),
            'target' => 'a[href="' . base_path() . 'admin/opigno/appearance/settings"]',
            'button_label' => t("Done"),
            'options' => array(
              'tooltip_location' => 'left',
            ),
          ),
        ),
        'admin/opigno/content/course-administration' => array(
          array(
            'title' => t("This is the Opigno course administration"),
            'description' => t("This is where you can administer all Opigno courses."),
          ),
          array(
            'title' => t("Add a new course"),
            'description' => t("Click here to create a new course."),
            'target' => '.action-links .add-course',
            'button_label' => t("Done"),
            'options' => array(
              'tooltip_location' => 'bottom',
            ),
          ),
        ),
		'my-courses' => array(
          array(
            'title' => t("My courses interface"),
            'description' => t("This is the interface where you will find all courses you are member of."),
          ),
		  array(
            'title' => t("Category"),
            'description' => t("You can group courses by category which makes possible to filter them in the list."),
            'target' => '#edit-opigno-course-categories-tid-wrapper',
            'button_label' => t("Done"),
            'options' => array(
              'tooltip_location' => 'right',
            ),
          ),
          array(
            'title' => t("Add a new course"),
            'description' => t("Click here to create a new course."),
            'target' => '.opigno-simple-ui-course-administration-add-course-link',
            'button_label' => t("Done"),
            'options' => array(
              'tooltip_location' => 'bottom',
            ),
          ),
        ),
        'node/add/course' => array(
          array(
            'title' => t("Here you can create your course"),
            'description' => t("Start by giving it a title."),
            'target' => 'input[name="title"]',
            'options' => array(
              'tooltip_location' => 'top',
            ),
          ),
          array(
            'title' => t("Give it a description"),
            'description' => t("A description helps students understand what the course is about."),
            'target' => '#edit-body',
            'options' => array(
              'tooltip_location' => 'top',
            ),
          ),
          array(
            'title' => t("Choose this course availability"),
            'description' => t("A public course can be viewed by anyone, even anonymous visitors. A semi-public course requires to first create an account or to authenticate before being able to subscribe. Subscriptions to private courses can only be done by the teacher or an admin."),
            'target' => '#edit-group-access-und-0',
            'options' => array(
              'tooltip_location' => 'left',
            ),
          ),
          array(
            'title' => t("Choose this course tools"),
            'description' => t("This field allows you to choose which tools are available for this course. You can change this setting later as well. The more additional modules you will install, the more tool will appear here (for ex. video gallery, audio gallery, etc.). For this guided tour, please activate the Lesson tool."),
            'target' => '.form-item-opigno-course-tools-und',
            'options' => array(
              'tooltip_location' => 'right',
            ),
          ),
          array(
            'title' => t("Save the course"),
            'description' => t("There are many more options, but you can explore them later. Let's save it."),
            'target' => '#edit-submit',
			'button_label' => t("Done"),
            'options' => array(
              'tooltip_location' => 'bottom',
            ),
          ),
        ),
        'course/*/*' => array(
          array(
            'title' => t("This is the main page of your course"),
            'description' => t("It presents the course description and the tools you enabled just before."),
          ),
		  array(
            'title' => t("This bloc summarizes the course characteristics"),
			'description' => t(""),
            'target' => '.node-course-more-info',
			'button_label' => t("Done"),
            'options' => array(
              'tooltip_location' => 'left',
            ),
          ),
		  array(
            'title' => t("Clicking here allows to define course settings"),
			'description' => t(""),
            'target' => '.platon-og-context-settings-tab',
			'button_label' => t("Done"),
            'options' => array(
              'tooltip_location' => 'bottom',
            ),
		  ),		  
		  array(
            'title' => t("Clicking here allows to manage course members"),
			'description' => t(""),
            'target' => '.platon-og-context-users-tab',
			'button_label' => t("Done"),
            'options' => array(
              'tooltip_location' => 'bottom',
            ),
		  ),
		  array(
            'title' => t("Let's create your first lesson for this course"),
			'description' => t("To do that, simply click on the 'Lesson' tool."),
            'target' => '.opigno-quiz-tool',
			'button_label' => t("Done"),
            'options' => array(
              'tooltip_location' => 'top',
            ),
		  ),
        ),
		'node/*/quizzes' => array (
		  array(
            'title' => t("This is the page listing all the lessons of the course"),
            'description' => t("As an admin you can create lessons and sort them into this list."),
          ),
		  array(
            'title' => t("Let's create your first lesson"),
			'description' => t("Please click on the 'Add new lesson' button."),
            'target' => '.opigno-quiz-app-add-quiz',
			'button_label' => t("Done"),
            'options' => array(
              'tooltip_location' => 'bottom',
            ),
          ),
		),
		'node/add/quiz' => array (
		  array(
            'title' => t("Creating a lesson is very easy."),
            'description' => t("For this first lesson we will create a quiz composed of a multiple choice question. The interface proposes many settings, that you will be able to discover later. We will concentrate on a simple example for this guided tour."),
          ),
		  array(
            'title' => t("Start by giving it a title."),
            'description' => t(" "),
            'target' => 'input[name="title"]',
            'options' => array(
              'tooltip_location' => 'bottom',
            ),
          ),
          array(
            'title' => t("Give it a description"),
            'description' => t("A description helps students understand what the lesson is about."),
            'target' => '#edit-body',
            'options' => array(
              'tooltip_location' => 'top',
            ),
		  ),
		  array(
            'title' => t("Choose a category"),
            'description' => t("This helps students understand if it's a theoretical lesson or an assessment. The questions proposed inside the lesson are filtered according to this typology (for ex. theoretical lessons can only contain slides). Since we want to create a multiple choice question, let's choose quiz."),
            'target' => '#edit-quiz-type',
            'options' => array(
              'tooltip_location' => 'left',
            ),
		  ),
		  array(
            'title' => t("Save the lesson"),
            'description' => t("There are many more options, but you can explore them later. Let's save it."),
            'target' => '#edit-submit',
			'button_label' => t("Done"),
            'options' => array(
              'tooltip_location' => 'bottom',
            ),
          ),
		),
		'node/*/questions' => array (
		  array(
            'title' => t("This button allows to modify the settings of the lesson you just created"),
            'description' => t(""),
			'target' => '#tabs .node-edit-tab',
			'options' => array(
              'tooltip_location' => 'bottom',
            ),
          ),
		  array(
            'title' => t("This button allows to manage the questions (or steps) inside the lesson"),
            'description' => t(""),
			'target' => '.node-tab .active',
			'options' => array(
              'tooltip_location' => 'bottom',
            ),
          ),
		  array(
            'title' => t("You can see here all the questions you added to this lesson."),
            'description' => t(""),
			'target' => '#mq-fieldset',
			'options' => array(
              'tooltip_location' => 'left',
            ),
          ),
		  array(
            'title' => t("Each question created will be stored inside a pool in order to be available for other lessons."),
            'description' => t("You can select here questions previously created and simply adding them to this lesson by checking them."),
			'target' => '#quiz-browser-target',
			'options' => array(
              'tooltip_location' => 'left',
            ),
          ),
		  array(
            'title' => t("Let's create your first question from scratch."),
            'description' => t("Simply click on 'Create new question' to expand it."),
			'target' => '#tabs',
			'options' => array(
              'tooltip_location' => 'top',
            ),
          ),
		  array(
            'title' => t("You can see here all question types available."),
            'description' => t("To create a multiple choice question (as proposed in this guided tour), simply click on 'Multiple choice question'."),
			'target' => '.add-questions',
			'options' => array(
              'tooltip_location' => 'right',
            ),
          ),
		),
		'node/add/multichoice' => array (
		   array(
            'title' => t("Enter the question text here."),
            'description' => t(""),
			'target' => '#edit-body',
			'options' => array(
              'tooltip_location' => 'top',
            ),
          ),
		  array(
            'title' => t("You can define some additional settings here."),
            'description' => t("If there is more than one correct answer to your question, check the option 'Multiple answers'. If you want to have the answers displayed in a random order, check the corresponding option."),
			'target' => '#edit-alternatives-settings',
			'options' => array(
              'tooltip_location' => 'top',
            ),
          ),
		  array(
            'title' => t("Enter the first alternative answer here."),
            'description' => t(""),
			'target' => '.form-item-alternatives-0-answer-value',
			'options' => array(
              'tooltip_location' => 'top',
            ),
          ),
		  array(
            'title' => t("If this alternative is correct, check here."),
            'description' => t(""),
			'target' => '#edit-alternatives-0-correct',
			'options' => array(
              'tooltip_location' => 'bottom',
            ),
          ),
		  array(
            'title' => t("Enter the second alternative here."),
            'description' => t(""),
			'target' => '.form-item-alternatives-1-answer-value',
			'options' => array(
              'tooltip_location' => 'top',
            ),
          ),
		  array(
            'title' => t("If this alternative is correct, check here."),
            'description' => t(""),
			'target' => '#edit-alternatives-1-correct',
			'options' => array(
              'tooltip_location' => 'bottom',
            ),
          ),
		  array(
            'title' => t("If you want to add more alternative answers, click here."),
            'description' => t(""),
			'target' => '#edit-alternatives-multichoice-add-alternative',
			'options' => array(
              'tooltip_location' => 'bottom',
            ),
          ),
		  array(
            'title' => t("Then save the question"),
            'description' => t(""),
			'target' => '#edit-submit',
			'options' => array(
              'tooltip_location' => 'bottom',
            ),
          ),
		),
	  ),
    ),
  );
}
