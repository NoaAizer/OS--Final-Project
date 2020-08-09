#define _XOPEN_SOURCE 500
#define _GNU_SOURCE
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>

static int display_info(const char *fpath, const struct stat *sb,
             int tflag, struct FTW *ftwbuf)
{

    if(tflag==FTW_SL ) return 0; //soft link
    printf("%s %ld %s \n",
        (tflag == FTW_D) ? "D" :
        (tflag == FTW_F) ?   "F" :
        (tflag == FTW_DNR) ? "DNR" :
        (tflag == FTW_DP) ? "DP" :
        (tflag == FTW_NS) ? "NS" :"UNKNOWN", sb->st_ino, basename(fpath));
    return 0;           // To tell nftw() to continue 
}

int main(int argc, char *argv[])
{
    struct stat sb;
    const char *fpath=argv[1];

    if (argc != 2) { //not valid input
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
   if (nftw(fpath, display_info, 20, (FTW_PHYS))== -1) { /*FTW_PHYS= Do not follow symbolic links
                                                       !lstat(fpath,&sb)- ALSO WORK AS A FLAG*/
       perror("nftw");
        exit(EXIT_FAILURE);

    }
return 0;
}