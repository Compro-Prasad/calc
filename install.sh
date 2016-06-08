#!/bin/bash

echo Compiling...
make
if [ $? -eq 0 ]; then
    echo Compilation Finished
    if [[ $(id | grep sudo > /dev/null;echo $?) -eq 0 || "$USER" = "root" ]]; then
	sudo make install
	if [ $? -eq 0 ]; then
	    echo "Installation Finished"
	    make cleanall
	    echo "Cleaned up residual files"
	    echo -n "Do you want to launch the application? "
	    read input
	    case $input in
		"y" | "Y" | "yes" | "Yes" )
		    calc
		    if [ $? -eq 0 ]; then
			echo "You can now remove the calc project tree"
		    else
			echo Unable to launch application
			echo ".bashrc is config file for your bash shell"
			echo -n "Do you want to edit your .bashrc file{y/n/q only}? "
			read input
			if [[ "$input" = "y" && -f "$HOME/.bashrc" ]]; then
			    config="$HOME/.bashrc"
			else
			    if [ "$input" = "q" ]; then exit; fi
			    echo -n "Enter the absolute file path to your shell config file: "
			    read config
			    if [ ! -f "$config" ]; then
				echo "'$config' file not found"
				exit
			    fi
			fi
			if [ ! -w "$config" ]; then
			    echo "Shell config file is not writable"
			    exit
			fi
			echo -n "Enter the absolute path to your installation directory of calc: "
			read install_dir
			if [ -d "$install_dir" ]; then
			    echo "Changing your config file..."
			    echo 'export $PATH="$PATH:$install_dir"' >> $config
			    cd $install_dir
			    ./calc
			    echo "Config file changed"
			    echo "Restart terminal to reload config file"
			fi
		    fi;;
		"n" | "N" | "no" | "No" )
		    exit;;
	    esac
	fi
    else
	echo "Not Installed"
	echo "Try changing value of INSTALL_DIR in the Makefile"
    fi
fi
