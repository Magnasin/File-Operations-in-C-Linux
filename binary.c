#include <arpa/inet.h> 
#include <string.h>

#include "create.h"

uint32_t extract_special_int(char *where, int len) 
{

   int32_t val = -1;

   if ( (len >= sizeof(val)) && (where[0] & 0x80)) 
   {
   /* the top bit is set and we have space * extract the last four bytes */
      val = *(int32_t *)(where + len - sizeof(val));
      val = ntohl(val); /* convert to host byte order */ 
   }
   return val; 
}

int insert_special_int(char *where, size_t size, int32_t val) 
{

   int err=0;
   if(val<0||(size<sizeof(val)) )
   {

      err++;
   }   
   else 
   {

      memset(where, 0, size);
      *(int32_t *)(where + size - sizeof(val)) = htonl(val);
      *where |= 0x80; /* set that high–order bit */
   }
   return err; 
}

int octal_in(char *where, size_t size, int val)
{
   char buff[13];
   int err = 0;
   int len;

   sprintf(buff, "%0*o", (int)size - 1, val);
   len = strlen(buff);

   if (len > size - 1)
   {
      if (insert_special_int(where, size, val))
      {
         usage();
         err++;
      }
   }
   
   else
   {
      memmove(where, buff, len);
   }
   return err;
}

