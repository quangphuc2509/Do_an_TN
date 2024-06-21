import socket
import threading

def handle_client(client_socket, client_address):
    print(f"Client {client_address} connected.")
    while True:
        try:
            message = client_socket.recv(1024)
            if not message:
                break
            print(f"Received from {client_address}: {message.decode('utf-8')}")
            client_socket.send("ACK".encode('utf-8'))
        except ConnectionResetError:
            break
    print(f"Client {client_address} disconnected.")
    client_socket.close()

def start_server(port):
    host = socket.gethostbyname(socket.gethostname())
    server = socket.socket()
    server.bind((host, port))
    server.listen(5)
    print(f"Server listening on {host}:{port}")

    # while True:
    client_socket, client_address = server.accept()
    client_handler = threading.Thread(target=handle_client, args=(client_socket, client_address))
    client_handler.start()

if __name__ == "__main__":
    start_server(55555)
# socket.AF_INET, socket.SOCK_STREAM