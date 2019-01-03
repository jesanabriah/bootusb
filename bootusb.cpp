/*
*
* Create a bootable Debian Linux USB with the specified disk image
*
* This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Copyright (2017) Jorge Eliécer Sanabria Hernández
*
*   jorelsahe@gmail.com
*/

#include <iostream>
#include <cstring>

void make_bootusb(char **argv);

//$ bootusb /path/to/origen.iso /dev/sdX
int main(int argc, char **argv){


	if(argc != 3){
		std::cout << "Incorrect number of arguments" << std::endl;
		std::cout << "example:\t'root@debian:~ bootusb /path/to/origen.iso /dev/sdX'" << std::endl;
	}
	else if(strncmp(argv[2], "/dev/sda", 8) == 0){
		std::cout << "This procedure, for security reasons, can not be done in /dev/sda" << std::endl;
		std::cout << "Try better in a removable medium /dev/sdX" << std::endl;
	}
	else{
		make_bootusb(argv);
		std::cout << "Now you can remove the USB :)" << std::endl;
	}

	return 0;
}

void make_bootusb(char **argv){

	char buffer[256];

 	//apt-get install mbr syslinux mtools
 	strcpy(buffer, "apt-get install mbr syslinux mtools");
 	std::cout << buffer << std::endl;
	system (buffer);

	//umount /dev/sdX1
	strcpy(buffer, "umount ");
	strcat(buffer, argv[2]);
	strcat(buffer, "1");
	std::cout << buffer << std::endl;
	system (buffer);

	//cfdisk
	strcpy(buffer, "cfdisk ");
	strcat(buffer, argv[2]);
	std::cout << buffer << std::endl;
	system (buffer);

	 //install-mbr /dev/sdX
	strcpy(buffer, "install-mbr ");
	strcat(buffer, argv[2]);
	std::cout << buffer << std::endl;
	system (buffer);

	//mkdosfs /dev/sdX1
	strcpy(buffer, "mkdosfs ");
	strcat(buffer, argv[2]);
	strcat(buffer, "1");
	std::cout << buffer << std::endl;
	system (buffer);

	//syslinux /dev/sdX1
	strcpy(buffer, "syslinux ");
	strcat(buffer, argv[2]);
	strcat(buffer, "1");
	std::cout << buffer << std::endl;
	system (buffer);

	//cp debian.iso /dev/sdX
	strcpy(buffer, "cp ");
	strcat(buffer, argv[1]);
	strcat(buffer, " ");
	strcat(buffer, argv[2]);
	std::cout << buffer << std::endl;
	system (buffer);

	//sync
	strcpy(buffer, "sync");
	std::cout << buffer << std::endl;
	system (buffer);
}

