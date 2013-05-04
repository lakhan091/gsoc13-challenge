Openlighting GSOC 2013 Challenge
================================

This Repo is created in response to the challenge given to GSOC applicants by Open Lighting. <br>
Challange home-page: http://www.opendmx.net/index.php/GSOC_Challenge

Steps to be followed:
###1] Build source files


<code>
sh ./build.sh
</code>

Compiled files can be found under 'build' directory.

###2] Execute


######First run the olad server:
<code>
olad -l 3
</code>

######Monitor:
<code>
./build/monitor
</code>

######Client
<code>
./build/client
</code>

Client will send 20 channels to ArtNet input port which is patched to universe 1.

