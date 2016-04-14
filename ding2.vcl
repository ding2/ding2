backend default {
  .host = "127.0.0.1";
  .port = "80";
}

# List of upstream proxies we trust to set X-Forwarded-For correctly.
acl upstream_proxy {
  "127.0.0.1";
  "172.21.0.0"/24;
}

# Respond to incoming requests.
sub vcl_recv {
  # Make sure that the client ip is forward to the client.
  if (req.restarts == 0) {
    if (client.ip ~ upstream_proxy && req.http.x-forwarded-for) {
      set req.http.X-Forwarded-For = req.http.X-Forwarded-For + ", " + client.ip;
    }
    else {
      set req.http.X-Forwarded-For = client.ip;
    }
  }

  if (req.request != "GET" && req.request != "HEAD") {
    /* We only deal with GET and HEAD by default */
    return (pass);
  }

  # Ensure that ding_wayf and SimpleSAMLphp is not cached.
  if (req.url ~ "^/simplesaml" || req.url ~ "^/wayf" || req.url ~ "^/gatewayf") {
    return (pipe);
  }

  # We'll always restart once. Therefore, when restarts == 0 we can ensure
  # that the HTTP headers haven't been tampered with by the client.
  if (req.restarts == 0) {
    unset req.http.X-Drupal-Roles;

    # We're going to change the URL to x-drupal-roles so we'll need to save
    # the original one first.
    set req.http.X-Original-URL = req.url;
    set req.url = "/varnish/roles";

    return (lookup);
  }

  # Do not cache these paths.
  if (req.url ~ "^/status\.php$" ||
    req.url ~ "^/update\.php$" ||
    req.url ~ "^/admin/build/features" ||
    req.url ~ "^/info/.*$" ||
    req.url ~ "^/flag/.*$" ||
    req.url ~ "^.*/ajax/.*$" ||
    req.url ~ "^.*/ahah/.*$" ||
    req.url ~ "^.*/edit.*$" ||
    req.url ~ "^.*/ding_availability.*$") {
    return (pass);
  }

  # Pipe these paths directly to Apache for streaming.
  if (req.url ~ "^/admin/content/backup_migrate/export") {
    return (pipe);
  }

  # Allow the backend to serve up stale content if it is responding slowly.
  set req.grace = 6h;

  # Use anonymous, cached pages if all backends are down.
  if (!req.backend.healthy) {
    unset req.http.Cookie;
  }

  # Always cache the following file types for all users.
  if (req.url ~ "(?i)\.(pdf|asc|dat|txt|doc|xls|ppt|tgz|csv|png|gif|jpeg|jpg|ico|swf|css|js)(\?[\w\d=\.\-]+)?$") {
    unset req.http.Cookie;
  }

  # Remove all cookies that Drupal doesn't need to know about. ANY remaining
  # cookie will cause the request to pass-through to Apache. For the most part
  # we always set the NO_CACHE cookie after any POST request, disabling the
  # Varnish cache temporarily. Cookies are only removed for not logged in users
  # theme with role 1 (anonymous user).
  if (req.http.Cookie && req.http.X-Drupal-Roles == "1") {
    set req.http.Cookie = ";" + req.http.Cookie;
    set req.http.Cookie = regsuball(req.http.Cookie, "; +", ";");
    set req.http.Cookie = regsuball(req.http.Cookie, ";(S?SESS[a-z0-9]+|NO_CACHE)=", "; \1=");
    set req.http.Cookie = regsuball(req.http.Cookie, ";[^ ][^;]*", "");
    set req.http.Cookie = regsuball(req.http.Cookie, "^[; ]+|[; ]+$", "");

    if (req.http.Cookie == "") {
      # If there are no remaining cookies, remove the cookie header. If there
      # aren't any cookie headers, Varnish's default behavior will be to cache
      # the page.
      unset req.http.Cookie;
    }
    else {
      # If there are any cookies left (a session or NO_CACHE cookie), do not
      # cache the page. Pass it on to Apache directly.
      return (pass);
    }
  }
  # Handle compression correctly. Different browsers send different
  # "Accept-Encoding" headers, even though they mostly all support the same
  # compression mechanisms. By consolidating these compression headers into
  # a consistent format, we can reduce the size of the cache and get more hits.
  # @see: http:// varnish.projects.linpro.no/wiki/FAQ/Compression
  if (req.http.Accept-Encoding) {
    if (req.http.Accept-Encoding ~ "gzip") {
      # If the browser supports it, we'll use gzip.
      set req.http.Accept-Encoding = "gzip";
    }
    else if (req.http.Accept-Encoding ~ "deflate") {
      # Next, try deflate if it is supported.
      set req.http.Accept-Encoding = "deflate";
    }
    else {
      # Unknown algorithm. Remove it and send unencoded.
      unset req.http.Accept-Encoding;
    }
  }
  return (lookup);
}

sub vcl_deliver {
  # If the response contains the X-Drupal-Roles header and the request URL
  # is right. Copy the X-Drupal-Roles header over to the request and restart.
  if (req.url == "/varnish/roles" && resp.http.X-Drupal-Roles) {
    set req.http.X-Drupal-Roles = resp.http.X-Drupal-Roles;
    set req.url = req.http.X-Original-URL;
    unset req.http.X-Original-URL;
    return (restart);
  }

  # If responces X-Drupal-Roles is not set, move it from the request.
  if (!resp.http.X-Drupal-Roles) {
    set resp.http.X-Drupal-Roles = req.http.X-Drupal-Roles;
  }

  # Remove server information
  set resp.http.X-Powered-By = "Ding T!NG";

  # Debug
  if (obj.hits > 0 ) {
    set resp.http.X-Varnish-Cache = "HIT";
  }
  else {
    set resp.http.X-Varnish-Cache = "MISS";
  }
}

# Code determining what to do when serving items from the Apache servers.
sub vcl_fetch {
  # Allow items to be stale if needed.
  set beresp.grace = 6h;

  # We need this to cache 404s, 301s, 500s. Otherwise, depending on backend but
  # definitely in Drupal's case these responses are not cacheable by default.
  if (beresp.status == 404 || beresp.status == 301 || beresp.status == 500) {
    set beresp.ttl = 10m;
  }

  # Don't allow static files to set cookies.
  # (?i) denotes case insensitive in PCRE (perl compatible regular expressions).
  # This list of extensions appears twice, once here and again in vcl_recv so
  # make sure you edit both and keep them equal.
  if (req.url ~ "(?i)\.(pdf|asc|dat|txt|doc|xls|ppt|tgz|csv|png|gif|jpeg|jpg|ico|swf|css|js)(\?[\w\d=\.\-]+)?$") {
    unset beresp.http.set-cookie;
  }

  # If ding_varnish has marked the page as cachable simeply deliver is to make
  # sure that it's cached.
  if (beresp.http.X-Drupal-Varnish-Cache) {
    return (deliver);
  }
}

# In the event of an error, show friendlier messages.
sub vcl_error {
  # Redirect to some other URL in the case of a homepage failure.
  #if (req.url ~ "^/?$") {
  #  set obj.status = 302;
  #  set obj.http.Location = "http://backup.example.com/";
  #}

  # Otherwise redirect to the homepage, which will likely be in the cache.
  set obj.http.Content-Type = "text/html; charset=utf-8";
  synthetic {"
<html>
<head>
  <title>Page Unavailable</title>
  <style>
    body { background: #303030; text-align: center; color: white; }
    #page { border: 1px solid #CCC; width: 500px; margin: 100px auto 0; padding: 30px; background: #323232; }
    a, a:link, a:visited { color: #CCC; }
    .error { color: #222; }
  </style>
</head>
<body onload="setTimeout(function() { window.location = '/' }, 5000)">
  <div id="page">
    <h1 class="title">Page Unavailable</h1>
    <p>The page you requested is temporarily unavailable.</p>
    <p>We're redirecting you to the <a href="/">homepage</a> in 5 seconds.</p>
    <div class="error">(Error "} + obj.status + " " + obj.response + {")</div>
  </div>
</body>
</html>
"};
  return (deliver);
}
