/******************************************************************************
 * STYLE2A VER: 0.01
 * 05/04/2016
 * URL: https://github.com/erickleist/STYLE2A
 *
 * Inspired by:     style50        (https://cs50.harvard.edu/)
 * Written by:      eric kleist    (http://www.ericjk.com)
 * Color Credits:   gon1332        (http://bit.ly/24yODQ0)
 *
 * Project Goal:
 *
 * STYLE2A is designed around the style rules for CS2A at Foothill College.
 * Good style is essential to quality programming and STYLE2A makes sure
 * that you follow the correct style so your code is consistent and within
 * the CS2A Style Requirements.
 *
 * Don't lose points for a silly style mistake!
 * Check your code with STYLE2A before submission!
 *
 * Requirements:
 *
 * Currently STYLE2A only works on linux and most likely unix. For optimal
 * display you must have a color enabled terminal.
 *
 * Operation:
 *
 * ./STYLE2A /home/user/example/source_code_file_location
 *
 * Limitations:
 *
 * Although the code is simple, it has been working effectively for my homework
 * submissions. This does not mean you should not do a manual check as well.
 * STYLE2A is not complete, and currently only checks your file for:
 *
 *    - Tabs
 *    - Line Length
 *    - Brace Location
 *    - File Type
 *    - Paste of Run
 *    - more to come...
 *
 * Disclaimer:
 *
 * Code is only up to par for features that are implemented. As new features
 * are implemented, code will be upgraded to match style rules. :)
 *
 * Bugs? Errors? Want to Help?
 *
 * Bug list coming soon...
 *
 * If you want to help out or find any bugs or errors please send me an email
 * at ericjkleist@gmail.com, thank you!
 *
 *****************************************************************************/

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <string>
using namespace std;

#define RST   "\x1B[0m";
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define RED(x) KRED x RST
#define GRN(x) KGRN x RST
#define YEL(x) KYEL x RST
#define BOLD(x) "\x1B[1m" x RST

bool validateUsage(int arguments, char *fileLocation);
void checkTabs(char *fileLocation);
void checkLineLength(char *fileLocation);
void checkBraces(char *fileLocation);
void isFileTxt(char *fileLocation);
void checkPasteOfRun(char *fileLocation);

int main(int argc, char *argv[])
{
   char *fileLocation = argv[1];
   bool validRun;

   validRun = validateUsage(argc, fileLocation);

   if (validRun)
   {
      checkTabs(fileLocation);
      checkLineLength(fileLocation);
      checkBraces(fileLocation);
      isFileTxt(fileLocation);
      checkPasteOfRun(fileLocation);
   }
   else
   {
      return 0;
   }

   return 0;
}

bool validateUsage(int arguments, char *fileLocation)
{
   if (arguments != 2)
   {
      cout << "ERROR: Incorrect Usage. Please use: "
            "./STYLE2A file_name.txt\n";
      return false;
   }
   else
   {
      ifstream user_file (fileLocation);
      if (!user_file.is_open())
      {
         cout << "ERROR: Opening File. Check file path and try again.\n";
         return false;
      }
   }
   return true;
}

void checkTabs(char *fileLocation)
{
   char singleChar;
   int lineCounter, charCounter, tabCounter;
   string lineCharStr;
   ifstream user_file (fileLocation);

   lineCounter = 1;
   charCounter = 1;
   tabCounter = 0;

   while (user_file.get(singleChar))
   {
      if (singleChar == '\t')
      {
         cout << BOLD(RED(":( " << setw(4) << right
               << lineCounter << ":" << setw(3) << left
               << charCounter << "  Tab Found. \n"));
         tabCounter++;
      }
      if (singleChar == '\n')
      {
         lineCounter++;
         charCounter = 0;
      }
      charCounter++;
   }
   if (tabCounter == 0)
   {
      cout << BOLD(GRN(":) Tab Check Complete. No tabs Found.\n"));
   }
}

void checkLineLength(char *fileLocation)
{
   char singleChar;
   int charCounter, lineCounter, lineLengthCounter;
   ifstream user_file (fileLocation);

   lineCounter = 1;
   charCounter = 0;
   lineLengthCounter = 0;

   while (user_file.get(singleChar))
   {
      charCounter++;

      if (singleChar == '\n')
      {
         if (charCounter > 81)
         {
            cout << BOLD(RED( << setw(5) << left << ":( " <<  setw(6)
                  << left << lineCounter
                  << "  Line exceeds 80 characters in length. \n"));
            lineLengthCounter++;
         }
         lineCounter++;
         charCounter = 0;
      }
   }

   if (lineLengthCounter == 0)
   {
      cout << BOLD(GRN(":) Line Length Check Complete. No lines over 80 "
            << "characters found.\n"));
   }
}

void checkBraces(char *fileLocation)
{
   bool hasOthers;
   char singleChar;
   int lineCounter, charCounter, braceCounter, braceLineCounter;
   string lineCharStr;
   ifstream user_file (fileLocation);

   lineCounter = 1;
   charCounter = 0;
   braceCounter = 0;
   braceLineCounter = 0;
   hasOthers = false;

   while (user_file.get(singleChar))
   {
      if (singleChar != ' ')
      {
         charCounter++;
      }

      if (singleChar == '{' || singleChar == '}')
      {
         if (charCounter > 1)
         {
            hasOthers = true;
         }
         braceLineCounter++;
      }

      if (singleChar == '\n')
      {

         if (charCounter > 3 && braceLineCounter >= 1)
         {
            cout << BOLD(RED(<< setw(5) << left << ":( "
                  << setw(6) << left << lineCounter
                  << "  Brace found on a line with other characters. \n"));
            braceCounter++;
            hasOthers = false;
         }


         if (hasOthers == true && braceLineCounter >= 1)
         {
            cout << BOLD(RED(<< setw(5) << left << ":( "
                  << setw(6) << left << lineCounter
                  << "  Brace found on a line with other characters. \n"));
            braceCounter++;
         }

         lineCounter++;
         braceLineCounter = 0;
         hasOthers = false;
         charCounter = 0;
      }
   }
   if (braceCounter == 0)
   {
      cout << BOLD(GRN(":) Brace Check Complete. All braces on "
            "lines by themselves.\n"));
   }
}

void isFileTxt(char *fileLocation)
{
   int length;
   string prefix;

   length = strlen(fileLocation);

   for (int k = length - 3; k < length; k++)
   {
      prefix += tolower(fileLocation[k]);
   }

   if (prefix != "txt")
   {
      cout << BOLD(YEL(":| " << "File Type Check Complete. File is"
            " not a .txt file \n"));
   }
   else
   {
      cout << BOLD(GRN(":( " << "File Type Check Complete. File is"
            " a .txt file \n"));
   }



}

void checkPasteOfRun(char *fileLocation)
{
   int strLength, totalLines, lineCounter;
   string inString, searchString;
   ifstream user_file (fileLocation);
   ifstream user_file2 (fileLocation);

   totalLines = 0;
   lineCounter = 0; // need to bug check?? why not 0?
   strLength = 0;

   while ( getline(user_file, inString))
   {
      totalLines++;
   }

   while ( getline(user_file2, inString))
   {
      lineCounter++;
      strLength = inString.length();

      if (lineCounter == totalLines)
      {

         if (inString.find("end of run") != std::string::npos)
         {
            cout << BOLD(GRN(":) Paste of Run Check Complete. Last line is "
                  << "end of run comment.\n"));
         }
         else if (inString[strLength - 2] == '/' &&
               inString[strLength - 3] == '*')
         {
            cout << BOLD(GRN(":) Paste of Run Check Complete. Last line is "
                  << "end of multi-line comment.\n"));
         }
         else if (inString.find("}") != std::string::npos ||
               inString.find("return") != std::string::npos)
         {
            cout << BOLD(RED(":( WARNING!  Paste of run is not included.\n"));
         }
         else if (inString.length() == 1)
         {
            cout << BOLD(YEL(":| Paste of Run Check Complete. Last line is "
                  << "empty, please check.\n"));
         }
         else
         {
            cout << BOLD(YEL(":| Paste of Run Check Complete. Could not verify "
                  << "paste of run, please check.\n"));
            cout << inString.length();
         }
      }
   }
}
