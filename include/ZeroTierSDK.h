/*
 * ZeroTier One - Network Virtualization Everywhere
 * Copyright (C) 2011-2016  ZeroTier, Inc.  https://www.zerotier.com/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * This defines the external C++ API for the ZeroTier SDK's service
 */

#ifndef ZT_ZEROTIERSDK_H
#define ZT_ZEROTIERSDK_H

#include <sys/socket.h>

/****************************************************************************/
/* Defines                                                                  */
/****************************************************************************/

#define SDK_MTU                       1200                             // FIXME: ZT_MAX_MTU, usually 
#define UNIX_SOCK_BUF_SIZE            1024*1024
#define ZT_PHY_POLL_INTERVAL          50                               // in ms
// picoTCP 
#define MAX_PICO_FRAME_RX_BUF_SZ      ZT_MAX_MTU * 128
// TCP
#define DEFAULT_TCP_TX_BUF_SZ         1024 * 1024
#define DEFAULT_TCP_RX_BUF_SZ         1024 * 1024
#define DEFAULT_TCP_TX_BUF_SOFTMAX    DEFAULT_TCP_TX_BUF_SZ * 0.80
#define DEFAULT_TCP_TX_BUF_SOFTMIN    DEFAULT_TCP_TX_BUF_SZ * 0.20
#define DEFAULT_TCP_RX_BUF_SOFTMAX    DEFAULT_TCP_RX_BUF_SZ * 0.80
#define DEFAULT_TCP_RX_BUF_SOFTMIN    DEFAULT_TCP_RX_BUF_SZ * 0.20
// UDP
#define DEFAULT_UDP_TX_BUF_SZ         ZT_MAX_MTU
#define DEFAULT_UDP_RX_BUF_SZ         ZT_MAX_MTU * 10

#define ZT_SDK_RPC_DIR_PREFIX         "rpc.d"

#define ZT_SDK_VERSION_MAJOR          1
#define ZT_SDK_VERSION_MINOR          0
#define ZT_SDK_VERSION_REVISION       0

#define ZT_MAX_IPADDR_LEN             64
#define ZT_ID_LEN                     10
#define ZT_VER_STR_LEN                6
#define ZT_HOME_PATH_MAX_LEN          128

/****************************************************************************/
/* Socket API Signatures                                                    */
/****************************************************************************/

#define ZT_SETSOCKOPT_SIG int fd, int level, int optname, const void *optval, socklen_t optlen
#define ZT_GETSOCKOPT_SIG int fd, int level, int optname, void *optval, socklen_t *optlen
#define ZT_SENDMSG_SIG int fd, const struct msghdr *msg, int flags
#define ZT_SENDTO_SIG int fd, const void *buf, size_t len, int flags, const struct sockaddr *addr, socklen_t addrlen
#define ZT_RECV_SIG int fd, void *buf, size_t len, int flags
#define ZT_RECVFROM_SIG int fd, void *buf, size_t len, int flags, struct sockaddr *addr, socklen_t *addrlen
#define ZT_RECVMSG_SIG int fd, struct msghdr *msg,int flags
#define ZT_SEND_SIG int fd, const void *buf, size_t len, int flags
#define ZT_WRITE_SIG int fd, const void *buf, size_t len
#define ZT_READ_SIG int fd, void *buf, size_t len
#define ZT_SOCKET_SIG int socket_family, int socket_type, int protocol
#define ZT_CONNECT_SIG int fd, const struct sockaddr *addr, socklen_t addrlen
#define ZT_BIND_SIG int fd, const struct sockaddr *addr, socklen_t addrlen
#define ZT_LISTEN_SIG int fd, int backlog
#define ZT_ACCEPT4_SIG int fd, struct sockaddr *addr, socklen_t *addrlen, int flags
#define ZT_ACCEPT_SIG int fd, struct sockaddr *addr, socklen_t *addrlen
#define ZT_CLOSE_SIG int fd
#define ZT_GETSOCKNAME_SIG int fd, struct sockaddr *addr, socklen_t *addrlen
#define ZT_GETPEERNAME_SIG int fd, struct sockaddr *addr, socklen_t *addrlen
#define ZT_FCNTL_SIG int fd, int cmd, int flags
#define ZT_SYSCALL_SIG long number, ...

/****************************************************************************/
/* SDK Socket API (ZeroTier Service Controls)                               */
/* Implemented in SDKService.cpp                                            */ 
/****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Start core ZeroTier service (generates identity)
 */
void zts_start(const char *path);

/**
 * Stops the core ZeroTier service
 */
void zts_stop();

/**
 * Join a network
 */
void zts_join_network(const char * nwid);

/**
 * Join a network - Just create the dir and conf file required, don't instruct the core to do anything
 */
void zts_join_network_soft(const char * filepath, const char * nwid);

/**
 * Leave a network
 */
void zts_leave_network(const char * nwid);

/**
 * Leave a network - Only delete the .conf file, this will prevent the service from joining upon next startup
 */
void zts_leave_network_soft(const char * filepath, const char * nwid);

/**
 * Return the home path for this instance of ZeroTier
 * FIXME: double check this is correct on all platforms
 */
void zts_get_homepath(char *homePath, const int len);

/**
 * Provides core ZeroTier service version
 */
void zts_core_version(char *ver);

/**
 * Provides core SDK service version
 */
void zts_sdk_version(char *ver);

/**
 * Get device ID
 * 10-digit hex + NULL byte
 */
int zts_get_device_id(char *devID);

/**
 * Check whether the service is running
 */
int zts_service_running();

/**
 * Returns whether any IPv6 address has been assigned to the SockTap for this network
 * - This is used as an indicator of readiness for service for the ZeroTier core and stack
 */
int zts_has_ipv4_address(const char *nwid);

/**
 * Returns whether any IPv4 address has been assigned to the SockTap for this network
 * - This is used as an indicator of readiness for service for the ZeroTier core and stack
 */
int zts_has_ipv6_address(const char *nwid);

/**
 * Returns whether any address has been assigned to the SockTap for this network
 * - This is used as an indicator of readiness for service for the ZeroTier core and stack
 */
int zts_has_address(const char *nwid);

/**
 * Get IPV4 Address for this device on a given network
 * FIXME: Only returns first address found for given protocol and network (should be enough for now)
 */
void zts_get_ipv4_address(const char *nwid, char *addrstr, const int addrlen);

/**
 * Get IPV6 Address for this device on a given network
 * FIXME: Only returns first address found for given protocol and network (should be enough for now)
 */
void zts_get_ipv6_address(const char *nwid, char *addrstr, const int addrlen);

/**
 * Returns a 6PLANE IPv6 address given a network ID and zerotier ID
 */
void zts_get_6plane_addr(char *addr, const char *nwid, const char *devID);

/**
 * Returns an RFC 4193 IPv6 address given a network ID and zerotier ID
 */
void zts_get_rfc4193_addr(char *addr, const char *nwid, const char *devID);

/**
 * Return the number of peers on this network
 */
unsigned long zts_get_peer_count();

/**
 * Get the IP address of a peer if a direct path is available
 */
int zts_get_peer_address(char *peer, const char *devID);

/**
 * Enable HTTP control plane (traditionally used by zerotier-cli)
 * - Allows one to control the ZeroTier core via HTTP requests
 * FIXME: Implement
 */
void zts_enable_http_control_plane();

/**
 * Disable HTTP control plane (traditionally used by zerotier-cli)
 * - Allows one to control the ZeroTier core via HTTP requests
 * FIXME: Implement
 */
void zts_disable_http_control_plane();

/****************************************************************************/
/* SDK Socket API (Socket User Controls)                                    */
/* - These functions are designed to work just like regular socket calls    */
/*   but are provisioned and handled by ZeroTier                            */
/* Implemented in Socket.c                                                  */ 
/****************************************************************************/

/**
 * Creates a socket
 */
int zts_socket(ZT_SOCKET_SIG);

 /**
 * Connect a socket to a remote host
 */
int zts_connect(ZT_CONNECT_SIG);

/**
 * Bind a socket to a local address
 */
int zts_bind(ZT_BIND_SIG);

/**
 * Accept a connection
 */
#if defined(__linux__)
	int zts_accept4(ZT_ACCEPT4_SIG);
#endif

/**
 * Accept a connection
 */
int zts_accept(ZT_ACCEPT_SIG);

/**
 * Listen for incoming connections
 */
int zts_listen(ZT_LISTEN_SIG);

/**
 * Set socket options
 */
int zts_setsockopt(ZT_SETSOCKOPT_SIG);

/**
 * Get socket options
 */
int zts_getsockopt(ZT_GETSOCKOPT_SIG);

/**
 * Get socket name
 */
int zts_getsockname(ZT_GETSOCKNAME_SIG);

/**
 * Get a peer name
 */
int zts_getpeername(ZT_GETPEERNAME_SIG);

/**
 * Close a socket
 */
int zts_close(ZT_CLOSE_SIG);

/**
 * Issue file control commands on a socket
 */
int zts_fcntl(ZT_FCNTL_SIG);

/**
 * Send data to a remote host
 */
ssize_t zts_sendto(ZT_SENDTO_SIG);

/**
 * Send a message to a remote host
 */
ssize_t zts_sendmsg(ZT_SENDMSG_SIG);

/**
 * Receive data from a remote host
 */
ssize_t zts_recvfrom(ZT_RECVFROM_SIG);

/**
 * Receive a message from a remote host
 */
ssize_t zts_recvmsg(ZT_RECVMSG_SIG);

/****************************************************************************/
/* SocketTap Multiplexer Functionality --- DONT CALL THESE DIRECTLY         */
/* - This section of the API is used to implement the general socket        */
/*   controls. Basically this is designed to handle socket provisioning     */
/*   requests when no SocketTap is yet initialized, and as a way to         */
/*   determine which SocketTap is to be used for a particular connect() or  */ 
/*   bind() call                                                            */
/****************************************************************************/

namespace ZeroTier
{
    class picoTCP;
    struct Connection;
    extern ZeroTier::picoTCP *picostack;
}

/**
 * Creates a new Connection objects and keeps it in UnassignedConnections
 * until a connect() or bind() call is made, at which point it is assigned
 * to the appropriate SocketTap.
 */
int zts_multiplex_new_socket(ZT_SOCKET_SIG);

/**
 * Given a file descriptor, looks up the relevant Connection object and then
 * searches for a SocketTap with an appropriate route. Once found, the 
 * Connection object will be assigned to that SocketTap and a connection 
 * to the remote host will be attempted.
 */
int zts_multiplex_new_connect(ZT_CONNECT_SIG);

/**
 * 
 */
int zts_multiplex_new_bind(ZT_BIND_SIG);

/****************************************************************************/
/* SDK Socket API Helper functions --- DONT CALL THESE DIRECTLY             */
/****************************************************************************/

/**
 * Don't call this directly, use 'zts_start()'
 */
void *_start_service(void *thread_id);

/****************************************************************************/
/* Debug                                                                    */
/****************************************************************************/

#include <pthread.h>
#include <sys/syscall.h>
#include <sys/types.h>

#define ZT_DEBUG_LEVEL     5 // Set this to adjust what you'd like to see in the debug traces

#define ZT_MSG_ERROR       1 // Errors
#define ZT_MSG_TRANSFER    2 // RX/TX specific statements
#define ZT_MSG_INFO        3 // Information which is generally useful to any developer
#define ZT_MSG_EXTRA       4 // If nothing in your world makes sense
#define ZT_MSG_FLOW        5 // High-level flow messages
#define ZT_FILENAMES       true
#define ZT_COLOR           true

// Debug output colors
#if defined(__APPLE__)
    #include "TargetConditionals.h"
#endif
#if defined(ZT_COLOR) && !defined(__ANDROID__) && !defined(TARGET_OS_IPHONE) && !defined(TARGET_IPHONE_SIMULATOR) && !defined(__APP_FRAMEWORK__)
  #define ZT_RED   "\x1B[31m"
  #define ZT_GRN   "\x1B[32m"
  #define ZT_YEL   "\x1B[33m"
  #define ZT_BLU   "\x1B[34m"
  #define ZT_MAG   "\x1B[35m"
  #define ZT_CYN   "\x1B[36m"
  #define ZT_WHT   "\x1B[37m"
  #define ZT_RESET "\x1B[0m"
#else
  #define ZT_RED
  #define ZT_GRN
  #define ZT_YEL
  #define ZT_BLU
  #define ZT_MAG
  #define ZT_CYN
  #define ZT_WHT
  #define ZT_RESET
#endif

// filenames
#if ZT_FILENAMES
  #if ZT_FULL_FILENAME_PATH
    #define ZT_FILENAME __FILE__ // show the entire mess
  #else
    #define ZT_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) // short
  #endif
#else
  #define ZT_FILENAME // omit filename
#endif

#ifdef __linux__
  #define ZT_THREAD_ID 0 // (long)getpid()
#elif __APPLE__
  #define ZT_THREAD_ID 0 // (long)syscall(SYS_thread_selfid)
#endif

#if defined(__JNI_LIB__)
      #include <jni.h>
#endif
#if defined(__ANDROID__)
    #include <android/log.h>
    #define ZT_LOG_TAG "ZTSDK"
#endif

 #if ZT_DEBUG_LEVEL >= ZT_MSG_ERROR
  #define DEBUG_ERROR(fmt, args...) fprintf(stderr, ZT_RED "ZT_ERROR[%ld] : %14s:%4d:%25s: " fmt   \
    "\n" ZT_RESET, ZT_THREAD_ID, ZT_FILENAME, __LINE__, __FUNCTION__, ##args)
 #else
  #define DEBUG_ERROR(fmt, args...)
 #endif
 
 #if ZT_DEBUG_LEVEL >= ZT_MSG_INFO
  #if defined(__ANDROID__)
    #define DEBUG_INFO(fmt, args...) ((void)__android_log_print(ANDROID_LOG_VERBOSE, ZT_LOG_TAG,   \
      "ZT_INFO : %14s:%4d:%20s: " fmt "\n", ZT_FILENAME, __LINE__, __FUNCTION__, ##args))
    #define DEBUG_BLANK(fmt, args...) ((void)__android_log_print(ANDROID_LOG_VERBOSE, ZT_LOG_TAG,  \
      "ZT_INFO : %14s:%4d:" fmt "\n", ZT_FILENAME, __LINE__, __FUNCTION__, ##args))
    #define DEBUG_ATTN(fmt, args...) ((void)__android_log_print(ANDROID_LOG_VERBOSE, ZT_LOG_TAG,   \
      "ZT_INFO : %14s:%4d:%25s: " fmt "\n", ZT_FILENAME, __LINE__, __FUNCTION__, ##args))
    #define DEBUG_STACK(fmt, args...) ((void)__android_log_print(ANDROID_LOG_VERBOSE, ZT_LOG_TAG,  \
      "ZT_STACK: %14s:%4d:%25s: " fmt "\n", ZT_FILENAME, __LINE__, __FUNCTION__, ##args))
  #else
    #define DEBUG_INFO(fmt, args...) fprintf(stderr,                                                                   \
      "ZT_INFO [%ld] : %14s:%4d:%25s: " fmt "\n", ZT_THREAD_ID, ZT_FILENAME, __LINE__, __FUNCTION__, ##args)
    #define DEBUG_ATTN(fmt, args...) fprintf(stderr, ZT_CYN                                                            \
      "ZT_ATTN [%ld] : %14s:%4d:%25s: " fmt "\n" ZT_RESET, ZT_THREAD_ID, ZT_FILENAME, __LINE__, __FUNCTION__, ##args)
    #define DEBUG_STACK(fmt, args...) fprintf(stderr, ZT_YEL                                                           \
      "ZT_STACK[%ld] : %14s:%4d:%25s: " fmt "\n" ZT_RESET, ZT_THREAD_ID, ZT_FILENAME, __LINE__, __FUNCTION__, ##args)
    #define DEBUG_BLANK(fmt, args...) fprintf(stderr,                                                                  \
      "ZT_INFO [%ld] : %14s:%4d:" fmt "\n", ZT_THREAD_ID, ZT_FILENAME, __LINE__, ##args)
  #endif
 #else
  #define DEBUG_INFO(fmt, args...)
  #define DEBUG_BLANK(fmt, args...)
  #define DEBUG_ATTN(fmt, args...)
  #define DEBUG_STACK(fmt, args...)
 #endif
 
 #if ZT_DEBUG_LEVEL >= ZT_MSG_TRANSFER
  #if defined(__ANDROID__)
    #define DEBUG_TRANS(fmt, args...) ((void)__android_log_print(ANDROID_LOG_VERBOSE, ZT_LOG_TAG,  \
      "ZT_TRANS : %14s:%4d:%25s: " fmt "\n", ZT_FILENAME, __LINE__, __FUNCTION__, ##args))
  #else
    #define DEBUG_TRANS(fmt, args...) fprintf(stderr, ZT_GRN "ZT_TRANS[%ld] : %14s:%4d:%25s: " fmt \
      "\n" ZT_RESET, ZT_THREAD_ID, ZT_FILENAME, __LINE__, __FUNCTION__, ##args)
  #endif
 #else
  #define DEBUG_TRANS(fmt, args...)
 #endif
 
 #if ZT_DEBUG_LEVEL >= ZT_MSG_EXTRA
   #if defined(__ANDROID__)
    #define DEBUG_EXTRA(fmt, args...) ((void)__android_log_print(ANDROID_LOG_VERBOSE, ZT_LOG_TAG, \
      "ZT_EXTRA : %14s:%4d:%25s: " fmt "\n", ZT_FILENAME, __LINE__, __FUNCTION__, ##args))
  #else
    #define DEBUG_EXTRA(fmt, args...) fprintf(stderr, \
      "ZT_EXTRA[%ld] : %14s:%4d:%25s: " fmt "\n", ZT_THREAD_ID, ZT_FILENAME, __LINE__, __FUNCTION__, ##args)
  #endif
 #else
  #define DEBUG_EXTRA(fmt, args...)
 #endif

#if ZT_DEBUG_LEVEL >= ZT_MSG_FLOW
   #if defined(__ANDROID__)
    #define DEBUG_FLOW(fmt, args...) ((void)__android_log_print(ANDROID_LOG_VERBOSE, ZT_LOG_TAG, \ 
      "ZT_FLOW : %14s:%4d:%25s: " fmt "\n", ZT_FILENAME, __LINE__, __FUNCTION__, ##args))
  #else
    #define DEBUG_FLOW(fmt, args...) fprintf(stderr, "ZT_FLOW [%ld] : %14s:%4d:%25s: " fmt "\n", \
      ZT_THREAD_ID, ZT_FILENAME, __LINE__, __FUNCTION__, ##args)
  #endif
 #else
  #define DEBUG_FLOW(fmt, args...)
 #endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ZT_ZEROTIERSDK_H