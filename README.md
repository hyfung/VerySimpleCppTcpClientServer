# Sample TCP Client and Server

### Compilation
```bash
make all
```

### Running
First run the server, you can also supply -p PORT to specify a port larger than 1023

By the server listens to 0.0.0.0
```bash
./Server
```

Then run the client
```bash
./Client -h HOST_IP -p HOST_PORT
```
