import socket
import time

def start_client(host, port):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((host, port))

    try:
        while True:
            message = input("Enter message to send: ")
            if message.lower() == 'exit':
                break
            client.send(message.encode('utf-8'))
            response = client.recv(1024)
            print(f"Received from server: {response.decode('utf-8')}")
    except KeyboardInterrupt:
        pass
    finally:
        client.close()

if __name__ == "__main__":
    while True:
        try:
            start_client("172.20.16.52", 55555)
        except ConnectionRefusedError:
            print("Server is not available, retrying in 5 seconds...")
            time.sleep(5)
