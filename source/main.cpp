#include <stdio.h>
#include <3ds.h>
#include <stdlib.h>
#include <iostream>

#include "mbedtls/aes.h"

int main()
{
    // Allows to take inputs (Specifically the start button for our case)
    hidInit();
    hidScanInput();

    //Tells us when a key is pressed down
    u32 kDown = hidKeysDown();

    //Allows for graphics (Needed for console INit)
	gfxInitDefault();

	//gfxSet3D(true); //Uncomment if using stereoscopic 3D
	consoleInit(GFX_TOP, NULL); //Change this line to consoleInit(GFX_BOTTOM, NULL) if using the bottom screen.

	mbedtls_aes_context aes;

	mbedtls_aes_init( &aes );
	
	unsigned char key[32] = {'p', 'a', 's', 's', 'w', 'o', 'r', 'd', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	unsigned char iv[16] = { 14, 31, 6, 126, 18, 12, 36, 70, 100, 9, 42, 51, 111, 84, 3, 25 };
	unsigned char iv2[16] = { 14, 31, 6, 126, 18, 12, 36, 70, 100, 9, 42, 51, 111, 84, 3, 25 };
	unsigned char input [128] = { 's', 'e', 'c', 'r', 'e', 't', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	unsigned char output[128];
	unsigned char outputReadable[128];
	unsigned char outputAgain[128];
	unsigned char outputAgainReadable[128];
	
	size_t input_len = 16;
	size_t output_len = 0;
	
	
	
	std::cout << "Unencrypted message: " << std::endl;	
	std::cout << input << std::endl;
	
	if(mbedtls_aes_setkey_enc( &aes, key, 256 )  ==  0) {
		if(mbedtls_aes_crypt_cbc( &aes, MBEDTLS_AES_ENCRYPT, input_len, iv, input, output) != 0) {
			std::cout << "There was an error setting the key" << std::endl;
		}
	} else {
			std::cout << "There was an error setting the key" << std::endl;
	}
	
	std::cout << "Encrypted version of message: " << std::endl;
	
	for(unsigned index = 0; index < 16; ++index)
		outputReadable[index] = output[index];
	
	std::cout << outputReadable << std::endl;
	
	mbedtls_aes_setkey_dec( &aes, key, 256 );
	mbedtls_aes_crypt_cbc( &aes, MBEDTLS_AES_DECRYPT, 16, iv2, output, outputAgain);
	
	std::cout << "Decrypted version of message: " << std::endl;
	
	for(unsigned index = 0; index < 16; ++index)
		outputAgainReadable[index] = outputAgain[index];
	
		std::cout << outputAgainReadable << std::endl;
	
	// Main loop
	while (aptMainLoop())
	{
		if (kDown & KEY_START)
			break; //Break in order to return to hbmenu

		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}
