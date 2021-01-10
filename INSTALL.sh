#!/bin/sh

pipinstall(){

	echo "Welcome to GUIded installation!";
	# Checking the installation of pip
	! [ -x /usr/bin/pip ] || ! [ -x /usr/bin/pip3 ] && \
	# User OS selection
	echo "\nRequested SU privileges to install python-pip\nSelect the number of the operative system currently in use.
		\n(1) Arch based\n(2) Debian based\n(3) RHEL/Fedora\n(4) Gentoo based\n(5) macOS" && \
	read input
	case $input in
		1)echo "Using pacman..."; sudo pacman -Syu; sudo pacman -S python-pip; checkmembership;;
		2)echo "Using apt..."; sudo apt update; sudo apt install python3-pip; checkmembership;;
		3)echo "Using dnf..."; sudo dnf install python-pip; checkmembership;;
		4)echo "Using emerge..."; emerge --ask dev-python/pip; checkmembership;;
		5) curl	-o get-pip.py https://bootstrap.pypa.io/get-pip.py;
			chmod +x get-pip.py
			python3 get-pip.py
			rm get-pip.py;;
			# The membership to uucp is not required for Mac Users.
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

	pip3 install virtualenv
	mkdir venv && virtualenv venv
	source venv/bin/activate
	pip3 install -r mac_gnu_requirements.txt
	garden install graph

}

pipinstall
