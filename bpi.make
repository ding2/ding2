api = 2
core = 7.x

; Ctools
projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.3"

; Date
projects[date][subdir] = "contrib"
projects[date][version] = "2.6"

; Media
projects[media][subdir] = "contrib"
projects[media][version] = "1.3"

; Wysiwyg
projects[wysiwyg][subdir] = "contrib"
projects[wysiwyg][version] = "2.2"

; CKEditor lib for wysiwyg
libraries[ckeditor][destination]    = "libraries"
libraries[ckeditor][directory_name] = "ckeditor"
libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url]  = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.6.6.1/ckeditor_3.6.6.1.zip"

; Ding popup
projects[ding_popup][type] = "module"
projects[ding_popup][download][type] = "git"
projects[ding_popup][download][url]  = "git@github.com:ding2/ding_popup.git"
projects[ding_popup][download][branch] = "master"
