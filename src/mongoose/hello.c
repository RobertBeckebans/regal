#include <stdio.h>
#include <string.h>
#include "mongoose.h"

static int begin_request(struct mg_connection *conn)
{
  const struct mg_request_info *request_info = mg_get_request_info(conn);

  char content[1024];
  int content_length = snprintf(content, sizeof(content),
                                "Hello from mongoose! Remote port: %d",
                                request_info->remote_port);
  mg_printf(conn,
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: %d\r\n"        // Always set Content-Length
            "\r\n"
            "%s",
            content_length, content);
  // Mark as processed
  return 1;
}

int main(void)
{
  struct mg_context *ctx;
  struct mg_callbacks callbacks;
  const char *options[] = {"listening_ports", "8080", NULL};

  memset(&callbacks,0,sizeof(callbacks));
  callbacks.begin_request = begin_request;
  ctx = mg_start(&callbacks, NULL, options);
  getchar();  // Wait until user hits "enter"
  mg_stop(ctx);

  return 0;
}
