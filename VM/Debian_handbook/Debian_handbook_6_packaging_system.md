As a Debian system administrator, you will routinely handle .deb packages, since they contain consistent functional units(applications, document, etc), whose installation and maintenance they facilitate. It is therefore a good idea to know what they are and how to use them.

This chapter describes the structure and contents of "binary" and "source" package. The former are .deb fiels, directly usable by **dpkg**, while the latter contain the program source code, as well as intructions for building binary package.


## Structure of a Binary Package ##

- The Debian package format is designed so that its content may be extracted on any Unix system that has classic commands ar, tar, and gzip. This seemingly trivial property is important for portability and disaster recovery.

- **when you mistakenly deleted the dpkg program. if you know format of package, you can download the **.deb** file of the dpkg package and install it manually.**

- dpkg,apt and ar

    dpkg is the program that handles .deb files, notably extracting, analyzing, and unpacking them.
    
    
    APT is a group of programs that allows the execution of higher-level modification to the system: installing or removing a package(while keeping depencies statified), updating the system, listing the available packages. etc.
    
    As for the ar program, it allows handlings files of the same name, ar t archive
displays the list of files contained in such an archive, ar x archive extracts
the files from the archive into the current working directory, ar d archive
file deletes a file from the archive, etc. Its man page (ar(1)) documents its
many other operations. ar is a very rudimentary tool that a Unix administra-
tor would only use on rare occasions, but admins routinely use tar , a more
evolved archive and file management program. This is why it is easy to restore
dpkg in the event of an erroneous deletion. You would only have to download
the Debian package and extract the content from the archive data.tar.gz in
the system's root ( / ):

        # ar x dpkg_1.15.8.5_i386.deb
        # tar -C / -p -xzf data.tar.gz
        
      
   - It can be confusing for beginners to find references to “ar(1)” in the literature.
This is generally a convenient means of referring to the man page entitled ar
in section 1.  