1. Enable `shadow build`  
2. Set the address to your project address, in order not to make things elsewhere  

![](https://github.com/davood-dorostkar/Cplusplus_in_Qt/blob/main/images/shadow%20build.jpg)  
  
3. Set the config to `release` mode  
4. Set to 32bit for compatibility and ease of deployment (future steps)  
5. Build  

![](https://github.com/davood-dorostkar/Cplusplus_in_Qt/blob/main/images/release.JPG)  
  
6. Go to `<main project folder>/release` and copy the .exe file  
7. Paste it somewhere else and copy its address  
8. Open MinGW and enter: `cd <above address>`  
9. Then enter: `windeployqt <program name.exe>`  

![](https://github.com/davood-dorostkar/Cplusplus_in_Qt/blob/main/images/mingw.JPG)  
  
Application is ready