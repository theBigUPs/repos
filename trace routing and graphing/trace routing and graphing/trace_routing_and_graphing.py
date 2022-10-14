import socket


def traceroute(the_url):

    the_url = socket.gethostbyname(the_url)
    port = 54321 #or 33534 for traceroute port 33434
    icmp = socket.getprotobyname("icmp")
    udp = socket.getprotobyname("udp")
    ttl = 1

    while True:
        recv_sock = socket.socket(socket.AF_INET, socket.SOCK_RAW, icmp)
        send_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, udp)
        send_sock.setsockopt(socket.SOL_IP, socket.IP_TTL, ttl)
        
        recv_sock.bind(("",port))#(())
        send_sock.sendto("".encode(),(the_url,port))
        
        curr_adress = None
        curr_name = None

        try:

            curr_adress = recv_sock.recvfrom(512)
            curr_adress = curr_adress[0]

            try:
                curr_name = socket.gethostbyaddr(curr_adress)[0]
                pass
            except socket.error():
                curr_name = curr_adress
                pass

            pass

        except socket.error:
            pass

        finally:
            send_sock.close()
            recv_sock.close()
            pass


        if curr_addr is not None:
                curr_host = "%s (%s)" % (curr_name, curr_addr)
        else:
                curr_host = "*"
        print( "%d\t%s" % (ttl, curr_host))



        ttl = ttl + 1
        if curr_addr == dest_addr or ttl > max_hops:
            break
        
        pass




    pass


traceroute("bing.com")


print("ert")

