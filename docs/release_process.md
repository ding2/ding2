# Release proces

This document describes how to create a new release.

## Naming

The naming scheme is based on a combination of [Drupal release name conventions](https://www.drupal.org/node/1015226) and [semantic versioning](http://semver.org/).

Each release is named in the format `[Drupal major version].x-[Project major version].[Project minor version].[Project patch version]-[Pre-release information (optional)]`.

An example name could be `7.x-3.4.2-rc1`.

## Howto

1. Make sure you have a clone of this repository on your local machine which is up to date with the latest changes on GitHub `git clone git@github.com:ding2/ding2.git`
2. Checkout the existing `release` branch `git checkout release`
3. Rebase the release branch on master `git rebase master`
4. In `ding2.info` set `version = 7.x-3.4.2-rc1`
5. Amend your changes to the existing commit `git add ding2.info && git commit -m "Set version in info file to 7.x-3.4.2-rc1" --amend`
6. Force push your changes to the release branch on GitHub `git push origin release --force`
7. Go to [Circle CI](https://circleci.com/gh/ding2/ding2) and ensure that the build has been completed successfully
8. Under the build find the "Artifacts" section and download the archive named `ding2-[Commit SHA].tar.gz` to your local machine
9. Rename the downloaded file according to the release name e.g. `ding2-7.x-3.4.2-rc1.tar.gz`
10. In the git repository tag the commit with the release name og push it `git tag 7.x-3.4.2-rc1 && git push origin 7.x-3.4.2-rc1`  
11. Find the tag [on GitHub under releases](https://github.com/ding2/ding2/releases) and on the tag details page click "Edit tag"
12. Set the title to the release name `7.x-3.4.2-rc1` and upload the previously downloaded and renamed file to the release
13. If the release is a release candidate, beta or the like then select the "This is a pre-release" checkbox
14. Click "Publish release"