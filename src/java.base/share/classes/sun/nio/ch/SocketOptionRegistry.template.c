/*
 * Copyright (c) 2008, 2020, Oracle and/or its affiliates. All rights reserved.
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */
// @@END_COPYRIGHT@@

#include <stdio.h>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#endif

/* Defines SO_REUSEPORT */
#if !defined(SO_REUSEPORT)
#ifdef _WIN32
#define SO_REUSEPORT 0
#elif defined(__linux__)
#define SO_REUSEPORT 15
#elif defined(AIX) || defined(MACOSX)
#define SO_REUSEPORT 0x0200
#else
#define SO_REUSEPORT 0
#endif
#endif

/* To be able to name the Java constants the same as the C constants without
   having the preprocessor rewrite those identifiers, add PREFIX_ to all
   identifiers matching a C constant. The PREFIX_ is filtered out in the
   makefile. */

// @@START_HERE@@

const char *pre =
"package sun.nio.ch;\n"
"import java.net.SocketOption;\n"
"import java.net.StandardSocketOptions;\n"
"import java.net.ProtocolFamily;\n"
"import java.net.StandardProtocolFamily;\n"
"import java.util.Map;\n"
"import java.util.HashMap;\n"
"class SocketOptionRegistry {\n"
"\n"
"    private SocketOptionRegistry() { }\n"
"\n"
"    private static class RegistryKey {\n"
"        private final SocketOption<?> name;\n"
"        private final ProtocolFamily family;\n"
"        RegistryKey(SocketOption<?> name, ProtocolFamily family) {\n"
"            this.name = name;\n"
"            this.family = family;\n"
"        }\n"
"        public int hashCode() {\n"
"            return name.hashCode() + family.hashCode();\n"
"        }\n"
"        public boolean equals(Object ob) {\n"
"            if (ob == null) return false;\n"
"            if (!(ob instanceof RegistryKey)) return false;\n"
"            RegistryKey other = (RegistryKey)ob;\n"
"            if (this.name != other.name) return false;\n"
"            if (this.family != other.family) return false;\n"
"            return true;\n"
"        }\n"
"    }\n"
"\n"
"    private static class LazyInitialization {\n"
"\n"
"        static final Map<RegistryKey,OptionKey> options = options();\n"
"\n"
"        private static Map<RegistryKey,OptionKey> options() {\n"
"            Map<RegistryKey,OptionKey> map =\n"
"                new HashMap<RegistryKey,OptionKey>();\n";

const char *post =
"\n"
"            return map;\n"
"        }\n"
"    }\n"
"\n"
"    public static OptionKey findOption(SocketOption<?> name, ProtocolFamily family) {\n"
"        RegistryKey key = new RegistryKey(name, family);\n"
"        return LazyInitialization.options.get(key);\n"
"    }\n"
"}\n";

int main(void) {
    printf("%s\n", pre);

    printf("map.put(new RegistryKey(StandardSocketOptions.PREFIX_SO_BROADCAST, Net.UNSPEC), new OptionKey(SOL_SOCKET, %d));\n", SO_BROADCAST);
    printf("map.put(new RegistryKey(StandardSocketOptions.PREFIX_SO_KEEPALIVE, Net.UNSPEC), new OptionKey(SOL_SOCKET, %d));\n", SO_KEEPALIVE);
    printf("map.put(new RegistryKey(StandardSocketOptions.PREFIX_SO_LINGER, Net.UNSPEC), new OptionKey(SOL_SOCKET, %d));\n", SO_LINGER);
    printf("map.put(new RegistryKey(StandardSocketOptions.PREFIX_SO_SNDBUF, Net.UNSPEC), new OptionKey(SOL_SOCKET, %d));\n", SO_SNDBUF);
    printf("map.put(new RegistryKey(StandardSocketOptions.PREFIX_SO_RCVBUF, Net.UNSPEC), new OptionKey(SOL_SOCKET, %d));\n", SO_RCVBUF);
    printf("map.put(new RegistryKey(StandardSocketOptions.PREFIX_SO_REUSEADDR, Net.UNSPEC), new OptionKey(SOL_SOCKET, %d));\n", SO_REUSEADDR);
    printf("map.put(new RegistryKey(StandardSocketOptions.PREFIX_SO_REUSEPORT, Net.UNSPEC), new OptionKey(SOL_SOCKET, %d));\n", SO_REUSEPORT);

    printf("// IPPROTO_TCP is 6\n");
    printf("map.put(new RegistryKey(StandardSocketOptions.PREFIX_TCP_NODELAY, Net.UNSPEC), new OptionKey(6, %d));\n", TCP_NODELAY);

    printf("// IPPROTO_IP is 0\n");
    printf("map.put(new RegistryKey(StandardSocketOptions.PREFIX_IP_TOS, StandardProtocolFamily.INET), new OptionKey(0, %d));\n", IP_TOS);
    printf("map.put(new RegistryKey(StandardSocketOptions.PREFIX_IP_MULTICAST_IF, StandardProtocolFamily.INET), new OptionKey(0, %d));\n", IP_MULTICAST_IF);
    printf("map.put(new RegistryKey(StandardSocketOptions.PREFIX_IP_MULTICAST_TTL, StandardProtocolFamily.INET), new OptionKey(0, %d));\n", IP_MULTICAST_TTL);
    printf("map.put(new RegistryKey(StandardSocketOptions.PREFIX_IP_MULTICAST_LOOP, StandardProtocolFamily.INET), new OptionKey(0, %d));\n", IP_MULTICAST_LOOP);

#ifdef AF_INET6
    printf("// IPPROTO_IPV6 is 41\n");
    printf("map.put(new RegistryKey(StandardSocketOptions.PREFIX_IP_TOS, StandardProtocolFamily.INET6), new OptionKey(41, %d));\n", IPV6_TCLASS);
    printf("map.put(new RegistryKey(StandardSocketOptions.PREFIX_IP_MULTICAST_IF, StandardProtocolFamily.INET6), new OptionKey(41, %d));\n", IPV6_MULTICAST_IF);
    printf("map.put(new RegistryKey(StandardSocketOptions.PREFIX_IP_MULTICAST_TTL, StandardProtocolFamily.INET6), new OptionKey(41, %d));\n", IPV6_MULTICAST_HOPS);
    printf("map.put(new RegistryKey(StandardSocketOptions.PREFIX_IP_MULTICAST_LOOP, StandardProtocolFamily.INET6), new OptionKey(41, %d));\n", IPV6_MULTICAST_LOOP);
#endif

    printf("map.put(new RegistryKey(ExtendedSocketOption.PREFIX_SO_OOBINLINE, Net.UNSPEC), new OptionKey(SOL_SOCKET, %d));\n", SO_OOBINLINE);

    printf("%s\n", post);
    return 0;
}
