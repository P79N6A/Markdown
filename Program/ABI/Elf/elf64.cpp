#define FILE_PATH "/home/damoncheng/Git/Markdown/Program/ABI/test/test"

#include <iostream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



typedef long  Elf64_Addr;     //8 bytes
typedef long  Elf64_Off;      //8 bytes
typedef short Elf64_Half;     //2 bytes
typedef int   Elf64_Word;     //4 bytes
typedef int   Elf64_Sword;    //4 bytes
typedef long  Elf64_Xword;    //8 bytes
typedef long  Elf64_Sxword;   //8 bytes

typedef struct {

    unsigned char e_ident[16];    //ELF identification
    Elf64_Half    e_type;         //Object file type
    Elf64_Half    e_machine;;     //Machine type
    Elf64_Word    e_version;      //Object file version
    Elf64_Addr    e_entry;        //Entry point address
    Elf64_Off     e_phoff;        //Program header offset
    Elf64_Off     e_shoff;        //Section header offset
    Elf64_Word    e_flags;        //Processor-specific flags
    Elf64_Half    e_ehsize;       //ELF header size
    Elf64_Half    e_phentsize;    //Size of programe header entry
    Elf64_Half    e_phnum;        //Number of program header entries
    Elf64_Half    e_shentsize;    //Size of section header entry
    Elf64_Half    e_shnum;        //Number of section header entries
    Elf64_Half    e_shstrndx;     //Section name string table index

} Elf64_Ehdr;

void hex_cout(const char * hint, int value)
{
    cout << hint << "0x" << hex << value << endl;
}

int main()
{

    int fd;
    ssize_t r_size;
    const unsigned int ELF_HEADER_SIZE = sizeof(Elf64_Ehdr);
    Elf64_Ehdr * elf_header = NULL;

    if((fd = open(FILE_PATH, O_RDONLY)) == -1)
    {
        cout << "open " << FILE_PATH << " failed!" << endl;
        perror(NULL);
        exit(1);
    }

    elf_header = new Elf64_Ehdr;
    r_size = read(fd, elf_header, ELF_HEADER_SIZE);
    if((int)r_size == -1)
    {
        perror(NULL);
        exit(1);
    }
    if((unsigned int)r_size != ELF_HEADER_SIZE)
    {
        cout << "should read ELF_HEADER: " << ELF_HEADER_SIZE << endl;
        cout << "accully read ELF_HEADER: " << (long)r_size << endl;
        exit(1);
    }

    cout << endl << endl;

    cout << "#----------START ELF HEADER--------#" << endl;
    cout << "ELF header size: " << hex << elf_header->e_ehsize << dec << endl;
    cout << "File identifycation: " << hex << (int)elf_header->e_ident[0] << dec << elf_header->e_ident[1] 
         << elf_header->e_ident[2]  <<  elf_header->e_ident[3] << endl;

    if((unsigned int)elf_header->e_ident[4] == 1)
       cout << "File Class: " << "32-bit objects" << endl;
    else if((unsigned int)elf_header->e_ident[4] == 2)
       cout << "File Class: " << "64-bit objects" << endl;
    else
       cout << "File Class: " << "unknown objects" << endl;


    if((unsigned int)elf_header->e_ident[5] == 1)
       cout << "Data Encoding: " << "little endian" << endl;
    else if((unsigned int)elf_header->e_ident[4] == 2)
       cout << "Data Encoding: " << "big endian" << endl;
    else
       cout << "Data Encoding: " << "unknown endian" << endl;


    if((unsigned int)elf_header->e_ident[7] == 0)
       cout << "OS/ABI identification: " << "System V ABI" << endl;
    else if((unsigned int)elf_header->e_ident[7] == 1)
       cout << "OS/ABI identification: " << "HP-UX operating system" << endl;
    else if((unsigned int)elf_header->e_ident[7] == 255)
       cout << "OS/ABI identification: " << "Standalone (embedded)" << endl;
    else
       cout << "OS/ABI identification: " << "unknown ABI" << endl;

    //0 for system v, third edition
    hex_cout("ABI Version:  ", (unsigned int)elf_header->e_ident[8]);

    cout << "Object File Types: ";
    switch((unsigned int)elf_header->e_type)
    {
    
        case 0: 
            cout << "No file type" << endl;
            break;
        case 1:
            cout << "Relocatable object file" << endl;
            break;
        case 2:
            cout << "Executable file" << endl;
            break;
        case 3:
            cout << "Shared object file" << endl;
            break;
        case 4:
            cout << "Core file" << endl;
            break;
        default:
            cout << "unknow Object File Type" << endl;
    }

    hex_cout("Start of padding bytes: ",(unsigned int)elf_header->e_ident[9]);

    //1 = current
    cout << "File Version: " << (unsigned int)elf_header->e_ident[6] << endl;
    hex_cout("Machine Type: ", elf_header->e_machine);

    //1 = current
    hex_cout("Object File Version: ", elf_header->e_version);

    hex_cout("Entry Point Address: ", elf_header->e_entry);

    //contain processor-specific flags
    hex_cout("Processor-specific flags: ", elf_header->e_flags);
    
    //if no programe header, it is set to 0
    cout << endl;
    hex_cout("Programe header Offset: ", elf_header->e_phoff);
    hex_cout("Size of program header entry: ", elf_header->e_phentsize);
    hex_cout("Number of program header entries: ", elf_header->e_phnum);
    cout << endl;

    cout << endl;
    hex_cout("Section header Offset: ", elf_header->e_shoff);
    hex_cout("Size of section header entry: ", elf_header->e_shentsize);
    hex_cout("Number of section header entires: ", elf_header->e_shnum);
    hex_cout("Section name string table index: ", elf_header->e_shstrndx);
    cout << endl;

    cout << "#----------START ELF HEADER--------#" << endl;
    free(elf_header);
    close(fd);

    return 0;
}
