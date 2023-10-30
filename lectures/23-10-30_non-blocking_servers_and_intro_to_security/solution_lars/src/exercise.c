#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h> 

#include "./exercise.h"
#include "./sha256.h"

/*
 * Gets a sha256 hash of specified data, sourcedata. The hash itself is
 * placed into the given variable 'hash'. Any size can be created, but a
 * a normal size for the hash would be given by the global variable
 * 'SHA256_HASH_SIZE', that has been defined in sha256.h
 */
void get_data_sha(const char* sourcedata, hashdata_t hash, uint32_t data_size, 
    int hash_size)
{
  SHA256_CTX shactx;
  unsigned char shabuffer[hash_size];
  sha256_init(&shactx);
  sha256_update(&shactx, sourcedata, data_size);
  sha256_final(&shactx, shabuffer);

  for (int i=0; i<hash_size; i++)
  {
      hash[i] = shabuffer[i];
  }
}

/*
 * Combine a password and salt together and hash the result to form the 
 * 'signature'. The result is written to the 'hash' variable
 */
void get_signature(char* password, char* salt, hashdata_t hash)
{
    char to_hash[strlen(password) + strlen(salt)];

    // TODO Put some code in here so that to_hash contains the password and 
    // salt and is then hashed

    // You can use this to confirm that you are hashing what you think you are
    // hashing 

    memcpy(to_hash, password, strlen(password));
    memcpy(to_hash+strlen(password), salt, strlen(salt));
    get_data_sha(to_hash, hash, strlen(password)+strlen(salt), SHA256_HASH_SIZE);

    for (uint8_t i=0; i<strlen(to_hash); i++)
    {
        printf("[%c]", to_hash[i]);
    }
    printf("\n");
}

int main()
{
    int PASSWORD_LEN = 16;
    int network_socket, c;
    struct sockaddr_in serv_addr;
    
    char password[PASSWORD_LEN];
    char salt[65] = 
        "0123456789012345678901234567890123456789012345678901234567890123\0";
 
    fprintf(stdout, "Enter your password: ");
    scanf("%16s", password);
    while ((c = getchar()) != '\n' && c != EOF);
    // Clean up password string as otherwise some extra chars can sneak in.
    for (int i=strlen(password); i<PASSWORD_LEN; i++)
    {
        password[i] = '\0';
    }

    fprintf(stdout, "Using salt: %s\n", salt);

    // Register the signature
    hashdata_t signature;
    get_signature(password, salt, signature);

    // Setup the socket and connect. Note hard coded port and host
    char* ip = "0.0.0.0";
    char* port = "12345";
    network_socket = compsys_helper_open_clientfd(ip, port);

    // Send the request
    write(network_socket, signature, SHA256_HASH_SIZE);
    
    close(network_socket);

    exit(EXIT_SUCCESS);
}
