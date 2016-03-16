'use strict';

var gulp = require('gulp-help')(require('gulp'));

// Plugins.
var sass = require('gulp-sass');

var sassPath = './sass/**/*.scss';

gulp.task('sass', 'Process SCSS using libsass',
  function () {
    gulp.src(sassPath)
      .pipe(sass({
        outputStyle: 'compressed',
        includePaths: [
          'node_modules/compass-mixins/lib',
          // Zen grids is downloaded as a library using drush make.
          '../../libraries/zen-grids/stylesheets'
        ]
      }).on('error', sass.logError))
      .pipe(gulp.dest('./css'));
  }
);

gulp.task('watch', 'Watch and process SCSS files', ['sass'],
  function() {
    gulp.watch(sassPath, ['sass']);
  }
);

gulp.task('default', ['help']);