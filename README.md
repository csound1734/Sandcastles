If you access token is stil current (see last few lines of outputfeb22 to check this),

`./fresh {{ACCESS_TOKEN}} ` to get a refresh access token. Refresh once every 24 hours at least.
(this comes from the fresh.c source file, of course)

To get a new access token run `./sandcastles` (from the auth1.c source file)

`./sandcastles_down1` is an executible (source code: down1.c) representing a simple download. The sound
 will be downloaded into out.wav, which will be overwritten if it exists.


