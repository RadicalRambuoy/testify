#include<stdio.h>
#include<stdint.h>

int main(){
    unsigned int a,b,c,d,n,hosts,size,i;
    uint32_t ip,mask,newmask,network,broadcast,first,last;
    int hostbits,borrowed = 0;

    printf("Enter network address: ");
    scanf("%u.%u.%u.%u", &a,&b,&c,&d);

    if (a>255||b>255||c>255||d>255){
        printf("Invalid IP address\n");
        return 0;
    }

    ip = (a<<24) | (b<<16) | (c<<8) | d;
    if(a>=1&&a<=126){
        printf("IP class: A\n");
        mask = 0xFF000000;
        hostbits = 24;
    }
    else if(a==127){
        printf("127.x.x.x is reserved for loopback address\n");
        return 0;
    }
    else if(a>=128&&a<=191){
        printf("IP class: B\n");
        mask = 0xFFFF0000;
        hostbits = 16;
    }
    else if(a>=192&&a<=223){
        printf("IP class: C\n");
        mask = 0xFFFFFF00;
        hostbits = 8;
    }
    else{
        printf("Invalid or reserved IP address\n");
        return 0;
    }

    printf("Enter number of subnets: ");
    scanf("%u", &n);
    while((1U << borrowed) < n) borrowed++;
    if(borrowed > hostbits - 2){
        printf("Too many subnets for this network\n");
        return 0;
    }

    hostbits = hostbits - borrowed;
    newmask = mask | (((1U << borrowed) - 1) << hostbits);
    size = 1U << hostbits;
    hosts = size - 2;

    printf("\nBits borrowed: %d", borrowed);
    printf("\nSubnet mask: %u.%u.%u.%u",
            (newmask >> 24) & 255,
            (newmask >> 16) & 255,
            (newmask >> 8) & 255,
            newmask & 255);
    printf("\nUsable hosts per subnet: %u\n", hosts);

    for(i = 0; i < n; i++){
        network = (ip & mask) + i * size;
        broadcast = network | (~newmask);
        first = network + 1;
        last = broadcast - 1;

        printf("\nSubnet %u", i + 1);
        printf("\nNetwork Address: %u.%u.%u.%u",
                (network >> 24) & 255,
                (network >> 16) & 255,
                (network >> 8) & 255,
                network & 255);
        printf("\nBroadcast: %u.%u.%u.%u",
                (broadcast >> 24) & 255,
                (broadcast >> 16) & 255,
                (broadcast >> 8) & 255,
                broadcast & 255);
        printf("\nFirst host: %u.%u.%u.%u",
                (first >> 24) & 255,
                (first >> 16) & 255,
                (first >> 8) & 255,
                first & 255);
        printf("\nLast host: %u.%u.%u.%u",
                (last >> 24) & 255,
                (last >> 16) & 255,
                (last >> 8) & 255,
                last & 255);
        printf("\nUsable hosts: %u\n", hosts);
    }
    return 0;
}