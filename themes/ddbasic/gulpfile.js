var gulp = require('gulp');

// Plugins.
var gutil = require('gulp-util');
var jshint = require('gulp-jshint');
var uglify = require('gulp-uglify');
var rename = require('gulp-rename');
var sass = require('gulp-sass');

// We only want to process our own non-processed JavaScript files.
var jsPath = './scripts/ddbasic.!(*.min).js';
var sassPath = './sass/**/*.scss';

// Run Javascript through JSHint.
gulp.task('jshint', function() {
  return gulp.src(jsPath)
    .pipe(jshint())
    .pipe(jshint.reporter('jshint-stylish'));
});

// Minify JavaScript using Uglify.
gulp.task('uglify', function() {
  gulp.src(jsPath)
    .pipe(uglify({
      // Preserve the $ variable name.
      mangle: { except: ['$'] }
    }).on('error', gutil.log))
    // Use gulp-rename to change the name of processed files.
    // We keep them in the same folder as the originals.
    .pipe(rename(function (path) {
      path.extname = '.min.js'
    }))
    .pipe(gulp.dest('./scripts'));
});

// Process SCSS using libsass
gulp.task('sass', function () {
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
});

gulp.task('watch', function() {
  gulp.watch(jsPath, ['jshint', 'uglify']);
  gulp.watch(sassPath, ['sass']);
});

gulp.task('default', ['uglify', 'sass', 'watch']);
