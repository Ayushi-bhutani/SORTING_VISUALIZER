# from http.server import BaseHTTPRequestHandler, HTTPServer
# import os

# class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
#     def do_GET(self):
#         if self.path == '/':
#             self.path = '/index.html'
#         elif self.path.startswith('/sort'):
#             algorithm = self.path.split('=')[1]
#             os.system(f'./sort {algorithm}')
#             self.path = f'/{algorithm}_steps.txt'

#         try:
#             file_to_open = open(self.path[1:]).read()
#             self.send_response(200)
#         except Exception as e:
#             print(f'Error: {e}')
#             file_to_open = "File not found"
#             self.send_response(404)

#         self.end_headers()
#         self.wfile.write(bytes(file_to_open, 'utf-8'))

# if __name__ == '__main__':
#     PORT = 8000
#     print(f'Server listening on port {PORT}...')
#     httpd = HTTPServer(('localhost', PORT), SimpleHTTPRequestHandler)
#     httpd.serve_forever()

from http.server import BaseHTTPRequestHandler, HTTPServer
import os

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/':
            self.path = '/index.html'
        
        try:
            # Serve the file from the current directory
            file_to_open = open(self.path[1:], encoding='utf-8').read()
            self.send_response(200)
        except Exception as e:
            file_to_open = f"File not found: {e}"
            self.send_response(404)
        
        self.end_headers()
        self.wfile.write(bytes(file_to_open, 'utf-8'))

if __name__ == '__main__':
    PORT = 8000
    print(f'Server listening on port {PORT}...')
    httpd = HTTPServer(('localhost', PORT), SimpleHTTPRequestHandler)
    httpd.serve_forever()
