# Basic Network Information

## List all network interfaces (NICs)
ifconfig

## Cleaner, modern version
ipconfig getifaddr en0

## Show detailed interface info
networksetup -listallhardwareports

## Check your MAC address
ifconfig en0 | grep ether

## Show routing table
netstat -rn

## Display DNS servers
scutil --dns



# Deep Packet Inspection with tcpdump


## List available interfaces
tcpdump -D

## Capture Wi-Fi traffic (basic)
sudo tcpdump -i en0

## Capture specific host (e.g., google.com)
sudo tcpdump -i en0 host 142.250.80.46

## Capture specific port (e.g., HTTP)
sudo tcpdump -i en0 port 80

## Save to file for analysis
sudo tcpdump -i en0 -w capture.pcap

## Read from file
tcpdump -r capture.pcap -nn -X



# Network Connectivity Testing

## Ping: Test basic connectivity and latency
ping google.com

## Traceroute: See the path/route taken
traceroute google.com

## Alternative with more detail
mtr google.com  # Install: brew install mtr

## Check open ports on your machine
sudo lsof -i -P | grep LISTEN

## Scan remote ports (if permitted)
nc -zv google.com 80 443

## DNS lookup
dig google.com
nslookup google.com

## Who owns an IP/Domain
whois google.com

### 1. Find your gateway
netstat -rn | grep default

### 2. Ping it (should be <5ms)
ping 192.168.1.1  # Your gateway IP

### 3. Ping beyond it
ping 8.8.8.8  # Google's DNS

### 4. Compare latencies
 Gateway: ~1ms (local)
 Google: ~10-50ms (internet)



# Examine Your Network Configuration

## Complete network configuration
ifconfig -a

## Specific interface details
ifconfig en0

## Wi-Fi details
/System/Library/PrivateFrameworks/Apple80211.framework/Versions/Current/Resources/airport -I

## DHCP info (how you got your IP)
ipconfig getpacket en0

## Renew DHCP lease
sudo ipconfig set en0 DHCP

## Show ARP table (IP to MAC mappings)
arp -a

## Flush DNS cache
sudo dscacheutil -flushcache; sudo killall -HUP mDNSResponder



# Local Server Experimentation

## Start a simple HTTP server
python3 -m http.server 8000

## Now from another terminal, examine:
curl -v http://localhost:8000
## Watch the request/response headers

## In another terminal, capture the traffic:
sudo tcpdump -i lo0 port 8000 -A



# Virtual Networks with Docker

## Install Docker Desktop
brew install --cask docker

## Create isolated networks
docker network create my-network

## Run containers on that network
docker run -d --name server --network my-network nginx
docker run -it --name client --network my-network alpine sh

## From client container:
ping server

This demonstrates internal DNS resolution and container networking



# Build a Mini Lab
Scenario: Simulate Corporate Network
## 1. Create VLAN-like separation using interfaces
### Create virtual interface (alias)
sudo ifconfig en0 alias 192.168.100.1 netmask 255.255.255.0

## 2. Enable Internet Sharing (creates NAT)
### System Settings → General → Sharing → Internet Sharing
### Your Mac becomes a router.

## 3. Examine the NAT table
sudo natpmpd  # NAT daemon
### Or use: sudo pfctl -s nat

## 4. Watch DHCP leases
cat /var/db/dhcpd_leases



#Key Files on macOS

## Network configuration
/etc/resolv.conf          # DNS servers (generated)
/etc/hosts               # Local DNS overrides
/etc/pf.conf             # Packet filter (firewall) rules
/Library/Preferences/SystemConfiguration/  # Network prefs

## Logs
/var/log/wifi.log        # Wi-Fi events
/var/log/system.log      # General system (including network)

