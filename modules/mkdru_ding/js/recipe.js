'use strict';

/**
 * Function designed to call functions in given order.
 * @param url
 * @returns {*}
 */
Drupal.mkdruProcessExternalUrl = function (url) {
  var process_callbacks = Drupal.settings.mkdruPreprocessExternalUrlCallbacks;

  process_callbacks.forEach(function(item, i, process_callbacks) {
    var urlCallback = window[item];

    if (typeof urlCallback === 'function') {
      url = urlCallback(url);
    }
  });

  return url;
};

/**
 * URL processing.
 * @param data
 * @returns {*}
 */
function ting_proxy(data) {
  var url = document.createElement("a");
  url.href = data;

  var ting_proxy = Drupal.settings.mkdru_ding.proxy_settings;

  if (ting_proxy.length > 0 && ting_proxy.hostnames.length > 0) {
    for (var i = 0; i < ting_proxy.hostnames.length; i++) {
      if (ting_proxy.hostnames[i].hostname === data.hostname && ting_proxy.hostnames[i].disable_prefix === 0) {
        var regexp = ting_proxy.hostnames[i].expression.regex;
        var replacement = ting_proxy.hostnames[i].expression.replacement;

        url = ting_proxy.prefix + data.href;

        if (regexp.length > 0 && replacement.length > 0) {
          url = url.replace(new RegExp(regexp), replacement);
        }
      }
      else {
        url = data;
      }
    }
  }

  return url;
}

function choose_url(data, proxyPattern) {
  // First try to prepare local_url from recipe.
  var local_url = data["md-url_recipe"] !== undefined ? prepare_url(data["md-url_recipe"][0], data) : null;

  var use_url_proxy = data["md-use_url_proxy"] !== undefined ? data["md-use_url_proxy"] : "0";

  // Use the proxyPattern.
  if (proxyPattern && use_url_proxy === "1") {
    if (local_url) {
      data["md-local-url"] = [];
      data["md-local-url"].push(local_url);
    }
    var ref_local_url = prepare_url(proxyPattern, data);
    if (ref_local_url) {
      return ref_local_url;
    }
  }

  // ProxyPattern failed, go for local.
  if (local_url) {
    return local_url;
  }

  // Process url before attach it to the template.
  if (data['md-electronic-url'] !== undefined) {
    data["md-electronic-url"][0] = Drupal.mkdruProcessExternalUrl(data["md-electronic-url"][0]);
  }

  // Local failed, go for resource.
  return data["md-electronic-url"] !== undefined ? data["md-electronic-url"][0] : null;
}

var XRef = function (url, text) {
  this.url = url;
  this.text = text;
};

function has_recipe (data) {
  var has = false;
  if (data["md-url_recipe"] !== undefined) {
     var recipe = data["md-url_recipe"][0];
     if (typeof recipe == "string" && recipe.length>0) {
       has = true;
     }
  }
  return has;
}

function getUrlFromRecipe (data) {
  if (has_recipe(data)) {
    return prepare_url(data["md-url_recipe"][0],data);
  } else {
    return null;
  }
}

function getElectronicUrls (data) {
  var urls = [];
  if (data["md-electronic-url"] !== undefined) {
    for (var i=0; i<data["md-electronic-url"].length; i++) {
      var linkUrl = data["md-electronic-url"][i];
      var linkText = data["md-electronic-text"][i];
      var ref = new XRef(linkUrl, (linkText.length === 0 ? "Web Link" : linkText));
      urls.push(ref);
    }
  }
  return urls;
}


// Prepares urls from recipes with expressions in the form:
// ${variable-name[pattern/replacement/mode]}, [regex] is optional
// eg. http://sever.com?title=${md-title[\s+//]} will strip all whitespaces.
function prepare_url(url_recipe, meta_data) {
    if (typeof url_recipe != "string" || url_recipe.length === 0) {
        return null;
    }
    if (typeof meta_data != "object") {
        return null;
    }
    try {
        return url_recipe.replace(/\${[^}]*}/g, function(match) {
          return get_var_value(match, meta_data);
        });
    } catch (e) {
        return "Malformed URL recipe: " + e.message;
    }
}

function get_var_value (expr_in, meta_data) {
    // Strip ${ and }.
    var expr = expr_in.substring(2, expr_in.length-1)
    if (expr == "") return "";
    // Extract name.
    var var_name = expr.match(/^[^\[]+/)[0];
    if (typeof meta_data[var_name] == "undefined") return "";
    else var var_value = meta_data[var_name][0];
    if (var_name.length < expr.length) { //possibly a regex
       var_value = exec_sregex(
          expr.substring(var_name.length+1, expr.length-1),
          var_value);
    }
    return var_value;
}

// Exec perl-like substitution regexes in the form: pattern/replacement/mode.
function exec_sregex (regex_str, input_str) {
    var regex_parts = ["", "", ""];
    var i = 0;
    for (var j=0; j<regex_str.length && i<3; j++) {
        if (j>0 && regex_str.charAt(j) == '/' && regex_str.charAt(j-1) != '\\')
            i++;
        else
            regex_parts[i] += regex_str.charAt(j);
    }
    var regex_obj = new RegExp(regex_parts[0], regex_parts[2]);
    return input_str.replace(regex_obj, regex_parts[1]);
}

function test_url_recipe() {
  var url_recipe = "http://www.indexdata.com/?title=${md-title[\\s+/+/g]}&author=${md-author}";
  var meta_data = { "md-title" : ["Art of Computer Programming"], "md-author" : ["Knuth"]}
  var final_url = prepare_url(url_recipe, meta_data);
  alert(final_url);
}
