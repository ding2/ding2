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

4. Clone the service library for ting.

	4.1. Make a fresh clone `git clone git@github.com:ding2/ting-client`

	4.2. Checkout the existing `release` branch `git checkout release`

	4.3. Rebase the release branch on master `git rebase master`

	4.5. Force push your changes to the release branch on GitHub `git push origin release --force`

	4.6. Tag the commit with the release name og push it `git tag 7.x-3.4.2-rc1 && git push origin 7.x-3.4.2-rc1`

5. Clone the service library for BPI.

	5.1. Make a fresh clone `git clone git@github.com:ding2/bpi-client`

	5.2. Checkout the existing `release` branch `git checkout release`

	5.3. Rebase the release branch on master `git rebase master`

	5.5. Force push your changes to the release branch on GitHub `git push origin release --force`

	5.6. Tag the commit with the release name og push it `git tag 7.x-3.4.2-rc1 && git push origin 7.x-3.4.2-rc1`

6. Update `ding2.make` to point to the new releases of `ting_client` and `bpi_client`.

7. Update `drupal.make` to point to the new ding2 release tag.

7. In `ding2.info` set `version = 7.x-3.4.2-rc1`

8. Commit your changes `git add ding2.info ding2.make drupal.make && git commit -m "Core: Bumped version to 7.x-3.4.2-rc1"`

9. Force push your changes to the release branch on GitHub `git push origin release --force`

10. Go to [Circle CI](https://circleci.com/gh/ding2/ding2) and ensure that the build has been completed successfully

11. Under the build find the "Artifacts" section and download the archive named `ding2-[Commit SHA].tar.gz` to your local machine

12. Rename the downloaded file according to the release name e.g. `ding2-7.x-3.4.2-rc1.tar.gz`

13. In the git repository tag the commit with the release name og push it `git tag 7.x-3.4.2-rc1 && git push origin 7.x-3.4.2-rc1`

14. Find the tag [on GitHub under releases](https://github.com/ding2/ding2/releases) and on the tag details page click "Edit tag"

15. Set the title to the release name `7.x-3.4.2-rc1` and upload the previously downloaded and renamed file to the release

16. If the release is a release candidate, beta or the like then select the "This is a pre-release" checkbox

17. Click "Publish release"
