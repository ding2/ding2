This module and it's two sub-modules adds the ability to log into the site through wayf.dk without any need for any external libraries installed on the server.

The usage of the module requires that you have an agreement with wayf.dk about usage of their identity provider service and that your have a valid set of SSL certificates.

# Login
Enable the module and go to /admin/config/people/wayf and fill out the information in the "Service provider" tab and then go to "Metadata (SP)" tab (after you have click "Save configuration"). You can use this metadata to create a new connection at http://janus.wayf.dk or you can use the path /wayf/metadata as import in janus.

For more information about configuration see the contribute module "wayf_dk_login".

# User creation
The user creation module requires that the provider you are using has support for creating new users. 
