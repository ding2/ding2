# Release proces

This document describes how to create a new release.

## Naming

The naming scheme is based on a combination of [Drupal release name conventions](https://www.drupal.org/node/1015226) and [semantic versioning](http://semver.org/).

Each release is named in the format `[Drupal major version].x-[Project major version].[Project minor version].[Project patch version]-[Pre-release information (optional)]`. Pre-releases must include the string `rc` in `Pre-release information`.

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

8. In `ding2.info` set `version = 7.x-3.4.2-rc1`

9. Commit your changes `git add ding2.info ding2.make drupal.make && git commit --amend -m "Core: Bumped version to 7.x-3.4.2-rc1"`

10. In the git repository tag the commit with the release name og push changes and tag `git tag 7.x-3.4.2-rc1 && git push origin release  7.x-3.4.2-rc1 --force`

11. If the build completes then the release is automatically created on GitHub under [the projects releases](https://github.com/ding2/ding2/releases).
