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
#include "fossil/mockup/network.h"
#include <string.h>

xmock_network_t* xmock_network_create(const char *host, const char *request, const char *response) {
    xmock_network_t *network = (xmock_network_t *)malloc(sizeof(xmock_network_t));
    if (network == NULL) {
        perror("Failed to allocate memory for network mock");
        exit(EXIT_FAILURE);
    }
    network->host = _custom_xmock_core_strdup(host);
    network->request = _custom_xmock_core_strdup(request);
    network->response = _custom_xmock_core_strdup(response);
    network->next = NULL;
    return network;
}

const char* xmock_network_request(xmock_network_t *network, const char *request) {
    if (strcmp(request, network->request) == 0) {
        return network->response;
    }
    return NULL;
}

void xmock_network_erase(xmock_network_t *network) {
    free(network->host);
    free(network->request);
    free(network->response);
    free(network);
}
