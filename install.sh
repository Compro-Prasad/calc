#!/bin/bash

Strip=yes
AutoLaunch=no
CompileOnly=no

while [ -n "$1" ]; do
	case $1 in
		no-strip) Strip=no;;
		auto-launch) AutoLaunch=yes;;
		compile-only) CompileOnly=yes;;
		*) echo "Invalid Option : $1"
		   echo "Usage: $0 [no-strip] [auto-launch] [compile-only]"
		   exit
	esac
	shift
done

function comment_
{
	if [ -n "$1" ]; then
		sed "/^[^\/]*$1/s/^/\/\//" src/include/calc_features.hpp > calc_features.temp
		rm -f src/include/calc_features.hpp
		mv calc_features.temp src/include/calc_features.hpp
	fi
}

function uncomment_
{
	if [ -n "$1" ]; then
		sed "/$1/s/^\/\/[\/]*//" src/include/calc_features.hpp > calc_features.temp
		rm -f src/include/calc_features.hpp
		mv calc_features.temp src/include/calc_features.hpp
	fi
}

function replace_
{
	read input
	if [ "$input" = "n" ]; then
		if [ -z "$2" ]; then
			comment_ "$1"
		else
			sed -e "s/$2/$1/g" src/include/calc_features.hpp > calc_features.temp
			rm -f src/include/calc_features.hpp
			mv calc_features.temp src/include/calc_features.hpp
		fi
	elif [ "$input" = "y" ]; then
		if [ -z "$2" ]; then
			uncomment_ "$1"
		else
			sed "s/$1/$2/g" src/include/calc_features.hpp > calc_features.temp
			rm -f src/include/calc_features.hpp
			mv calc_features.temp src/include/calc_features.hpp
		fi
	fi
}

echo -n 'Do you want a custom install[not recommended](y/n)? '
read input
if [ "$input" = "y" -o -z "$input" ]; then
	echo "Input method:"
	echo "1) SHELL_INPUT"
	echo "2) DIRECT_INPUT"
	echo "3) Both of the above"
	echo -n "Choose an option: "
	read input
	if [ "$input" = "1" ]; then
		comment_ "define DIRECT_INPUT"
		uncomment_ "define SHELL_INPUT"
	elif [ "$input" = "2" ];then
		comment_ "define SHELL_INPUT"
		uncomment_ "define DIRECT_INPUT"
	else
		uncomment_ "define SHELL_INPUT"
		uncomment_ "define DIRECT_INPUT"
	fi
	if [ -e calc_features.temp ]; then
		rm -f src/include/calc_features.hpp
		mv calc_features.temp src/include/calc_features.hpp
	fi
    echo -n "Stable features[e(nable all)/d(isable all)/c(hoose manually)]: "
	read input
	if [ "$input" = "c" ]; then
		echo -en "\tDo you want operator stack details(helpful for programmers)? "
		replace_ "define OPTR_DETAILS"

		echo -en "\tDo you want number stack details(helpful for programmers)? "
		replace_ "define NUM_DETAILS"

		echo -en "\tDo you want the suming feature(for everyone)? "
		replace_ "define SUM"

		echo -en "\tDo you want factorizing feature(for everyone)? "
		replace_ "define FACTORIZE"

		echo -en "\tDo you want calculation steps(not flexible)? "
		replace_ "define STEPS_CMD"

		echo -en "\tDo you want the ability to change angle type? "
		replace_ "define CHANGE_ANGLE"

		echo -en "\tDo you need direct input help commands? "
		replace_ "define HELP_CMD"

		echo -en "\tDo you ever want a very lengthy and memory consuming calculation? "
		replace_ "define SPEED_UP" "define ACCELERATE_UP"

		echo -en "\tDo you want to record calculation time? "
		replace_ "define CALC_PROCESS_TIME"

		echo -en "\tDo you want prompt feature? "
		replace_ "define PROMPT"

		echo -en "\tDo you need defining constants? "
		replace_ "define CONST_CMDS"

		echo -en "\tDo you want answers to be recorded? "
		replace_ "define ANS_CMD"

		echo -en "\tDo you want to access shell from within your calculator? "
		replace_ "define SHELL_CMD"

		echo -en "\tDo you want the ability to change precision? "
		replace_ "define CHANGE_PRECISION"
	elif [ "$input" = "d" ]; then
		comment_ "define CALC_STABLE"
	else
		uncomment_ "define CALC_STABLE"
		sed "/#ifdef CALC_STABLE/,/#endif \/\/ CALC_STABLE/s/^\/\///" src/include/calc_features.hpp > calc_features.temp
		rm -f src/include/calc_features.hpp
		mv calc_features.temp src/include/calc_features.hpp
	fi

	echo "Unstable features"
	echo "Under Development/not Cross Platform but usable on standard platforms"
	echo -n "[e(nable) all/d(isable all)/c(hoose manually)]: "
	read input
	if [ "$input" = "e" ]; then
		uncomment_ "define CALC_UNSTABLE"
		sed "/#ifdef CALC_STABLE/,/#endif \/\/ CALC_UNSTABLE/s/^\/\/[\/]*//" src/include/calc_features.hpp > calc_features.temp
		rm -f src/include/calc_features.hpp
		mv calc_features.temp src/include/calc_features.hpp
	elif [ "$input" = "d" ]; then
		comment_ "define CALC_UNSTABLE"
	else
		echo -en "Do you want colors? "
		replace_ "define CALC_COLORS"

		echo -en "Do you want screen manipulation? "
		replace_ "define SCREEN_MANIP"
	fi
fi

make cleanall

echo Compiling...
make
if [ $? -eq 0 ]; then
	echo Compilation Finished
	if [[ "$CompileOnly" = "no" && $(id | grep sudo > /dev/null;echo $?) -eq 0 || "$USER" = "root" ]]; then
		if [ "$Strip" == "yes" ]; then
			strip calc
		fi
		sudo make install
		if [ $? -eq 0 ]; then
			echo "Installation Finished"
			make cleanall
			echo "Cleaned up residual files"
			if [ "$AutoLaunch" = "no" ]; then
				echo -n "Do you want to launch the application? "
				read input
			else
				input=y
			fi
			case $input in
				"" | "y" | "Y" | "yes" | "Yes" | "YES" )
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
							echo "Restart shell to reload config file"
						fi
					fi;;
				"n" | "N" | "no" | "No" | "NO" )
					exit 0;;
			esac
		fi
	else
		echo "Not Installed"
		echo "Try changing value of INSTALL_DIR in the Makefile"
	fi
fi
