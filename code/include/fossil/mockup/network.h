/*
==============================================================================
Author: Michael Gene Brockus (Dreamer)
Email: michaelbrockus@gmail.com
Organization: Fossil Logic
Description: 
    This file is part of the Fossil Logic project, where innovation meets
    excellence in software development. Michael Gene Brockus, also known as
    "Dreamer," is a dedicated contributor to this project. For any inquiries,
    feel free to contact Michael at michaelbrockus@gmail.com.
==============================================================================
*/
#ifndef FOSSIL_MOCK_NETWORK_H
#define FOSSIL_MOCK_NETWORK_H

#include "internal.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Example usage:
// int main() {
//     // Create a network mock for the host and request
//     fossil_mockup_network_t *network = fossil_mockup_network_create("api.example.com", "GET /data HTTP/1.1", "HTTP/1.1 200 OK\nContent-Length: 13\n\nHello, world!");
//
//     // Simulate making a network request using the mocked network
//     const char *response = fossil_mockup_network_request(network, "GET /data HTTP/1.1");
//
//     // Verify the response
//     if (response && strcmp(response, "HTTP/1.1 200 OK\nContent-Length: 13\n\nHello, world!") == 0) {
//         printf("Network request verification succeeded\n");
//     } else {
//         printf("Network request verification failed\n");
//     }
//
//     // Clean up
//     fossil_mockup_network_erase(network);
//
//     return 0;
// }

// Network mock object type
typedef struct fossil_mockup_network {
    char *host;
    char *request;
    char *response;
    struct fossil_mockup_network *next; // for chaining network mocks
} fossil_mockup_network_t;

// Create a new network mock object
fossil_mockup_network_t* fossil_mockup_network_create(const char *host, const char *request, const char *response);

// Perform a network request using the mocked network
const char* fossil_mockup_network_request(fossil_mockup_network_t *network, const char *request);

// Erase the network mock object
void fossil_mockup_network_erase(fossil_mockup_network_t *network);

#ifdef __cplusplus
}
#endif

#endif
