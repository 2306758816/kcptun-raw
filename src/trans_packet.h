#include <openssl/aes.h>

#define MTU 1440

#define FIRST_SYN UINT_MAX - 2
#define REPLY_SYN_ACK UINT_MAX - 1
#define REPLY_ACK UINT_MAX

struct trans_packet_state {
  unsigned int seq;
  unsigned int ack;
};

struct packet_info {
  char dest_ip[128];
  char source_ip[128];
  uint16_t dest_port;
  uint16_t source_port;
  void (*on_packet_recv)(char*, uint16_t, char*, int);
  int is_server;
  struct trans_packet_state state;
  int disable_seq_update;
  int syn_only;
};

int packet_send_sd;
int packet_recv_sd;

char* aes_ckey;
char* aes_vec;
AES_KEY aes_key;

void init_packet(struct packet_info* packetinfo);
int send_packet(struct packet_info* packetinfo, char* source_payload, int payloadlen, unsigned int flag);

void set_packet_recv_nonblocking();
void set_packet_send_nonblocking();
void check_packet_recv(struct packet_info* packetinfo);
