/*
Copyright (c) 2003-2013, CKSource - Frederico Knabben. All rights reserved.
For licensing, see LICENSE.html or http://ckeditor.com/license
*/



CKEDITOR.on( 'dialogDefinition', function( ev ) {
  // Take the dialog name and its definition from the event data.
  var dialogName = ev.data.name;
  var dialogDefinition = ev.data.definition;

  // Switch between dialogs and remove several fields and tabs.
  switch(dialogName) {
    case 'link':
      // Remove tabs.
      dialogDefinition.removeContents( 'target' );
      dialogDefinition.removeContents( 'advanced' );
      break;

    case 'image' :
      // Remove tab.
      dialogDefinition.removeContents( 'advanced' );

      // Get fields from info tab.
      var infoTab = dialogDefinition.getContents( 'info' );

      // Remove fields.
      infoTab.remove( 'ratioLock' );
      infoTab.remove( 'txtHeight' );
      infoTab.remove( 'txtWidth' );
      infoTab.remove( 'txtBorder');
      infoTab.remove( 'txtHSpace');
      infoTab.remove( 'txtVSpace');
      infoTab.remove( 'cmbAlign' );
      infoTab.remove( 'txtAlt' );
      infoTab.remove( 'cke_dialog_ui_hbox_first' );
      break;

    case 'table' :
      // Remove tab.
      dialogDefinition.removeContents( 'advanced' );

      // Get fields from info tab.
      var tableTab = dialogDefinition.getContents( 'info' );

      // Remove fields.
      tableTab.remove( 'cmbAlign' );
      tableTab.remove( 'selHeaders' );
      tableTab.remove( 'txtBorder' );
      tableTab.remove( 'txtWidth' );
      tableTab.remove( 'txtHeight' );
      tableTab.remove( 'txtCellSpace' );
      tableTab.remove( 'txtCellPad' );
      tableTab.remove( 'txtSummary' );
      tableTab.remove( 'txtCaption' );
      break;
  }
});

