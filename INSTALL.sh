#!/bin/sh

pipinstall(){

	echo "Welcome to GUIded installation!";
	# Checking the installation of pip
	! [ -x /usr/bin/pip ] || ! [ -x /usr/bin/pip3 ] && \
	# User OS selection
	echo -e "\nRequested SU privileges to install python-pip\nWhat system are you using?
		\n(1) Arch based\n(2) Debian based\n(3) RHEL/Fedora\n(4) Gentoo based\n(5) macOS (brew package manager is prompted)" && \
	read input
	case $input in
		1)echo "Using pacman..."; sudo pacman -Syu; sudo pacman -S python-pip; checkmembership;;
		2)echo "Using apt..."; sudo apt update; sudo apt install python3-pip; checkmembership;;
		3)echo "Using dnf..."; sudo dnf install python-pip; checkmembership;;
		4)echo "Using emerge..."; emerge --ask dev-python/pip checkmembership;;
		5)echo "Asking for brew installation";
			echo "Wanna install brew package manager? (Y/n)" && read choice;
			([ -z $choice  ] || [ $choice == 'y' ] || [ $choice == 'Y' ] && echo "installazione") && \
			sh -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
		;;
		*)echo "Skipping the python-pip installation!";;
	esac
	# If no virtual environment is present, manage a new install.
	! [ -d ./venv ] && newvirtualenv
	echo "All set! Running the application..." && ./RUN.sh

}

checkmembership(){

	[ -z $(< /etc/group | grep "uucp.*"$USER) ] && echo "Assigning membership to group uucp" && sudo usermod -a -G uucp $USER

}
newvirtualenv(){

	pip install virtualenv
	mkdir venv && virtualenv venv
	source venv/bin/activate
	pip install -r mac_gnu_requirements.txt
	garden install graph

}

pipinstall
