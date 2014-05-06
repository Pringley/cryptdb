# Proof of Concept Database for an Untrusted Server

This project demonstrates a database in which all the server sees is ciphertexts. The clients
have keys to their data, and can provide the server with sufficient data to perform various
queries on the data and returning results without actually knowing the plaintext of the data
searched.

This database is based on the work presented in this paper:
http://www.cs.berkeley.edu/~dawnsong/papers/se.pdf

Original Authors (up to commit 151cb350225932ff35210ba3e8eca893faff4eee):
 * Samuel Rhody
 * Nathan Hourt
 * Patrick Biernat

All code since commit 151cb350225932ff35210ba3e8eca893faff4eee is the work of:
 * Nathan Hourt
 * Jennifer Karkoska
 * Mike Moore
	
Default Parameters:
	Set m = 8
	Set n = 32

Implementation notes:
	To determine F_k_i(S_i), use HMAC with SHA-1

	Use a PRNG to generate all S_i

	Use single instance of k'' for pre-encryption. Key k'' has been randomly chosen to be 4.

	k_i = f_k'(L_i)

	Using qca-qt5 from AUR and Qt 5

## Build using Vagrant

Follow these steps to build the code using
[Vagrant](http://www.vagrantup.com/), a portable development environment
creator.

1.  Install [Vagrant](http://www.vagrantup.com/downloads.html) and
    [VirtualBox](https://www.virtualbox.org/wiki/Downloads) on your computer.

2.  Clone this repository.

        git clone https://github.com/Pringley/cryptdb.git

    If you don't have Git installed, you can instead [download a
    zip](https://github.com/Pringley/cryptdb/archive/master.zip) and unpack it
    into a folder named `cryptdb/`.

3.  Initialize the virtual machine using Vagrant.

        cd cryptdb
        vagrant up

    This will set up the virtual machine and automatically install
    dependencies.

4.  SSH into the virtual machine.

        vagrant ssh

    This will connect your terminal to the Ubuntu 14.04 VM. This folder is
    shared in the virtual machine as `vagrant/.

5.  Build the project.

        cd /vagrant
        qmake Project1.pro
        make

6.  Run the project!

        ./Project1

    (The command might take a while to get started as it loads the database.)
