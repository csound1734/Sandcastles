# Tutorial 1 - first program

The "first" program (that's its name) gets you an access token if you don't already have one.
Let's compile it. These instructions are for Mac OS X. Linux will be very similar, and Windows should also be transferrable. 
The code should be cross-platform. These instructions assume that libcurl and its headers are installed and included in the PATH.

`gcc -lcurl -I include/ -o example_first first.c misc.c`

*Note: misc.c is a small local library of functions used across these programs. The local header files are found in the include/ directory, including misc.h - thus is -I flag.*

The output of "first" is ultimately a buffer of JSON data. Included in the data is an access token good for 24 hours and a refresh token (used to ask for a new access token) good for 24 hours. 
As long as you refresh every 24 hours or sooner you never need to deal with auth codes again. 
If the deadline passess the access token will expire and you will need to start over again by getting a new temporary auth code, running the "first" executible again, and so on.


# How to get an authorization code (good for only 10 minutes - tradable for access token)

Prior to running the first program (e.g. running ./first on Mac or Linux) you can visit the following link ot get your temporary auth code beforehand. "First" will give you the same URL and ask you to retreive the auth code when you run it anyway. If you do this first, you can paste in the auth code right away when first asks you for it.

*Note: if you already have the temporary auth code, you can actually paste it into the first command-line argument when you run the executible. If you don't, first will just ask you for it as soon as it starts up.*

Link to get the temporary auth code:
[Click this link to be directed to freesound.org](https://freesound.org/apiv2/outh2/authorize/?client_id=1k4d2Azct3D650WgIFbh&response_type=code)
Once there, you will be asked to sign in using your freesound account and then authorize the app from inside your account.
If you click authorize, freesound will give you the temporary authorization code.
