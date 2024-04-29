/***********************************************************
	         mini-library 2018-05
	         Edouard  BERGE v0.47

      !!! DO NOT INCLUDE THIS FILE, USE library.h !!!	

changes v047:
- bugfix linux fnmatch
- TxtStrDupLen

changes v046:
- _internal_readtextfile windows compatibility

changes v045:
- debug info on FileReadBinary
- bugfix in FileSeekBinary (to complete)

changes v044:
- stristr
- CSVGetQuotedFieldNumber
- CSVGetAllQuotedFields

changes v043:
- no INFO/DEBUG/ERROR message if colors are enabled

changes v042:
- TxtToMultiLigne, TxtJustifyAlloc
- better date format check
- XMLGetFieldAttrValue check if there is attributes

changes v041:
- XML core improvement
- FileSeekBinary
- File core can handle an unlimited of files
- BlockFileInit, BlockFileRead, BlockFileWritePrepare, BlockFileWriteFinalize, BlockFileClose
	  
changes v040:
- XML core can handle and check namespaces
- XML core may join contiguous CDATA segments
- XML behaviour of Get functions
- XMLMakeCDATASection
- bugfix in comment duplication in XMLDuplicateField
- bugfix in MemCpy overriding check

changes v039:
- FileWriteLines

changes v038:
- RandIsaacForceSeed
- MaxDouble, MinDouble, MaxFloat, MinFloat
- MaxLong, MinLong, MaxULong, MinULong
- MaxInt, MinInt, MaxUInt, MinUInt
- MaxShortInt, MinShortInt, MaxUShortInt, MinUShortInt
- MaxChar, MinChar, MaxUChar, MinUChar

changes v037:
- MinMaxFloat casting
- FastRand
- XMLGetFieldValue
- FileReadContent
- ChronoGetMicroSecond,ChronoGetNanoSecond

changes v036:
- MemDuplicate give useful informations when memory overflow
- Isaac generator with a "real" random init

changes v035:
- ChronoGetSecond, ChronoGetMilliSecond Windows compliant
- Regexp function wrapper for Windows compatibility
- RandIsaac cryptographically secure pseudorandom generator
	  
changes v034:
- Better casting for memory functions (less warning with verbose compiler)
- More info on MemCheck error
- OpenLibrary allow Linux programm to guess wich caused segfault
- XML core bugfix on CDATA segment
- pthread Windows compliant
- ChronoStart/Stop, NanoSleep Windows compliant
- Dir function Windows compliant (readdir wrapper)
- LookForFile Windows compliant
- _internal_CPUGetCoreNumber Windows compliant
- ChronoGetMilliSecond
- Regexp functions ARE NOT compliant under Windows
- Process functions ARE NOT compliant under Windows
	  
changes v033:
- CorrelationCharStep

changes v032:
- XMLFieldAddAttribute, XMLFieldAddAttributeLong, XMLFieldAddAttributeDouble
- XMLFieldAddAttributeList, XMLFieldAddAttributeListLong, XMLFieldAddAttributeListDouble
- GetYear, GetCurrentYear
- MemDuplicate
- ChronoGetSecond

changes v031:
- Memory(De)Crunch now use LZ4 compression from Yann Colet under New BSD Licence
- MemoryCrunchMax reach better compression ratio (but ten times slower)
- new XML core with full parsing, more integrity checks
- bugfix in FieldArrayAddDynamicValueConcat
- bugfix 64 bits long long casting in TxtSimplifyNumber
- XMLGetFieldAttrValue
- ANSI colors
- MemMove
- NanoSleep

changes v030:
- XML core debug
- Memory core improvement, multi-thread fix
- HashFlush is threaded to run in background
- HashRemoveData, HashPutString, HashGetString, HashPutStringCrunched, HashGetStringCrunched
- MemSet
- Bugfixed FileGetStat when no file found

changes v029: (XML work in progress)
- MemoryCrunch, MemoryDecrunch
- HashPutData, HashGetData, HashFlush, HashFree
- HashPutDataCrunched, HashGetDataCrunched
- BinaryGetCRC
- MemCpy
- ObjectArrayAddDynamicValueConcat
- *ArrayAddDynamicValue optimisation
- XMLGetFieldMulti, XMLDuplicateFieldRecurse, XMLGetFieldAttr
- TxtRegMatch cache mechanism
- FileReadLine(s)XML deprecated
- CSVReadFile, CSVReadFileWithSeparator

changes v028: (XML work in progress)
- CopyFields
- new XML core, XMLParseAttribute, XML attributes, comments and CDATA support, XMLGetField
- FileReadPos

changes v027:
- ProcessFork, ProcessDetach
- IntArrayAddDynamicValueConcat
- FieldArrayAddDynamicValueConcat activated
- FAST_LIBRARY cleaning
- LookForFile rewrite (clever)
- MemDump 32 bits compliant, also bugfixed for char 127

changes v026:
- ProcessSearch, ProcessExists, ProcessInfo, ProcessQuit, ProcessQuitBackGround
- FileReadClose
- TxtGetFile
- TxtSplit optimisation
- FieldArrayAddDynamicValueConcat changes (multi-thread compliant)
- Linux host as default 

changes v025:
- TxtConcat, TxtConcatWithSeparator
- ChronoStart optimisation
- ExecuteSysCmdBackGround,ExecuteSysCmdBackGroundPushed,ExecuteSysCmdWaitForThreads
- setdebug is now deprecated
- _internal_strdup optimisation
- SystemInfo now running on Linux platform
- FileExists

changes v024:
- do not display memory stats when using FAST_LIBRARY mode
- FAST_LIBRARY mode use google perftools http://code.google.com/p/gperftools/
- MemFree, MemMalloc, MemCalloc, MemRealloc, MemCheck, MemMonitor are now multi-thread compliant
- strappend, strnappend, strappendchar, strnappendchar
- TxtSplit, TxtMerge, TxtMergeWithSeparator
- strnicmp

changes v023:
- DirReadAllEntriesRecurse, DirMatchAllEntriesRecurse
- FileReadLines, FileReadLinesXML
- TxtGetCRC
- _internal_CPUGetCoreNumber
- FieldArrayAddDynamicValueConcat
- FAST_LIBRARY mode (no check on MemMalloc, MemRealloc of MemFree)

changes v022:
- ChronoStart, ChronoStop
- TxtTrimEnd optimisation
- more includes

changes v021:
- Numeric filter functions
- SmoothBufferInt
- MinMaxDouble, MinMaxLong, MinMaxInt
- CorrelationChar, CorrelationInt
- DirReadAllEntries, DirMatchAllEntries
- ParameterParseFieldList now can parse static buffers
- BugFix in XMLLoadFile
- BugFix in _internal_DirReadGlob
- BugFix in _MemFree

changes v020:
- Now we may disable the memory wrapper (for performance)
- Linux include bugfix
- Bugfixed GetEndianMode

changes v019:
- TxtRegMatch, TxtGlobMatch
- DirMatchEntry

changes v018:
- stricmp
- KeyGetString, KeyGetChoice
- TxtCleanSpecialChar, TxtDeleteSpecialChar, TxtReplaceSpecialChar

changes v017:
- Some bugfixes with va_list usage (Linux)
- Bugfix with programs starting with a Realloc of a NULL pointer and no debug mode
- Better flushing method in _internal_put2log

changes v016:
- Linux compliant
- 64bits compliant
- SystemInfo to display some details about running architecture
- GetAutoEndian to know if the current architecture is big-endian or little-endian
- GetEndianSHORTINT, GetEndianINT, GetEndianLONGLONG to retrieve values regardless of endianness mode
- PutEndianSHORTINT, PutEndianINT, PutEndianLONGLONG to put values in memory regardless of endianness mode
- TxtIsFloat, TxtIsDouble, TxtIsLongDouble
- Some bugfixes in _internal_TxtIsFloat (used for float, double and long double check)

changes v015:
- MemTrace, MemUntrace may use variable label
- Secured writes to text buffer in put2file, ExecuteSysCmd, MemTrace
- MemDump
- TxtGetSubstr
- TxtIsDouble

changes v014:
- Bugfixed FileGetStat error processing
- Harmonisation of errno management
- CloseLibrary checks for opened monitors
- MemTrace, MemUntrace may use label
- _internal_put2log flush when logtype change (to avoid conflicts when both stderr and stdout are redirected together)

changes v013:
- MemTrace, MemUntrace
- Check the memory when freeing memory

changes v012:
- TxtStrReplace is clever with zero size strings
- ChangeDir, GetDir
- ExecuteSysCmdGetLimit
- ExecuteSysCmdBypassError
- ExecuteSysCmd, ExecuteSysCmdBypassError now compute the maximum command line limit
- All filesystem related functions now check for PATH_MAX before processing

changes v011:
- FileChmod
- MakeDirWithRights, MakeDir
- ExecuteSysCmd system limit check (lower for rex compatibility)
- Trim functions now can handle tabs
- ParameterParseFieldList now can handle reversed interval

changes v010:
- Bugfixed MemFree (memory was not freed in the v007, v008, v009)
- Bugfixed Memory monitor leak
- FileRemoveIfExists
- DirRemoveIfExists
- General clean up, comments, internal prototypes harmonisation

changes v009:
- Bugfixed memory leak in CheckDateFormat
- Bugfixed CSVGetAllFields when separator was the very last char of a string (may occur when trimming strings)
- XMLLookForFieldByName, XMLLookForFieldByValue
- FieldArrayAddDynamicValue
- ExecuteSysCmd
- DirRemove now can remove non empty directories recursively

changes v008:
- MemRealloc is more flexible (may realloc to zero size, as a free)
- XML library (parsing, management, file operation)
- ConvertDate (convert any date format to any other)
- Leap year fix in CheckDateFormat
- TxtIsInteger

changes v007:
- Automatic memory check (full in debug_mode, light otherwise)
- TxtIsInvisible function
- TxtTrimEnd, TxtTrimStart, TxtTrimSpace, TxtTrim functions
- Bugfixed LookForFile (memory of callers is now preserved)

changes v006:
- Automatic memory monitor
- CloseLibrary function (check of unfreed memory, unfreed system pointers)
- Bugfixed memory leaks in FileClose and DirClose

changes v005:
- Datetime functions
- Directory reading functions
- File stat function
- Log on file function
- XML specific read function
	
changes v004:
- CSV field parsing functions
- TxtStrDup function
	
changes v003:
- Log functions can handle multiple arguments (very useful)
- Library functions do not use buffers for logs anymore...
- INTERNAL_ERROR is now 7 instead of 1 like ABORT_ERROR
- default DEBUG_MODE to 0
	
changes v002:
- ParameterParseFieldList now can handle interval
- File functions now can handle many file simultaneously

initial release v001:
- Log functions
- Memory management functions
- Text functions (substr, replace)
- File read&write functions
- Parameters array functions

************************************************************/

#define __FILENAME__ "library_v046.c"
#define FUNC ""

#define LIBRARY_NO_MEMORY_WRAPPER 0

/* force DEBUG_MODE to a value */
#ifndef DEBUG_MODE
#define DEBUG_MODE 0
#endif

/* default is a Linux host */
#ifndef OS_WIN
#define OS_LINUX 1
#define OS_AIX 1
#ifdef OS_LINUX
#undef OS_AIX
#endif
#endif

/* includes for all OS */

#include<stddef.h>
#include<stdint.h>
#include<setjmp.h>

#include<string.h>
#include<stdlib.h>
#include<stdarg.h>
#ifndef OS_WIN
#include<dirent.h>
#endif
#include<stdio.h>
#include<errno.h>
#include<ctype.h>
#include<time.h>
#include<math.h>
#include<sys/types.h>
#include<sys/stat.h>
#ifndef OS_WIN
#include<unistd.h>
#endif
#include<fcntl.h>
#ifndef OS_WIN
#include<regex.h>
#endif

/* OS specific includes */
#ifdef OS_AIX
#include<curses.h>
#endif

#ifdef OS_LINUX
#include<wait.h>
#include<signal.h>
#include<limits.h>
#include<tgmath.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/timeb.h>
#define ARG_MAX 131072
#endif

#ifdef OS_WIN
#include<errno.h>
#include<io.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<direct.h>
#include<windows.h>
#include<setjmp.h>
#include<intrin.h>
#include<errno.h>
#include<sys/timeb.h>

#include"trex.h"
#include"fnmatch.h"
#include"dirent.h"
#include"winpthread.h"
#define PATH_MAX MAX_PATH
#define ARG_MAX 8191
#else
#include<fnmatch.h>
#endif

#ifndef FAST
#ifdef FAST_LIBRARY
//#include <gperftools/tcmalloc.h>
#if OS_WIN
#define tc_malloc malloc
#define tc_realloc realloc
#define tc_free free
#else
#include "../../code/gperftools-2.0/src/gperftools/tcmalloc.h"
#endif
#endif
#else
	/* FAST */
	#define tc_malloc malloc
	#define tc_realloc realloc
	#define tc_free free
	#define FAST_LIBRARY 1
#endif


#ifndef RDD
#include"lz4.h"
#endif

#ifndef M_PI
#define M_PI 3.141592653589793238462643
#endif
#ifndef M_LN2
#define M_LN2 0.69314718055994530942
#endif

enum e_bool {
false=0,
true
};

#ifndef OS_WIN
extern char **environ;
#else
	char **environ=NULL;
	#endif

#define INTERNAL_ERROR 7
#define ABORT_ERROR 1

#define MAX_LINE_BUFFER 16384

#define REG_MATCH             0

#define GET_ENDIAN_UNDEFINED -1
#define GET_LITTLE_ENDIAN     0
#define GET_BIG_ENDIAN        1
#define GET_AUTO_ENDIAN       2

#define PUT_ENDIAN_UNDEFINED  GET_ENDIAN_UNDEFINED
#define PUT_LITTLE_ENDIAN     GET_LITTLE_ENDIAN
#define PUT_BIG_ENDIAN        GET_BIG_ENDIAN
#define PUT_AUTO_ENDIAN       GET_AUTO_ENDIAN

#ifndef OS_WIN
#define KNORMAL "\x1B[0m"
#define KRED    "\x1B[31m"
#define KGREEN  "\x1B[32m"
#define KYELLOW "\x1B[33m"
#define KBLUE   "\x1B[34m"
#define KCYAN   "\x1B[36m"
#define KWHITE  "\x1B[37m"
#else
#define KNORMAL ""
#define KRED    ""
#define KGREEN  ""
#define KYELLOW ""
#define KBLUE   ""
#define KCYAN   ""
#define KWHITE  ""
#endif
/* statics */

pthread_mutex_t mutex_memory_management;

static char _static_library_txtcleanconvtable[256];
static int _static_library_endian_mode=GET_ENDIAN_UNDEFINED;

static int _static_library_nbfile_opened=0;
static int _static_library_nbfile_opened_max=0;
static int _static_library_nbdir_opened=0;
static int _static_library_nbdir_opened_max=0;

enum e_quote_type {
	NO_QUOTE=0,
	SINGLE_QUOTE='\'',
	DOUBLE_QUOTE='"'
};

/***
	LOG functions
	
	output:
	- the type of log (info, warning, error)
	- the source filename
	- the line of the log
	- the C function
	- the error message
*/


/***
	_internal_put2log
	
	internal use, do not call this function
*/
enum e_logtype {
LOG_START,
LOG_STDOUT,
LOG_STDERR
};


int _internal_CPUGetCoreNumber()
{
        #undef FUNC
        #define FUNC "_internal_CPUGetCoreNumber"

        static int nb_cores=0;
#ifdef OS_WIN
		SYSTEM_INFO sysinfo;
		if (!nb_cores) {
			GetSystemInfo( &sysinfo );
			nb_cores=sysinfo.dwNumberOfProcessors;
		}
#else
        if (!nb_cores) {
                nb_cores=sysconf(_SC_NPROCESSORS_ONLN );
                if (nb_cores<=0)
                        nb_cores=1;
        }
#endif
        return nb_cores;
}
#define CPU_NB_CORES _internal_CPUGetCoreNumber()



/***
	stricmp, strnicmp
	
	make an strcmp comparison case insensitive
*/
#ifndef OS_WIN
int stricmp(char *str1,char *str2)
{
	int idx;
	int c1,c2;
	
	if (!str1) return (!str2)?0:-(*str2);
	if (!str2) return *str1;

	while ((c1=tolower(*str1))==(c2=tolower(*str2)) && *str1)
	{
		str1++;
		str2++;
	}
	
	return c1-c2;
}

int strnicmp(char *str1,char *str2,int l)
{
	int idx;
	int c1=0,c2=0;

	if (!l) return 0;	
	if (!str1) return (!str2)?0:-(*str2);
	if (!str2) return *str1;

	while (l && (c1=tolower(*str1))==(c2=tolower(*str2)) && *str1)
	{
		str1++;
		str2++;
		l--;
	}
	
	return c1-c2;
}
#endif

char *stristr(char *str, char *sub)
{
	int idx,ls,imax,l;

	ls=strlen(sub);
	l=strlen(str);
	for (idx=0;idx<l-ls;idx++) {
		if (strnicmp(&str[idx],sub,ls)==0) {
			return str+idx;
		}
	}
	return NULL;
}

char *strn0cpy(char *str1, const char *str2, int lg)
{
	if (str1==NULL || str2==NULL) return NULL;
	while (lg && *str2) {
		*str1++=*str2++;
		lg--;
	}
	*str1=0;
	return str1;
}

/***
 *	strappend, strnappend, strappendchar, strnappendchar
 *
 *	like strcat but returns the number of concatenated char
 *	this is usefull to optimized many strcat
 *	anyway the function will check that the pointer is
 *	the really end of the string. If not, it will seek
 *	to the end.
 *
 *	char versions optimised for char
 *	n versions limit the number of concat chars
 *
 *	outstr[0]=0;
 *	cw =strappend(outstr  ,"blablablala");
 *	cw+=strappend(oustr+cw,"reblablabla");
 *	cw+=strappend(oustr+cw,"reblablabla");
 *	cw+=strappend(oustr+cw,"reblablabla");
 *	    strappend(oustr+cw,"reblablabla");
 *
 */
/***
 *	append a string
 *	return the number of char appened
 */
int strappend(char *Adst, char *Asrc)
{
	int Lcpt=0;

	/* must be at the end to concat */
	while (*Adst) {
		Adst++;
	}

	/* concat and count */
	while (*Asrc) {
		*Adst++=*Asrc++;
		Lcpt++;
	}
	*Adst=0;

	return Lcpt;
}
/***
 *	append a string, limited to Amax
 *	return the number of char appened
 */
int strnappend(char *Adst, char *Asrc, int Amax)
{
	int Lcpt=0;

	if (Amax<1) return 0;

	/* must be at the end to concat */
	while (*Adst) {
		Adst++;
	}
	/* concat, count and limit */
	while (*Asrc && Amax) {
		*Adst++=*Asrc++;
		Lcpt++;
		Amax--;
	}
	*Adst=0;

	return Lcpt;
}

/***
 *	append a char to a string
 *	return the number of char appened
 */
int strappendchar(char *Adst, char Asrc)
{
	int Lcpt=0;

	/* must be at the end to concat */
	while (*Adst) {
		Adst++;
	}

	/* concat */
	*Adst++=Asrc;
	*Adst=0;

	return 1;
}
/***
 *	append a char, limited to Amax
 *	return the number of char appened
 */
int strnappendchar(char *Adst, char Asrc, int Amax)
{
	/* limit */
	if (Amax<1) return 0;

	/* must be at the end to concat */
	while (*Adst) {
		Adst++;
	}

	/* concat, count */
	*Adst++=Asrc;
	*Adst=0;

	return 1;
}



void _internal_put2log(char *logtype, char *cursource, int curline, char *curfunc, ...)
{
	#undef FUNC
	#define FUNC "_internal_put2log"
	
	static int last_std=LOG_START;
	int cur_std;
	char *format;
	va_list argptr;
	long dek=0;

	char zedatetime[256];
#ifdef OS_WIN
        time_t l_time;
#else
        long l_time;
#endif
        struct tm *timestruct;

#ifdef OS_WIN
        dek=0;
        time(&l_time);
#else
        l_time = time(&dek);
#endif
        timestruct = localtime( &l_time);

	sprintf(zedatetime,"%d%02d%02d|%02d:%02d:%02d",timestruct->tm_year+1900,timestruct->tm_mon+1,timestruct->tm_mday,timestruct->tm_hour,timestruct->tm_min,timestruct->tm_sec);

	va_start(argptr,curfunc);
	format=va_arg(argptr,char *);

	if (strcmp(logtype,"INFO  ")==0 || strcmp(logtype,"WARN  ")==0 || strcmp(logtype,"MONITOR ")==0 || strcmp(logtype,"DEBUG ")==0)
		cur_std=LOG_STDOUT;
	else
		cur_std=LOG_STDERR;
		
	/* when logtype changes from previous value, we flush the previous output buffer */
	if (cur_std!=last_std)
	{
		switch (last_std)
		{
			case LOG_STDOUT:fflush(stdout);break;
			case LOG_START:fflush(stderr);break;
			default:break;
		}
		last_std=cur_std;
	}	

	if (strcmp(logtype,"DEBUG ")==0)
	{
		if (DEBUG_MODE)
		{
			fprintf(stdout,KCYAN"%s (%s) L%d - %s - ",zedatetime,cursource,curline,curfunc);
			vfprintf(stdout,format,argptr);
			fprintf(stdout,KNORMAL"\n");
		}
	}
	else
	if (strcmp(logtype,"INFO  ")==0 || strcmp(logtype,"WARN  ")==0 || strcmp(logtype,"MONITOR ")==0)
	{
		switch (logtype[0]) {
			case 'I':fprintf(stdout,KNORMAL);break;
			case 'W':fprintf(stdout,KYELLOW);break;
			case 'M':fprintf(stdout,KWHITE);break;
		}
		fprintf(stdout,"%s (%s) L%d - %s - ",zedatetime,cursource,curline,curfunc);
		vfprintf(stdout,format,argptr);
		fprintf(stdout,KNORMAL"\n");
	}
	else
	{
		fprintf(stderr,KRED"%s (%s) L%d - %s - ",zedatetime,cursource,curline,curfunc);
		vfprintf(stderr,format,argptr);
		fprintf(stderr,KNORMAL"\n");
	}
	
	va_end(argptr);
}

/* prototypes needed in the top of the file */
void CSVFreeFields(char **fields);
#define FreeFields(fields) CSVFreeFields(fields)

#ifndef OS_WIN
mode_t FileGetMode(char *filename);
#define FileIsSocket(filename) ((FileGetMode(filename) & S_IFSOCK)==S_IFSOCK)
#define FileIsLink(filename) ((FileGetMode(filename) & S_IFLNK)==S_IFLNK)
#define FileIsRegular(filename) ((FileGetMode(filename) & S_IFREG)==S_IFREG)
#define FileIsBlockDevice(filename) ((FileGetMode(filename) & S_IFBLK)==S_IFBLK)
#define FileIsDir(filename) ((FileGetMode(filename) & S_IFDIR)==S_IFDIR)
#define FileIsCharacterDevice(filename) ((FileGetMode(filename) & S_IFCHR)==S_IFCHR)
#define FileIsFifo(filename) ((FileGetMode(filename) & S_IFIFO)==S_IFIFO)
#else
	#define FileIsDir(filename) printf(filename)
#define FileIsRegular(filename) printf(filename)
#endif
long long FileGetSize(char *filename);
char **_internal_DirReadAllGlob(char *dirname,int globflag,int recurseflag,int sortflag);
#define DirReadEntry(dirname) _internal_DirReadGlob(dirname,0,0)
#define DirMatchEntry(dirname) _internal_DirReadGlob(dirname,1,0)
#define DirReadAllEntries(dirname) _internal_DirReadAllGlob(dirname,0,0,0)
#define DirMatchAllEntries(dirname) _internal_DirReadAllGlob(dirname,1,0,0)
#define DirReadAllEntriesRecurse(dirname) _internal_DirReadAllGlob(dirname,0,1,0)
#define DirMatchAllEntriesRecurse(dirname) _internal_DirReadAllGlob(dirname,1,1,0)

#define DirReadAllEntriesSort(dirname) _internal_DirReadAllGlob(dirname,0,0,1)
#define DirMatchAllEntriesSort(dirname) _internal_DirReadAllGlob(dirname,1,0,1)
#define DirReadAllEntriesRecurseSort(dirname) _internal_DirReadAllGlob(dirname,0,1,1)
#define DirMatchAllEntriesRecurseSort(dirname) _internal_DirReadAllGlob(dirname,1,1,1)

void FileWriteLine(char *filename, char *buffer);
void *_internal_MemRealloc(void *ptr, int size, char *cursource,int curline, char *curfunc);
void _internal_MemFree(void *ptr, char *cursource,int curline, char *curfunc);
#define MemRealloc(ptr,size) _internal_MemRealloc(ptr,size,__FILENAME__,__LINE__,FUNC)
#define MemFree(ptr) _internal_MemFree(ptr,__FILENAME__,__LINE__,FUNC)

void _internal_ObjectArrayAddDynamicValue(void **zearray, void *zeobject, int object_size,int curline, char *curfunc, char *cursource);
void _internal_ObjectArrayAddDynamicValueConcat(void **zearray, int *nbfields, int *maxfields, void *zeobject, int object_size, int curline, char *curfunc, char *cursource);
#define ObjectArrayAddDynamicValue(zearray,zeobject,objsize) _internal_ObjectArrayAddDynamicValue(zearray,zeobject,objsize,__LINE__,FUNC,__FILENAME__)
#define ObjectArrayAddDynamicValueConcat(zearray,nbv,maxv,zeobject,objsize) _internal_ObjectArrayAddDynamicValueConcat(zearray,nbv,maxv,zeobject,objsize,__LINE__,FUNC,__FILENAME__)
void _internal_IntArrayAddDynamicValueConcat(int **zearray, int *nbval, int *maxval, int zevalue, int curline, char *curfunc, char *cursource);
#define IntArrayAddDynamicValueConcat(zearray,nbv,maxv,zevalue) _internal_IntArrayAddDynamicValueConcat(zearray,nbv,maxv,zevalue,__LINE__,FUNC,__FILENAME__)
void _internal_FieldArrayAddDynamicValue(char ***zearray, char *zevalue, int curline, char *curfunc, char *cursource);
#define FieldArrayAddDynamicValue(zearray,zevalue) _internal_FieldArrayAddDynamicValue(zearray,zevalue,__LINE__,FUNC,__FILENAME__)
void _internal_FieldArrayAddDynamicValueConcat(char ***zearray, int *nbfields, int *maxfields, char *zevalue, int curline, char *curfunc, char *cursource);
#define FieldArrayAddDynamicValueConcat(zearray,nb,maxf,zevalue) _internal_FieldArrayAddDynamicValueConcat(zearray,nb,maxf,zevalue,__LINE__,FUNC,__FILENAME__)
/***
	logfile
	
	log into a file
	internal use, do not call this function
	
	as we must use a temporary buffer before writing to a file
	we must compute the final string size to be sure that we
	have enough memory for it
*/
void _internal_put2file(char *ferrname, char *format, ...)
{
	#undef FUNC
	#define FUNC "logfile"
	
	static char *errbuffer=NULL;
	static int errbuffer_size=0;
	int zelen;
	va_list argptr;
	
	if (format==NULL)
	{
		FileWriteLine(ferrname,NULL);
		errbuffer_size=0;
		/* conditionnal algo may close file without having opened */
		if (errbuffer)
		{
			MemFree(errbuffer);
			errbuffer=NULL;
		}
	}
	else
	{
		/* check that our temporary buffer is big enough for string plus carriage return */
		va_start(argptr,format);
		zelen=vsnprintf(NULL,0,format,argptr)+3;
		/* we reallocate for a bigger size only */
		if (zelen>errbuffer_size)
			errbuffer=MemRealloc(errbuffer,zelen);
		/* reinit the va_list */
		va_end(argptr);
		va_start(argptr,format);
		vsnprintf(errbuffer,zelen,format,argptr);
		va_end(argptr);
		strcat(errbuffer,"\n");
		FileWriteLine(ferrname,errbuffer);
	}
}

/*** LOG macros send useful informations to the put2log function */
#define loginfo(...) _internal_put2log("INFO  ",__FILENAME__,__LINE__,FUNC,__VA_ARGS__)
#define logdebug(...) {if (DEBUG_MODE) _internal_put2log("DEBUG ",__FILENAME__,__LINE__,FUNC,__VA_ARGS__);}
#define logmemory(...) {if (DEBUG_MODE>1) _internal_put2log("DEBUG ",__FILENAME__,__LINE__,FUNC,__VA_ARGS__);}
#define logwarn(...) _internal_put2log("WARN  ",__FILENAME__,__LINE__,FUNC,__VA_ARGS__)
#define logerr(...) _internal_put2log("ERROR ",__FILENAME__,__LINE__,FUNC,__VA_ARGS__)
#define logfile(...) _internal_put2file(__VA_ARGS__)
#define logfileclose(ferrname) _internal_put2file(ferrname,NULL)
#define _internal_put2fileclose(ferrname) _internal_put2file(ferrname,NULL)

/***
	the memory_monitor structure stores for every alloc the
	location in the source of the memory call (function, line)
	as some additionnal informations like the size and the
	auto-incremental number of memory operation.
	
	in addition to that, when allocating memory, we allocate
	more than requested to put an header before the memory
	block and a footer, after. Both are filled with checksum
	and memory codes.
	
	in debug mode, every allocation is checked with those
	headers and footers to prevent segmentation fault and
	make the debuging easier.
	
	there is also a user memory monitor to trace memory operations
	of selected memory areas. The user define a memory zone to
	monitor, then every MemCheck, memory is compared to a backup
	and a warning is done when modifications are encountered.

	note: every functions are disabled in FAST_LIBRARY mode	
*/

#define MEM_MONITOR_FRAG_ELEMENT 20000
/* #define MEM_CHECK_FILLER_SIZE 96 */
#if DEBUG_MODE!=0
#define MEM_CHECK_FILLER_SIZE 220
#else
#define MEM_CHECK_FILLER_SIZE 8
#endif

enum e_memory_way {
WAY_MALLOC,
WAY_REALLOC,
WAY_FREE
};

struct s_memory_monitor
{
	char *ptr;
	unsigned long size;
	char *cursource;
	char *curfunc;
	int curline;
	int mem_op;
};
struct s_memory_monitor *mem_monitor=NULL;

struct s_memory_check_header
{
	unsigned char filler[MEM_CHECK_FILLER_SIZE];
	unsigned long checksum[4]; /* may be 32 or 64 bits depending on the architecture */
};
struct s_memory_check_footer
{
	unsigned long checksum[4]; /* may be 32 or 64 bits depending on the architecture */
	unsigned char filler[MEM_CHECK_FILLER_SIZE];
};

struct s_memory_trace
{
	char *name;
	char *ptr;
	char *backup;
	unsigned long size;
	int active;
	struct s_memory_trace *next;
};

#ifndef FAST_LIBRARY
/* stats disabled in fast library mode */
static struct s_memory_trace *memory_trace_ROOT=NULL;
static int _static_library_memory_used=0;
static int _static_library_memory_used_max=0;
static int _static_library_memory_monitor_top=0;
static int _static_library_memory_monitor_max=0;
static int _static_library_memory_operation=0;
static int _static_library_memory_aggregate=0;
static int _static_library_memory_active_area=0;
#endif

/* need some memory related prototypes cause of cross definitions */
void _internal_MemTrace(char *cursource,int curline, char *curfunc,char *ptr,int size,...);
void _internal_MemUntrace(char *cursource,int curline, char *curfunc,void *ptr,...);
#define MemUntrace(...) _internal_MemUntrace(__FILENAME__,__LINE__,FUNC , ## __VA_ARGS__)
#define MemTrace(...) _internal_MemTrace(__FILENAME__,__LINE__,FUNC , __VA_ARGS__)
char *_internal_strdup(char *in_str,char *cursource,int curline, char *curfunc);
#define TxtStrDup(in_str) _internal_strdup(in_str,__FILENAME__,__LINE__,FUNC)

/***
	MemDump
	
	dump memory in hexa/text on stdout
	
	input: pointer to memory
	       size of the dump in bytes
	
	_internal_MemDump does not make any check about memory rights
	_internal_MemDumpChecked does a check and allow only mallocated memory to be dumped
	MemDump is the library exported function
*/
void _internal_MemDumpFragment(unsigned char * ptr, int row, int max)
{
	#undef FUNC
	#define FUNC "_internal_MemDumpFragment"

	int i,lim1,lim2;

	lim1=row*8;
	lim2=(row+1)*8;

	if (lim1>max) lim1=max;
	if (lim2>max) lim2=max;
	for (i=lim1;i<lim2;i++)
		printf("%02X ",*(ptr+i));
	for (i=0;i<8-(lim2-lim1);i++)
		printf("   ");
	printf(" ");
}
void _internal_MemDump(unsigned char *ptr,int sizedump)
{
	#undef FUNC
	#define FUNC "_internal_MemDump"
	
	int i,j,lim1,lim2;

	fflush(stdout);	
	fflush(stderr);	
	for (i=0;i<sizedump;i+=32)
	{
		printf("%*lX - ",(int)sizeof(long),(long)ptr+i);
		_internal_MemDumpFragment(ptr+i,0,sizedump-i);
		_internal_MemDumpFragment(ptr+i,1,sizedump-i);
		_internal_MemDumpFragment(ptr+i,2,sizedump-i);
		_internal_MemDumpFragment(ptr+i,3,sizedump-i);
		lim2=i+32;
		if (lim2>sizedump) lim2=sizedump;
		for (j=i;j<lim2;j++) {
			if ((*(ptr+j))>=32 && (*(ptr+j))<127)
				printf("%c",(*(ptr+j)));
			else
				printf(".");
		}
		printf("\n");
	}	
	fflush(stdout);	
}
void _internal_MemDumpChecked(char *ptr,int sizedump, char *cursource, int curline, char *curfunc)
{
	#undef FUNC
	#define FUNC "MemDump"

#ifndef FAST_LIBRARY
	int i,ok=0;
	
	_internal_put2log("ERROR ",cursource,curline,curfunc,"dumping %X:%d",ptr,sizedump);
	for (i=0;i<_static_library_memory_monitor_top && !ok;i++)
	{
		if (mem_monitor[i].ptr!=NULL)
		{
			if (ptr>=mem_monitor[i].ptr && ptr<mem_monitor[i].ptr+mem_monitor[i].size)
				ok=1;
		}
	}
	if (!ok)
	{
		_internal_put2log("ERROR ",cursource,curline,curfunc,"You cannot dump an area that was not previously allocated");
		exit(INTERNAL_ERROR);
	}
#endif
	_internal_MemDump(ptr,sizedump);
}
#define MemDump(ptr,sizedump) _internal_MemDumpChecked((unsigned char *)ptr,sizedump,__FILENAME__,__LINE__,FUNC)

/***
	_MemCheck
	
	perform a check of all memory allocated blocks
	
	fullcheck:
	0 perform only one memory check
	1 perform a full memory check (when using DEBUG_MODE or macro call)
	
	in addition to that, a monitor check may be performed if the user enabled it with MemTrace
	
	internal use, do not call this function
	please use the macro MemCheck()
*/
void _mc()
{
printf("exit\n");
}
void _MemCheck(int fullcheck,char *cursource,int curline, char *curfunc)
{
	#undef FUNC
	#define FUNC "_MemCheck"

#ifndef FAST_LIBRARY
	static int cur_check_idx=0;
	struct s_memory_check_header *mem_header;
	struct s_memory_check_footer *mem_footer;
	struct s_memory_trace *mem_trace;
	char *realptr;
	int i,j,ok,istart,iend,dump_size;

	/* multi-thread compliant */
	pthread_mutex_lock(&mutex_memory_management);

	/** memory monitor check **/
	mem_trace=memory_trace_ROOT;
	while (mem_trace!=NULL)
	{
		if (mem_trace->active) {
			/* check if there was some active memory user monitor when freeing memory */
			ok=0;
			for (i=0;i<_static_library_memory_monitor_top && !ok;i++)
			{
				if (mem_monitor[i].ptr<=mem_trace->ptr && mem_trace->ptr<mem_monitor[i].ptr+mem_monitor[i].size)
				{
					ok=1;
				}
			}
			if (!ok)
			{
				_internal_put2log("MONITOR",cursource,curline,curfunc,"Cannot monitor anymore the block [%8X:%d:%s] cause it was freed!",mem_trace->ptr,mem_trace->size,mem_trace->name);
				mem_trace->active=0;
				/* au plus simple */
				mem_trace=memory_trace_ROOT;
				continue;
			}
			
			/* monitor the memory */
			if (memcmp(mem_trace->ptr,mem_trace->backup,mem_trace->size)!=0)
			{
				
				/* warn about the change, then update memory backup */
				_internal_put2log("MONITOR",cursource,curline,curfunc,"memory block [%8X:%d:%s] memory changed!",mem_trace->ptr,mem_trace->size,mem_trace->name);
				if (mem_trace->size<128)
				{
					dump_size=mem_trace->size;
					_internal_put2log("MONITOR",cursource,curline,curfunc,"from:",mem_trace->ptr,mem_trace->size,mem_trace->name);
				}
				else
				{
					dump_size=128;
					_internal_put2log("MONITOR",cursource,curline,curfunc,"from: (dump is limited to 128 bytes)",mem_trace->ptr,mem_trace->size,mem_trace->name);
				}
				_internal_MemDump(mem_trace->backup,dump_size);
				_internal_put2log("MONITOR",cursource,curline,curfunc,"to:",mem_trace->ptr,mem_trace->size,mem_trace->name);
				_internal_MemDump(mem_trace->ptr,dump_size);
				
				memcpy(mem_trace->backup,mem_trace->ptr,mem_trace->size);
			}
		}
		mem_trace=mem_trace->next;
	}
	
	/** memory check **/
	
	//if (!fullcheck)
	if (0)
	{
		/* we want to control only one but used cell */
		istart=cur_check_idx;
		while (istart<_static_library_memory_monitor_top && mem_monitor[istart].ptr==NULL)
			istart++;
		if (istart>=_static_library_memory_monitor_top)
			istart=cur_check_idx=0;
		
		iend=cur_check_idx+1;
		/* we wont check the first alloc if it is a realloc on NULL pointer */
		if (iend>_static_library_memory_monitor_top)
			iend=_static_library_memory_monitor_top;
	} else {
		istart=0;
		iend=_static_library_memory_monitor_top;
	}	
	
	for (j=istart;j<iend;j++)
	{
		if (mem_monitor[j].ptr!=NULL)
		{
			realptr=mem_monitor[j].ptr-sizeof(struct s_memory_check_header);
			mem_header=(struct s_memory_check_header *)realptr;
			mem_footer=(struct s_memory_check_footer *)(mem_monitor[j].ptr+mem_monitor[j].size);
			
			for (i=0;i<MEM_CHECK_FILLER_SIZE;i++)
			{
				if (mem_header->filler[i]!=0xA5)
				{
					/* This is a direct call to put2log, specific to memory management! Do not copy this! */
					_internal_put2log("ERROR",cursource,curline,curfunc,"memory block %8lX header check failed!",(long)mem_monitor[j].ptr);
					_internal_put2log("ERROR",cursource,curline,curfunc,"block ID (%s,L%d,%s)",mem_monitor[j].cursource,mem_monitor[j].curline,mem_monitor[j].curfunc);
					_internal_put2log("ERROR",cursource,curline,curfunc,"dump of the header");
					_internal_MemDump((char*)mem_header,sizeof(struct s_memory_check_header));
					_internal_put2log("ERROR",cursource,curline,curfunc,"dump of data after header");
					_internal_MemDump((char*)mem_monitor[j].ptr,64);
					pthread_mutex_unlock(&mutex_memory_management);
					_mc();
					exit(INTERNAL_ERROR);
				}
				if (mem_footer->filler[i]!=0x5A)
				{
					/* This is a direct call to put2log, specific to memory management! Do not copy this! */
					_internal_put2log("ERROR",cursource,curline,curfunc,"memory block %8lX footer check failed!",(long)mem_monitor[j].ptr);
					_internal_put2log("ERROR",cursource,curline,curfunc,"block ID (%s,L%d,%s)",mem_monitor[j].cursource,mem_monitor[j].curline,mem_monitor[j].curfunc);
					_internal_put2log("ERROR",cursource,curline,curfunc,"dump of data before footer");
					_internal_MemDump((char*)mem_footer-64,64);
					_internal_put2log("ERROR",cursource,curline,curfunc,"dump of footer");
					_internal_MemDump((char*)mem_footer,sizeof(struct s_memory_check_footer));
					pthread_mutex_unlock(&mutex_memory_management);
					_mc();
					exit(INTERNAL_ERROR);
				}
			}
			for (i=0;i<4;i++)
			{
				if (mem_header->checksum[i]!=(unsigned long)realptr*(i+1))
				{
					/* This is a direct call to put2log, specific to memory management! Do not copy this! */
					_internal_put2log("ERROR",cursource,curline,curfunc,"memory block %8X header check checksum failed!",mem_monitor[j].ptr);
					_internal_put2log("ERROR",cursource,curline,curfunc,"block ID (%s,L%d,%s)",mem_monitor[j].cursource,mem_monitor[j].curline,mem_monitor[j].curfunc);
					_internal_put2log("ERROR",cursource,curline,curfunc,"dump of the header");
					_internal_MemDump((char*)mem_header,sizeof(struct s_memory_check_header));
					_internal_put2log("ERROR",cursource,curline,curfunc,"dump of data after header");
					_internal_MemDump((char*)mem_monitor[j].ptr,64);
					pthread_mutex_unlock(&mutex_memory_management);
					_mc();
					exit(INTERNAL_ERROR);
				}
				if (mem_footer->checksum[i]!=(unsigned long)realptr*(i+1))
				{
					/* This is a direct call to put2log, specific to memory management! Do not copy this! */
					_internal_put2log("ERROR",cursource,curline,curfunc,"memory block %8X (s=%ld) footer check checksum failed!",mem_monitor[j].ptr,mem_monitor[j].size);
					_internal_put2log("ERROR",cursource,curline,curfunc,"block ID (%s,L%d,%s)",mem_monitor[j].cursource,mem_monitor[j].curline,mem_monitor[j].curfunc);
					_internal_put2log("ERROR",cursource,curline,curfunc,"dump of data before footer");
					_internal_MemDump((char*)mem_footer-64,64);
					_internal_put2log("ERROR",cursource,curline,curfunc,"dump of footer");
					_internal_MemDump((char*)mem_footer,sizeof(struct s_memory_check_footer));
					pthread_mutex_unlock(&mutex_memory_management);
					_mc();
					exit(INTERNAL_ERROR);
				}
			}
		}
	}
	pthread_mutex_unlock(&mutex_memory_management);
#endif
}

long MemInfo(void *ptr,struct s_memory_monitor *info)
{
	#undef FUNC
	#define FUNC "MemInfo"

	long memsize=0;
#ifndef FAST_LIBRARY
	int memory_monitor_idx=0;

	pthread_mutex_lock(&mutex_memory_management);
	while (mem_monitor[memory_monitor_idx].ptr!=ptr && memory_monitor_idx<_static_library_memory_monitor_top) {
		memory_monitor_idx++;
	}
	if (memory_monitor_idx!=_static_library_memory_monitor_top) {
		if (info) {
			*info=mem_monitor[memory_monitor_idx];
		}
		memsize=mem_monitor[memory_monitor_idx].size;
	} else {
		memsize=-1;
	}
	pthread_mutex_unlock(&mutex_memory_management);
#endif
	return memsize;
}

/***
	_MemMonitor

	monitor memory alloc and free (the adresses are the users adresses, not the real ptr values)
	
	when alloc, informations are stored in a dynamic array, grouping all memory requests
	when realloc, informations are updated
	when free, we check that the pointer is in the array, then we delete informations	
	
	when memory_way equals WAY_MALLOC
	we store ptr in the table, newptr is not used
	when memory_way equals WAY_REALLOC
	we look for ptr in the table then we store the newptr value
	when memory_way equals WAY_FREE
	we look for ptr in the table then we delete the value. newptr is not used
	
	other parameters give debug informations
		
	internal use, do not call this function
*/
#ifndef FAST_LIBRARY	
void _MemMonitor(void *ptr, void *newptr, int size, char *cursource,int curline, char *curfunc,int memory_way)
{
	#undef FUNC
	#define FUNC "_MemMonitor"

	struct s_memory_check_header *mem_header;
	struct s_memory_check_footer *mem_footer;
	char *waylibs[3]={"Malloc ","Realloc","Free   "};
	static int last_memory_monitor_idx=0;
	int memory_monitor_idx;
	char *realptr;
	int i;

	
	_static_library_memory_operation++;
	
	if (memory_way==WAY_REALLOC) {
		logmemory("%s (%8lX->%8lX;%d) %s %s L%d op:%d mem:%d active:%d",waylibs[memory_way],(long)ptr,(long)newptr,size,cursource,curfunc,curline,_static_library_memory_operation,_static_library_memory_used,_static_library_memory_active_area);
	} else {
		logmemory("%s (%8lX;%d) %s %s L%d op:%d mem:%d active:%d",waylibs[memory_way],(long)ptr,size,cursource,curfunc,curline,_static_library_memory_operation,_static_library_memory_used,_static_library_memory_active_area);
	}
	
	/* all structs full, need more memory */
	if (_static_library_memory_monitor_top==_static_library_memory_monitor_max)
	{
		_static_library_memory_monitor_max+=MEM_MONITOR_FRAG_ELEMENT;
		logmemory("Reallocating memory monitor structure to %d",_static_library_memory_monitor_max);
		mem_monitor=realloc(mem_monitor,_static_library_memory_monitor_max*sizeof(struct s_memory_monitor));
		if (!mem_monitor)
		{
			logerr("not enough memory to realloc memory monitor structure (%d elements eq %dkb) - memory in used=%dkb",_static_library_memory_monitor_max,_static_library_memory_monitor_max*sizeof(struct s_memory_monitor)/1024,_static_library_memory_used/1024);
			pthread_mutex_unlock(&mutex_memory_management);
			exit(INTERNAL_ERROR);
		}
	}
	/* init top cell struct to ZERO */
	memset(&mem_monitor[_static_library_memory_monitor_top],0,sizeof(struct s_memory_monitor));
	
	switch (memory_way)
	{
		case WAY_MALLOC:
			/* is one of the last blocks used to malloc ? */
			if (mem_monitor[last_memory_monitor_idx].ptr==NULL)
				memory_monitor_idx=last_memory_monitor_idx;
			else
			if (last_memory_monitor_idx>0 && mem_monitor[last_memory_monitor_idx-1].ptr==NULL)
				memory_monitor_idx=last_memory_monitor_idx-1;
			else
			if (last_memory_monitor_idx<_static_library_memory_monitor_top && mem_monitor[last_memory_monitor_idx+1].ptr==NULL)
				memory_monitor_idx=last_memory_monitor_idx+1;
			else
				memory_monitor_idx=_static_library_memory_monitor_top;

			/* not found the easiest way, try to get a free block in the full list */
			if (memory_monitor_idx==_static_library_memory_monitor_top)
			{
				memory_monitor_idx=0;
				while (mem_monitor[memory_monitor_idx].ptr!=NULL && memory_monitor_idx<_static_library_memory_monitor_top)
					memory_monitor_idx++;
			}
				
			if (memory_monitor_idx==_static_library_memory_monitor_top)
				_static_library_memory_monitor_top++;
			
			mem_monitor[memory_monitor_idx].ptr=ptr;
			mem_monitor[memory_monitor_idx].size=size;
			mem_monitor[memory_monitor_idx].cursource=cursource;
			mem_monitor[memory_monitor_idx].curfunc=curfunc;
			mem_monitor[memory_monitor_idx].curline=curline;
			mem_monitor[memory_monitor_idx].mem_op=_static_library_memory_operation;
			_static_library_memory_used+=size;
			_static_library_memory_aggregate+=size;
			_static_library_memory_active_area++;
			last_memory_monitor_idx=memory_monitor_idx;
			break;
		case WAY_REALLOC:
			/* is one of the last blocks used to realloc? */
			if (mem_monitor[last_memory_monitor_idx].ptr==ptr) {
				memory_monitor_idx=last_memory_monitor_idx;
			} else if (last_memory_monitor_idx>0 && mem_monitor[last_memory_monitor_idx-1].ptr==ptr) {
				memory_monitor_idx=last_memory_monitor_idx-1;
			} else if (last_memory_monitor_idx<_static_library_memory_monitor_top && mem_monitor[last_memory_monitor_idx+1].ptr==ptr) {
				memory_monitor_idx=last_memory_monitor_idx+1;
			} else {
				memory_monitor_idx=0;
				while (mem_monitor[memory_monitor_idx].ptr!=ptr && memory_monitor_idx<_static_library_memory_monitor_top)
					memory_monitor_idx++;

				if (memory_monitor_idx==_static_library_memory_monitor_top)
				{
					/* This is a direct call to put2log, specific to memory management! Do not copy this! */
					_internal_put2log("ERROR",cursource,curline,curfunc,"you cannot realloc a memory block that wasn't previously alloc!");
					pthread_mutex_unlock(&mutex_memory_management);
					exit(INTERNAL_ERROR);
				}
			}
			/* update monitor block */
			_static_library_memory_used+=size-mem_monitor[memory_monitor_idx].size;
			_static_library_memory_aggregate+=size;
			
			mem_monitor[memory_monitor_idx].ptr=newptr;
			mem_monitor[memory_monitor_idx].size=size;
			mem_monitor[memory_monitor_idx].cursource=cursource;
			mem_monitor[memory_monitor_idx].curfunc=curfunc;
			mem_monitor[memory_monitor_idx].curline=curline;
			mem_monitor[memory_monitor_idx].mem_op=_static_library_memory_operation;
			last_memory_monitor_idx=memory_monitor_idx;
			break;
		case WAY_FREE:
			/* is one of the last blocks used to free? */
			if (mem_monitor[last_memory_monitor_idx].ptr==ptr) {
				memory_monitor_idx=last_memory_monitor_idx;
			} else if (last_memory_monitor_idx>0 && mem_monitor[last_memory_monitor_idx-1].ptr==ptr) {
				memory_monitor_idx=last_memory_monitor_idx-1;
			} else if (last_memory_monitor_idx<_static_library_memory_monitor_top && mem_monitor[last_memory_monitor_idx+1].ptr==ptr) {
				memory_monitor_idx=last_memory_monitor_idx+1;
			} else {
				memory_monitor_idx=0;
				while (mem_monitor[memory_monitor_idx].ptr!=ptr && memory_monitor_idx<_static_library_memory_monitor_top)
					memory_monitor_idx++;

				if (memory_monitor_idx==_static_library_memory_monitor_top)
				{
					/* This is a direct call to put2log, specific to memory management! Do not copy this! */
					_internal_put2log("ERROR",cursource,curline,curfunc,"you cannot free a memory block that wasn't previously alloc!");
					pthread_mutex_unlock(&mutex_memory_management);
					exit(INTERNAL_ERROR);
				}
			}
			_static_library_memory_used-=mem_monitor[memory_monitor_idx].size;
			_static_library_memory_active_area--;
			/* reset monitor block */
			memset(&mem_monitor[memory_monitor_idx],0,sizeof(struct s_memory_monitor));
			/* keep this id for next alloc */
			last_memory_monitor_idx=memory_monitor_idx;
			break;
		default:
			logerr("Unknown memory_way method! This should not happened!");
			pthread_mutex_unlock(&mutex_memory_management);
			exit(INTERNAL_ERROR);
	}
	/* add checksum control to structures */
	switch (memory_way)
	{
		case WAY_MALLOC:
			newptr=ptr;
		case WAY_REALLOC:
			realptr=(char*)newptr-sizeof(struct s_memory_check_header);
			mem_header=(struct s_memory_check_header *)realptr;
			mem_footer=(struct s_memory_check_footer *)((char*)newptr+size);
			for (i=0;i<MEM_CHECK_FILLER_SIZE;i++)
			{
				mem_header->filler[i]=0xA5;
				mem_footer->filler[i]=0x5A;
			}
			for (i=0;i<4;i++)
			{
				mem_header->checksum[i]=(unsigned long)realptr*(i+1);
				mem_footer->checksum[i]=(unsigned long)realptr*(i+1);
			}
		default:break;
	}
	if (_static_library_memory_used>_static_library_memory_used_max)
		_static_library_memory_used_max=_static_library_memory_used;

}
#endif


/***
	Memory management functions
	- Check NULL pointer
	- Display usefull debug informations when things go wrong
	
	Warning: log messages use direct call to put2log, this is
	specific to memory management because we need to know which
	function calls the memory function! Do not copy this behaviour!

	MemRealloc(ptr,size) like realloc
	MemMalloc(size)      like malloc
	MemCalloc(size)      like calloc
	MemFree(ptr)         like free
	MemCheck()           check memory allocations for overriding bugs
	
	You do not have to check returned pointer. If things go wrong
	the program will be halted and display an error message

*/

/***
	_internal_MemFree
	internal use, do not call this function
	please use the macro MemFree(ptr)

*/
void _internal_MemFree(void *ptr, char *cursource,int curline, char *curfunc)
{
#ifdef FAST_LIBRARY
	tc_free(ptr);
#else
	if (!ptr)
	{
		/* This is a direct call to put2log, specific to memory management! Do not copy this! */
		_internal_put2log("ERROR",cursource,curline,curfunc,"cannot free NULL pointer");
		exit(INTERNAL_ERROR);
	}
	/* multi-thread compliant */
	_MemCheck(DEBUG_MODE,cursource,curline,curfunc);
	pthread_mutex_lock(&mutex_memory_management);
	_MemMonitor(ptr,NULL,0,cursource,curline,curfunc,WAY_FREE);
	pthread_mutex_unlock(&mutex_memory_management);
	free((char*)ptr-sizeof(struct s_memory_check_header));
#endif
}

/***
	_internal_MemRealloc
	internal use, do not call this function
	please use the macro MemRealloc(ptr,size)

*/
void *_internal_MemRealloc(void *ptr, int size, char *cursource,int curline, char *curfunc)
{
	struct s_memory_check_header *mem_header;
	struct s_memory_check_footer *mem_footer;
	char *newptr,*realptr;
	int realsize;
	int i;
#ifdef RDDUSED
	static int tic=100;
if (tic==100) {tic=0;printf("%dk used        \r",_static_library_memory_used/1024);fflush(stdout);} else tic++;
#endif

#ifdef FAST_LIBRARY
	return tc_realloc(ptr,size);
#else
	/* realloc of size 0, we must free and quit */
	if (size==0 && ptr!=NULL)
	{
		_internal_MemFree(ptr,cursource,curline,curfunc);
		return NULL;
	}
	/* if debug mode enabled, perform a full check every operations */
	//_MemCheck(DEBUG_MODE,cursource,curline,curfunc);

	/* we malloc more than requested, to store memory check structures */
	realsize=size+sizeof(struct s_memory_check_header)+sizeof(struct s_memory_check_footer);

	/* multi-thread compliant */
	pthread_mutex_lock(&mutex_memory_management);

	/* more compliant because on posix system, realloc can do his job on an input NULL pointer */
	if (ptr!=NULL)
	{
		int memchkidx=0;
		while (mem_monitor[memchkidx].ptr!=ptr && memchkidx<_static_library_memory_monitor_top)
			memchkidx++;
		if (memchkidx==_static_library_memory_monitor_top)
		{
			/* This is a direct call to put2log, specific to memory management! Do not copy this! */
			_internal_put2log("ERROR",cursource,curline,curfunc,"you cannot realloc a memory block that wasn't previously alloc!");
			exit(INTERNAL_ERROR);
		}
		realptr=realloc((char*)ptr-sizeof(struct s_memory_check_header),realsize);
	}
	else
		realptr=malloc(realsize);
		
	if (!realptr)
	{
		/* This is a direct call to put2log, specific to memory management! Do not copy this! */
		_internal_put2log("ERROR",cursource,curline,curfunc,"not enough memory to allocate %d byte%s (operation %d cumul %d)",size,(size>1)?"s":"",_static_library_memory_operation,_static_library_memory_aggregate);
		exit(ABORT_ERROR);
	}
	
	newptr=realptr+sizeof(struct s_memory_check_header);
	
	if (ptr==NULL)
		_MemMonitor(newptr,NULL,size,cursource,curline,curfunc,WAY_MALLOC);
	else
		_MemMonitor(ptr,newptr,size,cursource,curline,curfunc,WAY_REALLOC);
	pthread_mutex_unlock(&mutex_memory_management);
		
	return newptr;
#endif
}
/***
	_MemCalloc
	internal use, do not call this function
	please use the macro MemCalloc(size)

*/
void *_MemCalloc(int size, char *cursource,int curline, char *curfunc)
{
	char *newptr;
	
	newptr=_internal_MemRealloc(NULL,size,cursource,curline,curfunc);
	memset(newptr,0,size);
	return newptr;
}

/***
 *	MemCpy / MemSet
 *
 *	secure memcpy/memset check for allocated area
 *
 */
int _internal_MemCheckArea(char *memfunc, int i, size_t num, char *ptr, char *cursource,int curline, char *curfunc)
{
	#undef FUNC
	#define FUNC "MemCpyCheck"

	if (mem_monitor[i].ptr==ptr) {
		if (num<=mem_monitor[i].size) {
			return 1;
		} else {
			_internal_put2log("ERROR",cursource,curline,curfunc,"%s overflow of %d byte%s",memfunc,num-mem_monitor[i].size,(num-mem_monitor[i].size>1)?"s":"");
			pthread_mutex_unlock(&mutex_memory_management);
			exit(INTERNAL_ERROR);
		}		
	} else if (mem_monitor[i].ptr<ptr && (unsigned long)(ptr-mem_monitor[i].ptr)<=mem_monitor[i].size) {
		if (num<=mem_monitor[i].size-(unsigned long)ptr+(unsigned long)mem_monitor[i].ptr) {
			return 1;
		} else {
			_internal_put2log("ERROR",cursource,curline,curfunc,"%s clipped overflow of %d byte%s",memfunc,num-mem_monitor[i].size+(unsigned long)ptr-(unsigned long)mem_monitor[i].ptr,(num-(mem_monitor[i].size+(unsigned long)ptr-(unsigned long)mem_monitor[i].ptr))>1?"s":"");
			pthread_mutex_unlock(&mutex_memory_management);
			exit(INTERNAL_ERROR);
		}		
	}
	return 0;
}
void * _internal_MemCpy(void *destination, const void *source, size_t num, char *cursource,int curline, char *curfunc)
{
	#undef FUNC
	#define FUNC "MemCpy"

#ifndef FAST_LIBRARY
	int i,ok=0;
	pthread_mutex_lock(&mutex_memory_management);
	for (i=0;i<_static_library_memory_monitor_top && ok!=3;i++) {
		if (!(ok&1) && _internal_MemCheckArea("MemCpy (source)",i,num,(char*)source,cursource,curline,curfunc)) ok|=1;
		if (!(ok&2) && _internal_MemCheckArea("MemCpy (destination)",i,num,(char*)destination,cursource,curline,curfunc)) ok|=2;
	}
	pthread_mutex_unlock(&mutex_memory_management);
	if ((destination<source && (char*)destination+num>(char*)source) || (source<destination && (char*)source+num>(char*)destination)) {
		_internal_put2log("ERROR",cursource,curline,curfunc,"MemCpy has source and destination overriding, since behaviour cannot be guaranted, use two different memory areas, or use MemMove");
		exit(INTERNAL_ERROR);
	}
#endif
	return memcpy(destination,source,num);
}
void *_internal_MemSet(void *destination, int filler, size_t num, char *cursource,int curline, char *curfunc)
{
	#undef FUNC
	#define FUNC "MemSet"

#ifndef FAST_LIBRARY
	int i,ok=0;
	pthread_mutex_lock(&mutex_memory_management);
	for (i=0;i<_static_library_memory_monitor_top && !ok;i++) {
		if (_internal_MemCheckArea("MemSet",i,num,(char*)destination,cursource,curline,curfunc)) ok=1;
	}
	pthread_mutex_unlock(&mutex_memory_management);
#endif
	return memset(destination,filler,num);
}
void *_internal_MemMove(void *destination, void *source, size_t num, char *cursource, int curline, char *curfunc)
{
	#undef FUNC
	#define FUNC "MemMove"

#ifndef FAST_LIBRARY
	int i,ok=0;
	pthread_mutex_lock(&mutex_memory_management);
	for (i=0;i<_static_library_memory_monitor_top && ok!=3;i++) {
		if (!(ok&1) && _internal_MemCheckArea("MemMove (source)",i,num,(char*)source,cursource,curline,curfunc)) ok|=1;
		if (!(ok&2) && _internal_MemCheckArea("MemMove (destination)",i,num,(char*)destination,cursource,curline,curfunc)) ok|=2;
	}
	pthread_mutex_unlock(&mutex_memory_management);
#endif
	return memmove(destination,source,num);
}

/*** Exported memory management prototypes */

/*** no memory trick functions */
#if LIBRARY_NO_MEMORY_WRAPPER==1
#define MemRealloc(ptr,size) realloc(ptr,size)
#define MemMalloc(size) malloc(size)
#define MemCalloc(size) calloc(size,1)
#define MemFree(ptr) free(ptr)
#define MemCheck() while (0)
#define MemCpy(dst,src,size) memcpy(dst,src,size)
#define MemSet(dst,filler,size) memset(dst,filler,size)
#define MemMove(dst,src,size) memmove(dst,src,size)
#else
/*** patched memory functions */
#define MemRealloc(ptr,size) _internal_MemRealloc(ptr,size,__FILENAME__,__LINE__,FUNC)
#define MemMalloc(size) _internal_MemRealloc(NULL,size,__FILENAME__,__LINE__,FUNC)
#define MemCalloc(size) _MemCalloc(size,__FILENAME__,__LINE__,FUNC)
#define MemFree(ptr) _internal_MemFree(ptr,__FILENAME__,__LINE__,FUNC)
#define MemCheck() _MemCheck(1,__FILENAME__,__LINE__,FUNC)
#define MemCpy(dst,src,size) _internal_MemCpy(dst,src,size,__FILENAME__,__LINE__,FUNC)
#define MemSet(dst,filler,size) _internal_MemSet(dst,filler,size,__FILENAME__,__LINE__,FUNC)
#define MemMove(dst,src,size) _internal_MemMove(dst,src,size,__FILENAME__,__LINE__,FUNC)
#endif

/***
	void *MemDuplicate

*/
void *_internal_MemDuplicate(void *source, size_t num, int direct, char *cursource,int curline, char *curfunc)
{
	#undef FUNC
	#define FUNC "MemDuplicate"

	unsigned char *newmem;

	newmem=MemMalloc(num);
	if (direct) {
		memcpy(newmem,source,num);
	} else {
		_internal_MemCpy(newmem,source,num,cursource,curline,curfunc);
	}
	return newmem;
}
#if LIBRARY_NO_MEMORY_WRAPPER==1
#define MemDuplicate(source,num) _internal_MemDuplicate(source,num,1,__FILENAME__,__LINE__,FUNC)
#else
#define MemDuplicate(source,num) _internal_MemDuplicate(source,num,0,__FILENAME__,__LINE__,FUNC)
#endif



/***
	MemTrace
	_internal_MemTrace
	
	store a trace order in the global structure
	input: ptr, size
	
	then <size> bytes will be monitored for change at <ptr> adress
	an optionnal end parameter with the macro can define a monitor name (with arguments to include some counters)
*/
void _internal_MemTrace(char *cursource,int curline, char *curfunc,char *ptr,int size,...)
{
	#undef FUNC
	#define FUNC "MemTrace"

#ifndef FAST_LIBRARY
	struct s_memory_trace *newtrace,*curtrace;
	char *memtracename;
	int i,ok=0,zelen;
	char *zename;
	
	va_list argptr;
	va_start(argptr,size);
	zename=va_arg(argptr,char *);
	if (zename!=NULL)
	{
		zelen=vsnprintf(NULL,0,zename,argptr)+1;
		va_end(argptr);
		memtracename=MemMalloc(zelen);
		va_start(argptr,size);
		zename=va_arg(argptr,char *);
		vsprintf(memtracename,zename,argptr);
	}		
	else
		memtracename=TxtStrDup("");
	va_end(argptr);

	logmemory("monitoring %lX:%d",ptr,size);
	for (i=0;i<_static_library_memory_monitor_top && !ok;i++)
	{
		if (mem_monitor[i].ptr!=NULL)
		{
			if (ptr>=mem_monitor[i].ptr && ptr<mem_monitor[i].ptr+mem_monitor[i].size)
				ok=1;
		}
	}
	if (!ok)
	{
		_internal_put2log("ERROR ",cursource,curline,curfunc,"You cannot monitor an area that was not previously allocated");
		exit(INTERNAL_ERROR);
	}	
	
	newtrace=MemCalloc(sizeof(struct s_memory_trace));
	newtrace->name=memtracename;
	newtrace->ptr=ptr;
	newtrace->size=size;
	newtrace->backup=MemMalloc(size);
	memcpy(newtrace->backup,ptr,size);
	newtrace->active=1;
	
	curtrace=memory_trace_ROOT;
	if (curtrace!=NULL)
	{
		/* check for duplicate name */
		if (strlen(newtrace->name))
		{
			if (!strcmp(curtrace->name,newtrace->name))
			{
				_internal_put2log("ERROR ",cursource,curline,curfunc,"You cannot use the same monitor name twice or more [%s]",newtrace->name);
				exit(INTERNAL_ERROR);
			}			
		}
		
		while (curtrace->next!=NULL)
			curtrace=curtrace->next;
		curtrace->next=newtrace;
	}
	else
		memory_trace_ROOT=newtrace;
#endif
}

/***
	MemUntrace
	_internal_MemUntrace
	
	remove a trace order from the global structure
	input: ptr
	the <ptr> adress wont be monitored anymore
	an optionnal end parameter with the macro can define a monitor name (with arguments to include some counters)
*/
void _internal_MemUntrace(char *cursource,int curline, char *curfunc, void *ptr,...)
{
	#undef FUNC
	#define FUNC "MemUntrace"

#ifndef FAST_LIBRARY	
	struct s_memory_trace *zetrace,*curtrace,*seektrace;
	char *zename,*memtracename;
	int zelen;
	va_list argptr;

	va_start(argptr,ptr);
	zename=va_arg(argptr,char *);
	if (ptr==NULL && zename!=NULL)
	{
		zelen=vsnprintf(NULL,0,zename,argptr)+1;
		va_end(argptr);
		memtracename=MemMalloc(zelen);
		va_start(argptr,ptr);
		zename=va_arg(argptr,char *);
		vsprintf(memtracename,zename,argptr);
		zename=memtracename;
		logmemory("unmonitoring %X:%s",ptr,zename);
	}
	else
	{
		zename=NULL;
		logmemory("unmonitoring %X",ptr);
	}
	va_end(argptr);
	
	curtrace=memory_trace_ROOT;
	if (curtrace!=NULL)
	{
		if (ptr!=NULL)
		{
			while (curtrace!=NULL && curtrace->ptr!=ptr)
			{
				curtrace=curtrace->next;
			}
		}
		else
		if (zename!=NULL)
		{
			while (curtrace!=NULL && strcmp(curtrace->name,zename))
			{
				curtrace=curtrace->next;
			}
		}
		else
		{
			_internal_put2log("ERROR ",cursource,curline,curfunc,"You must specify a pointer or a name to remove the trace...");
			exit(INTERNAL_ERROR);
		}		
		
		if (!curtrace)
		{
			_internal_put2log("ERROR ",cursource,curline,curfunc,"trace %8X not found! Exiting",ptr);
			exit(INTERNAL_ERROR);
		}
	}
	else
	{
		_internal_put2log("ERROR ",cursource,curline,curfunc,"There is no trace to remove! Exiting");
		exit(INTERNAL_ERROR);
	}
	
	if (curtrace==memory_trace_ROOT)
	{
		memory_trace_ROOT=curtrace->next;
	}
	else
	{
		zetrace=memory_trace_ROOT;
		while (zetrace->next!=curtrace)
			zetrace=zetrace->next;
		zetrace->next=curtrace->next;
	}
	if (zename)
		MemFree(zename);
	MemFree(curtrace->name);
	MemFree(curtrace->backup);
	MemFree(curtrace);
#endif
}


pthread_t *g_threads=NULL;
int g_nb_threads=0;

void _internal_PushThread(pthread_t thread)
{
	#undef FUNC
	#define FUNC "_internal_PushThread"

	g_threads=MemRealloc(g_threads,(g_nb_threads+1)*sizeof(pthread_t));
	g_threads[g_nb_threads++]=thread;
}

void _internal_WaitForThreads()
{
	#undef FUNC
	#define FUNC "_internal_WaitForThreads"

	void *status;
	int rc;

	while (g_nb_threads) {
		g_nb_threads--;
		if ((rc=pthread_join(g_threads[g_nb_threads],&status))) {
			logerr("thread join error!");
			exit(INTERNAL_ERROR);
		}
	}
	if (g_threads)
		MemFree(g_threads);
}
#define ExecuteSysCmdWaitForThreads _internal_WaitForThreads


unsigned int TxtGetCRC(char *zestring)
{
	unsigned int Lcrc=0x990951BA;

	while (*zestring) {
		Lcrc=Lcrc<<6^(Lcrc>>26)^*zestring+*zestring; /* petit CRC simple avec re-injection */
		zestring++;
	}
	return Lcrc;
}
unsigned int BinaryGetCRC(char *zedata, int datalen)
{
	unsigned int Lcrc=0x990951BA;

	while (datalen) {
		Lcrc=Lcrc<<6^(Lcrc>>26)^*zedata+*zedata; /* petit CRC simple avec re-injection */
		zedata++;
		datalen--;
	}
	return Lcrc;
}

/***
 *	MemoryCrunc / MemoryDecrunch
 *
 *	fast compression using LZ4 from Yann Colet under New BSD Licence
 *
 */
#ifndef RDD
int _internal_MemoryCrunch(unsigned char *AMemIn, unsigned char **AMemOut, int ASize, int compression_max)
{
	#undef FUNC
	#define FUNC "MemoryCrunch"

	int LCompressedSize=0;
	static unsigned char *LSBufCompress=NULL;
	static int LSBufSize=0;

	if (!AMemIn) {
		if (LSBufCompress && LSBufSize) MemFree(LSBufCompress);
		LSBufCompress=NULL;
		LSBufSize=0;
		return 0;
	}

	/* reallocation only if needed */
	if (!LSBufCompress || LSBufSize<LZ4_compressBound(ASize)+sizeof(int)) {
		LSBufSize=LZ4_compressBound(ASize)+sizeof(int);
		LSBufCompress=MemRealloc(LSBufCompress,LSBufSize); /* worst compression case */
	}

	*((int*)LSBufCompress)=ASize;
	if (compression_max) {
		LCompressedSize=LZ4_compressHC(AMemIn,LSBufCompress+sizeof(int),ASize);
	} else {
		LCompressedSize=LZ4_compress(AMemIn,LSBufCompress+sizeof(int),ASize);
	}
	*AMemOut=LSBufCompress;
	return LCompressedSize+sizeof(int);
}
#define MemoryCrunch(AMemIn,AMemOut,ASize) _internal_MemoryCrunch(AMemIn,AMemOut,ASize,0)
#define MemoryCrunchMax(AMemIn,AMemOut,ASize) _internal_MemoryCrunch(AMemIn,AMemOut,ASize,1)
int MemoryDecrunch(unsigned char *AMemIn, unsigned char **AMemOut)
{
	#undef FUNC
	#define FUNC "MemoryDecrunch"

	int LSize=0;
	unsigned char *LMemOut=NULL;

	LSize=*((int*)AMemIn);

	if (*AMemOut==NULL) {
		LMemOut=MemMalloc(LSize);
	} else {
		LMemOut=*AMemOut;
	}
	if (LZ4_uncompress(AMemIn+sizeof(int),LMemOut,LSize)<0) {
		logerr("invalid compressed data!");
		exit(ABORT_ERROR);
	}
	*AMemOut=LMemOut;
	return LSize;
}
/***
 *	Hash table functions
 *
 */

struct s_hash_cell
{
	char *key;
	int keylen;
	char *data;
	int datalen;
};
struct s_hash_tree
{
	struct s_hash_tree *low_part;
	struct s_hash_tree *high_part;
	struct s_hash_tree *parent;
	struct s_hash_cell *cell;
	int nb_cell,max_cell;
};
struct s_hash_table
{
	int max_elem;
	int nb_elem;
	long memory_used;
	long memory_max;
	struct s_hash_tree *root;
};

void _internal_HashFreeTreeRecurse(struct s_hash_tree *ht)
{
	#undef FUNC
	#define FUNC "_internal_HashFreeTreeRecurse"

	int i=0;
	while (i<ht->nb_cell) {
		MemFree(ht->cell[i].key);
		MemFree(ht->cell[i].data);
		i++;
	}
	if (ht->cell) MemFree(ht->cell);
	if (ht->low_part) _internal_HashFreeTreeRecurse(ht->low_part);
	if (ht->high_part) _internal_HashFreeTreeRecurse(ht->high_part);
	MemFree(ht);
}

void *_internal_HashFlushThread(void *zeroot)
{
	#undef FUNC
	#define FUNC "_internal_HashFlushThread"

	_internal_HashFreeTreeRecurse((struct s_hash_tree *)zeroot);
	pthread_exit(NULL);
#ifdef OS_WIN
	return NULL;
#endif
}
void HashFlush(struct s_hash_table *htab)
{
	#undef FUNC
	#define FUNC "HashFlush"

	pthread_t thread;
	pthread_attr_t attr;
	int rc;

	if (!htab->root) return;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	pthread_attr_setstacksize(&attr,65536);
	if ((rc=pthread_create(&thread,&attr,_internal_HashFlushThread,(void *)htab->root))) {
		logerr("Cannot create thread!");
		exit(INTERNAL_ERROR);
	}
	_internal_PushThread(thread);

	htab->root=NULL;
	htab->nb_elem=0;
	htab->memory_used=0;
}

void HashFree(struct s_hash_table *htab)
{
	#undef FUNC
	#define FUNC "HashFree"

	HashFlush(htab);
	MemFree(htab);	
}

#define TREE_FOLLOW 0
#define TREE_MALLOC 1

struct s_hash_tree *_internal_HashGetTree(struct s_hash_table *htab, unsigned char *zekey, int zelen, int create_branch)
{
	#undef FUNC
	#define FUNC "_internal_HashGetTree"

	struct s_hash_tree *ht;
	int found=0;
	unsigned int target;
	unsigned int curbit,mask;

	target=BinaryGetCRC(zekey,zelen);

	if (!htab->root) {
		htab->root=MemCalloc(sizeof(struct s_hash_tree));
	}
	ht=htab->root;

	/* follow the tree and create cells if necessary */
	mask=1;
	while (mask) {
		curbit=target&mask;
		mask+=mask;
		if (!curbit) {
			if (!ht->low_part) {
				if (!create_branch) return NULL;
				ht->low_part=MemCalloc(sizeof(struct s_hash_tree));
				ht->low_part->parent=ht;
			}
			ht=ht->low_part;
		} else {
			if (!ht->high_part) {
				if (!create_branch) return NULL;
				ht->high_part=MemCalloc(sizeof(struct s_hash_tree));
				ht->high_part->parent=ht;
			}
			ht=ht->high_part;
		}
	}

	return ht;
}

int HashRemoveData(struct s_hash_table *htab, char *zekey, int keylen)
{
	#undef FUNC
	#define FUNC "HashRemoveData"

	struct s_hash_tree *ht,*parent;
	struct s_hash_cell cell;
	int i=0,found=0;

	ht=_internal_HashGetTree(htab,zekey,keylen,TREE_FOLLOW);
	if (!ht) return 0;
	/* remove the data */
	while (i<ht->nb_cell) {
		if (keylen==ht->cell[i].keylen && memcmp(zekey,ht->cell[i].key,keylen)) {
			ht->nb_cell--;
			MemFree(ht->cell[i].key);
			MemFree(ht->cell[i].data);
			ht->cell[i]=ht->cell[ht->nb_cell];
			found=1;
			break;
		}
		i++;
	}
	/* clean the tree */
	while (!ht->nb_cell) {
		if (ht->cell) MemFree(ht->cell);
		parent=ht->parent;
		if (parent!=NULL && !parent->low_part && !parent->high_part) {
			MemFree(ht);
			if (parent->low_part==ht) parent->low_part=NULL;
			else if (parent->high_part==ht) parent->high_part=NULL;
			ht=parent;
		}
	}
	return found;
}

void _internal_HashPutData(struct s_hash_table *htab, char *zekey, int keylen, char *zedata, int datalen, int crunch)
{
	#undef FUNC
	#define FUNC "HashPutData"

	struct s_hash_tree *ht;
	struct s_hash_cell cell;
	int i=0;

	if (htab->memory_max) {
		if (htab->memory_used>htab->memory_max) {
			HashFlush(htab);
		}
	}

	ht=_internal_HashGetTree(htab,zekey,keylen,TREE_MALLOC);
	while (i<ht->nb_cell) {
		if (keylen==ht->cell[i].keylen && memcmp(zekey,ht->cell[i].key,keylen)) {
			htab->memory_used+=datalen-ht->cell[i].datalen;
			ht->cell[i].datalen=datalen;
			if (crunch) {
				datalen=MemoryCrunch(zedata,(unsigned char **)&zedata,datalen);
			}
			ht->cell[i].data=MemRealloc(ht->cell[i].data,datalen);
			memcpy(ht->cell[i].data,zedata,datalen);
			return;
		}
		i++;
	}
	cell.keylen=keylen;
	cell.key=MemMalloc(keylen);
	memcpy(cell.key,zekey,keylen);
	cell.datalen=datalen;
	if (crunch) {
		datalen=MemoryCrunch(zedata,(unsigned char **)&zedata,datalen);
	}
	cell.data=MemMalloc(datalen);
	memcpy(cell.data,zedata,datalen);
	ObjectArrayAddDynamicValueConcat((void **)&ht->cell,&ht->nb_cell,&ht->max_cell,&cell,sizeof(cell));
	htab->nb_elem++;
	htab->memory_used+=keylen+datalen+sizeof(struct s_hash_tree)*20+sizeof(struct s_hash_cell);
}

int _internal_HashGetData(struct s_hash_table *htab, char *zekey, int keylen, char **zedata, int *datalen, int crunch)
{
	#undef FUNC
	#define FUNC "HashGetData"

	char *decrunched_buffer=NULL;
	struct s_hash_tree *ht;
	int i=0,tmplen;

	/* with strings, we do not need to return len */
	if (!datalen) datalen=&tmplen;

	ht=_internal_HashGetTree(htab,zekey,keylen,TREE_FOLLOW);
	if (ht) {
		while (i<ht->nb_cell) {
			if (keylen==ht->cell[i].keylen && !memcmp(zekey,ht->cell[i].key,keylen)) {
				if (crunch) {
					*datalen=MemoryDecrunch(ht->cell[i].data,(unsigned char **)&decrunched_buffer);
					*zedata=decrunched_buffer;
				} else {
					*datalen=ht->cell[i].datalen;
					*zedata=MemMalloc(*datalen);
					memcpy(*zedata,ht->cell[i].data,*datalen);
				}
				return 1;
			}
			i++;
		}
	}
	*datalen=-1;
	*zedata=NULL;
	return 0;
}
#define HashPutData(htab,zekey,keylen,zedata,datalen) _internal_HashPutData(htab,zekey,keylen,zedata,datalen,0)
#define HashGetData(htab,zekey,keylen,zedata,datalen) _internal_HashGetData(htab,zekey,keylen,zedata,datalen,0)
#define HashPutDataCrunched(htab,zekey,keylen,zedata,datalen) _internal_HashPutData(htab,zekey,keylen,zedata,datalen,1)
#define HashGetDataCrunched(htab,zekey,keylen,zedata,datalen) _internal_HashGetData(htab,zekey,keylen,zedata,datalen,1)

#define HashPutString(htab,zekey,keylen,zedata) _internal_HashPutData(htab,zekey,keylen,zedata,strlen(zedata)+1,0)
#define HashGetString(htab,zekey,keylen,zedata) _internal_HashGetData(htab,zekey,keylen,zedata,NULL,0)
#define HashPutStringCrunched(htab,zekey,keylen,zedata) _internal_HashPutData(htab,zekey,keylen,zedata,strlen(zedata)+1,1)
#define HashGetStringCrunched(htab,zekey,keylen,zedata) _internal_HashGetData(htab,zekey,keylen,zedata,NULL,1)
#endif




/***
 *	Timing functions
 *
 *	ChronoStart
 *	ChronoStop
 *
 *	return a time in nanoseconds
 *
 */
#define CLOCK_NANO  (1000000000L)

/*********************************
	Time functions for Windows
*********************************/
#ifdef OS_WIN

LARGE_INTEGER g_clockfrequency;
LARGE_INTEGER g_lastclock;

int ChronoStart()
{
	#undef FUNC
	#define FUNC "ChronoStart"
	static int chrono_init=1;
	
	if (chrono_init) {
		QueryPerformanceFrequency(&g_clockfrequency);
		if (g_clockfrequency.QuadPart==0) {
			logerr("QueryPerformanceFrequency (CLOCK_REALTIME) error (no resolution)");
			return 0;
		}
	}
	QueryPerformanceCounter(&g_lastclock);
	return 1;
}
long ChronoStop()
{
	#undef FUNC
	#define FUNC "ChronoStop / ChronoGetIntermediate"

	LARGE_INTEGER clockend={0};
	unsigned long ret=0;

	QueryPerformanceCounter(&clockend);
	ret=(clockend.QuadPart-g_lastclock.QuadPart)*1000000000.0/g_clockfrequency.QuadPart;
	return ret;
}
unsigned long ChronoGetSecond()
{
	#undef FUNC
	#define FUNC "ChronoGetSecond"

	LARGE_INTEGER clockend={0};
	QueryPerformanceCounter(&clockend);
	return clockend.QuadPart/g_clockfrequency.QuadPart;
}
unsigned long ChronoGetMilliSecond()
{
	#undef FUNC
	#define FUNC "ChronoGetMilliSecond"

	LARGE_INTEGER clockend={0};
	QueryPerformanceCounter(&clockend);
	return clockend.QuadPart*1000.0/g_clockfrequency.QuadPart;
}
void NanoSleep(double nanotime)
{
	#undef FUNC
	#define FUNC "NanoSleep (not accurate)"

	Sleep(nanotime/1000000.0);
}

#else

/********************************
	Time functions for Linux
********************************/
 
static struct timespec g_clockinfo={0};
int ChronoStart()
{
	#undef FUNC
	#define FUNC "ChronoStart"
	static int chrono_init=1;

	if (chrono_init) {
		if (clock_getres(CLOCK_REALTIME,&g_clockinfo)) {
			logerr("CLOCK_REALTIME error (no resolution)");
			return 0;
		} else {
			if (g_clockinfo.tv_sec!=0 && g_clockinfo.tv_nsec!=1) {
				logwarn("CLOCK_REALTIME is not accurate");
				return 0;
			} else {
				chrono_init=0;
			}
		}
	}
	clock_gettime(CLOCK_REALTIME,&g_clockinfo);
	return 1;
}
unsigned long ChronoStop()
{
	#undef FUNC
	#define FUNC "ChronoStop / ChronoGetIntermediate"

	struct timespec clockend={0};
	unsigned long ret=0;
	long diffnano=0,diffsec=0;

	if (clock_gettime(CLOCK_REALTIME,&clockend)==0) {
		diffnano=clockend.tv_nsec-g_clockinfo.tv_nsec;
		diffsec=clockend.tv_sec-g_clockinfo.tv_sec;
		if (diffnano<0) {
			ret=CLOCK_NANO+diffnano+(diffsec-1)*CLOCK_NANO;
		} else {
			ret=diffnano+diffsec*CLOCK_NANO;
		}
	}
	return ret;
}
#define ChronoGetIntermediate ChronoStop
unsigned long ChronoGetSecond()
{
	#undef FUNC
	#define FUNC "ChronoGetSecond"

	struct timespec clockend={0};
	if (clock_gettime(CLOCK_REALTIME,&clockend)==0) {
		return clockend.tv_sec;
	} else {
		return 0;
	}
}
unsigned long ChronoGetMilliSecond()
{
	#undef FUNC
	#define FUNC "ChronoGetMilliSecond"

	struct timespec clockend={0};
	if (clock_gettime(CLOCK_REALTIME,&clockend)==0) {
		return (unsigned long)clockend.tv_sec*1000L+clockend.tv_nsec/1000000L;
	} else {
		return 0;
	}
}
unsigned long ChronoGetMicroSecond()
{
	#undef FUNC
	#define FUNC "ChronoGetMicroSecond"

	struct timespec clockend={0};
	if (clock_gettime(CLOCK_REALTIME,&clockend)==0) {
		return (unsigned long)clockend.tv_sec*1000000L+clockend.tv_nsec/1000L;
	} else {
		return 0;
	}
}
unsigned long ChronoGetNanoSecond()
{
	#undef FUNC
	#define FUNC "ChronoGetNanoSecond"

	struct timespec clockend={0};
	if (clock_gettime(CLOCK_REALTIME,&clockend)==0) {
		return (unsigned long)clockend.tv_sec*1000000000L+clockend.tv_nsec;
	} else {
		return 0;
	}
}
void NanoSleep(double nanotime)
{
	#undef FUNC
	#define FUNC "NanoSleep"

	struct timespec req;
	req.tv_sec=floor(nanotime/1000000000.0);;
	req.tv_nsec=nanotime-req.tv_sec*1000000000.0;;
	clock_nanosleep(CLOCK_REALTIME,0,&req,NULL);
}
#endif

#define ChronoGetIntermediate ChronoStop


static inline float MaxFloat(float a, float b)
{
if (a>b) return a; else return b;
}
static inline float MinFloat(float a, float b)
{
if (a<b) return a; else return b;
}

static inline double MaxDouble(double a, double b)
{
if (a>b) return a; else return b;
}
static inline double MinDouble(double a, double b)
{
if (a<b) return a; else return b;
}

static inline long MaxLong(long a, long b)
{
if (a>b) return a; else return b;
}
static inline long MinLong(long a, long b)
{
if (a<b) return a; else return b;
}

static inline unsigned long MaxULong(unsigned long a, unsigned long b)
{
if (a>b) return a; else return b;
}
static inline unsigned long MinULong(unsigned long a, unsigned long b)
{
if (a<b) return a; else return b;
}

static inline int MaxInt(int a, int b)
{
if (a>b) return a; else return b;
}
static inline int MinInt(int a, int b)
{
if (a<b) return a; else return b;
}

static inline unsigned int MaxUInt(unsigned int a, unsigned int b)
{
if (a>b) return a; else return b;
}
static inline unsigned int MinUInt(unsigned int a, unsigned int b)
{
if (a<b) return a; else return b;
}

static inline short int MaxShortInt(short int a, short int b)
{
if (a>b) return a; else return b;
}
static inline short int MinShortInt(short int a, short int b)
{
if (a<b) return a; else return b;
}

static inline unsigned short int MaxUShortInt(unsigned short int a, unsigned short int b)
{
if (a>b) return a; else return b;
}
static inline unsigned short int MinUShortInt(unsigned short int a, unsigned short int b)
{
if (a<b) return a; else return b;
}

static inline char MaxChar(char a, char b)
{
if (a>b) return a; else return b;
}
static inline char MinChar(char a, char b)
{
if (a<b) return a; else return b;
}

static inline unsigned char MaxUChar(unsigned char a, unsigned char b)
{
if (a>b) return a; else return b;
}
static inline unsigned char MinUChar(unsigned char a, unsigned char b)
{
if (a<b) return a; else return b;
}

/***
	MinMaxDouble
*/
double MinMaxDouble(double zeval, double zemin, double zemax)
{
	#undef FUNC
	#define FUNC "MinMaxDouble"

	if (zeval<zemin) return zemin;
	if (zeval>zemax) return zemax;
	return zeval;
}

/***
	MinMaxFloat
*/
float MinMaxFloat(float zeval, float zemin, float zemax)
{
	#undef FUNC
	#define FUNC "MinMaxFloat"

	if (zeval<zemin) return zemin;
	if (zeval>zemax) return zemax;
	return zeval;
}


/***
	MinMaxLong
*/
long MinMaxLong(long zeval, long zemin, long zemax)
{
	#undef FUNC
	#define FUNC "MinMaxLong"

	if (zeval<zemin) return zemin;
	if (zeval>zemax) return zemax;
	return zeval;
}


/***
	MinMaxInt
*/
int MinMaxInt(int zeval, int zemin, int zemax)
{
	#undef FUNC
	#define FUNC "MinMaxInt"

	if (zeval<zemin) return zemin;
	if (zeval>zemax) return zemax;
	return zeval;
}






/***
	KeyGetString
	
*/
char *KeyGetString(char *format, ...)
{
	#undef FUNC
	#define FUNC "KeyGetString"
	
	char buffer[PATH_MAX+1];
	va_list argptr;
	int c=0,idx=0;;
	
	va_start(argptr,format);
	vprintf(format,argptr);
	va_end(argptr);
	fflush(stdout);
	
	while (c!=0x0A && idx<PATH_MAX)
		buffer[idx++]=c=getchar();
		
	buffer[idx-1]=0;
	return TxtStrDup(buffer);
}


enum e_keychoices {
CHOICE_YES=1,
CHOICE_NO=2,
CHOICE_ALL=4,
CHOICE_QUIT=8,
};

/***
	KeyGetChoice
	
		
*/
int KeyGetChoice(int choice, char *format, ...)
{
	#undef FUNC
	#define FUNC "KeyGetYesNo"
	
	va_list argptr;
	char question[PATH_MAX]; /* big enough to put all options */
	char *buffer;
	int c=-1;
	char sep[2];
	
	if (!choice)
		return 0;
	
	va_start(argptr,format);
	vprintf(format,argptr);
	va_end(argptr);
	strcpy(sep,"");	
	strcpy(question,"(");
	if (choice & CHOICE_YES) {strcat(question,"Yes");strcpy(sep,"/");}
	if (choice & CHOICE_NO) {strcat(question,sep);strcat(question,"No");strcpy(sep,"/");}
	if (choice & CHOICE_ALL) {strcat(question,sep);strcat(question,"All");strcpy(sep,"/");}
	if (choice & CHOICE_QUIT) {strcat(question,sep);strcat(question,"Quit");strcpy(sep,"/");}
	strcat(question,")");
	
	buffer=KeyGetString("%s:",question);
	while ((stricmp(buffer,"Yes") || !(choice & CHOICE_YES))
	 && (stricmp(buffer,"No") || !(choice & CHOICE_NO))
	 && (stricmp(buffer,"All") || !(choice & CHOICE_ALL))
	 && (stricmp(buffer,"Quit") || !(choice & CHOICE_QUIT)))
	{
		MemFree(buffer);
		buffer=KeyGetString("Please enter %s:",question);
	}
	if (stricmp(buffer,"Yes")==0) c=CHOICE_YES;
	if (stricmp(buffer,"No")==0) c=CHOICE_NO;
	if (stricmp(buffer,"All")==0) c=CHOICE_ALL;
	if (stricmp(buffer,"Quit")==0) c=CHOICE_QUIT;
	MemFree(buffer);
	return c;
}


/***
	TxtIsInteger
	
	return 1 if the string is a pure integer (positive or negative)
	else return 0
*/
int TxtIsInteger(char *in_str)
{
	#undef FUNC
	#define FUNC "TxtIsInteger"
	
	int idx;
	
	if (!in_str[0])
		return 0;
	if (in_str[0]=='-' && in_str[1]==0)
		return 0;
	if (in_str[0]=='-' || (in_str[0]>='0' && in_str[0]<='9'))
	{
		idx=1;
		while (in_str[idx]>='0' && in_str[idx]<='9')
			idx++;
		if (in_str[idx]==0)
			return 1;
	}
	return 0;
}
/***
	TxtIsFloat
	TxtIsDouble
	TxtIsLongDouble
	
	return 1 if the string is a double (positive or negative)
	else return 0
	
	limits are 1.7E+308 and 1.7E-308 (long double)
*/
int _internal_TxtIsFloat(char *in_str, double mantmax, int expmax)
{
	#undef FUNC
	#define FUNC "_internal_TxtIsFloat"
	
	int idx,zepoint=0,zeexp=0;
	int valexp=0,backidx;
	char *expptr=NULL;
	double valmant,mul=10.0;
	
	if (in_str==NULL)
	{
		logerr("first parameter cannot be NULL!");
		exit(INTERNAL_ERROR);		
	}
	if (!in_str[0])
		return 0;
	if ((in_str[0]=='+' || in_str[0]=='-') && in_str[1]==0)
		return 0;
	if (in_str[0]=='+' ||in_str[0]=='-' || (in_str[0]>='0' && in_str[0]<='9'))
	{
		if (in_str[0]=='+' || in_str[0]=='-')
			idx=1;
		else
			idx=0;
		while (in_str[idx]>='0' && in_str[idx]<='9' || in_str[idx]=='.')
		{
			/* the dot must be before the exponent */
			if (in_str[idx]=='.') {if (expptr) return 0; else zepoint++;}
			else
			if (in_str[idx+1]=='E' && (in_str[idx+2]=='+' || in_str[idx+2]=='-') && (in_str[idx+3]>='0' && in_str[idx+3]<='9'))
				{expptr=&in_str[idx+3];zeexp++;idx+=3;valexp=atoi(expptr);}
			else
			if (in_str[idx+1]=='E') /* invalid exponent format */
				return 0;
			idx++;
		}
		backidx=idx;
		if (zepoint>1 || zeexp>1) return 0;
		if (valexp>expmax) return 0;
		if (valexp==expmax)
		{
			valmant=0;
			zepoint=0;
			if (in_str[0]=='-' || in_str[0]=='+') idx=1; else idx=0;
			while (in_str[idx]!='E')
			{
				if (in_str[idx]>='0' && in_str[idx]<='9' && !zepoint) valmant=valmant*mul+in_str[idx]-'0';
				else
				if (in_str[idx]=='.') zepoint++;
				else
				if (in_str[idx]>='0' && in_str[idx]<='9') {valmant=valmant+(in_str[idx]-'0')/mul;mul=mul*10.0;}
				else
				{
					logerr("Internal decoding error");
					exit(INTERNAL_ERROR);
				}				
				idx++;
			}
			if (valmant>mantmax)
				return 0;			
		}
		
		if (in_str[backidx]==0)
			return 1;
	}
	return 0;
}

/* doubles and floats have the same limits but not long doubles */
#define TxtIsFloat(in_str)      _internal_TxtIsFloat(in_str,1.0,37)
#define TxtIsDouble(in_str)     _internal_TxtIsFloat(in_str,1.0,37)
#define TxtIsLongDouble(in_str) _internal_TxtIsFloat(in_str,1.7,308)

/***
	TxtIsInvisible
	
	check for spaces and carriage returns
	
	return 1 if the text is invisible, 0 if not
*/
int TxtIsInvisible(char *in_str)
{
	#undef FUNC
	#define FUNC "TxtIsInvisible"

	int idx=0;
	
	while (in_str[idx]!=0)
	{
		if (in_str[idx]!=0x0D && in_str[idx]!=0x0A && in_str[idx]!=' ' && in_str[idx]!=0x0C)
			return 0;
		else
			idx++;
	}
	return 1;
}

/***
	TxtStrDup
	
	make a secure strdup of a string
*/
char *_internal_strdup(char *in_str,char *cursource,int curline, char *curfunc)
{
	#undef FUNC
	#define FUNC "TxtStrDup"
	
	char *out_str;
	int len;
	
	if (!in_str) return NULL;		
	len=strlen(in_str)+1;
	out_str=_internal_MemRealloc(NULL,len,cursource,curline,curfunc);
	memcpy(out_str,in_str,len);
	return out_str;
}
#define TxtStrDup(in_str) _internal_strdup(in_str,__FILENAME__,__LINE__,FUNC)

char *_internal_strduplen(char *str, int *len,char *cursource,int curline, char *curfunc)
{
        #undef FUNC
        #define FUNC "TxtStrDupLen"

        char *newstr;
        *len=strlen(str)+1;
        newstr=_internal_MemRealloc(NULL,*len,cursource,curline,curfunc);
        strcpy(newstr,str);
        return newstr;
}
#define TxtStrDupLen(in_str,len) _internal_strduplen(in_str,len,__FILENAME__,__LINE__,FUNC)


/***
	TxtSubstr copy a substring from a string to a new alloc and free string
	TxtGetSubstr copy a substring from a string to a new alloc	
	
	in_str:    reference string
	start_idx: start copy from offset start_idx
	len:       copy len characters.
	           may be relative to the end with a negative value
	           
	out:       the substring, dynamically mallocated
	
	note: in_str MUST BE previously mallocated for TxtSubstr
*/
char *TxtGetSubstr(char *in_str, int start_idx, int len)
{
	#undef FUNC
	#define FUNC "TxtGetSubstr"
	
	char *out_str;
	int sl;
	
	if (in_str==NULL)
		return NULL;

	/*logdebug("substr(\"%s\",%d,%d)",in_str,start_idx,len);*/
	
	sl=strlen(in_str);
	if (!sl || start_idx<0 || start_idx>=sl)
		return NULL;
		
	/* relative to the end */
	if (len<=0)
	{
		/*logdebug("len<=0\nlen=%d-%d-%d",sl,start_idx,len);*/
		len=sl-start_idx+len;
		/*logdebug("len=0%d",len);*/
	}
	
	if (len<0 || start_idx+len>sl)
		return NULL;

	out_str=MemMalloc(len+1);
	strncpy(out_str,in_str+start_idx,len);
	out_str[len]=0;
	/*logdebug("out_str=\"%s\"\n",out_str);*/
	return out_str;
}
char *TxtSubstr(char *in_str, int start_idx, int len)
{
	#undef FUNC
	#define FUNC "TxtSubstr"
	
	char *out_str;
	
	out_str=TxtGetSubstr(in_str,start_idx,len);
	MemFree(in_str);
	return out_str;
}

/***
	TxtReplace
	
	input:
	in_str:     string where replace will occur
	in_substr:  substring to look for
	out_substr: replace substring
	recurse:    loop until no in_substr is found
	
	note: in_str MUST BE previously mallocated if out_substr is bigger than in_substr
*/
char *TxtReplace(char *in_str, char *in_substr, char *out_substr, int recurse)
{
	#undef FUNC
	#define FUNC "TxtReplace"
	
	char *str_look,*m1,*m2;
	char *out_str;
	int i,sl,l1,l2,dif,cpt;

	if (in_str==NULL)
		return NULL;
		
	sl=strlen(in_str);
	l1=strlen(in_substr);
	/* empty string, nothing to do except return empty string */
	if (!sl || !l1)
		return in_str;
		
	l2=strlen(out_substr);
	dif=l2-l1;
	
	/*if (recurse)	
		logdebug("replace in recurse mode");
	else
		logdebug("replace in normal mode");*/
		
	/* replace string is small or equal in size, we dont realloc */
	if (dif<=0)
	{
		/* we loop while there is a replace to do */
		str_look=strstr(in_str,in_substr);
		while (str_look!=NULL)
		{
			/*logdebug(str_look);*/
			
			/* we copy the new string if his len is not null */
			if (l2)
				memcpy(str_look,out_substr,l2);
			/* only if len are different */
			if (l1!=l2)
			{
				/* we move the end of the string byte per byte
				   because memory locations overlap. This is
				   faster than memmove */
				m1=str_look+l1;
				m2=str_look+l2;
				while (*m1!=0)
				{
					*m2=*m1;
					m1++;m2++;
				}
				/* we must copy the EOL */
				*m2=*m1;
			}
			/* look for next replace */
			if (!recurse)
				str_look=strstr(str_look+l2,in_substr);
			else
				str_look=strstr(in_str,in_substr);
		}
		out_str=in_str;
	}
	else
	{
		/* we need to count each replace */
		cpt=0;
		str_look=strstr(in_str,in_substr);
		while (str_look!=NULL)
		{
			cpt++;
			str_look=strstr(str_look+l1,in_substr);
		}
		/* is there anything to do? */
		if (cpt)
		{
			/*logdebug("found!");*/
			/* we realloc to a size that will fit all replaces */
			out_str=MemRealloc(in_str,sl+1+dif*cpt);
			str_look=strstr(out_str,in_substr);
			while (str_look!=NULL && cpt)
			{
				/*logdebug("before");
				logdebug(out_str);
				logdebug(str_look);*/
				
				/* as the replace string is bigger we
				   have to move memory first from the end */
				m1=out_str+sl;
				m2=m1+dif;
				sl+=dif;
				while (m1!=str_look+l1-dif)
				{
					*m2=*m1;
					m1--;m2--;
				}
				/*logdebug("intermediate");
				logdebug(out_str);*/
				
				/* then we copy the replace string (can't be NULL in this case) */
				memcpy(str_look,out_substr,l2);
				
				/*logdebug("after");
				logdebug(out_str);
				logdebug(str_look);*/
				
				/* look for next replace */
				if (!recurse)
					str_look=strstr(str_look+l2,in_substr);
				else
					str_look=strstr(in_str,in_substr);
					
				/* to prevent from naughty overlap */
				cpt--;
			}
			if (str_look!=NULL)
			{
				logerr("overlapping replace string (%s/%s), you can't use this one!",in_substr,out_substr);
				exit(ABORT_ERROR);
			}
		}
		else
			out_str=in_str;
	}
	
	/*logdebug(out_str);*/
	return out_str;
}

/***
	TxtCleanSpecialChar
	TxtDeleteSpecialChar
	TxtReplaceSpecialChar
	_internal_TxtCleanInitTable
	_internal_TxtChangeSpecialChar
	
	clean a string from spaces, accented characters and other special chars and replace them with underscore
	delete from a string every spaces, accented chars and other special chars
*/

#define TXT_UNDEFINED_SPECIAL_CHAR 0
#define TXT_CLEAN_SPECIAL_CHAR 1
#define TXT_DELETE_SPECIAL_CHAR 2
#define TXT_REPLACE_LIST_SPECIAL_CHAR 3

int _internal_TxtCleanInitTable(int zemode, va_list argptr)
{
	#undef FUNC
	#define FUNC "_internal_TxtCleanInitTable"
	/* must be unsigned cause in_replace will be offset */
	unsigned char *in_replace,*out_replace;
	char default_char;
	int i,l1,l2;

	/* common to all methods */
	_static_library_txtcleanconvtable[0]=0;
	
	switch(zemode)
	{
		case TXT_CLEAN_SPECIAL_CHAR:default_char='_';break;
		case TXT_DELETE_SPECIAL_CHAR:default_char=0;break;
		case TXT_REPLACE_LIST_SPECIAL_CHAR:
			in_replace=va_arg(argptr,unsigned char *);
			out_replace=va_arg(argptr,unsigned char *);
			l1=strnlen(in_replace,255);
			l2=strnlen(out_replace,255);
			if (l1==255 || l2==255)
			{
				logerr("replace substring musn't be longer than 255 chars");
				exit(INTERNAL_ERROR);
			}
			if (l1!=l2)
			{
				logerr("replace substrings must be the same size (%d!=%d)",l1,l2);
				logerr("in =[%s]\nout=[%s]",in_replace,out_replace);
				exit(INTERNAL_ERROR);
			}
			if (!l1 || !l2)
			{
				logerr("replace substring musn't start with zero value");
				exit(INTERNAL_ERROR);
			}
			/* default */
			for (i=1;i<256;i++)
				_static_library_txtcleanconvtable[i]=i;
			/* user define */
			for (i=0;i<l1;i++)
				_static_library_txtcleanconvtable[in_replace[i]]=out_replace[i];
			
			return TXT_UNDEFINED_SPECIAL_CHAR;
			
		default:logerr("unsupported cleaning method");exit(INTERNAL_ERROR);
	}
	
	for (i=1;i<256;i++)
		_static_library_txtcleanconvtable[i]=default_char;
	for (i='a';i<='z';i++)
		_static_library_txtcleanconvtable[i]=i;
	for (i='A';i<='Z';i++)
		_static_library_txtcleanconvtable[i]=i;
	for (i='0';i<='9';i++)
		_static_library_txtcleanconvtable[i]=i;
	_static_library_txtcleanconvtable['.']='.';
	_static_library_txtcleanconvtable['-']='-';
	return zemode;
}

char *_internal_TxtChangeSpecialChar(char *in_str, int zemode, ...)
{
	#undef FUNC
	#define FUNC "_internal_TxtChangeSpecialChar"
	static int init=TXT_UNDEFINED_SPECIAL_CHAR;
	va_list argptr;
	char convtmp[2];
	char convrep[2];
	int i;
	
	convtmp[1]=0;
	convrep[1]=0;
	
	if (init!=zemode)
	{
		va_start(argptr,zemode);
		init=_internal_TxtCleanInitTable(zemode,argptr);
		va_end(argptr);
	}
	
	for (i=1;i<256;i++)	
	{
		if (_static_library_txtcleanconvtable[i]!=i)
		{
			convtmp[0]=i;
			convrep[0]=_static_library_txtcleanconvtable[i];
			TxtReplace(in_str,convtmp,convrep,1);
		}
	}
	return in_str;
}
#define TxtCleanSpecialChar(in_str) _internal_TxtChangeSpecialChar(in_str,TXT_CLEAN_SPECIAL_CHAR)
#define TxtDeleteSpecialChar(in_str) _internal_TxtChangeSpecialChar(in_str,TXT_DELETE_SPECIAL_CHAR)
#define TxtReplaceSpecialChar(in_str,in_replace,out_replace) _internal_TxtChangeSpecialChar(in_str,TXT_REPLACE_LIST_SPECIAL_CHAR,in_replace,out_replace)


/******** trim functions ***********/

/***
	TxtTrimEnd
	
	trim end of string
*/
char * TxtTrimEnd(char *in_str)
{
	#undef FUNC
	#define FUNC "TxtTrimEnd"

	char *curs;
	char *space=NULL;

	curs=in_str;
	/* read the string and save the first space position, unfollowed by another character */
	while (*curs) {
		//if (*curs==' ' || *curs==0x0D || *curs==0x0A || *curs=='\t') {
		/* this include tab, space, line feed, carriage return, ...*/
		if (*curs<=' ') {
			if (!space) {
				space=curs;
			}
		} else {
			space=NULL;
		}
		curs++;
	}
	if (space) {
		*space=0;
	}

	return in_str;
}

/***
	TxtTrimStart
	
	trim start of string
*/
char * TxtTrimStart(char *in_str)
{
	#undef FUNC
	#define FUNC "TxtTrimStart"

	int l=strlen(in_str);
	char *m1,*m2;
	int idx;
	
	idx=0;
	while (in_str[idx]==' ' || in_str[idx]=='\t')
		idx++;

	/* faster than memmove */	
	m1=in_str;
	m2=in_str+idx;
	while (*m2!=0)
	{
		*m1=*m2;
		m1++;m2++;
	}
	/* we must copy the EOL */
	*m1=*m2;
	
	return in_str;
}

/*** macro that replace double or more spaces by a single one */
#define TxtTrimSpace(in_str) TxtReplace(in_str, "  "," ",1)
#define TxtTrimTab(in_str) TxtReplace(in_str, "\t\t","\t",1)

/***
	TxtTrim
	char * TxtTrim(char *in_str)
	
	trim start, end of string, then multiple spaces
*/
char * TxtTrim(char *in_str)
{
	#undef FUNC
	#define FUNC "TxtTrim"
	
	TxtTrimEnd(in_str);
	TxtTrimStart(in_str);
	TxtTrimSpace(in_str);
	TxtTrimTab(in_str);
	
	return in_str;
}
/***
	TxtJustifyAlloc
	void TxtJustifyAlloc(char **in_str, int maxlen) {

	in_str: pointer to allocated string (may be reallocated)
	out_str: length of destination string

*/
void TxtJustifyAlloc(char **in_str, int maxlen) {
        #undef FUNC
        #define FUNC "TxtJustifyAlloc"
        char *Lout_str=NULL;
        int idx=0,jdx=0,s=0,i=0,cw=1;
        /* new spaces */
        float ns=0;
        int distri=0;

        Lout_str=MemMalloc(maxlen+1);

        /* global trim */
	TxtTrim(*in_str);

        /* count spaces from the end */
        idx=strlen(*in_str)-1;
        while (*in_str[idx]==' ' && idx>0) {idx--;s++;}

        /* count words -1 */
        cw=0;
        for (i=0;i<idx;i++) {
                if (*in_str[i]==' ') cw++;
        }
        ns=(float)s/(float)cw;
        distri=floor(ns);
        s-=distri*cw;

        for (idx=jdx=0;*in_str[idx];idx++) {
                if (*in_str[idx]==' ') {
                        /* give new spaces */
                        for (i=0;i<distri;i++) {
                                Lout_str[jdx++]=' ';
                        }
                        /* give more space */
                        if (s) {
                                Lout_str[jdx++]=' ';
                                s--;
                        }
                }
        }

        MemFree(*in_str);
        *in_str=Lout_str;
}

/***
	TxtToMultiLigne
	char **TxtToMultiLigne(char *in_str, int out_lng) {

	split a text into fixed length substring array

	in_str:  input string
	out_lng: max length of substrings

	return: array of substrings
*/
char **TxtToMultiLigne(char *in_str, int out_lng) {
        char **out_str=NULL;
        char *tmp_str=NULL;
        int nbstr=0,maxstr=0;
        /* idx */
        int idx=0,idxback=0,lng;

        if (!in_str) return NULL;

        tmp_str=MemMalloc(out_lng+1);

        lng=strlen(in_str);
        while (idx+out_lng<lng) {
                idxback=idx;
                idx+=out_lng-1;
                /* looking for a space, a tab, from the end of the string  */
                while (idx>idxback && in_str[idx]!=0x0A && in_str[idx]!=0x0D && in_str[idx]!=0x20 && in_str[idx]!=0x09) idx--;
                /* the word is bigger than the output string, we cut it anyway */
                if (idx==idxback) {
                        strn0cpy(tmp_str,in_str+idxback,out_lng);
                        idx+=out_lng;
                } else {
                        strn0cpy(tmp_str,in_str+idxback,idx-idxback+1);
                        idx++;
                }
                FieldArrayAddDynamicValueConcat(&out_str,&nbstr,&maxstr,tmp_str);
                while (idx<lng && (in_str[idx]==0x09 || in_str[idx]==0x20)) idx++;
        }
        /* we had the remaining to the substring array */
        FieldArrayAddDynamicValueConcat(&out_str,&nbstr,&maxstr,in_str+idx);

        MemFree(tmp_str);
        return out_str;
}


/***
 *	TxtGetFile
 *
 * 	input : a full path to a file
 * 	output: the name of the file without the path
 */
char *TxtGetFile(char *in_str)
{
	#undef FUNC
	#define FUNC "TxtGetFile"

	int i=0,dep;
	char *rev;
	TxtTrim(in_str);
	rev=strrchr(in_str,'/');
	if (rev) {
		dep=rev-in_str;
		if (dep) {
			dep++;
			while (in_str[dep]) {
				in_str[i++]=in_str[dep++];
			}
			in_str[i]=0;
		}
	}
	return in_str;
}

 
char *TxtSimplifyNumber(long long zevalue, char *zeunit, char **tmpbuf)
{
	#undef FUNC
	#define FUNC ""

	static char zestring[128];
	char *IU[9]={"","k","M","G","T","P","E","Z","Y"};
	char *ret;
	int idx=0;
	
	while (zevalue>1000 && idx<8) {
		zevalue/=1000;
		idx++;
	}
	if (tmpbuf) ret=*tmpbuf; else ret=zestring;
	sprintf(ret,"%lld%s%s",zevalue,IU[idx],zeunit);
	return ret;
}


/***
 *	TxtSplit
 *
 * 	split the parameter string into an array of strings
 */
char **_internal_TxtSplitWithChar(char *in_str, char split_char)
{
	#undef FUNC
	#define FUNC "_internal_TxtSplitWithChar"

	char **tab=NULL;
	char *match_str;
	int redo=1;
	int idx,idmax;

	match_str=in_str;

	while (redo && *in_str) {
		while (*match_str && *match_str!=split_char) match_str++;
		redo=*match_str;
		*match_str=0;
		FieldArrayAddDynamicValueConcat(&tab,&idx,&idmax,in_str);
		in_str=++match_str;
	}

	return tab;
}
char ** TxtSplit(char *in_str, char *split_str)
{
	#undef FUNC
	#define FUNC "TxtSplit"

	char **tab=NULL;
	char *match_str;
	int split_size;
	int idx,idmax;

	if (!in_str || !split_str || *split_str==0) {
		logerr("parameters cannot be NULL, split string cannot be empty");
		exit(INTERNAL_ERROR);
	}
	if (split_str[1]==0)
		return _internal_TxtSplitWithChar(in_str,split_str[0]);
	else
		split_size=strlen(split_str);

	while ((match_str=strstr(in_str,split_str))) {
		*match_str=0;
		FieldArrayAddDynamicValueConcat(&tab,&idx,&idmax,in_str);
		in_str=match_str+split_size;
	}
	FieldArrayAddDynamicValueConcat(&tab,&idx,&idmax,in_str);

	return tab;
}

char *TxtMerge(char **tab_str)
{
	#undef FUNC
	#define FUNC "TxtMerge"

	char *ret_str="";
	int i=0,len=1,cw=0;

	while (tab_str[i]) {
		len+=strlen(tab_str[i]);
		i++;
	}
	if (len>1) {
		ret_str=MemMalloc(len);
		ret_str[0]=0;
		for (i=0;tab_str[i];i++) {
			cw+=strappend(ret_str+cw,tab_str[i]);
		}
	}

	return ret_str;
}

char *TxtMergeWithSeparator(char **tab_str, char *separator)
{
	#undef FUNC
	#define FUNC "TxtMergeWithSeparator"

	char *ret_str="";
	int i=0,len=1,cw,lns;

	lns=strlen(separator);

	while (tab_str[i]) {
		len+=strlen(tab_str[i]);
		i++;
	}
	len+=lns*(i-1);
	if (len>1) {
		ret_str=MemMalloc(len);
		ret_str[0]=0;
		cw=strappend(ret_str,tab_str[0]);
		for (i=1;tab_str[i];i++) {
			cw+=strappend(ret_str+cw,separator);
			cw+=strappend(ret_str+cw,tab_str[i]);
		}
	}

	return ret_str;
}

/***
 *	TxtConcat
 *
 *	input: two strings
 *	output: concatenated string
 *
 */
char *TxtConcat(char *in_str, char *cat_str)
{
	#undef FUNC
	#define FUNC "TxtConcat"

	char *new_str;
	int l1,l2;

	l1=strlen(in_str);
	l2=strlen(cat_str);
	new_str=MemMalloc(l1+l2+1);
	memcpy(new_str,in_str,l1);
	memcpy(new_str+l1,cat_str,l2+1);
	return new_str;
}

/***
 *	TxtConcatWithSeparator
 *
 *	input: two strings
 *	output: concatenated string
 *
 */
char *TxtConcatWithSeparator(char *in_str, char *separator, char *cat_str)
{
	#undef FUNC
	#define FUNC "TxtConcatWithSeparator"

	char *new_str;
	int l1,l2,ls;

	l1=strlen(in_str);
	l2=strlen(cat_str);
	ls=strlen(separator);
	new_str=MemMalloc(l1+l2+ls+1);
	memcpy(new_str,in_str,l1+1);
	strcat(new_str+l1,separator); /* bacause separator is supposed to be small */
	memcpy(new_str+l1+ls,cat_str,l2+1);
	return new_str;
}


/***
	Regular expression matching functions

	struct s_reg_machine is designed to handle
	in the future a caching system of regexp
	
*/

#ifdef OS_WIN
/* regular expression wrapper for T-Rex */
#define regex_t    TRex
#define regmatch_t char
#define REG_NOSUB     0
#define REG_EXTENDED  0
#define REG_NOMATCH   1
#endif

struct s_reg_machine
{
	regex_t *preg;
	char *regexp;
	unsigned int regcrc;
	struct s_reg_machine *next;
};


#ifdef OS_WIN
/* regular expression wrapper for T-Rex */
int regcomp(regex_t *preg, const char *regex, int cflags)
{
	TRex *newregexp;
	newregexp=trex_compile(regex,NULL);
	memcpy(preg,newregexp,sizeof(struct TRex));
	free(newregexp);
	return 0;
}
int regexec(const regex_t *preg, const char *string, size_t nmatch,regmatch_t pmatch[], int eflags)
{
	if (trex_match(preg,string)) return 0; else return REG_NOMATCH;
}
void regfree(regex_t *preg)
{
	trex_free(preg);
}
size_t regerror(int errcode, const regex_t *preg, char *errbuf,size_t errbuf_size)
{
	return 0;
}
#else

/***
	_internal_regerror
	
	the POSIX regerror needs a static buffer (why?)
	so it is simple to wrap the function with this
	
	we wont free the memory allocated for the buffer
	because we ALWAYS quit in internal error after
	calling this function
*/
char *_internal_regerror(int regexp_error,regex_t *preg)
{
	#undef FUNC
	#define FUNC "_internal_regerror"
	
	char *buffer;
	buffer=MemCalloc(MAX_LINE_BUFFER+1);
	regerror(regexp_error,preg,buffer,MAX_LINE_BUFFER);
	/* buffer overflow security */
	if (strnlen(buffer,MAX_LINE_BUFFER)==MAX_LINE_BUFFER)
		buffer[MAX_LINE_BUFFER]=0;
	return buffer;
}
/***
	_internal_compile_regexp
	
	compile the regular expression then fill our
	regular expression pool structure
*/
void _internal_compile_regexp(struct s_reg_machine * current_regexp,char *regexp)
{
	#undef FUNC
	#define FUNC "_internal_compile_regexp"

	regex_t *preg;
	int err;
	
	/* we malloc this cause we don't known how to free it, except with regfree */
	preg=malloc(sizeof(regex_t));
	
	if ((err=regcomp(preg,regexp,REG_EXTENDED|REG_NOSUB))!=0)
	{
		logerr("cannot compile regexp [%s]",regexp);
		logerr("%s",_internal_regerror(err,current_regexp->preg));
		exit(INTERNAL_ERROR);
	}
	current_regexp->preg=preg;
	current_regexp->regexp=TxtStrDup(regexp);
}
void _internal_regexp_free(struct s_reg_machine *current_regexp)
{
	#undef FUNC
	#define FUNC "_internal_regexp_free"

	if (current_regexp->preg) {
		regfree(current_regexp->preg);
		MemFree(current_regexp->regexp);
	}
}
struct s_reg_machine * _internal_regexp_get_cache(char *regexp)
{
	#undef FUNC
	#define FUNC "_internal_regexp_get_cache"

	#define REGEXP_CACHE_SIZE 100
	static struct s_reg_machine *regexp_cache=NULL;
	int i,empty=-1;
	unsigned int crc;

	if (!regexp) {
		if (regexp_cache) {
			for (i=0;i<REGEXP_CACHE_SIZE;i++) {
				_internal_regexp_free(&regexp_cache[i]);
			}
			MemFree(regexp_cache);
		}
		return NULL;
	}
	if (!regexp_cache) {
		regexp_cache=MemCalloc(sizeof(struct s_reg_machine)*REGEXP_CACHE_SIZE);
	}

	crc=TxtGetCRC(regexp);

	/* look in previous requests */
	for (i=0;i<REGEXP_CACHE_SIZE;i++) {
		if (regexp_cache[i].regexp) {
			if (regexp_cache[i].regcrc==crc && !strcmp(regexp_cache[i].regexp,regexp)) {
				return &regexp_cache[i];
			}
		} else empty=i;
	}
	if (empty==-1) {
		/* cache is full */
		empty=0;
		_internal_regexp_free(&regexp_cache[empty]);
	}
	regexp_cache[empty].regcrc=crc;
	_internal_compile_regexp(&regexp_cache[empty],regexp);
	return &regexp_cache[empty];
}

/***
	TxtRegMatch (is not multithreaded)
	
	make a regular expression match on in_str with regexp
	
	return REG_MATCH if match
	return REG_NOMATCH if not
	
	warning, this is a pure regular match so if you want to
	match a whole string, use ^ at the beginning of your
	regexp, and $ at the end.
	
	or simply use TxtGlobMatch
*/
int TxtRegMatch(char *in_str, char *regexp)
{
	#undef FUNC
	#define FUNC "TxtRegMatch"
	
	struct s_reg_machine *current_regexp;
	int err;
	
	current_regexp=_internal_regexp_get_cache(regexp);
	
	err=regexec(current_regexp->preg,in_str,0,NULL,0);
	if (err!=0 && err!=REG_NOMATCH)
	{
		logerr("regexp execution error with [%s]",regexp);
		logerr("%s",_internal_regerror(err,current_regexp->preg));
		exit(INTERNAL_ERROR);
	}
	
	return err;
}

#endif

/***
	TxtGlobMatch
	
	like TxtRegMatch bug match the whole string
	by adding constraints to the regular expression
	
	useful to match filenames (globing)
*/
int TxtGlobMatch(char *in_str, char *pattern)
{
	#undef FUNC
	#define FUNC "TxtGlobMatch"
	return fnmatch(pattern,in_str,0);
}

/************************** File operation ******************************/


/***
	s_fileid
	structure used by FileReadLine and FileWriteLine to manage multiple files at a time
*/
struct s_fileid
{
	FILE *file_id;
	char *filename;
	char opening_type[4];
	int cpt;
	struct s_fileid *next;
	/* v2 */
	int closed;
	unsigned long curpos;
};

static struct s_fileid *fileidROOT=NULL;

/***
	FileGetStructFromName
	
	input: filename
	output: file structure
		NULL if not found
*/
struct s_fileid *FileGetStructFromName(char *filename)
{
	#undef FUNC
	#define FUNC "FileGetStructFromName"
	struct s_fileid *curfile;
	struct s_fileid *prevfile;

	if (!filename)
	{
		logerr("filename must not be NULL");
		exit(ABORT_ERROR);
	}

	if (strnlen(filename,PATH_MAX)==PATH_MAX)
	{
		logerr("cannot open this file because the argument size is bigger than PATH_MAX (%d)",PATH_MAX);
		exit(ABORT_ERROR);
	}
	
	/* try to find the file in the list */
	curfile=fileidROOT;
	prevfile=NULL;
	while (curfile!=NULL)
	{
		if (!strcmp(curfile->filename,filename)) {		
			break;
		} else {
			prevfile=curfile;
			curfile=curfile->next;
		}
	}
	/* put the struct to the top of the list */
	if (curfile && prevfile) {
		prevfile->next=curfile->next;
		curfile->next=fileidROOT;
		fileidROOT=curfile;
	}
	
	return curfile;
}

/***
	FileOpen function
	
	open a file in any mode (r,w,a,r+,w+,a+)
	check if the file is already open
	check for conflicts	
*/
FILE *FileOpen(char *filename, char *opening_type)
{
	#undef FUNC
	#define FUNC "FileOpen"
	struct s_fileid *curfile;
	struct s_fileid *oldfile;
	
	/* check parameters coherency */
	if (strlen(opening_type)>3)
	{
		logerr("illegal opening type (too long)");
		exit(ABORT_ERROR);
	}	
	if (strcmp(opening_type,"a") && strcmp(opening_type,"w") && strcmp(opening_type,"r")
	 && strcmp(opening_type,"a+")  && strcmp(opening_type,"w+") && strcmp(opening_type,"r+"))
	{
		logerr("illegal opening type [%s]\nallowed options are: r,w,a,r+,w+,a+",opening_type);
		exit(ABORT_ERROR);
	}		
	
	curfile=FileGetStructFromName(filename);
	
	/* if curfile is NULL then the file is not opened yet */
	if (!curfile)
	{
		/* insert a new record */
		_static_library_nbfile_opened++;
		if (_static_library_nbfile_opened>_static_library_nbfile_opened_max)
			_static_library_nbfile_opened_max=_static_library_nbfile_opened;
		curfile=MemCalloc(sizeof(struct s_fileid));
		curfile->filename=MemMalloc(strlen(filename)+1);
		strcpy(curfile->filename,filename);
		strcpy(curfile->opening_type,opening_type);
		curfile->next=fileidROOT;
		curfile->cpt=0;
		fileidROOT=curfile;
	}
	else
	{
		if (strcmp(curfile->opening_type,opening_type))
		{
			logerr("You can't open the file [%s] in [%s] mode cause it's already open in [%s] mode",filename,opening_type,curfile->opening_type);
			exit(ABORT_ERROR);
		}
		if (!curfile->closed) {
			/* already opened, just return the id */
			return curfile->file_id;
		}
	}
_set_fmode(_O_BINARY);	
	curfile->file_id=fopen(filename,opening_type);
_set_fmode(_O_BINARY);	
	if (!curfile->file_id)
	{
		if (errno==EMFILE) {
			/* too many files opened, close the latest of the list */
			oldfile=fileidROOT;
			while (oldfile->next && !oldfile->next->closed) oldfile=oldfile->next;
			if (oldfile==curfile) {
				logerr("cannot open a single file!");
				exit(INTERNAL_ERROR);
			}
			/* save position and close the file */
			oldfile->curpos=ftell(oldfile->file_id);
			fclose(oldfile->file_id);
			oldfile->file_id=0;
			oldfile->closed=1;
			/* then try again */
			curfile->file_id=fopen(filename,opening_type);
			if (curfile->file_id) {
				if (curfile->curpos) {
					fseek(curfile->file_id,curfile->curpos,SEEK_SET);
					curfile->curpos=0;
				}

				logdebug("opening file [%s] in %s mode (too many opened files limit reached)",filename,opening_type);
				return curfile->file_id;
			}
		}
		
		logerr("failed to open file [%s] with mode [%s]",filename,opening_type);
		logerr("check empty space and permissions");
		exit(ABORT_ERROR);
	}
	
	/* go on previous position */
	if (curfile->curpos) {
		fseek(curfile->file_id,curfile->curpos,SEEK_SET);
		curfile->curpos=0;
	}
	
	logdebug("opening file [%s] in %s mode",filename,opening_type);
	return curfile->file_id;
}

struct s_fileid *FileGetStructFromID(FILE *file_id);

void FileSeekBinary(char *filename,int pos, int st)
{
	#undef FUNC
	#define FUNC "FileSeekBinary"
	FILE *last_id=NULL;
	struct s_fileid *curfile=NULL;
	int err;
	
	last_id=FileOpen(filename,"r");
	if ((err=fseek(last_id,pos,st))!=0) {
		logerr("error seeking %s (%d)",filename,ferror(last_id));
		exit(ABORT_ERROR);
	}
	
	curfile=FileGetStructFromID(last_id);
	switch (st) {
		case SEEK_SET: curfile->curpos=pos; break;
		case SEEK_CUR: curfile->curpos+=pos; break;
		case SEEK_END: logerr("TODO§§§"); break;
		default:logerr("unknown SEEK mode!");exit(INTERNAL_ERROR);
	}
}

/***
	FileGetStructFromID
	
	retrieve the file structure from the tree, with his ID
*/
struct s_fileid *FileGetStructFromID(FILE *file_id)
{
	#undef FUNC
	#define FUNC "FileGetStructFromID"
	struct s_fileid *curfile;
	struct s_fileid *prevfile;
	
	curfile=fileidROOT;
	prevfile=NULL;
	while (curfile!=NULL)
	{
		if (curfile->file_id==file_id) {
			break;
		} else {
			prevfile=curfile;
			curfile=curfile->next;
		}
	}
	if (!curfile)
	{
		logerr("ID requested for an unknown file! (was supposed to be opened)");
		exit(INTERNAL_ERROR);
	}
	/* put the struct to the top of the list */
	if (prevfile) {
		prevfile->next=curfile->next;
		curfile->next=fileidROOT;
		fileidROOT=curfile;
	}
	
	return curfile;
}

/***
	FileClose function
	
	check for closing return code
	free the memory file structure
*/
void FileClose(FILE *file_id)
{
	#undef FUNC
	#define FUNC "FileClose"
	struct s_fileid *curfile;
	struct s_fileid *unlinkcell;
	
	curfile=FileGetStructFromID(file_id);

	if (!curfile->closed) {
		if (fclose(curfile->file_id))
		{
			logerr("error while closing file [%s]",curfile->filename);
		}
	} else {
		/* already closed */
	}

	/* unlink the cell from ROOT */
	if (curfile==fileidROOT)
	{
		fileidROOT=curfile->next;
	}
	else
	{
		unlinkcell=fileidROOT;
		while (unlinkcell->next!=curfile)
			unlinkcell=unlinkcell->next;
		unlinkcell->next=curfile->next;
	}
	MemFree(curfile->filename);
	MemFree(curfile);
	_static_library_nbfile_opened--;
}

/***
	FileAddCPT
	
	add n to counter when reading or writing in a file
*/
void FileAddCPT(FILE *file_id, int n)
{
	#undef FUNC
	#define FUNC "FileAddCPT"
	struct s_fileid *curfile;
	
	curfile=FileGetStructFromID(file_id);
	curfile->cpt+=n;
}
#define FileIncCPT(file_id) FileAddCPT(file_id,1)

/***
	FileGetCPT
	
	Get file counter information
	input: file_id
*/
int FileGetCPT(FILE *file_id)
{
	#undef FUNC
	#define FUNC "FileGetCPT"
	struct s_fileid *curfile;
	
	curfile=FileGetStructFromID(file_id);
	return curfile->cpt;
}
/***
	FileGetCPTFromName
	
	Get file counter information
	input: filename
*/
int FileGetCPTFromName(char *filename)
{
	#undef FUNC
	#define FUNC "FileGetCPTFromName"
	struct s_fileid *curfile;
	
	curfile=FileGetStructFromName(filename);
	if (!curfile)
	{
		logerr("You requested a counter for a file that is not opened! [%s]",filename);
		exit(INTERNAL_ERROR);
	}
	return curfile->cpt;
}



char *_internal_fgetsClose(char *buffer, int maxlen, FILE *f)
{
	#undef FUNC
	#define FUNC "_internal_fgetsClose"
	return NULL;
}

/***
	FileReadLine/FileReadLineXML function
	
	input:
	- filename

	output:
	- a static buffer with the line read
	
	this function can handle many file simultaneously
	just use different filenames without regarding to opened/closed pointer
	the opened handles are automatically closed when the end of the file is reached	
	you are only limited by the system, not by the code
	
	the XML version ass carriage returns after closing tag
	this can be usefull for parsing when reading XML file in a single line
*/
enum e_reading_mode {
RAW_READING,
CLOSE_READING
};

char *_internal_fgetsmulti(char *filename, int read_mode)
{
	#undef FUNC
	#define FUNC "_internal_fgetsmulti"
	static char buffer[MAX_LINE_BUFFER+1]={0};
	FILE *last_id=NULL;
	char * (*_file_get_string)(char *, int, FILE *);
	
	last_id=FileOpen(filename,"r");
	
	switch (read_mode)
	{
		case RAW_READING:_file_get_string=fgets;break;
		case CLOSE_READING:_file_get_string=_internal_fgetsClose;break;
		default:logerr("Unknown read mode! (%d)",read_mode);
	}	
	
	if (_file_get_string(buffer,MAX_LINE_BUFFER,last_id)!=NULL)
	{
		FileIncCPT(last_id);
		if (strnlen(buffer,MAX_LINE_BUFFER)==MAX_LINE_BUFFER)
		{
			logerr("line %d is too long! More than %d characters\n",FileGetCPT(last_id),MAX_LINE_BUFFER);
			exit(INTERNAL_ERROR);
		}
		return buffer;
	}
	else
	{
		/* End of file, we close the handle */
		logdebug("%d line(s) read from %s",FileGetCPT(last_id),filename);
		FileClose(last_id);
		return NULL;
	}
}

char **_internal_fgetsmultilines(char *filename, int read_mode)
{
	#undef FUNC
	#define FUNC "_internal_fgetsmultilines"
	static char buffer[MAX_LINE_BUFFER+1]={0};
	FILE *last_id=NULL;
	char * (*_file_get_string)(char *, int, FILE *);
	char **lines_buffer=NULL;
	int cur_line=0,max_line=0;
	
	last_id=FileOpen(filename,"r");
	
	switch (read_mode)
	{
		case RAW_READING:_file_get_string=fgets;break;
		case CLOSE_READING:_file_get_string=_internal_fgetsClose;break;
		default:logerr("Unknown read mode! (%d)",read_mode);
	}	


	while (_file_get_string(buffer,MAX_LINE_BUFFER,last_id)!=NULL)
	{
		FileIncCPT(last_id);
		if (strnlen(buffer,MAX_LINE_BUFFER)==MAX_LINE_BUFFER)
		{
			logerr("line %d is too long! More than %d characters\n",FileGetCPT(last_id),MAX_LINE_BUFFER);
			exit(INTERNAL_ERROR);
		}
		FieldArrayAddDynamicValueConcat(&lines_buffer,&cur_line,&max_line,buffer);
	}
	/* if file is empty, we allocate an empty struct */
	if (!lines_buffer) {
		/* create the end of the list */
		lines_buffer=MemMalloc(sizeof(char*));
		lines_buffer[0]=NULL;
	}

	/* End of file, we close the handle */
	logdebug("%d line(s) read from %s",FileGetCPT(last_id),filename);
	FileClose(last_id);

	return lines_buffer;
}

#define FileReadClose(filename) _internal_fgetsmulti(filename,CLOSE_READING)
#define FileReadLine(filename) _internal_fgetsmulti(filename,RAW_READING)
#define FileReadLines(filename) _internal_fgetsmultilines(filename,RAW_READING)

long FileReadPos(char *filename)
{
	#undef FUNC
	#define FUNC "FileReadPos"

	FILE *last_id;

	last_id=FileOpen(filename,"r");
	return ftell(last_id);
}

/***

	FileWriteLine function
	
	input:
	- filename
	- a buffer with the line to write
	
	the function do not close the file until a NULL buffer is sent.
	It prevents from too much write flushes
	
	you can use it with many files simultaneously but do not forget
	to close your files if you use this function in a loop of filenames
	or the system will warn you
*/

void FileWriteLine(char *filename, char *buffer)
{
	#undef FUNC
	#define FUNC "FileWriteLine"
	FILE *last_id=NULL;
	
	last_id=FileOpen(filename,"a+");

	if (buffer!=NULL)
	{	
		fputs(buffer,last_id);
		FileIncCPT(last_id);
	}
	else
	{
		/* NULL buffer sent, this means End of file, we close the handle */
		logdebug("%d line(s) written to %s",FileGetCPT(last_id),filename);
		FileClose(last_id);
	}
}
#define FileWriteLineClose(filename) FileWriteLine(filename,NULL)
void FileWriteLines(char *filename, char **buffer)
{
	#undef FUNC
	#define FUNC "FileWriteLines"
	FILE *last_id=NULL;
	int i;
	
	last_id=FileOpen(filename,"a+");
	for (i=0;buffer[i];i++) {
		fputs(buffer[i],last_id);
		FileIncCPT(last_id);
	}
	logdebug("%d line(s) written to %s",FileGetCPT(last_id),filename);
	FileClose(last_id);
}

/***
	FileReadBinary function
	
	read n bytes into buffer
	return number of byte really read
	
	as other File functions, you can use it with many files simultaneously
*/
int FileReadBinary(char *filename,char *data,int n)
{
	#undef FUNC
	#define FUNC "FileReadBinary"
	FILE *last_id=NULL;
	int nn;
	
	last_id=FileOpen(filename,"r");
_set_fmode(_O_BINARY);
	if (data==NULL)
	{
		FileClose(last_id);
		return 0;
	}
	
	nn=fread(data,1,n,last_id);
	FileAddCPT(last_id,nn);
	if (nn!=n)
	{
		/* if eof is set, this is not an error */
		if (feof(last_id))
		{
			logdebug("%d byte(s) read from %s",FileGetCPT(last_id),filename);
		}
		else
		if (ferror(last_id))
		{
			if (!nn)
				logerr("cannot read %s",filename);
			else
				logerr("error %d bytes were read during reading of %d bytes of %s",nn,n,filename);
			exit(ABORT_ERROR);
		}
		else
		{
			logerr("error during read of %s (but no error neither eof flag set)",filename);
			exit(INTERNAL_ERROR);
		}				
		FileClose(last_id);
	}
	return nn;
}

/***
	FileWriteBinary function
	
	write n bytes from buffer to file
	return number of byte really written
	
	as other File functions, you can use it with many files simultaneously
*/
int FileWriteBinary(char *filename,char *data,int n)
{
	#undef FUNC
	#define FUNC "FileWriteBinary"
	FILE *last_id=NULL;
	int nn;
	
	last_id=FileOpen(filename,"a+");
_set_fmode(_O_BINARY);	
	if (data!=NULL)
	{	
		nn=fwrite(data,1,n,last_id);
		FileAddCPT(last_id,nn);
		/* we must always write the same amount of data */
		if (n!=nn)
		{
			if (ferror(last_id))
			{
				if (!nn)
					logerr("cannot write %s",filename);
				else
					logerr("error during write of %s (%d byte(s))",filename,FileGetCPT(last_id));
				exit(ABORT_ERROR);
			}
			else
			{
				logerr("error during write of %s (but no error neither eof flag set) %d byte(s) written",filename,FileGetCPT(last_id));
				exit(INTERNAL_ERROR);
			}
		}
	}
	else
	{
		/* NULL buffer sent, this means End of file, we close the handle */
		logdebug("%d byte(s) written to %s",FileGetCPT(last_id),filename);
		FileClose(last_id);
	}
	return nn;
}
/*** macro to close binary files */
#define FileReadBinaryClose(filename) FileReadBinary(filename,NULL,0)
#define FileWriteBinaryClose(filename) FileWriteBinary(filename,NULL,0)



/*****************/

struct s_blockfile_entry {
char *filename;
int crc;
int size;
int dataoffset;
};

struct s_blockfile_resource {
char *filename;
struct s_blockfile_entry *entry;
int nbentry;
};

struct s_blockfile {
struct s_blockfile_resource *resource;
int nbresource,maxresource;
};


struct s_blockfile resourcefileROOT={0};

struct s_blockfile_entry *s_writeblockfileentry=NULL;
int s_writeblockfileentrynb=0,s_writeblockfileentrymax=0;

#ifndef RDD
void BlockFileInit(char *blockfilename)
{
	#undef FUNC
	#define FUNC "BlockFileInit"
	
	struct s_blockfile_resource blockfile_resource={0};
	unsigned char *rawheader;
	int headersize;
	int idx,tidx;
	int i;
	
	for (i=0;i<resourcefileROOT.nbresource;i++) {
		if (strcmp(resourcefileROOT.resource[i].filename,blockfilename)==0) {
			logwarn("blockfile [%s] already loaded, updating",blockfilename);
		}
	}

	
	if (FileReadBinary(blockfilename,(char*)&headersize,4)!=4) {
		rawheader=MemMalloc(headersize);
		if (FileReadBinary(blockfilename,rawheader,headersize)!=headersize) {
			logerr("[%s] is corrupted! (Truncated header)",blockfilename);
			exit(ABORT_ERROR);
		}
	} else {
		logerr("[%s] is corrupted! (Less than 4 bytes)",blockfilename);
		exit(ABORT_ERROR);
	}
	
	/* header parsing */
	idx=4;
	blockfile_resource.nbentry=*((int *)rawheader);
	loginfo("resource file [%s] contains %d file%s",blockfilename,blockfile_resource.nbentry,blockfile_resource.nbentry>1?"s":"");
	blockfile_resource.entry=MemMalloc(blockfile_resource.nbentry*sizeof(struct s_blockfile_entry));
	
	for (i=0;i<blockfile_resource.nbentry;i++) {
		tidx=idx;
		while (rawheader[tidx]!=0 && tidx<headersize) tidx++;
		if (rawheader[tidx] || tidx+8>headersize) {
			logerr("[%s] is corrupted! (Wrong header)",blockfilename);
			exit(ABORT_ERROR);
		}
		/* copy string */
		blockfile_resource.entry[i].filename=TxtStrDup(&rawheader[idx]);
		blockfile_resource.entry[i].crc=TxtGetCRC(blockfile_resource.entry[i].filename);
		blockfile_resource.entry[i].size=*((int *)(&rawheader[tidx]));
		blockfile_resource.entry[i].dataoffset=*((int *)(&rawheader[tidx+4]));
		tidx+=8;
		
		loginfo("[%s] entry [%s] size=%d offset=%d",blockfilename,blockfile_resource.entry[i].filename,
			blockfile_resource.entry[i].size,blockfile_resource.entry[i].dataoffset);
	}
	
	ObjectArrayAddDynamicValueConcat((void **)&resourcefileROOT.resource,&resourcefileROOT.nbresource,&resourcefileROOT.maxresource,&blockfile_resource,sizeof(struct s_blockfile_resource));
}

unsigned char *BlockFileRead(char *filename, int *size)
{
	#undef FUNC
	#define FUNC "BlockFileRead"
	
	unsigned char *datain,*dataout=NULL;
	unsigned int crc;
	int i,j;
	
	crc=TxtGetCRC(filename);
	for (i=0;i<resourcefileROOT.nbresource;i++) {
		for (j=0;j<resourcefileROOT.resource[i].nbentry;j++) {
			if (resourcefileROOT.resource[i].entry[j].crc==crc && strcmp(resourcefileROOT.resource[i].entry[j].filename,filename)==0) {
				datain=MemMalloc(resourcefileROOT.resource[i].entry[j].size);
				/* lecture */
				FileSeekBinary(resourcefileROOT.resource[i].filename,resourcefileROOT.resource[i].entry[j].dataoffset,SEEK_SET);
				FileReadBinary(resourcefileROOT.resource[i].filename,datain,resourcefileROOT.resource[i].entry[j].size);
				*size=MemoryDecrunch(datain,&dataout);
				return dataout;
			}
		}
	}
	
	*size=0;
	return NULL;
}

void BlockFileWritePrepare(char *filename)
{
	#undef FUNC
	#define FUNC "BlockFileWritePrepare"
	
	struct s_blockfile_entry blank_entry={0};
	
	blank_entry.filename=TxtStrDup(filename);
	blank_entry.size=FileGetSize(filename);
	
	ObjectArrayAddDynamicValueConcat((void **)&s_writeblockfileentry,&s_writeblockfileentrynb,&s_writeblockfileentrymax,&blank_entry,sizeof(struct s_blockfile_entry));
}
void BlockFileWriteFinalize(char *blockfilename)
{
	#undef FUNC
	#define FUNC "BlockFileWriteFinalize"
	
	unsigned char **filedata;
	unsigned char *rawdata=NULL;
	int dataoffset=4+4; /* headersize & nbentry */
	int i,headersize;
	unsigned long uncompressedsize=0,compressedsize=0,cursize;

	
	loginfo("new blockfile %s of %d file%s",blockfilename,s_writeblockfileentrynb,s_writeblockfileentrynb>1?"s":"");
	
	for (i=0;i<s_writeblockfileentrynb;i++) {
		dataoffset+=strlen(s_writeblockfileentry[i].filename)+1;
		dataoffset+=8; /* size & dataoffset */
		uncompressedsize+=s_writeblockfileentry[i].size;
	}
	headersize=dataoffset-4;
	/* 2nd pass */
	loginfo("loading/crunching into memory");
	filedata=MemCalloc(s_writeblockfileentrynb*sizeof(unsigned char *));
	for (i=0;i<s_writeblockfileentrynb;i++) {
		s_writeblockfileentry[i].dataoffset=dataoffset;
		rawdata=MemRealloc(rawdata,s_writeblockfileentry[i].size);
		FileReadBinary(s_writeblockfileentry[i].filename,rawdata,s_writeblockfileentry[i].size+1); /* size+1 to autoclose the file */
		cursize=MemoryCrunchMax(rawdata,&filedata[i],s_writeblockfileentry[i].size);
	loginfo("(compression %.1f%%) %s",100.0-(float)cursize*100.0/(float)s_writeblockfileentry[i].size,s_writeblockfileentry[i].filename);
		s_writeblockfileentry[i].size=cursize;
		dataoffset+=s_writeblockfileentry[i].size;
	}
	/* 3rd pass */
	loginfo("writing header size");
	//FileWriteBinary(blockfilename,&headersize,4);
	loginfo("writing header");
	//FileWriteBinary(blockfilename,&s_writeblockfileentrynb,4);
	compressedsize=8;
	for (i=0;i<s_writeblockfileentrynb;i++) {
		//FileWriteBinary(blockfilename,s_writeblockfileentry[i].filename,strlen(s_writeblockfileentry[i].filename)+1);
		//FileWriteBinary(blockfilename,s_writeblockfileentry[i].size,4);
		//FileWriteBinary(blockfilename,s_writeblockfileentry[i].dataoffset,4);
		compressedsize+=8+strlen(s_writeblockfileentry[i].filename)+1;
	}
	loginfo("global header=%d",compressedsize);
	loginfo("writing data");
	for (i=0;i<s_writeblockfileentrynb;i++) {
		//FileWriteBinary(blockfilename,filedata[i],s_writeblockfileentry[i].size);
		compressedsize+=s_writeblockfileentry[i].size;
	}
	//FileWriteBinaryClose(blockfilename);
	loginfo("blockfile is %d bytes (compression %.1f%%)",compressedsize,100.0-(float)compressedsize*100.0/(float)uncompressedsize);
	/* clean memory */
	MemFree(rawdata);
	MemFree(filedata);
	for (i=0;i<s_writeblockfileentrynb;i++) {
		MemFree(s_writeblockfileentry[i].filename);
	}
	MemFree(s_writeblockfileentry);
	s_writeblockfileentrynb=0;
	s_writeblockfileentrymax=0;
}

void _internal_BlockFileWriteDir(char *directory, char *filename, int recurse)
{
	#undef FUNC
	#define FUNC "_internal_BlockFileWriteDir"
	
	char **zelist=NULL;
	int i=0;
	
	if (recurse) zelist=DirReadAllEntriesRecurse(directory); else zelist=DirReadAllEntries(directory);
	while (zelist[i]) {
		if (FileIsRegular(zelist[i])) {
			BlockFileWritePrepare(zelist[i]);
		}
		i++;
	}
	BlockFileWriteFinalize(filename);
	FreeFields(zelist);
}

#define BlockFileWriteDir(directory,filename) _internal_BlockFileWriteDir(directory,filename,0)
#define BlockFileWriteDirRecurse(directory,filename) _internal_BlockFileWriteDir(directory,filename,1)

void BlockFileClose(char *blockfilename)
{
	#undef FUNC
	#define FUNC "BlockFileClose"
	
	int i;
	char a;
	
	for (i=0;i<resourcefileROOT.nbresource;i++) {
		if (strcmp(resourcefileROOT.resource[i].filename,blockfilename)==0) {
			break;
		}
	}

	if (i!=resourcefileROOT.nbresource) {
		FileReadBinaryClose(blockfilename);
		MemFree(resourcefileROOT.resource[i].filename);
		if (i+1<resourcefileROOT.nbresource) {
			resourcefileROOT.resource[i]=resourcefileROOT.resource[resourcefileROOT.nbresource-1];
		}
		resourcefileROOT.nbresource--;
		if (!resourcefileROOT.nbresource) {
			MemFree(resourcefileROOT.resource);
			MemSet(&resourcefileROOT,0,sizeof(struct s_blockfile));
		}
	} else {
		logerr("blockfile [%s] was not opened",blockfilename);
		exit(ABORT_ERROR);
	}
}
#endif


/***
	FileChmod
	
*/
#ifdef OS_WIN
#define mode_t int
void FileChmod(char *filename, mode_t zemode)
{
	/* no effect on windows system */
}
#else
void FileChmod(char *filename, mode_t zemode)
{
	#undef FUNC
	#define FUNC "FileChmod"

	if (!filename)
	{
		logerr("filename cannot be NULL!");
		exit(ABORT_ERROR);
	}
	/* checked after by the system but... */
	if (strnlen(filename,PATH_MAX)==PATH_MAX)
	{
		logerr("cannot chmod this file or directory because the argument size is bigger than PATH_MAX (%d)",PATH_MAX);
		exit(ABORT_ERROR);
	}
	
	logdebug("chmod file %s with rights %o",filename,zemode);
	if (chmod(filename,zemode)!=0)
	{
		logerr("file: %s mode:%o",filename,zemode);
		switch (errno)
		{
			case EACCES:logerr("Search permission is denied on a component of the path prefix.");break;
			case ELOOP:logerr("A loop exists in symbolic links encountered during resolution of the path argument.");break;
			case ENAMETOOLONG:logerr("The length of the path argument exceeds maximum path value or a pathname component is longer than name maximum value.");break;
			case ENOTDIR:logerr("A component of the path prefix is not a directory.");break;
			case ENOENT:logerr("A component of path does not name an existing file or path is an empty string.");break;
			case EPERM:logerr("The effective user ID does not match the owner of the file and the process does not have appropriate privileges.");break;
			case EROFS:logerr("The named file resides on a read-only file system.");break;
			case EINTR:logerr("A signal was caught during execution of the function.");break;
			case EINVAL:logerr("The value of the mode argument is invalid.");break;
			default:logerr("Unknown error %d during chmod: %s",errno,strerror(errno));
		}
		exit(ABORT_ERROR);
	}	
}
#endif
/***
	MakeDirWithRights
	
	to simplify directories creation management, we override the umask
*/
void MakeDirWithRights(char *dirname, mode_t zemode)
{
	#undef FUNC
	#define FUNC "MakeDirWithRights"
	
	if (!dirname)
	{
		logerr("directory name must not be NULL");
		exit(ABORT_ERROR);
	}
	/* apparently not checked by the system so... */
	if (strnlen(dirname,PATH_MAX)==PATH_MAX)
	{
		logerr("cannot create this directory because the argument size is bigger than PATH_MAX (%d)",PATH_MAX);
		exit(ABORT_ERROR);
	}
	
	logdebug("make directory %s with rights %o",dirname,zemode);
#ifdef OS_WIN
	if (_mkdir(dirname)==-1)
#else
	if (mkdir(dirname,zemode)!=0)
#endif
	{
		logerr("dir: %s mode:%o",dirname,zemode);
		switch (errno)
		{
			case EACCES:logerr("Write permission is denied for the parent directory in which the new directory is to be added.");break;
			case EEXIST:logerr("An entry named %s already exists.",dirname);break;
			case EMLINK:logerr("The parent directory has too many links.");break;
			case ENOSPC:logerr("The file system doesn't have enough room to create the new directory.");break;
			case EROFS:logerr("The parent directory of the directory being created is on a read-only file system and cannot be modified.");break;
			default:logerr("Unknown error %d during mkdir: %s",errno,strerror(errno));
		}
		exit(ABORT_ERROR);
	}
	/* because i do not want to deal with umask for this function */
	FileChmod(dirname,zemode);
}
#define MakeDir(dirname) MakeDirWithRights(dirname,S_IRWXU|S_IRWXG|S_IRWXO);



/***
	FileGetStat
	
	Get file statistics (size, timestamp, etc.)

struct stat {
    dev_t     st_dev;      ID of device containing file 
    ino_t     st_ino;      inode number 
    mode_t    st_mode;     protection 
    nlink_t   st_nlink;    number of hard links 
    uid_t     st_uid;      user ID of owner 
    gid_t     st_gid;      group ID of owner 
    dev_t     st_rdev;     device ID (if special file) 
    off_t     st_size;     total size, in bytes 
    blksize_t st_blksize;  blocksize for filesystem I/O 
    blkcnt_t  st_blocks;   number of blocks allocated 
    time_t    st_atime;    time of last access 
    time_t    st_mtime;    time of last modification 
    time_t    st_ctime;    time of last status change 
};

S_IFMT  0170000  bitmask for the file type bitfields  
S_IFSOCK  0140000  socket  
S_IFLNK  0120000  symbolic link  
S_IFREG  0100000  regular file  
S_IFBLK  0060000  block device  
S_IFDIR  0040000  directory  
S_IFCHR  0020000  character device  
S_IFIFO  0010000  FIFO  
S_ISUID  0004000  set UID bit  
S_ISGID  0002000  set-group-ID bit (see below)  
S_ISVTX  0001000  sticky bit (see below)  
S_IRWXU  00700  mask for file owner permissions  
S_IRUSR  00400  owner has read permission  
S_IWUSR  00200  owner has write permission  
S_IXUSR  00100  owner has execute permission  
S_IRWXG  00070  mask for group permissions  
S_IRGRP  00040  group has read permission  
S_IWGRP  00020  group has write permission  
S_IXGRP  00010  group has execute permission  
S_IRWXO  00007  mask for permissions for others (not in group)  
S_IROTH  00004  others have read permission  
S_IWOTH  00002  others have write permission  
S_IXOTH  00001  others have execute permission 
*/

/***
	FileGetStat
	
	input: filename
	return the stat structure of a given file
*/
struct stat *FileGetStat(char *filename)
{
	#undef FUNC
	#define FUNC "FileGetStat"
	return NULL;
}

/***
	FileGetSize
	
	input: filename
	output: the size in bytes of the file
*/
long long FileGetSize(char *filename)
{
	#undef FUNC
	#define FUNC "FileGetSize"
	long long nn=0;
	
	return nn;
}
/***
	FileGetMode
	
	input: filename
	output: the mode_t structure of the file
*/
mode_t FileGetMode(char *filename)
{
	#undef FUNC
	#define FUNC "FileGetMode"
	return 0;
}

/***
	FileGetUID
	
	input: filename
	output: the uid of the file
*/
#ifndef OS_WIN
uid_t FileGetUID(char *filename)
{
	#undef FUNC
	#define FUNC "FileGetUID"
	struct stat *filestat;
	uid_t nn;
	
	filestat=FileGetStat(filename);
	nn=filestat->st_uid;
	MemFree(filestat);
	return nn;
}

/***
	FileGetGID
	
	input: filename
	output: the gid of the file
*/
gid_t FileGetGID(char *filename)
{
	#undef FUNC
	#define FUNC "FileGetGID"
	struct stat *filestat;
	gid_t nn;
	
	filestat=FileGetStat(filename);
	nn=filestat->st_gid;
	MemFree(filestat);
	return nn;
}
#endif
#ifndef RDD
/*
 * optimised reading of text file in one shot
 */
unsigned char *_internal_readbinaryfile(char *filename, int *filelength)
{
	#undef FUNC
	#define FUNC "_internal_readbinaryfile"

	unsigned char *binary_data=NULL;
	
	*filelength=FileGetSize(filename);
	binary_data=MemMalloc((*filelength)+1);
	/* we try to read one byte more to close the file just after the read func */
	if (FileReadBinary(filename,binary_data,(*filelength)+1)!=*filelength) {
		logerr("Cannot fully read %s",filename);
		exit(INTERNAL_ERROR);
	}
	return binary_data;
}
char **_internal_readtextfile(char *filename)
{
	#undef FUNC
	#define FUNC "_internal_readtextfile"

	char **lines_buffer=NULL;
	unsigned char *bigbuffer;
	int nb_lines=0,max_lines=0,i=0,e=0;
	FILE *file_id;
	int file_size;

	bigbuffer=_internal_readbinaryfile(filename,&file_size);

	while (i<file_size) {
		while (e<file_size && bigbuffer[e]!=0x0A) {
			if (bigbuffer[e]==0x0D && e+1<file_size && bigbuffer[e+1]==0x0A) {
				bigbuffer[e]=0x0A;
				bigbuffer[e+1]=0;
				e++;
				break;
			}
			e++;
		}
		if (e<file_size) e++;
		if (nb_lines>=max_lines) {
			max_lines=max_lines*2+10;
			lines_buffer=MemRealloc(lines_buffer,(max_lines+1)*sizeof(char **));
		}
		lines_buffer[nb_lines]=MemMalloc(e-i+2);
		memcpy(lines_buffer[nb_lines],bigbuffer+i,e-i);
		lines_buffer[nb_lines][e-i]=0;
		nb_lines++;
		i=e;
	}
	if (!max_lines) {
		lines_buffer=MemMalloc(sizeof(char*));
		lines_buffer[0]=NULL;
	} else {
		lines_buffer[nb_lines]=NULL;
	}
	MemFree(bigbuffer);
	return lines_buffer;
}

#define FileReadLines(filename) _internal_readtextfile(filename)
#define FileReadContent(filename,filesize) _internal_readbinaryfile(filename,filesize)
#endif



/***
	ParameterParseFieldList
	input : a string representing a list of fields	
	this may be 1,2,3,7,5,12 (only positives numbers) but also
	an interval like 6-24 (ascending or descending) or a mix like 5,20-15,2
	
	output: an allocated integer array of fields, terminated by -1 value
*/
int *ParameterParseFieldList(char *fieldlist)
{
	#undef FUNC
	#define FUNC "ParameterParseFieldList"
	static int terminator=-1;
	char *buffer,*fieldbuffer;
	int cl,cpt,i,startidx,endidx;
	int *field;

	if (fieldlist==NULL)
	{
		field=MemMalloc(sizeof(int));
		field[0]=-1;
		return field;
	}	
	
	/* parse fieldlist */
	buffer=TxtStrDup(fieldlist);
	/* +1 cause we need the ending character to get the last field*/
	fieldbuffer=buffer;
	cl=strlen(buffer)+1;
	cpt=1;
	i=0;
	while (i<cl)
	{
		if (buffer[i]=='-')
		{
			buffer[i]=0;
			startidx=atoi(fieldbuffer);
			buffer[i]='-';
			fieldbuffer=&buffer[i+1];
			i++;
			while (buffer[i]!=',' && buffer[i]!=0 && buffer[i]!=0x0D && buffer[i]!=0x0A) i++;
			buffer[i]=0;
			endidx=atoi(fieldbuffer);
			if (endidx<startidx)
				cpt+=startidx-endidx+1;
			else
				cpt+=endidx-startidx+1;
			
			fieldbuffer=&buffer[i+1];
		}
		
		if (buffer[i]==',')
		{
			cpt++;
			fieldbuffer=&buffer[i+1];
		}
		i++;
	}
	field=MemMalloc((cpt+1)*sizeof(int));
	
	fieldbuffer=buffer;
	i=cpt=0;
	while (i<cl)
	{
		if (buffer[i]=='-')
		{
			buffer[i]=0;
			startidx=atoi(fieldbuffer);
			fieldbuffer=&buffer[i+1];
			i++;
			while (buffer[i]!=',' && buffer[i]!=0 && buffer[i]!=0x0D && buffer[i]!=0x0A) i++;
			buffer[i]=0;
			endidx=atoi(fieldbuffer);
			if (endidx<startidx)
				while (startidx>=endidx)
				{
					field[cpt++]=startidx;
					startidx--;
				}
			else
				while (startidx<=endidx)
				{
					field[cpt++]=startidx;
					startidx++;
				}
			fieldbuffer=&buffer[i+1];
		}
		else
		if (buffer[i]==',' || buffer[i]==0 || buffer[i]==0x0D || buffer[i]==0x0A)
		{
			buffer[i]=0;
			field[cpt]=atoi(fieldbuffer);
			fieldbuffer=&buffer[i+1];
			cpt++;
		}
		i++;
	}
	/* end of field list */
	field[cpt]=-1;
	MemFree(buffer);
	return field;
}
#define ParameterFreeFieldList(fieldlist) MemFree(fieldlist)

/***
	CalcArrayMax
	input: 
	- array of integer
	- size of the array. If null then run until it gets -1 value
	output
	- maximum value in the array (always positive for the array terminated by -1)
*/
int CalcArrayMax(int *myarray, int asize)
{
	#undef FUNC
	#define FUNC "CalcArrayMax"

	int i,maxarray;
	
	if (asize==0)
	{
		maxarray=myarray[0];
		i=1;
		while (myarray[i]!=-1)
		{
			if (maxarray<myarray[i])
				maxarray=myarray[i];
			i++;
		}
	}
	else
	{
		maxarray=myarray[0];
		for (i=1;i<asize;i++)
			if (maxarray<myarray[i])
				maxarray=myarray[i];
	}
	return maxarray;
}

/***
	CalcArrayElem
	input: 
	- array of integer terminated by -1
	output
	- number of elem of the array
*/
int CalcArrayElem(int *myarray)
{
	#undef FUNC
	#define FUNC "CalcArrayElem"

	int cpt=0;
	
	while (myarray[cpt]!=-1)
		cpt++;
	return cpt;
}



/***
	CSV fields parsing functions

	get number of fields in a line
	to split read line into field
*/

int CSVGetFieldNumber(char *buffer, char separator)
{
	#undef FUNC
	#define FUNC "CSVGetFieldNumber"
	
	int i,l,numfield=1;
	
	l=strnlen(buffer,MAX_LINE_BUFFER);
	i=0;
	
	while (i<l && buffer[i]!=0x0D && buffer[i]!=0x0A)
	{
		while (buffer[i]!=separator && i<l && buffer[i]!=0x0D && buffer[i]!=0x0A) i++;
		if (buffer[i]==separator)
			numfield++;
		i++;
	}
	return numfield;
}
int CSVGetQuotedFieldNumber(char *buffer, char separator)
{
	#undef FUNC
	#define FUNC "CSVGetQuotedFieldNumber"
	
	int i,l,numfield=1,open=0;
	
	l=strnlen(buffer,MAX_LINE_BUFFER);
	i=0;
	
	while (i<l && buffer[i]!=0x0D && buffer[i]!=0x0A)
	{
		while (i<l && buffer[i]!=0x0D && buffer[i]!=0x0A) {
			if (buffer[i]=='"') {
				open=1-open;
			} else if (buffer[i]==separator && !open) {
				break;
			}
			i++;
		}
		if (buffer[i]==separator && !open)
			numfield++;
		i++;
	}
	return numfield;
}
/***
	CSVGetAllFields
	
	return an array of strings after parsing a buffer with separator
	
	input: buffer (not modified by the function)
	       separator
	       
*/
char **CSVGetAllFields(char *backbuffer, char separator)
{
	#undef FUNC
	#define FUNC "CSVGetAllFields"

	char **curcolumn;
	char *colbuffer;
	char *buffer;
	int i,l,cl,ncol,icol,sep;
	
	buffer=TxtStrDup(backbuffer);
	
	l=strnlen(buffer,MAX_LINE_BUFFER);
	i=0;
	
	ncol=CSVGetFieldNumber(buffer,separator);
	if (!ncol)
	{
		logwarn("The line you read was empty! This may cause some trouble...");
		return NULL;
	}
	curcolumn=MemCalloc((ncol+1)*sizeof(char*));
	
	icol=0;
	while (i<l && buffer[i]!=0x0D && buffer[i]!=0x0A)
	{
		colbuffer=&buffer[i];
		sep=0;
		while (buffer[i]!=separator && i<l && buffer[i]!=0x0D && buffer[i]!=0x0A) i++;
		if (buffer[i]==separator)
			sep=1;
		buffer[i]=0;
		/*
		cl=strlen(colbuffer);
		curcolumn[icol]=MemCalloc(cl+1);
		strcpy(curcolumn[icol],colbuffer);
		*/
		curcolumn[icol++]=TxtStrDup(colbuffer);
		i++;
	}
	/* separator on the last character, we must add an empty field */
	if (sep)
		curcolumn[icol++]=TxtStrDup("");	
	curcolumn[icol]=NULL;
	MemFree(buffer);
	return curcolumn;
}

char **CSVGetAllQuotedFields(char *backbuffer, char separator)
{
	#undef FUNC
	#define FUNC "CSVGetAllQuotedFields"

	char **curcolumn;
	char *colbuffer;
	char *buffer;
	int i,l,cl,ncol,icol,sep,open=0;
	
	buffer=TxtStrDup(backbuffer);
	
	l=strnlen(buffer,MAX_LINE_BUFFER);
	i=0;
	
	ncol=CSVGetQuotedFieldNumber(buffer,separator);
	if (!ncol)
	{
		logwarn("The line you read was empty! This may cause some trouble...");
		return NULL;
	}
	curcolumn=MemCalloc((ncol+1)*sizeof(char*));
	
	icol=0;
	while (i<l && buffer[i]!=0x0D && buffer[i]!=0x0A)
	{
		colbuffer=&buffer[i];
		sep=0;
		while (i<l && buffer[i]!=0x0D && buffer[i]!=0x0A) {
			if (buffer[i]=='"') {
				open=1-open;
			} else if (buffer[i]==separator && !open) {
				sep=1;
				break;
			}
			i++;
		}
		buffer[i]=0;
		/*
		cl=strlen(colbuffer);
		curcolumn[icol]=MemCalloc(cl+1);
		strcpy(curcolumn[icol],colbuffer);
		*/
		curcolumn[icol++]=TxtStrDup(colbuffer);
		i++;
	}
	/* separator on the last character, we must add an empty field */
	if (sep)
		curcolumn[icol++]=TxtStrDup("");	
	curcolumn[icol]=NULL;
	MemFree(buffer);
	return curcolumn;
}
/***
	CSVGetFieldArrayNumber
	
	count array elements
*/
int CSVGetFieldArrayNumber(char **myfield)
{
	#undef FUNC
	#define FUNC "CSVGetFieldArrayNumber"
	
	int n=0;
	
	if (myfield==NULL)
		return 0;
	
	while (myfield[n]!=NULL) n++;
	
	return n;

}

void _internal_ObjectArrayAddDynamicValueConcat(void **zearray, int *nbfields, int *maxfields, void *zeobject, int object_size, int curline, char *curfunc, char *cursource)
{
	#undef FUNC
	#define FUNC "ObjectArrayAddDynamicValueConcat"

	char *dst;

	if ((*zearray)==NULL) {
		*nbfields=1;
		*maxfields=3;
		(*zearray)=_internal_MemRealloc(NULL,(*maxfields)*object_size,cursource,curline,curfunc);
	} else {
		*nbfields=(*nbfields)+1;
		if (*nbfields>=*maxfields) {
			*maxfields=(*maxfields)*2;
			(*zearray)=_internal_MemRealloc((*zearray),(*maxfields)*object_size,cursource,curline,curfunc);
		}
	}
	/* using direct calls because it is more interresting to know which is the caller */
	dst=((char *)(*zearray))+((*nbfields)-1)*object_size;
	/* control of memory for overflow */
	_internal_MemCpy(dst,zeobject,object_size,cursource,curline,curfunc);
}

/***
	Add a value to a list of integers
	Reallocate memory on the fly

	zearray: pointer to the array of integers
	nbval:   pointer to the current index
	maxval:  pointer to the current allocated memory
	zevalue: integer value to concat to	
	       
	output: the pointer to the array is modified because the
	function reallocate memory to store the new string at
	the end of the array.
*/
void _internal_IntArrayAddDynamicValueConcat(int **zearray, int *nbval, int *maxval, int zevalue, int curline, char *curfunc, char *cursource)
{
	#undef FUNC
	#define FUNC "IntArrayAddDynamicValue"

	if ((*zearray)==NULL) {
		*nbval=1;
		*maxval=4;
		(*zearray)=MemMalloc(sizeof(int)*(*maxval));
	} else {
		*nbval=*nbval+1;
		if (*nbval>=*maxval) {
			*maxval=(*maxval)*2;
			(*zearray)=_internal_MemRealloc((*zearray),sizeof(int)*(*maxval),cursource,curline,curfunc);
		}
	}
	(*zearray)[(*nbval)-1]=zevalue;
}

/***
	Add a value to a list of strings
	Reallocate memory on the fly
	
	input: pointer to an array of string
	       string value
	       
	output: the pointer to the array is modified because the
	function reallocate memory to store the new string at
	the end of the array.
*/
void _internal_FieldArrayAddDynamicValue(char ***zearray, char *zevalue, int curline, char *curfunc, char *cursource)
{
	#undef FUNC
	#define FUNC "FieldArrayAddDynamicValue"
	int nbfield;
	if ((*zearray)==NULL) nbfield=2; else nbfield=CSVGetFieldArrayNumber((*zearray))+2;
	/* using direct calls because it is more interresting to know which is the caller */
	(*zearray)=_internal_MemRealloc((*zearray),nbfield*sizeof(char *),cursource,curline,curfunc);
	(*zearray)[nbfield-2]=_internal_strdup(zevalue,cursource,curline,curfunc);
	(*zearray)[nbfield-1]=NULL;
}
void _internal_FieldArrayAddDynamicValueConcat(char ***zearray, int *nbfields, int *maxfields, char *zevalue, int curline, char *curfunc, char *cursource)
{
	#undef FUNC
	#define FUNC "FieldArrayAddDynamicValueConcat"

	if ((*zearray)==NULL) {
		*nbfields=1;
		*maxfields=10;
		(*zearray)=_internal_MemRealloc(NULL,(*maxfields)*sizeof(char *),cursource,curline,curfunc);
	} else {
		*nbfields=(*nbfields)+1;
		if (*nbfields>=*maxfields) {
			*maxfields=(*maxfields)*2;
			(*zearray)=_internal_MemRealloc((*zearray),(*maxfields)*sizeof(char *),cursource,curline,curfunc);
		}
	}
	/* using direct calls because it is more interresting to know which is the caller */
	(*zearray)[(*nbfields)-1]=_internal_strdup(zevalue,cursource,curline,curfunc);
	(*zearray)[(*nbfields)]=NULL;
}

/***
 *	copy an array of strings, terminated by a NULL pointer
 *
 */
char **CSVCopyFields(char **fields)
{
	#undef FUNC
	#define FUNC "CSVCopyFields"

	int idx=0,idxmax=0;
	char **newfields=NULL;

	if (fields) {
		while (fields[idx]) {
			FieldArrayAddDynamicValueConcat(&newfields,&idx,&idxmax,fields[idx]);
		}
	}

	return newfields;
}

/***
	CSVFreeFields

	free allocated memory for fields
*/
void CSVFreeFields(char **fields)
{
	#undef FUNC
	#define FUNC "CSVFreeFields"
	
	int i=0;
	if (fields!=NULL)
	{
		/*loginfo("%8X",fields);
		if (fields[i]==NULL)
			loginfo("NULL i=%d",i); */
		
		while (fields[i]!=NULL)
		{
			MemFree(fields[i]);
			i++;
		}
		MemFree(fields);
	}
}
void FreeArrayDynamicValue(char ***zearray)
{
	CSVFreeFields(*zearray);
	*zearray=NULL;
}
#define CopyFields(fields) CSVCopyFields(fields)
#define FieldsNumber(fields) CSVGetFieldArrayNumber(fields)

/***
 * 	CSVReadFile / CSVReadFileWithSeparator
 *
 *	read en entire file into an array of CSV fields lines
 */
char ***_internal_CSVReadFile(char *filename, int *nb_lines, char separator)
{
	#undef FUNC
	#define FUNC "CSVReadFile"

	char ***csv_data=NULL;
	char **csv_line;
	char *buffer=NULL;
	int idx=0,maxidx=0;

	*nb_lines=0;
	while ((buffer=FileReadLine(filename))!=NULL) {
		csv_line=CSVGetAllFields(buffer,separator);
		ObjectArrayAddDynamicValueConcat((void **)csv_data,&idx,&maxidx,(void *)csv_line,sizeof(char **));
		*nb_lines=*nb_lines+1;
	}
	return csv_data;
}
#define CSVReadFile(filename,nb_lines) _internal_CSVReadFile(filename,nb_lines,';')
#define CSVReadFileWithSeparator _internal_CSVReadFile

/***
 * 	CSVFreeData
 *
 *	Free an array of CSV fields lines
 */
void CSVFreeData(char ***csv_lines)
{
	#undef FUNC
	#define FUNC "CSVFreeData"

	int l=0,c;

	if (csv_lines) {
		while (csv_lines[l]) {
			CSVFreeFields(csv_lines[l]);
			l++;
		}
	}
}

/***
	GetTxtDate
	
	input: time offset in second
	output: date in DD.MM.YYYY;HHhMMmSSs format
*/
char *GetTxtDate(long dek)
{
	#undef FUNC
	#define FUNC "GetTxtDate"
	
	char *txtdate;
#ifdef OS_WIN
	time_t l_time;
#else
	long l_time;
#endif
	struct tm *timestruct;
	
	txtdate=MemMalloc(21);
#ifdef OS_WIN
	dek=0;
  	time(&l_time);
#else
  	l_time = time(&dek);
#endif
	timestruct = localtime( &l_time);
  
	sprintf(txtdate,"%02d.%02d.%d;%02dh%02dm%02ds"       ,
                                     timestruct->tm_mday       ,
                                     timestruct->tm_mon+1      ,
                                     timestruct->tm_year+1900  ,
                                     timestruct->tm_hour       ,
                                     timestruct->tm_min        ,
                                     timestruct->tm_sec);
	return txtdate;
}
#define GetTxtCurrentDate() GetTxtDate(0)
int GetYear(long dek)
{
	struct tm *timestruct;
#ifdef OS_WIN
	time_t l_time;
	dek=0;
  	time(&l_time);
#else
	long l_time;
  	l_time = time(&dek);
#endif
	timestruct=localtime(&l_time);
	return timestruct->tm_year+1900;
}
#define GetCurrentYear() GetYear(0)
int GetMonth(long dek)
{
	struct tm *timestruct;
#ifdef OS_WIN
	time_t l_time;
	dek=0;
  	time(&l_time);
#else
	long l_time;
  	l_time = time(&dek);
#endif
	timestruct=localtime(&l_time);
	return timestruct->tm_mon+1;
}
#define GetCurrentMonth() GetMonth(0)
int GetDay(long dek)
{
	struct tm *timestruct;
#ifdef OS_WIN
	time_t l_time;
	dek=0;
  	time(&l_time);
#else
	long l_time;
  	l_time = time(&dek);
#endif
	timestruct=localtime(&l_time);
	return timestruct->tm_mday;
}
#define GetCurrentDay() GetDay(0)
int GetHour(long dek)
{
	struct tm *timestruct;
#ifdef OS_WIN
	time_t l_time;
	dek=0;
  	time(&l_time);
#else
	long l_time;
  	l_time = time(&dek);
#endif
	timestruct=localtime(&l_time);
	return timestruct->tm_hour;
}
#define GetCurrentHour() GetDay(0)
int GetMinute(long dek)
{
	struct tm *timestruct;
#ifdef OS_WIN
	time_t l_time;
	dek=0;
  	time(&l_time);
#else
	long l_time;
  	l_time = time(&dek);
#endif
	timestruct=localtime(&l_time);
	return timestruct->tm_min;
}
#define GetCurrentMinute() GetDay(0)
int GetSecond(long dek)
{
	struct tm *timestruct;
#ifdef OS_WIN
	time_t l_time;
	dek=0;
  	time(&l_time);
#else
	long l_time;
  	l_time = time(&dek);
#endif
	timestruct=localtime(&l_time);
	return timestruct->tm_sec;
}
#define GetCurrentSecond() GetDay(0)


/***
	CheckDateFormat

	check that a date is well formated	
	input: a date, formated DD.MM.YYYY;HHhMMmSSs
	output: 0 if NOK, 1 if OK
*/

#define IS_LEAP_YEAR(year) (!(year % 4) && ((year % 100) || !(year % 400)))
#define A_LEAP_YEAR (366*24*3600)
#define A_YEAR (365*24*3600)
#define A_DAY (24*3600)

int CheckDateFormat(char *curdate)
{
	#undef FUNC
	#define FUNC "CheckDateFormat"
	
	char *wdate;
	int ddiff,bi;
	int day,month,year,hour,minute,second;
	
	/* check for digit */
	if (strlen(curdate)!=20) {logerr("wrong date format (must be 20 characters) [%s]",curdate);return 0;}
	
	if (!isdigit(curdate[0]) || !isdigit(curdate[1])
		|| !isdigit(curdate[3]) || !isdigit(curdate[4])
		|| !isdigit(curdate[6]) || !isdigit(curdate[7]) || !isdigit(curdate[8]) || !isdigit(curdate[9])
		|| !isdigit(curdate[11]) || !isdigit(curdate[12])
		|| !isdigit(curdate[14]) || !isdigit(curdate[15])
		|| !isdigit(curdate[17]) || !isdigit(curdate[18]))
		{logerr("wrong date format (missing digits) [%s]",curdate);return 0;}

	if (isdigit(curdate[2]) || isdigit(curdate[5]) || isdigit(curdate[10]) || isdigit(curdate[13]) || isdigit(curdate[16]) || isdigit(curdate[19]))
		{logerr("wrong date format (avoid digits out of the date mask DD.MM.YYYY hh.mm.ss.) [%s]",curdate);return 0;}
	
	wdate=TxtStrDup(curdate);
	wdate[2]=wdate[5]=wdate[10]=wdate[13]=wdate[16]=wdate[19]=0;
	day=atoi(&wdate[0]);
	month=atoi(&wdate[3]);
	year=atoi(&wdate[6]);
	hour=atoi(&wdate[11]);
	minute=atoi(&wdate[14]);
	second=atoi(&wdate[17]);
	MemFree(wdate);
	
	/* check day & month */
	if (day<1) {
		logerr("wrong date format, day cannot be less than 1 [%s]",curdate);
		return 0;
	}
	switch (month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (day>31) {logerr("wrong date format (31 days max) [%s]",curdate);return 0;}
			break;
		case 2:
			if (day>28+IS_LEAP_YEAR(year)) {logerr("wrong date format (%d days max this year) [%s]",28+IS_LEAP_YEAR(year),curdate);return 0;}
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			if (day>30) {logerr("wrong date format (30 days max) [%s]",curdate);return 0;}
			break;
		default:
			logerr("wrong date format (month must be between 1 and 12, included) [%s]",curdate);
			return 0;
	}
	
	/* check time */
	if (hour>24 || minute>60 || second>60) {logerr("wrong date format (time is incorrect) [%s]",curdate);return 0;}
	
	return 1;
}

/***
	ConvertDate
	
	input: A date in an unknown format
	       the mask of this date
	output: same date, with the output mask
*/
char *ConvertDate(char *rawdate,char *input_mask, char *output_mask)
{
	#undef FUNC
	#define FUNC "ConvertDate"

	char newdate[256];
	char tmptext[16];
	char tmpdate[21];
	int day,month,year,hour,minute,second;
	int i,l;
	
	/* may be blank */
	day=month=year=0;
	hour=minute=second=0;
	
	l=strlen(input_mask);
	i=0;
	while (i<l)
	{
		/* DD MM YYYY hh mm ss */
		/* YY DD MM */
		switch (input_mask[i])
		{
			case 'D':day=day*10+rawdate[i]-'0';break;
			case 'M':month=month*10+rawdate[i]-'0';break;
			case 'Y':year=year*10+rawdate[i]-'0';break;
			case 'h':hour=hour*10+rawdate[i]-'0';break;
			case 'm':minute=minute*10+rawdate[i]-'0';break;
			case 's':second=second*10+rawdate[i]-'0';break;
			default:break;
		}
		i++;		
	}
	if (year<100) year+=2000;
	
	sprintf(tmpdate,"%02d %02d %04d %02d %02d %02d ",day,month,year,hour,minute,second);
	CheckDateFormat(tmpdate);

	l=strlen(output_mask);
	strcpy(newdate,"");
	i=0;
	while (i<l)
	{
		if (output_mask[i]=='%')
		{
			switch (output_mask[++i])
			{
				case 'D':sprintf(tmptext,"%02d",day);break;
				case 'M':sprintf(tmptext,"%02d",month);break;
				case 'Y':sprintf(tmptext,"%04d",year);break;
				case 'y':sprintf(tmptext,"%02d",year-2000);break;
				case 'h':sprintf(tmptext,"%02d",hour);break;
				case 'm':sprintf(tmptext,"%02d",minute);break;
				case 's':sprintf(tmptext,"%02d",second);break;
				case '%':sprintf(tmptext,"%%");break;
				default:logerr("unsupported date output format: you can use %%D %%M %%Y %%y %%h %%m %%s %%%%");
					exit(ABORT_ERROR);
			}
		}
		else
			sprintf(tmptext,"%c",output_mask[i]);
		
		strcat(newdate,tmptext);
		i++;
	}
	return TxtStrDup(newdate);
}


/***
	GetDiffDate
	
	input: two dates, formated DD.MM.YYYY;HHhMMmSSs
	output: difference in seconds
*/
long long GetDiffDate(char *curdate, char *zedate)
{
	#undef FUNC
	#define FUNC "GetDiffDate"
	
	static int monthcount[12]={0,31,59,90,120,151,181,212,243,273,304,334};
	unsigned long long stime1,stime2;
	char *wdate;
	int i;
	int day,month,year,hour,minute,second;
	int day2,month2,year2,hour2,minute2,second2;
	
	
	/* check correct format of the date */
	if (!CheckDateFormat(curdate) || !CheckDateFormat(zedate))
		exit(ABORT_ERROR);

	wdate=TxtStrDup(curdate);
	wdate[2]=wdate[5]=wdate[10]=wdate[13]=wdate[16]=0;
	day=atoi(&wdate[0]);
	month=atoi(&wdate[3]);
	year=atoi(&wdate[6]);
	hour=atoi(&wdate[11]);
	minute=atoi(&wdate[14]);
	second=atoi(&wdate[17]);
	MemFree(wdate);
		
	wdate=TxtStrDup(zedate);
	wdate[2]=wdate[5]=wdate[10]=wdate[13]=wdate[16]=0;
	day2=atoi(&wdate[0]);
	month2=atoi(&wdate[3]);
	year2=atoi(&wdate[6]);
	hour2=atoi(&wdate[11]);
	minute2=atoi(&wdate[14]);
	second2=atoi(&wdate[17]);
	MemFree(wdate);

	/* year offsets refer to 2000, no incidence on leap year calculation 
	   this give us a compatiblity until 2068 when compiled on 32 bits architecture...
	*/
	year-=2000;
	year2-=2000;

	stime1=second+minute*60LL+hour*3600LL+(day+monthcount[month-1])*3600LL*24LL;
	stime2=second2+minute2*60LL+hour2*3600LL+(day2+monthcount[month2-1])*3600LL*24LL;
	
	/* leap year adjustment over the years */
	i=0;
	while (i<year)
	{
		if IS_LEAP_YEAR(i) stime1+=366*24*3600; else stime1+=365*24*3600;
		i++;
	}
	if IS_LEAP_YEAR(year) if (month>2) stime1+=3600*24;
	i=0;
	while (i<year2)
	{
		if IS_LEAP_YEAR(i) stime2+=366*24*3600; else stime2+=365*24*3600;
		i++;
	}
	if IS_LEAP_YEAR(year2) if (month2>2) stime2+=3600*24;
	
	return stime1-stime2;
}




/*****************  XML related functions *****************/

struct s_xml_field
{
	char *xml_name;
	char **xml_attribute;
	char **xml_attribute_value;
	char *xml_value;
	char *xml_cdata;
	char *xml_comment;
	
	struct s_xml_field **child;
	int nb_child;
	struct s_xml_field *parent;
	char **xml_namespace;
	int auto_closed;
	int definition;
	int cdata;
	int comment;
};

char *XMLMakeCDATASection(char *cdata)
{
	#undef FUNC
	#define FUNC "XMLMakeCDATASection"

	return TxtReplace(cdata,"]]>","]]]]><![CDATA[>",0);
}
/***
	XMLDumpTreeRecurse
	
	follow an XML tree and display all fields, with identation
*/
void _internal_XMLDumpTreeRecurse(FILE *id, struct s_xml_field *zefield,int zetab)
{
	#undef FUNC
	#define FUNC "_internal_XMLDumpTreeRecurse"
	int i;
	char *tmp_cdata=NULL;

	if (zefield->cdata) {
		tmp_cdata=XMLMakeCDATASection(zefield->xml_cdata);
		fprintf(id,"%*.*s<!CDATA[[%s]]>\n",zetab,zetab,"",zefield->xml_cdata);
	} else if (zefield->comment) {
		fprintf(id,"%*.*s<!--%s-->\n",zetab,zetab,"",zefield->xml_comment);
	} else {
		/* marker */
		fprintf(id,"%*.*s<%s",zetab,zetab,"",zefield->xml_name);
		/* attributes */
		if (zefield->xml_attribute) {
			if (zefield->definition) {
				fprintf(id," %s",zefield->xml_attribute[0]);
			} else {
				for (i=0;zefield->xml_attribute[i];i++) {
					fprintf(id," %s=\"%s\"",zefield->xml_attribute[i],zefield->xml_attribute_value[i]);
				}
			}
		}
		/* data */
		if (!(zefield->auto_closed && !zefield->definition)) {
			if (zefield->definition) {
				fprintf(id,">\n");
				zetab-=3;
				if (zetab<0) zetab=0;
			} else {
				fprintf(id,">%s",zefield->xml_value);
			}
			/* childs */
			if (zefield->nb_child) fprintf(id,"\n");
			for (i=0;i<zefield->nb_child;i++)
				_internal_XMLDumpTreeRecurse(id,zefield->child[i],zetab+3);
			if (!zefield->definition) {
				if (zefield->nb_child) fprintf(id,"%*.*s",zetab,zetab,"");
				fprintf(id,"</%s>\n",zefield->xml_name);
			}
		} else {
			fprintf(id,"/>\n");
		}
	}
}
void _internal_XMLDumpTree(char *filename, struct s_xml_field *zefield)
{
	#undef FUNC
	#define FUNC "XMLDumpTree/XMLWriteFile"
	int i;
	FILE *last_id=NULL;
	
	if (filename) {
		last_id=FileOpen(filename,"a+");
	} else {
		last_id=stdout;
	}

	for (i=0;i<zefield->nb_child;i++)
		_internal_XMLDumpTreeRecurse(last_id,zefield->child[i],0);

	if (filename) {
		FileClose(last_id);
	}
}
#define XMLDumpTree(zefield) _internal_XMLDumpTree(NULL,zefield)
#define XMLWriteFile(filename,zefield) _internal_XMLDumpTree(filename,zefield)

/***
	XMLSetField
	
	put a name and a value in a XML field structure
	
	input: field structure
	       name
	       text value
*/
void XMLSetField(struct s_xml_field *zefield,char *zename, char *zevalue)
{
	#undef FUNC
	#define FUNC "XMLSetField"

	MemFree(zefield->xml_name);
	MemFree(zefield->xml_value);
	zefield->xml_name=TxtStrDup(zename);
	zefield->xml_value=TxtStrDup(zevalue);
}

/***
	XMLAddChild
	
	add a XML child to another XML field
	
	input: XML field structure of the parent
	       XML field structure of the child
*/
void XMLAddChild(struct s_xml_field *parent,struct s_xml_field *child)
{
	#undef FUNC
	#define FUNC "XMLAddChild"
	
	parent->child=MemRealloc(parent->child,sizeof(struct s_xml_field *)*(parent->nb_child+1));
	parent->child[parent->nb_child]=child;
	parent->nb_child++;
	
	child->parent=parent;
}
/*** 
	XMLCreateField
	
	create a new XML field structure, featuring a name and a text value

*/
struct s_xml_field *XMLCreateField(char *zename, char **zeattributes, char **zeattributesvalues, char *zevalue, char *zecdata, char *zecomment,int auto_closed, int definition, int cdata, int comment)
{
	#undef FUNC
	#define FUNC "XMLCreateField"
	
	struct s_xml_field *curfield;
	char **parsed_attributes=NULL;
	
	curfield=MemCalloc(sizeof(struct s_xml_field));
	
	curfield->xml_name=TxtStrDup(zename);

	curfield->xml_attribute=zeattributes;
	curfield->xml_attribute_value=zeattributesvalues;

	/* deprecated
	if (!definition || !zeattributes) {
		XMLParseAttribute(zeattributes,&curfield->xml_attribute,&curfield->xml_attribute_value);
	} else {
		// definition tags must use another parser
		FieldArrayAddDynamicValue(&curfield->xml_attribute,zeattributes);
		FieldArrayAddDynamicValue(&curfield->xml_attribute_value,"");
	}*/
	curfield->xml_value=TxtStrDup(zevalue);
	if (cdata) {
		curfield->xml_cdata=TxtStrDup(zecdata);
	} else curfield->xml_cdata=NULL;
	if (comment) {
		curfield->xml_comment=TxtStrDup(zecomment);
	} else curfield->xml_comment=NULL;
	curfield->child=NULL;
	curfield->parent=NULL;
	curfield->xml_namespace=NULL;
	curfield->nb_child=0;
	curfield->definition=definition;
	curfield->auto_closed=auto_closed;
	curfield->cdata=cdata;
	curfield->comment=comment;
	
	return curfield;
}
#define XMLCreateBlankField(zename) XMLCreateField(zename,NULL,NULL,"",NULL,NULL,1,1,0,0)
#define XMLCreateSimpleField(zename,zevalue) XMLCreateField(zename,NULL,NULL,zevalue,NULL,NULL,1,0,0,0)
#define XMLCreateAttributeField(zename,zeattributes,zeattributesvalues) XMLCreateField(zename,zeattributes,zeattributesvalues,"",NULL,NULL,1,0,0,0)
#define XMLCreateOpenedAttributeField(zename,zeattributes,zeattributesvalues) XMLCreateField(zename,zeattributes,zeattributesvalues,"",NULL,NULL,0,0,0,0)
struct s_xml_field *_internal_XMLCreateFieldWithAttributeList(int simple, char *zename, ...)
{
	#undef FUNC
	#define FUNC "XMLCreateFieldWithAttributeList"

	va_list attribute_list;
	char *attribute_name,*attribute_value;
	char **attributes=NULL,**attributesvalues=NULL;
	int attridx,attrmax,attrvidx,attrvmax;

	va_start(attribute_list,zename);
	attribute_name=va_arg(attribute_list,char *);
	while (attribute_name!=NULL) {
		attribute_value=va_arg(attribute_list,char *);
		FieldArrayAddDynamicValueConcat(&attributes,&attridx,&attrmax,attribute_name);
		FieldArrayAddDynamicValueConcat(&attributesvalues,&attrvidx,&attrvmax,attribute_value);
		attribute_name=va_arg(attribute_list,char *);
	}
	if (simple)
		return XMLCreateOpenedAttributeField(zename,attributes,attributesvalues);
	else
		return XMLCreateAttributeField(zename,attributes,attributesvalues);
}
#define XMLCreateFieldWithAttributeList(...)  _internal_XMLCreateFieldWithAttributeList(0,__VA_ARGS__)
#define XMLCreateOpenedFieldWithAttributeList(...)  _internal_XMLCreateFieldWithAttributeList(1,__VA_ARGS__)

void XMLFieldAddAttribute(struct s_xml_field *curfield, char *attr_name, char *attr_value)
{
	#undef FUNC
	#define FUNC "XMLFieldAddAttribute"
	FieldArrayAddDynamicValue(&curfield->xml_attribute,attr_name);
	FieldArrayAddDynamicValue(&curfield->xml_attribute_value,attr_value);
}
void XMLFieldAddAttributeLong(struct s_xml_field *curfield, char *attr_name, long attr_value)
{
	#undef FUNC
	#define FUNC "XMLFieldAddAttributeLong"
	char long_value[128];
	sprintf(long_value,"%ld",attr_value);
	FieldArrayAddDynamicValue(&curfield->xml_attribute,attr_name);
	FieldArrayAddDynamicValue(&curfield->xml_attribute_value,long_value);
}
void XMLFieldAddAttributeDouble(struct s_xml_field *curfield, char *attr_name, double attr_value)
{
	#undef FUNC
	#define FUNC "XMLFieldAddAttributeDouble"
	char double_value[128];
	sprintf(double_value,"%lf",attr_value);
	FieldArrayAddDynamicValue(&curfield->xml_attribute,attr_name);
	FieldArrayAddDynamicValue(&curfield->xml_attribute_value,double_value);
}
void XMLFieldAddAttributeList(struct s_xml_field *curfield, ...)
{
	#undef FUNC
	#define FUNC "XMLFieldAddAttributeList"
	va_list attribute_list;
	char *attribute_name,*attribute_value;
	/* surely we can optimise with concat to retrieve end of list only once -> TODO */
	va_start(attribute_list,curfield);
	attribute_name=va_arg(attribute_list,char *);
	while (attribute_name!=NULL) {
		attribute_value=va_arg(attribute_list,char *);
		FieldArrayAddDynamicValue(&curfield->xml_attribute,attribute_name);
		FieldArrayAddDynamicValue(&curfield->xml_attribute_value,attribute_value);
		attribute_name=va_arg(attribute_list,char *);
	}
}
void XMLFieldAddAttributeListLong(struct s_xml_field *curfield, ...)
{
	#undef FUNC
	#define FUNC "XMLFieldAddAttributeListLong"
	va_list attribute_list;
	char *attribute_name,attribute_value[128];
	long attr_long;
	/* surely we can optimise with concat to retrieve end of list only once -> TODO */
	va_start(attribute_list,curfield);
	attribute_name=va_arg(attribute_list,char *);
	while (attribute_name!=NULL) {
		attr_long=va_arg(attribute_list,long);
		sprintf(attribute_value,"%ld",attr_long);
		FieldArrayAddDynamicValue(&curfield->xml_attribute,attribute_name);
		FieldArrayAddDynamicValue(&curfield->xml_attribute_value,attribute_value);
		attribute_name=va_arg(attribute_list,char *);
	}
}
void XMLFieldAddAttributeListDouble(struct s_xml_field *curfield, ...)
{
	#undef FUNC
	#define FUNC "XMLFieldAddAttributeListDouble"
	va_list attribute_list;
	char *attribute_name,attribute_value[128];
	double attr_double;
	/* surely we can optimise with concat to retrieve end of list only once -> TODO */
	va_start(attribute_list,curfield);
	attribute_name=va_arg(attribute_list,char *);
	while (attribute_name!=NULL) {
		attr_double=va_arg(attribute_list,double);
		sprintf(attribute_value,"%lf",attr_double);
		FieldArrayAddDynamicValue(&curfield->xml_attribute,attribute_name);
		FieldArrayAddDynamicValue(&curfield->xml_attribute_value,attribute_value);
		attribute_name=va_arg(attribute_list,char *);
	}
}


/***
 *	XMLDuplicateField
 *
 *	duplicate a single XML field
 */
struct s_xml_field *XMLDuplicateField(struct s_xml_field *zefield)
{
	#undef FUNC
	#define FUNC "XMLDuplicateField"

	struct s_xml_field *curfield;

	if (!zefield) return NULL;
	
	curfield=MemCalloc(sizeof(struct s_xml_field));
	curfield->xml_name=TxtStrDup(zefield->xml_name);
	curfield->xml_attribute=CopyFields(zefield->xml_attribute);
	curfield->xml_attribute_value=CopyFields(zefield->xml_attribute_value);
	curfield->xml_value=TxtStrDup(zefield->xml_value);
	if (zefield->cdata) {
		curfield->xml_cdata=TxtStrDup(zefield->xml_cdata);
	} else curfield->xml_cdata=NULL;
	if (zefield->comment) {
		curfield->xml_comment=TxtStrDup(zefield->xml_comment);
	} else curfield->xml_comment=NULL;
	curfield->child=NULL;
	curfield->parent=zefield->parent;
	curfield->xml_namespace=CopyFields(zefield->xml_namespace);
	curfield->nb_child=0;
	curfield->definition=zefield->definition;
	curfield->auto_closed=zefield->auto_closed;
	curfield->cdata=zefield->cdata;
	curfield->comment=zefield->comment;

	return curfield;
}
/***
 *	XMLDuplicateFieldRecurse
 *
 * 	duplicate a full XML tree
 */
struct s_xml_field *XMLDuplicateFieldRecurse(struct s_xml_field *zefield)
{
	#undef FUNC
	#define FUNC "XMLDuplicateFieldRecurse"

	struct s_xml_field *curfield,*curchild;
	int i;

	if (!zefield) return NULL;
	
	curfield=XMLDuplicateField(zefield);
	for (i=0;i<zefield->nb_child;i++) {
		curchild=XMLDuplicateFieldRecurse(zefield->child[i]);
		XMLAddChild(curfield,curchild);
	}
	return curfield;
}

/***
	XMLFreeField
	
	free the memory of a XML field
	
	input: XML field structure
*/
void XMLFreeField(struct s_xml_field *xml_field)
{
	#undef FUNC
	#define FUNC "XMLFreeField"
	
	int i;
	
	/* free all childs */
	for (i=0;i<xml_field->nb_child;i++) {
		XMLFreeField(xml_field->child[i]);
	}
	if (i) {
		MemFree(xml_field->child);
	}
	FreeFields(xml_field->xml_attribute);
	FreeFields(xml_field->xml_attribute_value);
	FreeFields(xml_field->xml_namespace);
	if (xml_field->xml_value) {
		MemFree(xml_field->xml_value);
	}
	if (xml_field->xml_cdata) {
		MemFree(xml_field->xml_cdata);
	}
	if (xml_field->xml_comment) {
		MemFree(xml_field->xml_comment);
	}
	MemFree(xml_field->xml_name);
	MemFree(xml_field);
}
/***
	XMLDeleteChild
	
	delete a child from his parent

	input: XML field structure of the parent
	       XML field structure of the child
*/
void XMLDeleteChild(struct s_xml_field *parent,struct s_xml_field *child)
{
	#undef FUNC
	#define FUNC "XMLDeleteChild"
	
	int i,ok=0;
	
	if (parent) {
		for (i=0;i<parent->nb_child;i++) {
			if (parent->child[i]==child)
			{
				XMLFreeField(child);
				parent->nb_child--;
				if (i!=parent->nb_child)
					parent->child[i]=parent->child[parent->nb_child];
				parent->child=MemRealloc(parent->child,sizeof(struct s_xml_field *)*(parent->nb_child+1));
				ok=1;
			}
		}
	}
	if (!ok)
	{
		logerr("XML child was not found");
		logerr("parent: <%s>%s</%s>",parent->xml_name,parent->xml_value,parent->xml_name);
		logerr("child : <%s>%s</%s>",child->xml_name,child->xml_value,child->xml_name);
		exit(INTERNAL_ERROR);
	}	
}

/***
	XMLPurgeMarker

	this function delete every XML marker of a string and
	replace markers by spaces then feature a full trim of the string
	
	example	before: <cursorx>pouet 56</cursorx>gnagna<plop><xml=youpi>glapi</plop>
	example after : pouet 56 gnagna glapi
	
	input: a string
	output: the pointer to this string, modified
*/
char *XMLPurgeMarker(char *in_str)
{
	#undef FUNC
	#define FUNC "XMLPurgeMarker"
	
	int idx,l;
	int marker;
	
	idx=0;
	l=strlen(in_str);
	while (in_str[idx]!=0)
	{
		if (in_str[idx]=='<')
			marker=1;

		if (marker)
		{
			if (in_str[idx]=='>')
				marker=0;
			in_str[idx]=' ';
		}
		idx++;
	}
	TxtTrim(in_str);
	return in_str;
}


struct s_xml_field *XMLGetField(struct s_xml_field *zefield, char *zepath)
{
	#undef FUNC
	#define FUNC "XMLGetField"

	int idxstart=0,idxend,i;
	char *separator;

	if (!zefield) return NULL;
	
	while ((separator=strchr(zepath+idxstart,'>'))!=NULL) {
		idxend=separator-zepath;
		for (i=0;i<zefield->nb_child;i++)
			if (!strncmp(zefield->child[i]->xml_name,zepath+idxstart,idxend-idxstart) && strlen(zefield->child[i]->xml_name)==idxend-idxstart) {
				break;
			}
		if (i==zefield->nb_child) {
			return NULL;
		}
		zefield=zefield->child[i];
		idxstart=idxend+1;
	}
	for (i=0;i<zefield->nb_child;i++)
		if (!strcmp(zefield->child[i]->xml_name,zepath+idxstart)) {
			break;
		}
	if (i==zefield->nb_child) {
		return NULL;
	}
	return zefield->child[i];
}
char *XMLGetFieldValue(struct s_xml_field *zefield, char *zepath)
{
	#undef FUNC
	#define FUNC "XMLGetFieldValue"

	struct s_xml_field *curfield;
	curfield=XMLGetField(zefield,zepath);
	if (curfield) {
		return curfield->xml_value;
	} else {
		return "";
	}
}

struct s_xml_field *XMLGetFieldAttr(struct s_xml_field *zefield, char *zepath, char *attr, char *attr_value)
{
	#undef FUNC
	#define FUNC "XMLGetFieldAttr"

	int idxstart=0,idxend,i,iattr=0;
	char *separator;

	if (!zefield) return NULL;
	
	while ((separator=strchr(zepath+idxstart,'>'))!=NULL) {
			idxend=separator-zepath;
			for (i=0;i<zefield->nb_child;i++)
					if (!strncmp(zefield->child[i]->xml_name,zepath+idxstart,idxend-idxstart) && strlen(zefield->child[i]->xml_name)==idxend-idxstart) {
							break;
					}
			if (i==zefield->nb_child) {
					return NULL;
			}
			zefield=zefield->child[i];
			idxstart=idxend+1;
	}
	for (i=0;i<zefield->nb_child;i++) {
			if (!strcmp(zefield->child[i]->xml_name,zepath+idxstart)) {
					for (iattr=0;zefield->child[i]->xml_attribute[iattr];iattr++) {
							if (!strcmp(attr,zefield->child[i]->xml_attribute[iattr])) {
									if (!strcmp(zefield->child[i]->xml_attribute_value[iattr],attr_value)) {
						return zefield->child[i];
				}
							}
					}
			}
	}
	return NULL;
}

char *XMLGetFieldAttrValueFromField(struct s_xml_field *zefield, char *attr)
{
	#undef FUNC
	#define FUNC "XMLGetFieldAttrValue"

	int iattr;

	if (!zefield) return "";
	
	for (iattr=0;zefield->xml_attribute[iattr];iattr++) {
		if (!strcmp(attr,zefield->xml_attribute[iattr])) {
			return zefield->xml_attribute_value[iattr];
		}
	}
	return "";
}

char *XMLGetFieldAttrValue(struct s_xml_field *zefield, char *zepath, char *attr)
{
	#undef FUNC
	#define FUNC "XMLGetFieldAttrValue"

	int idxstart=0,idxend,i,iattr=0,sepflag=0;
	char *separator;

	if (!zefield) return "";
	
	while ((separator=strchr(zepath+idxstart,'>'))!=NULL) {
		idxend=separator-zepath;
		for (i=0;i<zefield->nb_child;i++)
			if (!strncmp(zefield->child[i]->xml_name,zepath+idxstart,idxend-idxstart) && strlen(zefield->child[i]->xml_name)==idxend-idxstart) {
				break;
			}
		if (i==zefield->nb_child) {
				return "";
		}
		zefield=zefield->child[i];
		idxstart=idxend+1;
		sepflag=1;
	}
	/* if there is no separator, we must find the right child anyway */
	if (!sepflag) {
		for (i=0;i<zefield->nb_child;i++)
			if (!strcmp(zefield->child[i]->xml_name,zepath)) {
				break;
			}
		if (i==zefield->nb_child) {
			return "";
		}
		zefield=zefield->child[i];
	}
	if (zefield->xml_attribute) {
		for (iattr=0;zefield->xml_attribute[iattr];iattr++) {
			if (!strcmp(attr,zefield->xml_attribute[iattr])) {
				return zefield->xml_attribute_value[iattr];
			}
		}
	}
	return "";
}

struct s_xml_field *XMLGetFieldMulti(struct s_xml_field *zefield, char *zepath, int *nb)
{
	#undef FUNC
	#define FUNC "XMLGetFieldMulti"

	struct s_xml_field *xml_fields=NULL;
	int idxstart=0,idxend,i;
	int maxv=0;
	char *separator;

	*nb=0;
	if (!zefield) return NULL;

	while ((separator=strchr(zepath+idxstart,'>'))!=NULL) {
		idxend=separator-zepath;
		for (i=0;i<zefield->nb_child;i++)
			if (!strncmp(zefield->child[i]->xml_name,zepath+idxstart,idxend-idxstart) && strlen(zefield->child[i]->xml_name)==idxend-idxstart) {
				break;
			}
		if (i==zefield->nb_child) {
			return NULL;
		}
		zefield=zefield->child[i];
		idxstart=idxend+1;
	}
	for (i=0;i<zefield->nb_child;i++)
		if (!strcmp(zefield->child[i]->xml_name,zepath+idxstart)) {
			ObjectArrayAddDynamicValueConcat((void **)&xml_fields,nb,&maxv,zefield->child[i],sizeof(struct s_xml_field));
		}
	return xml_fields;
}

/***
	XMLLookForFieldByName
	
	return the first child of a XML root with the requested name
	
	input: XML field structure of the root
	       XML name of the field
*/
struct s_xml_field *XMLLookForFieldByName(struct s_xml_field *zefield, char *xmlname)
{
	#undef FUNC
	#define FUNC "XMLLookForFieldByName"
	
	int idx;
	
	for (idx=0;idx<zefield->nb_child;idx++)
		if (!strcmp(zefield->child[idx]->xml_name,xmlname))
			return zefield->child[idx];
		else
		if ((zefield=XMLLookForFieldByName(zefield->child[idx],xmlname))!=NULL)
			return zefield;
	return NULL;
}

/***
	XMLLookForFieldByValue
	
	return the first child of a XML root with the requested value
*/
struct s_xml_field *XMLLookForFieldByValue(struct s_xml_field *zefield, char *xmlvalue)
{
	#undef FUNC
	#define FUNC "XMLLookForFieldByValue"
	
	int idx;
	
	for (idx=0;idx<zefield->nb_child;idx++)
		if (!strcmp(zefield->child[idx]->xml_value,xmlvalue))
			return zefield->child[idx];
		else
		if ((zefield=XMLLookForFieldByValue(zefield->child[idx],xmlvalue))!=NULL)
			return zefield;
	return NULL;
}


/* RFC XML http://www.w3.org/TR/xml/#sec-common-syn
  *         http://www.w3.org/TR/xml/#NT-Char
  *
*/
int XMLTestFirstChar(unsigned char c) {
	if ((c>='A' && c<='Z') || (c>='a' && c<='z') || c==':' || c=='_' || (c>=0xC0 && c<=0xD6) || (c>=0xD8 && c<=0xF6) || c>=0xF8)
		return 1;
	else return 0;
}
int XMLTestChar(unsigned char c) {
	if ((c>='A' && c<='Z') || (c>='a' && c<='z') || c==':' || c=='_' || (c>=0xC0 && c<=0xD6) || (c>=0xD8 && c<=0xF6) || c>=0xF8 || c=='-' || c=='.' || (c>='0' && c<='9') || c==0xB7)
		return 1;
	else return 0;
}
int XMLTestCDATAChar(unsigned char c) {
	if (c==0x09 || c==0x0A || c==0x0D || c>=0x20)
		return 1;
	else return 0;
}

/***
	XMLLoadFile

	load an entire xml file into a XML tree
	
	input: name of the xml file
	output: xml root structure
*/
void _internal_XMLCheckSpace(char **zespace, int idx, int *zesize)
{
	#undef FUNC
	#define FUNC "_internal_XMLCheckSpace"

	if (idx>=*zesize) {
		while (idx>=*zesize) *zesize=16+*zesize*2;
		*zespace=MemRealloc(*zespace,*zesize);
	}
}

#define XML_EXIT {logerr("buffer=[%-50.50s]",buffer+idx);FileReadClose(filename);XMLFreeField(xmlroot);MemFree(buffer);MemFree(zComment);MemFree(zCdata);MemFree(zElem);MemFree(zAttr);MemFree(zVal);return NULL;}

struct s_xml_field *XMLLoadFile(char *filename)
{
	#undef FUNC
	#define FUNC "XMLLoadFile"

	#define XML_BLOCK_SIZE 65536

	/* parser v3.5 */
	
	struct s_xml_field *xmlroot,*curfield,*child,*checkfield;
	char *buffer;

	char *zComment=NULL;int icomment,maxcomment=0;
	char *zCdata=NULL;  int icdata,maxcdata=0;
	char *zElem=NULL;   int ielem,maxelem=0;
	char *zAttr=NULL;   int iattr,maxattr=0;
	char *zVal=NULL;    int ival,maxval=0;
	char **attributes=NULL;
	char **attributesvalues=NULL;
	char **namespaces=NULL;
	int xml_string_ok,xml_block_size,empty_marker,auto_closed;
	int opened_tag,opened_cdata,opened_comment;
	int closed_tag,space_encountered;
	int cdata_flag,comment_flag;
	int pos,idx,definition,special_tag;
	int namespacetoggled,namespacedefinitiontoggled;
	int namespacelng,namespaceidx;
	char c;
	int parse_name,parse_value,dobackslash,iverif;
	int pos_name,pos_equal,allow_end_tag,end_tag_code;
	enum e_quote_type quote_type=NO_QUOTE;
	
	curfield=xmlroot=XMLCreateBlankField("XML_ROOT");
	xmlroot->auto_closed=1;
	curfield=xmlroot;

	pos=opened_tag=closed_tag=space_encountered=opened_comment=0;
	icdata=ielem=iattr=ival=icomment=auto_closed=opened_cdata=definition=0;
	cdata_flag=comment_flag=end_tag_code=0;
	allow_end_tag=namespacetoggled=namespacedefinitiontoggled=0;

	buffer=MemMalloc(XML_BLOCK_SIZE);
	xml_block_size=FileReadBinary(filename,buffer,XML_BLOCK_SIZE);

	/* default working size */
	_internal_XMLCheckSpace(&zComment,1024,&maxcomment);
	_internal_XMLCheckSpace(&zCdata,65536,&maxcdata);
	_internal_XMLCheckSpace(&zElem,1024,&maxelem);
	_internal_XMLCheckSpace(&zAttr,1024,&maxattr);
	_internal_XMLCheckSpace(&zVal,1024,&maxval);

	/*	XML machine state
	 *
	 *	comments and CDATA segments have priority over the markers
	 */
	while (xml_block_size)
	{
		xml_string_ok=0;
		for (idx=pos;idx<xml_block_size && !xml_string_ok;idx++) {
			c=buffer[idx];
			//loginfo("idx=%d c=%c allow=%d",idx,c,allow_end_tag);
			/*********************************************************
			 * CDATA segment / http://www.w3.org/TR/xml/#dt-cdsection
			 ********************************************************/
			if (opened_cdata) {
				if (!XMLTestCDATAChar(c)) {
					logerr("Wrong XML file, a CDATA segment has an invalid char  %c (0x%x)",c>0x20?c:' ',c);
					XML_EXIT
				}
				zCdata[icdata++]=c;
				_internal_XMLCheckSpace(&zCdata,icdata,&maxcdata);

				if (icdata>3 && !strncmp(zCdata+icdata-3,"]]>",3)) {
					/* end of CDATA segment */
					auto_closed=1;     /* because CDATA segment is always auto-closed */
					icdata-=3;         /* we do not copy the end of the marker */
					empty_marker=1;    /* CDATA segment is like an empty marker */
					opened_cdata=0;
					closed_tag=1;
					xml_string_ok=1;
					pos=idx+1;         /* parsing will follow next char */
					cdata_flag=1;
				}
			} else {
				/*************************************************
				 * XML Specs chap 2.3 Common Syntactic Constructs
				 * http://www.w3.org/TR/xml/#sec-common-syn
				 *************************************************/
				if (c==0x09 || c == 0x0d || c == 0x0a) c=' ';
				/******************
 				 * COMMENT segment
				 ******************/
				if (opened_comment) {
					if (!XMLTestCDATAChar(c)) {
						logerr("Wrong XML file, a comment has an invalid char %c (0x%x)",c,c);
						XML_EXIT
					}
					/* we are inside the comment unless we find a comment closing tag */
					zComment[icomment++]=c;
					_internal_XMLCheckSpace(&zComment,icomment,&maxcomment);
					if (c=='>' && icomment>=2) {
						/* end tag found */
						if (!strncmp(zComment+icomment-3,"-->",3)) {
							auto_closed=1;
							icomment-=3;    /* do not copy the end of the marker */
							empty_marker=1; /* comment segment is like an empty marker */
							opened_comment=0;
							closed_tag=1;
							xml_string_ok=1;
							pos=idx+1;      /* parsing will follow next char */
							comment_flag=1;
						}
					}
				} else if (!opened_tag) { /* looking for an opening bracket */
				/******************
 				 *     TAG name
				 ******************/
					if (c=='<') {
						special_tag=0;
						opened_tag=1;
					} else if (c=='>') {
						logerr("Wrong XML file, cannot close marker before opening it!");
						XML_EXIT
					}
				} else { /* bracket opened */
					if (!closed_tag) { /* tag not closed, running over element + attribute */
						if (!space_encountered) { /* element */
							if (c==' ') { /* space encountered, switch on attribute */
								space_encountered=1;
								zElem[ielem]='\0';
								/* initialisation of attribute parser */
								parse_name=parse_value=dobackslash=0;
								pos_name=pos_equal=-1;
								quote_type=NO_QUOTE;
							} else {
								if (c=='>') {
									if (ielem && zElem[ielem-1]=='/') { /* auto-closing tag without attribute, we leave */
										ielem--;
										auto_closed=1;
										empty_marker=1;
										xml_string_ok=1;
										pos=idx+1;
									}
									if (zElem[0]=='/') { /* closing tag */
										xml_string_ok=1;
										pos=idx+1;
									}
									if (!ielem) {
										logerr("Wrong XML file, marker has no name!");
										XML_EXIT
									}
									zElem[ielem]='\0';
									closed_tag=1;
									allow_end_tag=0;
								} else {
									if (!ielem && (c=='?' || c=='!')) {
										special_tag=1;
									} else {
										if (allow_end_tag) {
											zElem[ielem]=0;
											logerr("Wrong XML file, the %s tag [%s...] has an invalid char '%c' (0x%x)",special_tag?"special":"",zElem,zElem[ielem-1],zElem[ielem-1]);
											XML_EXIT
										}
										if (!special_tag) {
											/* tag name must conform to RFC */
											if ((!ielem || (ielem==1 && zElem[0]=='/')) && (!XMLTestFirstChar(c) && !(ielem==0 && c=='/'))) {
												logerr("Wrong XML file, the tag cannot start with the char '%c' (0x%x)",c,c);
												XML_EXIT
											} else if (ielem && !XMLTestChar(c)) {
												if (c=='?' || c=='/') {
													/* those two char are allowed only if they are before the end of the tag */
													allow_end_tag=1;
												} else {
													zElem[ielem]=0;
													logerr("Wrong XML file, the tag [%s...] has an invalid char '%c' (0x%x)",zElem,c,c);
													XML_EXIT
												}
											}
										}
										if (c==':') {
											if (namespacetoggled) {
												zElem[ielem]=0;
												logerr("Wrong XML file, the tag [%s:...] has more than one namespace",zElem);
												XML_EXIT
											}
											namespacetoggled=1;
											namespacelng=ielem;
										}
										zElem[ielem++]=c;
										_internal_XMLCheckSpace(&zElem,ielem,&maxelem);
										if (ielem==2 && special_tag && !strncmp(zElem,"--",2)) {
											opened_comment=1;
											icomment=ielem=0;
										} else if (ielem==7 && special_tag && !strncmp(zElem,"[CDATA[",7)) {
											/* CDATA segment is renamed (nicer) */
											icdata=0;
											opened_cdata=1;
											strcpy(zElem,"CDATA");ielem=strlen(zElem);
										}
									}
								}
							}
						} else { /* space encoutered, parsing attributes v3.0+ */
							/******************
							 * TAG attributes
							 ******************/
							/* parsing attributes until '>', except if it is inside quotes or double-quotes */
							if (c=='>' && quote_type==NO_QUOTE) {
								/* /!\ */
								if (end_tag_code) {
									parse_name=0;
									pos_name=-1;
								}
								end_tag_code=0;
								/* checking for unclosed attribute */
								if (pos_name!=-1 || pos_equal!=-1 || parse_name || parse_value) {
									logerr("Wrong XML file, invalid attribute for the tag [%s]",zElem);
									XML_EXIT
								}

								if (iattr && (zAttr[iattr-1]=='/' || zAttr[iattr-1]=='?')) {  /* auto-closed tag with attributes, we leave */
									iattr--;
									auto_closed=1;
									empty_marker=1;
									xml_string_ok=1;
									pos=idx+1;
								}
								closed_tag=1;
							} else {
								if (end_tag_code) {
									logerr("Wrong XML file, tag [%s], char %c is forbidden as attribute name",zElem,end_tag_code);
									XML_EXIT
								}
								zAttr[iattr++]=c;
								_internal_XMLCheckSpace(&zAttr,iattr,&maxattr);
								/* while putting attributes in a global buffer
								 * we manage partitioning of attributes except for ?xml !DOCTYPE */
								if (!special_tag) {
									/* attributes values may use backslash */
									if (dobackslash) {
										dobackslash=0;
									} else if (c=='\\') {
										if (parse_name && !parse_value) {
											logerr("Wrong XML file, tag [%s], attribute name has an invalid char '\\'",zElem);
											XML_EXIT
										}
										dobackslash=1;
									} else if (!parse_name) {
										/* looking for first char of an attribute name
										 * do not confuse with end of special tag */
										if (c!=' ') {
											if (c=='/' || c=='?') {
												/* probably an end of tag */
												end_tag_code=c;
											} else if (c=='=') {
												logerr("Wrong XML file, tag [%s], attribute name cannot be empty",zElem);
												XML_EXIT
											}
											parse_name=1;
											pos_name=iattr-1;
										}
									} else { /* parsing attribute name */
										if (!parse_value) {
											if (c=='=') {
												pos_equal=iattr-1;
												parse_value=1;
											}
											/* is there a namespace in the attribute name? */
											if (c==':') {
												/* manque un contrôle sur le double ':' */
												namespacedefinitiontoggled=1;
											}
										} else { /* parsing attribute value */
											if (iattr==pos_equal+2) {
												if (c!=SINGLE_QUOTE && c!=DOUBLE_QUOTE) {
													logerr("Wrong XML file, tag [%s], attribute value must immediatly follow equal sign with single or double quotes -> %c ou %c",zElem,DOUBLE_QUOTE,SINGLE_QUOTE);
													XML_EXIT
												}
												quote_type=c;
											} else if (c==quote_type) {
												/* we must close the attribute with the same quote type
												 * so it is possible to put single quote inside double-quotes
												 * and vice versa */
												zAttr[pos_equal]=0;
												zAttr[iattr-1]=0;
												FieldArrayAddDynamicValue(&attributes,zAttr+pos_name);
												FieldArrayAddDynamicValue(&attributesvalues,zAttr+pos_equal+2);

												/* attribute name must respect RFC */
												if (!XMLTestFirstChar(zAttr[pos_name])) {
													logerr("Wrong XML file, tag [%s] attribute name cannot start with char %c (%x)",zElem,zAttr[pos_name],zAttr[pos_name]);
													XML_EXIT
												}
												for (iverif=0;zAttr[pos_name+iverif];iverif++) {
													if (!XMLTestChar(zAttr[pos_name+iverif])) {
														logerr("Wrong XML file, tag [%s] attribute name has an invalid char %c (0x%x)",zElem,zAttr[pos_name+iverif],zAttr[pos_name+iverif]);
														XML_EXIT
													}
												}

												quote_type=NO_QUOTE;
												pos_name=pos_equal=-1;
												parse_name=parse_value=0;
											}
										}
									}
								}
							}
						}
					} else { /* tag closed, parsing value */
						/*********************
						*      TAG value
						**********************/
						if (c=='<') {
							xml_string_ok=1; /* new tag, we leave */
							pos=idx;         /* parsing will redo from this point */
						} else {
							/* tag value must respect RFC */
							if (!XMLTestCDATAChar(c)) {
								zElem[ielem]=0;
								logerr("Wrong XML file, tag [%s] text value has an invalid char %c (0x%x)",zElem,c,c);
								XML_EXIT
							}
							zVal[ival++]=c;
							_internal_XMLCheckSpace(&zVal,ival,&maxval);
						}
					}
				}
			}
		}

		if (!xml_string_ok) { /* need to read more datas */
			if (xml_block_size==XML_BLOCK_SIZE) {
				xml_block_size=FileReadBinary(filename,buffer,XML_BLOCK_SIZE);
			} else {
				xml_block_size=0;
				/* end of raw data, checking for unfinished job */
				if (opened_cdata) {
					logerr("Wrong XML file, a CDATA segment was not closed!");
					XML_EXIT
				}
				if (opened_comment) {
					logerr("Wrong XML file, a comment was not closed!");
					XML_EXIT
				}
				if (opened_tag && !closed_tag) {
					logerr("Wrong XML file, the last marker was not closed!");
					XML_EXIT
				}
			}
			pos=0;
		} else { /* put datas in the tree */
			zElem[ielem]=0;
			zAttr[iattr]=0;
			zVal[ival]=0;
			zComment[icomment]=0;
			zCdata[icdata]=0;

			/*********************
			*  namespaces control
			**********************/
			/* namespaces update */
			if (namespacedefinitiontoggled) {
				for (iverif=0;attributes[iverif];iverif++) {
					if (strncmp(attributes[iverif],"xmlns:",strlen("xmlns:"))==0) {
						FieldArrayAddDynamicValue(&namespaces,attributes[iverif]+strlen("xmlns:"));
					}
				}
			}			
			/* namespace control */
			if (namespacetoggled) {
				namespacetoggled=0;
				for (iverif=0;namespaces[iverif];iverif++) {
					if (strncmp(zElem,namespaces[iverif],namespacelng)==0 && namespaces[iverif][namespacelng]==0) {
						namespacetoggled=1;
						namespaceidx=iverif;
						break;
					}
				}
				if (!namespacetoggled) {
					checkfield=curfield;
					while (!namespacetoggled) {
						for (iverif=0;checkfield->xml_namespace[iverif];iverif++) {
							if (strncmp(zElem,checkfield->xml_namespace[iverif],namespacelng)==0 && checkfield->xml_namespace[iverif][namespacelng]==0) {
								namespacetoggled=1;
								namespaceidx=iverif;
								break;
							}
						}
						if (!namespacetoggled) {
							checkfield=curfield->parent;
							if (!checkfield) {
								logerr("Wrong XML file, the namespace of the tag [%s] is not defined",zElem);
								XML_EXIT
							}
						}
					}
				}
			}
			
			if (cdata_flag && curfield->nb_child && curfield->child[curfield->nb_child]->xml_cdata) {
				/* contiguous CDATA segments append to each others */
				curfield->xml_cdata=MemRealloc(curfield->xml_cdata,strlen(curfield->xml_cdata)+icdata);
				strcat(curfield->xml_cdata,zCdata);				
			} else {
				if (*zElem=='/') { /* close a marker */
					if (strcmp(curfield->xml_name,zElem+1))
					{
						logerr("cannot close the marker [%s] within [%s]",zElem+1,curfield->xml_name);
						XML_EXIT
					}
//loginfo("close [%s]",curfield->xml_name);
					curfield=curfield->parent;
					/* retrieve current namespaces */
					if (curfield) {
						FreeFields(namespaces);
						namespaces=CopyFields(curfield->xml_namespace);
					}
				} else {
					/*************************
					* add a child in the tree
					**************************/
					zVal[ival]=0;
					TxtTrimStart(zVal);
					TxtTrimEnd(zVal);
					child=XMLCreateField(zElem,attributes,attributesvalues,zVal,zCdata,zComment,auto_closed,definition,cdata_flag,comment_flag);
					/* copy the namespaces if needed */
					if (namespaces) {
						child->xml_namespace=CopyFields(namespaces);
					}
					XMLAddChild(curfield,child);
//loginfo("addchild [%s] to [%s] %s",zElem,curfield->xml_name,auto_closed?"autoclosed":"opened");
					if (!auto_closed) curfield=child;
				}
			}
			/*********************
			*      cleanup
			**********************/
			namespacetoggled=namespacedefinitiontoggled=0;
			ielem=iattr=ival=0;
			cdata_flag=comment_flag=0;
			closed_tag=opened_tag=space_encountered=0;
			attributes=attributesvalues=namespaces=NULL;
			special_tag=0;
			xml_string_ok=0;
			auto_closed=0;
			empty_marker=0;
			allow_end_tag=0;
		}
	}

	/* the last field must be the xmlroot */
	if (opened_cdata) {
		logerr("XML file is corrupted, an opened CDATA segment was not closed!");
		XML_EXIT
	} else if (opened_comment) {
		logerr("XML file is corrupted, an opened comment segment was not closed!");
		XML_EXIT
	} else if (curfield!=xmlroot) {
		logerr("XML file is corrupted, there is a missing closing tag for %s",curfield->xml_name);
		XML_EXIT
	}

	/* check XML structure */
	while (0) {
	}

	/*********************
	* full cleanup
	**********************/
	if (namespaces) MemFree(namespaces);
	MemFree(buffer);
	MemFree(zComment);
	MemFree(zCdata);
	MemFree(zElem);
	MemFree(zAttr);
	MemFree(zVal);
	
	return xmlroot;
}



/***
	OpenDirectory
	
	input: directory to read
	       recursive mode
	input options:
	       minimal size
	       maximal size
	       older than	       
	       
	output: filename
*/


/***
	s_dirid
	structure used by ReadDir to manage multiple directories at a time
*/
struct s_dirid {
	DIR *dir_id;
	char *dirname;
	int cpt;
	struct s_dirid *next;
};

static struct s_dirid *diridROOT=NULL;

/***
	DirOpen function
	
	open a directory for reading
	check if the dir is already open
*/
DIR *DirOpen(char *dirname)
{
	#undef FUNC
	#define FUNC "DirOpen"
	struct s_dirid *curdir;
	
	/* check parameters coherency */
	if (!dirname)
	{
		logerr("directory name must not be NULL");
		exit(ABORT_ERROR);
	}
	if (strnlen(dirname,PATH_MAX)==PATH_MAX)
	{
		logerr("cannot open directory because the argument size is bigger than PATH_MAX (%d)\n",PATH_MAX);
		exit(ABORT_ERROR);
	}
	
	/* try to find the directory in the list */
	curdir=diridROOT;
	while (curdir!=NULL)
	{
		if (!strcmp(curdir->dirname,dirname))
			break;
		else
			curdir=curdir->next;
	}
	/* if curdir is NULL then the directory is not opened yet */
	if (!curdir)
	{
		_static_library_nbdir_opened++;
		if (_static_library_nbdir_opened>_static_library_nbdir_opened_max)
			_static_library_nbdir_opened_max=_static_library_nbdir_opened;
		curdir=MemCalloc(sizeof(struct s_dirid));
		curdir->dirname=MemMalloc(strlen(dirname)+1);
		strcpy(curdir->dirname,dirname);
		curdir->next=diridROOT;
		curdir->cpt=0;
		diridROOT=curdir;
	}
	else
		return curdir->dir_id;
	
	if ((curdir->dir_id=opendir(dirname))==NULL) {
		int cpt=0;

		switch (errno)
		{
			case EACCES:logerr("Read permission is denied for [%s].",dirname);break;
			case EMFILE:logerr("The process has too many files open. Cannot open directory [%s]",dirname);break;
			case ENFILE:logerr("The entire system, or perhaps the file system which contains the directory [%s], cannot support any additional open files at the moment.",dirname);break;
			default:logerr("Unknown error %d during opendir [%s]: %s",errno,dirname,strerror(errno));
		}
		exit(ABORT_ERROR);
	}
	else
	{
		logdebug("opening directory [%s]",dirname);
	}
	
	return curdir->dir_id;
}

/***
	DirGetStructFromID
	
	retrieve the dir structure from the tree, with his ID
*/
struct s_dirid *DirGetStructFromID(DIR *dir_id)
{
	#undef FUNC
	#define FUNC "DirGetStructFromID"
	struct s_dirid *curdir;
	
	curdir=diridROOT;
	while (curdir!=NULL)
	{
		if (curdir->dir_id==dir_id)
			break;
		else
			curdir=curdir->next;
	}
	if (!curdir)
	{
		logerr("ID requested for an unknown directory! (was supposed to be opened)");
		exit(INTERNAL_ERROR);
	}
	
	return curdir;
}


/***
	DirClose function
	
	check for closing return code
	free the memory dir structure
*/
void DirClose(DIR *dir_id)
{
	#undef FUNC
	#define FUNC "DirClose"
	struct s_dirid *curdir;
	struct s_dirid *unlinkcell;
	
	curdir=DirGetStructFromID(dir_id);
	if (closedir(curdir->dir_id))
	{
		logerr("error while closing directory [%s]",curdir->dirname);
	}	

	logdebug("closing directory [%s] %d entr%s read",curdir->dirname,curdir->cpt,(curdir->cpt>1)?"ies":"y");
	/* unlink the cell from ROOT */
	if (curdir==diridROOT)
	{
		diridROOT=curdir->next;
	}
	else
	{
		unlinkcell=diridROOT;
		while (unlinkcell->next!=curdir)
			unlinkcell=unlinkcell->next;
		unlinkcell->next=curdir->next;
	}
	MemFree(curdir->dirname);
	MemFree(curdir);
	_static_library_nbdir_opened--;
}

/***
	DirCloseName function
	
	close a dir, from his name
	check for closing return code
	free the memory dir structure
*/
void DirCloseName(char *dirname)
{
	#undef FUNC
	#define FUNC "DirCloseName"
	DirClose(DirOpen(dirname));
}

/***
	DirIncCPT
	
	increase line counter when reading a directory
*/
void DirIncCPT(DIR *dir_id)
{
	#undef FUNC
	#define FUNC "DirIncCPT"
	struct s_dirid *curdir;
	
	curdir=DirGetStructFromID(dir_id);
	curdir->cpt++;
}

/***
	DirGetCPT
	
	Get line counter information
*/
int DirGetCPT(DIR *dir_id)
{
	#undef FUNC
	#define FUNC "DirGetCPT"
	struct s_dirid *curdir;
	
	curdir=DirGetStructFromID(dir_id);
	return curdir->cpt;
}


/***
	DirReadEntry
	Get the first/next entry in the directory dirname

	DirMatchEntry
	Get the entries matching the glob name
*/
char *_internal_DirReadGlob(char *dirname, int globflag, int recurseflag)
{
	#undef FUNC
	#define FUNC "_internal_DirReadGlob"
	DIR *zedir=NULL;	
	struct dirent *dit;
	char *dupfilename;
	char *last_slash;
	char *globname;

	static int last_recurse_idx=-1;
	static char subdirname[PATH_MAX]={0};
	static char sbuffer[PATH_MAX]={0};
	static DIR **tabdir=NULL;
	int reinit;

	dupfilename=TxtStrDup(dirname);
	if (globflag) {
		last_slash=strrchr(dupfilename,'/');
		if (!last_slash) {
			globflag=0;
		} else {
			*last_slash=0;
			globname=last_slash+1;
		}
	}
	zedir=DirOpen(dupfilename);
	
	/* jump over . and .. then glob filename */
	if (!recurseflag) {
		if (!globflag)
			while ((dit=readdir(zedir))!=NULL && (!strcmp(dit->d_name,".") || !strcmp(dit->d_name,"..")));
		else
			while ((dit=readdir(zedir))!=NULL)
			{
				if (!strcmp(dit->d_name,".") || !strcmp(dit->d_name,".."))
					continue;
				if (!TxtGlobMatch(dit->d_name,globname)) {
					break;
				}
			}
	} else {
		/* recursive mode */
		if (last_recurse_idx==-1) {
			tabdir=MemMalloc(sizeof(DIR **));
			tabdir[0]=zedir;
			last_recurse_idx=0;
			strcpy(subdirname,dupfilename);
		}
		do {
			reinit=0;
			while ((dit=readdir(tabdir[last_recurse_idx]))!=NULL)
			{
				if (!strcmp(dit->d_name,".") || !strcmp(dit->d_name,".."))
					continue;
				if (dit->d_type==DT_DIR) {
					/* follow the pathtree */
					last_recurse_idx++;
					strcat(subdirname,"/");
					strcat(subdirname,dit->d_name);
					tabdir=MemRealloc(tabdir,sizeof(DIR**)*(last_recurse_idx+1));
					tabdir[last_recurse_idx]=DirOpen(subdirname);
				} else if (globflag && !TxtGlobMatch(dit->d_name,globname)) {
					break;
				} else if (!globflag) {
					break;
				}
			}
			if (last_recurse_idx) {
				if (!dit) {
					DirClose(tabdir[last_recurse_idx]);
					last_recurse_idx--;
					last_slash=strrchr(subdirname,'/');
					*last_slash=0;
					reinit=1;
				} else {
					DirIncCPT(tabdir[last_recurse_idx]);
					MemFree(dupfilename);
					snprintf(sbuffer,PATH_MAX,"%s/%s",subdirname,dit->d_name);
					return sbuffer;
				}
			}
		} while (last_recurse_idx>0 || reinit);
	}
	MemFree(dupfilename);
	
	if (dit!=NULL)
	{
		DirIncCPT(zedir);
		return dit->d_name;
	}
	else
	{
		/* End of directory, we close the handle */
		if (tabdir) MemFree(tabdir);
		last_recurse_idx=-1;
		DirClose(zedir);
		return NULL;
	}
}

int _sortcmpstring(const void *a, const void *b)
{
	char *sa,*sb;

	sa=(char*)*(char**)a;sb=(char*)*(char**)b;
	return strcmp(sa,sb);
}

char **_internal_DirReadAllGlob(char *dirname,int globflag,int recurseflag,int sortflag)
{
	#undef FUNC
	#define FUNC "_internal_DirReadAllGlob"

	char **dir_entries;
	char *curfile;
	int nb_entries=0;

	dir_entries=(char **)MemMalloc(sizeof(char *));
	while ((curfile=_internal_DirReadGlob(dirname,globflag,recurseflag))!=NULL) {
		dir_entries=MemRealloc(dir_entries,(nb_entries+2)*sizeof(char *));
		dir_entries[nb_entries]=TxtStrDup(curfile);
		nb_entries++;
	}
	if (sortflag) {
		qsort(dir_entries,nb_entries,sizeof(char *),_sortcmpstring);
	}

	/* to end the list */
	dir_entries[nb_entries]=NULL;

	return dir_entries;
}


/***
	LookForFile
	
	input: filename or dirname
	output: 1 if success
	        0 if failed
	        
	lookforfile is useful when you cannot open a file and just wanted to test it
*/
int LookForFile(char *filename, char *dirname)
{
	#undef FUNC
	#define FUNC "LookForFile"

	char fullpath[PATH_MAX+1];	
	int pathlen;

	/* checked by DirReadEntry but it is more convenient to have an error inside this function */
	if (!filename)
	{
		logerr("You must specify at least a filename with the path, or a filename and a dirname. Filename cannot be NULL!");
		exit(INTERNAL_ERROR);
	}
	pathlen=strnlen(filename,PATH_MAX);
	if (pathlen==PATH_MAX)
	{
		logerr("cannot look for this file or directory because the argument size is bigger than PATH_MAX (%d)",PATH_MAX);
		exit(ABORT_ERROR);
	}

	if (!dirname) {
#ifdef OS_WIN
		if (_access(filename,0)==0) return 1; else return 0;
#else
		if (access(filename,F_OK)!=-1) return 1; else return 0;
#endif
	} else {
		pathlen+=strnlen(dirname,PATH_MAX-pathlen);
		if (pathlen>=PATH_MAX-1)
		{
			logerr("cannot look for this file or directory because the full path size is bigger than PATH_MAX (%d)",PATH_MAX);
			exit(ABORT_ERROR);
		}
		sprintf(fullpath,"%s/%s",dirname,filename);
#ifdef OS_WIN
		if (_access(fullpath,0)==0) return 1; else return 0;
#else
		if (access(fullpath,F_OK)!=-1) return 1; else return 0;
#endif
	}
}

#define FileExists(zefile) LookForFile(zefile,NULL)

/***
	_do_remove
	
	remove a file or a directory
	with error management
*/
int _internal_do_remove(char *zename, char *zetype)
{
	#undef FUNC
	#define FUNC "_do_remove"

	if (zename==NULL)
	{
		logerr("the argument cannot be NULL");
		exit(INTERNAL_ERROR);
	}
	if (strnlen(zename,PATH_MAX)==PATH_MAX)
	{
		logerr("cannot remove this file or directory because the argument size is bigger than PATH_MAX (%d)",PATH_MAX);
		exit(ABORT_ERROR);
	}
	
	if (remove(zename))
	{
		switch (errno)
		{
			case EACCES:logerr("Write permission is denied for the directory from which the %s [%s] is to be removed, or the directory has the sticky bit set and you do not own the file.",zetype,zename);break;
			case EBUSY:logerr("This error indicates that the %s [%s] is being used by the system in such a way that it can't be unlinked. For example, you might see this error if the file name specifies the root directory or a mount point for a file system.",zetype,zename);break;
			case ENOENT:logerr("The %s named [%s] to be deleted doesn't exist.",zetype,zename);break;
			case EPERM:logerr("On some systems unlink cannot be used to delete the name of a directory [%s], or at least can only be used this way by a privileged user. To avoid such problems, use rmdir to delete directories.",zename);break;
			case EROFS:logerr("The directory containing the %s named [%s] to be deleted is on a read-only file system and can't be modified.",zetype,zename);break;
			case ENOTEMPTY:logerr("The directory [%s] to be deleted is not empty.",zename);break;
			default:logerr("Unknown error %d during remove [%s]: %s",errno,zename,strerror(errno));
		}
		exit(ABORT_ERROR);
	}
	logdebug("%s deleted",zename);
	return 0;	
}

#define FileRemove(filename) _internal_do_remove(filename,"file")

/***
        FileTruncate function
        set file to zero size then leave        
*/
int FileTruncate(char *filename)
{
#undef FUNC
#define FUNC "FileTruncate"
FILE *last_id=NULL;

#ifdef OS_WIN
int sr;
last_id=FileOpen(filename,"w");
sr=_setmode(_fileno(last_id), _O_BINARY );
if (sr==-1) {
logerr("FATAL: cannot set binary mode for writing");
exit(ABORT_ERROR);
}
#else
last_id=FileOpen(filename,"a+");
#endif
FileClose(last_id);
return 0;
}



/***
	DirRemove
	
	delete a non-empty directory
	this function is recursive
	
	at this time, we do not want to delete socket or special files
*/
void DirRemove(char *zerep)
{
  #undef FUNC
  #define FUNC "DirRemove"
  char curname[MAX_LINE_BUFFER];
  char *curfile;
  
loginfo("remouve");
  if (zerep==NULL)
  {
  	logerr("the directory name cannot be NULL");
  	exit(INTERNAL_ERROR);
  }
  if (strnlen(zerep,PATH_MAX)==PATH_MAX)
  {
	logerr("cannot remove directory because the argument size is bigger than PATH_MAX (%d)",PATH_MAX);
  	exit(ABORT_ERROR);
  }
  
  while ((curfile=DirReadEntry(zerep))!=NULL)
  {
    	sprintf(curname,"%s/%s",zerep,curfile);
    	if (FileIsRegular(curname))
    		FileRemove(curname);
    	else
    	if (FileIsDir(curname))
    		DirRemove(curname);
    	else
    	{
    		logerr("The file %s cannot be deleted cause it is not a regular file",curname);
    		exit(ABORT_ERROR);
    	}    	
  }  
  _internal_do_remove(zerep,"directory");
}

/***
	FileRemoveIfExists
	
	remove a file if it exists but do not quit in error
	if the file is not present
*/
void FileRemoveIfExists(char *filename)
{
	#undef FUNC
	#define FUNC "FileRemoveIfExists"
	if (FileExists(filename))
		FileRemove(filename);
}
/***
	DirRemoveIfExists
	
	remove a dir if it exists but do not quit in error
	if the dir is not present
*/
void DirRemoveIfExists(char *dirname)
{
	#undef FUNC
	#define FUNC "DirRemoveIfExists"
loginfo("remouve if");
	if (FileIsDir(dirname)) {
loginfo("%s est un repertoire",dirname);
		DirRemove(dirname);
	}
}

/***
	ChangeDir
	
	change working directory
	input argument is controlled
	it cannot be NULL and cannot be bigger than PATH_MAX (1024 bytes on AIX system)
*/
void ChangeDir(char *zedir)
{
	#undef FUNC
	#define FUNC "ChangeDir"
	
	if (!zedir)
	{
		logerr("cannot change directory as the provided parameter is NULL");
		exit(INTERNAL_ERROR);
	}
	if (strnlen(zedir,PATH_MAX)==PATH_MAX)
	{
		logerr("cannot change directory because the argument size is bigger than PATH_MAX (%d)",PATH_MAX);
		exit(ABORT_ERROR);
	}
	if (chdir(zedir)==-1)
	{
		logerr("cannot change directory to %s",zedir);
		switch (errno)
		{
			case EINVAL:logerr("The size argument is zero and buffer is not a null pointer.");break;
			case ERANGE:logerr("The size argument is less than the length of the working directory name. You need to allocate a bigger array and try again.");break;
			case EACCES:logerr("Permission to read or search a component of the directory name was denied.");break;
			default:logerr("Unknown error %d during chdir: %s",errno,strerror(errno));
		}
		exit(ABORT_ERROR);
	}
}
/***
	GetDir
	
	return the current directory path in an allocated pointer
	do not forget to free your memory after use!
	note: under AIX system, getcwd cannot be called with zero size buffer and NULL pointer...
*/
char *GetDir()
{
	#undef FUNC
	#define FUNC "GetDir"
	
	char *zesysdir;
	
	zesysdir=MemMalloc(PATH_MAX+1);
#ifdef OS_WIN
	if (_getcwd(zesysdir,PATH_MAX)==NULL)
#else
	if (getcwd(zesysdir,PATH_MAX)==NULL)
#endif
	{	
		logerr("cannot get working directory");
		switch (errno)
		{
			case EINVAL:logerr("The size argument is zero and buffer is not a null pointer.");break;
			case ERANGE:logerr("The size argument is less than the length of the working directory name. You need to allocate a bigger array and try again.");break;
			case EACCES:logerr("Permission to read or search a component of the directory name was denied.");break;
			default:logerr("Unknown error %d during getcwd: %s",errno,strerror(errno));
		}
		exit(INTERNAL_ERROR);
	}
	/* realloc to the real size with a secure len control */
	return MemRealloc(zesysdir,strnlen(zesysdir,PATH_MAX)+1);
}
#define PWD GetDir


/***
	ExecuteSysCmdGetLimit
	
	compute maximum command line size for use with system command
	The value is calculated by substracting environnement size to ARG_MAX
	
	For example, the limit will be approx 19k under shell session but
	only 16k under rex pech process. It is crap to define a fixed value
	cause system configuration may change in the future
	
	the official documentation dont give a precise answer but it seems
	to fit well by simply adding length of strings, including terminators
	
	http://publib.boulder.ibm.com/infocenter/aix/v6r1/index.jsp?topic=/com.ibm.aix.basetechref/doc/basetrf1/posix_spawn.htm
	The number of bytes available for the child process' combined argument and environment lists is {ARG_MAX}.
	The implementation specifies in the system documentation whether any list overhead, such as length words,
	null terminators, pointers, or alignment bytes, is included in this total.
*/
int ExecuteSysCmdGetLimit()
{
	#undef FUNC
	#define FUNC "ExecuteSysCmdGetLimit"
	
	int env_size;
	int env_idx;
	int idx;
	
	logdebug("computing environnement size");
	env_idx=env_size=0;
	while (environ[env_idx]!=NULL)
		env_size+=strlen(environ[env_idx++])+1;
	/* dont ask... */
	env_size+=256;
	/* check that environnement is not too big for a usable usage */
	if (env_size>ARG_MAX)
	{
		logerr("Your environnement is full, you should check you system configuration to use system command properly");
		exit(INTERNAL_ERROR);
	}	
	logdebug("environnement size=%d",env_size);
	env_size=ARG_MAX-env_size;
	logdebug("maximum argument size is %d",env_size);	
	return env_size;
}
/* compatibility mode */
#define MAX_COMMAND_LINE_BUFFER ExecuteSysCmdGetLimit()

/***
	_internal_ExecuteSysCmd
	
	execute a system command line
	the first parameter defines the behaviour in error case
	you must not call this function, use the two functions macro above
	- ExecuteSysCmd(...) will quit on error
	- ExecuteSysCmdBypassError(...) wont quit on error
	- ExecuteSysCmdBackGround(...) execute in the background, there is no error test
	
	input: string format, ... (like printf)
*/
enum e_sys_cmd_mode {
EXECUTE_SYS_CMD_QUIT_ON_ERROR,
EXECUTE_SYS_CMD_BYPASS_ERROR,
EXECUTE_SYS_CMD_BACKGROUND,
EXECUTE_SYS_CMD_BACKGROUND_PUSHED
};

void *_internal_ExecuteSysCmdThread(void *commande)
{
	#undef FUNC
	#define FUNC "_internal_ExecuteSysCmdThread"

	char *zecommande;
	int ret;

	zecommande=(char*)commande;
	ret=system(zecommande);
	MemFree(zecommande);
	pthread_exit(NULL);
#ifdef OS_WIN
	return NULL;
#endif
}

int _internal_ExecuteSysCmd(int zemode,char *format,...)
{
	#undef FUNC
	#define FUNC "_internal_ExecuteSysCmd"
	
	/* system buffer is bigger than expected, to check the limits */
	char zecommande[ARG_MAX];
	char *dyncommande;
	va_list argptr;
	int rc,zelen;
	pthread_t thread;
	pthread_attr_t attr;
	static int arg_limit=-1;
	int arg_size;
	
	/* we compute the size of the environnement only once per program execution */
	if (arg_limit==-1)
		arg_limit=ExecuteSysCmdGetLimit();

	if (format==NULL)
	{
		logerr("the argument of this function cannot be NULL");
		exit(INTERNAL_ERROR);
	}	
	
	va_start(argptr,format);
	zelen=vsnprintf(NULL,0,format,argptr)+1;
	va_end(argptr);
	if (zelen>=arg_limit)
	{
		logerr("Your command line is too long (%d for %d)",zelen,arg_limit);
		logerr("You must be aware that this value is dynamic and is environnement dependent");
		logerr("You could use ExecuteSysCmdGetLimit() to get the current value");
		exit(ABORT_ERROR);
	}
	
	va_start(argptr,format);
	vsprintf(zecommande,format,argptr);	
	va_end(argptr);
	logdebug("system command: %s",zecommande);

	if (zemode==EXECUTE_SYS_CMD_BACKGROUND || zemode==EXECUTE_SYS_CMD_BACKGROUND_PUSHED) {
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
		pthread_attr_setstacksize(&attr,65536);
		dyncommande=TxtStrDup(zecommande);
		if ((rc=pthread_create(&thread,&attr,_internal_ExecuteSysCmdThread,(void *)dyncommande))) {
			logerr("Cannot create thread!");
			exit(INTERNAL_ERROR);
		}
		if (zemode==EXECUTE_SYS_CMD_BACKGROUND_PUSHED)
			_internal_PushThread(thread);
		return 0;		
	}
	
	rc=system(zecommande);
#ifndef OS_WIN
	if ((WIFSIGNALED(rc) &&	(WTERMSIG(rc)==SIGINT || WTERMSIG(rc)==SIGQUIT)))
	{
		logerr("command aborted by user or system: %-200.200s...",zecommande);
		exit(ABORT_ERROR);
	}
#endif
	if(rc!=0)
	{
		switch (zemode)
		{
			default:
			case EXECUTE_SYS_CMD_QUIT_ON_ERROR:
				logerr("system command failed");
				logerr("command=%s",zecommande);
				logerr("ret=%d",rc);
				logerr("errno=%d",errno);
				logerr("strerror(errno)=%s",strerror(errno));
				exit(ABORT_ERROR);
			case EXECUTE_SYS_CMD_BYPASS_ERROR:
				logdebug("system command failed");
				logdebug("command=%s",zecommande);
				logdebug("ret=%d",rc);
				logdebug("errno=%d",errno);
				logdebug("strerror(errno)=%s",strerror(errno));
				break;
		}
	}
	return(rc);
}
#define ExecuteSysCmd(...) _internal_ExecuteSysCmd(EXECUTE_SYS_CMD_QUIT_ON_ERROR,__VA_ARGS__)
#define ExecuteSysCmdBypassError(...) _internal_ExecuteSysCmd(EXECUTE_SYS_CMD_BYPASS_ERROR,__VA_ARGS__)
#define ExecuteSysCmdBackGround(...) _internal_ExecuteSysCmd(EXECUTE_SYS_CMD_BACKGROUND,__VA_ARGS__)
#define ExecuteSysCmdBackGroundPushed(...) _internal_ExecuteSysCmd(EXECUTE_SYS_CMD_BACKGROUND,__VA_ARGS__)


/***
	GetSHORTINT
	GetINT
	GetLONGLONG

	get values from memory, regardless of endianness
	useful to read some exotics file formats
*/

/* prototype needed */
int GetEndianMode();

/***
	GetAutoEndian
	
	if the endian mode is not specified then we get the architecture endian mode
*/

int GetAutoEndian(int zemode)
{
	#undef FUNC
	#define FUNC "GetAutoEndian"
	
	if (zemode==GET_AUTO_ENDIAN)
	{
		if (_static_library_endian_mode==GET_ENDIAN_UNDEFINED)
			GetEndianMode();
		zemode=_static_library_endian_mode;
	}
	return zemode;
}
unsigned short int GetEndianSHORTINT(unsigned char *ptr, int zemode)
{
	#undef FUNC
	#define FUNC "GetEndianSHORTINT"

	unsigned short int zevalue=0;

	zemode=GetAutoEndian(zemode);
	
	switch (zemode)
	{
		case GET_LITTLE_ENDIAN:zevalue=ptr[0]+ptr[1]*256;break;
		case GET_BIG_ENDIAN:   zevalue=ptr[0]*256+ptr[1];break;
		default:logerr("You must use GET_LITTLE_ENDIAN or GET_BIG_ENDIAN");exit(INTERNAL_ERROR);
	}
	return zevalue;
}
unsigned int GetEndianINT(unsigned char *ptr,int zemode)
{
	#undef FUNC
	#define FUNC "GetEndianINT"

	unsigned int zevalue=0;

	zemode=GetAutoEndian(zemode);
	
	switch (zemode)
	{
		case GET_LITTLE_ENDIAN:zevalue=ptr[0]+ptr[1]*256+ptr[2]*65536+ptr[3]*16777216;break;
		case GET_BIG_ENDIAN:   zevalue=ptr[0]*16777216+ptr[1]*65536+ptr[2]*256+ptr[3];break;
		default:logerr("You must use GET_LITTLE_ENDIAN or GET_BIG_ENDIAN");exit(INTERNAL_ERROR);
	}
	return zevalue;
}
unsigned long long GetEndianLONGLONG(unsigned char *ptr,int zemode)
{
	#undef FUNC
	#define FUNC "GetEndianLONGLONG"

	/* the long long type is 64 bits in both 32 bits and 64 bits architecture */
	unsigned long long zevalue=0;

	zemode=GetAutoEndian(zemode);

	/* tiny code for 32 bits architecture (how sucks, obviously) */
	switch (zemode)
	{
		case GET_LITTLE_ENDIAN: zevalue=4294967296ULL*(unsigned long long)GetEndianINT(ptr+4,zemode)+(unsigned long long)GetEndianINT(ptr,zemode);break;
		case GET_BIG_ENDIAN: zevalue=4294967296ULL*(unsigned long long)GetEndianINT(ptr,zemode)+(unsigned long long)GetEndianINT(ptr+4,zemode);break;
/*
		case GET_LITTLE_ENDIAN:zevalue=
			(*ptr)
			+(*(ptr+1))<<8
			+(*(ptr+2))<<16
			+(*(ptr+3))<<24
			+((unsigned long long)(*(ptr+4)))<<32
			+((unsigned long long)(*(ptr+5)))<<40
			+((unsigned long long)(*(ptr+6)))<<48
			+((unsigned long long)(*(ptr+7)))<<56;
			break;
		case GET_BIG_ENDIAN:   zevalue=
			((unsigned long long)(*ptr))<<56
			+((unsigned long long)(*(ptr+1)))<<48
			+((unsigned long long)(*(ptr+2)))<<40
			+((unsigned long long)(*(ptr+3)))<<32
			+(*(ptr+4))<<24
			+(*(ptr+5))<<16
			+(*(ptr+6))<<8
			+(*(ptr+7));
			break;
*/
		default:logerr("You must use GET_LITTLE_ENDIAN or GET_BIG_ENDIAN");exit(INTERNAL_ERROR);
	}
	
	return zevalue;
}

int GetEndianMode()
{
	#undef FUNC
	#define FUNC "GetEndianMode"
	
	unsigned short int *endian_test_value;
	unsigned char endiantest[2];
	
	endiantest[0]=0x12;
	endiantest[1]=0x34;
	endian_test_value=(unsigned short int*)endiantest;
	
	if (*endian_test_value==0x1234)
	{
		logdebug("big-endian architecture");
		_static_library_endian_mode=GET_BIG_ENDIAN;
	}
	else
	{
		logdebug("little-endian architecture");
		_static_library_endian_mode=GET_LITTLE_ENDIAN;
	}
	return _static_library_endian_mode;
}

/* shortcuts to get values with the current architecture */
#define GetShortInt(ptr) GetEndianSHORTINT(ptr,GET_AUTO_ENDIAN)
#define GetInt(ptr)           GetEndianINT(ptr,GET_AUTO_ENDIAN)
#define GetLongLong(ptr) GetEndianLONGLONG(ptr,GET_AUTO_ENDIAN)

void PutEndianSHORTINT(short int zevalue,unsigned char *ptr, int zemode)
{
	#undef FUNC
	#define FUNC "PutEndianSHORTINT"

	zemode=GetAutoEndian(zemode);
	
	switch (zemode)
	{
		case PUT_LITTLE_ENDIAN:
			*ptr=zevalue&0xFF;ptr++;
			*ptr=(zevalue&0xFF00)>>8;
			break;
		case PUT_BIG_ENDIAN:
			*ptr=(zevalue&0xFF00)>>8;ptr++;
			*ptr=zevalue&0xFF;
			break;
		default:logerr("You must use PUT_LITTLE_ENDIAN or PUT_BIG_ENDIAN");exit(INTERNAL_ERROR);
	}
}
void PutEndianINT(int zevalue, unsigned char *ptr,int zemode)
{
	#undef FUNC
	#define FUNC "PutEndianINT"

	zemode=GetAutoEndian(zemode);
	
	switch (zemode)
	{
		case PUT_LITTLE_ENDIAN:
			*ptr=zevalue&0xFF;ptr++;
			*ptr=(zevalue&0xFF00)>>8;ptr++;
			*ptr=(zevalue&0xFF0000)>>16;ptr++;
			*ptr=(zevalue&0xFF000000)>>24;
			break;
		case PUT_BIG_ENDIAN:
			*ptr=(zevalue&0xFF000000)>>24;ptr++;
			*ptr=(zevalue&0xFF0000)>>16;ptr++;
			*ptr=(zevalue&0xFF00)>>8;ptr++;
			*ptr=zevalue&0xFF;
			break;
		default:logerr("You must use GET_LITTLE_ENDIAN or GET_BIG_ENDIAN");exit(INTERNAL_ERROR);
	}
}
void PutEndianLONGLONG(unsigned long long zevalue, unsigned char *ptr,int zemode)
{
	#undef FUNC
	#define FUNC "PutEndianLONGLONG"
	/* the long long type is 64 bits in both 32 bits and 64 bits architecture */

	zemode=GetAutoEndian(zemode);

	/* tiny code for 32 bits architecture (how sucks, obviously) */
	switch (zemode)
	{
		case GET_LITTLE_ENDIAN:
			PutEndianINT((zevalue&0x00000000FFFFFFFFULL),ptr,zemode);
			PutEndianINT((zevalue&0xFFFFFFFF00000000ULL)>>32,ptr+4,zemode);
			break;
		case GET_BIG_ENDIAN:
			PutEndianINT((zevalue&0xFFFFFFFF00000000ULL)>>32,ptr,zemode);
			PutEndianINT((zevalue&0x00000000FFFFFFFFULL),ptr+4,zemode);
			break;
		default:logerr("You must use GET_LITTLE_ENDIAN or GET_BIG_ENDIAN");exit(INTERNAL_ERROR);
	}
}
/* shortcuts to put values with the current architecture */
#define PutShortInt(zeval,ptr) PutEndianSHORTINT(zeval,ptr,GET_AUTO_ENDIAN)
#define PutInt(zeval,ptr)           PutEndianINT(zeval,ptr,GET_AUTO_ENDIAN)
#define PutLongLong(zeval,ptr) PutEndianLONGLONG(zeval,ptr,GET_AUTO_ENDIAN)


/***
	SystemInfo
	
	display usage statistics in debug mode (memory, files, dirs)
	
	perform some system checking

	- endian mode
	- 32bits or 64bits mode
*/
void SystemInfo()
{
	#undef FUNC
	#define FUNC "SystemInfo"
	
#ifdef OS_WIN
	SYSTEM_INFO sysinfo;
	OSVERSIONINFOEX  osvi;
	BOOL bIsWindowsXPorLater;
	char windows_string[128];

	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((OSVERSIONINFO*)&osvi);
	GetSystemInfo(&sysinfo);
	switch (osvi.dwMajorVersion) {
		case 5:
			switch (osvi.dwMinorVersion) {
				case 0:if (osvi.wProductType==VER_NT_WORKSTATION) strcpy(windows_string,"2000 Professional"); else strcpy(windows_string,"2000");break;
				case 1:if (osvi.wSuiteMask==VER_SUITE_PERSONAL) strcpy(windows_string,"XP Home Edition"); else strcpy(windows_string,"XP Professional");break;
				case 2:if (osvi.wProductType==VER_NT_WORKSTATION && sizeof(long)==8) strcpy(windows_string,"XP Professional x64 Edition"); else strcpy(windows_string,"Server 2003 or similar");break;
				default:sprintf(windows_string,"%d.%d",osvi.dwMajorVersion,osvi.dwMinorVersion);
			}
			break;
		case 6:
			switch (osvi.dwMinorVersion) {
				case 0:if (osvi.wProductType==VER_NT_WORKSTATION) strcpy(windows_string,"Vista"); else strcpy(windows_string,"Server 2008");break;
				case 1:if (osvi.wProductType==VER_NT_WORKSTATION) strcpy(windows_string,"Seven"); else strcpy(windows_string,"Server 2008 R2");break;
				case 2:if (osvi.wProductType==VER_NT_WORKSTATION) strcpy(windows_string,"8"); else strcpy(windows_string,"Server 2012");break;
				default:sprintf(windows_string,"%d.%d",osvi.dwMajorVersion,osvi.dwMinorVersion);
			}
			break;
		default:sprintf(windows_string,"%d.%d",osvi.dwMajorVersion,osvi.dwMinorVersion);
	}
	loginfo("running Windows %s (%d core%s)",windows_string,CPU_NB_CORES,CPU_NB_CORES>1?"s":"");
#else	
	char infofile[PATH_MAX];
	pid_t process_id;
	char *buffer;
	char *info_machine;
	char *info_archi;
	char *info_os;
	char *info_version;
	char *info_release;
	
	process_id=getpid();
	loginfo("using %s on",__FILENAME__);

	sprintf(infofile,"/tmp/%d_systeminfo.txt",process_id);
#ifdef OS_AIX
	ExecuteSysCmd("uname -M >  %s",infofile);
	ExecuteSysCmd("uname -p >> %s",infofile);
	ExecuteSysCmd("uname -s >> %s",infofile);
	ExecuteSysCmd("uname -v >> %s",infofile);
	ExecuteSysCmd("uname -r >> %s",infofile);
#endif
#ifdef OS_LINUX
	ExecuteSysCmd("uname -i >  %s",infofile);
	ExecuteSysCmd("uname -p >> %s",infofile);
	ExecuteSysCmd("uname -o >> %s",infofile);
	ExecuteSysCmd("uname -r >> %s",infofile);
	ExecuteSysCmd("uname -v >> %s",infofile);
#endif
	info_machine=TxtStrDup(TxtTrim(FileReadLine(infofile)));
	info_archi  =TxtStrDup(TxtTrim(FileReadLine(infofile)));
	info_os     =TxtStrDup(TxtTrim(FileReadLine(infofile)));
	info_version=TxtStrDup(TxtTrim(FileReadLine(infofile)));
	info_release=TxtStrDup(TxtTrim(FileReadLine(infofile)));
	FileReadClose(infofile);
	FileRemove(infofile);
	
	loginfo("%s %s",info_machine,info_archi);
	loginfo("running %s %s.%s",info_os,info_version,info_release);
	MemFree(info_machine);MemFree(info_archi);MemFree(info_os);MemFree(info_version);MemFree(info_release);
#endif	
	if (sizeof(long)==8)
		loginfo("64bits mode");
	else
		loginfo("32bits mode");
		
	if (GetEndianMode()==GET_BIG_ENDIAN)
		loginfo("big-endian architecture");
	else
		loginfo("little-endian architecture");
}


/*******************************************************************************************************

	Process related function, Linux specific

*******************************************************************************************************/
#ifndef OS_WIN
/***
 *	ProcessFork
 *
 * 	if provided, execute a command line, detached from the current process
 * 	else fork the current process
 */
pid_t ProcessFork(char *format, ...)
{
	#undef FUNC
	#define FUNC "ProcessFork"

        va_list argptr;
	pid_t pid;

	pid=fork();
	va_start(argptr,format);
	switch (pid) {
		case -1:logerr("Cannot fork!");logerr(format,argptr);exit(INTERNAL_ERROR);
		case  0:if (format!=NULL)
				exit(ExecuteSysCmd(format,argptr));
		default:break;
	}
	return pid;
}

/***
 *	ProcessDetach
 *
 *	detach process from its father, then it cannot
 *	be killed by the launching session
 */
void ProcessDetach()
{
	#undef FUNC
	#define FUNC "ProcessDetach"

	if (ProcessFork(NULL)) exit(0);
	setsid();
}


/***
 *	ProcessSearch
 *
 * 	return the pid of the first matching process
 * 	this function may take a while (50ms) to proceed
 */
pid_t ProcessSearch(char *process_name)
{
	#undef FUNC
	#define FUNC "ProcessSearch"

	char status_file[PATH_MAX];
	char **status_files;
	char *buffer;
	pid_t zepid=0;
	int i=0,ok=0;

	status_files=DirReadAllEntries("/proc");
	while (status_files[i] && !ok) {
		if (!isdigit(status_files[i][0])) {
			i++;
			continue;
		}
		sprintf(status_file,"/proc/%s/status",status_files[i]);
		/* we MUST read line per line */
		while ((buffer=FileReadLine(status_file))!=NULL) {
			if (!strncmp(buffer,"Name:",5)) {
				buffer=TxtTrim(buffer+5);
				if (!strcmp(buffer,process_name)) {
					ok=1;
				}
			} else if (!strncmp(buffer,"Pid:",4)) {
				zepid=atoi(buffer+4);
			}
		}
		i++;
	}
	FreeFields(status_files);
	return zepid;
}

/***
 *	ProcessExists
 *
 *	input: process id
 *	output: 1 if the process exists, 0 if not
 */
int ProcessExists(pid_t pid)
{
	#undef FUNC
	#define FUNC "ProcessExists"

	char proc_status[PATH_MAX];
	sprintf(proc_status,"/proc/%d",pid);
	return FileIsDir(proc_status);
}
/***
 *	ProcessInfo
 *
 * 	input: process id
 * 		pointers to information variables that can be NULL
 * 	output: if pointers are not NULL then they are filled with information
 */
int ProcessInfo(pid_t pid, char **commande, long *memused, int *nbthread)
{
	#undef FUNC
	#define FUNC "ProcessInfo"

	char proc_status_file[PATH_MAX];
	char *buffer;

	sprintf(proc_status_file,"/proc/%d/status",pid);

	if (commande!=NULL) *commande="";
	if (memused!=NULL) *memused=1;
	if (nbthread!=NULL) *nbthread=1;

	if (ProcessExists(pid)) {
		while ((buffer=FileReadLine(proc_status_file))!=NULL) {
			if (!strncmp(buffer,"Name:",5)) {
				if (commande!=NULL) {
					*commande=TxtStrDup(buffer+5);
					*commande=TxtTrim(*commande);
				}
			} else if (!strncmp(buffer,"VmRSS:",6)) {
				if (memused!=NULL) {
					*memused=1024*atoi(buffer+6);
				}
			} else if (!strncmp(buffer,"Threads:",8)) {
				if (nbthread!=NULL) {
					*nbthread=atoi(buffer+8);
				}
			}
		}
		return 1;
	} else {
		return 0;
	}
}
/***
 *	ProcessQuit
 *
 * 	wait for process to quit normaly
 * 	after 15s, kill it
 */
void ProcessQuit(pid_t pid)
{
	#undef FUNC
	#define FUNC "ProcessQuit"

	#define WAIT_US_MAX 15*1000*1000

	int wait_a_little=10;

	kill(pid,SIGTERM);

	while (ProcessExists(pid) && wait_a_little<=WAIT_US_MAX) {
		usleep(wait_a_little);
		wait_a_little*=2;
	}

	if (wait_a_little>WAIT_US_MAX)
		kill(pid,SIGKILL);
}
void * _internal_ProcessQuit(void *pid)
{
	#undef FUNC
	#define FUNC "_internal_ProcessQuit"

	pid_t zepid;
	zepid=(pid_t)(long)pid;
	ProcessQuit(zepid);
	pthread_exit(NULL);
}
/***
 *	ProcessQuitBackGround
 *
 *	kill process in background
 *	with a thread
 */
void ProcessQuitBackGround(pid_t pid)
{
	#undef FUNC
	#define FUNC "ProcessQuitBackGround"

	pthread_t thread;
	pthread_attr_t attr;
	int rc;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	pthread_attr_setstacksize(&attr,65536);

	if ((rc=pthread_create(&thread,&attr,_internal_ProcessQuit,(void *)(long)pid))) {
		logerr("Cannot create thread!");
		exit(INTERNAL_ERROR);
	}
	_internal_PushThread(thread);
}
#endif
/***
	GraveDiggerLibrary
	
	perform a full check of allocated blocks
*/
void GraveDiggerLibrary()
{
	#undef FUNC
	#define FUNC "GraveDiggerLibrary"
	MemCheck();
	loginfo("unknown segmentation fault");
	exit(INTERNAL_ERROR);
}
/***
	OpenLibrary
	
	some initialisations must be done for windows or Linux
*/
void OpenLibrary()
{
	#undef FUNC
	#define FUNC "OpenLibrary"
	
#ifndef OS_WIN
	signal(SIGSEGV,GraveDiggerLibrary);
#else
	pthread_mutex_init(&mutex_memory_management);
#endif
}

/***
	CloseLibrary
	
	display usage statistics in debug mode (memory, files, dirs)
	
	perform a check for opened resources
	
	warn on monitor who are not closed
	warn on file who are not closed
	warn on dir who are not closed
	warn on memory blocks who are not freed
*/
void CloseLibrary()
{
	#undef FUNC
	#define FUNC "CloseLibrary"
	
	struct s_memory_trace *mem_trace;
	struct s_fileid *curfile;
	struct s_dirid *curdir;
	int i;

	logdebug("freeing library memory");
	/* empty memory crunch alloc */
#ifndef RDD
	MemoryCrunch(NULL,NULL,0);
#endif
#ifndef OS_WIN
	/* empty regexp cache */
	_internal_regexp_get_cache(NULL);
#endif
	/* wait for active threads to finish */
	logdebug("waiting for pending threads");
	_internal_WaitForThreads();

	logdebug("checking for remaining memory");

#ifndef FAST_LIBRARY
	logdebug("statistiques:");
	logdebug("maximum de memoire utilisee: %dko",_static_library_memory_used_max/1024);
	logdebug("maximum de fichiers ouverts: %d",_static_library_nbfile_opened_max);
	logdebug("maximum de repertoires ouverts: %d",_static_library_nbdir_opened_max);
	logdebug("");

	mem_trace=memory_trace_ROOT;
	while (mem_trace!=NULL)
	{
		logwarn("the monitor of %X:%d is still active",mem_trace->ptr,mem_trace->size);
		mem_trace=mem_trace->next;
	}
	if (_static_library_memory_used) {
		logwarn("there is still %d bytes of memory declared allocated",_static_library_memory_used);
	}
	for (i=0;i<_static_library_memory_monitor_top;i++)
	{
		if (mem_monitor[i].ptr!=NULL)
		{
			char tmpstr[32+4]={0};
			int itmp;

			for (itmp=0;itmp<mem_monitor[i].size && itmp<32;itmp++) {
				if (mem_monitor[i].ptr[itmp]>31) tmpstr[itmp]=mem_monitor[i].ptr[itmp]; else if (mem_monitor[i].ptr[itmp]) tmpstr[itmp]='.';
			}
			if (itmp==32 && mem_monitor[i].size>32) strcat(tmpstr,"...");

			logwarn("memory block of %d byte%s wasn't freed %s - %s L%d operation %d [%s]",
				mem_monitor[i].size,
				(mem_monitor[i].size>1)?"s":"",
				mem_monitor[i].cursource,
				mem_monitor[i].curfunc,
				mem_monitor[i].curline,
				mem_monitor[i].mem_op,tmpstr);
		}		
	}
#endif
	logdebug("checking for remaining opened files or directories");
	for (i=0;i<resourcefileROOT.nbresource;i++) {
		logwarn("the blockfile [%s] was not closed",resourcefileROOT.resource[i].filename);
	}
	
	curfile=fileidROOT;
	while (curfile!=NULL)
	{
		logwarn("the file [%s](%s) was not closed",curfile->filename,curfile->opening_type);
		curfile=curfile->next;
	}

	curdir=diridROOT;
	while (curdir!=NULL)
	{
		logwarn("the directory [%s] was not closed",curdir->dirname);
		curdir=curdir->next;
	}

	printf("(c) 2011-%4d Mini-library by Edouard BERGE\n",GetCurrentYear());
	printf("(c) 2011-%4d LZ4 compression by Yann COLLET\n",GetCurrentYear());
#ifdef FAST_LIBRARY
#ifndef OS_WIN
	printf("(c) 2007-%4d Gperftools by GOOGLE Inc.\n",GetCurrentYear());
#endif
#endif
#ifdef OS_WIN
	printf("(c) 2004-%4d regexp library (modified) by Alberto DEMICHELIS\n",GetCurrentYear());
#ifdef LIBAUDIOLABEL
	printf("(c) 2003-%4d libao audio library by xiph.org\n",GetCurrentYear());
#endif
	printf("(c) 1997-%4d POSIX directory browsing for win32 by Kevlin HENNEY\n",GetCurrentYear());
#else
#ifdef LIBAUDIOLABEL
	printf("(c) 2003-%4d libao audio library by xiph.org\n",GetCurrentYear());
#endif
#endif
	printf("(c) 1996-%4d Isaac pseudo random generator by Bob JENKINS\n",GetCurrentYear());
#ifdef OS_WIN
	printf("(c) 1989-%4d fnmatch by University of California, Berkeley\n",GetCurrentYear());
#endif
}


/***
	Numeric filter functions

*/

enum e_filter_type
{
INACTIVE,
LOW_PASS,
LOW_PASS_ALT,
BANDPASS,
HIGH_PASS
};

struct s_filter_coef
{
        enum e_filter_type  filter_type;
        double acquisition_frequency;
        double low_frequency;
        double high_frequency;
        double quality_coef;

        int nb_coef_in;
        int nb_coef_out;

        double coef_in[3];
        double coef_out[3];
};


struct s_filter_coef *FilterInit(enum e_filter_type filter_type, double acquisition_freq, double low_freq, double high_freq, double quality_coef)
{
	struct s_filter_coef *coef=NULL;
        int i;
        double a, b, c, a1, a2, b1, b2, f;
        double e, e2, e3, o, o2, o3, q2;

        double psi;
        double delta_t;
        double omega_t;
        double omega_zero_t;    // w0 * T
        double omega_zero2_t;   // w0 * T

	/* regular check */
	if (low_freq>=high_freq) {
		logerr("High frequency is lower than low frequency");
		exit(ABORT_ERROR);
	}
	if (high_freq>acquisition_freq) {
		logerr("High frequency is higher than acquisition frequency");
		exit(ABORT_ERROR);
	}
	if (low_freq<=0) {
		logerr("Low frequency must be greater than zero");
		exit(ABORT_ERROR);
	}

	coef=MemCalloc(sizeof(struct s_filter_coef));

	coef->filter_type=filter_type;
        coef->low_frequency=low_freq;
        coef->high_frequency=high_freq;
	coef->acquisition_frequency=acquisition_freq;
	coef->quality_coef=quality_coef;

	f = M_PI / acquisition_freq;

        switch (filter_type)
        {
        case 0:
                break;

        case LOW_PASS:
	        omega_zero_t = 2 * f * high_freq;
	        omega_zero2_t = 2 * f * low_freq;

                if (quality_coef <= 0)
                {
                        logerr("Quality coef cannot be lower or equal than zero");
                        exit(ABORT_ERROR);
                }

                if (quality_coef == 1)
                {
			e = exp( -omega_zero_t );
                        coef->coef_out[1] = 2 * e;
                        coef->coef_out[2] = -exp( -2 * omega_zero_t );
                        coef->coef_in[0] = 1 - e * (1 + omega_zero_t);
                        coef->coef_in[1] = e * ( e + omega_zero_t - 1);
                }
		else 
		{
			q2 = quality_coef * quality_coef;
			if (quality_coef > 1) {
				omega_t = omega_zero_t * sqrt( q2 - 1 );
				psi = quality_coef / sqrt( q2 - 1 );
			} else {
				omega_t = omega_zero_t * sqrt( 1 - q2 );
				psi = quality_coef / sqrt( 1 - q2 );
			}

			delta_t = quality_coef * omega_zero_t;
			e = exp( -delta_t );
			a = cosh( omega_t );
			b = sinh( omega_t );
			c = psi * b;

			coef->coef_out[1] = 2 * e * a;
			coef->coef_out[2] = -exp( -2 * delta_t );
			coef->coef_in[0] = 1 - e * (a + c );
			coef->coef_in[1] = e * ( e - a + c );
		}
                break;

        case LOW_PASS_ALT:
        	omega_zero_t = 2 * f * high_freq;
	        omega_zero2_t = 2 * f * low_freq;

		e = exp( -omega_zero_t );
		e2 = exp( -omega_zero2_t );
		e3 = exp( -omega_zero2_t - omega_zero_t );

		o = omega_zero_t - omega_zero2_t;
		o3 = 1 / (o * omega_zero_t * omega_zero2_t);

                coef->coef_in[0] = (o - omega_zero_t * e2 + omega_zero2_t * e) * o3;
                coef->coef_in[1] = (o * e3 + omega_zero2_t * e2 - omega_zero_t * e) * o3;

                coef->coef_out[1] = e + e2;
                coef->coef_out[2] = -e3 ;
                break;

        case BANDPASS:
                a = f * low_freq;
                b = f * high_freq;

                a = sin( a ) / cos( a );        // == F Bas
                b = sin( b ) / cos( b );        // == F Haut

		a1 = 1 + a;
		a2 = 1 - a;
		b1 = 1 + b;
		b2 = 1 - b;
		c  = 1 / (a1 * b1);

                coef->coef_in[0] = -b * c;
                coef->coef_in[1] = 0;
                coef->coef_in[2] = -coef->coef_in[0];

                coef->coef_out[1] = (a1 * b2 + a2 * b1 ) * c;
                coef->coef_out[2] = -a2 * b2 * c;
                break;
        case HIGH_PASS:
                omega_zero2_t = f * low_freq;

                a = sin( omega_zero2_t ) / cos( omega_zero2_t );        // == F Bas
                b = 1.0 / ((1.0 + a) * (1.0 + a));
		c = -2.0 * b;

                coef->coef_in[0] = b;
                coef->coef_in[1] = c;
                coef->coef_in[2] = b;
                coef->coef_out[1] = c * (a * a - 1);
                coef->coef_out[2] = -(1 - a) * (1 - a) * b;
                break;

        default:
                logerr("Filter type's not recognized");
                exit(ABORT_ERROR);
        }

	return coef;
}

void FilterDo(struct s_filter_coef *coef, double *data_in, double *data_out, unsigned long nb)
{
        double A1, A2, B0, B1, B2;
        double e, old_e = 0, old_old_e = 0;
        double s, old_s = 0, old_old_s = 0;

        if (!data_in || !data_out)
        	return;

        if (coef->filter_type >= BANDPASS) {
                s = old_old_s = old_s = 0.0;
                (*data_in) = data_in[1];
                old_old_e = old_e = (*data_in);
        } else {
                old_old_s = old_s = old_old_e = old_e = (*data_in);
        }

        A1 = coef->coef_out[1];
        A2 = coef->coef_out[2];
        B0 = coef->coef_in[0];
        B1 = coef->coef_in[1];
        B2 = coef->coef_in[2];

        while (nb)
        {
		e = *data_in;
		s = e * B0 + old_e * B1 + old_old_e * B2 + old_s * A1 + old_old_s * A2;
		*data_out = s;

		old_old_s = old_s;
		old_s = s;
		old_old_e = old_e;
		old_e = e;

		data_in++;
		data_out++;
		nb--;
        }
}

void FilterDoReverse(struct s_filter_coef *coef, double *data_in, double *data_out, unsigned long nb)
{
        double A1, A2, B0, B1, B2;
        double e, old_e = 0, old_old_e = 0;
        double s, old_s = 0, old_old_s = 0;

        if (!data_in || !data_out)
                return;

        data_in += nb - 1;
        data_out += nb - 1;

        if (coef->filter_type >= BANDPASS) {
                s = old_old_s = old_s = 0.0;
                (*data_in) = *(data_in-1);
                old_old_e = old_e = (*data_in);
        } else {
                old_old_s = old_s = old_old_e = old_e = (*data_in);
        }

        A1 = coef->coef_out[1];
        A2 = coef->coef_out[2];
        B0 = coef->coef_in[0];
        B1 = coef->coef_in[1];
        B2 = coef->coef_in[2];

        while (nb)
        {
		e = *data_in;
		s = e * B0 + old_e * B1 + old_old_e * B2 + old_s * A1 + old_old_s * A2;
		*data_out = s;

		old_old_s = old_s;
		old_s = s;
		old_old_e = old_e;
		old_e = e;

		data_in--;
		data_out--;
		nb--;
        }
}

void SmoothBufferInt(unsigned int *data, int size, int loop)
{
        #undef FUNC
	#define FUNC "SmoothBufferInt"

	int *tmpbuf;
	int i;

	if (size<5) return;

	tmpbuf=MemMalloc(size*sizeof(int));
	while (loop) {
		tmpbuf[0]=(data[0]*4+data[1]+data[2])/8;
		tmpbuf[1]=(data[0]+data[1]*4+data[2]+data[3])/8;
		for (i=2;i<size-2;i++) {
			tmpbuf[i]=(data[i-2]+data[i-1]+data[i]*4+data[i+1]+data[i+2])/8;
		}
		tmpbuf[i]=(data[i-2]+data[i-1]+data[i]*4+data[i+1])/8;i++;
		tmpbuf[i]=(data[i-2]+data[i-1]+data[i]*4)/8;
		memcpy(data,tmpbuf,size*sizeof(int));
		loop--;
	}
	MemFree(tmpbuf);
}

int CorrelationChar(unsigned char *data, int ldata, unsigned char *dataref, int ldataref)
{
        #undef FUNC
	#define FUNC "CorrelationChar"

	int i,j,total,tmax,pmax;

	if (ldataref>ldata) {
		logerr("the reference signal cannot be bigger than the signal");
		exit(INTERNAL_ERROR);
	}

	tmax=-1;
	pmax=0;
	for (i=0;i<ldata-ldataref;i++) {
		total=0;
		/* unoptimised loop */
		for (j=0;j<ldataref;j++) {
			total+=data[i+j]*dataref[j];
		}
		if (total>tmax) {
			tmax=total;
			pmax=i;
		}
	}
	return pmax;
}
int CorrelationCharStep(unsigned char *data, int ldata, unsigned char *dataref, int ldataref, int step)
{
        #undef FUNC
	#define FUNC "CorrelationChar"

	int i,j,total,tmax,pmax;

	if (ldataref>ldata) {
		logerr("the reference signal cannot be bigger than the signal");
		exit(INTERNAL_ERROR);
	}

	tmax=-1;
	pmax=0;
	for (i=0;i<ldata-ldataref;i+=step) {
		total=0;
		/* unoptimised loop */
		for (j=0;j<ldataref;j++) {
			total+=data[i+j]*dataref[j];
		}
		if (total>tmax) {
			tmax=total;
			pmax=i;
		}
	}
	return pmax;
}
int CorrelationInt(unsigned int *data, int ldata, unsigned int *dataref, int ldataref)
{
        #undef FUNC
	#define FUNC "CorrelationInt"

	double total,tmax;
	int i,j,pmax;

	if (ldataref>ldata) {
		logerr("the reference signal cannot be bigger than the signal");
		exit(INTERNAL_ERROR);
	}

	tmax=-1;
	pmax=0;
	for (i=0;i<ldata-ldataref;i++) {
		total=0;
		/* unoptimised loop */
		for (j=0;j<ldataref;j++) {
			total+=data[i+j]*dataref[j];
		}
		if (total>tmax) {
			tmax=total;
			pmax=i;
		}
	}
	return pmax;
}
/*
------------------------------------------------------------------------------
readable.c: My random number generator, ISAAC.
(c) Bob Jenkins, March 1996, Public Domain
You may use this code in any way you wish, and it is free.  No warrantee.
* May 2008 -- made it not depend on standard.h
------------------------------------------------------------------------------
*/

/* a ub4 is an unsigned 4-byte quantity */
typedef  unsigned int  ub4;

/* external results */
ub4 randrsl[256], randcnt=0;

/* internal state */
static    ub4 mm[256];
static    ub4 aa=0, bb=0, cc=0;


void isaac()
{
	#undef FUNC
	#define FUNC "Isaac functions"

   register ub4 i,x,y;

   cc = cc + 1;    /* cc just gets incremented once per 256 results */
   bb = bb + cc;   /* then combined with bb */

   for (i=0; i<256; ++i)
   {
     x = mm[i];
     switch (i%4)
     {
     case 0: aa = aa^(aa<<13); break;
     case 1: aa = aa^(aa>>6); break;
     case 2: aa = aa^(aa<<2); break;
     case 3: aa = aa^(aa>>16); break;
     }
     aa              = mm[(i+128)%256] + aa;
     mm[i]      = y  = mm[(x>>2)%256] + aa + bb;
     randrsl[i] = bb = mm[(y>>10)%256] + x;

     /* Note that bits 2..9 are chosen from x but 10..17 are chosen
        from y.  The only important thing here is that 2..9 and 10..17
        don't overlap.  2..9 and 10..17 were then chosen for speed in
        the optimized version (rand.c) */
     /* See http://burtleburtle.net/bob/rand/isaac.html
        for further explanations and analysis. */
   }
}


/* if (flag!=0), then use the contents of randrsl[] to initialize mm[]. */
#define mix(a,b,c,d,e,f,g,h) \
{ \
   a^=b<<11; d+=a; b+=c; \
   b^=c>>2;  e+=b; c+=d; \
   c^=d<<8;  f+=c; d+=e; \
   d^=e>>16; g+=d; e+=f; \
   e^=f<<10; h+=e; f+=g; \
   f^=g>>4;  a+=f; g+=h; \
   g^=h<<8;  b+=g; h+=a; \
   h^=a>>9;  c+=h; a+=b; \
}

void randinit(ub4 seed1,ub4 seed2,ub4 seed3)
{
   int i;
   ub4 a,b,c,d,e,f,g,h;
   aa=bb=cc=0;
   a=b=c=d=e=f=g=h=0x9e3779b9;  /* the golden ratio */

   b+=seed1;
   d+=seed2;
   f+=seed3;

   for (i=0; i<256; ++i) mm[i]=randrsl[i]=(ub4)0;

   for (i=0; i<4; ++i)          /* scramble it */
   {
     mix(a,b,c,d,e,f,g,h);
   }

   for (i=0; i<256; i+=8)   /* fill in mm[] with messy stuff */
   {
     a+=randrsl[i  ]; b+=randrsl[i+1]; c+=randrsl[i+2]; d+=randrsl[i+3];
     e+=randrsl[i+4]; f+=randrsl[i+5]; g+=randrsl[i+6]; h+=randrsl[i+7];
     mix(a,b,c,d,e,f,g,h);
     mm[i  ]=a; mm[i+1]=b; mm[i+2]=c; mm[i+3]=d;
     mm[i+4]=e; mm[i+5]=f; mm[i+6]=g; mm[i+7]=h;
   }

   /* do a second pass to make all of the seed affect all of mm */
   for (i=0; i<256; i+=8)
   {
       a+=mm[i  ]; b+=mm[i+1]; c+=mm[i+2]; d+=mm[i+3];
       e+=mm[i+4]; f+=mm[i+5]; g+=mm[i+6]; h+=mm[i+7];
       mix(a,b,c,d,e,f,g,h);
       mm[i  ]=a; mm[i+1]=b; mm[i+2]=c; mm[i+3]=d;
       mm[i+4]=e; mm[i+5]=f; mm[i+6]=g; mm[i+7]=h;
   }
}
unsigned int RandIsaac()
{
	static int init=0;
	static int cpt=256;
	
	if (!init) {
   		srand(time(NULL));
		randinit(rand(),rand(),rand());
		init=1;
	}	
	if (!randcnt) {
		isaac();
		randcnt=256;
	}
	return randrsl[--randcnt];	
}
void RandIsaacForceSeed(ub4 seed1, ub4 seed2, ub4 seed3)
{
	RandIsaac();
	randinit(seed1,seed2,seed3);
}

unsigned int _FastRand(unsigned int *zeseed)
{
	#undef FUNC
	#define FUNC "FastRand"
	*zeseed=(214013*(*zeseed)+2531011);
	return ((*zeseed)>>16)&0x7FFF;
}

#undef __FILENAME__

/************************************
	end of mini-library
********************************EOF*/
