<?php
/**
 * @file
 * ding_frontend.menu_block.inc
 */

/**
 * Implements hook_menu_block_defaults().
 */
function ding_frontend_menu_block_defaults() {
  $export = array();

  $menu_block = new stdClass();
  $menu_block->disabled = FALSE; /* Edit this to true to make a default menu_block disabled initially */
  $menu_block->api_version = 1;
  $menu_block->name = '1';
  $menu_block->label = 'Main menu (default)';
  $menu_block->description = '';
  $menu_block->depth = 1;
  $menu_block->expanded = 0;
  $menu_block->follow = '';
  $menu_block->level = 1;
  $menu_block->parent = 'main-menu:0';
  $menu_block->sort = 0;
  $menu_block->title_link = 0;
  $export['1'] = $menu_block;

  $menu_block = new stdClass();
  $menu_block->disabled = FALSE; /* Edit this to true to make a default menu_block disabled initially */
  $menu_block->api_version = 1;
  $menu_block->name = '2';
  $menu_block->label = 'Secondary menu (menu block)';
  $menu_block->description = '';
  $menu_block->depth = 1;
  $menu_block->expanded = 0;
  $menu_block->follow = '';
  $menu_block->level = 1;
  $menu_block->parent = 'menu-secondary-menu:0';
  $menu_block->sort = 0;
  $menu_block->title_link = 0;
  $export['2'] = $menu_block;

  return $export;
}
