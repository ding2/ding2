# Ding user roles
This feature holds the default roles used in standard ding2 installations. The
different roles are described below. This feature does not set the permissions
for the roles as this is up to the features them self (news, events, etc.) to do
so. When a given feature defines permissions e.g. for news, these can be
overridden by local changes by using the feature override module.

This module is based on recommendations from D!ng.team and feedback from editor
groups at KKB and AAKB.

## Guest blogger (gæsteblogger)
The idea behind this role is to allow people not working in the library to
create content for a shorter period. This could be an author that it invited to
write blog/news post for a library.

There should be some control (workflow) over when this roles is allowed to
create and publish posts. This will be achieved by using organic groups and
workbench moderation module.

## Facilitator (formidler)
Editors are the ones responsible for creating standard content such as news and
events (things that changes almost every day). They should be able to published
posts created by guest bloggers.

## Local editors (lokalredaktør)
This group is facilitators with extended permissions to handle users, libraries,
pages, campaigns and opening hours. They are daily super-users that has access
to handle site content needed to run a ding2 site or local library on the site.

## Editors (redaktør)
They are an extension to the local editors that have access to more advanced
configuration options, such as cache clear, url alias and taxonomies. They have
access to handle basic site configuration and are able to change the site basic
behavior.

## Local administrator
This groups of user have premissions to make basic site configuration and the
same access as the above groups. So this should only be given to trusted super
users.

## Provider
Providers are the library users, which normally logges into the system using
library card or CPR number an they are only allowed to view content not create
new.

## Staff
This users are the library staff, which have limit premissions to edit there
profile2 profile with basic information about there role at their library.

## Administrator
This group of users have full access to all parts for the site and access to
alter any configuration they want.
