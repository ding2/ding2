backend default { 
  .host = "127.0.0.1";
  .port = "80";
}
 
# Respond to incoming requests.
sub vcl_recv {
  # Make sure that the client ip is forward to the client.
  if (req.restarts == 0) {
    if (req.http.x-forwarded-for) {
      set req.http.X-Forwarded-For = req.http.X-Forwarded-For + ", " + client.ip;
    } 
    else {
      set req.http.X-Forwarded-For = client.ip;
    }
  }

  # Allow forms to be posted.
  if (req.request == "POST") {
    return (pass);
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
    req.url ~ "^/ooyala/ping$" ||
    req.url ~ "^/admin/build/features" ||
    req.url ~ "^/info/.*$" ||
    req.url ~ "^/flag/.*$" ||
    req.url ~ "^.*/ajax/.*$" ||
    req.url ~ "^.*/ahah/.*$" ||
    req.url ~ "^.*/edit.*$") {
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
  if (req.url ~ "(?i)\.(png|gif|jpeg|jpg|ico|swf|css|js|html|htm)(\?[a-z0-9]+)?$") {
    unset req.http.Cookie;
  }

  # Remove all cookies that Drupal doesn't need to know about. ANY remaining
  # cookie will cause the request to pass-through to Apache. For the most part
  # we always set the NO_CACHE cookie after any POST request, disabling the
  # Varnish cache temporarily. Cookies are only removed for not logged in users
  # theme with role 1.
  if (req.http.Cookie && req.http.X-Drupal-Roles == "1") {
    set req.http.Cookie = ";" + req.http.Cookie;
    set req.http.Cookie = regsuball(req.http.Cookie, "; +", ";");
    set req.http.Cookie = regsuball(req.http.Cookie, ";(SESS[a-z0-9]+|NO_CACHE)=", "; \1=");
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
    set resp.http.X-Cache = "HIT";
  }
  else {
    set resp.http.X-Cache = "MISS";
  }
}

# Code determining what to do when serving items from the Apache servers.
sub vcl_fetch {
  # Allow items to be stale if needed.
  set beresp.grace = 6h;

  # If ding_varnish has marked the page as cachable simeply deliver is to make
  # sure that it's cached.
  if (beresp.http.X-Drupal-Varnish-Cache) {
    return (deliver);
  }
}
