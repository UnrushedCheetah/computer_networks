#include <stdio.h>
#include <string.h>

void takeInput(char data[]){
    printf("Enter data: ");
    scanf("%s", data);
}

int calculateParityBits(int m){
    int r = 0;

    while((1 << r) < (m + r + 1)){
        r++;
    }

    return r;
}

void createHamming(int n, int hamming[]){
    int a = 0;

    for(int i = 1; i <= n; i++){
        hamming[i] = -1;
    }

    while((1 << a) <= n){
        hamming[1 << a] = 0;
        a++;
    }
}

void insertDataBits(char data[], int hamming[], int n){
    int index = 0;

    for(int i = n; i >= 1; i--){

        if((i & (i - 1)) == 0){
            continue;
        }

        hamming[i] = data[index] - '0';
        index++;
    }
}

void calculateParity(int hamming[], int n){

    int parity = 1;

    while(parity <= n){

        int value = 0;

        for(int i = 1; i <= n; i++){

            if((i & parity) && i != parity){
                value ^= hamming[i];
            }
        }

        hamming[parity] = value;

        parity <<= 1;
    }
}

void printHamming(int hamming[], int n){

    for(int i = n; i >= 1; i--){
        printf("%d", hamming[i]);
    }

    printf("\n");
}

void introduceError(int hamming[], int position){

    if(hamming[position] == 0)
        hamming[position] = 1;
    else
        hamming[position] = 0;
}

int detectError(int hamming[], int n){

    int parity = 1;
    int errorPosition = 0;

    while(parity <= n){

        int value = 0;

        for(int i = 1; i <= n; i++){

            if(i & parity){
                value ^= hamming[i];
            }
        }

        if(value != 0){
            errorPosition += parity;
        }

        parity <<= 1;
    }

    return errorPosition;
}

void correctError(int hamming[], int position){

    if(position == 0)
        return;

    hamming[position] ^= 1;
}

int main(){

    char data[20];
    int hamming[101];

    takeInput(data);

    int m = strlen(data);

    int r = calculateParityBits(m);

    int n = m + r;

    createHamming(n, hamming);

    insertDataBits(data, hamming, n);

    calculateParity(hamming, n);

    printf("\nGenerated Hamming Code : ");
    printHamming(hamming, n);

    int position;

    printf("\nEnter the position to introduce error (1-%d): ", n);
    scanf("%d", &position);

    introduceError(hamming, position);

    printf("\nReceived Code : ");
    printHamming(hamming, n);

    int error = detectError(hamming, n);

    if(error == 0){
        printf("\nNo Error Detected.\n");
    }
    else{
        printf("\nError Detected at Position : %d\n", error);

        correctError(hamming, error);

        printf("\nCorrected Code : ");
        printHamming(hamming, n);
    }

    return 0;
}
