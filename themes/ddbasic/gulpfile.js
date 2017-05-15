/*globals require*/
'use strict';

var gulp = require('gulp-help')(require('gulp'));

// Plugins.
var gutil = require('gulp-util');
var jshint = require('gulp-jshint');
var uglify = require('gulp-uglify');
var rename = require('gulp-rename');
var sass = require('gulp-sass');
var cleanCSS = require('gulp-clean-css');
var concat = require('gulp-concat');
var gulpStylelint = require('gulp-stylelint');
var argv = require('yargs').argv;

// We only want to process our own non-processed JavaScript files.
// var jsPath = './scripts/ddbasic.!(*.min).js';
var jsPath = ['./scripts/**/*.js', '!./scripts/contrib/*', '!./scripts/min/**/*.js'];
var sassPath = ['./sass/**/*.scss', '!./sass/contrib/**'];

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
      .pipe(gulp.dest('./scripts/min'));
  }
);

/**
  * Usage:
  * gulp validate-sass [--dir=foldername]
  *
  * Check that all .scss files are style compliant
  *
  * Arguments:
  *
  * foldername - Optional foldername to check just a single folder
  *
  */
gulp.task('validate-sass', 'Validate the SCSS', function () {
  var testPath = argv.dir ? ['./sass/' + argv.dir + "/*.scss"] : sassPath;
  return gulp
    .src(testPath)
    .pipe(gulpStylelint({
     syntax: 'scss',
     reporters: [
        {formatter: 'string', console: true}
      ]
    }));
});

/**
 * Usage:
 * gulp sass
 *
 * Precompile all sass files into css files in the sass_css folder
 *
 */
gulp.task('sass', 'Process SCSS using libsass',
  function () {
    gulp.src(sassPath)
      .pipe(sass({outputStyle: 'nested'})
        .on('error', sass.logError))
      // Save verbose output for testing purposes.
      .pipe(gulp.dest('./sass_css_verbose_output'))
      // Minify the css and save it.
      .pipe(cleanCSS())
      .pipe(gulp.dest('./sass_css'));
  }
);

/**
  * Usage:
  * gulp kss
  *
  * Create the KSS micro site in the stylesheets folder
  * See ./sass/homepage.md
  *
  */
gulp.task('kss', 'Process SCSS using KSS / kss-node',
  function () {
    // Use kss-node and not gulp-kss
    var kss = require('kss');
    var styleGuide = {
        source: './sass',
        css: '../sass_css/bundle.css'
    };

    // Create the bundle.css
    gulp.src('./sass_css/**/*.css')
      .pipe(concat('bundle.css'))
      .pipe(gulp.dest('./sass_css'));

    return kss(styleGuide);
  }
);

/**
  * Usage:
  * gulp watch
  *
  * Watch js and sass files for changes and gulp accordingly
  *
  */
gulp.task('watch', 'Watch and process JS and SCSS files', ['uglify', 'sass'],
  function() {
    gulp.watch(jsPath, ['jshint', 'uglify']);
    gulp.watch(sassPath, ['validate-sass', 'sass']);
  }
);

gulp.task('default', ['help']);
