The PHPExcel module allows developers to export/import data to/from real Excel files.



# DEPENDENCIES

This module depends on the Libraries API module (http://drupal.org/project/libraries).

In order for this module to work, you must download the PHPExcel library (version 1.7 - http://phpexcel.codeplex.com/).

  ## IMPORTANT NOTE

Code downloaded from Github (the new home of the PHPExcel library) will not contain a proper version number in the changelog.txt file (http://drupal.org/node/1908282). The Libraries API module requires this information, though. If you download the code from Github, open the changelog.txt file and change the ##VERSION## string to the proper version tag (e.g. 1.7.8).



# INSTALLATION

The PHPExcel library can be extracted in any libraries folder you want (sites/*/libraries). You should have sites/*/libraries/PHPExcel/Classes/PHPExcel.php.



# IMPORTANT: UPGRADE FROM 2.x TO 3.x

The phpexcel.api.inc file was still available in 2.x for backward compatibility reasons, *but has completely been removed in 3.x*. Code must now include phpexcel.inc !

Also, *the include path for the PHPExcel library changes*! Make sure to move your library files (see Installation above). This may seem odd, but the previous way to store the library was not "right", in that you could not simply extract the downloaded archive to your libraries folder. Now you can.