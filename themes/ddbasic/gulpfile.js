'use strict';

var gulp = require('gulp-help')(require('gulp'));

// Plugins.
var gutil = require('gulp-util');
var jshint = require('gulp-jshint');
var uglify = require('gulp-uglify');
var rename = require('gulp-rename');
var sass = require('gulp-sass');

// We only want to process our own non-processed JavaScript files.
var jsPath = './scripts/ddbasic.!(*.min).js';
var sassPath = './sass/**/*.scss';

gulp.task('jshint', 'Run Javascript through JSHint',
  function() {
    return gulp.src(jsPath)
      .pipe(jshint())
      .pipe(jshint.reporter('jshint-stylish'));
  }
);

gulp.task('uglify', 'Minify JavaScript using Uglify',
  function() {
    gulp.src(jsPath)
      .pipe(uglify({
        // Preserve the $ variable name.
        mangle: { except: ['$'] }
      }).on('error', gutil.log))
      // Use gulp-rename to change the name of processed files.
      // We keep them in the same folder as the originals.
      .pipe(rename(function (path) {
        path.extname = '.min.js';
      }))
      .pipe(gulp.dest('./scripts'));
  }
);

gulp.task('sass', 'Process SCSS using libsass',
  function () {
    var includePaths = [
      'node_modules/compass-mixins/lib',
      // Zen grids is downloaded as a library using drush make.
      '../../libraries/zen-grids/stylesheets'
    ];

    // Reference version of compiled files.
    // These can be used for debugging or determining changes.
    gulp.src(sassPath)
      .pipe(sass({
        // The nested output style is the most verbose one.
        outputStyle: 'nested',
        includePaths: includePaths
      }).on('error', sass.logError))
      .pipe(gulp.dest('./css'));
    // Production version of compiled files. These are used by default.
    gulp.src(sassPath)
      .pipe(sass({
        outputStyle: 'compressed',
        includePaths: includePaths
      }).on('error', sass.logError))
      // Add a .min to compiled files to separate them from the verbose set.
      .pipe(rename(function (path) {
        path.extname = '.min.css';
      }))
      .pipe(gulp.dest('./css'));
  }
);

gulp.task('watch', 'Watch and process JS and SCSS files', ['uglify', 'sass'],
  function() {
    gulp.watch(jsPath, ['jshint', 'uglify']);
    gulp.watch(sassPath, ['sass']);
  }
);

gulp.task('default', ['help']);
