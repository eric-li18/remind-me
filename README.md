# Remind Me (WIP)

A project created to solve the problem of missing deadlines by integrating C with shell scripting to efficiently monitor due dates and automate submissions.

![Demo](remindme_demo.gif)

_The demo reflects basic functionality, subject to change_

## Running the program

Open a bash terminal in the directory and run the command below to start the driver to add entries to monitor.

        $ ./run.sh

<!-- ## Built From:
![Selenium](https://www.seleniumhq.org/images/big-logo.png "Selenium")
<img src="https://www.seleniumhq.org/images/big-logo.png" width="150" height="150"><img src="https://www.python.org/static/opengraph-icon-200x200.png" width="150" height="150"><img src="https://www.macworld.co.uk/cmsdata/features/3608274/Terminalicon2_thumb800.png" width="250" height="150">
![Python](https://www.python.org/static/opengraph-icon-200x200.png  "Python") -->

## To Do List

1. Implement text handler
2. Figure out communication between local and VM

## Workflow

<img src="./other/remind-me workflow .png">

## Data and Signal Flow

<img src="./other/Text Handler.png">

## Bug List

1. set_crontab.sh does not work with Windows currently

## Required Installations

### Shell Script

The shell script requires a \*nix system with a bash terminal. If not, instructions can be found [here](https://docs.microsoft.com/en-us/windows/wsl/install-win10) for WSL, or [here](https://cmder.net/) for a console emulator. At the time of writing, the current Ubuntu version is 18.04 LTS.

### Python Script

This is assuming you have Python installed _(> 2.6)_, if not, the Anaconda distribution is recommended (Selenium and many other packages come with it), and can be found [here](https://www.anaconda.com/distribution/).

To work with Selenium:

1.  Download Selenium by python, via the command:

        pip install selenium

2.  Download the files along with the "`chromedriver.exe`" file in the same directory
