syntax: netfilter-test "host" <br>
sample: netfilter-test test.gilgil.net <br>

For test <br>
additional - open another terminal and input these <br>
===========<br>
sudo iptables -F <br>
sudo iptables -A OUTPUT -j NFQUEUE --queue-num 0 <br>
sudo iptables -A INPUT -j NFQUEUE --queue-num 0 <br>
