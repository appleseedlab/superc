#include<string.h>

/** Number of UTF-16 characters per entry */
#define FILENAME_LENGTH 13

#ifdef SDSUPPORT

void cardreader(char *prepend)
{
  int len = strlen(prepend) + FILENAME_LENGTH + 1; // Error - not enough space allocated if prepend is empty
  char path[len];
  // Get the short name for the item, which we know is a folder
  //char lfilename[FILENAME_LENGTH];
  //createFilename(lfilename, p);
  char lfilename[FILENAME_LENGTH] = "FOLDERNAME12\0";
  // Append the FOLDERNAME12/ to the passed string.
  // It contains the full path to the "parent" argument.
  // We now have the full path to the item in this folder.
  path[0] = '\0';
  if (prepend[0] == '\0') strcat(path, "/"); // a root slash if prepend is empty
  strcat(path, prepend);
  strcat(path, lfilename);
  strcat(path, "/");

}
#endif


int main(int argc, char **argv)
{
  cardreader("");
  return 0;
}
