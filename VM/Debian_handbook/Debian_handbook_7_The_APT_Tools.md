#APT:advanced package tool #

what make debian so popular with administrator is how easily software can be installed and how easily the whole system can be updated. This unique advantage is largely due to the **APT programe**, the features of which Falcot Corp administrator studied with enthusiasm.

It doesn't simply evaluate them individually, but it considers them as a whole and produces the best possible combination of packages depending on what is available and compatible(according to dependencies)


## package source and source package ##

The word source can be ambiguous. A **source package** - a package containing the source code of a program- should not be confused with a **package source** - a repository(website, FTP server, CD-ROM, local directory, etc.) which contains packages.

- APT need be given a "list of package sources": the file **/etc/apt/sources.list** will list the different repositories(or 'sources') that publish Debian package.

    APT will then import the list of packages published by each of these sources. This operate is achieved by downloading **Packages.gz or Packages.bz2** files(in case of **a source of binary packages**) and **Sources.gz or Sources.bz2** files(in case of **a source of source packages**) and by analyzing their contents.
  
    when an old copy of these files is already present, APT can update it by only downloading the differences(see siderbar "Incremental upgrade")(page 109)
    
- A **.gz extension** refers to a files compressed with the gzip utility. gzip is the fast and effecient traditional Unix utility to compress files. Newer tools achieve better rates of compression but require more calculation time to compress a file. Among them, and by order of appearance, **there are bzip2(generating files with a .bz2 extension), lzma(generating .lzma files) and xz(generating .xz files).**


- a source made of 3 parts seperated by spaces.

    - The first field indicates the source type:
    
        * "deb" for binary packages.
        * "deb-src" for source packages.
        
    - The second field gives the base URL of the source(combined with the filenames present in Packages.gz, it must give a full and valid URL)
    
        * The URL can start with file:// to indicate a local source installed in the system's file hierarchy.
        * with http:// to indicate a source accessible from a web server
        * or with ftp:// for a source available on a FTP srver
        * The URL can also start with cdrom:// for CD-ROM based installation
      
     - The syntax of the last field depends on whether the source corresponds to a Debian mirror or not.
        * In the case of a Debian mirror, name the chosen distribution(stable, testing, unstable or their current code names), then the sections to enable(chosen between main,contrib,and non-free)
        * In all other cases, simply indicate the subdirectory of the desired sources(this is often a simple './' which refers to the absence of a subdirectory-the packages are then directly at the specified URL).
       
- The main, contrib and non-free archives

    Debian uses three sections to differentiate packages according to the licenses chosen by the authors of each program.
    
    - **Main(the main archive)** gathers all packages which fully comply with the Debian Free Software Guidelines.
    - The **non-free archive** is different because it contains software which does not(entirely) conform to these principles but which can nevertheless be distributed freely.
    - **Contrib(contributions)** is a stock of open source software which cannot function without some non-free elements. 

- Generally, the contents of a standard sources.list file can be the following:

        # Security updates
        deb http://security.debian.org/ stable/updates main contrib non-free
        deb-src http://security.debian.org/ stable/updates main contrib non-free
        # Debian mirror
        deb http://ftp.debian.org/debian stable main contrib non-free
        deb-src http://ftp.debian.org/debian stable main contrib non-fre
    
- When the desired version of a package is available on serveral mirrors, the first one listed in the sources.list file will be used. For this reason, non-official sources are usually added at the end of the file.

- **/etc/apt/sources.list.d/*.list files** 

    If many package sources are referenced, it can be useful to split them in multiple files. Each part is then stored in /etc/apt/sources.list.d/filename.list

- apt-spy

    This software tests the downloaded speed from serveral Debian mirrors and generate a sources.list file which points to the fastest mirror.
    
- supplement for cd

    The sources.list file contains several other entry types: some describe the Debian CD-ROMs
you have. Contrary to other entries, a CD-ROM is not always available since it has to be inserted
into the drive and since only one disc can be read at a time — consequently, these sources are
managed in a slightly different way. These entries need to be added with the apt-cdrom pro-
gram, usually executed with the add parameter. The latter will then request the disc to be
inserted in the drive and will browse its contents looking for Packages files. It will use these
files to update its database of available packages (this is usually done by the aptitude update
command). From then on, APT can require the disc to be inserted if it needs one of its packages.

- Other Available Official Repositories

    - Stable Updates
    
        Once published, the **Stable** distribution is only updated abount once every 2 months in order to integate the security updates published on **security.debian.org.**
        
        All those updates are prepared in a repository known as **proposed-updates**. Anyone can use this repository to test those updates before their official publication. The extract below uses squeeze-proposed-updates alias which is both more explicit and more consistent since lenny-proposed-updates also exists(for the Oldstable updates):
        
            deb http://ftp.debian.org/debian squeeze-proposed-updates main contrib non-free
            
        Once ready, the most important updates - those which cannnot wait for the next minor Debian release -  are published in the **stable-updates** repository(which most systems are expected to use):
        
            deb http://ftp.debian.org/debian stable-updates main contrib non-free
            
            
    - The Backports from backports.debian.org
     
        Unsurprisingly, the backports.debian.org server hosts “package backports”. The term refers
to a package of a recent software which has been recompiled for an older distribution, gener-
ally for Stable. When the distribution becomes a little dated, numerous software projects have
released new versions that are not integrated into the current Stable (which is only modified
to address the most critical problems, such as security problems). Since the Testing and Unsta-
ble distributions can be more risky, some volunteers sometimes offer recompilations of recent
software applications for Stable, which has the advantage to limit potential instability to a small
number of chosen packages.

            http://backports.debian.org/
        
        The sources.list entry for backports targeting the Squeeze distribution is the following:
          
            deb http://backports.debian.org/debian-backports squeeze-backports main contrib non-free        
            
     - The Experimental Repository
     
        The archive of Experimental packages is present on all Debian mirrors, and contains packages which are not in the Unstable version yet because of their substandard quality- they are often software development versions or pre-versions (alpha, beta, release candidate...).
        
        A package can also be sent there after undergoing subsequent changes which can generate problems. The maintainer then tries to uncover them thanks to advanced users who can manage important
issues. After this first stage, the package is moved into Unstable, where it reaches a much larger
audience and where it will be tested in much more detail.

        **Experimental** is generally used by users who do not mind breaking their system and then re-
pairing it. This distribution gives the possibility to import a package which a user wants to try
or use as the need arises. That is exactly how Debian approaches it, since adding it in APT's
sources.list file does not lead to the systematic use of its packages. The line to be added is:

            deb http://ftp.debian.org/debian experimental main contrib non-free
            
- Non-Official Resources : apt-get.org and mentors.debian.net

    There are numerous non-official sources of Debian packages set up by advanced users who have
recompiled some softwares, by programmers who make their creation available to all, and even
by Debian developers who offer pre-versions of their package online.

            http://www.apt-get.org/
            
    The **mentors.debian.net** site is also interesting, since it gathers packages created by candidates to the status of official Debian developer or by volunteers who wish to create Debian packages without going through that process of integration. These packages are made available without
any guarantee regarding their quality; make sure that you check their origin and integrity and
then test them before you consider using them in production.


## aptitude and apt-get Commands ##

APT is based on a library which contains the core application.

**apt-get** : is the first interface - command-line based - which was developed within the project.******

**synaptic, aptitude** : a tex mode interface and a graphic one, even if not complete yet. 


The most recommended interface, aptitude, is the one used during the installation of Debian. since its command-line syntax is similar to apt-get's. 

- **Installation**

    **aptitude update** : get the list of available packages, like apt-get update, it download a certain number of a Packages.(gz|bz2) files (or even Sources.(gz|bz2))
    
- **Installation and Removing**

    aptitude install package
    
    aptitude remove package
    
    aptitude purge package or apt-get purge package : complete uninstallation - the configuration files also deleted.


- **Installing the same selection of packages serveral times**

    It can be useful to systematically install the same list of packages on several computers, This can be done quite easily.
   
       - retrive the list of packages installed on the computer which will serve as the "model" to copy.
       
            $ dpkg --get-selections > pkg-list
            
       - The pkg-list file then contains the list of installed packages. Next, transfer the pkg-list file on the computer you want to update and use the following commands.
       
            $ dpkg --set-selections <pkg-list
            
       
            $ apt-get dselect-upgrade
            
            
- ** Removing and Installation at the same time by adding a suffix **

    aptitude install package1 package2-
    
    aptitude install package1+ package2
    
- ** reinstall damaged package **

    apt-get --reinstall install postfix
    
    aptitude reinstall postfix
    
- **give the version of the package to install**

    aptitude install package=version
    
- **indicating its distribution of origin(Stable, Testing or Unstable)**

    aptitude install package/distribution
    
- otherwise the **snapshot.debian.org** archive can come to the rescue

- **The cache of .deb files**

    APT keeps a copy of each downloaded .deb file in the directory /var/cache/apt/archive/. In case of frequently updates, this directory can quickly take a lot of disk space with several versions of each package. Two commands can be used to clean:
   
    **aptitude clean** entirely empties the directory
    
    **aptitude autoclean** only removes packages which cannot be downloaded, and the parameter  **APT::Clean-Installed**  can prevent the removal of .deb files that are currently installed.
    
    
## System Upgrade ##

Regular upgrades are recommended, because they include the latest security updates. 

**aptitude safe-upgrade or apt-get upgrade(of course after aptitude update)**

apt-get is slightly more demanding than aptitude because it will refuse to install packages which where not installed beforehand.

- Incremental upgrade

    - **apt-get update** command download packages that contaning list of package, 

    - apt can download the changes since the previous update
    
    - **aptitude update** is often divided by 10. and download diff file.
    
    - set **Acquire::Pdiffs to false** close aptitude's incremental upgrade.
    
    - aptitude generally select the most recent version number(except for experimental packages, which are ignore by default whatever their version number). If you specified Testing or Unstable, which might not be what you intened.
   
- **Tell aptitude to use a specific distribution when searching for upgrade packages:**

    **option -t or --target-release : aptitude -t stable safe-upgrade**
    
    To avoid specifying this option every time you use aptitude. you can add APT::Default-Relase "stable"; in the file /etc/apt/apt.conf.d/local.
    
- change from one major Debian version to the next:

    aptitude full-upgrade (the option used to be named dist-upgrade, for "distribution upgrade") With this instruction, aptitude will complete the upgrade even if it has to remove some obsolete packages or install new dependencies. This is also the command used by users who work daily with the Debian Unstable release and follow its evolution day by day. It is so simple that it hardly explanation: APT's reputation is based on this great functionality. 
    
    aptitude dist-upgrade is still available as a synonm for aptitude full-upgrade; apt-get only recognizes the former.
    
## Configuration Options ##

Besides the configuraton elements already mentioned, it is possible to configuration certain aspects of **APT by adding directives in a file of the /etc/apt/apt.conf.d/ directory.**

**Remember for instance that it is possible for APT to tell dpkg to ignore file conflict errors by specifying DPkg::Options{"--force-overwrite";};**

**Configure a http proxy: Acquire::http::proxy "http://yourproxy:3128"**

**For an FTP proxy: Acquire::ftp::proxy "ftp://yourproxy"**

To discover more configuration options, read the apt.conf(5) manual page with the command man apt.conf

Directories with a .d suffix are used more and more often. Each directory represents a configuration file which is split over multiple files.

The Exim 4 mail server is an example of the generated file method: it can be configured through several files ( /etc/exim4/conf.d/* ) which are concatenated into /var/lib/exim4/config.autogenerated by the update-exim4.conf command.

## Managing Packaging Priorities ##

** One of the most important aspects in the configuration of APT is the management of the priorities associated with each package source. **

For instance, you might want to extend one distribution with one or two newer packages from Testing, Unstable or Experimental. It is possible to assign a priority to each available packages(**the same package can have several priorities depanding on its version or the distribution providing it**), These priorities will influence APT's behavior: for each package, it will always select the version with the highest priority(except if this version is older than the installed one and if its priorities is less than 1000).

**APT defines several default priorities. Each installed package version has a priority of 100. A non-installed version has a priority of 500 by default. but it can jump to 990 if it is part of the target release(defined with the -t command-line option or the APT::Target-Release configuration directive).**

you can modify the priorities by adding entries in the file **/etc/apt/preference** with the names of the affected packages. 

**APT will never install an older version of a package(that is, a package whose version number is lower than the one of the currently installed package), except if its priority is higher than 1000.** 

if two packages have the same priority, APT installs the newest one(whose version number is the highest).

If two packages of same version have the same priorities but diff their content, APT installs the version that is not installed(this rule has been created to cover the case of a pacakge update without the increment of the revision number, which is usually required).


**In more concrete terms, a package whose priority is less than 0 will never be installed. a package with a priority between 0 and 100[0,100) will only be installed if no other version of the package is already installed. with the priority between 100 and 500[100, 500), the package will only be installed if there is no other newer version installed or available in another distribution. A package of priority between 500 and 990[500, 990) will only be installed if there is no newer version installed or available in the target distribution. With a priority between 990 and 1000[990, 1000), the package will be installed except if the installed version is newer. A priority greater than 1000 will always lead to the installation of the package even if it forces APT to downgrade to an older version.**

When APT checks /etc/apt/preferences, it first takes into account the most specific entires(often those specifying the concerned package). then the more generic ones(including for example all the packages of a distribution). If several generic entries exist, the first match is used. The available selection criteria include the packages's name and the source providing it. **Every package source is identified by the information contained in a Release file that APT downloads together with the Packages.gz files.**  It specifies the origin(usually "Debian" for the packages of official mirrors, but it can also be a person's or an organization's name for third-parties repositories.) It also gives the name of the distribution (usually Stable, Testing, Unstable or Experimental for the standard distributions provided by Debian) together with its version (for example 5.0 for Debian Lenny). **Let's have a look at its syntax through some realistic case studies of this mechanism.**

**Note**

**If you listed Experimental in your sources.list file, the corresponding pack-
ages will almost never be installed because their default APT priority is 1.
This is of course a specific case, designed to keep users from installing Ex-
perimental packages by mistake. The packages can only be installed by typ-
ing aptitude install package/experimental — users typing this command
can only be aware of the risks that they take. It is still possible (though not
recommended) to treat packages of Experimental like those of other distribu-
tions by giving them a priority of 500. This is done with a specific entry in
/etc/apt/preferences :**

        Package: *
        Pin: release a=experimental
        Pin-Priority: 500
        
**
If you only want to use packages from the stable version of Debian. Those provided in other versions should not be installed except if explicitly requested. You could write the following entires in the /etc/apt/preferences file:
**

        Package: *
        Pin: release a=stable
        Pin-Priority: 900
        Package: *
        Pin: release o=Debian
        Pin-Priority: -10

a=stable defines the name of the selected distribution. o=Debian limits the scope to packages
whose origin is “Debian”


**Let's now assume that you have a server with several local programs depending on the version
5.10 of Perl and that you want to ensure that upgrades will not install another version of it. You
could use this entry:**

        Package: perl
        Pin: version 5.10*
        Pin-Priority: 1001
        
The reference documentation for this configuration file is available in the manual page apt_-
preferences(5), which you can display with man apt_preferences.


**Comments in /etc/apt/preferences**

    There is no official syntax to put comments in the /etc/apt/preferences file,
    but some textual descriptions can be provided by puring one or more “Expla
    nation” fields at the start of each entry:
    
        Explanation: The package xserver-xorg-video-intel provided
        Explanation: in experimental can be used safely
        Package: xserver-xorg-video-intel
        Pin: release a=experimental
        Pin-Priority: 500
        
## Working with Serveral Distribution ##

**aptitude** being such a marvelous tool,
it is tempting to pick packages coming from other dis-
tributions. For example, after having installed a Stable system, you might want to try out a
software package available in Testing or Unstable without diverging too much from the system's
initial state.

Even if you will occasionally encounter problems while mixing packages from different distribu-
tions, aptitude manages such coexistence very well and limits risks very effectively. T**he best
way to proceed is to list all distributions used in /etc/apt/sources.list (some people always
put the three distributions, but remember that Unstable is reserved for experienced users) and to
define your reference distribution with the APT::Default-Release parameter (see Section 6.2.3,
“System Upgrade” (page 109)).**


Let's suppose that Stable is your reference distribution but that Testing and Unstable are also listed
in your sources.list file. In this case, you can use **aptitude install package/testing** to
install a package from Testing. If the installation fails due to some unsatisfiable dependencies,
let it solve those dependencies within Testing by adding the -t testing parameter. The same
obviously applies to Unstable.

In this situation, **upgrades ( safe-upgrade and dist-upgrade ) are done within Stable except for
packages already upgraded to an other distribution**: those will follow updates available in the
other distributions. We'll explain this behavior with the help of the default priorities set by APT
below. Do not hesitate to use **apt-cache policy** (see sidebar) to verify the given priorities.

Everything centers around the fact that APT only considers packages of higher or equal ver-
sion than the installed one (assuming that /etc/apt/preferencs has not been used to force
priorities higher than 1000 for some packages).

**apt-cache policy** :To gain a beer understanding of the mechanism of priority, do not hesitate
to execute apt-cache policy to display the default priority associated with
each package source. **You can also use apt-cache policy package to display
the priorities of all available versions of a given package.**

###Example:###

Let's assume that you have installed version 1 of a first package from Stable and that version 2
and 3 are available respectively in Testing and Unstable. The installed version has a priority of 100
but the version available in Stable (the very same) has a priority of 990 (because it is part of the
target release). Packages in Testing and Unstable have a priority of 500 (the default priority of a
non-installed version). The winner is thus version 1 with a priority of 990. The package “stays
in Stable”.

Let's take the example of another package whose version 2 has been installed from Testing. Ver-
sion 1 is available in Stable and version 3 in Unstable. Version 1 (of priority 990 — thus lower
than 1000) is discarded because it is lower than the installed version. This only leaves version 2
and 3, both of priority 500. Faced with this alternative, APT selects the newest version, the one
from Unstable.If you don't want a package installed from Testing to migrate to Unstable, you have
to assign a priority lower than 500 (490 for example) to packages coming from Unstable. You can
modify /etc/apt/preferences to this effect:

    Package: *
    Pin: release a=unstable
    Pin-Priority: 490
        
        
## apt-cache ##

The apt-cache ccommand can display much of the information **stored in APT's internal database. This information is a sort of cache since it gathered from the different sources in the sources.list.** This happens during the **aptitude update** operation. 


###Cache###

A cache is a temporary storage system used to speed up frequent data access when the usual access method is expensive(performance-wise). **This concept can be applied in numerous situations and at different scales, from the core of microprocessors up to high-end storage systems.**

In the case of APT, the reference Packages files are those located on Debian mirrors. That said, it would be very ineffective to go though the network for every search that might want to do in the database of available packages. That is why APT stores a copy of those files (in **/var/lib/apt/lists/**) and searches are done within those local files. similary, **/var/cache/apt/archives** contains a cache of already downloaded packaegs to avoid downloading them again if you need to reinstall them after a removal.

The apt-get command can do **keyword-based** package searches with **apt-cache search keyword**. It can also display the headers of the package's available versions with **apt-cache show packages**. This command provides the package's description, its dependencies, the name of its maintainer, etc. Note that **aptitude search and aptitude show** work in the same way.

Some features are more rarely used. For instance, **apt-cache policy** displays the priorities of package sources as well as those of individual packages. Another example is **apt-cache pkgnames**, displays the list of all the packages which appear at least once in the cache.

### Frontends : aptitude, synaptic ###

**APT is a C++ program whose code mainly resides in the libapt-pkg shared library**,  Using a shared library facilitates the creation of user interface(front-ends), sinece the code contained in the library can easily be reused. Historically, **apt-get was only designed as a test front-end for libapt-pkg but its success tends to obscure this fact.**


**aptitude**

**aptitude** is an interactive program that can be used in semi-graphical mode on the console. You can browser the list of installed and available packages.  look up all the available information, and select packages to install or remove. **The programe is designed specifically to be used by administrators, so that its default behaviors are much more intelligent than apt-get's, and its interface much easier to understand.**

aptitude displays a list combinding categories and packages on the screen. Categories are organized through a tree structure. 

- whose branches can respectively be unfolded or closed with the Enter, [ and ] keys.
- `?` for help
- The Search for a package, you can type / followed by a search pattern. This pattern matches the name of the packge, but can also be applied to the description(if preceded by ~d), to the section(
with ~s) or to other characteristics detailed in the documentation. The same patterns can filter the list of displayed packages: type the l key(as in limit) and enter the pattern.

(note than these keys can also be used for
categories, in which case the corresponding actions will be applied to all the packages of the  category)

### Tracking Automatically Installed Packages ###

**One of the essential functionalities of aptitude (which has also been integrated to apt-get since Lenny) is the tracking of packages installed only through dependencies.** These packages are called "automatic" and are tagged with "A" in the list of packages - they often include libraries for instance.

When a package is removed, the corresponding automatic packages are also selected for removal unless another "manually installed" package depends on them.

It is possible to mark a package as a automatic(with Shift+m) or to remove the mark(m key).

When maintaining a system with aptitude, it is a good habit to mark as automatic any package that you don't need directly so that they are automatically removed when they aren't necessary anymore. You can either navigate the list of installed and play with shift+m, or apply the flag to entire sections (for example the libs section). The habit can help you to keep your the habit can help you to keep your system tidy and offers a simple way to visualize  the packages in use on a machine, without all the libraries and dependencies that you don't realy care about. **The related pattern that you can use l(to active the filter mode) is ~i!~M. It specifies that you only want to see installed packages(~i) not marked as automatic(!~M).**

People might want to know **why an automatically installed package** is present on the system. To get this information from the command-line, you can use **aptitude why package**.

    $ aptitude why python-debian
    i   aptitude                    Recommends apt-xapian-index
    i A apt-xapian-index Depends    python-debian (>= 0.1.15)


#### --Recent evolutions of apt-get and aptitude-- ####
Some of the advantages that **aptitude** historically had over apt-get have recently disappeared. For instance, since the release of Lenny, apt-get memorizes the packages that have been installed only to satisfy dependencies,  just like aptitude has always done. It can also follow recommendations expressed by one package on another. 

Among the recent evoluations of aptitude, a new version with a graphical interface is currently being
developed. Even if it's available in Squeeze(in the separate aptitude-gtk package), it's not complete yet and is subject to stability issues.

#### --Using aptitude on the command-line interface-- ####
Most of aptitude's features are accessible via the interactive interface as well as via command-lines. These command-lines will seem familiar to regular users of **apt-get** and **apt-cache**.

**The advantage features of aptitude are also available on the command-line.** You can use the same package search patterns as in the interactive version:

for rexample: if you want to run the previously suggested cleanup of "auto-matic" packages, and if you know that none of the locally installed programs require particular libraries or Perl modules, you can mark the corresponding packages as automatic with a single command:

        # aptitude markauto '~slibs|~sperl'
        
**Here, you can clearly see the power of the search pattern system of aptitude, which enables the instance selection of all the packages in the libs and perl sections.** 

**Beware, if some packages are marked as automatic and if no other package depends on them, they will be removed immediatly (after a confirmation request)**

#### -- Managing Recommandations, Suggestions and Tasks --####
Another intersting feature of aptitude is the fact that it repects recommandations between pacakges while still giving users the choice not to install them on a case basis. For example, the gnome-desktop-environment package recommends gnome-accessibility(among others). When you select the former for installation, the latter will also be selected(and marked as automatic if not already installed on the system). Typing **g** will make it obvious: gnome-accessibility appears on the summary screen of pending actions in the list of packages installed automatically to satisfy dependencies. However, you can decide not to install it before confirming the operation.

Note that this **recommendation tracking feature does not apply to upgrades.** For instance, if
a new version of gnome-desktop-environment recommends a package that it did not recommend
formerly, the package won't be marked for installation. However, it will be listed on the upgrade
screen so that the administrator can still select it for installation.

Suggestions between packages are also taken into account, but in a manner adapted to their
specific status. For example, since gnome-desktop-environment suggests gnome-audio, the latter
will be displayed on the summary screen of pending actions (in the section of packages sug-
gested by other packages). This way, it is visible and the administrator can decide whether to
take the suggestion into account or not. **Since it is only a suggestion and not a dependency
or a recommendation, the package will not be selected automatically — its selection requires a
manual intervention from the user (thus, the package will not be marked as automatic).**

In the same spirit, remember that aptitude makes intelligent use of the concept of task. Since
tasks are displayed as categories in the screens of package lists, you can either select a full task
for installation or removal, or browse the list of packages included in the task to select a smaller
subset.

#### --Better Solver Algorithms-- ####

**To conclude this secions, let's note that aptitude has more eleborate algorithms compared to apt-get when it comes to resolving difficult situations**. When a set of actions is requested and when these combined actions would lead to a incoherent system. **aptitude evaluates several possible scenarios and presents them in order of decreasing relevance. these algorithms are not failproof.** Fortunately there is always the possibility to manually select the actions to perform. When the currently selected actions lead to contradictions, the upper part of the screen indicates a numebr of "broken" packages(and you can directly navigate to those packages by pressing **b**). It is then possible to manully build solution for the problems found. **In particular, you can get access to the different available versions by simply selecting the pack-
age with Enter. If the selection of one of these versions solves the problem, you should not hesi-
tate to use the function. When the number of broken packages gets down to zero, you can safely
go the summary screen of pending actions for a last check before you apply them.**

#### --aptitude's log-- ####

**Like dpkg, aptitude keeps a trace of excuted actions in its logfile(/var/log/aptitude)**. However, since both commands work at a very different level. **you
cannot find the same information in their respective logfiles. While dpkg logs
all the operations executed on individual packages step by step, aptitude gives
a broader view of high-level operations like a system-wide upgrade.**

Beware, this logfile only contains a summary of operations performed by apt
itude . If other front-ends (or even dpkg itself) are occasionally used, then aptitude 's
log will only contain a partial view of the operations, so you can't
rely on it to build a trustworthy history of the system.