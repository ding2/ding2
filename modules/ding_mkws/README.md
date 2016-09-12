#Set up and configuration of the ding_mkws module.#

First, ensure that you have proxy config in your virtual host files for instance you are testing on.

##Settup virtual host files##

**Settings for the nginx vhost file**

`location /service-proxy/
{ proxy_set_header X-Forwarded-Host $host; 
proxy_set_header X-Forwarded-Server $host; 
proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for; 
proxy_pass http://sp-emusikk-no.eu.indexdata.com/service-proxy/; 
}`

**Settings for httpd vhost file**

`ProxyPass /service-proxy/ http://sp-emusikk-no.eu.indexdata.com/service-proxy/
ProxyPassReverse /service-proxy/ http://sp-emusikk-no.eu.indexdata.com/service-proxy/`

After download the module, download the third party libraries:
pz2 and jsrender

To accomplish this please follow the steps:

**Configure pz2 library**

1. cd to profile libraries folder
2. wget http://ftp.indexdata.dk/pub/pazpar2/pazpar2-1.12.5.tar.gz
3. tar -xvzf pazpar2-1.12.5.tar.gz
4. mv pazpar2-1.12.5 pz2
5. cd pz2/js
6. mv pz2.js ../
7. rm -rf !(pz2.js) //This step is optional

**Configure jsrender library**

1. cd to profile libraries folder
2. wget https://github.com//BorisMoore/jsrender/archive/master.zip
3. unzip master.zip
4. mv jsrender-master jsrender
5. rm -rf !(jsrender.min.js) // This step is optional

**Configure ding_mkws module**

1. Go to /admin/config/ding/mkws
2. Apply the following configs:
 * url of service: http://sp-emusikk-no.eu.indexdata.com/service-proxy/
 * username: emusik_no462
 * password: emusik_no462
 * service proxy url: /service-proxy/
3. Save form
