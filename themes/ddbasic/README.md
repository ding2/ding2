# DDBasic V2.0

DDBasic is the default theme provided with DDBCMS and the recommended parent theme for inheritance of DDBCMS subthemes.

This document explains important parts of the theme layer and best practices for theming modules and inheriting subthemes from DDBasic.

*Note: KSS docs in links below are temporary awaiting a general doc solution.*

## The DDBasic framework

DDBasic is the actual implementation of the frontend for DDBCMS, and can be considered a kind of framework that works in many layers:

* Drupal: view modes
* Drupal: image styles
* html : markup and classes with special purposes
* scss : mixins, variables, extensions and responsive styling
* js : helper and ui functions
* php : Drupal template functions and other similar functions
* gulp: Developer tools

To reduce duplication of functionality and styling and to maintain consistence of both implementation and user experience, DDBasic provides a documentation for each of these layers.

## View modes

Drupal view modes allows for reuse of markup, styling and interaction of entities across views, panels and many other ways of rendering Drupal entities.

DDBasic introduces the following basic view modes which should be used across all submodules:

node:

```php
* full
* teaser
* teaser_highlight
* search_result
```

ting_object:

```php
* full
* teaser
* search_result
```

Note that each view mode can be styled individually for specific purposes, and fields can perfectly valid be hidden with display:none to create simpler outputs of each view mode. 

Hiding a few fields with CSS is preferred to increasing the number of view modes. 

Rendered view modes is the preferred method of presentation of entities as opposed to fielded views. 

**Rendering ting materials**

A recurring frontend task is to present a list of materials. The prefered procedure is to render an array of material ids as a carousel:

```php
theme("ting_carousel", array("items" => array($id1, $id2, $id3)));
```

The carousel can hold alot of materials and still keep the UI clean across devices. 

Future versions of the carousel could include custom settings for the user to render the materials more compact, with more deltails or as lists.

### Field type ting_reference

Any entity can reference specific ting materials via the ting_reference field type which in turn is easy to edit for the editors. Reuse this field when possible instead of introducing new fields for referencing materials.

Render this field with the desired viewmode to output a list of materials from an entity which can be edited in the CMS.

## Image styles

Drupal image styles makes preprocessing and cropping of images easy. Fluid responsive design and everchanging DPIs of devices makes it unfeasible to render images in 1:1 with the display on each device. The purpose left for the image styles is to deliver relevant aspect ratios and *reasonable* resolution of the content.

Upscaling should be avoided in all cases, and moderate CCS downscaling and optionally cropping is the prefered way of delivery for images. Always try to find a proper existing image style optionally downscaling it instead of introducing a new imagestyle with perfect pixel dimensions.

### Manual crop

[Manual cropping](https://www.drupal.org/project/manualcrop) is used to create optional crops of important aspect ratios. 

* Keep the number of manual crop instances minimal
* There must never be two manual crop instances with the same aspect ratio.
* Always derive new image styles from manual crops in order to be able to reuse the manual crop in other styles
* Design for existing manual crop aspect ratios
* If no aspect matches a desired manual crop, consider using a manual crop very close to the aspect and crop in a derived style or in CSS

## HTML markup

Along with preprocessing done in template.php the [template files](https://github.com/ding2/ding2/tree/master/themes/ddbasic/templates) are the html implementation of the Drupal objects. 

DDBasic follows [Drupal best practices](https://www.drupal.org/coding-standards/css/architecture) for frontend development and Drupals take on CSS and best practices for SCSS.

DDBasic introduces reusable html classes of special purpose which are documented in KSS along with their corresponding SCSS implementation. [See KSS Styleguide (temp link)](http://msd.ding2.server003.b14cms.dk/profiles/ding2/themes/ddbasic/styleguide)

## CSS architecture

Drupal introduces many useful concepts that can be used as guidelines for semantic markup and styling.

Nodes, entities, fields, menus, panels and modules are examples of important concepts that the Drupal template engine treats in a structured manner regarding APIs, markup and naming.


The [scss file structure](https://github.com/ding2/ding2/tree/master/themes/ddbasic/sass) separates Drupal concepts and provides a hierarchy close to SMACSS recommendations. Note that due to clashes between Drupal default markup DDBasic is not SMACSS compliant.

The stylesheets are selfdocumented with [KSS](https://github.com/kneath/kss) and the [compiled DDBasic styleguide (temp link)](http://msd.ding2.server003.b14cms.dk/profiles/ding2/themes/ddbasic/styleguide/) shows how classes, mixins, extensions and variables are correctly applied in future frontend styling of DDBasic.

The grid system is a 12 column grid based on [Bourbon Neat](http://neat.bourbon.io/) which is a light weight semantic framework for grids. See [grid settings](https://github.com/ding2/ding2/tree/master/themes/ddbasic/sass/configuration/_grid-settings.scss) for details.

A number of [practical breakpoints](https://github.com/ding2/ding2/tree/master/themes/ddbasic/sass/configuration/_grid-settings.scss) divides the styling into different device cases based on only one dimension, the screen width. Frontend development in contributed modules should use the established breakpoints, and tests should cover all breakpoint cases.

Specific Drupal / DDBasic rule of thumbs:

* Drupal structures are replicated as nested SCSS objects. 
* Viewmodes are styled inside the parent entity object
* Responsive specifications are styled inside the selector they override using the  ```@include media(..)``` mixin.
* Specifications of viewmode rendering in views are placed inside entities using the ```&```-parent selector keeping styling of entities in same file.

### Example - Nesting / Styling of a general entity

In general nesting levels should be kept minimal, but certain patterns of nesting supports the Drupal object hierachy well. This example shows how entities are styled in general:

```less

// File: ddbasic/sass/components/<entity>/<bundle>.scss

// Bundle specific styling
.entity-bundle {

    // Field styling
    .field-name-field-xyz {}
	
    // View mode specific styling
    &.view-mode-1 {

        .field-name-field-xyz {}
    
        // Responsive specifications
        @include media($tablet) {}

        @include media($mobile) {}	

    }
    
    &.view-mode-2 {}
}
```


See the [news.scss](https://github.com/ding2/ding2/tree/master/themes/ddbasic/sass/components/node/news.scss) for a complete example styling of an entity.

## Theme development

[Gulp](http://gulpjs.com/) will assist in workflow automation for the theme.

The following exampels takes place in the theme folder:

```
~$ cd DRUPAL/profiles/ding2/themes/ddbasic
```
 

Install [Node.js](https://github.com/joyent/node/wiki/Installing-Node.js-via-package-manager) if it is not already available on your platform.

Install Gulp and other packages:

```
 ~$ npm install
```

### Watch source files

```
~$ gulp watch
```

### Compile the source files once

```
~$ gulp sass
```

### Compile KSS from SCSS

KSS target folder is [sites/all/themes/ddbasic/styleguide (temp link)](http://msd.ding2.server003.b14cms.dk/profiles/ding2/themes/ddbasic/styleguide)

```
# Compile KSS into the styleguide folder 
# Note: the complete css is compacted into bundle.css for KSS reasons
~$ gulp kss
```

### SCSS lint

The [lint settings](https://github.com/ding2/ding2/tree/master/themes/ddbasic/package.json
) extends the [stylelint-config-standard](https://github.com/stylelint/stylelint-config-standard/blob/master/index.js) with a few exceptions towards flexibility.

```
~$ gulp validate-sass 
```
Pull requests are required to pass the linter.


## Compatibility

Browser capabilities has been converging fast since the exit of IE10. At the time of release DDBasic is compatible with IE11+, Chrome 52 and similar Webkit releases. No experimental features has been implemented and future compatibility is expected.

## Subtheming

Creating subthemes on top of DDBasic is the recommended method of altering the frontend of DDBCMS.

Note that the ongoing work with DDBBasic while improving the frontpage *can* break inherited subthemes. Having a subtheme may require additional testing and maintaining when new versions of DDBCms are released, as only pure DDBasic installations are guaranteed to be fully backward compatible with future updates.
