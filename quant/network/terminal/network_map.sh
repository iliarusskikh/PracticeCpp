!/bin/bash
# Run to discover your network

echo "=== YOUR MACHINE ==="
ifconfig en0 | grep "inet "
ifconfig en0 | grep "ether "

echo "=== GATEWAY ==="
netstat -rn | grep default

echo "=== LOCAL NETWORK DEVICES ==="
# Ping sweep (be careful, don't overwhelm)
for i in {1..254}; do
  ping -c 1 -W 10 192.168.1.$i > /dev/null 2>&1 && echo "Host up: 192.168.1.$i" &
done
wait

echo "=== ARP TABLE (discovered MACs) ==="
arp -a

echo "=== DNS SERVERS ==="
scutil --dns | grep 'nameserver\[[0-9]*\]'
