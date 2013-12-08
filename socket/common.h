//
//  common.h
//  CommandLineApp
//
//  Created by Guo Jiazhen on 12/8/13.
//  Copyright (c) 2013 Guo Jiazhen. All rights reserved.
//

#ifndef CommandLineApp_common_h
#define CommandLineApp_common_h

#define BUFF_LENGTH 1024    //!< buffer length for communicating


// explicit declaration to remove the warnings
int  close(int) __DARWIN_ALIAS_C(close);

ssize_t	 read(int, void *, size_t) __DARWIN_ALIAS_C(read);
ssize_t	 write(int, const void *, size_t) __DARWIN_ALIAS_C(write);

unsigned int sleep(unsigned int) __DARWIN_ALIAS_C(sleep);

//! General socket-realted error handler that terminates the program on error.
/*!
 \param fd input parameter, the return value of a previous socket function.
 \param msg input parameter, the additional message.
 */
void handle_error(int fd, char* msg)
{
    if (fd == -1)
    {
        perror(msg);
        exit(EXIT_FAILURE);
    }
}

#endif
