#ifndef ANYCAST_H
#define ANYCAST_H

#include "net/rpl/rpl.h"
#include "net/netstack.h"
#include "net/mac/frame802154.h"
#include "net/uip-ds6.h"
#include "orpl-log.h"
#include "routing-set.h"

#define EDC_DIVISOR 128
#define EDC_TICKS_TO_METRIC(edc) (uint16_t)((edc) / (CONTIKIMAC_CONF_CYCLE_TIME / EDC_DIVISOR))

#define EXTRA_ACK_LEN 10

#define DO_ACK            1 /* Set if a link-layer ack must be sent */
#define IS_ANYCAST        2 /* Set if the packet is a anycast */
#define FROM_SUBDODAG     4 /* Set if the packet is coming from the sub-dodag (going upwards) */
#define IS_RECOVERY       8 /* Set if the packet comes from false positive recovery */

extern int forwarder_set_size;
extern int neighbor_set_size;
extern rimeaddr_t anycast_addr_up;
extern rimeaddr_t anycast_addr_down;
extern rimeaddr_t anycast_addr_nbr;
extern rimeaddr_t anycast_addr_recover;
extern uint16_t hbh_edc;
extern uint16_t e2e_edc;
extern uint32_t anycast_count_incomming;
extern uint32_t anycast_count_acked;
extern uint32_t routing_set_merged_count;
extern int sending_bloom;
extern int is_edc_root;

void orpl_print_ranks();
uint8_t orpl_parse_802154_frame(uint8_t *data, uint8_t len, uint16_t *neighbor_edc);
void anycast_packet_sent();
void anycast_packet_received();
void update_e2e_edc();
int is_in_subdodag(uip_ipaddr_t *ipv6);
int is_reachable_neighbor(uip_ipaddr_t *ipv6);
void anycast_set_packetbuf_addr();
void orpl_trickle_callback(rpl_instance_t *instance);
void broadcast_acked(const rimeaddr_t *receiver);
void broadcast_done();
void bloom_broacast_failed();
void blacklist_insert(uint32_t seqno);
int blacklist_contains(uint32_t seqno);
void acked_down_insert(uint32_t seqno, uint16_t id);
int acked_down_contains(uint32_t seqno, uint16_t id);
void received_noip();
void anycast_init(const uip_ipaddr_t *my_ipaddr, int is_root, int up_only);

#endif