# Tutorial 1 - first program

The "first" program (that's its name) gets you an access token if you don't already have one.
Let's compile it. These instructions are for Mac OS X. Linux will be very similar, and Windows should also be transferrable. 
The code should be cross-platform. These instructions assume that libcurl and its headers are installed and included in the PATH.

`gcc -lcurl -I include/ -o example_first first.c misc.c`

*Note: misc.c is a small local library of functions used across these programs. The local header files are found in the include/ directory, including misc.h - thus is -I flag.*

Now execute:

`./example_first`

The output of "first" is ultimately a buffer of JSON data. Included in the data is an access token good for 24 hours and a refresh token (used to ask for a new access token) good for 24 hours. 
As long as you refresh every 24 hours or sooner you never need to deal with auth codes again. 
If the deadline passess the access token will expire and you will need to start over again by getting a new temporary auth code, running the "first" executible again, and so on.


## Optional: How to get a temporary authorization code before executing "first"

Prior to running the first program (e.g. running ./first on Mac or Linux) you can visit the following link ot get your temporary auth code beforehand. "First" will give you the same URL and ask you to retreive the auth code when you run it anyway. If you do this first, you can paste in the auth code right away when first asks you for it.

*Note: The auth code is a long string of numbers and letters. if you already have the temporary auth code, you can actually paste it into the first command-line argument when you run the executible:
`./first <auth_code>` (the carats are not included)
If you don't, first will just ask you for it as soon as it starts up.*

Link to get the temporary auth code:
[Click this link to be directed to freesound.org](https://freesound.org/apiv2/outh2/authorize/?client_id=1k4d2Azct3D650WgIFbh&response_type=code)
Once there, you will be asked to sign in using your freesound account and then authorize the app from inside your account.
If you click authorize, freesound will give you the temporary authorization code.

# Tutorial 2 - Download a sound.

You need to have a valid access token to do this.

Compile the down1 executible (for Mac OS X - other operating systems, the process is similar).

`gcc -lcurl -I include/ -o example_down1 down1.c misc.c` (you can give the -o flag any name you want the reuslting executible file to be named, I went with `example_down1`)

And execute the resulting program:

`./example_down1`

If you do that you will be asked right away to enter you access token. Alternatively, put the access token in as the first command-line argument like so:

`./example_down1 <acessToken>`

A soundfile will be downloaded from freesound's server and stored in this directory as a file named "out.wav"
