<?php
/**
 * @file
 * ding_page.menu_block.inc
 */

/**
 * Implements hook_menu_block_defaults().
 */
function ding_page_menu_block_defaults() {
  $export = array();

  $menu_block = new stdClass();
  $menu_block->disabled = FALSE; /* Edit this to true to make a default menu_block disabled initially */
  $menu_block->api_version = 1;
  $menu_block->name = '3';
  $menu_block->label = 'Submenu (menu block)';
  $menu_block->description = '';
  $menu_block->depth = 0;
  $menu_block->expanded = 0;
  $menu_block->follow = '';
  $menu_block->level = 3;
  $menu_block->parent = 'main-menu:0';
  $menu_block->sort = 0;
  $menu_block->title_link = 1;
  $export['3'] = $menu_block;

  $menu_block = new stdClass();
  $menu_block->disabled = FALSE; /* Edit this to true to make a default menu_block disabled initially */
  $menu_block->api_version = 1;
  $menu_block->name = '4';
  $menu_block->label = 'Submenu (secodary menu block)';
  $menu_block->description = '';
  $menu_block->depth = 0;
  $menu_block->expanded = 0;
  $menu_block->follow = '';
  $menu_block->level = 2;
  $menu_block->parent = 'menu-secondary-menu:0';
  $menu_block->sort = 0;
  $menu_block->title_link = 1;
  $export['4'] = $menu_block;

  return $export;
}
