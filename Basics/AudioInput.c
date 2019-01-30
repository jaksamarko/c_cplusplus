#include <stdio.h>

#include <windows.h>
#include <winsock2.h>
#include <math.h>

#define abs(val) (val<0?val*-1:val)
#define MAX_INTERVAL 4

#define BUFFSIZE 3
#define PORT 6969
#define ADDRESS "192.168.0.255"
#define NUMPTS (1100)

int sampleRate = 8000;

HWAVEIN      hWaveIn;
WAVEHDR      WaveInHdr;

struct sockaddr_in server_addr = { 0 }, client_addr = { 0 };
int conn_fd;
short int waveIn[NUMPTS];

double norm(short int *t, const int n) {
    int i;
    double sum=0;
    for(i=0;i<n;sum+=(double)t[i++]);
    return sum/(double)n;
}

void fallback(MMRESULT res, char *err) {
    if (res) {
        printf(err);
        exit(-1);
    }
}

void initAudio(WAVEFORMATEX *pF) {
    pF->wFormatTag=WAVE_FORMAT_PCM;     // simple, uncompressed format
    pF->nChannels=1;                    //  1=mono, 2=stereo
    pF->nSamplesPerSec=sampleRate;      // 44100
    pF->nAvgBytesPerSec=sampleRate*2;   // = nSamplesPerSec * n.Channels * wBitsPerSample/8
    pF->nBlockAlign=2;                  // = n.Channels * wBitsPerSample/8
    pF->wBitsPerSample=16;              //  16 for high quality, 8 for telephone-grade
    pF->cbSize=0;
}

float getAudio() {
    WaveInHdr.lpData = (LPSTR)waveIn;
    WaveInHdr.dwBufferLength = NUMPTS*2;
    WaveInHdr.dwBytesRecorded=0;
    WaveInHdr.dwUser = 0L;
    WaveInHdr.dwFlags = 0L;
    WaveInHdr.dwLoops = 0L;
    waveInPrepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));

    fallback(waveInAddBuffer(hWaveIn, &WaveInHdr, sizeof(WAVEHDR)),"Cannot create buffer");
    fallback(waveInStart(hWaveIn),"Cannot start record");

    return norm(waveIn,NUMPTS);
}

void sendData(int sock, unsigned char *datBuff, int n) {
    if(sendto(sock,datBuff,n,0,(struct sockaddr_in *)&server_addr, sizeof(server_addr))!=n) {
        printf("-%s",WSAGetLastError());
    }
}

int main(int argc, char*argv[]) {
    float v;
    unsigned char sV[4];

    memset(waveIn,0,NUMPTS*sizeof(short int));

    WAVEFORMATEX pFormat;
    initAudio(&pFormat);

    conn_fd = INVALID_SOCKET;

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    // Create a socket
      conn_fd = socket(AF_INET, SOCK_DGRAM, 0);
      if (conn_fd < 0)
      {
        printf("*** ERROR - socket() failed \n");
        exit(-1);
      }

    memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr(ADDRESS);

	conn_fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	int broadcastPermission = 1;
	if (setsockopt(conn_fd, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission,sizeof(broadcastPermission)) < 0){
       fprintf(stderr, "setsockopt error");
       exit(1);
   }

	if (conn_fd == INVALID_SOCKET) {
		perror("socket");
		printf("%s",WSAGetLastError());
		return -1;
	}

    fallback(waveInOpen(&hWaveIn, 0,&pFormat,0L, 0L, WAVE_FORMAT_DIRECT),"Cannot init audio!");
    printf("Ready!");
    v=100;
    float temp=0;
    do {
        v=fabs(getAudio());
        sV[0]=sV[1]=sV[2]=0;
        sV[1+(int)v%3]=(int)fmax(pow(v,1.9),2)*(v>1.5);
        //sV[0]=sV[1]=sV[2]=v;
        temp+=1;

        printf("%.1lf %d %d %d\n",v,sV[1],sV[2],sV[3]);
        sendData(conn_fd,sV,3);
        /*v+=2;
        getch();*/
        do {} while (waveInUnprepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR))==WAVERR_STILLPLAYING);
    } while(1);
    waveInClose(hWaveIn);
    close(conn_fd);

    return 0;
}
