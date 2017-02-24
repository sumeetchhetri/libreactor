#ifndef REACTOR_STREAM_H_INCLUDED
#define REACTOR_STREAM_H_INCLUDED

#ifndef REACTOR_STREAM_BLOCK_SIZE
#define REACTOR_STREAM_BLOCK_SIZE 65536
#endif

enum reactor_stream_event
{
  REACTOR_STREAM_EVENT_ERROR,
  REACTOR_STREAM_EVENT_READ,
  REACTOR_STREAM_EVENT_BLOCKED,
  REACTOR_STREAM_EVENT_WRITE,
  REACTOR_STREAM_EVENT_HANGUP,
  REACTOR_STREAM_EVENT_CLOSE
};

enum reactor_stream_state
{
  REACTOR_STREAM_STATE_CLOSED,
  REACTOR_STREAM_STATE_OPEN,
  REACTOR_STREAM_STATE_LINGER,
  REACTOR_STREAM_STATE_ERROR
};

typedef struct reactor_stream reactor_stream;
struct reactor_stream
{
  int           state;
  reactor_user  user;
  int           ref;
  int           fd;
  buffer        input;
  buffer        output;
};

typedef struct reactor_stream_data reactor_stream_data;
struct reactor_stream_data
{
  void         *base;
  size_t        size;
};

void reactor_stream_hold(reactor_stream *);
void reactor_stream_release(reactor_stream *);
void reactor_stream_open(reactor_stream *, reactor_user_callback *, void *, int);
void reactor_stream_close(reactor_stream *);
void reactor_stream_write(reactor_stream *, void *, size_t);
void reactor_stream_flush(reactor_stream *);
void reactor_stream_write_notify(reactor_stream *);
void reactor_stream_data_consume(reactor_stream_data *, size_t);

#endif /* REACTOR_STREAM_H_INCLUDED */
