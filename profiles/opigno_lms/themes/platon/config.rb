##
## This file is only needed for Compass/Sass integration. If you are not using
## Compass, you may safely ignore this file.
##

# Location of the theme's resources.
css_dir = "css"
sass_dir = "sass"
images_dir = "img"
generated_images_dir = images_dir + "/generated"
javascripts_dir = "js"

# Require any additional compass plugins installed on your system.
require 'compass-normalize'
require 'fileutils'

# You can select your preferred output style here (:expanded, :nested, :compact
# or :compressed).
output_style = (environment == :development) ? :expanded : :compressed

# To enable relative paths to assets via compass helper functions. Since Drupal
# themes can be installed in multiple locations, we don't need to worry about
# the absolute path to the theme from the server omega.
relative_assets = true

# Conditionall enable line comments when in development mode.
line_comments = (environment == :development) ? true : false

# Output debugging info in development mode.
sass_options = (environment == :development) ? {:debug_info => true} : {}

on_stylesheet_saved do |file|
  if File.exists?(file) && File.basename(file) == "preview.css"
      puts "Moving: #{file}"
      FileUtils.mv(file, File.dirname(file) + "/../color/" + File.basename(file))
    end
end