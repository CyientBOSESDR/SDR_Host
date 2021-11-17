

#ifndef __SECURITY_INTF_H__
#define __SECURITY_INTF_H__

#define SDRID_LEN 6
#define MISSIONID_LEN 8

#define MAX_PEERS 16

#define MAX_PAIRKEY_LEN 32
#define MAX_TSECKEY_LEN 32
#define MAX_BCASTKEY_LEN 32

typedef struct
{
    uint8_t sdrid[SDRID_LEN];
    uint8_t pairkey[MAX_PAIRKEY_LEN];
} peer_info_t;

typedef struct
{
	uint8_t mission_id[MISSIONID_LEN];
/* Interval(in minutes) for network authentication */
	uint32_t na_interval;
/* Interval(in minutes) for user authentication */
	uint32_t ua_interval;
/* Mission completer period(in minutes) */
	uint32_t mission_period;
/* Interval(in minutes) for update session keys */
    uint32_t upssk_interval;
    uint8_t host_addr[SDRID_LEN];
    uint16_t transeckey_length;
	uint8_t transeckey[MAX_TSECKEY_LEN];
    uint16_t bcastkey_length;
	uint8_t broadcastkey[MAX_BCASTKEY_LEN];
    uint16_t nof_peers;
    uint16_t pairkey_length;
/*  Followed by nof_peers peer_info_t structures size */
	peer_info_t peers[MAX_PEERS]; 
} security_params_t;

int authenticate_user(uint8_t *pin, int is_first, security_params_t *security_params );

#endif /*__SECURITY_INTF_H__ */
