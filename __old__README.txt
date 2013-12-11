 *********************************** 
 * built date: 12 April 2010
 * by shondll
 ***********************************
 

 *** Project description ***
This is a very simple project for the LPC-H2294 board produced by Olimex Ltd. The board 
features LPC2294 processor. When the demo is started LED starts flashing with a period of about 0.5 seconds. The project is configured to run in the embedded FLASH memory of the device.

 *** Hardware Requirements ***
-- Demo board LPC-H2294 by Olimex
-- ARM-USB-OCD or ARM-USB-TINY ARM debbugger by Olimex

 *** Installation ***
The workspace is configured to work with an installation of Olimex OpenOCD rev.G. It is highly
recommended to keep the default installation directory ("C:\gccfd\"). This workspace directory 
"project_LPC-H2294" should be copied/moved in the installation directory (again "C:\gccfd\" if using
defaults).

If you haven't installed the JTAG debugger yet, please connect and install it using the 
drivers in the installation folder before moving on.

 *** Running the Demo ***
When you start Eclipse choose File->Switch Workspace->Other... and then select
the folder "project_LPC-H2294". 

Build the project (right click the project->Build Project).

Open the file "main.c" and with the editor window still active select
Run->External tools->(The name of your debugger). If the acive window is not the editor a popup
window will appear displaying an error!

You can now start the program by selecting: 
Run->Debug Configurations...->LPC-2294_flash and then press the Debug button in the lower right 
corner of the window.

Switch to Debug perspective and use the buttons for debugging above the editor window.

Enjoy ;)

