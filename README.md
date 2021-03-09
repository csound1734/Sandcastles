Compile the .c files with the -lcurl flag set to create the executables.

E.g.

`gcc -lcurl -o first first.c`
`gcc -lcurl -o first fresh.c`
`gcc -lcurl -o first down1.c`

# Refreshing a current access token
If you access token is stil current (see last few lines of outputfeb22 to check this),

`./fresh {{ACCESS_TOKEN}} ` to get a refresh access token. Refresh once every 24 hours at least.
(this comes from the fresh.c source file, of course)

# Getting a new access token
First use your web browser to visit:

`https://freesound.org/apiv2/oauth2/authorize/?client_id=1k4d2Azct3D650WgIFbh&response_type=code`

It will ask you to log in to Freesound with your Freesound account, then ask you for authorization for Sandcastles. Click Authorize. The next page will give you an authorization code. Copy it. The authorization code is only good for 10 minutes. The rest of getting an access token can be done with the executibles created by this repo. read on.

In your terminal type ./first then paste the authorization code. first is a c program that asks you for an authorization code and then gets an access token (good for 24 hours and comes with refresh token). When you run first and give it an authorization code, your access token arrives inside of the header when curl gets a response. Save the response that curl prints to stdout when you run first. 

By the way, if you forget and run first with only one argument (i.e. without an authorization code), first will ask you for an authorization code and give you the URL shown above. It will wait for you to come back and enter the authorization code before proceeding as usual to get the access token.

# Using sound resources with a current access token

Once you have an access token avilable

`./sandcastles_down1` is an executible (source code: down1.c) representing a simple download. The sound
 will be downloaded into out.wav, which will be overwritten if it exists.


