#include <stdio.h>

void printDefinition() {
    printf("Subnet := Subnetting is the process of dividing a large IP network into smaller logical networks called subnets.\nEach subnet allows devices to communicate efficiently, improving network performance, security, and manageability.\n\n");
    printf("Subnet mask := A subnet mask is a 32-bit number used in IP addressing to separate the network portion of an IP address from the host portion.\n\n");
}

void ipDetails(int ipAddress[]) {
    int a = ipAddress[0];
    
    if(a >= 0 && a <= 126) {
        printf("\nClass                     : A\n");
        printf("IP Range                  : 0.0.0.0 - 126.255.255.255\n");
        printf("First Binary Octet        : 0XXX XXXX\n");
        printf("Default Subnet Mask.      : 255.0.0.0\n");
        printf("Networks Possible         : 2^7\n");
        printf("Hosts per Network         : 2^24 - 2\n");
    }
    else if (a == 127)
    {
        printf("\nClass                     : A\n");
        printf("First Octet Decimal Range : 127.0.0.0 - 127.255.255.255\n");
        printf("Default Subnet Mask.      : 255.0.0.0\n");
        printf("Networks Possible         : 2^7\n");
        printf("Hosts per Network         : 2^24 - 2\n");
        printf("Special Address           : Loopback Address\n");
        printf("Definition                : Used to test the TCP/IP stack. Packets never leave the local computer.\n");
    }
    else if (a >= 128 && a <= 191)
    {
        printf("\nClass                     : B\n");
        printf("First Octet Decimal Range : 128.0.0.0 - 191.255.255.255\n");
        printf("First Binary Octet        : 10XX XXXX\n");
        printf("Default Subnet Mask.      : 255.255.0.0\n");
        printf("Networks Possible         : 2^14\n");
        printf("Hosts per Network         : 2^16 - 2\n");
    }
    else if (a >= 192 && a <= 223)
    {
        printf("\nClass                     : C\n");
        printf("First Octet Decimal Range : 192.0.0.0 - 223.255.255.255\n");
        printf("First Binary Octet        : 110X XXXX\n");
        printf("Default Subnet Mask.      : 255.255.255.0\n");
        printf("Networks Possible         : 2^21\n");
        printf("Hosts per Network         : 2^8 - 2\n");
    }
    else if (a >= 224 && a <= 239)
    {
        printf("\nClass                     : D\n");
        printf("First Octet Decimal Range : 224.0.0.0 - 239.255.255.255\n");
        printf("First Binary Octet        : 1110 XXXX\n");
        printf("Purpose                   : Multicast\n");
    }
    else if (a >= 240 && a <= 255)
    {
        printf("\nClass                     : E\n");
        printf("First Octet Decimal Range : 240.0.0.0 - 255.255.255.255\n");
        printf("First Binary Octet        : 1111 XXXX\n");
        printf("Purpose                   : Experimental / Research\n");
    }
    else
    {
        printf("\nInvalid IP Address!\n");
    }

}

int main() {
    printDefinition();
    
    int ipAddress[4];
    printf("Enter IP Address: ");
    scanf("%d.%d.%d.%d", &ipAddress[0], &ipAddress[1], &ipAddress[2], &ipAddress[3]);
    
    ipDetails(ipAddress);

    return 0;
}
