(function($) {
	Drupal.behaviors.facetbrowser = {
    attach: function(context, settings) {
      $('#block-ding-facetbrowser-facetbrowser .item-list input').click(function() {
				$(this).parent().toggleClass('selected');
				var facets = Drupal.updateFacetURL($('.block-ding-facetbrowser'), $(this));
				document.location.href =  '?facets=' + str_replace('-', '.', facets) + '#' + 'facets=' + facets;
      });
      Drupal.initFacetBrowser();
    }
	};	

  Drupal.initFacetBrowser = function() {
    Drupal.updateFacetURL($(this));
    Drupal.updateFacetsFromURL($(this));
  }

	Drupal.updateFacetsFromURL = function(element) {
    var facets, match;
    if ($.url.attr('anchor')) {
      match = $.url.attr('anchor').match('facets=(([^:]*:[^;]*;)+)');
      if (match && match.length > 1) {
        facets = match[1].split(';');
        for (f in facets) {
          f = facets[f].split(':');
          if (f.length > 1) {
            $('#' + f[0] + '-' + f[1]).attr('checked', true);
          }
        }
      }
    }
    return $('.selected').size() > 0;
	}

	Drupal.updateFacetURL = function (context, element) {
			var facets, sort, vars;
			facets = '';
			$('.selected', context).each(function(i, e) {
        console.log($(this));
				facets += $(e).parents('ul').attr('id') + ':' + $(e).parents('li').attr('rel') + ';';
			});
			return facets;
	};
})(jQuery);
function str_replace (search, replace, subject, count) {
    // Replaces all occurrences of search in haystack with replace  
    // 
    // version: 1101.3117
    // discuss at: http://phpjs.org/functions/str_replace
    // +   original by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
    // +   improved by: Gabriel Paderni
    // +   improved by: Philip Peterson
    // +   improved by: Simon Willison (http://simonwillison.net)
    // +    revised by: Jonas Raoni Soares Silva (http://www.jsfromhell.com)
    // +   bugfixed by: Anton Ongson
    // +      input by: Onno Marsman
    // +   improved by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
    // +    tweaked by: Onno Marsman
    // +      input by: Brett Zamir (http://brett-zamir.me)
    // +   bugfixed by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
    // +   input by: Oleg Eremeev
    // +   improved by: Brett Zamir (http://brett-zamir.me)
    // +   bugfixed by: Oleg Eremeev
    // %          note 1: The count parameter must be passed as a string in order
    // %          note 1:  to find a global variable in which the result will be given
    // *     example 1: str_replace(' ', '.', 'Kevin van Zonneveld');
    // *     returns 1: 'Kevin.van.Zonneveld'
    // *     example 2: str_replace(['{name}', 'l'], ['hello', 'm'], '{name}, lars');
    // *     returns 2: 'hemmo, mars'
    var i = 0, j = 0, temp = '', repl = '', sl = 0, fl = 0,
            f = [].concat(search),
            r = [].concat(replace),
            s = subject,
            ra = r instanceof Array, sa = s instanceof Array;
    s = [].concat(s);
    if (count) {
        this.window[count] = 0;
    }
 
    for (i=0, sl=s.length; i < sl; i++) {
        if (s[i] === '') {
            continue;
        }
        for (j=0, fl=f.length; j < fl; j++) {
            temp = s[i]+'';
            repl = ra ? (r[j] !== undefined ? r[j] : '') : r[0];
            s[i] = (temp).split(f[j]).join(repl);
            if (count && s[i] !== temp) {
                this.window[count] += (temp.length-s[i].length)/f[j].length;}
        }
    }
    return sa ? s : s[0];
}

