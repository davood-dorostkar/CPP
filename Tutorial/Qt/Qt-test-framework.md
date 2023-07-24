## Make a tree project
`File > new > Other project > Subdirs project`  
this will make a folder that contains sub-projects
## Add subprojects
making the first subproject will come up automatically. for other subprojects you should:  
on the main tree, `right-click > new subproject`  
> if you set the `build system` to `qmake`, then the subproject will be shown under the main tree. if you use `cmake` it will be shown outside the main project, but don't worry, in reality, it is inside.  
## Add unit test
use `add subproject > other project > auto test project`  
`qmake` is preferred for better visuality  
make sure `Generate initialization and cleanup code` is selected  
## Relate test and app together
right-click on the test subproject and click `add existing files`, and add every `class.h` you want to be tested. a shortcut of that translation unit will be shown inside test folder  
> alternatively you can add this to `test.pro`: `HEADERS += ../app/myclass.h`  
go to `test/sources/someTest.cpp` and add:  
`#include "../app/myclass.h"`  
## Write the tests
inside test class, initiate an instance of that class like:  
`myclass *a;`  
inside the test functions, use the functions of the class like:  
`QVERIFY(a.myfunc()==1);`  
to only show pass or fail or  
`QCOMPARE(a.myfunc(),1);`  
to show the real vs expected values
## Do the test
in the buttom pane, open `test output`, or use `alt+8`  
click on the `run tests for current file`  
> if you run the project, the tests will be run also, and the output will be shown in the `application output` or `alt+3`