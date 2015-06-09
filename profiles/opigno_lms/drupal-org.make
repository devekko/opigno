api = 2
core = 7.x


; Opigno modules ===============================================================

projects[opigno][version] = 1.11
projects[opigno][subdir]  = "opigno"

;projects[opigno][type]               = module
;projects[opigno][subdir]             = "opigno"
;projects[opigno][download][type]     = git
;projects[opigno][download][branch]   = 7.x-1.x
;projects[opigno][download][revision] = 3412f06fa8a19dfd725d562651b5ba83833da4f7

projects[opigno_calendar_app][version] = 1.0
projects[opigno_calendar_app][subdir]  = "opigno"

;projects[opigno_calendar_app][type]               = module
;projects[opigno_calendar_app][subdir]             = "opigno"
;projects[opigno_calendar_app][download][type]     = git
;projects[opigno_calendar_app][download][branch]   = 7.x-1.x
;projects[opigno_calendar_app][download][revision] = 85474ccb92d9737e88f8de48732cc04251ffc1c9

projects[opigno_certificate_app][version] = 1.1
projects[opigno_certificate_app][subdir]  = "opigno"

;projects[opigno_certificate_app][type]               = module
;projects[opigno_certificate_app][subdir]             = "opigno"
;projects[opigno_certificate_app][download][type]     = git
;projects[opigno_certificate_app][download][branch]   = 7.x-1.x
;projects[opigno_certificate_app][download][revision] = 7113b061ff4f15a524c08e11a340dd3522375196

projects[opigno_forum_app][version] = 1.0
projects[opigno_forum_app][subdir]  = "opigno"

projects[opigno_messaging_app][version] = 1.0-rc3
projects[opigno_messaging_app][subdir]  = "opigno"

projects[opigno_notifications_app][version] = 1.0-rc3
projects[opigno_notifications_app][subdir]  = "opigno"

projects[opigno_poll_app][version] = 1.0
projects[opigno_poll_app][subdir]  = "opigno"

projects[opigno_quiz_import_app][version] = 1.1
projects[opigno_quiz_import_app][subdir]  = "opigno"

;projects[opigno_quiz_import_app][type] = module
;projects[opigno_quiz_import_app][subdir]  = "opigno"
;projects[opigno_quiz_import_app][download][type]     = git
;projects[opigno_quiz_import_app][download][branch]   = 7.x-1.x
;projects[opigno_quiz_import_app][download][revision] = 4812b71ec1d1613a6318695c62b631278bff9184

projects[opigno_class_app][version] = 1.3
projects[opigno_class_app][subdir]  = "opigno"

projects[opigno_quiz_app][version]    = 1.11
projects[opigno_quiz_app][subdir]  = "opigno"

;projects[opigno_quiz_app][type] = module
;projects[opigno_quiz_app][subdir]  = "opigno"
;projects[opigno_quiz_app][download][type]     = git
;projects[opigno_quiz_app][download][branch]   = 7.x-1.x
;projects[opigno_quiz_app][download][revision] = aaef67e728c8bd57beba319f5e17489ad8242033

projects[opigno_wt_app][version] = 1.0-rc3
projects[opigno_wt_app][subdir]  = "opigno"

projects[opigno_course_categories_app][version] = 1.1
projects[opigno_course_categories_app][subdir]  = "opigno"

projects[tft][type]               = module
projects[tft][subdir]             = "opigno"
projects[tft][download][type]     = git
projects[tft][download][branch]   = "7.x-1.x"
projects[tft][download][url]      = "http://git.drupal.org/sandbox/wadmiraal/2071579.git"
projects[tft][download][revision] = 5fc9053efc85fc22044fb9e4f5cfb3cd9a417b08


; Opigno themes ================================================================

projects[platon][version] = 3.10
projects[platon][type] = theme

;projects[platon][type]               = theme
;projects[platon][download][type]     = git
;projects[platon][download][branch]   = "7.x-3.x"
;projects[platon][download][revision] = 97d5d08238d7b6f110af804f12b01a59f2cf975a

; Third-party modules that need to be patched ==================================

projects[quiz][version] = 4.0-beta3
projects[quiz][subdir]  = "contrib"
projects[quiz][patch][] = "http://drupal.org/files/issues/quiz_modify-quiz-to-lesson-in-ui-strings-2101063_4.patch"
projects[quiz][patch][] = "http://drupal.org/files/add_plural_quiz_name-937430-8.patch"
projects[quiz][patch][] = "http://drupal.org/files/issues/quiz-questiontostep-2185205-1.patch"
projects[quiz][patch][] = "http://drupal.org/files/issues/quiz_2190283.patch"
projects[quiz][patch][] = "http://drupal.org/files/issues/quiz_h5p-dd_lines_js_bug-2212789-7.patch"
projects[quiz][patch][] = "http://drupal.org/files/issues/quiz_feedback-after-question_2384955.patch"
projects[quiz][patch][] = "http://drupal.org/files/issues/quiz_poll-conflict_2394843.patch"
projects[quiz][patch][] = "http://drupal.org/files/issues/quiz_laq-0score_2394759.patch"
projects[quiz][patch][] = "http://drupal.org/files/issues/quiz-browser_per_quiz_type-2401779-2.patch"

; Quiz File Upload
projects[quizfileupload][version] = 1.0
projects[quizfileupload][subdir]  = "contrib"
projects[quizfileupload][patch][] = "http://drupal.org/files/adding_manual_scoring_extension_validation_feedback-2092275-5.patch"

; OG
projects[og][version] = 2.7
projects[og][subdir]  = "contrib"
projects[og][patch][] = "http://drupal.org/files/issues/og_2330777.patch"
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
projects[apps][version] = 1.0-beta17
projects[apps][patch][] = "http://drupal.org/files/issues/apps_module-2357093.patch"

; Certificate
projects[certificate][subdir]  = "contrib"
projects[certificate][version] = 2.0

; i18n (note: will probably get fixed in 1.12)
projects[i18n][subdir]  = "contrib"
projects[i18n][version] = 1.11
projects[i18n][patch][] = "http://drupal.org/files/issues/i18n_string-2227523-7.patch"

projects[l10n_update][subdir]  = "contrib"
projects[l10n_update][version] = 2.0

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
projects[quiz_drag_drop][patch][] = "http://drupal.org/files/issues/quiz_drag_drop_2364215.patch"


; Third-party modules ==========================================================

projects[h5p][subdir] = "contrib"
projects[h5p][version] = 1.1

projects[admin_menu][subdir] = "contrib"
projects[admin_menu][version] = 3.0-rc5

projects[ctools][subdir] = "contrib"
projects[ctools][version] = 1.4

projects[views][subdir] = "contrib"
projects[views][version] = 3.10

projects[views_php][subdir] = "contrib"
projects[views_php][version] = 1.0-alpha1

projects[defaultconfig][subdir] = "contrib"
projects[defaultconfig][version] = 1.0-alpha9

projects[module_filter][subdir]  = "contrib"
projects[module_filter][version] = 1.8

projects[entity][subdir]  = "contrib"
projects[entity][version] = 1.6

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

projects[rules_conditional][subdir]  = "contrib"
projects[rules_conditional][version] = 1.0-beta2

projects[features][subdir]  = "contrib"
projects[features][version] = 2.0

projects[og_massadd][subdir]  = "contrib"
projects[og_massadd][version] = 1.0-beta2

projects[og_quiz][subdir]  = "contrib"
projects[og_quiz][version] = 1.3

;projects[og_quiz][type]               = module
;projects[og_quiz][subdir]             = "contrib"
;projects[og_quiz][download][type]     = git
;projects[og_quiz][download][branch]   = "7.x-1.x"
;projects[og_quiz][download][revision] = 600d1481f3492cef8f669173da6a700b48757924

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
projects[date][version] = 2.8
projects[date][patch][] = "http://drupal.org/files/issues/title_date_formats-2294973-6.patch"

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
projects[homebox][version] = 2.0-rc1
;projects[homebox][patch][] = "http://drupal.org/files/issues/homebox-check_widths-1634486-6.patch"

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
projects[user_import][patch][] = "http://drupal.org/files/issues/creationdate_2220193_1.patch"

projects[jquery_countdown][subdir]  = "contrib"
projects[jquery_countdown][version] = 1.1

projects[content_access][subdir]  = "contrib"
projects[content_access][version] = 1.2-beta2

projects[r4032login][subdir] = "contrib"
projects[r4032login][version] = 1.8
projects[r4032login][patch][] = "http://drupal.org/files/issues/r4032login-exclude_homepage-2362997.patch"

projects[better_exposed_filters][subdir] = "contrib"
projects[better_exposed_filters][version] = 3.0-beta4

projects[guideme][subdir]  = "contrib"
projects[guideme][version] = 1.0-rc1

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
