#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <zlib.h>

#ifdef _WIN32
#include <libbase64.h>
#endif

int main(void) {
    char buffer_in [256] = {"Conan is a MIT-licensed, Open Source package manager for C and C++ development "
                            "for C and C++ development, allowing development teams to easily and efficiently "
                            "manage their packages and dependencies across platforms and build systems."};
    char buffer_out [256] = {0};

    z_stream defstream;
    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;
    defstream.avail_in = (uInt) strlen(buffer_in);
    defstream.next_in = (Bytef *) buffer_in;
    defstream.avail_out = (uInt) sizeof(buffer_out);
    defstream.next_out = (Bytef *) buffer_out;

    deflateInit(&defstream, Z_BEST_COMPRESSION);
    deflate(&defstream, Z_FINISH);
    deflateEnd(&defstream);

    printf("Uncompressed size is: %lu\n", strlen(buffer_in));
    printf("Compressed size is: %lu\n", strlen(buffer_out));

    printf("ZLIB VERSION: %s\n", zlibVersion());
    
    #ifdef _WIN32
    int flags = 0;
    const char * src = "YW55IGNhcm5hbCBwbGVhc3VyZQ==";
    char enc[128], dec[128];
    size_t srclen = strlen(src);
    size_t enclen, declen;

    base64_decode(src, srclen, enc, &enclen, flags);
    enc[enclen] = '\0';
    printf("decoded size (\"any carnal pleasure\"): %zu\n", enclen);
    base64_encode(enc, enclen, dec, &declen, flags);
    dec[declen] = '\0';
    printf("%s\n", dec);
    #endif
    
    return EXIT_SUCCESS;
}
