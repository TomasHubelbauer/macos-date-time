#include <iostream>
#include <vector>
#include <CoreFoundation/CoreFoundation.h>

int main(int argc, char *argv[])
{
  for (int flag = 0; flag < 2; flag++)
  {
    for (int index = 0; index < 5; index++)
    {
      // https://developer.apple.com/documentation/corefoundation/cfdateformatterstyle?language=objc
      CFDateFormatterStyle formatter;
      char *formatterDebug;
      switch (index)
      {
      case 0:
        formatter = kCFDateFormatterNoStyle;
        formatterDebug = (char *)"no";
        continue;
      case 1:
        formatter = kCFDateFormatterShortStyle;
        formatterDebug = (char *)"short";
        break;
      case 2:
        formatter = kCFDateFormatterMediumStyle;
        formatterDebug = (char *)"medium";
        break;
      case 3:
        formatter = kCFDateFormatterLongStyle;
        formatterDebug = (char *)"long";
        break;
      case 4:
        formatter = kCFDateFormatterFullStyle;
        formatterDebug = (char *)"full";
        break;
      }

      CFLocaleRef locale = CFLocaleCopyCurrent();
      CFDateFormatterRef f = CFDateFormatterCreate(NULL, locale, flag == 0 ? formatter : kCFDateFormatterNoStyle, flag == 1 ? formatter : kCFDateFormatterNoStyle);
      CFStringRef cfStr = CFDateFormatterGetFormat(f);
      CFIndex length = CFStringGetLength(cfStr);
      CFIndex maxSize = CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8);
      std::vector<char> buffer(maxSize, 0);
      CFStringGetCString(cfStr, buffer.data(), maxSize, kCFStringEncodingUTF8);
      std::string s = std::string(buffer.begin(), buffer.end());
      printf("%s %s: \"%s\"\n", flag == 0 ? "date" : "time", formatterDebug, s.c_str());
      CFRelease(locale);
      CFRelease(f);
    }
  }
}
