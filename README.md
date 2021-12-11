# File-Operations-in-C-Linux
The program can either create an archive file from a list of files or extract the files from a given archive file. The program takes the follow arguments:

mytar {-t | -c | -x | -u} -f <archive_file> [list_of_files]

-t   List the contents of the archive file to stdout
-c   Create a new archive containing the list of one or more files 
-x   Extract the files from the archive
-u   Add one or more new files to an existing archive

All four options above requires the name of the archive file be provided using the -f option.

Only the -c and -u options require the user to provide the list of file names (there could be one or more files). The list is ignored for the other options.  You can assume that the files in the list must be from the current directory.

The -t option lists the files stored in the archive (including the name and the size of each file). The list of the files should be sorted. 

The -x option extracts files from the archive and place them in the current directory.

Implementation
The archive file is a binary file with the following format:
The first four bytes contain an integer which is the number of files contained by the archive.
The next 480 bytes contain a directory. It's an array of 20 elements, each being the following data structure:

struct directory_entry_t {
    char name[20]; /* file name as a null-terminated string */ 
    int size; /* the size of the file in bytes */
    int offset; /* the location (offset from the start of the archive file in bytes) of the file placed in the archive */
};
This means the archive must not contain more than 20 files. And each file's name must not exceed 19 characters (an a null character).

Starting from byte 484 will be the content of the files listed one after another (with their starting offsets registered in the corresponding directory entry).
The -c option creates a new archive, meaning that you need to format the archive file accordingly (putting the number of files, creating the directory, and placing the content of the files). The -u option, however, only needs to add additional files (updating the directory, and appending the content of the new files at the end of the archive). The -t option lists the content of the archive. Also, you need to sort the files according to their names. The -x option extract all the files stored in the archive. You need to create a new file of the given name, and copy the content from the archive (from the given location and with the given size).
Code is able to handle normal error conditions such as:
Either -c, -t, -x, or -u option should be provided. And only one of them is provided.
The -f option must be provided.
The list of file names (to be archived) cannot be longer than 19.
For -c and -u options, one must provide one or more file names.  
The -u option requires an existing archive.
The files to be archived must exist in the current directory (as regular files, not directories). They can be read.
The total number of archived files must not exceed 20.
The same file cannot be archived twice.
The -x option extracts the files by writing them to the current directory. One cannot overwrite an existing file already in the directory.
