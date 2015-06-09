api = 2
core = 7.x

projects[drupal][version] = 7.27

projects[opigno_lms][type]             = profile
projects[opigno_lms][download][type]   = git
projects[opigno_lms][download][branch] = 7.x-1.x

; Opigno modules ===============================================================

projects[opigno][type]               = module
projects[opigno][subdir]             = "opigno"
projects[opigno][download][type]     = git
projects[opigno][download][branch]   = 7.x-1.x

projects[opigno_calendar_app][type]    = module
projects[opigno_calendar_app][subdir]  = "opigno"
projects[opigno_calendar_app][download][type] = git
projects[opigno_calendar_app][download][branch] = 7.x-1.x

projects[opigno_certificate_app][type]    = module
projects[opigno_certificate_app][subdir]  = "opigno"
projects[opigno_certificate_app][download][type] = git
projects[opigno_certificate_app][download][branch] = 7.x-1.x

projects[opigno_forum_app][type]    = module
projects[opigno_forum_app][subdir]  = "opigno"
projects[opigno_forum_app][download][type] = git
projects[opigno_forum_app][download][branch] = 7.x-1.x

projects[opigno_messaging_app][type]    = module
projects[opigno_messaging_app][subdir]  = "opigno"
projects[opigno_messaging_app][download][type] = git
projects[opigno_messaging_app][download][branch] = 7.x-1.x

projects[opigno_notifications_app][type]    = module
projects[opigno_notifications_app][subdir]  = "opigno"
projects[opigno_notifications_app][download][type] = git
projects[opigno_notifications_app][download][branch] = 7.x-1.x

projects[opigno_poll_app][type]    = module
projects[opigno_poll_app][subdir]  = "opigno"
projects[opigno_poll_app][download][type] = git
projects[opigno_poll_app][download][branch] = 7.x-1.x

projects[opigno_quiz_import_app][type]    = module
projects[opigno_quiz_import_app][subdir]  = "opigno"
projects[opigno_quiz_import_app][download][type] = git
projects[opigno_quiz_import_app][download][branch] = 7.x-1.x

projects[opigno_class_app][type]    = module
projects[opigno_class_app][subdir]  = "opigno"
projects[opigno_class_app][download][type] = git
projects[opigno_class_app][download][branch] = 7.x-1.x

projects[opigno_quiz_app][type]    = module
projects[opigno_quiz_app][subdir]  = "opigno"
projects[opigno_quiz_app][download][type] = git
projects[opigno_quiz_app][download][branch] = 7.x-1.x

projects[opigno_wt_app][type]    = module
projects[opigno_wt_app][subdir]  = "opigno"
projects[opigno_wt_app][download][type] = git
projects[opigno_wt_app][download][branch] = 7.x-1.x

projects[opigno_course_categories_app][type]    = module
projects[opigno_course_categories_app][subdir]  = "opigno"
projects[opigno_course_categories_app][download][type] = git
projects[opigno_course_categories_app][download][branch] = 7.x-1.x

projects[tft][type]               = module
projects[tft][subdir]             = "opigno"
projects[tft][download][type]     = git
projects[tft][download][branch]   = "7.x-1.x"
projects[tft][download][url]      = "http://git.drupal.org/sandbox/wadmiraal/2071579.git"
projects[tft][download][revision] = 421f84959c9f2899361a8383f17edf36422a99fc


; Opigno themes ================================================================

projects[platon][type]               = theme
projects[platon][download][type]     = git
projects[platon][download][branch]   = "7.x-3.x"

; Third-party modules that need to be patched ==================================

; Quiz
projects[quiz][version] = 4.0-beta2
projects[quiz][subdir]  = "contrib"
projects[quiz][patch][] = "http://drupal.org/files/hide_save_button_when_no_rights_2076853.patch"
;projects[quiz][patch][] = "http://drupal.org/files/quiz.module.correct_delete_access_1529302.patch"
;projects[quiz][patch][] = "http://drupal.org/files/prevent_user_from_clicking_on_question_title_2076873_0.patch"
;projects[quiz][patch][] = "http://drupal.org/files/quiz_question.module.og_quiz-integration.patch"
projects[quiz][patch][] = "http://drupal.org/files/QuizQuestion_FileUpload.patch"
projects[quiz][patch][] = "http://drupal.org/files/issues/modify-quiz-to-lesson-in-ui-strings-2101063-for-4-0-beta2.patch"
projects[quiz][patch][] = "http://drupal.org/files/add_plural_quiz_name-937430-8.patch"
projects[quiz][patch][] = "http://drupal.org/files/issues/quiz_question_render_node_teaser_when_taking_quiz_2133347_2.patch"
projects[quiz][patch][] = "http://drupal.org/files/issues/quiz-questiontostep-2185205-1.patch"
projects[quiz][patch][] = "http://drupal.org/files/issues/quiz_2190283.patch"
projects[quiz][patch][] = "http://drupal.org/files/issues/quiz-2191649_2.patch"
projects[quiz][patch][] = "http://drupal.org/files/issues/quiz-2195239.patch"
projects[quiz][patch][] = "http://drupal.org/files/issues/quiz-2212789.patch"

; Quiz File Upload
projects[quizfileupload][version] = 1.0
projects[quizfileupload][subdir]  = "contrib"
projects[quizfileupload][patch][] = "http://drupal.org/files/adding_manual_scoring_extension_validation_feedback-2092275-5.patch"

; OG
projects[og][version] = 2.6
projects[og][subdir]  = "contrib"
;projects[og][patch][] = "http://drupal.org/files/og_ui.block_subscribtion_programatically-2032775.patch"

; OG Create Permissions
projects[og_create_perms][version] = 1.0
projects[og_create_perms][subdir]  = "contrib"
projects[og_create_perms][patch][] = "http://drupal.org/files/update_to_og2.x_api-2077031-2.patch"

; OG forum
projects[og_forum_D7][version] = 2.0-alpha1
projects[og_forum_D7][subdir]  = "contrib"
projects[og_forum_D7][type] = module
projects[og_forum_D7][patch][] = "http://drupal.org/files/fix-forum-access-1844104-2.patch"
projects[og_forum_D7][patch][] = "http://drupal.org/files/og_forum_D7-change-group_audience_to_gid-1802208.patch"
projects[og_forum_D7][patch][] = "http://drupal.org/files/issues/og_forum_2206711.patch"

; Calendar (prevent warnings)
projects[calendar][subdir]  = "contrib"
projects[calendar][version] = 3.4
projects[calendar][patch][] = "http://drupal.org/files/calendar-php54-1471400-58.patch"

; Rules
projects[rules][subdir]  = "contrib"
projects[rules][version] = 2.6
projects[rules][patch][] = "http://drupal.org/files/system.rules_.inc_.patch"

; Apps
projects[apps][subdir]  = "contrib"
projects[apps][version] = 1.0-beta7
projects[apps][patch][] = "http://drupal.org/files/correct_pdo_error-12-1830680.patch"

; Certificate
projects[certificate][subdir]  = "contrib"
projects[certificate][version] = 2.0

; Third-party modules ==========================================================

; Quiz cloze
projects[cloze][type]               = module
projects[cloze][subdir]             = "contrib"
projects[cloze][download][type]     = git
projects[cloze][download][branch]   = "7.x-1.x"
projects[cloze][download][url]      = "http://git.drupal.org/project/cloze.git"
projects[cloze][download][revision] = e3bb806823e46870e8e0d6dafce2d0b261c024c5
projects[cloze][patch][] = "http://drupal.org/files/issues/cloze_change_question_type_name-2249881-1.patch"

; Quiz drag drop
projects[quiz_drag_drop][subdir]  = "contrib"
projects[quiz_drag_drop][version] = 1.4
projects[quiz_drag_drop][patch][] = "http://drupal.org/files/issues/drag_and_drop-forgivingbox-2249971-1.patch"

projects[admin_menu][subdir] = "contrib"
projects[admin_menu][version] = 3.0-rc5

projects[devel][subdir] = "contrib"
projects[devel][version] = 1.3

projects[ctools][subdir] = "contrib"
projects[ctools][version] = 1.4

projects[views][subdir] = "contrib"
projects[views][version] = 3.7

projects[defaultconfig][subdir] = "contrib"
projects[defaultconfig][version] = 1.0-alpha9

projects[module_filter][subdir]  = "contrib"
projects[module_filter][version] = 1.8

projects[entity][subdir]  = "contrib"
projects[entity][version] = 1.5

projects[entityreference][subdir]  = "contrib"
projects[entityreference][version] = 1.1

projects[entityreference_prepopulate][subdir]  = "contrib"
projects[entityreference_prepopulate][version] = 1.5

projects[token][subdir]  = "contrib"
projects[token][version] = 1.5

projects[multiselect][subdir]  = "contrib"
projects[multiselect][version] = 1.9

projects[crumbs][subdir]  = "contrib"
projects[crumbs][version] = 2.0-beta13

projects[variable][subdir]  = "contrib"
projects[variable][version] = 2.5

projects[i18n][subdir]  = "contrib"
projects[i18n][version] = 1.11

projects[rules_conditional][subdir]  = "contrib"
projects[rules_conditional][version] = 1.0-beta2

projects[features][subdir]  = "contrib"
projects[features][version] = 2.0

projects[og_massadd][subdir]  = "contrib"
projects[og_massadd][version] = 1.0-beta2

projects[og_quiz][subdir]  = "contrib"
projects[og_quiz][version] = 1.1

projects[wysiwyg][subdir]  = "contrib"
projects[wysiwyg][version] = 2.2

projects[wysiwyg_template][subdir]  = "contrib"
projects[wysiwyg_template][version] = 2.11

projects[wysiwyg_filter][subdir]  = "contrib"
projects[wysiwyg_filter][version] = 1.6-rc2

projects[imce][subdir]  = "contrib"
projects[imce][version] = 1.8

projects[imce_wysiwyg][subdir]  = "contrib"
projects[imce_wysiwyg][version] = 1.0

projects[field_group][subdir]  = "contrib"
projects[field_group][version] = 1.3

projects[menu_attributes][subdir]  = "contrib"
projects[menu_attributes][version] = 1.0-rc2

projects[print][subdir]  = "contrib"
projects[print][version] = 1.3

projects[date][subdir]  = "contrib"
projects[date][version] = 2.7

projects[advanced_forum][subdir]  = "contrib"
projects[advanced_forum][version] = 2.3

projects[date_popup_authored][subdir]  = "contrib"
projects[date_popup_authored][version] = 1.1

projects[privatemsg][subdir]  = "contrib"
projects[privatemsg][version] = 1.4

projects[phpexcel][subdir]  = "contrib"
projects[phpexcel][version] = 3.7

projects[login_redirect][subdir]  = "contrib"
projects[login_redirect][version] = 1.1

projects[homebox][subdir]  = "contrib"
projects[homebox][version] = 2.0-beta7

projects[views_bulk_operations][subdir]  = "contrib"
projects[views_bulk_operations][version] = 3.2

projects[libraries][subdir]  = "contrib"
projects[libraries][version] = 2.2

projects[pathauto][subdir]  = "contrib"
projects[pathauto][version] = 1.2

projects[strongarm][subdir]  = "contrib"
projects[strongarm][version] = 2.0

projects[user_import][subdir]  = "contrib"
projects[user_import][version] = 2.2
projects[user_import][patch][] = "https://drupal.org/files/issues/creationdate_2220193_1.patch"

projects[jquery_countdown][subdir]  = "contrib"
projects[jquery_countdown][version] = 1.1

projects[content_access][subdir]  = "contrib"
projects[content_access][version] = 1.2-beta2

projects[pdf][subdir]  = "contrib"
projects[pdf][version] = 1.6


; Third-patry libraries ========================================================

libraries[CKEditor][download][type] = get
libraries[CKEditor][download][url]  = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.6.3/ckeditor_3.6.3.tar.gz"
libraries[CKEditor][destination]    = "libraries"
libraries[CKEditor][directory_name] = "ckeditor"

libraries[DOMPDF][download][type] = get
libraries[DOMPDF][download][url]  = "http://dompdf.googlecode.com/files/dompdf_0-6-0_beta3.tar.gz"
libraries[DOMPDF][destination]    = "libraries"
libraries[DOMPDF][directory_name] = "dompdf"

libraries[PHPExcel][download][type] = "get"
libraries[PHPExcel][download][url]  = "https://github.com/PHPOffice/PHPExcel/archive/1.7.9.tar.gz"
libraries[PHPExcel][destination]    = "libraries"
libraries[PHPExcel][directory_name] = "PHPExcel"
libraries[PHPExcel][patch][]        = "http://drupal.org/files/changelog_version_number-1908282-3.patch"
