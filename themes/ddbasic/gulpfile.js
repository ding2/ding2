'use strict';

var gulp = require('gulp-help')(require('gulp'));

// Plugins.
var gutil = require('gulp-util');
var jshint = require('gulp-jshint');
var uglify = require('gulp-uglify');
var rename = require('gulp-rename');
var sass = require('gulp-sass');
var cleanCSS = require('gulp-clean-css');
var concatCss = require('gulp-concat-css');
var gulpStylelint = require('gulp-stylelint');
var gdeb = require('gulp-debug');


// We only want to process our own non-processed JavaScript files.
// var jsPath = './scripts/ddbasic.!(*.min).js';
var jsPath = ['./scripts/**/*.js', '!./scripts/contrib/*'];
var sassPath = ['./sass/**/*.scss', , '!./sass/contrib/**'];

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
      // .pipe(rename(function (path) {
        // path.extname = '.min.js';
      // }))
      .pipe(gulp.dest('./scripts/min'));
  }
);

gulp.task('testsass', function lintCssTask() {
  const gulpStylelint = require('gulp-stylelint');
  var argv = require('yargs').argv;
  var testPath = ['./sass/' + argv.dir + "/*.scss"];
  console.log("Testing: " + testPath);
  return gulp
    .src(testPath)
    .pipe(gulpStylelint({
     syntax: 'scss',
     reporters: [
        {formatter: 'string', console: true}
      ]
    }));
});

gulp.task('testsassall', function lintCssTask() {
  const gulpStylelint = require('gulp-stylelint');
  return gulp
    .src(sassPath)
    .pipe(gulpStylelint({
     syntax: 'scss',
     reporters: [
        {formatter: 'string', console: true}
      ]
    }));
});

gulp.task('sass', 'Process SCSS using libsass',
  function () {
    gulp.src(sassPath)
      .pipe(gulpStylelint({
        syntax: 'scss',
        failAfterError: false,
        reporters: [
          {formatter: 'string', console: true},
        ]
      }))
      .pipe(sass({outputStyle: 'compressed'})
        .on('error', sass.logError))
      .pipe(concatCss("bundle.css"))
      .pipe(cleanCSS())
      .pipe(gulp.dest('./sass_css'));
  }
);

gulp.task('kss', 'Process SCSS using KSS',
  function () {
    var gulpkss = require('gulp-kss');
    gulp.src(['sass/**/*.scss'])
      .pipe(gulpkss({
        overview: './sass/kss_styleguide.md',
        // kss-node options https://github.com/kss-node/kss-node
        kss: {
          css: './sass_css/bundle.css'
        }
      }))
      .pipe(gulp.dest('styleguide/'));
  }
);

gulp.task('watch', 'Watch and process JS and SCSS files', ['uglify', 'sass'],
  function() {
    gulp.watch(jsPath, ['jshint', 'uglify']);
    gulp.watch(sassPath, ['sass']);
    }
);

gulp.task('default', ['help']);
