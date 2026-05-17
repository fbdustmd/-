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
    if (!parse(&param, argc, argv))return -1;
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
        /*여기서 부터 내가 임의로 추가한 코드*/
        memcpy(eth, packet, header->caplen); // 여기서 eth 배열 안에 packet 의 정보를 담음 
        if (header->caplen < 54) continue; // 여기서 이더넷,ip,tcp 헤더파일 만큼도 없으면 이상한거이므로 예외처리
        if (eth[23] != 6) { // 여기서 tcp 연결인지 판단
            printf("not tcp \n\n\n\n");
            continue;
        }
        unsigned char x = eth[14];
        int alal = 8;
        sum = eth[14] & 0x0F; /*ip 패킷의 첫번째에는 ip 패킷이 얼마나 
        큰지 판단할수 있는 값이 들어있음. 최소 4에 최대 12임. 
        그게 바이트 형식이므로 그거 판단하는 용도*/
        int tcp_start = 14 + sum * 4;  /*이더넷은 14 고정이므로 +14*/
        printf("==========Ethernet Header==========\nDst Mac : ");
        for (int i = 0; i < 12; i++) { // 여기서 이더넷 헤더 안에 있는 값 출력
            printf("%02x", eth[i]);
            if (i != 5 && i != 11) printf(":");
            if (i == 5) printf("\nSrc Mac : ");
        }//이더넷 헤더는 1~6 == dst mac, 7~12 = src mac 임 
        printf("\n");
        printf("==========IP Header==========\nSrc IP : ");
        for (int i = 26; i < 34; i++) { 
            printf("%d", eth[i]);
            if (i != 29 && i != 33) printf(".");
            if (i == 29) printf("\nDst IP : ");
        }// ip 헤더도 12~16 , 17~20 에 각각 src, dst 값이 있음. 
        printf("\n==========TCP Header==========\nSrc Port : ");
        int src_port = (eth[tcp_start] << 8) | eth[tcp_start + 1];
        int dst_port = (eth[tcp_start + 2] << 8) | eth[tcp_start + 3];
        printf("%d\nDst Port : %d\n", src_port,dst_port);
        int tcp_header_len = ((eth[tcp_start + 12] >> 4) & 0x0F) * 4;
        int last = tcp_header_len + tcp_start;
        int max = 0;
        for (int i = 0; i < header->caplen - last && max < 20; i++) {
            printf("%02x ", eth[i + last]);
            max++;
        } //여기서 남은 패킷 최대 20바이트까지만 출력하게 함
        printf("\n");
    }
    pcap_close(pcap);
}
