#include <pcap.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void usage() {
        printf("syntax: pcap-test <interface>\n");
        printf("sample: pcap-test wlan0\n");
}

typedef struct {
        char* dev_;
} Param;

Param param = {
        .dev_ = NULL
};

bool parse(Param* param, int argc, char* argv[]) {
        if (argc != 2) {
                usage();
                return false;
        }
        param->dev_ = argv[1];
        return true;
}

int main(int argc, char* argv[]) {
        unsigned char eth[100000];
        int sum = 0;
        if (!parse(&param, argc, argv))
                return -1;

        char errbuf[PCAP_ERRBUF_SIZE];
        pcap_t* pcap = pcap_open_live(param.dev_, BUFSIZ, 1, 1000, errbuf);
        if (pcap == NULL) {
                fprintf(stderr, "pcap_open_live(%s) return null - %s\n", param.dev_, errbuf);
                return -1;
        }

        while (true) {
            struct pcap_pkthdr* header;
            const u_char* packet;
            int res = pcap_next_ex(pcap, &header, &packet);
            if (res == 0) continue;
            if (res == PCAP_ERROR || res == PCAP_ERROR_BREAK) {
                printf("pcap_next_ex return %d(%s)\n", res, pcap_geterr(pcap));
                break;
            }
            memcpy(eth, packet,header->caplen);
            if(eth[23] != 6){
                printf("not tcp \n\n");
                goto skip;
            }
			unsigned char x = eth[14];
			int alal = 8;
			sum = eth[14] & 0x0F;
			int tcp_start = 14 + sum * 4;
			printf("==========Ethernet Header==========\nDst Mac : ");
            for(int i = 0;i<12;i++){
                printf("%02x",eth[i]);
			if(i != 5 && i != 11) printf(":");
            if(i == 5)printf("\nSrc Mac : ");
            }
            printf("\n");
			printf("==========IP Header==========\n");
			printf("Src IP : ");
			for(int i = 26;i<34;i++){
		  		printf("%d",eth[i]);
		  		if(i != 29 && i!= 33)printf(".");
		  		if(i == 29)printf("\nDst IP : ");
			}
			printf("\n==========TCP Header==========\nSrc Port : ");
			int src_port = (eth[tcp_start] << 8) | eth[tcp_start + 1];
			int dst_port = (eth[tcp_start + 2] << 8) | eth[tcp_start + 3];
			printf("%d\n",src_port);
			printf("Dst Port : ");
			printf("%d",dst_port);
			printf("\n");
			unsigned char y = eth[tcp_start+4];
			int tcp_header_len = ((eth[tcp_start + 12] >> 4) & 0x0F) * 4;
			int last = tcp_header_len + tcp_start;
			for(int i = last;i<last+20;i++){
				printf("%02x ",eth[i]);
			}
			printf("\n");
			skip:;
        }
	pcap_close(pcap);
}


