# Loaders
<img width="350" height="107" alt="Screenshot 2025-09-03 234154" src="https://github.com/user-attachments/assets/49f6ede3-deb4-49e8-ac2c-a822e11469f0" />

The main part of this repository is to provide with a menu selector, where you can navigate through executable files with vim motions.

## Installing
First you need to have scoop installed on windows machine
### Installing scoop
Open powershell and type this: 
* <code>Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser</code>
* <code>Invoke-RestMethod -Uri https://get.scoop.sh | Invoke-Expression</code>

After installing run: <code>scoop status</code>

Here is scoop official page: https://scoop.sh/

### Installing bucket with scoop
Open powershell and type this:
* <code>scoop bucket add loaders https://github.com/Fire-coin/firecoin-scoop-loaders</code>
* <code>scoop install loaders</code>

After this you can type xmenu, and the menu with executables will pop up.

### Using prebuilt files
To use prebuilt files navigate to this directory: 
* <code>cd ~\scoop\apps\loaders\1.0.0\bin</code>

Now when you run xmenu, you will see the prebuilt programs.


## Using main program
### -> You navigate using vim motions only up and down, so by pressing j you move down by 1 and by pressing k you move up by 1
### -> To select an executable to be run, you need to press enter key, after selected exe file finishes running, program will prompt you to press enter to go back to the menu
### -> To exit menu press q or Q

# Prebuilt programs
Alongside with main.cpp, there are included 2 other files to test the it with them.

## Tree.exe
This file prompts user to enter directory from which to create a tree from, including files. If left empty or dot is entered the directory is defaulted to the current one it is in. The tree looks like this: 
<img width="858" height="550" alt="Screenshot 2025-09-01 153353" src="https://github.com/user-attachments/assets/509415ee-73cf-4cf1-becf-c2426433d183" />

## Table.exe
This file promts user to provide source file of space separated columns and new line separated rows, to create a table. Then it also prompts wheter to display it in console or output to the file. In the image are shown both console and file output from data.txt file.
<img width="867" height="919" alt="Screenshot 2025-09-03 233511" src="https://github.com/user-attachments/assets/ccc2e92a-5231-41ba-a27f-8f91c783def9" />

# Building
All files are independent of each other. Just compile files with below stated C++ version.
## main.cpp
-> you need C++ 17 or later because of filesystem header, also it is windows dependent
## tree.cpp
-> you need C++ 17 or later, cross platform
## table.cpp
-> idk, just dont use C++ 98 or older, cross platform
