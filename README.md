# minitalk
Who don't talk. Minitalk!!!

Minitalk is a server/client project aiming to send and receive text information using `UNIX signals`.

In order to try my code, please use `make` or `make all`

When you execute the server, the server will print the process ID of itself and waiting for the signals from client. `SIGUSRx`
Once the signal received, server will decode the signal into the binary and combine it from LSB to MSB until received 8 bits.
After that, these are converted to the character and print to the screen.

For the client, user will input the "PID" of the server as well as the sending text to the program.
Onced executing, the client will look into each characters, convert to binary and finally send it to the server.
