/**
 * HTTP Proxy - Starter Template
 * 
 * Serves local files or proxies requests to a backend.
 * Pure HTTP/1.1, GET only, no TLS.
 * 
 * Usage: ./proxy -b <port> -r <host> -p <port>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <errno.h>

#define BUFFER_SIZE 4096
#define DEFAULT_LOCAL_PORT 18443
#define DEFAULT_REMOTE_HOST "127.0.0.1"
#define DEFAULT_REMOTE_PORT 18444

/* Global configuration */
int local_port = DEFAULT_LOCAL_PORT;
char remote_host[256] = DEFAULT_REMOTE_HOST;
int remote_port = DEFAULT_REMOTE_PORT;

/**
 * Get MIME type based on file extension
 */
const char *get_mime_type(const char *path) {
    const char *ext = strrchr(path, '.');
    if (!ext) return "application/octet-stream";
    
    if (strcmp(ext, ".html") == 0) return "text/html; charset=UTF-8";
    if (strcmp(ext, ".txt") == 0) return "text/plain; charset=UTF-8";
    
    return "application/octet-stream";
}

/**
 * Send an HTTP error response
 */
void send_error(int client_fd, int status_code, const char *status_msg, const char *body) {
    char response[BUFFER_SIZE];
    int body_len = strlen(body);
    int response_len = snprintf(response, sizeof(response),
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        status_code, status_msg, body_len, body);
    
    send(client_fd, response, response_len, 0);
}

/**
 * TODO: Implement serve_local_file()
 * Serve local file at `path` to client. Return 404 if not found.
 */
void serve_local_file(int client_fd, const char *path) {
    // TODO
    send_error(client_fd, 500, "Internal Server Error", "Not implemented");
}

/**
 * TODO: Implement proxy_request()
 * Proxy request to backend and relay response. Return 0 on success, -1 on failure.
 */
int proxy_request(int client_fd, const char *request, int request_len) {
    // TODO
    return -1;
}

/**
 * TODO: Implement handle_client()
 * Parse HTTP request, serve local files or proxy to backend.
 */
void handle_client(int client_fd) {
    // TODO
    send_error(client_fd, 500, "Internal Server Error", "Not implemented");
}

/**
 * Parse command-line arguments
 */
void parse_args(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-b") == 0 && i + 1 < argc) {
            local_port = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-r") == 0 && i + 1 < argc) {
            strncpy(remote_host, argv[++i], sizeof(remote_host) - 1);
        } else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            remote_port = atoi(argv[++i]);
        }
    }
}

int main(int argc, char *argv[]) {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    int optval = 1;

    parse_args(argc, argv);

    /* Create socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    /* Set socket options */
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    /* Setup server address */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(local_port);

    /* Bind */
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    /* Listen */
    if (listen(server_fd, 10) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("HTTP Proxy listening on port %d\n", local_port);
    printf("Backend server: %s:%d\n", remote_host, remote_port);

    /* Main accept loop */
    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }

        handle_client(client_fd);
        close(client_fd);
    }

    close(server_fd);
    return 0;
}