# Testing

## Pyramid

```
       /\
      /UI\
     /____\
    /Integr\
   /________\
  / Unittest \
 /____________\
```

## Motivation

The pyramid shows the hierarchy of different types of tests.

In the bottom we have unit tests which are good for low level testing
and should be used to reach all corners of the code. In this type of
test it's necessary to test both expected code, i.e. what input is
expected for normal execution, but also abnormal input to make sure
that the code doesn't break when it receives input it doesn't expect.

Integration testing tests the interaction between different systems or
services. Each system or service should be tested independently (e.g.
with unit tests), and the integration testing tests that they work
properly together. How does one service handle other services when
they function correctly, and how does it handle them when they send
unexpected data or fail in some way?

On the top we have user interface testing, which assumes that the
systems and applications are working correctly, i.e. we assume that
everything is working correctly and we're testing that the user
interface is working as expected. This also means that we won't
necessarily go into all edge cases in the user interface tests.

In Ding2 we use Behat with Mink for testing the user interface.
