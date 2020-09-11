# Running Tests

run the scripts in the following order:

* 1_buildAnwalic.sh
    * build the object files of the application to test
* 2_buildTest.sh
    * build the test code
* 3_deploy.sh
    * generate all dependencies needed by the application to test and the test
    * only deploy once, so that the Qt libraries exist in this folder
* 4_runTest.sh
    * runs all the test cases

When updating the tests you have to re-run 2_buildTest.sh, 3_deploy.sh and
4_runTest.sh . Re-run 1_buildAnwalic.sh if the object files have been cleaned
up.

