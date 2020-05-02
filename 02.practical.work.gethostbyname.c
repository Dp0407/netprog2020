#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <netdb.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

char *addrtype(int addrtype) {
        switch(addrtype) {
                case AF_INET:
                        return "AF_INET";
                case AF_INET6:
                        return "AF_INET6";
        }
        return "Unknown";
}

int main(int argc, char **argv) {
        struct hostent *hostname = 0;
        int i = 0;

        if (argc < 2) {
                printf("Usage: %s <hostname>\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        hostname = gethostbyname(argv[1]);

        if (!hostname) {
                printf("Lookup Failed: %s\n", hstrerror(h_errno));
                return 0;
        }

        i = 0;
        while(hostname->h_addr_list[i] != NULL) {
                printf("h_addr_list[i]: %s\n", inet_ntoa( (struct in_addr) *((struct in_addr *) hostname->h_addr_list[i])));
                i++;
        }

        return 0;
}
