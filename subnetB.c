#include <stdio.h>

void takeInput(int ip[], int *cidr){

    printf("Enter base IP address (e.g., 192.168.10.0): ");
    scanf("%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);

    printf("Enter CIDR prefix (e.g., 26): ");
    scanf("%d", cidr);
}

void findSubnetMask(int cidr, int mask[]){

    int bits = cidr;

    for(int i = 0; i < 4; i++){

        if(bits >= 8){
            mask[i] = 255;
            bits -= 8;
        }
        else if(bits > 0){
            mask[i] = 256 - (1 << (8 - bits));
            bits = 0;
        }
        else{
            mask[i] = 0;
        }
    }
}

void findNetworkAddress(int ip[], int mask[], int network[]){

    for(int i = 0; i < 4; i++){
        network[i] = ip[i] & mask[i];
    }
}

void findBroadcastAddress(int network[], int mask[], int broadcast[]){

    for(int i = 0; i < 4; i++){
        broadcast[i] = network[i] | (255 - mask[i]);
    }
}

void printIP(int ip[]){

    printf("%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
}

void printSubnetMask(int mask[]){

    printf("%d.%d.%d.%d", mask[0], mask[1], mask[2], mask[3]);
}

void demonstrateSubnets(int network[], int cidr){

    int extraBits = 4 - (cidr % 4);

    if(cidr >= 31){
        printf("\nSubnetting cannot be demonstrated for CIDR /%d.\n", cidr);
        return;
    }

    int subnetBits = 2;

    if(cidr + subnetBits > 30){
        subnetBits = 30 - cidr;
    }

    if(subnetBits <= 0){
        printf("\nNo additional subnet bits available.\n");
        return;
    }

    int numberOfSubnets = 1 << subnetBits;
    int newCIDR = cidr + subnetBits;

    int newMask[4];

    findSubnetMask(newCIDR, newMask);

    int blockSize = 0;

    for(int i = 0; i < 4; i++){

        if(newMask[i] != 255){
            blockSize = 256 - newMask[i];
            break;
        }
    }

    printf("\n--- Subnetting Demonstration ---\n");

    printf("Borrowed Bits : %d\n", subnetBits);
    printf("Number of Subnets : %d\n", numberOfSubnets);

    printf("New CIDR : /%d\n", newCIDR);

    printf("New Subnet Mask : ");
    printSubnetMask(newMask);
    printf("\n");

    printf("\nSubnets:\n");

    int subnet[4];
    int broadcast[4];

    for(int i = 0; i < numberOfSubnets; i++){

        for(int j = 0; j < 4; j++){
            subnet[j] = network[j];
        }

        for(int j = 0; j < 4; j++){

            if(newMask[j] != 255){

                subnet[j] = network[j] + i * blockSize;

                break;
            }
        }

        findBroadcastAddress(subnet, newMask, broadcast);

        printf("\nSubnet %d\n", i + 1);

        printf("Network Address : ");
        printIP(subnet);

        printf("\nBroadcast Address : ");
        printIP(broadcast);

        printf("\n");
    }
}

int main(){

    int ip[4];
    int mask[4];
    int network[4];
    int broadcast[4];

    int cidr;

    takeInput(ip, &cidr);

    if(cidr < 0 || cidr > 32){

        printf("\nInvalid CIDR prefix.\n");
        return 0;
    }

    findSubnetMask(cidr, mask);

    findNetworkAddress(ip, mask, network);

    findBroadcastAddress(network, mask, broadcast);

    printf("\n--- Subnet Information ---\n");

    printf("IP Address : ");
    printIP(ip);

    printf("\nCIDR : /%d", cidr);

    printf("\nSubnet Mask : ");
    printSubnetMask(mask);

    printf("\nNetwork Address : ");
    printIP(network);

    printf("\nBroadcast Address : ");
    printIP(broadcast);

    printf("\n");

    demonstrateSubnets(network, cidr);

    return 0;
}