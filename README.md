**Project Title**
MP3 Tag Reader and Editor using ID3v2.3

**Overview**
This project is a console-based MP3 metadata reader and editor that works with ID3v2.3 tags.
It allows users to read and modify important metadata fields of an MP3 file without affecting the audio content.

**The project focuses on six commonly used tags:**
  Title
  Artist
  Album
  Year
  Composer
  Content (Genre)
  
**Features**
Read MP3 metadata (ID3v2.3)
Edit selected tags
Supports only ID3v2.3 format
Console-based user interface
Safe editing without corrupting audio data

**Working Principle**
MP3 files contain metadata stored in ID3 tags at the beginning of the file.
Each tag is stored as a frame:
Frame ID (e.g., TIT2 for title)
Size
Flags
Data

**The program:**
Reads the tag header
Identifies frames
Extracts or modifies required fields

**Supported Frames**
Tag	Frame ID
Title	TIT2
Artist	TPE1
Album	TALB
Year	TYER
Composer	TCOM
Content (Genre)	TCON

**Requirements**
GCC Compiler
MP3 file with ID3v2.3 tags

**Limitations**
Supports only ID3v2.3
Limited to 6 tags
No GUI (console-based)
Does not support ID3v1 or ID3v2.4

**Future Improvements**
Support ID3v2.4
Add album art editing
GUI-based interface
Batch processing of multiple files

**Key Concepts Used**
File handling in C
Binary file parsing
Structure handling
Endianness (Big-endian handling)
String manipulation

**Applications**
Music library management
Metadata editing tools
Digital media organization
