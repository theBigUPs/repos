import time
import socket



class NetworkLayer:
  def __init__(self, host, port):
    self.host = host
    self.port = port
    self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    self.socket.bind((self.host, self.port))

  def send(self, packet, host, port):
    self.socket.sendto(packet, (host, port))

  def receive(self):
    data, address = self.socket.recvfrom(1024)
    return data


class RDT:
  def __init__(self, network_layer):
    self.network_layer = network_layer
    self.sequence_number = 0
    self.acknowledgement_number = 0
    self.window_size = 1
    self.packet_buffer = {}

  def send(self, data):
    packet = self.create_packet(data)
    self.network_layer.send(packet)
    self.sequence_number += 1
    self.packet_buffer[self.sequence_number] = packet
    timer = Timer(self.timeout, self.resend, [packet])
    timer.start()

  def resend(self, packet):
    self.network_layer.send(packet)
    timer = Timer(self.timeout, self.resend, [packet])
    timer.start()

  def receive(self):
    packet = self.network_layer.receive()
    if self.validate_packet(packet):
      self.acknowledgement_number = packet['sequence_number'] + 1
      self.send_ack()
      return packet['data']
    else:
      return None

  def send_ack(self):
    packet = self.create_packet(None, acknowledgement=True)
    self.network_layer.send(packet)

  def create_packet(self, data, acknowledgement=False):
    packet = {
      'sequence_number': self.sequence_number,
      'acknowledgement_number': self.acknowledgement_number,
      'data': data,
      'acknowledgement': acknowledgement
    }
    return packet

  def validate_packet(self, packet):
    if packet['sequence_number'] == self.acknowledgement_number:
      return True
    else:
      return False






















class RDT2:
    def __init__(self, network_layer):
        self.network_layer = network_layer
        self.sequence_number = 0
        self.acknowledgement_number = 0
        self.window_size = 1
        self.packet_buffer = {}

def send(self, data):
    packet = self.create_packet(data)
    self.network_layer.send(packet)
    self.sequence_number += 1
    self.packet_buffer[self.sequence_number] = packet
    timer = Timer(self.timeout, self.resend, [packet])
    timer.start()

def resend(self, packet):
    self.network_layer.send(packet)
    timer = Timer(self.timeout, self.resend, [packet])
    timer.start()

def receive(self):
    packet = self.network_layer.receive()
    if self.validate_packet(packet):
      self.acknowledgement_number = packet['sequence_number'] + 1
      self.send_ack()
      return packet['data']
    else:
      return None

def send_ack(self):
    packet = self.create_packet(None, acknowledgement=True)
    self.network_layer.send(packet)

def create_packet(self, data, acknowledgement=False):
    packet = {
      'sequence_number': self.sequence_number,
      'acknowledgement_number': self.acknowledgement_number,
      'data': data,
      'acknowledgement': acknowledgement
    }
    return packet

def validate_packet(self, packet):
    if packet['sequence_number'] == self.acknowledgement_number:
      return True
    else:
      return False















network_layer = NetworkLayer('localhost', 8000)
rdt = RDT(network_layer)


network_layer = NetworkLayer('localhost', 8001)
rdt2 = RDT2(network_layer)








#rdt 2.0
import random

# Constants for the RDT 2.0 protocol
PACKET_LOSS_PROBABILITY = 0.1
ACK_LOSS_PROBABILITY = 0.1

def send_packet(packet):
    """Sends a packet over the network. Returns True if the packet was successfully
    transmitted, or False if the packet was lost.
    """
    if random.random() < PACKET_LOSS_PROBABILITY:
        # Packet was lost
        return False
    else:
        # Packet was transmitted successfully
        return True

def send_ack(ack):
    """Sends an acknowledgement over the network. Returns True if the acknowledgement
    was successfully transmitted, or False if it was lost.
    """
    if random.random() < ACK_LOSS_PROBABILITY:
        # Acknowledgement was lost
        return False
    else:
        # Acknowledgement was transmitted successfully
        return True

def rdt_send(packet):
    """Sends a packet reliably using the RDT 2.0 protocol. Returns True if the
    packet was successfully transmitted, or False if the transmission failed.
    """
    while True:
        # Send packet
        if send_packet(packet):
            # Wait for acknowledgement
            if send_ack(True):
                # Packet was successfully transmitted
                return True
        # Retransmit packet

def rdt_receive():
    """Receives a packet reliably using the RDT 2.0 protocol. Returns the packet if
    it was successfully received, or None if the packet was lost.
    """
    while True:
        # Wait for packet
        packet = receive_packet()
        if packet is not None:
            # Send acknowledgement
            if send_ack(True):
                # Return received packet
                return packet
        # Packet was lost, wait for retransmission








#rdt 1.0


import random

# Constants for the RDT 1.0 protocol
PACKET_LOSS_PROBABILITY = 0.1

def send_packet(packet):
    """Sends a packet over the network. Returns True if the packet was successfully
    transmitted, or False if the packet was lost.
    """
    if random.random() < PACKET_LOSS_PROBABILITY:
        # Packet was lost
        return False
    else:
        # Packet was transmitted successfully
        return True

def rdt_send(packet):
    """Sends a packet reliably using the RDT 1.0 protocol. Returns True if the
    packet was successfully transmitted, or False if the transmission failed.
    """
    while True:
        # Send packet
        if send_packet(packet):
            # Packet was successfully transmitted
            return True
        # Retransmit packet

def rdt_receive():
    """Receives a packet reliably using the RDT 1.0 protocol. Returns the packet if
    it was successfully received, or None if the packet was lost.
    """
    while True:
        # Wait for packet
        packet = receive_packet()
        if packet is not None:
            # Return received packet
            return packet
        # Packet was lost, wait for retransmission

















#rdt3.0


import random

# Constants for the RDT protocol
PACKET_LOSS_PROBABILITY = 0.1
ACK_LOSS_PROBABILITY = 0.1
MAX_RETRIES = 3

def send_packet(packet):
    """Sends a packet over the network. Returns True if the packet was successfully
    transmitted, or False if the packet was lost.
    """
    if random.random() < PACKET_LOSS_PROBABILITY:
        # Packet was lost
        return False
    else:
        # Packet was transmitted successfully
        return True

def send_ack(ack):
    """Sends an acknowledgement over the network. Returns True if the acknowledgement
    was successfully transmitted, or False if it was lost.
    """
    if random.random() < ACK_LOSS_PROBABILITY:
        # Acknowledgement was lost
        return False
    else:
        # Acknowledgement was transmitted successfully
        return True

def rdt_send(packet):
    """Sends a packet reliably using the RDT protocol. Returns True if the
    packet was successfully transmitted, or False if the transmission failed.
    """
    retries = 0
    while True:
        # Send packet
        if send_packet(packet):
            # Wait for acknowledgement
            if send_ack(True):
                # Packet was successfully transmitted
                return True
            else:
                # Acknowledgement was lost, retransmit packet
                retries += 1
                if retries >= MAX_RETRIES:
                    # Maximum number of retries reached, transmission failed
                    return False
        # Packet was lost, retransmit packet
        retries += 1
        if retries >= MAX_RETRIES:
            # Maximum number of retries reached, transmission failed
            return False

def rdt_receive():
    """Receives a packet reliably using the RDT protocol. Returns the packet if
    it was successfully received, or None if the packet was lost.
    """
    while True:
        # Wait for packet
        packet = receive_packet()
        if packet is not None:
            # Send acknowledgement
            if send_ack(True):
                # Return received packet
                return packet
            else:
                # Acknowledgement was not received, wait for retransmission
                continue
        # Packet was lost, wait for retransmission





