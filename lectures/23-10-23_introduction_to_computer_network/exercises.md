# Exercises for Introduction to Computer Network

The following exercises relate to Chapter 1 in Kurose and Ross on the topic "Introduction to Computer Networks". From page 97.

* R13 
* R14
* P4
* P13
* P31 (optional)
* P33 (optional)

# Setup programming for the rest of the networking part
Verify that you can run Python3 and all the requird modules. If you can type the following into your command line in the same directory as this file and get a positive feedback message, you are good to go.

	python3 test.py

If you need to install python then follow this guide: https://realpython.com/installing-python/

Mostly we are just going to use standard libraries for Python3, but you may need to install PyYAML if you get a "No module named 'yaml'" error. You can do so with pip, the main python package manager which should come bundled with your python3 install. On some linux distributions it does not, in which case you should run:

	sudo apt install python3-pip

Once you have pip you can run the following:

	python3 -m pip install pyyaml

# Converting network communications
Complete the tasks in the src/conversion.c file. Here you will need to convert between different endianness's. Have a look at ( https://linux.die.net/man/3/htonl ) for some useful functions. Also note the functions added in the endian.h file.
