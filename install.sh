#!/bin/bash

function replace_()
{
    read input
    if [ "$input" = "n" ]; then
	if [ -z "$2" ]; then
	    sed "s/$1/\/\/$1/g" src/include/calc_features.hpp > calc_features.temp
	else
	    sed "s/$2/$1/g" src/include/calc_features.hpp > calc_features.temp
	fi
	rm src/include/calc_features.hpp
	mv calc_features.temp src/include/calc_features.hpp
    elif [ "$input" = "y" ]; then
	if [ -z "$2" ]; then
	    sed "s/\/\/$1/$1/g" src/include/calc_features.hpp > calc_features.temp
	else
	    sed "s/$1/$2/g" src/include/calc_features.hpp > calc_features.temp
	fi
	rm src/include/calc_features.hpp
	mv calc_features.temp src/include/calc_features.hpp
    fi
}

echo -n 'Do you want a custom install[recommended](y/n)? '
read input
if [ "$input" = "y" ]; then
    echo "Stable features[e(nable all)/o(ne by one)]:"
    read input
    if [ "$input" = "o" ]; then
	echo -en "\tDo you want optr/num stack details(helpful for programmers)? "
	replace_ "#define OPTR_DETAILS"
	replace_ "#define NUM_DETAILS"

	echo -en "\tDo you want the suming feature(for everyone)? "
	replace_ "#define SUM"

	echo -en "\tDo you want factorizing feature(for everyone)? "
	replace_ "#define FACTORIZE"

	echo -en "\tDo you want calculation steps(not flexible)? "
	replace_ "#define STEPS_CMD"

	echo -en "\tDo you want the ability to change angle type? "
	replace_ "#define CHANGE_ANGLE"

	echo -en "\tDo you need direct input help commands? "
	replace_ "#define HELP_CMD"

	echo -en "\tDo you ever want a very lengthy and memory consuming calculation? "
	replace_ "#define SPEED_UP" "#define ACCELERATE_UP"

	echo -en "\tDo you want shell input features? "
	replace_ "#define SHELL_INPUT"

	echo -en "\tDo you want application direct input? "
	replace_ "#define DIRECT_INPUT"

	echo -en "\tDo you want to record calculation time? "
	replace_ "#define CALC_PROCESS_TIME"

	echo -en "\tDo you want prompt feature? "
	replace_ "#define PROMPT"

	echo -en "\tDo you need defining constants? "
	replace_ "#define CONST_CMDS"

	echo -en "\tDo you want answers to be recorded? "
	replace_ "#define ANS_CMD"

	echo -en "\tDo you want to access bash from within your calculator? "
	replace_ "#define SHELL_CMD"

	echo -en "\tDo you want the ability to change precision? "
	replace_ "#define CHANGE_PRECISION"
    elif [ "$input" = "e" ]; then
	sed "s/\/\/#define/#define/g" src/include/calc_features.hpp > calc_features.temp
	rm src/include/calc_features.hpp
	mv calc_features.temp src/include/calc_features.hpp
    fi
fi

	
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
