<?php

/**
 * @file
 * Color module settings.
 */


// Put the logo and theme paths into JavaScript for the live preview.
drupal_add_js(array(
  'color' => array(
    'logo' => theme_get_setting('logo', 'platon'),
    'themePath' => drupal_get_path('theme', 'platon'),
  )
), 'setting');

$info = array(
  // Fields. Just use the variable color definitions we have in SASS.
  'fields' => array(
    'white' => t('White'),
    'very_light_gray' => t('Very light gray'),
    'light_gray' => t('Light gray'),
    'medium_gray' => t('Medium gray'),
    'dark_gray' => t('Dark gray'),
    'light_blue' => t('Light blue'),
    'dark_blue' => t('Dark blue'),
    'deep_blue' => t('Deep blue'),
    'leaf_green' => t('Leaf green'),
    'blood_red' => t('Blood red'),
    'base' => t("not used"), // This one is to prevent Notices.
    'link' => t("not used"), // This one is to prevent Notices.
  ),
  // Provided color schemes.
  'schemes' => array(
    'default' => array(
      'title' => t('Platon (default)'),
      'colors' => array(
        'white' => '#fcfcfc',
        'very_light_gray' => '#f2f2f0',
        'light_gray' => '#f8f7f5',
        'medium_gray' => '#ececeb',
        'dark_gray' => '#58585a',
        'light_blue' => '#88c1e6',
        'dark_blue' => '#009ee0',
        'deep_blue' => '#0a71b4',
        'leaf_green' => '#5aa449',
        'blood_red' => '#ea645b',
        'base' => '#ffffff',
        'link' => '#009ee0',
      ),
    ),
    'socrates' => array(
      'title' => t('Socrates'),
      'colors' => array(
        'white' => '#fcfcfc',
        'very_light_gray' => '#f2f2f0',
        'light_gray' => '#f8f7f5',
        'medium_gray' => '#f8f7f5',
        'dark_gray' => '#58585a',
        'light_blue' => '#37a09f',
        'dark_blue' => '#145352',
        'deep_blue' => '#00b8b5',
        'leaf_green' => '#6e9fbb',
        'blood_red' => '#9c9c9c',
        'base' => '#ffffff',
        'link' => '#18681d',
      ),
    ),
    'aristoteles' => array(
      'title' => t('Aristoteles'),
      'colors' => array(
        'white' => '#fcfcfc',
        'very_light_gray' => '#f2f2f0',
        'light_gray' => '#ffffff',
        'medium_gray' => '#e8e8e8',
        'dark_gray' => '#58585a',
        'light_blue' => '#3e3e3e',
        'dark_blue' => '#000000',
        'deep_blue' => '#040404',
        'leaf_green' => '#0f1a2c',
        'blood_red' => '#e2a238',
        'base' => '#ffffff',
        'link' => '#18681d',
      ),
    ),
  ),
  // Rewrite styles.css
  'css' => array(
    'css/color.css',
  ),
  // Prevent Notices.
  'copy' => array(),
  'gradients' => array(),
  // Color areas to fill (x, y, width, height).
  'fill' => array(
    'dark_blue' => array(0, 0, 500, 212),
    'deep_blue' => array(0, 318, 3000, 134),
  ),
  // Coordinates of all the theme slices (x, y, width, height)
  // with their filename as used in the stylesheet.
  'slices' => array(
    'img/all.png'                                              => array(0, 0, 500, 500),
    'img/main-navigation-training-catalogue-icon-inactive.png' => array(0, 0, 106, 106),
    'img/main-navigation-my-courses-icon-inactive.png'         => array(106, 0, 106, 106),
    'img/main-navigation-my-achievements-icon-inactive.png'    => array(212, 0, 106, 106),
    'img/main-navigation-messages-icon-inactive.png'           => array(318, 0, 106, 106),
    'img/main-navigation-home-icon-inactive.png'               => array(0, 106, 106, 106),
    'img/main-navigation-forum-icon-inactive.png'              => array(106, 106, 106, 106),
    'img/main-navigation-calendar-icon-inactive.png'           => array(212, 106, 106, 106),
    'img/main-navigation-administration-icon-inactive.png'     => array(318, 106, 106, 106),
    'img/collapse-menu-icon.png'                               => array(424, 0, 13, 50),
    'img/back-icon.png'                                        => array(437, 0, 6, 8),
    'img/header-background.jpg'                                => array(0, 318, 3000, 134),
  ),
  // Reference color used for blending.
  'blend_target' => '#ffffff',
  // Preview files.
  'preview_css' => 'color/preview.css',
  'preview_js' => 'color/preview.js',
  'preview_html' => 'color/preview.html',
  // Base file for image generation.
  'base_image' => 'color/base.png',
);
