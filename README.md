# test
```bash
nc -u 127.0.0.1 10000
socat -d -d pty,link=/dev/ttytest1,raw pty,link=/dev/ttytest2,raw
```
