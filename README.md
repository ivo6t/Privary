How to run Privary browser
Option 1: Run directly from the folder

    Open a terminal and navigate to the Privary folder.

    Build the program:

make

    Run the browser:

./gui_browser

Option 2: Create a convenient command privary (optional)

To make running easier, you can create an alias in your shell:

    Open your shell config file (for example, .bashrc or .zshrc):

nano ~/.bashrc

    Add this line at the end (replace /full/path/to/Privary with your actual folder path):

alias privary='/full/path/to/Privary/gui_browser'

    Save and close the editor.

    Reload the shell config:

source ~/.bashrc

    Now you can just run:

privary

Option 3: Install system-wide (requires sudo/admin rights)

    Copy the binary to a system folder so it’s available anywhere:

sudo cp /full/path/to/Privary/gui_browser /usr/local/bin/privary
sudo chmod +x /usr/local/bin/privary

    Now you can open a terminal and just type:

privary

