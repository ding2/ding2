/*
	Copyright (c) 2012 Webtrends, Inc.
	Facebook App Plugin v10.2.23
  
	An example of including the plugin with your tag.
  
	<script type="text/javascript">
	// async loader function, called by webtrends.js after load
	window.webtrendsAsyncInit=function(){
		var dcs=new Webtrends.dcs().init({
			dcsid:"YOUR_WEBTRENDS_DCSID_HERE"
			,timezone:YOUR_TIMEZONE_HERE
			,plugins:{
				facebook:{src:"webtrends.fb.js"}
			}
			}).track();
	};
	(function(){
		var s=document.createElement("script"); s.async=true; s.src="webtrends.js";    
		var s2=document.getElementsByTagName("script")[0]; s2.parentNode.insertBefore(s,s2);
	}());
	</script>

	The track() function will return 'true' when it tracks data, 'false' otherwise.
*/

/*
http://www.JSON.org/json2.js
2011-02-23
	Public Domain.

	NO WARRANTY EXPRESSED OR IMPLIED. USE AT YOUR OWN RISK.
*/


// Create a JSON object only if one does not already exist. We create the
// methods in a closure to avoid creating global variables.

var JSON;
if (!JSON) {
	JSON = {};
}

(function () {
	"use strict";

	function f(n) {
		// Format integers to have at least two digits.
		return n < 10 ? '0' + n : n;
	}

	if (typeof Date.prototype.toJSON !== 'function') {

		Date.prototype.toJSON = function (key) {

			return isFinite(this.valueOf()) ?
				this.getUTCFullYear()     + '-' +
				f(this.getUTCMonth() + 1) + '-' +
				f(this.getUTCDate())      + 'T' +
				f(this.getUTCHours())     + ':' +
				f(this.getUTCMinutes())   + ':' +
				f(this.getUTCSeconds())   + 'Z' : null;
		};

		String.prototype.toJSON      =
			Number.prototype.toJSON  =
			Boolean.prototype.toJSON = function (key) {
				return this.valueOf();
			};
	}

	var cx = /[\u0000\u00ad\u0600-\u0604\u070f\u17b4\u17b5\u200c-\u200f\u2028-\u202f\u2060-\u206f\ufeff\ufff0-\uffff]/g,
		escapable = /[\\\"\x00-\x1f\x7f-\x9f\u00ad\u0600-\u0604\u070f\u17b4\u17b5\u200c-\u200f\u2028-\u202f\u2060-\u206f\ufeff\ufff0-\uffff]/g,
		gap,
		indent,
		meta = {    // table of character substitutions
			'\b': '\\b',
			'\t': '\\t',
			'\n': '\\n',
			'\f': '\\f',
			'\r': '\\r',
			'"' : '\\"',
			'\\': '\\\\'
		},
		rep;


	function quote(string) {

// If the string contains no control characters, no quote characters, and no
// backslash characters, then we can safely slap some quotes around it.
// Otherwise we must also replace the offending characters with safe escape
// sequences.

		escapable.lastIndex = 0;
		return escapable.test(string) ? '"' + string.replace(escapable, function (a) {
			var c = meta[a];
			return typeof c === 'string' ? c :
				'\\u' + ('0000' + a.charCodeAt(0).toString(16)).slice(-4);
		}) + '"' : '"' + string + '"';
	}


	function str(key, holder) {

// Produce a string from holder[key].

		var i,          // The loop counter.
			k,          // The member key.
			v,          // The member value.
			length,
			mind = gap,
			partial,
			value = holder[key];

// If the value has a toJSON method, call it to obtain a replacement value.

		if (value && typeof value === 'object' &&
				typeof value.toJSON === 'function') {
			value = value.toJSON(key);
		}

// If we were called with a replacer function, then call the replacer to
// obtain a replacement value.

		if (typeof rep === 'function') {
			value = rep.call(holder, key, value);
		}

// What happens next depends on the value's type.

		switch (typeof value) {
		case 'string':
			return quote(value);

		case 'number':

// JSON numbers must be finite. Encode non-finite numbers as null.

			return isFinite(value) ? String(value) : 'null';

		case 'boolean':
		case 'null':

// If the value is a boolean or null, convert it to a string. Note:
// typeof null does not produce 'null'. The case is included here in
// the remote chance that this gets fixed someday.

			return String(value);

// If the type is 'object', we might be dealing with an object or an array or
// null.

		case 'object':

// Due to a specification blunder in ECMAScript, typeof null is 'object',
// so watch out for that case.

			if (!value) {
				return 'null';
			}

// Make an array to hold the partial results of stringifying this object value.

			gap += indent;
			partial = [];

// Is the value an array?

			if (Object.prototype.toString.apply(value) === '[object Array]') {

// The value is an array. Stringify every element. Use null as a placeholder
// for non-JSON values.

				length = value.length;
				for (i = 0; i < length; i += 1) {
					partial[i] = str(i, value) || 'null';
				}

// Join all of the elements together, separated with commas, and wrap them in
// brackets.

				v = partial.length === 0 ? '[]' : gap ?
					'[\n' + gap + partial.join(',\n' + gap) + '\n' + mind + ']' :
					'[' + partial.join(',') + ']';
				gap = mind;
				return v;
			}

// If the replacer is an array, use it to select the members to be stringified.

			if (rep && typeof rep === 'object') {
				length = rep.length;
				for (i = 0; i < length; i += 1) {
					if (typeof rep[i] === 'string') {
						k = rep[i];
						v = str(k, value);
						if (v) {
							partial.push(quote(k) + (gap ? ': ' : ':') + v);
						}
					}
				}
			} else {

// Otherwise, iterate through all of the keys in the object.

				for (k in value) {
					if (Object.prototype.hasOwnProperty.call(value, k)) {
						v = str(k, value);
						if (v) {
							partial.push(quote(k) + (gap ? ': ' : ':') + v);
						}
					}
				}
			}

// Join all of the member texts together, separated with commas,
// and wrap them in braces.

			v = partial.length === 0 ? '{}' : gap ?
				'{\n' + gap + partial.join(',\n' + gap) + '\n' + mind + '}' :
				'{' + partial.join(',') + '}';
			gap = mind;
			return v;
		}
	}

// If the JSON object does not yet have a stringify method, give it one.

	if (typeof JSON.stringify !== 'function') {
		JSON.stringify = function (value, replacer, space) {

// The stringify method takes a value and an optional replacer, and an optional
// space parameter, and returns a JSON text. The replacer can be a function
// that can replace values, or an array of strings that will select the keys.
// A default replacer method can be provided. Use of the space parameter can
// produce text that is more easily readable.

			var i;
			gap = '';
			indent = '';

// If the space parameter is a number, make an indent string containing that
// many spaces.

			if (typeof space === 'number') {
				for (i = 0; i < space; i += 1) {
					indent += ' ';
				}

// If the space parameter is a string, it will be used as the indent string.

			} else if (typeof space === 'string') {
				indent = space;
			}

// If there is a replacer, it must be a function or an array.
// Otherwise, throw an error.

			rep = replacer;
			if (replacer && typeof replacer !== 'function' &&
					(typeof replacer !== 'object' ||
					typeof replacer.length !== 'number')) {
				throw new Error('JSON.stringify');
			}

// Make a fake root object containing our value under the key of ''.
// Return the result of stringifying the value.

			return str('', {'': value});
		};
	}


// If the JSON object does not yet have a parse method, give it one.

	if (typeof JSON.parse !== 'function') {
		JSON.parse = function (text, reviver) {

// The parse method takes a text and an optional reviver function, and returns
// a JavaScript value if the text is a valid JSON text.

			var j;

			function walk(holder, key) {

// The walk method is used to recursively walk the resulting structure so
// that modifications can be made.

				var k, v, value = holder[key];
				if (value && typeof value === 'object') {
					for (k in value) {
						if (Object.prototype.hasOwnProperty.call(value, k)) {
							v = walk(value, k);
							if (v !== undefined) {
								value[k] = v;
							} else {
								delete value[k];
							}
						}
					}
				}
				return reviver.call(holder, key, value);
			}


// Parsing happens in four stages. In the first stage, we replace certain
// Unicode characters with escape sequences. JavaScript handles many characters
// incorrectly, either silently deleting them, or treating them as line endings.

			text = String(text);
			cx.lastIndex = 0;
			if (cx.test(text)) {
				text = text.replace(cx, function (a) {
					return '\\u' +
						('0000' + a.charCodeAt(0).toString(16)).slice(-4);
				});
			}

// In the second stage, we run the text against regular expressions that look
// for non-JSON patterns. We are especially concerned with '()' and 'new'
// because they can cause invocation, and '=' because it can cause mutation.
// But just to be safe, we want to reject all unexpected forms.

// We split the second stage into 4 regexp operations in order to work around
// crippling inefficiencies in IE's and Safari's regexp engines. First we
// replace the JSON backslash pairs with '@' (a non-JSON character). Second, we
// replace all simple value tokens with ']' characters. Third, we delete all
// open brackets that follow a colon or comma or that begin the text. Finally,
// we look to see that the remaining characters are only whitespace or ']' or
// ',' or ':' or '{' or '}'. If that is so, then the text is safe for eval.

			if (/^[\],:{}\s]*$/
					.test(text.replace(/\\(?:["\\\/bfnrt]|u[0-9a-fA-F]{4})/g, '@')
						.replace(/"[^"\\\n\r]*"|true|false|null|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?/g, ']')
						.replace(/(?:^|:|,)(?:\s*\[)+/g, ''))) {

// In the third stage we use the eval function to compile the text into a
// JavaScript structure. The '{' operator is subject to a syntactic ambiguity
// in JavaScript: it can begin a block or an object literal. We wrap the text
// in parens to eliminate the ambiguity.

				j = eval('(' + text + ')');

// In the optional fourth stage, we recursively walk the new structure, passing
// each name/value pair to a reviver function for possible transformation.

				return typeof reviver === 'function' ?
					walk({'': j}, '') : j;
			}

// If the text is not JSON parseable, then a SyntaxError is thrown.

			throw new SyntaxError('JSON.parse');
		};
	}
}());
/* 
A way to read Facebook's signed_request in JavaScript.

http://developers.facebook.com/blog/post/462

https://github.com/diulama/js-facebook-signed-request/blob/master/fb_signed_request.js

*/

(function(win){
	function utf8_decode (str_data) {
		// http://kevin.vanzonneveld.net
		// +   original by: Webtoolkit.info (http://www.webtoolkit.info/)
		// +      input by: Aman Gupta
		// +   improved by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
		// +   improved by: Norman "zEh" Fuchs
		// +   bugfixed by: hitwork
		// +   bugfixed by: Onno Marsman
		// +      input by: Brett Zamir (http://brett-zamir.me)
		// +   bugfixed by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
		// *     example 1: utf8_decode('Kevin van Zonneveld');
		// *     returns 1: 'Kevin van Zonneveld'
		var tmp_arr = [],
			i = 0,
			ac = 0,
			c1 = 0,
			c2 = 0,
			c3 = 0;

		str_data += '';

		while (i < str_data.length) {
			c1 = str_data.charCodeAt(i);
			if (c1 < 128) {
				tmp_arr[ac++] = String.fromCharCode(c1);
				i++;
			} else if (c1 > 191 && c1 < 224) {
				c2 = str_data.charCodeAt(i + 1);
				tmp_arr[ac++] = String.fromCharCode(((c1 & 31) << 6) | (c2 & 63));
				i += 2;
			} else {
				c2 = str_data.charCodeAt(i + 1);
				c3 = str_data.charCodeAt(i + 2);
				tmp_arr[ac++] = String.fromCharCode(((c1 & 15) << 12) | ((c2 & 63) << 6) | (c3 & 63));
				i += 3;
			}
		}

		return tmp_arr.join('');
	}

	function base64_encode (data) {
		// http://kevin.vanzonneveld.net
		// +   original by: Tyler Akins (http://rumkin.com)
		// +   improved by: Bayron Guevara
		// +   improved by: Thunder.m
		// +   improved by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
		// +   bugfixed by: Pellentesque Malesuada
		// +   improved by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
		// -    depends on: utf8_encode
		// *     example 1: base64_encode('Kevin van Zonneveld');
		// *     returns 1: 'S2V2aW4gdmFuIFpvbm5ldmVsZA=='
		// mozilla has this native
		// - but breaks in 2.0.0.12!
		//if (typeof this.window['atob'] == 'function') {
		//    return atob(data);
		//}
		var b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
		var o1, o2, o3, h1, h2, h3, h4, bits, i = 0,
			ac = 0,
			enc = "",
			tmp_arr = [];

		if (!data) {
			return data;
		}

		data = this.utf8_encode(data + '');

		do { // pack three octets into four hexets
			o1 = data.charCodeAt(i++);
			o2 = data.charCodeAt(i++);
			o3 = data.charCodeAt(i++);

			bits = o1 << 16 | o2 << 8 | o3;

			h1 = bits >> 18 & 0x3f;
			h2 = bits >> 12 & 0x3f;
			h3 = bits >> 6 & 0x3f;
			h4 = bits & 0x3f;

			// use hexets to index into b64, and append result to encoded string
			tmp_arr[ac++] = b64.charAt(h1) + b64.charAt(h2) + b64.charAt(h3) + b64.charAt(h4);
		} while (i < data.length);

		enc = tmp_arr.join('');

		switch (data.length % 3) {
		case 1:
			enc = enc.slice(0, -2) + '==';
			break;
		case 2:
			enc = enc.slice(0, -1) + '=';
			break;
		}

		return enc;
	}

	function base64_decode (data) {
		// http://kevin.vanzonneveld.net
		// +   original by: Tyler Akins (http://rumkin.com)
		// +   improved by: Thunder.m
		// +      input by: Aman Gupta
		// +   improved by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
		// +   bugfixed by: Onno Marsman
		// +   bugfixed by: Pellentesque Malesuada
		// +   improved by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
		// +      input by: Brett Zamir (http://brett-zamir.me)
		// +   bugfixed by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
		// -    depends on: utf8_decode
		// *     example 1: base64_decode('S2V2aW4gdmFuIFpvbm5ldmVsZA==');
		// *     returns 1: 'Kevin van Zonneveld'
		// mozilla has this native
		// - but breaks in 2.0.0.12!
		//if (typeof this.window['btoa'] == 'function') {
		//    return btoa(data);
		//}
		var b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
		var o1, o2, o3, h1, h2, h3, h4, bits, i = 0,
			ac = 0,
			dec = "",
			tmp_arr = [];

		if (!data) {
			return data;
		}

		data += '';

		do { // unpack four hexets into three octets using index points in b64
			h1 = b64.indexOf(data.charAt(i++));
			h2 = b64.indexOf(data.charAt(i++));
			h3 = b64.indexOf(data.charAt(i++));
			h4 = b64.indexOf(data.charAt(i++));

			bits = h1 << 18 | h2 << 12 | h3 << 6 | h4;

			o1 = bits >> 16 & 0xff;
			o2 = bits >> 8 & 0xff;
			o3 = bits & 0xff;

			if (h3 == 64) {
				tmp_arr[ac++] = String.fromCharCode(o1);
			} else if (h4 == 64) {
				tmp_arr[ac++] = String.fromCharCode(o1, o2);
			} else {
				tmp_arr[ac++] = String.fromCharCode(o1, o2, o3);
			}
		} while (i < data.length);

		dec = tmp_arr.join('');
		dec = utf8_decode(dec);

		return dec;
	}

	/********************************************************/


	function parse_signed_request(signed_request, secret) {
	  signed_request = signed_request.split('.');
	  var encoded_sig = signed_request[0];
	  var payload = signed_request[1];

	  //var sig = base64_decode(encoded_sig);
	  payload = base64_decode(payload);

	  // Removing null character \0 from the JSON data
	  payload = payload.substring(0, payload.length - 1);

	  data = JSON.parse(payload);

	  if (data.algorithm.toUpperCase() != 'HMAC-SHA256') {
		return 'Unknown algorithm. Expected HMAC-SHA256';
	  }

	  // TODO: Check signature!

	  return data;
	}
	
	
	win['parse_signed_request'] = parse_signed_request;
	
})(window);


(function(WT){
	if (!window.Webtrends){
		return;
	}
	// internal vars
	var fbAsyncInitOriginal,
		fbpi;
	function webtrendsFbAsyncInitWrapper(FBPI){
		if (fbAsyncInitOriginal && !(fbAsyncInitOriginal.hasRun===true)){
			fbAsyncInitOriginal()
			fbAsyncInitOriginal.hasRun=true;
		}
		FBPI.fbAsyncInit();
	}
	// plugin constructor
	function FBPlugin() {
		this.dcs = {};
		this.config = {};
		this.FBReadySemphore = 0;
		this.init();
	}
	FBPlugin.prototype=function(){
		//private vars
		var keyMap = {'app_data':'fb_ad','admin':'fb_pa','id':'fb_pid','liked':'fb_fan',
					'country':'fb_uc','localse':'fb_ul','min':'fb_uam'},
			tags = {},
			convEvents = 
				{'auth.login':1, 
				'auth.logout':1, 
				'edge.create':1, 
				'edge.remove':1, 
				'message.send':1,
				'comments.add':1, 
				'comment.remove':1,
				'comment.create':1
				}, // conversion events
			config = {},
			uid = null,
			token = null,
			has_run = false;
			app_data={};
		return {
			init:function(){
				var FBPI = this;
				this.tags = tags;// make public
				
				this.user_status = null;
				//increment Counter... waiting on fbAsyncInit.
				this.FBReadySemphore++;					
				
				if(window.fbAsyncInit&&!window.fbAsyncInit.hasRun){
					//On an Async FB page, but we ran before FB loaded.
					fbAsyncInitOriginal = window.fbAsyncInit;
					window.fbAsyncInit = function(){webtrendsFbAsyncInitWrapper(FBPI);};
				} else if (!(window.fbAsyncInit) && window.FB) {
					// non Async FB page.  
					window.setTimeout( function(){
						webtrendsFbAsyncInitWrapper(FBPI);
					}, 1 );
				} else if (window.fbAsyncInit&&window.fbAsyncInit.hasRun) {
					//We loaded after FB has already loaded.
					window.setTimeout( function(){
						webtrendsFbAsyncInitWrapper(FBPI);
					}, 1 );
				} else if (!window.fbAsyncInit){
					// possible they aren't using FB js on page, even though they have plugin?
					window.setTimeout( function(){
						webtrendsFbAsyncInitWrapper(FBPI);
					}, 300 );
					window.fbAsyncInit = function(){webtrendsFbAsyncInitWrapper(FBPI);};
				}
			},
			onLogon : function(sess){
				if (sess && 'userID' in sess){
					// oauth2.0
					uid   = sess.userID;
					token = sess.accessToken;
					if (sess.signedRequest){
						try {
							sr = parse_signed_request(sess.signedRequest);
							this.addSignedRequest(sr);
						} catch (e) {
							if(this.dcs && this.dcs.errors){
								this.dcs.errors.push(e);
							}
						}
					}
				} else {
					// pre oauth2.0
					uid   = sess.uid;
					token = sess.access_token;
				}
				//increment Counter...  waiting for getProfile	
				this.FBReadySemphore++;	
				this.getProfile(); 
			},
			/**
			 * Run the initial setup, tag setup
			*/
			run_setup : function (response) {
				has_run = true;
				if (!response) return;
				var WTFB = this,
					sess = response.session ? response.session : response.authResponse;
				
				this.user_status = response.status; //connected or notConnected string
				
				tags["WT.fb_tv"] = "10.2.23";
				
				var queryParams = Webtrends.getQryParams(location.search);

				if (sess!='undefined' && sess != undefined) {
					// to have session, they must have authorized/installed app
					this.onLogon(sess); 
					tags["WT.fb_ses"] = "1";
				} else {
					tags["WT.fb_ses"] = "0";
				}
				if ('_apiKey' in FB){
					tags["WT.fb_appid"] = FB._apiKey;
				}
				if ('_inCanvas' in FB && FB._inCanvas===true){
					tags["WT.fb_ctx"] = "1";
					if (queryParams && queryParams.ref){
						if (queryParams.type){
							tags['WT.fb_ref'] =queryParams.ref + "_" + queryParams.type;
						} else {
							tags['WT.fb_ref'] = queryParams.ref;
						}
					} else if (queryParams && queryParams.type){
						tags['WT.fb_ref'] = queryParams.type;
					}
				} else {
					tags["WT.fb_ctx"] = "0";// social plugins off fb
				}
				// this is hokey, check fb all_js to see if updated
				// what doc says:  https://github.com/facebook/connect-js/blob/master/src/core/event.js#L59
				//  'comments.create' doesn't work,
				//  'comments.remove'  doesn't to work
				//  'comment.create','comment.remove'   don't currently work, but will soon
				var events = new Array('auth.login', 'auth.logout', 'edge.create', 'edge.remove', 'message.send',
					'comments.add', 'comment.remove','comment.create');
				for(var thisEvent = 0; thisEvent < events.length; thisEvent++) {
					(function(thisEvent) {
						FB.Event.subscribe(events[thisEvent], function(response) {
							 WTFB.subscriptionCallback(events[thisEvent], response) 
						});
					})(thisEvent);
				}

				// lets not trust we are getting SR, lets look for AD:
				// we get app_data in qs on app canvas views (but not tab) 5/11
				if (queryParams && queryParams.app_data){
					this.addAppData(queryParams.app_data);
				}
				if (queryParams && queryParams.mc_id){
					tags['WT.mc_id'] = queryParams.mc_id;
				}
				if (queryParams.qryparams && queryParams.mc_ref){
					tags['WT.mc_ref'] = queryParams.mc_ref;
				}
				if (window.fb_signed_request){
					this.addSignedRequest(window.fb_signed_request);
					tags["WT.fb_sr"] = "1";
				} else {
					tags["WT.fb_sr"] = "0";
					if (FB._locale)  tags["WT.fb_ul"] = FB._locale;
				}
				
				// referrer:
				if ((window.document.referrer!="")&&(window.document.referrer!="-")){
					if (!(navigator.appName=="Microsoft Internet Explorer"&&parseInt(navigator.appVersion)<4)){
						//tags["DCS.dcsref"] = =window.document.referrer;
					}
				}
			},
			fbAsyncInit : function() {
				var WTFB = this;
				if (window.FB){
					var setupHasRun = false;
					var timeout = window.setTimeout( function(){
						if(setupHasRun) 
							return;
						setupHasRun = true;
						// well, just in case we don't get fb callback
						WTFB.run_setup({status:'notconnected'});
						//decrement Counter...	done waiting on fbAsyncInit.
						WTFB.FBReadySemphore--;	
						WTFB.checkReady();
					}, 1000 );

					FB.getLoginStatus(function(response) {
						if(setupHasRun) 
							return; 
						setupHasRun = true;
						window.clearTimeout(timeout);

						WTFB.run_setup(response);
						// notify we got the callback
						//decrement Counter...	done waiting on fbAsyncInit.
						WTFB.FBReadySemphore--;	
						WTFB.checkReady();
					});
					has_run = true;
					tags["WT.fb_js"] = "1";
				} else {
					setTimeout(function(){
						
						if (!window.FB){
							// abandon and do the rest????
							tags["WT.fb_js"] = "0";
							//decrement Counter...	done waiting on fbAsyncInit.
							WTFB.FBReadySemphore--;	
						} else {
							FB.getLoginStatus(function(response) {
								WTFB.run_setup(response);
								// notify we got the callback
								//decrement Counter...	done waiting on fbAsyncInit.
								WTFB.FBReadySemphore--;	
							});
							has_run = true;
							tags["WT.fb_js"] = "1";
						}
						WTFB.checkReady();
					},1000)
				}
			},
			checkReady: function () {
				if (this.FBReadySemphore == 0) 
					this.setReady();
			},
			setReady: function () {
				var self = this; //No dual tagging support for now....
				Webtrends.registerPlugin('facebook',function(dcs,config){
					self.config = config;
					self.dcs = dcs;
					Webtrends.addTransform(function(dcs){
						try {
							var omap = {'fb_appid':'fb_aid','fb_g':'fb_ug','fb_fc':'fb_ufc','fb_cl':'fb_ucl','fb_isauth':'fb_ua','fb_fan':'fb_pl'};
							for (key in omap){
								if (key in dcs.WT) dcs.WT[omap[key]] = dcs.WT[key];
							}
						} catch (e) {}
					},'all');
					/* Object to Array Conversion*/
					function _otoa_(obj, dcs){
						var x,  tags = {'WT':dcs.WT,'DCS':dcs.DCS,'DCSext':dcs.DCSExt,'fake':{}};
						for (n in obj){
							if (n.split('.').length) {
								tag = n.split('.')[0];
								tags[tag][n.replace(tag+'.','')] = obj[n];
							}
						}
					};
					Webtrends.addTransform(function(dcs){
						_otoa_(window.Webtrends.FBPlugin.tags, dcs);  // write in tags
					},'collect');
				});
			},
			/*
			 * add the app_data from facebook to tagging
			 * Since fb only gives us one name/value pair (app_data=value) to work with
			 * 	we overload the value to have sub-name/value paris using non &= splits
			 * 	if app_data=somevalue, it uses somevalue
			 * else if:
			 *      app_data=yourname;value:WT.mc_id;123:WT.cg_n;products
			 *      OR
			 *      app_data=yourname+value:WT.mc_id+123:WT.cg_n+products
			 *      OR
			 *      app_data=yourname value:WT.mc_id 123:WT.cg_n products
			 *      
			 *      it parses After the first :WT. and uses name/value pairs split
			 *      by : between pairs, and ; or + between name/value
			 *  also:
			 * 		stores all in this.app_data as object {name:value,name2:value2}
			 */
			addAppData : function( ad ) {
				if (ad && !this.addAppData.hasRun){
					ad = ad.replace(" ", ";").replace("+",";");
					var pairs=ad.split(":");
					for (var i=0;i<pairs.length;i++){
						if (pairs[i].indexOf(";")!=-1){
							app_data[pairs[i].split(";")[0]] = pairs[i].split(";")[1];
						} else if (pairs[i].indexOf("+")!=-1){
							app_data[pairs[i].split("+")[0]] = pairs[i].split("+")[1];
						}
					}
					// look for custom app_data tags
					if (pairs.length > 1){
						for (var n in app_data){
							if (n.indexOf("WT.")!=-1||n.indexOf("DCS.")!=-1){
								tags[n] =  app_data[n];
							}
						}
					}
					this.addAppData.hasRun=true;
				}
			},
			/*
			 * add the signed_request from facebook 
			 */
			addSignedRequest : function( signed_request ) {
				if (signed_request.app_data){
					this.addAppData(signed_request.app_data);
				}
				this.loopValues(signed_request);
			},
			loopValues : function( obj ) {
				for (key in obj){
					value = obj[key];
					if (typeof(value) == 'object') {
						this.loopValues(value);
					}
					else {
						if (key.indexOf("WT.") !== -1){
							tags[name] = value;
						} else {
							if (keyMap[key]) {
								tags['WT.' + keyMap[key]] = value;
							}
						}
					}
				}
			},
			// generates a Graph API url for the user's basic profile, with callback, optional token
			profileUrl : function() {
				if (token) {
					return "https://graph.facebook.com/" + uid + "?access_token=" + token + "&callback=window.Webtrends.FBPlugin.getProfileCB"
				} else {
					return "https://graph.facebook.com/" + uid + "?callback=window.Webtrends.FBPlugin.profileCB"
				}
			},
			/*
			* generates a Graph API url for a list of the user's friends, with callback and token
			*/
			friendsUrl : function() {
				if (token)
					return "https://graph.facebook.com/" + uid + "/friends?access_token=" + token + "&callback=window.Webtrends.FBPlugin.friendsCB"
				// no token, no worries.
				return false;
			},
			getProfile : function() {
				var self = this;
				if(!self.profileUrl)
					self = window.Webtrends.FBPlugin;
				Webtrends.loadJS( self.profileUrl(),false );
			},
			// callback to process the Graph API basic profile
			getProfileCB : function( data ) {
				var self = this;
				if(!self.parseCurrentLocation)
					self = window.Webtrends.FBPlugin;
				
				if (config.userflag){
					tags['WT.fb_uid'] = data.id;
				}
				tags['WT.fb_ul'] = data.locale;
				if (data.gender) {
					tags['WT.fb_ug'] = (data.gender.match(/^m/i) ? "male" : "female");
				}
				tags['WT.fb_ucl'] = self.parseCurrentLocation( data.location );
				tags['WT.fb_uau'] = (token=='' ? null : '1');

				// trigger the friends request if there is a token
				if (token) {
					//increment Counter...		waiting on friendsCB.
					self.FBReadySemphore++;	
					Webtrends.loadJS( self.friendsUrl(),false )
				} 
				// notify we got the callback
				//decrement Counter...	done waiting for getProfile
				self.FBReadySemphore--;				
				self.checkReady();
			},
			// callback to process the Graph API friends list
			friendsCB : function( data ) {
				if (data.data && (data.data.length && data.data.length > -1)) {
					tags['WT.fb_fc'] = data.data.length;
				}
			
				var self = this;
				if(!self.dcs)
					self = window.Webtrends.FBPlugin;
				//decrement Counter...	done waiting for friendsCB
				self.FBReadySemphore--;				
				self.checkReady();	
			},
			parseCurrentLocation : function( data ) { 
				if(data==null)
					return null
				return data.name
			},
			subscriptionCallback : function (eventType, data) {
				var self = this;
				if(!self.dcs)
					self = window.Webtrends.FBPlugin;
				this.eventType = eventType;
				if (convEvents[eventType]){
					tags = {};
					if ({'comments.add':1,'comment.create':1,'comments.create':1}[eventType]){
						eventType='comments.add';
					}
					if (eventType === 'auth.login'&&data&&data.session){
//						if (this.user_status == 'notConnected') {
//						}
						this.onLogon(data.session);
					}
					if ((eventType === 'comments.add') && data.widget && data.widget._attr) {
						tags['WT.fb_xid'] =data.widget._attr.xid;
					}
					
					var EventTypeMap = {
						'auth.login':"Login", 
						'auth.logout':"Logout", 
						'edge.create':"Like", 
						'edge.remove':"Unlike", 
						'message.send':"Share",//Todo double check this one is a share...
						'comments.add':"CommentsAdd", 
						'comment.remove':"CommentRemove",
						'comment.create':"CommentAdd"};
					
					tags['WT.conv'] = "Facebook:"+ EventTypeMap[eventType];
					tags['WT.convval'] = 'fb_' + eventType;
					tags['WT.soc_action'] = "Facebook:"+EventTypeMap[eventType];
					tags['WT.dl'] =  "111" ;
					tags["DCS.dcsuri"] = "/multitrackevents/fb_" + eventType;
					self.dcs.dcsMultiTrack({args:tags});
				}
			}
		}
	}()
	
	Webtrends.FB = {
		ui:function(params,callback){
			//var fbpi = window.Webtrends.FBPlugin;
			if ('method' in params && params.method === 'feed' && window.FB){
				window.FB.ui(params,function(response){
					if (response && response.post_id) {
						Webtrends.multiTrack({argsa:["DCS.dcsuri","/multitrackevents/fb.share_finished","WT.conv","1","WT.convval","fb_share","WT.fb_postid",response.post_id],
							callback:function(){
								if (callback) callback(response);
							}
						});
					} else {
						if (callback) callback(response);
					}
				});
			} else if (window.FB) {
				window.FB.ui(params,callback);
			} else {
				// ???
				if (callback) callback({});
			}
		}
	}
	window.Webtrends.FBPlugin = new FBPlugin();
	
})(window.Webtrends);

