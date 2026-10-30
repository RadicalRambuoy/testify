import ipaddress

def print_subnet_info(network, subnet_num):
    print(f"\n=== Subnet {subnet_num} (/25) ===")
    print(f"Subnet Mask:        {network.netmask}")
    print(f"Network ID:         {network.network_address}")
    print(f"Broadcast ID:       {network.broadcast_address}")
    
    hosts = list(network.hosts())
    print(f"Usable Host Range:  {hosts[0]} - {hosts[-1]}")
    print(f"Usable Hosts:       {len(hosts)}")

def main():
    # Base network given in Q4: 192.168.1.0/24
    base_net = ipaddress.ip_network("192.168.1.0/24")
    
    # Divide /24 into 2 equal subnets of prefix /25
    subnets = list(base_net.subnets(new_prefix=25))
    
    for i, subnet in enumerate(subnets, start=1):
        print_subnet_info(subnet, i)

if __name__ == "__main__":
    main()
