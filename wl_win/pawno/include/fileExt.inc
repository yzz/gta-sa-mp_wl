
native Ext_fopen(FileNum, FileName[], mode[]);
//mode "w" "r" "a" "w+" "r+" "a+"
// return value:
// -1 - file has been opened.
// -2 - open mode error.
// -3 - fileNum is too big.
// 0 - opening file failed.
// 1 - opening file succeed.

native Ext_fread(FileNum, string[], size = sizeof string);
// return value:
// -1 - the stream is not opened.
// -2 - the stream can't be readed.
// -3 - has been eof
// 0 - reading file failed.
// 1 - reading file succeed.

native Ext_fwrite(FileNum, string[]);
// return value:
// -1 - the stream is not opened.
// -2 - the stream can't be writed.
// -3 - the string is null
// 0 - writing file failed.
// 1 - writing file succeed.

native Ext_feof(FileNum);
// return value:
// -1 - the file is not opened.
// 0 - not eof.
// 1 - eof.

native Ext_fclose(FileNum);
// return value:
// -1 - the file is not opened.
// 0 - closing file failed.
// 1 - closing file succeed..



/*
PHP - Explanation of Different Types of fopen

These three basic ways to open a file have distinct purposes. If you want to get information out of a file, like search an e-book for the occurrences of "cheese", then you would open the file for read only.

If you wanted to write a new file, or overwrite an existing file, then you would want to open the file with the "w" option. This would wipe clean all existing data within the file.

If you wanted to add the latest order to your "orders.txt" file, then you would want to open it to append the data on to the end. This would be the "a" option.
PHP - File Open: Advanced

There are additional ways to open a file. Above we stated the standard ways to open a file. However, you can open a file in such a way that reading and writing is allowable! This combination is done by placing a plus sign "+" after the file mode character.

    * Read/Write: 'r+'

Opens a file so that it can be read from and written to. The file pointer is at the beginning of the file.

    * Write/Read: 'w+'

This is exactly the same as r+, except that it deletes all information in the file when the file is opened.

    * Append: 'a+'

This is exactly the same as r+, except that the file pointer is at the end of the file.
*/